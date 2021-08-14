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
//char* const start_ptr = base_ptr;
//char* const end_ptr = &start_ptr[i_element_size * (i_number_of_elements - 1)];
{
  char* run_ptr;

  /* Insertion sort, running from left-hand-side up to right-hand-side.  */
  run_ptr = start_ptr;
  while((run_ptr += i_element_size) <= end_ptr){
    //[start_ptr, search_range_left[ <= run_ptr
    char* search_range_left = run_ptr - max_threshold_size;
    //[search_range_right, run_ptr[ > run_ptr
    char* search_range_right = run_ptr;
    char* search_range_middle;
    if(search_range_left < start_ptr){
      search_range_left = start_ptr;
    }
    do{
      // the compiler should optimize "/ 2" to ">> 1", otherwise change compiler :P
      search_range_middle = search_range_left + (((search_range_right - search_range_left) / i_element_size) / 2) * i_element_size;
      #if TSODLULS_COMPARE_CAN_ERROR
      int i_compare_result = TSODLULS_COMPARE_CALL(run_ptr, search_range_middle);
      if(i_compare_result <= -2){// user defined error codes
        return i_compare_result;
      }
      if(i_compare_result >= 0){
        search_range_left = search_range_middle + i_element_size;
      }
      else{
        search_range_right = search_range_middle;
      }
      #else
      if(TSODLULS_COMPARE_CALL(run_ptr, search_range_middle) >= 0){
        search_range_left = search_range_middle + i_element_size;
      }
      else{
        search_range_right = search_range_middle;
      }
      #endif
    }while(search_range_left < search_range_right);

    if(search_range_right != run_ptr){
      char* trav;
      trav = run_ptr + i_element_size;
      while(--trav >= run_ptr){
        char c = *trav;
        char* hi;
        char* lo;
        for (hi = lo = trav; (lo -= i_element_size) >= search_range_right; hi = lo){
          *hi = *lo;
        }
        *hi = c;
      }
    }
  }
}
#endif

