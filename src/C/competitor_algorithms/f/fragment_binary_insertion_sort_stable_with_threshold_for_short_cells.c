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

Some of the code here is from glibc:
  Written by Douglas C. Schmidt (schmidt@ics.uci.edu).
  Copyright (C) 1991-2018 Free Software Foundation, Inc.

Modifications in this library to do a *binary* insertion sort:
©Copyright 2018-2023 Laurent Lyaudet
*/

#if TSODLULS_MAX_THRESH > 1
//t_TSODLULS_sort_element__short* const start_ptr = arr_elements;
//t_TSODLULS_sort_element__short* const end_ptr = &start_ptr[(i_number_of_elements - 1)];
{
  t_TSODLULS_sort_element__short* run_ptr;
  t_TSODLULS_sort_element__short tmp_cell;

  /* Insertion sort, running from left-hand-side up to right-hand-side.  */
  run_ptr = start_ptr;
  while((++run_ptr) <= end_ptr){
    #if TSODLULS_OPTIMIZE_INSERTION_SORT_WITHOUT_THRESHOLD
    //[start_ptr, search_range_left[ <= run_ptr
    t_TSODLULS_sort_element__short* search_range_left = start_ptr;
    #else
    //[start_ptr, search_range_left[ <= run_ptr
    t_TSODLULS_sort_element__short* search_range_left = run_ptr - TSODLULS_MAX_THRESH + 1;
    if(search_range_left < start_ptr){
      search_range_left = start_ptr;
    }
    #endif
    //[search_range_right, run_ptr[ > run_ptr
    t_TSODLULS_sort_element__short* search_range_right = run_ptr;
    t_TSODLULS_sort_element__short* search_range_middle;
    do{
      // the compiler should optimize "/ 2" to ">> 1", otherwise change compiler :P
      search_range_middle = search_range_left + ((search_range_right - search_range_left) / 2);
      if(run_ptr->i_key >= search_range_middle->i_key){
        search_range_left = search_range_middle + 1;
      }
      else{
        search_range_right = search_range_middle;
      }
    }while(search_range_left < search_range_right);
    if(search_range_right != run_ptr){
      tmp_cell = *run_ptr;
      t_TSODLULS_sort_element__short* hi;
      t_TSODLULS_sort_element__short* lo;
      for (hi = lo = run_ptr; (--lo) >= search_range_right; hi = lo){
        *hi = *lo;
      }
      *hi = tmp_cell;
    }
  }
}
#endif
