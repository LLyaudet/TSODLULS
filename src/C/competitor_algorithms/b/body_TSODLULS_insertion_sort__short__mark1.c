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
 * Sorting functions for short nextified strings
 * Insertion sort from qsort from glibc with short cells.
 */
//int TSODLULS_insertion_sort__short__mark1(
//  t_TSODLULS_sort_element__short* arr_elements,
//  size_t i_number_of_elements
//){
  t_TSODLULS_sort_element__short* const end_ptr = &arr_elements[(i_number_of_elements - 1)];
  t_TSODLULS_sort_element__short* tmp_ptr = arr_elements;
  t_TSODLULS_sort_element__short* run_ptr;
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

  /* Find smallest element in array and place it at the array's beginning.
  This operation speeds up insertion sort's inner loop.
  But it is not stable. */

  for(run_ptr = tmp_ptr + 1; run_ptr <= end_ptr; ++run_ptr){
    if(run_ptr->i_key < tmp_ptr->i_key){
      tmp_ptr = run_ptr;
    }
  }

  if(tmp_ptr != arr_elements){
    tmp_cell = *tmp_ptr; *tmp_ptr = *arr_elements; *arr_elements = tmp_cell;//swapping
  }

  /* Insertion sort, running from left-hand-side up to right-hand-side.  */
  run_ptr = arr_elements + 1;
  while((++run_ptr) <= end_ptr){
    tmp_ptr = run_ptr - 1;
    while(run_ptr->i_key < tmp_ptr->i_key){
      --tmp_ptr;
    }
    ++tmp_ptr;
    if(tmp_ptr != run_ptr){
      tmp_cell = *run_ptr;
      t_TSODLULS_sort_element__short* hi;
      t_TSODLULS_sort_element__short* lo;
      for (hi = lo = run_ptr; (--lo) >= tmp_ptr; hi = lo){
        *hi = *lo;
      }
      *hi = tmp_cell;
    }
  }
  return 0;
//}//end function TSODLULS_insertion_sort__short__mark1
