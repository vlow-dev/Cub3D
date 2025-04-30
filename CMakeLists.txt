cmake_minimum_required(VERSION 3.10)
project(Cub3d C)

# export compile‑commands JSON
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Werror)

# your headers
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/libft/include)
include_directories(${CMAKE_SOURCE_DIR}/minilibx-linux)

# grab every .c
file(GLOB_RECURSE SRC_FILES
  ${CMAKE_SOURCE_DIR}/src/*.c
  ${CMAKE_SOURCE_DIR}/libft/src/*.c
  ${CMAKE_SOURCE_DIR}/minilibx-linux/*.c
)

# declare a target (no build will be done unless you invoke it)
add_executable(${PROJECT_NAME} ${SRC_FILES})
