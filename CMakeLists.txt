cmake_minimum_required(VERSION 3.27)
project(ASD C)

set(CMAKE_C_STANDARD 11)
set(COMMON usefulFunctions.c
		usefulFunctions.h)

add_executable(2_2confrontoSelectionSort
				${COMMON}
				E02/2_2_confrontoSelectionSort.c
)


