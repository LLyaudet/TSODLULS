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

#include "TSODLULS__competitor.h"



//------------------------------------------------------------------------------------
//External functions
//------------------------------------------------------------------------------------
/**
 * Sorting functions for long nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 */
int TSODLULS_sort_radix8_count__mark1(
  t_TSODLULS_sort_element* arr_elements,
  size_t i_number_of_elements
){
  #include "./b/body_TSODLULS_sort_radix8_count__mark1.c"
}//end function TSODLULS_sort_radix8_count__mark1()



/**
 * Sorting functions for long nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements to sort is at most 5, we use insertion sort.
 */
int TSODLULS_sort_radix8_count_insertion__mark1(
  t_TSODLULS_sort_element* arr_elements,
  size_t i_number_of_elements
){
  #define TSODLULS_MAX_THRESH 5
  #include "./b/body_TSODLULS_sort_radix8_count_insertion__mark1.c"
  #undef TSODLULS_MAX_THRESH
}//end function TSODLULS_sort_radix8_count_insertion__mark1()



/**
 * Sorting functions for long nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements to sort is at most: 5 for initial sort or 2 for radix sequel, we use insertion sort.
 */
int TSODLULS_sort_radix8_count_insertion__mark2(
  t_TSODLULS_sort_element* arr_elements,
  size_t i_number_of_elements
){
  #define TSODLULS_MAX_THRESH 5
  #define TSODLULS_MAX_THRESH_SEQUEL 2
  #include "./b/body_TSODLULS_sort_radix8_count_insertion__mark2.c"
  #undef TSODLULS_MAX_THRESH
  #undef TSODLULS_MAX_THRESH_SEQUEL
}//end function TSODLULS_sort_radix8_count_insertion__mark2()



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
){
  #define TSODLULS_MAX_THRESH 5
  #define TSODLULS_MAX_THRESH_SEQUEL 2
  #include "./b/body_TSODLULS_sort_radix8_count_insertion__mark3.c"
  #undef TSODLULS_MAX_THRESH
  #undef TSODLULS_MAX_THRESH_SEQUEL
}//end function TSODLULS_sort_radix8_count_insertion__mark3()



/**
 * Sorting functions for long nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements to sort is at most: 5 for initial sort or 2 for radix sequel, we use insertion sort.
 * No data move if the array is already sorted (code variant, double loop).
 */
int TSODLULS_sort_radix8_count_insertion__mark4(
  t_TSODLULS_sort_element* arr_elements,
  size_t i_number_of_elements
){
  #define TSODLULS_MAX_THRESH 5
  #define TSODLULS_MAX_THRESH_SEQUEL 2
  #include "./b/body_TSODLULS_sort_radix8_count_insertion__mark4.c"
  #undef TSODLULS_MAX_THRESH
  #undef TSODLULS_MAX_THRESH_SEQUEL
}//end function TSODLULS_sort_radix8_count_insertion__mark4()

