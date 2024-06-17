cmake_minimum_required(VERSION 3.27)
project(E12 C)

set(CMAKE_C_STANDARD 11)
set(COMMON ../usefulFunctions.c
		../usefulFunctions.h)

add_executable(12_1mergeSort
                12_1mergeSort.c
                ${COMMON})

add_executable(12_2heapSort
                12_2heapSort.c
                ${COMMON})
