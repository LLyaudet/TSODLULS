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
//int TSODLULS_gallop_left__short(
//  t_TSODLULS_sort_element__short* p_element,
//  t_TSODLULS_sort_element__short* arr_sorted_elements,
//  size_t i_number_of_elements,
//  size_t i_hint_offset
//){
  size_t i_current_offset;
  size_t i_previous_offset;

  //simplifies the offsets for the first part of the search
  arr_sorted_elements += i_hint_offset;
  i_current_offset = 1;//absolute value from arr_sorted_elements[i_hint_offset]
  i_previous_offset = 0;
  if(p_element->i_key > arr_sorted_elements->i_key){
    //search on the right of hint
    //arr_sorted_elements[i_hint_offset + i_previous_offset] < element <= arr_sorted_elements[i_hint_offset + i_current_offset]
    size_t const i_max_offset = i_number_of_elements - i_hint_offset;
    while(i_current_offset < i_max_offset){
      if(p_element->i_key <= arr_sorted_elements[i_current_offset].i_key){
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
      if(p_element->i_key > (arr_sorted_elements - i_current_offset)->i_key){
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
  //arr_sorted_elements[i_previous_offset - 1] < element <= arr_sorted_elements[i_current_offset]
  while(i_previous_offset < i_current_offset){
    size_t i_middle_offset = i_previous_offset + ((i_current_offset - i_previous_offset) / 2);
    if(p_element->i_key > arr_sorted_elements[i_middle_offset].i_key){
      i_previous_offset = i_middle_offset + 1;
    }
    else{
      i_current_offset = i_middle_offset;
    }
  };
  return i_current_offset;
//}//end function TSODLULS_gallop_left__short()

