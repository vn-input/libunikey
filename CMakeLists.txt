cmake_minimum_required (VERSION 3.0)
project (libunikey)

add_compile_options(-std=c++11 -Werror -Wall -pedantic)

add_subdirectory(ukengine)
add_subdirectory(src)
add_subdirectory(tests)
