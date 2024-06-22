cmake_minimum_required(VERSION 3.27)
project(E02 C)

set(CMAKE_C_STANDARD 11)
set(COMMON ../usefulFunctions.c
		../usefulFunctions.h)

add_executable(02_1selSortRicorsivo
				${COMMON}
				02_1selSortRicor.c)

add_executable(02_2confrontoSelectionSort
				02_2confrontoSelectionSort.c)

add_executable(02_3hotel
				02_3hotel.c)