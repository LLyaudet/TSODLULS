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

#if TSODLULS_MAX_THRESH > 1
//char* const start_ptr = base_ptr;
//char* const end_ptr = &start_ptr[i_element_size * (i_number_of_elements - 1)];
{
  char* tmp_ptr = start_ptr;
  char* thresh = TSODLULS_min_exp(end_ptr, start_ptr + max_threshold_size);
  char* run_ptr;

  /* Find smallest element in first threshold and place it at the
     array's beginning.  This is the smallest array element,
     and the operation speeds up insertion sort's inner loop. */

  for(run_ptr = tmp_ptr + i_element_size; run_ptr <= thresh; run_ptr += i_element_size){
    #if TSODLULS_COMPARE_CAN_ERROR
    int i_compare_result = TSODLULS_COMPARE_CALL(run_ptr, tmp_ptr);
    if(i_compare_result <= -2){// user defined error codes
      return i_compare_result;
    }
    if(i_compare_result < 0){
      tmp_ptr = run_ptr;
    }
    #else
    if(TSODLULS_COMPARE_CALL(run_ptr, tmp_ptr) < 0){
      tmp_ptr = run_ptr;
    }
    #endif
  }

  if(tmp_ptr != start_ptr){
    TSODLULS_SWAP_VAR(tmp_ptr, start_ptr, i_element_size);
  }

  /* Insertion sort, running from left-hand-side up to right-hand-side.  */
  run_ptr = start_ptr + i_element_size;
  while((run_ptr += i_element_size) <= end_ptr){
    tmp_ptr = run_ptr;

    #if TSODLULS_COMPARE_CAN_ERROR
    {
      int i_compare_result;
      do{
        tmp_ptr -= i_element_size;
        i_compare_result = TSODLULS_COMPARE_CALL(tmp_ptr, run_ptr);
      }while(i_compare_result > 0);
      if(i_compare_result <= -2){// user defined error codes
        return i_compare_result;
      }
    }
    #else
    do{
      tmp_ptr -= i_element_size;
    }while(TSODLULS_COMPARE_CALL(tmp_ptr, run_ptr) > 0);
    #endif

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
}
#endif

