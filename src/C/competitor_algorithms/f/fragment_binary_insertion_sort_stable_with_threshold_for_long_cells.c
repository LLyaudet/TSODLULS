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
©Copyright 2018-2021 Laurent Lyaudet
*/

#if TSODLULS_MAX_THRESH > 1
//t_TSODLULS_sort_element* const start_ptr = arr_elements;
//t_TSODLULS_sort_element* const end_ptr = &start_ptr[(i_number_of_elements - 1)];
//t_TSODLULS_sort_element tmp_cell;
{
  t_TSODLULS_sort_element* run_ptr;

  /* Insertion sort, running from left-hand-side up to right-hand-side.  */
  run_ptr = start_ptr;
  while((++run_ptr) <= end_ptr){
    //[start_ptr, search_range_left[ <= run_ptr
    t_TSODLULS_sort_element* search_range_left = run_ptr - TSODLULS_MAX_THRESH + 1;
    //[search_range_right, run_ptr[ > run_ptr
    t_TSODLULS_sort_element* search_range_right = run_ptr;
    t_TSODLULS_sort_element* search_range_middle;
    if(search_range_left < start_ptr){
      search_range_left = start_ptr;
    }
    do{
      // the compiler should optimize "/ 2" to ">> 1", otherwise change compiler :P
      search_range_middle = search_range_left + ((search_range_right - search_range_left) / 2);
      int middle_is_more = 0;
      for(
        size_t j = 0, j_max = TSODLULS_min_exp(run_ptr->i_key_size, search_range_middle->i_key_size);
        j < j_max;
        ++j
      ){
        if(search_range_middle->s_key[j] < run_ptr->s_key[j]){
          break;
        }
        if(search_range_middle->s_key[j] > run_ptr->s_key[j]){
          middle_is_more = 1;
          break;
        }
      }
      if(middle_is_more){
        search_range_right = search_range_middle;
      }
      else{
        search_range_left = search_range_middle + 1;
      }
    }while(search_range_left < search_range_right);
    if(search_range_right != run_ptr){
      tmp_cell = *run_ptr;
      t_TSODLULS_sort_element* hi;
      t_TSODLULS_sort_element* lo;
      for (hi = lo = run_ptr; (--lo) >= search_range_right; hi = lo){
        *hi = *lo;
      }
      *hi = tmp_cell;
    }
  }
}
#endif
