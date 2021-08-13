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
©Copyright 2018-2021 Laurent Lyaudet
*/



/**
 * Sorting functions for long nextified strings
 * Insertion sort from qsort from glibc with long cells.
 */
//int TSODLULS_insertion_sort_stable__long__mark1(
//  t_TSODLULS_sort_element* arr_elements,
//  size_t i_number_of_elements
//){
  t_TSODLULS_sort_element* const end_ptr = &arr_elements[(i_number_of_elements - 1)];
  t_TSODLULS_sort_element* tmp_ptr = arr_elements;
  t_TSODLULS_sort_element* run_ptr;
  t_TSODLULS_sort_element tmp_cell;//for swapping
  size_t i__compare;
  size_t i_max__compare;
  int i_result__compare;
  int b_continue;

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

  /* Insertion sort, running from left-hand-side up to right-hand-side.  */
  run_ptr = arr_elements;
  while((++run_ptr) <= end_ptr){
    tmp_ptr = run_ptr - 1;
    b_continue = 1;
    while(b_continue > 0){
      b_continue = 0;
      TSODLULS_set_min_length__macraff(i_max__compare, run_ptr, tmp_ptr);
      for(i__compare = 0; i__compare < i_max__compare; ++i__compare){
        i_result__compare = ((int)(run_ptr->s_key[i__compare])) - ((int)(tmp_ptr->s_key[i__compare]));
        if(i_result__compare != 0){
          if(i_result__compare < 0){
            b_continue = 1;
            --tmp_ptr;
          }
          break;
        }
      }
      if(tmp_ptr < arr_elements){
        break;
      }
    }
    ++tmp_ptr;
    if(tmp_ptr != run_ptr){
      tmp_cell = *run_ptr;
      t_TSODLULS_sort_element* hi;
      t_TSODLULS_sort_element* lo;
      for (hi = lo = run_ptr; (--lo) >= tmp_ptr; hi = lo){
        *hi = *lo;
      }
      *hi = tmp_cell;
    }
  }
  return 0;
//}//end function TSODLULS_insertion_sort_stable__long__mark1

