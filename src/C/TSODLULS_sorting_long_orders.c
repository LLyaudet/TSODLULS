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

©Copyright 2018-2021 Laurent Lyaudet
*/

#include "TSODLULS.h"



//------------------------------------------------------------------------------------
//External functions
//------------------------------------------------------------------------------------
/**
 * Sorting functions for long nextified strings
 * The current state of the art sorting function for nextified strings.
 * Its implementation may change without warning.
 */
int TSODLULS_sort(t_TSODLULS_sort_element* arr_elements, size_t i_number_of_elements){
  return TSODLULS_sort_radix8_count_insertion(arr_elements, i_number_of_elements);
}//end function TSODLULS_sort()



/**
 * Sorting functions for long nextified strings
 * The current state of the art stable sorting function for nextified strings.
 * Its implementation may change without warning.
 */
int TSODLULS_sort_stable(t_TSODLULS_sort_element* arr_elements, size_t i_number_of_elements){
  return TSODLULS_sort_radix8_count_insertion(arr_elements, i_number_of_elements);
}//end function TSODLULS_sort_stable()



/**
 * Sorting functions for long nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 */
int TSODLULS_sort_radix8_count(t_TSODLULS_sort_element* arr_elements, size_t i_number_of_elements){
  #include "./competitor_algorithms/b/body_TSODLULS_sort_radix8_count__mark1.c"
}//end function TSODLULS_sort_radix8_count()



/**
 * Sorting functions for long nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements to sort is at most: 5 for initial sort or 2 for radix sequel, we use insertion sort
 */
int TSODLULS_sort_radix8_count_insertion(
  t_TSODLULS_sort_element* arr_elements,
  size_t i_number_of_elements
){
  #define TSODLULS_MAX_THRESH 5
  #define TSODLULS_MAX_THRESH_SEQUEL 2
  #include "./competitor_algorithms/b/body_TSODLULS_sort_radix8_count_insertion__mark2.c"
  #undef TSODLULS_MAX_THRESH
  #undef TSODLULS_MAX_THRESH_SEQUEL
}//end function TSODLULS_sort_radix8_count_insertion()



