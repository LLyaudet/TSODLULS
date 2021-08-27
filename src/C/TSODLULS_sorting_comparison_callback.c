/*
This file is part of TSODLULS library.

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

©Copyright 2018-2021 Laurent Lyaudet
*/

#include "TSODLULS.h"

#define TSODLULS_COMPARE_CAN_ERROR 0
#define TSODLULS_COMPARE_CALL TSODLULS_COMPARE_CALL_SIMPLE
#define TSODLULS_COMPARE_TYPE TSODLULS_COMPARE_TYPE_SIMPLE
#define TSODLULS_COMPARE_TIM_SORT_MERGE_STATE TSODLULS_COMPARE_TIM_SORT_MERGE_STATE_SIMPLE
#define TSODLULS_MERGE_TWO_RUNS TSODLULS_merge_two_runs__comparison_callback



//------------------------------------------------------------------------------------
//External functions
//------------------------------------------------------------------------------------
/**
 * Sorting functions using a comparison callback for arbitrary data structures.
 * The current state of the art sorting function using comparison callback.
 * Its implementation may change without warning.
 */
int TSODLULS_sort__comparison_callback(
  void* arr_elements,
  size_t i_number_of_elements,
  size_t i_element_size,
  t_comparison_function fn_comparison
){
  return TSODLULS_sort_logspace__comparison_callback(
    arr_elements,
    i_number_of_elements,
    i_element_size,
    fn_comparison
  );
}//end function TSODLULS_sort__comparison_callback()



/**
 * Sorting functions using a comparison callback for arbitrary data structures.
 * The current state of the art stable sorting function using comparison callback.
 * Its implementation may change without warning.
 */
int TSODLULS_sort_stable__comparison_callback(
  void* arr_elements,
  size_t i_number_of_elements,
  size_t i_element_size,
  t_comparison_function fn_comparison
){

  int TSODLULS_binary_insertion_sort_stable__comparison_callback__mark1(
    void* arr_elements,
    size_t i_number_of_elements,
    size_t i_element_size,
    t_comparison_function fn_comparison
  ){
    #include "./competitor_algorithms/b/body_TSODLULS_binary_insertion_sort_stable__comparison_callback__mark1.c"
  }

  #define TSODLULS_SWAP_VAR(a0,a1,a2) TSODLULS_SWAP_VAR_5(a0,a1,a2)
  #define TSODLULS_NATURAL_MERGE_MAIN_STRATEGY TSODLULS_natural_merge_main_strategy__adaptive_Shivers_sort
  size_t TSODLULS_macraff_i_chunk_size = TSODLULS_CHUNK_SIZE_FOR_SWAP_VAR(i_element_size);
  #include "./competitor_algorithms/b/body_TSODLULS_Tim_sort__comparison_callback__mark1.c"
  #undef TSODLULS_SWAP_VAR
  #undef TSODLULS_NATURAL_MERGE_MAIN_STRATEGY
}//end function TSODLULS_sort_stable__comparison_callback()



/**
 * Sorting functions using a comparison callback for arbitrary data structures.
 * The current state of the art logspace sorting function using comparison callback.
 * Its implementation may change without warning.
 */
int TSODLULS_sort_logspace__comparison_callback(
  void* arr_elements,
  size_t i_number_of_elements,
  size_t i_element_size,
  t_comparison_function fn_comparison
){
  #define TSODLULS_MAX_THRESH 5
  #define TSODLULS_SWAP_VAR(a0,a1,a2) TSODLULS_SWAP_VAR_5(a0,a1,a2)
  #define TSODLULS_INSERTION_SORT_TEMPLATE_WITH_THRESHOLD "../f/fragment_insertion_sort_with_threshold_for_comparison_callback.c"
  size_t TSODLULS_macraff_i_chunk_size = TSODLULS_CHUNK_SIZE_FOR_SWAP_VAR(i_element_size);
  #include "./competitor_algorithms/b/body_TSODLULS_qsort__comparison_callback.c"
  #undef TSODLULS_MAX_THRESH
  #undef TSODLULS_SWAP_VAR
  #undef TSODLULS_INSERTION_SORT_TEMPLATE_WITH_THRESHOLD
}//end function TSODLULS_sort_logspace__comparison_callback()



/**
 * Sorting functions using a comparison callback for arbitrary data structures.
 * The current state of the art stable logspace sorting function using comparison callback.
 * Its implementation may change without warning.
 */
int TSODLULS_sort_stable_logspace__comparison_callback(
  void* arr_elements,
  size_t i_number_of_elements,
  size_t i_element_size,
  t_comparison_function fn_comparison
){
  //Probably not really state of the art, will be improved later
  #include "./competitor_algorithms/b/body_TSODLULS_binary_insertion_sort_stable__comparison_callback__mark1.c"
}//end function TSODLULS_sort_stable_logspace__comparison_callback()



#undef TSODLULS_COMPARE_CAN_ERROR
#undef TSODLULS_COMPARE_CALL
#undef TSODLULS_COMPARE_TYPE
#undef TSODLULS_COMPARE_TIM_SORT_MERGE_STATE
#undef TSODLULS_MERGE_TWO_RUNS

