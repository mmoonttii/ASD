cmake_minimum_required(VERSION 3.27)
project(ASD C)

set(CMAKE_C_STANDARD 11)
set(COMMON usefulFunctions.c
		usefulFunctions.h)

add_executable(01_1selectionSortIter
				${COMMON}
				E01/01_1selectionSortIter.c)

add_executable(01_2antonino
				E01/01_2antonino.c)

add_executable(01_3linearSearch
				${COMMON}
				E01/01_3linearSearch.c)

add_executable(01_45binarySearch
				${COMMON}
				E01/01_45binarySearch.c)

add_executable(02_1selSortRicor
				${COMMON}
				E02/02_1selSortRicor.c)

add_executable(02_2confrontoSelectionSort
				${COMMON}
        		E02/02_2confrontoSelectionSort.c)

add_executable(02_3hotel
				E02/02_3hotel.c)

add_executable(03_1KMP
				${COMMON}
				E03/03_1KMP.c)

add_executable(03_3KMPCircolare
				${COMMON}
				E03/03_3KMPCircolare.c
				E03/03_3KMPCircolare.c)

add_executable(04_amazon
				${COMMON}
				E04/04_amazon.c)

add_executable(05_spotify
				E05/05_spotify.c)

add_executable(06_alberi
				E06/06_alberiDecisionali.c)

add_executable(07_er
				E07/07_er.c)

add_executable(10_parcheggio
				E10/10_parcheggio.c)

add_executable(report
				${COMMON}
				report/report.c)
