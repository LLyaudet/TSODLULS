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

Most of the code here is from glibc:
  Written by Douglas C. Schmidt (schmidt@ics.uci.edu).
  Copyright (C) 1991-2018 Free Software Foundation, Inc.

Modifications in this library:
©Copyright 2018-2022 Laurent Lyaudet
*/



/**
 * Sorting functions for long nextified strings
 * Insertion sort from qsort from glibc with long cells.
 */
//int TSODLULS_insertion_sort__long__mark1(
//  t_TSODLULS_sort_element* arr_elements,
//  size_t i_number_of_elements
//){
  t_TSODLULS_sort_element tmp_cell;//for swapping
  size_t i__compare;
  size_t i_max__compare;
  int i_result__compare;

  if(i_number_of_elements < 2){
    return 0;
  }

  if(i_number_of_elements == 2){
    TSODLULS_set_min_length__macraff(i_max__compare, &(arr_elements[0]), &(arr_elements[1]));
    for(i__compare = 0; i__compare < i_max__compare; ++i__compare){
      i_result__compare = ((int)(arr_elements[0].s_key[i__compare])) - ((int)(arr_elements[1].s_key[i__compare]));
      if(i_result__compare != 0){
        if(i_result__compare > 0){
          tmp_cell = arr_elements[1]; arr_elements[1] = arr_elements[0]; arr_elements[0] = tmp_cell;
        }
        break;
      }
    }
    return 0;
  }

  {
    //technical def without real meaning
    #define TSODLULS_MAX_THRESH 2
    //but this one sets that we will not use the threshold in fragment
    #define TSODLULS_OPTIMIZE_INSERTION_SORT_WITHOUT_THRESHOLD 1
    t_TSODLULS_sort_element* const start_ptr = arr_elements;
    t_TSODLULS_sort_element* const end_ptr = &start_ptr[(i_number_of_elements - 1)];
    #include "../f/fragment_insertion_sort_with_threshold_for_long_cells.c"
    #undef TSODLULS_OPTIMIZE_INSERTION_SORT_WITHOUT_THRESHOLD
    #undef TSODLULS_MAX_THRESH
  }

  return 0;
//}//end function TSODLULS_insertion_sort__long__mark1

