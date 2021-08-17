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
 * at the right of the rightmost equal or smaller element.
 */
//int TSODLULS_gallop_right__long(
//  t_TSODLULS_sort_element* p_element,
//  t_TSODLULS_sort_element* arr_sorted_elements,
//  size_t i_number_of_elements,
//  size_t i_hint_offset
//){
  size_t i_current_offset;
  size_t i_previous_offset;
  size_t i__compare;
  size_t i_max__compare;
  int i_result__compare;

  //simplifies the offsets for the first part of the search
  arr_sorted_elements += i_hint_offset;
  TSODLULS_set_min_length__macraff(i_max__compare, p_element, arr_sorted_elements);
  for(i__compare = 0; i__compare < i_max__compare; ++i__compare){
    i_result__compare = ((int)(p_element->s_key[i__compare])) - ((int)(arr_sorted_elements->s_key[i__compare]));
    if(i_result__compare != 0){
      break;
    }
  }
  i_current_offset = 1;//absolute value from arr_sorted_elements[i_hint_offset]
  i_previous_offset = 0;
  if(i_result__compare >= 0){
    //search on the right of hint
    //arr_sorted_elements[i_hint_offset + i_previous_offset] <= element < arr_sorted_elements[i_hint_offset + i_current_offset]
    size_t const i_max_offset = i_number_of_elements - i_hint_offset;
    while(i_current_offset < i_max_offset){
      TSODLULS_set_min_length__macraff(i_max__compare, p_element, arr_sorted_elements + i_current_offset);
      for(i__compare = 0; i__compare < i_max__compare; ++i__compare){
        i_result__compare = ((int)(p_element->s_key[i__compare])) - ((int)((arr_sorted_elements + i_current_offset)->s_key[i__compare]));
        if(i_result__compare != 0){
          break;
        }
      }
      if(i_result__compare < 0){
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
    //arr_sorted_elements[i_hint_offset - i_current_offset] <= element < arr_sorted_elements[i_hint_offset - i_previous_offset]
    size_t const i_max_offset = i_hint_offset + 1;
    size_t temp_offset;
    while(i_current_offset < i_max_offset){
      TSODLULS_set_min_length__macraff(i_max__compare, p_element, arr_sorted_elements - i_current_offset);
      for(i__compare = 0; i__compare < i_max__compare; ++i__compare){
        i_result__compare = ((int)(p_element->s_key[i__compare])) - ((int)((arr_sorted_elements - i_current_offset)->s_key[i__compare]));
        if(i_result__compare != 0){
          break;
        }
      }
      if(i_result__compare >= 0){
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
  arr_sorted_elements -= i_hint_offset;

  //classic dichotomic search after galloping
  i_previous_offset += 1;
  //arr_sorted_elements[i_previous_offset - 1] <= element < arr_sorted_elements[i_current_offset]
  while(i_previous_offset < i_current_offset){
    size_t i_middle_offset = i_previous_offset + ((i_current_offset - i_previous_offset) / 2);
    TSODLULS_set_min_length__macraff(i_max__compare, p_element, arr_sorted_elements + i_middle_offset);
    for(i__compare = 0; i__compare < i_max__compare; ++i__compare){
      i_result__compare = ((int)(p_element->s_key[i__compare])) - ((int)((arr_sorted_elements + i_middle_offset)->s_key[i__compare]));
      if(i_result__compare != 0){
        break;
      }
    }
    if(i_result__compare >= 0){
      i_previous_offset = i_middle_offset + 1;
    }
    else{
      i_current_offset = i_middle_offset;
    }
  };
  return i_current_offset;
//}//end function TSODLULS_gallop_right__long()

