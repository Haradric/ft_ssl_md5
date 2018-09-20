
cmake_minimum_required(VERSION 3.12)

project(ft_ssl)
add_compile_options(-Wall -Wextra -Werror)
set(CMAKE_STATIC_LIBRARY_PREFIX "")

add_library(libssl STATIC "")
add_executable(ft_ssl "")

target_sources(libssl
	PRIVATE
		src/libssl_md5.c
		src/libssl_sha256.c
)

target_sources(ft_ssl
	PRIVATE
		src/main.c
		src/md5.c
		src/sha256.c
		src/read_params.c
		src/read_stdin.c
		src/error.c
		src/util.c
)

target_include_directories(ft_ssl
	PRIVATE
		include
		libft/include
		libssl/include
)

target_include_directories(libssl
	PRIVATE
		include
		libft/include
)

add_subdirectory(libft)

target_link_libraries(ft_ssl libft libssl)
