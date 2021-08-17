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

©Copyright 2018-2021 Laurent Lyaudet
*/



/**
 * Find the offset to insert element in arr_sorted_elements
 * at the left of the leftmost equal or greater element.
 */
//int TSODLULS_gallop_left__comparison_callback(
//  void* p_element,
//  char* arr_sorted_elements,
//  size_t i_number_of_elements,
//  size_t i_element_size,
//  t_comparison_function or t_reentrant_comparison_function fn_comparison,
//  size_t i_hint_offset
//){
  size_t i_current_offset;
  size_t i_previous_offset;
  int i_compare_result;

  //simplifies the offsets for the first part of the search
  arr_sorted_elements += i_hint_offset * i_element_size;
  i_compare_result = TSODLULS_COMPARE_CALL(p_element, arr_sorted_elements);
  #if TSODLULS_COMPARE_CAN_ERROR
  if(i_compare_result <= -2){// user defined error codes
    return i_compare_result;
  }
  #endif
  i_current_offset = 1;//absolute value from arr_sorted_elements[i_hint_offset]
  i_previous_offset = 0;
  if(i_compare_result > 0){
    //search on the right of hint
    //arr_sorted_elements[i_hint_offset + i_previous_offset] < element <= arr_sorted_elements[i_hint_offset + i_current_offset]
    size_t const i_max_offset = i_number_of_elements - i_hint_offset;
    while(i_current_offset < i_max_offset){
      i_compare_result = TSODLULS_COMPARE_CALL(p_element, &arr_sorted_elements[i_current_offset * i_element_size]);
      #if TSODLULS_COMPARE_CAN_ERROR
      if(i_compare_result <= -2){// user defined error codes
        return i_compare_result;
      }
      #endif
      if(i_compare_result <= 0){
        break;
      }
      i_previous_offset = i_current_offset;
      i_current_offset = (i_current_offset * 2) + 1;
      if(i_current_offset <= i_previous_offset){//overflow
        i_current_offset = i_max_offset;
      }
    }
    if(i_current_offset > i_max_offset){
      i_current_offset = i_max_offset;
    }
    i_previous_offset += i_hint_offset;
    i_current_offset += i_hint_offset;
  }
  else{
    //search on the left of hint
    //arr_sorted_elements[i_hint_offset - i_current_offset] < element <= arr_sorted_elements[i_hint_offset - i_previous_offset]
    size_t const i_max_offset = i_hint_offset + 1;
    size_t temp_offset;
    while(i_current_offset < i_max_offset){
      i_compare_result = TSODLULS_COMPARE_CALL(p_element, arr_sorted_elements - (i_current_offset * i_element_size));
      #if TSODLULS_COMPARE_CAN_ERROR
      if(i_compare_result <= -2){// user defined error codes
        return i_compare_result;
      }
      #endif
      if(i_compare_result > 0){
        break;
      }
      i_previous_offset = i_current_offset;
      i_current_offset = (i_current_offset * 2) + 1;
      if(i_current_offset <= i_previous_offset){//overflow
        i_current_offset = i_max_offset;
      }
    }
    if(i_current_offset > i_max_offset){
      i_current_offset = i_max_offset;
    }
    temp_offset = i_previous_offset;
    i_previous_offset = i_hint_offset - i_current_offset;
    i_current_offset = i_hint_offset - temp_offset;
  }
  arr_sorted_elements -= i_hint_offset * i_element_size;

  //classic dichotomic search after galloping
  i_previous_offset += 1;
  //arr_sorted_elements[i_previous_offset - 1] < element <= arr_sorted_elements[i_current_offset]
  while(i_previous_offset < i_current_offset){
    size_t i_middle_offset = i_previous_offset + ((i_current_offset - i_previous_offset) / 2);
    int i_compare_result = TSODLULS_COMPARE_CALL(&arr_sorted_elements[i_middle_offset * i_element_size], p_element);
    #if TSODLULS_COMPARE_CAN_ERROR
    if(i_compare_result <= -2){// user defined error codes
      return i_compare_result;
    }
    #endif
    if(i_compare_result < 0){
      i_previous_offset = i_middle_offset + 1;
    }
    else{
      i_current_offset = i_middle_offset;
    }
  };

  return i_current_offset;
//}//end function TSODLULS_gallop_left__comparison_callback()

