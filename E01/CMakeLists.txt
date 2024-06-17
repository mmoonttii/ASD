cmake_minimum_required(VERSION 3.27)
project(E01 C)

set(CMAKE_C_STANDARD 11)
set(COMMON ../usefulFunctions.c
		../usefulFunctions.h)

add_executable(01_1selectionSortIter
				${COMMON}
				01_1selectionSortIter.c)

add_executable(01_2antonino
				01_2antonino.c)

add_executable(01_3linearSearch
				${COMMON}
				01_3linearSearch.c)

add_executable(01_45binarySearch
				${COMMON}
				01_45binarySearch.c)