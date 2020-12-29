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

©Copyright 2018-2020 Laurent Lyaudet
*/

#include "TSODLULS.h"



//------------------------------------------------------------------------------------
//External functions
//------------------------------------------------------------------------------------
/**
 * Sorting functions for short nextified strings
 * The current state of the art sorting function for nextified strings.
 * Its implementation may change without warning.
 */
int TSODLULS_sort__short(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
){
  return TSODLULS_sort_radix8_count_insertion__short(arr_elements, i_number_of_elements, i_max_length);
}//end function TSODLULS_sort()



/**
 * Sorting functions for short nextified strings
 * The current state of the art stable sorting function for nextified strings.
 * Its implementation may change without warning.
 */
int TSODLULS_sort_stable__short(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
){
  return TSODLULS_sort_radix8_count_insertion__short(arr_elements, i_number_of_elements, i_max_length);
}//end function TSODLULS_sort_stable()



/**
 * Sorting functions for short nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 */
int TSODLULS_sort_radix8_count__short(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
){
  #include "./competitor_algorithms/b/body_TSODLULS_sort_radix8_count__short__mark1.c"
}//end function TSODLULS_sort_radix8_count__short()



/**
 * Sorting functions for short nextified strings
 * Qsort from glibc inlined with short cells.
 */
int TSODLULS_qsort_inlined__short(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements
){
  #define TSODLULS_STACK_SIZE  (CHAR_BIT * sizeof(size_t))
  #define TSODLULS_PUSH(low, high)  ((void) ((top->p_low = (low)), (top->p_high = (high)), ++top))
  #define TSODLULS_POP(low, high)  ((void) (--top, (low = top->p_low), (high = top->p_high)))
  #define TSODLULS_STACK_NOT_EMPTY  (stack < top)
  #define TSODLULS_MAX_THRESH 4
  #include "./competitor_algorithms/b/body_TSODLULS_qsort_inlined__short.c"
  #undef TSODLULS_STACK_SIZE
  #undef TSODLULS_PUSH
  #undef TSODLULS_POP
  #undef TSODLULS_STACK_NOT_EMPTY
  #undef TSODLULS_MAX_THRESH
}//end function TSODLULS_qsort_inlined__short



/**
 * Sorting functions for short nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements to sort is at most 5, we use insertion sort
 * A variant with single memory allocation adapted to the max-depth.
 * No insertion sort if there is more than 5 elements and it is 8 bits datatype.
 * This is the current best algorithm and it is a stable one :)
 */
int TSODLULS_sort_radix8_count_insertion__short(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
){
  #define TSODLULS_MAX_THRESH 5
  #include "./competitor_algorithms/b/body_TSODLULS_sort_radix8_count_insertion__short__mark2.c"
  #undef TSODLULS_MAX_THRESH
}//end function TSODLULS_sort_radix8_count_insertion__short()



