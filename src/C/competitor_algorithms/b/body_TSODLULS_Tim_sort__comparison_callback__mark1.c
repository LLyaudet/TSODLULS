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

©Copyright 2018-2022 Laurent Lyaudet

http://en.wikipedia.org/wiki/Timsort
See the source code of Python for the original implementation of Tim Peters's list sort.
*/

#define TSODLULS_TIM_SORT_MAX_RUNS_TO_MERGE 85



/**
 * Sorting functions using a comparison callback for arbitrary data structures.
 * The famous Tim sort with comparison callback.
 */
//int TSODLULS_Tim_sort__comparison_callback__mark1(
//  void* arr_elements,
//  size_t i_number_of_elements,
//  size_t i_element_size,
//  t_comparison_function or t_reentrant_comparison_function fn_comparison,
//  and maybe void* context
//){
//  #define TSODLULS_SWAP_VAR(a0,a1,a2) TSODLULS_SWAP_VAR_1(a0,a1,a2)

  //Nested function
  /**
   * Auxiliary function for merging two runs in Tim sort.
   */
  int TSODLULS_merge_two_runs__comparison_callback(
    TSODLULS_COMPARE_TIM_SORT_MERGE_STATE* merge_state,
    size_t i_first_index_to_merge
  ){
    #include "./body_TSODLULS_merge_two_runs__comparison_callback.c"
  }//end function TSODLULS_merge_two_runs__comparison_callback()


  size_t i_run_min_number_of_elements;
  //[lower, higher[
  char* p_current_lower_element = (char*) arr_elements;
  char* p_current_higher_element = p_current_lower_element + i_element_size * i_number_of_elements;
  TSODLULS_COMPARE_TIM_SORT_MERGE_STATE merge_state;
  int i_compare_result = 0;

  if(i_number_of_elements < 2){
    return 0;
  }

  merge_state.i_element_size = i_element_size;
  merge_state.fn_comparison = fn_comparison;
  #if TSODLULS_COMPARE_REENTRANT
  merge_state.context = context;
  #endif
  merge_state.i_run_instances_count = 0;
  merge_state.i_min_gallop = TSODLULS_TIM_SORT_MIN_GALLOP;
  merge_state.arr_elements_copy = NULL;
  merge_state.i_max_number_of_elements_copy = 0;

  merge_state.i_max_number_of_elements_copy = TSODLULS_min_exp(TSODLULS_TIM_SORT_MERGESTATE_TEMP_SIZE, i_number_of_elements);
  merge_state.arr_elements_copy = calloc(merge_state.i_max_number_of_elements_copy, i_element_size);
  if(merge_state.arr_elements_copy == NULL){
    return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
  }

  //compute i_run_min_number_of_elements
  {
    size_t i_number_of_elements__copy = i_number_of_elements;
    int b_any_one_shifted_off = 0;
    while(i_number_of_elements__copy >= 64){
      b_any_one_shifted_off |= i_number_of_elements__copy & 1;
      i_number_of_elements__copy /= 2;
    }
    // i_number_of_elements / i_run_min_number_of_elements is close but less than a power of 2, if i_number_of_elements >= 64
    i_run_min_number_of_elements = i_number_of_elements__copy + b_any_one_shifted_off;
  }

  do{
    int b_descending_run = 0;
    int i_current_run_number_of_elements = 0;

    //find the current run
    do{
      char* p_current_element = p_current_lower_element + i_element_size;
      i_current_run_number_of_elements = 1;
      if(p_current_element >= p_current_higher_element){
        break;
      }
      i_current_run_number_of_elements = 2;
      i_compare_result = TSODLULS_COMPARE_CALL(p_current_lower_element, p_current_element);
      #if TSODLULS_COMPARE_CAN_ERROR
      if(i_compare_result <= -2){// user defined error codes
        goto clean_and_return_error;
      }
      #endif
      p_current_element += i_element_size;
      if(i_compare_result >= 0){
        b_descending_run = 1;
        for(
          ;
          p_current_element < p_current_higher_element;
          p_current_element += i_element_size, ++i_current_run_number_of_elements
        ){
          i_compare_result = TSODLULS_COMPARE_CALL(p_current_element - i_element_size, p_current_element);
          if(i_compare_result <= 0){
            break;
          }
        }
        #if TSODLULS_COMPARE_CAN_ERROR
        if(i_compare_result <= -2){// user defined error codes
          goto clean_and_return_error;
        }
        #endif
      }
      else{
        for(
          ;
          p_current_element < p_current_higher_element;
          p_current_element += i_element_size, ++i_current_run_number_of_elements
        ){
          i_compare_result = TSODLULS_COMPARE_CALL(p_current_element, p_current_element - i_element_size);
          if(i_compare_result < 0){
            break;
          }
        }
        #if TSODLULS_COMPARE_CAN_ERROR
        if(i_compare_result <= -2){// user defined error codes
          goto clean_and_return_error;
        }
        #endif
      }
    }while(0);

    //reverse descending run
    if(b_descending_run){
      char* p_lower_element_for_swap = p_current_lower_element;
      char* p_higher_element_for_swap = p_current_lower_element + (i_current_run_number_of_elements - 1) * i_element_size;
      do{
        TSODLULS_SWAP_VAR(p_lower_element_for_swap, p_higher_element_for_swap, i_element_size);
        p_lower_element_for_swap += i_element_size;
        p_higher_element_for_swap -= i_element_size;
      }while(p_lower_element_for_swap < p_higher_element_for_swap);
    }

    //ensure min length with binary sort
    if(i_current_run_number_of_elements < i_run_min_number_of_elements){
      char* const start_ptr = p_current_lower_element;
      char* end_ptr = p_current_lower_element + (i_run_min_number_of_elements - 1) * i_element_size;
      if(end_ptr > p_current_higher_element - i_element_size){
        end_ptr = p_current_higher_element - i_element_size;
      }
      i_current_run_number_of_elements = ((end_ptr - start_ptr) / i_element_size) + 1;
      i_compare_result = TSODLULS_binary_insertion_sort_stable__comparison_callback__mark1(
          (void*) start_ptr,
          i_current_run_number_of_elements,
          i_element_size,
          fn_comparison
          #if TSODLULS_COMPARE_REENTRANT
          , context
          #endif
      );
      if(i_compare_result != 0){
        goto clean_and_return_error;
      }
    }

    //add run instance to merge
    merge_state.arr_run_instances[merge_state.i_run_instances_count].p_base = p_current_lower_element;
    merge_state.arr_run_instances[merge_state.i_run_instances_count].i_length = i_current_run_number_of_elements;
    ++merge_state.i_run_instances_count;

    //merge right now if needed
    TSODLULS_NATURAL_MERGE_MAIN_STRATEGY

    p_current_lower_element += i_current_run_number_of_elements * i_element_size;
  }while(p_current_lower_element < p_current_higher_element);

  while(merge_state.i_run_instances_count > 1){
    size_t i_merge_at = merge_state.i_run_instances_count - 2;
    if(i_merge_at > 0
      && merge_state.arr_run_instances[i_merge_at - 1].i_length < merge_state.arr_run_instances[i_merge_at + 1].i_length
    ){
      --i_merge_at;
    }
    i_compare_result = TSODLULS_MERGE_TWO_RUNS(&merge_state, i_merge_at);
    if(i_compare_result != 0){
      goto clean_and_return_error;
    }
  }

  clean_and_return_error:
  if(merge_state.arr_elements_copy != NULL){
    TSODLULS_free(merge_state.arr_elements_copy);
  }

  return i_compare_result;
//}//end function TSODLULS_Tim_sort__comparison_callback__mark1

