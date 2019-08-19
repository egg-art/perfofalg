cmake_minimum_required(VERSION 3.14)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED TRUE)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wconversion -Wunused-result -pedantic")
#set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ggdb3")
#set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Ofast -g0 -march=native -mtune=native")

project(perfofalg)
add_executable(${PROJECT_NAME} "main.cpp" "sort_algs.cpp" "data_generator.cpp" "common.cpp")

set(SRC_IDE .clang-format)

add_custom_target(target_for_ide SOURCES ${SRC_IDE})

include_directories(./)
