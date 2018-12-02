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
