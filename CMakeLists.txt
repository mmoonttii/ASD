cmake_minimum_required(VERSION 3.27)
project(ASD C)

set(CMAKE_C_STANDARD 11)
set(COMMON usefulFunctions.c
		usefulFunctions.h)

set(SELECTION_SORT E01/1_1selectionSortIter.c
		 		   E01/1_1selectionSortIter.h)

add_executable(1_1selectionSortIter
				${COMMON}
				${SELECTION_SORT})

add_executable(1_2antonino
				E01/1_2antonino.c)

add_executable(1_3linearSearch
				${COMMON}
				E01/1_3linearSearch.c)

add_executable(1_45binarySearch
				${COMMON}
				E01/1_45binarySearch.c)

add_executable(2_1selSortRicor
				${COMMON}
				E02/2_1selSortRicor.c)

add_executable(2_2confrontoSelectionSort
				${COMMON}
        		E02/2_2confrontoSelectionSort.c)

add_executable(2_3hotel
				E02/2_3hotel.c)

add_executable(3_1KMP
				${COMMON}
				E03/3_1KMP.c)

add_executable(4_5amazon
				${COMMON}
				E04/4_5amazon.c)

add_executable(5_spotify
				E05/5_spotify.c)

add_executable(6_alberi
				E06/6_alberiDecisionali.c)

add_executable(10_parcheggio
				E10/10_parcheggio.c)
add_executable(report
				${COMMON}
				${SELECTION_SORT}
				report/report.c)
