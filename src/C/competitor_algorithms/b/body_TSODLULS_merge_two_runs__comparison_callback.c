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

©Copyright 2018-2022 Laurent Lyaudet
*/



#define TSODLULS_copy_and_inc(insertion_point, from, length, offset) \
  {\
    memcpy(insertion_point, from, offset * merge_state->i_element_size);\
    insertion_point += offset * merge_state->i_element_size;\
    from += offset * merge_state->i_element_size;\
    length -= offset;\
  }

#define TSODLULS_move_and_inc(insertion_point, from, length, offset) \
  {\
    memmove(insertion_point, from, offset * merge_state->i_element_size);\
    insertion_point += offset * merge_state->i_element_size;\
    from += offset * merge_state->i_element_size;\
    length -= offset;\
  }

#define TSODLULS_copy_and_dec(insertion_point, from, length, offset) \
  {\
    insertion_point -= (offset - 1) * merge_state->i_element_size;\
    from -= (offset - 1) * merge_state->i_element_size;\
    memcpy(insertion_point, from, offset * merge_state->i_element_size);\
    insertion_point -= merge_state->i_element_size;\
    from -= merge_state->i_element_size;\
    length -= offset;\
  }

#define TSODLULS_move_and_dec(insertion_point, from, length, offset) \
  {\
    insertion_point -= (offset - 1) * merge_state->i_element_size;\
    from -= (offset - 1) * merge_state->i_element_size;\
    memmove(insertion_point, from, offset * merge_state->i_element_size);\
    insertion_point -= merge_state->i_element_size;\
    from -= merge_state->i_element_size;\
    length -= offset;\
  }



/**
 * Auxiliary function for merging two runs in Tim sort.
 */
//int TSODLULS_merge_two_runs__comparison_callback(
//  t_TSODLULS_Tim_sort_merge_state__comparison_callback* or t_TSODLULS_Tim_sort_merge_state__reentrant_comparison_callback* merge_state,
//  size_t i_first_index_to_merge
//){

  //Nested functions
  /**
   * Find the offset to insert element in arr_sorted_elements
   * at the left of the leftmost equal or greater element.
   */
  int TSODLULS_gallop_left__comparison_callback(
    void* p_element,
    char* arr_sorted_elements,
    size_t i_number_of_elements,
    size_t i_element_size,
    TSODLULS_COMPARE_TYPE fn_comparison,
    size_t i_hint_offset
  ){
    #include "./body_TSODLULS_gallop_left__comparison_callback.c"
  }//end function TSODLULS_gallop_left__comparison_callback()

  /**
   * Find the offset to insert element in arr_sorted_elements
   * at the right of the rightmost equal or greater element.
   */
  int TSODLULS_gallop_right__comparison_callback(
    void* p_element,
    char* arr_sorted_elements,
    size_t i_number_of_elements,
    size_t i_element_size,
    TSODLULS_COMPARE_TYPE fn_comparison,
    size_t i_hint_offset
  ){
    #include "./body_TSODLULS_gallop_right__comparison_callback.c"
  }//end function TSODLULS_gallop_right__comparison_callback()

  char* p_base_1;
  char* p_base_2;
  size_t i_length_1;
  size_t i_length_2;
  size_t i_offset;
  int i_compare_result = 0;

  p_base_1 = merge_state->arr_run_instances[i_first_index_to_merge].p_base;
  p_base_2 = merge_state->arr_run_instances[i_first_index_to_merge + 1].p_base;
  i_length_1 = merge_state->arr_run_instances[i_first_index_to_merge].i_length;
  i_length_2 = merge_state->arr_run_instances[i_first_index_to_merge + 1].i_length;

  //we update the state to be coherent with the result of the merge
  merge_state->arr_run_instances[i_first_index_to_merge].i_length = i_length_1 + i_length_2;
  if(i_first_index_to_merge == merge_state->i_run_instances_count - 3){
    //slide the last instance
    merge_state->arr_run_instances[i_first_index_to_merge + 1] = merge_state->arr_run_instances[i_first_index_to_merge + 2];
  }
  --merge_state->i_run_instances_count;

  i_offset = TSODLULS_gallop_right__comparison_callback(
      p_base_2,//first element of second run
      p_base_1,
      i_length_1,
      merge_state->i_element_size,
      merge_state->fn_comparison,
      0
  );
  if(i_offset < 0){//user defined error code
    return i_offset;
  }
  p_base_1 += i_offset * merge_state->i_element_size;
  i_length_1 -= i_offset;
  if(i_length_1 == 0){
    return 0;
  }

  i_offset = TSODLULS_gallop_left__comparison_callback(
      p_base_1 + (i_length_1 - 1) * merge_state->i_element_size,//last element of first run
      p_base_2,
      i_length_2,
      merge_state->i_element_size,
      merge_state->fn_comparison,
      i_length_2 - 1
  );
  if(i_offset <= 0){//user defined error code (<) or nothing to move (=)
    return i_offset;
  }
  i_length_2 = i_offset;

  //Merging the smaller part in the bigger one
  i_offset = TSODLULS_min_exp(i_length_1, i_length_2);
  if(i_offset > merge_state->i_max_number_of_elements_copy){
    //No realloc because we do not need the old data
    TSODLULS_free(merge_state->arr_elements_copy);
    merge_state->i_max_number_of_elements_copy = i_offset;
    merge_state->arr_elements_copy = calloc(merge_state->i_max_number_of_elements_copy, merge_state->i_element_size);
    if(merge_state->arr_elements_copy == NULL){
      merge_state->i_max_number_of_elements_copy = 0;
      return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
    }
  }
  if(i_length_1 <= i_length_2){
    size_t i_min_gallop = merge_state->i_min_gallop;
    char* p_current_insertion_point = p_base_1;
    memcpy(merge_state->arr_elements_copy, p_base_1, i_length_1 * merge_state->i_element_size);
    p_base_1 = merge_state->arr_elements_copy;

    //first element after gallop is from p_base_2
    TSODLULS_move_and_inc(p_current_insertion_point, p_base_2, i_length_2, 1)
    if(i_length_1 <= 1 || i_length_2 == 0){
      goto break_2_1;
    }
    while(1){
      size_t i_consecutive_win_1 = 0;
      size_t i_consecutive_win_2 = 0;

      //normal merge
      while(1){
        i_compare_result = TSODLULS_COMPARE_CALL(p_base_1, p_base_2);
        #if TSODLULS_COMPARE_CAN_ERROR
        if(i_compare_result <= -2){// user defined error codes
          goto break_2_error_1;
        }
        #endif
        if(i_compare_result <= 0){
          ++i_consecutive_win_1;
          i_consecutive_win_2 = 0;
          TSODLULS_copy_and_inc(p_current_insertion_point, p_base_1, i_length_1, 1)
          if(i_length_1 == 1){
            goto break_2_1;
          }
          if(i_consecutive_win_1 >= i_min_gallop){
            break;
          }
        }
        else{
          ++i_consecutive_win_2;
          i_consecutive_win_1 = 0;
          TSODLULS_move_and_inc(p_current_insertion_point, p_base_2, i_length_2, 1)
          if(i_length_2 == 0){
            goto break_2_1;
          }
          if(i_consecutive_win_2 >= i_min_gallop){
            break;
          }
        }
      }

      //galloping merge
      ++i_min_gallop;
      do{
        i_min_gallop -= i_min_gallop > 1;
        merge_state->i_min_gallop = i_min_gallop;
        i_offset = TSODLULS_gallop_right__comparison_callback(
            p_base_2,//first element of second run
            p_base_1,
            i_length_1,
            merge_state->i_element_size,
            merge_state->fn_comparison,
            0
        );
        if(i_offset < 0){//user defined error code
          i_compare_result = i_offset;
          goto break_2_error_1;
        }
        i_consecutive_win_1 = i_offset;
        if(i_offset > 0){
          TSODLULS_copy_and_inc(p_current_insertion_point, p_base_1, i_length_1, i_offset)
          if(i_length_1 <= 1){
            goto break_2_1;
          }
        }
        TSODLULS_move_and_inc(p_current_insertion_point, p_base_2, i_length_2, 1)
        if(i_length_2 == 0){
          goto break_2_1;
        }

        i_offset = TSODLULS_gallop_left__comparison_callback(
            p_base_1 ,//first element of first run
            p_base_2,
            i_length_2,
            merge_state->i_element_size,
            merge_state->fn_comparison,
            0
        );
        if(i_offset < 0){//user defined error code
          i_compare_result = i_offset;
          goto break_2_error_1;
        }
        i_consecutive_win_2 = i_offset;
        if(i_offset > 0){
          TSODLULS_move_and_inc(p_current_insertion_point, p_base_2, i_length_2, i_offset)
          if(i_length_2 == 0){
            goto break_2_1;
          }
        }
        TSODLULS_copy_and_inc(p_current_insertion_point, p_base_1, i_length_1, 1)
        if(i_length_1 <= 1){
          goto break_2_1;
        }
      }while(i_consecutive_win_1 >= TSODLULS_TIM_SORT_MIN_GALLOP || i_consecutive_win_2 >= TSODLULS_TIM_SORT_MIN_GALLOP);

      --i_min_gallop;//penalty
      merge_state->i_min_gallop = i_min_gallop;
    };
    break_2_error_1:
    if(i_compare_result <= -2){//user defined error code
      if(i_length_1 > 0){
        TSODLULS_copy_and_inc(p_current_insertion_point, p_base_1, i_length_1, i_length_1)
      }
      return i_compare_result;
    }
    break_2_1:
    if(i_length_1 == 1){
      if(i_length_2 > 0){
        TSODLULS_move_and_inc(p_current_insertion_point, p_base_2, i_length_2, i_length_2)
      }
      TSODLULS_copy_and_inc(p_current_insertion_point, p_base_1, i_length_1, 1)
      return 0;
    }
    if(i_length_1 > 0){
      TSODLULS_copy_and_inc(p_current_insertion_point, p_base_1, i_length_1, i_length_1)
      return 0;
    }
    return 0;
  }
  else{
    char* p_true_base_1;
    char* p_true_base_2;
    size_t i_min_gallop = merge_state->i_min_gallop;
    char* p_current_insertion_point = p_base_2 + (i_length_2 - 1) * merge_state->i_element_size;
    memcpy(merge_state->arr_elements_copy, p_base_2, i_length_2 * merge_state->i_element_size);
    p_true_base_1 = p_base_1;
    p_true_base_2 = merge_state->arr_elements_copy;
    p_base_1 += (i_length_1 - 1) * merge_state->i_element_size;
    p_base_2 = p_true_base_2 + (i_length_2 - 1) * merge_state->i_element_size;

    //last element after gallop is from p_base_1
    TSODLULS_move_and_dec(p_current_insertion_point, p_base_1, i_length_1, 1)
    if(i_length_2 <= 1 || i_length_1 == 0){
      goto break_2_2;
    }
    while(1){
      size_t i_consecutive_win_1 = 0;
      size_t i_consecutive_win_2 = 0;

      //normal merge
      while(1){
        i_compare_result = TSODLULS_COMPARE_CALL(p_base_1, p_base_2);
        #if TSODLULS_COMPARE_CAN_ERROR
        if(i_compare_result <= -2){// user defined error codes
          goto break_2_error_2;
        }
        #endif
        if(i_compare_result > 0){
          ++i_consecutive_win_1;
          i_consecutive_win_2 = 0;
          TSODLULS_move_and_dec(p_current_insertion_point, p_base_1, i_length_1, 1)
          if(i_length_1 == 0){
            goto break_2_2;
          }
          if(i_consecutive_win_1 >= i_min_gallop){
            break;
          }
        }
        else{
          ++i_consecutive_win_2;
          i_consecutive_win_1 = 0;
          TSODLULS_copy_and_dec(p_current_insertion_point, p_base_2, i_length_2, 1)
          if(i_length_2 == 1){
            goto break_2_2;
          }
          if(i_consecutive_win_2 >= i_min_gallop){
            break;
          }
        }
      }

      //galloping merge
      ++i_min_gallop;
      do{
        i_min_gallop -= i_min_gallop > 1;
        merge_state->i_min_gallop = i_min_gallop;
        i_offset = TSODLULS_gallop_right__comparison_callback(
            p_base_2,//current element of second run
            p_true_base_1,
            i_length_1,
            merge_state->i_element_size,
            merge_state->fn_comparison,
            i_length_1 - 1
        );
        if(i_offset < 0){//user defined error code
          i_compare_result = i_offset;
          goto break_2_error_2;
        }
        i_offset = i_length_1 - i_offset;
        i_consecutive_win_1 = i_offset;
        if(i_offset > 0){
          TSODLULS_move_and_dec(p_current_insertion_point, p_base_1, i_length_1, i_offset)
          if(i_length_1 == 0){
            goto break_2_2;
          }
        }
        TSODLULS_copy_and_dec(p_current_insertion_point, p_base_2, i_length_2, 1)
        if(i_length_2 <= 1){
          goto break_2_2;
        }

        i_offset = TSODLULS_gallop_left__comparison_callback(
            p_base_1,//current element of first run
            p_true_base_2,
            i_length_2,
            merge_state->i_element_size,
            merge_state->fn_comparison,
            i_length_2 - 1
        );
        if(i_offset < 0){//user defined error code
          i_compare_result = i_offset;
          goto break_2_error_2;
        }
        i_offset = i_length_2 - i_offset;
        i_consecutive_win_2 = i_offset;
        if(i_offset > 0){
          TSODLULS_copy_and_dec(p_current_insertion_point, p_base_2, i_length_2, i_offset)
          if(i_length_2 <= 1){
            goto break_2_2;
          }
        }
        TSODLULS_move_and_dec(p_current_insertion_point, p_base_1, i_length_1, 1)
        if(i_length_1 == 0){
          goto break_2_2;
        }
      }while(i_consecutive_win_1 >= TSODLULS_TIM_SORT_MIN_GALLOP || i_consecutive_win_2 >= TSODLULS_TIM_SORT_MIN_GALLOP);

      --i_min_gallop;//penalty
      merge_state->i_min_gallop = i_min_gallop;
    };
    break_2_error_2:
    if(i_compare_result <= -2){//user defined error code
      if(i_length_2 > 0){
        TSODLULS_copy_and_dec(p_current_insertion_point, p_base_2, i_length_2, i_length_2)
      }
      return i_compare_result;
    }
    break_2_2:
    if(i_length_2 == 1){
      if(i_length_1 > 0){
        TSODLULS_move_and_dec(p_current_insertion_point, p_base_1, i_length_1, i_length_1)
      }
      TSODLULS_copy_and_dec(p_current_insertion_point, p_base_2, i_length_2, 1)
      return 0;
    }
    if(i_length_2 > 0){
      TSODLULS_move_and_dec(p_current_insertion_point, p_base_2, i_length_2, i_length_2)
      return 0;
    }
  }

  return 0;
//}//end function TSODLULS_merge_two_runs__comparison_callback()



#undef TSODLULS_copy_and_inc
#undef TSODLULS_move_and_inc
#undef TSODLULS_copy_and_dec
#undef TSODLULS_move_and_dec

