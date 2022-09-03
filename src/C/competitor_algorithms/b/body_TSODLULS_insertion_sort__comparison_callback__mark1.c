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
 * Sorting functions using a comparison callback for arbitrary data structures.
 * Insertion sort from qsort from glibc with minor modifications.
 */
//int TSODLULS_insertion_sort__comparison_callback__mark1(
//  void* arr_elements,
//  size_t i_number_of_elements,
//  size_t i_element_size,
//  t_comparison_function or t_reentrant_comparison_function fn_comparison,
//  and maybe void* context
//){
//  #define TSODLULS_SWAP_VAR(a0,a1,a2) TSODLULS_SWAP_VAR_1(a0,a1,a2)

  if(i_number_of_elements < 2){
    return 0;
  }

  {
    //technical def without real meaning
    #define TSODLULS_MAX_THRESH 2
    //but this one sets that we will not use the threshold in fragment
    #define TSODLULS_OPTIMIZE_INSERTION_SORT_WITHOUT_THRESHOLD 1
    char* const start_ptr = (char*) arr_elements;
    char* const end_ptr = &start_ptr[i_element_size * (i_number_of_elements - 1)];
    #include "../f/fragment_insertion_sort_with_threshold_for_comparison_callback.c"
    #undef TSODLULS_OPTIMIZE_INSERTION_SORT_WITHOUT_THRESHOLD
    #undef TSODLULS_MAX_THRESH
  }

  return 0;
//}//end function TSODLULS_insertion_sort__comparison_callback__mark1

