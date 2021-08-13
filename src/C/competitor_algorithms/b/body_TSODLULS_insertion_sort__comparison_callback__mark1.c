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
 * Sorting functions using a comparison callback for arbitrary data structures.
 * Insertion sort from qsort from glibc with minor modifications.
 */
//int TSODLULS_insertion_sort__comparison_callback__mark1(
//  void* arr_elements,
//  size_t i_number_of_elements,
//  size_t i_element_size,
//  t_comparison_function fn_comparison
//){
//  #define TSODLULS_SWAP_VAR(a0,a1,a2) TSODLULS_SWAP_VAR_1(a0,a1,a2)
  char* const base_ptr = (char*) arr_elements;
  char* const end_ptr = &base_ptr[i_element_size * (i_number_of_elements - 1)];
  char* tmp_ptr = base_ptr;
  char* run_ptr;

  if(i_number_of_elements < 2){
    return 0;
  }

  /* Find smallest element in array and place it at the array's beginning.
  This operation speeds up insertion sort's inner loop.
  But it is not stable. */

  for(run_ptr = tmp_ptr + i_element_size; run_ptr <= end_ptr; run_ptr += i_element_size){
    if((*fn_comparison) ((void *) run_ptr, (void *) tmp_ptr) < 0){
      tmp_ptr = run_ptr;
    }
  }

  if(tmp_ptr != base_ptr){
    TSODLULS_SWAP_VAR(tmp_ptr, base_ptr, i_element_size);
  }

  /* Insertion sort, running from left-hand-side up to right-hand-side.  */
  run_ptr = base_ptr + i_element_size;
  while((run_ptr += i_element_size) <= end_ptr){
    tmp_ptr = run_ptr - i_element_size;
    while((*fn_comparison) ((void *) run_ptr, (void *) tmp_ptr) < 0){
      tmp_ptr -= i_element_size;
    }
    tmp_ptr += i_element_size;
    if(tmp_ptr != run_ptr){
      char* trav;

      trav = run_ptr + i_element_size;
      while(--trav >= run_ptr){
        char c = *trav;
        char* hi;
        char* lo;
        for (hi = lo = trav; (lo -= i_element_size) >= tmp_ptr; hi = lo){
          *hi = *lo;
        }
        *hi = c;
      }
    }
  }
  return 0;
//}//end function TSODLULS_insertion_sort__comparison_callback__mark1

