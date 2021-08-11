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

//------------------------------------------------------------------------------------
//Sorting short orders
//------------------------------------------------------------------------------------
/**
 * Sorting functions for short nextified strings
 * The current state of the art sorting function for short nextified strings.
 * Its implementation may change without warning.
 */
int TSODLULS_sort__short(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
);



/**
 * Sorting functions for short nextified strings
 * The current state of the art stable sorting function for short nextified strings.
 * Its implementation may change without warning.
 */
int TSODLULS_sort_stable__short(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
);



