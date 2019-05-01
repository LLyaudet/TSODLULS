/*
This file is part of TSODLULS library.

TSODLULS is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

TSODLULS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with TSODLULS.  If not, see <http://www.gnu.org/licenses/>.

©Copyright 2018 Laurent Lyaudet
*/
#ifndef DEF_TSODLULS__COMPETITOR
#define DEF_TSODLULS__COMPETITOR

#include "../TSODLULS.h"
#include <unistd.h>

//------------------------------------------------------------------------------------
//Conversion of finite orders
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//Sorting long orders
//------------------------------------------------------------------------------------
/**
 * Sorting functions for long nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 */
int TSODLULS_sort_radix8_count__mark1(t_TSODLULS_sort_element* arr_elements, size_t i_number_of_elements);



/**
 * Sorting functions for long nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements to sort is at most 5, we use insertion sort
 */
int TSODLULS_sort_radix8_count_insertion__mark1(
  t_TSODLULS_sort_element* arr_elements,
  size_t i_number_of_elements
);



/**
 * Sorting functions for long nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements to sort is at most: 5 for initial sort or 2 for radix sequel, we use insertion sort.
 */
int TSODLULS_sort_radix8_count_insertion__mark2(
  t_TSODLULS_sort_element* arr_elements,
  size_t i_number_of_elements
);



/**
 * Sorting functions for long nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements to sort is at most: 5 for initial sort or 2 for radix sequel, we use insertion sort.
 * No data move if the array is already sorted (code variant).
 */
int TSODLULS_sort_radix8_count_insertion__mark3(
  t_TSODLULS_sort_element* arr_elements,
  size_t i_number_of_elements
);



//------------------------------------------------------------------------------------
//Sorting short orders
//------------------------------------------------------------------------------------
/**
 * Sorting functions for short nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 */
int TSODLULS_sort_radix8_count__short__mark1(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
);



/**
 * Sorting functions for short nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * A variant with single memory allocation, but it requires a lot of it.
 * It is slightly faster for 32 and 64 bits datatypes, but greatly slower for 8 bits datatypes.
 */
int TSODLULS_sort_radix8_count__short__mark2(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
);



/**
 * Sorting functions for short nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * A variant with single memory allocation adapted to the max-depth.
 * It is slightly faster for 32 and 64 bits datatypes.
 */
int TSODLULS_sort_radix8_count__short__mark3(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
);



/**
 * Sorting functions for short nextified strings
 * A sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements is below some threshold, it uses glibc qsort.
 */
int TSODLULS_sort_radix8_count_qsort__short(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
);



/**
 * Sorting functions for short nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements to sort is at most 5, we use insertion sort
 * A variant with single memory allocation adapted to the max-depth.
 */
int TSODLULS_sort_radix8_count_insertion__short__mark1(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
);



/**
 * Sorting functions for short nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements to sort is at most 5, we use insertion sort
 * A variant with single memory allocation adapted to the max-depth.
 * No insertion sort if there is more than 5 elements and it is 8 bits datatype.
 */
int TSODLULS_sort_radix8_count_insertion__short__mark2(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
);



/**
 * Sorting functions for short nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements to sort is at most 5, we use insertion sort
 * A variant with single memory allocation adapted to the max-depth.
 * No insertion sort if there is more than 5 elements and it is 8 bits datatype.
 * Simplified inner loops ( if(i_max_length > current_instance.i_depth + 1) )
 */
int TSODLULS_sort_radix8_count_insertion__short__mark3(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
);



/**
 * Sorting functions for short nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements to sort is at most 5, we use insertion sort
 * A variant with single memory allocation adapted to the max-depth.
 * No insertion sort if there is more than 5 elements and it is 8 bits datatype.
 * Simplified inner loops ( if(i_max_length > current_instance.i_depth + 1) )
 * No instance in copy buffer, after each step copy is moved in original buffer
 */
int TSODLULS_sort_radix8_count_insertion__short__mark4(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
);



/**
 * Sorting functions for short nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements to sort is at most 5, we use insertion sort.
 * A variant with single memory allocation adapted to the max-depth.
 * No insertion sort if there is more than 5 elements and it is 8 bits datatype.
 * No data move if the array is already sorted.
 */
int TSODLULS_sort_radix8_count_insertion__short__mark5(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
);



/**
 * Sorting functions for short nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements to sort is at most 5, we use insertion sort.
 * A variant with single memory allocation adapted to the max-depth.
 * No insertion sort if there is more than 5 elements and it is 8 bits datatype.
 * No data move if the array is already sorted (code variant).
 */
int TSODLULS_sort_radix8_count_insertion__short__mark6(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
);



#include "./TSODLULS__competitor__generated_qsort.h"



//------------------------------------------------------------------------------------
//Comparing
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//Miscellaneous
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//Padding
//------------------------------------------------------------------------------------

#endif
