
CC = gcc
override CFLAGS += -Wall -Wextra -Werror
override LDFLAGS +=
SOURCE = src/main.c        \
         src/md5.c         \
         src/read_params.c \
         src/read_file.c   \
         src/error.c       \
         src/util.c
OBJECT = $(SOURCE:.c=.o)
NAME   = ft_ssl
LIBFT  = libft/libft.a
LIBSSL = libssl.a
LIBSSL_SOURCE = src/libssl_md5.c
LIBSSL_OBJECT = $(LIBSSL_SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(LIBSSL) $(LIBFT) $(OBJECT)
	@echo "\033[34mcreating $(NAME)\033[39m"
	@$(CC) $(LDFLAGS) -o $(NAME) $(LIBSSL) $(LIBFT) $(OBJECT)

$(LIBSSL): $(LIBSSL_OBJECT)
	@echo "\033[34mcreating $@\033[39m"
	@ar rc $@ $<
	@echo "\033[34mgenerating index to $@\033[39m"
	@ranlib $@

$(LIBFT):
	@make -C libft

%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -Ilibft/include -o $@ -c $<

test: $(NAME) main.o
	@$(CC) $(LDFLAGS) -o libft_malloc_test main.o $(NAME)

clean:
	@make -C libft clean
	@echo "\033[34mremoving object files of $(NAME)\033[39m"
	@rm -f $(OBJECT) $(LIBSSL) $(LIBSSL_OBJECT)

fclean:
	@make -C libft fclean
	@echo "\033[34mremoving object files of $(NAME)\033[39m"
	@rm -f $(OBJECT) $(LIBSSL) $(LIBSSL_OBJECT)
	@echo "\033[34mremoving $(NAME)\033[39m"
	@rm -f $(NAME)

re: fclean all

