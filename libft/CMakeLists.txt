cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 11)
project(libft)
add_compile_options(-Wall -Wextra -Werror)
file(GLOB LIBFT "ft_*.c") # you can include files explicitly
add_library(libft STATIC ${LIBFT})
