
cmake_minimum_required(VERSION 3.12)

project(ft_ssl)

add_compile_options(-Wall -Wextra -Werror)

set(CMAKE_STATIC_LIBRARY_PREFIX "")
add_library(libssl STATIC "")
target_include_directories(libssl PRIVATE include libft/include)
target_sources(libssl PRIVATE src/libssl_md5.c)

add_executable(ft_ssl
		src/main.c
		src/md5.c
		src/read_params.c
		src/read_file.c
		src/error.c
		src/util.c
)

target_include_directories(ft_ssl
	PRIVATE
		include
		libft/include
		libssl/include
)

add_subdirectory(libft)

target_link_libraries(ft_ssl libft libssl)

