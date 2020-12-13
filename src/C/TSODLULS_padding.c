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

©Copyright 2018-2019 Laurent Lyaudet
*/

#include "TSODLULS.h"


//------------------------------------------------------------------------------------
//External functions
//------------------------------------------------------------------------------------
/**
 * Padding functions
 * Check padding parameters and return an error code if needed
 * Available as a macraff (see TSODLULS_padding__macro.h).
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
    || i_number_of_contrelex_padding_bytes_after == I_HALF_BYTE
  ){
    if(i_number_of_lex_padding_bytes_after != I_HALF_BYTE
      || i_number_of_contrelex_padding_bytes_after != I_HALF_BYTE
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
 * Available as a macraff (see TSODLULS_padding__macro.h).
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
 * Available as a macraff (see TSODLULS_padding__macro.h).
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



/**
 * Padding functions
 * Decrease last lex padding multibyte
 * (Done once at the end of a string for a lex node)
 */
int TSODLULS_decrease_last_lex_padding(
  t_TSODLULS_sort_element* p_sort_element,
  int8_t i_number_of_lex_padding_bytes,
  int8_t i_number_of_contrelex_padding_bytes
){
  int8_t i_offset = 0;
  size_t i_base = p_sort_element->i_key_size - 1;//last byte
  if(i_number_of_lex_padding_bytes == 0){//no padding, nothing to do
    return 0;
  }

  if(i_number_of_lex_padding_bytes == I_HALF_BYTE
    //&& i_number_of_contrelex_padding_bytes == I_HALF_BYTE
  ){
    if(p_sort_element->s_key[i_base] < 16){
      return I_ERROR__COULD_NOT_DECREASE_LEX_MULTIBYTE;
    }
    p_sort_element->s_key[i_base] -= 16;
    return 0;
  }

  i_base -= i_number_of_contrelex_padding_bytes;
  while(i_offset < i_number_of_lex_padding_bytes){
    if(p_sort_element->s_key[i_base - i_offset] > 0){
      --(p_sort_element->s_key[i_base - i_offset]);
      return 0;
    }
    p_sort_element->s_key[i_base - i_offset] = 255;
    ++i_offset;
  }
  return I_ERROR__COULD_NOT_DECREASE_LEX_MULTIBYTE;
}//end function TSODLULS_decrease_last_lex_padding()



/**
 * Padding functions
 * Increase last contrelex padding multibyte
 * (Done once at the end of a string for a contrelex node)
 */
int TSODLULS_increase_last_contrelex_padding(
  t_TSODLULS_sort_element* p_sort_element,
  int8_t i_number_of_contrelex_padding_bytes
){
  int8_t i_offset = 0;
  size_t i_base = p_sort_element->i_key_size - 1;//last byte
  if(i_number_of_contrelex_padding_bytes == 0){//no padding, nothing to do
    return 0;
  }

  if(i_number_of_contrelex_padding_bytes == I_HALF_BYTE){
    if((p_sort_element->s_key[i_base] % 16) == 15){
      return I_ERROR__COULD_NOT_INCREASE_CONTRELEX_MULTIBYTE;
    }
    ++p_sort_element->s_key[i_base];
    return 0;
  }

  while(i_offset < i_number_of_contrelex_padding_bytes){
    if(p_sort_element->s_key[i_base - i_offset] < 255){
      ++(p_sort_element->s_key[i_base - i_offset]);
      return 0;
    }
    p_sort_element->s_key[i_base - i_offset] = 0;
    ++i_offset;
  }
  return I_ERROR__COULD_NOT_INCREASE_CONTRELEX_MULTIBYTE;
}//end function TSODLULS_decrease_last_lex_padding()



/**
 * Padding functions
 * Add a few bits to the current key, managing current bit offset
 * and returning new current bit offset
 * Available as a macraff (see TSODLULS_padding__macro.h).
 */
uint8_t TSODLULS_add_bits_with_bit_level_offset(
  t_TSODLULS_sort_element* p_sort_element,
  uint8_t i_data_byte,
  uint8_t i_number_of_data_bits,//bits are in most significant digits
  uint8_t i_current_bit_level_offset
){
  uint8_t i_byte_mask;
  if(i_current_bit_level_offset > 0){
    i_byte_mask = i_data_byte >> i_current_bit_level_offset;
    p_sort_element->s_key[p_sort_element->i_key_size - 1] |= i_byte_mask;//first byte mask
    if(i_current_bit_level_offset + i_number_of_data_bits > 8){
      i_byte_mask = i_data_byte << (8 - i_current_bit_level_offset);
      p_sort_element->s_key[p_sort_element->i_key_size++] |= i_byte_mask;//second byte mask
    }
  }
  else{
    p_sort_element->s_key[p_sort_element->i_key_size++] = i_data_byte;
  }
  return (i_current_bit_level_offset + i_number_of_data_bits) % 8;
}//end function TSODLULS_add_bits_with_bit_level_offset()



