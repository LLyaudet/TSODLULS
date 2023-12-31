/*
This file is part of TSODLULS.

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

©Copyright 2018-2023 Laurent Lyaudet
*/



/**
 * Sorting functions for short nextified strings.
 * Binary insertion sort stable with short cells.
 */
//int TSODLULS_binary_insertion_sort_stable__short__mark1(
//  t_TSODLULS_sort_element__short* arr_elements,
//  size_t i_number_of_elements
//){
  t_TSODLULS_sort_element__short tmp_cell;//for swapping

  if(i_number_of_elements < 2){
    return 0;
  }

  if(i_number_of_elements == 2){
    if(arr_elements[1].i_key < arr_elements[0].i_key){
      tmp_cell = arr_elements[1]; arr_elements[1] = arr_elements[0]; arr_elements[0] = tmp_cell;
    }
    return 0;
  }

  {
    //technical def without real meaning
    #define TSODLULS_MAX_THRESH 2
    //but this one sets that we will not use the threshold in fragment
    #define TSODLULS_OPTIMIZE_INSERTION_SORT_WITHOUT_THRESHOLD 1
    t_TSODLULS_sort_element__short* const start_ptr = arr_elements;
    t_TSODLULS_sort_element__short* const end_ptr = &start_ptr[(i_number_of_elements - 1)];
    #include "../f/fragment_binary_insertion_sort_stable_with_threshold_for_short_cells.c"
    #undef TSODLULS_OPTIMIZE_INSERTION_SORT_WITHOUT_THRESHOLD
    #undef TSODLULS_MAX_THRESH
  }

  return 0;
//}//end function TSODLULS_binary_insertion_sort_stable__short__mark1

