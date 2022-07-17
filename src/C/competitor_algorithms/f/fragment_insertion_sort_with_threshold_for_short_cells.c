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

#if TSODLULS_MAX_THRESH > 1
//t_TSODLULS_sort_element__short* const start_ptr = arr_elements;
//t_TSODLULS_sort_element__short* const end_ptr = &start_ptr[(i_number_of_elements - 1)];
{
  t_TSODLULS_sort_element__short* tmp_ptr = start_ptr;
  #if TSODLULS_OPTIMIZE_INSERTION_SORT_WITHOUT_THRESHOLD
  t_TSODLULS_sort_element__short* thresh = end_ptr;
  #else
  t_TSODLULS_sort_element__short* thresh = TSODLULS_min_exp(end_ptr, start_ptr + TSODLULS_MAX_THRESH - 1);
  #endif
  t_TSODLULS_sort_element__short* run_ptr;
  t_TSODLULS_sort_element__short tmp_cell;

  /* Find smallest element in first threshold and place it at the
     array's beginning.  This is the smallest array element,
     and the operation speeds up insertion sort's inner loop. */

  for(run_ptr = tmp_ptr + 1; run_ptr <= thresh; ++run_ptr){
    if(run_ptr->i_key < tmp_ptr->i_key){
      tmp_ptr = run_ptr;
    }
  }

  if(tmp_ptr != start_ptr){
    tmp_cell = *tmp_ptr; *tmp_ptr = *start_ptr; *start_ptr = tmp_cell;//swapping
  }

  /* Insertion sort, running from left-hand-side up to right-hand-side.  */
  run_ptr = start_ptr + 1;
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
}
#endif
