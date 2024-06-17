cmake_minimum_required(VERSION 3.27)
project(E11 C)

set(CMAKE_C_STANDARD 11)
set(COMMON ../usefulFunctions.c
		../usefulFunctions.h)

add_executable(11_1insertionSort
                11_1insertionSort.c
                ${COMMON})