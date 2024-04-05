cmake_minimum_required(VERSION 3.24)
project(algorithm_c C)

set(CMAKE_C_STANDARD 17)

add_executable(algorithm_c src/sort/sort.h src/sort/sort.c src/main.c src/sort/util.h src/sort/util.c src/stack/stack.h src/array/array.h test/test_sort.h test/test_sort.c src/stack/stack.c test/test_stack.h test/test_stack.c)

