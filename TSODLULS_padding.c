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

©Copyright 2018 Laurent Lyaudet
*/

#include "TSODLULS.h"


//------------------------------------------------------------------------------------
//External functions
//------------------------------------------------------------------------------------
/**
 * Padding functions
 * Check padding parameters and return an error code if needed
 */
int TSODLULS_check_padding_parameters(
  int8_t i_number_of_lex_padding_bytes_before,
  int8_t i_number_of_contrelex_padding_bytes_before,
  int8_t i_number_of_lex_padding_bytes_after,
  int8_t i_number_of_contrelex_padding_bytes_after,
  int8_t i_number_of_contiguous_data_bytes,
  int8_t i_current_offset
){
  if(i_number_of_lex_padding_bytes_before == I_HALF_BYTE
    || i_number_of_contrelex_padding_bytes_before == I_HALF_BYTE
  ){
    if(i_number_of_lex_padding_bytes_before != I_HALF_BYTE
      || i_number_of_contrelex_padding_bytes_before != I_HALF_BYTE
    ){
      return I_ERROR__BOTH_LEX_AND_CONTRELEX_PADDING_BYTES_BEFORE_MUST_BE_HALF_BYTES;
    }
  }
  else{
    if(i_number_of_lex_padding_bytes_before < 0){
      return I_ERROR__NUMBER_OF_LEX_PADDING_BYTES_BEFORE_IS_INVALID;
    }
    if(i_number_of_contrelex_padding_bytes_before < 0){
      return I_ERROR__NUMBER_OF_CONTRELEX_PADDING_BYTES_BEFORE_IS_INVALID;
    }
  }
  if(i_number_of_lex_padding_bytes_after == I_HALF_BYTE
    || i_number_of_lex_padding_bytes_after == I_HALF_BYTE
  ){
    if(i_number_of_lex_padding_bytes_after != I_HALF_BYTE
      || i_number_of_lex_padding_bytes_after != I_HALF_BYTE
    ){
      return I_ERROR__BOTH_LEX_AND_CONTRELEX_PADDING_BYTES_AFTER_MUST_BE_HALF_BYTES;
    }
  }
  else{
    if(i_number_of_lex_padding_bytes_after < 0){
      return I_ERROR__NUMBER_OF_LEX_PADDING_BYTES_AFTER_IS_INVALID;
    }
    if(i_number_of_contrelex_padding_bytes_after < 0){
      return I_ERROR__NUMBER_OF_CONTRELEX_PADDING_BYTES_AFTER_IS_INVALID;
    }
  }

  if(i_number_of_contiguous_data_bytes < 1){
    return I_ERROR__NUMBER_OF_CONTIGUOUS_DATA_BYTES_MUST_BE_AT_LEAST_1;
  }
  if(i_current_offset < 0){
    return I_ERROR__CURRENT_OFFSET_MUST_BE_AT_LEAST_0;
  }
  if(i_number_of_contiguous_data_bytes <= i_current_offset){
    return I_ERROR__CURRENT_OFFSET_MUST_BE_LESS_THAN_THE_NUMBER_OF_CONTIGUOUS_DATA_BYTES;
  }
  return 0;
}//end function TSODLULS_check_padding_parameters()



/**
 * Padding functions
 * Compute size needed for the data bytes with padding
 */
size_t TSODLULS_compute_size_needed(
  size_t i_number_of_data_bytes,
  int8_t i_number_of_lex_padding_bytes_before,
  int8_t i_number_of_contrelex_padding_bytes_before,
  int8_t i_number_of_lex_padding_bytes_after,
  int8_t i_number_of_contrelex_padding_bytes_after,
  int8_t i_number_of_contiguous_data_bytes,
  int8_t i_current_offset
){
  //we assume that the padding parameters were checked by the previous function
  size_t i_size_needed = i_number_of_data_bytes;
  for(size_t i = 0; i < i_number_of_data_bytes; ++i){
    //padding bytes before
    if( ((i_current_offset + i) % i_number_of_contiguous_data_bytes) == 0){
      if(i_number_of_lex_padding_bytes_before == I_HALF_BYTE
        //&& i_number_of_contrelex_padding_bytes_before == I_HALF_BYTE already checked
      ){
        i_size_needed += 1;
      }
      else{
        i_size_needed += i_number_of_lex_padding_bytes_before;
        i_size_needed += i_number_of_contrelex_padding_bytes_before;
      }
    }
    //padding bytes after
    if( ((i_current_offset + i + 1) % i_number_of_contiguous_data_bytes) == 0){
      if(i_number_of_lex_padding_bytes_after == I_HALF_BYTE
        //&& i_number_of_contrelex_padding_bytes_after == I_HALF_BYTE already checked
      ){
        i_size_needed += 1;
      }
      else{
        i_size_needed += i_number_of_lex_padding_bytes_after;
        i_size_needed += i_number_of_contrelex_padding_bytes_after;
      }
    }
  }
  return i_size_needed;
}//end function TSODLULS_compute_size_needed()



/**
 * Padding functions
 * Padd
 */
void TSODLULS_padd(
  t_TSODLULS_sort_element* p_sort_element,
  int8_t i_number_of_lex_padding_bytes,
  int8_t i_number_of_contrelex_padding_bytes,
  int8_t i_current_offset
){
  if(i_current_offset == 0){
    if(i_number_of_lex_padding_bytes == I_HALF_BYTE
      //&& i_number_of_contrelex_padding_bytes == I_HALF_BYTE
    ){
      p_sort_element->s_key[p_sort_element->i_key_size++] = 240;
    }
    else{
      for(int8_t i = 0; i < i_number_of_lex_padding_bytes; ++i){
        p_sort_element->s_key[p_sort_element->i_key_size++] = 255;
      }
      for(int8_t i = 0; i < i_number_of_contrelex_padding_bytes; ++i){
        p_sort_element->s_key[p_sort_element->i_key_size++] = 0;
      }
    }
  }
}//end function TSODLULS_padd()



