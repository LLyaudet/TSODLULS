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
    memcpy(insertion_point, from, offset * sizeof(t_TSODLULS_sort_element__short));\
    insertion_point += offset;\
    from += offset;\
    length -= offset;\
  }

#define TSODLULS_move_and_inc(insertion_point, from, length, offset) \
  {\
    memmove(insertion_point, from, offset * sizeof(t_TSODLULS_sort_element__short));\
    insertion_point += offset;\
    from += offset;\
    length -= offset;\
  }

#define TSODLULS_copy_and_dec(insertion_point, from, length, offset) \
  {\
    insertion_point -= (offset - 1);\
    from -= (offset - 1);\
    memcpy(insertion_point, from, offset * sizeof(t_TSODLULS_sort_element__short));\
    --insertion_point;\
    --from;\
    length -= offset;\
  }

#define TSODLULS_move_and_dec(insertion_point, from, length, offset) \
  {\
    insertion_point -= (offset - 1);\
    from -= (offset - 1);\
    memmove(insertion_point, from, offset * sizeof(t_TSODLULS_sort_element__short));\
    --insertion_point;\
    --from;\
    length -= offset;\
  }



/**
 * Auxiliary function for merging two runs in Tim sort.
 */
//int TSODLULS_merge_two_runs__short(
//  t_TSODLULS_Tim_sort_merge_state__short*,
//  size_t i_first_index_to_merge
//){

  //Nested functions
  /**
   * Find the offset to insert element in arr_sorted_elements
   * at the left of the leftmost equal or greater element.
   */
  int TSODLULS_gallop_left__short(
    t_TSODLULS_sort_element__short* p_element,
    t_TSODLULS_sort_element__short* arr_sorted_elements,
    size_t i_number_of_elements,
    size_t i_hint_offset
  ){
    #include "./body_TSODLULS_gallop_left__short.c"
  }//end function TSODLULS_gallop_left__short()

  /**
   * Find the offset to insert element in arr_sorted_elements
   * at the right of the rightmost equal or greater element.
   */
  int TSODLULS_gallop_right__short(
    t_TSODLULS_sort_element__short* p_element,
    t_TSODLULS_sort_element__short* arr_sorted_elements,
    size_t i_number_of_elements,
    size_t i_hint_offset
  ){
    #include "./body_TSODLULS_gallop_right__short.c"
  }//end function TSODLULS_gallop_right__short()

  t_TSODLULS_sort_element__short* p_base_1;
  t_TSODLULS_sort_element__short* p_base_2;
  size_t i_length_1;
  size_t i_length_2;
  size_t i_offset;

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

  i_offset = TSODLULS_gallop_right__short(
      p_base_2,//first element of second run
      p_base_1,
      i_length_1,
      0
  );
  p_base_1 += i_offset;
  i_length_1 -= i_offset;
  if(i_length_1 == 0){
    return 0;
  }

  i_offset = TSODLULS_gallop_left__short(
      p_base_1 + i_length_1 - 1,//last element of first run
      p_base_2,
      i_length_2,
      i_length_2 - 1
  );
  if(i_offset == 0){//nothing to move (=)
    return i_offset;
  }
  i_length_2 = i_offset;

  //Merging the smaller part in the bigger one
  i_offset = TSODLULS_min_exp(i_length_1, i_length_2);
  if(i_offset > merge_state->i_max_number_of_elements_copy){
    //No realloc because we do not need the old data
    TSODLULS_free(merge_state->arr_elements_copy);
    merge_state->i_max_number_of_elements_copy = i_offset;
    merge_state->arr_elements_copy = calloc(merge_state->i_max_number_of_elements_copy, sizeof(t_TSODLULS_sort_element__short));
    if(merge_state->arr_elements_copy == NULL){
      merge_state->i_max_number_of_elements_copy = 0;
      return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
    }
  }
  if(i_length_1 <= i_length_2){
    size_t i_min_gallop = merge_state->i_min_gallop;
    t_TSODLULS_sort_element__short* p_current_insertion_point = p_base_1;
    memcpy(merge_state->arr_elements_copy, p_base_1, i_length_1 * sizeof(t_TSODLULS_sort_element__short));
    p_base_1 = merge_state->arr_elements_copy;

    //first element after gallop is from p_base_2
    *p_current_insertion_point++ = *p_base_2++;
    --i_length_2;
    if(i_length_1 <= 1 || i_length_2 == 0){
      goto break_2_1;
    }
    while(1){
      size_t i_consecutive_win_1 = 0;
      size_t i_consecutive_win_2 = 0;

      //normal merge
      while(1){
        if(p_base_1->i_key <= p_base_2->i_key){
          ++i_consecutive_win_1;
          i_consecutive_win_2 = 0;
          *p_current_insertion_point++ = *p_base_1++;
          --i_length_1;
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
          *p_current_insertion_point++ = *p_base_2++;
          --i_length_2;
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
        i_offset = TSODLULS_gallop_right__short(
            p_base_2,//first element of second run
            p_base_1,
            i_length_1,
            0
        );
        i_consecutive_win_1 = i_offset;
        if(i_offset > 0){
          TSODLULS_copy_and_inc(p_current_insertion_point, p_base_1, i_length_1, i_offset)
          if(i_length_1 <= 1){
            goto break_2_1;
          }
        }
        *p_current_insertion_point++ = *p_base_2++;
        --i_length_2;
        if(i_length_2 == 0){
          goto break_2_1;
        }

        i_offset = TSODLULS_gallop_left__short(
            p_base_1 ,//first element of first run
            p_base_2,
            i_length_2,
            0
        );
        i_consecutive_win_2 = i_offset;
        if(i_offset > 0){
          TSODLULS_move_and_inc(p_current_insertion_point, p_base_2, i_length_2, i_offset)
          if(i_length_2 == 0){
            goto break_2_1;
          }
        }
        *p_current_insertion_point++ = *p_base_1++;
        --i_length_1;
        if(i_length_1 <= 1){
          goto break_2_1;
        }
      }while(i_consecutive_win_1 >= TSODLULS_TIM_SORT_MIN_GALLOP || i_consecutive_win_2 >= TSODLULS_TIM_SORT_MIN_GALLOP);

      --i_min_gallop;//penalty
      merge_state->i_min_gallop = i_min_gallop;
    };
    break_2_1:
    if(i_length_1 == 1){
      if(i_length_2 > 0){
        TSODLULS_move_and_inc(p_current_insertion_point, p_base_2, i_length_2, i_length_2)
      }
      *p_current_insertion_point = *p_base_1;
      //*p_current_insertion_point++ = *p_base_1++;
      //--i_length_1;
      return 0;
    }
    if(i_length_1 > 0){
      TSODLULS_copy_and_inc(p_current_insertion_point, p_base_1, i_length_1, i_length_1)
      return 0;
    }
    return 0;
  }
  else{
    t_TSODLULS_sort_element__short* p_true_base_1;
    t_TSODLULS_sort_element__short* p_true_base_2;
    size_t i_min_gallop = merge_state->i_min_gallop;
    t_TSODLULS_sort_element__short* p_current_insertion_point = p_base_2 + i_length_2 - 1;
    memcpy(merge_state->arr_elements_copy, p_base_2, i_length_2 * sizeof(t_TSODLULS_sort_element__short));
    p_true_base_1 = p_base_1;
    p_true_base_2 = merge_state->arr_elements_copy;
    p_base_1 += i_length_1 - 1;
    p_base_2 = p_true_base_2 + i_length_2 - 1;

    //last element after gallop is from p_base_1
    *p_current_insertion_point-- = *p_base_1--;
    --i_length_1;
    if(i_length_2 <= 1 || i_length_1 == 0){
      goto break_2_2;
    }
    while(1){
      size_t i_consecutive_win_1 = 0;
      size_t i_consecutive_win_2 = 0;

      //normal merge
      while(1){
        if(p_base_1->i_key > p_base_2->i_key){
          ++i_consecutive_win_1;
          i_consecutive_win_2 = 0;
          *p_current_insertion_point-- = *p_base_1--;
          --i_length_1;
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
          *p_current_insertion_point-- = *p_base_2--;
          --i_length_2;
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
        i_offset = TSODLULS_gallop_right__short(
            p_base_2,//current element of second run
            p_true_base_1,
            i_length_1,
            i_length_1 - 1
        );
        i_offset = i_length_1 - i_offset;
        i_consecutive_win_1 = i_offset;
        if(i_offset > 0){
          TSODLULS_move_and_dec(p_current_insertion_point, p_base_1, i_length_1, i_offset)
          if(i_length_1 == 0){
            goto break_2_2;
          }
        }
        *p_current_insertion_point-- = *p_base_2--;
        --i_length_2;
        if(i_length_2 <= 1){
          goto break_2_2;
        }

        i_offset = TSODLULS_gallop_left__short(
            p_base_1,//current element of first run
            p_true_base_2,
            i_length_2,
            i_length_2 - 1
        );
        i_offset = i_length_2 - i_offset;
        i_consecutive_win_2 = i_offset;
        if(i_offset > 0){
          TSODLULS_copy_and_dec(p_current_insertion_point, p_base_2, i_length_2, i_offset)
          if(i_length_2 <= 1){
            goto break_2_2;
          }
        }
        *p_current_insertion_point-- = *p_base_1--;
        --i_length_1;
        if(i_length_1 == 0){
          goto break_2_2;
        }
      }while(i_consecutive_win_1 >= TSODLULS_TIM_SORT_MIN_GALLOP || i_consecutive_win_2 >= TSODLULS_TIM_SORT_MIN_GALLOP);

      --i_min_gallop;//penalty
      merge_state->i_min_gallop = i_min_gallop;
    };
    break_2_2:
    if(i_length_2 == 1){
      if(i_length_1 > 0){
        TSODLULS_move_and_dec(p_current_insertion_point, p_base_1, i_length_1, i_length_1)
      }
      *p_current_insertion_point = *p_base_2;
      //*p_current_insertion_point-- = *p_base_2--;
      //--i_length_2;
      return 0;
    }
    if(i_length_2 > 0){
      TSODLULS_move_and_dec(p_current_insertion_point, p_base_2, i_length_2, i_length_2)
      return 0;
    }
  }

  return 0;
//}//end function TSODLULS_merge_two_runs__short()



#undef TSODLULS_copy_and_inc
#undef TSODLULS_move_and_inc
#undef TSODLULS_copy_and_dec
#undef TSODLULS_move_and_dec

