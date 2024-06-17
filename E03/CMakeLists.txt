cmake_minimum_required(VERSION 3.27)
project(E03 C)

set(CMAKE_C_STANDARD 11)
set(COMMON ../usefulFunctions.c
		../usefulFunctions.h)

add_executable(03_1KMP
                03_1KMP.c)

add_executable(03_3KMPCircolare
                03_3KMPCircolare.c)