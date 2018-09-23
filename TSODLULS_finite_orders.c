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
 * Conversion of finite orders to unsigned integer types
 * Change a float into an uint32
 * Nan (not a number) are separated into positive and negative nan.
 * The ordering is as follow: -nan, -inf, negative numbers, -0, +0, positive numbers, inf, nan.
 * Use a custom function if you want to detect (-)nan floats and order them differently.
 */
uint32_t TSODLULS_get_uint_from_float(float f_float){
  union ieee754_float temp;
  temp.f = f_float;
  //negative first
  if(temp.ieee.negative == 1){
    return
        (((uint32_t)1) << 31)
      - (  (((uint32_t)temp.ieee.exponent) << 23)//8 bits
         + ((uint32_t)temp.ieee.mantissa)//23 bits
         + 1
        )
    ;
  }
  else{
    return (((uint32_t)1) << 31)
         + (((uint32_t)temp.ieee.exponent) << 23)//8 bits
         + ((uint32_t)temp.ieee.mantissa);//23 bits
  }
}//end function TSODLULS_get_uint_from_float()



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint32 to the float encoded by it (see TSODLULS_get_uint_from_float)
 */
float TSODLULS_get_float_from_uint(uint32_t i32){
  union ieee754_float temp;
  //negative first
  if(i32 < (((uint32_t)1) << 31)){
    i32 = (((uint32_t)1) << 31) - i32 - 1;
    temp.ieee.negative = 1;
  }
  else{
    temp.ieee.negative = 0;
  }
  temp.ieee.exponent = (i32 >> 23) % (((uint32_t)1) << 8);
  temp.ieee.mantissa = i32 % (((uint32_t)1) << 23);
  return temp.f;
}//end function TSODLULS_get_float_from_uint()



/**
 * Conversion of finite orders to unsigned integer types
 * Change a double into an uint64
 * Nan (not a number) are separated into positive and negative nan.
 * The ordering is as follow: -nan, -inf, negative numbers, -0, +0, positive numbers, inf, nan.
 * Use a custom function if you want to detect (-)nan floats and order them differently.
 */
uint64_t TSODLULS_get_uint_from_double(double f_double){
  union ieee754_double temp;
  temp.d = f_double;
  //negative first
  if(temp.ieee.negative == 1){
    return
        (((uint64_t)1) << 63)
      - (  (((uint64_t)temp.ieee.exponent) << 52)//11 bits
         + (((uint64_t)temp.ieee.mantissa0) << 32)//20 bits
         + ((uint64_t)temp.ieee.mantissa1)//32 bits
         + 1
        )
    ;
  }
  else{
    return (((uint64_t)1) << 63)
         + (((uint64_t)temp.ieee.exponent) << 52)//11 bits
         + (((uint64_t)temp.ieee.mantissa0) << 32)//20 bits
         + ((uint64_t)temp.ieee.mantissa1);//32 bits
  }
}//end function TSODLULS_get_uint_from_double()



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint64 to the double encoded by it (see TSODLULS_get_uint_from_double)
 */
double TSODLULS_get_double_from_uint(uint64_t i64){
  union ieee754_double temp;
  //negative first
  if(i64 < (((uint64_t)1) << 63)){
    i64 = (((uint64_t)1) << 63) - i64 - 1;
    temp.ieee.negative = 1;
  }
  else{
    temp.ieee.negative = 0;
  }
  temp.ieee.exponent = (i64 >> 52) % (((uint64_t)1) << 11);
  temp.ieee.mantissa0 = (i64 >> 32) % (((uint64_t)1) << 20);
  temp.ieee.mantissa1 = i64 % (((uint64_t)1) << 32);
  return temp.d;
}//end function TSODLULS_get_double_from_uint()



/**
 * Conversion of finite orders to unsigned integer types
 * Change an int8 into an uint8 so that order is preserved
 */
uint8_t TSODLULS_get_uint8_from_int8(int8_t i8){
  if(i8 >= 0){
    return ((uint8_t)i8) + (((uint8_t)1) << 7);
  }
  return ((uint8_t)((INT8_MAX + i8) + 1));
}//end function TSODLULS_get_uint8_from_int8()



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint8 to the int encoded by it (see TSODLULS_get_uint8_from_int8)
 */
int8_t TSODLULS_get_int8_from_uint8(uint8_t i8){
  if(i8 >= (((uint8_t)1) << 7)){
    return ((int8_t) (i8 - (((uint8_t)1) << 7)));
  }
  return ((int8_t)((((uint8_t)1) << 7) + i8));
}//end function TSODLULS_get_int8_from_uint8()



/**
 * Conversion of finite orders to unsigned integer types
 * Change an int16 into an uint16 so that order is preserved
 */
uint16_t TSODLULS_get_uint16_from_int16(int16_t i16){
  if(i16 >= 0){
    return ((uint16_t)i16) + (((uint16_t)1) << 15);
  }
  return ((uint16_t)((INT16_MAX + i16) + 1));
}//end function TSODLULS_get_uint16_from_int16()



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint16 to the int encoded by it (see TSODLULS_get_uint16_from_int16)
 */
int16_t TSODLULS_get_int16_from_uint16(uint16_t i16){
  if(i16 >= (((uint16_t)1) << 15)){
    return ((int16_t) (i16 - (((uint16_t)1) << 15)));
  }
  return ((int16_t)((((uint16_t)1) << 15) + i16));
}//end function TSODLULS_get_int16_from_uint16()



/**
 * Conversion of finite orders to unsigned integer types
 * Change an int32 into an uint32 so that order is preserved
 */
uint32_t TSODLULS_get_uint32_from_int32(int32_t i32){
  if(i32 >= 0){
    return ((uint32_t)i32) + (((uint32_t)1) << 31);
  }
  return ((uint32_t)((INT32_MAX + i32) + 1));
}//end function TSODLULS_get_uint32_from_int32()



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint32 to the int encoded by it (see TSODLULS_get_uint32_from_int32)
 */
int32_t TSODLULS_get_int32_from_uint32(uint32_t i32){
  if(i32 >= (((uint32_t)1) << 31)){
    return ((int32_t) (i32 - (((uint32_t)1) << 31)));
  }
  return ((int32_t)((((uint32_t)1) << 31) + i32));
}//end function TSODLULS_get_int32_from_uint32()



/**
 * Conversion of finite orders to unsigned integer types
 * Change an int64 into an uint64 so that order is preserved
 */
uint64_t TSODLULS_get_uint64_from_int64(int64_t i64){
  if(i64 >= 0){
    return ((uint64_t)i64) + (((uint64_t)1) << 63);
  }
  return ((uint64_t)((INT64_MAX + i64) + 1));
}//end function TSODLULS_get_uint64_from_int64()



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint64 to the int encoded by it (see TSODLULS_get_uint64_from_int64)
 */
int64_t TSODLULS_get_int64_from_uint64(uint64_t i64){
  if(i64 >= (((uint64_t)1) << 63)){
    return ((int64_t) (i64 - (((uint64_t)1) << 63)));
  }
  return ((int64_t)((((uint64_t)1) << 63) + i64));
}//end function TSODLULS_get_int64_from_uint64()



/**
 * Adding TSO-encoding to the current key
 * From uint8
 */
int TSODLULS_add_bytes_to_key_from_uint8(
  t_TSODLULS_sort_element* p_sort_element,
  uint8_t i8,
  int8_t i_number_of_lex_padding_bytes_before,
  int8_t i_number_of_contrelex_padding_bytes_before,
  int8_t i_number_of_lex_padding_bytes_after,
  int8_t i_number_of_contrelex_padding_bytes_after,
  int8_t i_number_of_contiguous_data_bytes,
  int8_t i_current_offset
){
  size_t i_size_needed = 1;
  int i_result = 0;

  i_result = TSODLULS_check_padding_parameters(
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_number_of_contiguous_data_bytes,
      i_current_offset
  );
  if(i_result != 0){
    return i_result;
  }

  i_size_needed = TSODLULS_compute_size_needed(
      1,
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_number_of_contiguous_data_bytes,
      i_current_offset
  );

  i_result = TSODLULS_element_allocate_space_for_key(
      p_sort_element,
      i_size_needed
  );
  if(i_result != 0){
    return i_result;
  }

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_current_offset
  );

  p_sort_element->s_key[p_sort_element->i_key_size++] = (uint8_t)i8;
  i_current_offset = (i_current_offset + 1) % i_number_of_contiguous_data_bytes;

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_current_offset
  );
  return 0;
}//end function TSODLULS_add_bytes_to_key_from_uint8()



/**
 * Adding TSO-encoding to the current key
 * From uint16
 */
int TSODLULS_add_bytes_to_key_from_uint16(
  t_TSODLULS_sort_element* p_sort_element,
  uint16_t i16,
  int8_t i_number_of_lex_padding_bytes_before,
  int8_t i_number_of_contrelex_padding_bytes_before,
  int8_t i_number_of_lex_padding_bytes_after,
  int8_t i_number_of_contrelex_padding_bytes_after,
  int8_t i_number_of_contiguous_data_bytes,
  int8_t i_current_offset
){
  size_t i_size_needed = 2;
  int i_result = 0;

  i_result = TSODLULS_check_padding_parameters(
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_number_of_contiguous_data_bytes,
      i_current_offset
  );
  if(i_result != 0){
    return i_result;
  }

  i_size_needed = TSODLULS_compute_size_needed(
      2,
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_number_of_contiguous_data_bytes,
      i_current_offset
  );

  i_result = TSODLULS_element_allocate_space_for_key(
      p_sort_element,
      i_size_needed
  );
  if(i_result != 0){
    return i_result;
  }

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_current_offset
  );

  p_sort_element->s_key[p_sort_element->i_key_size++] = (uint8_t)(i16 >> 8);
  i_current_offset = (i_current_offset + 1) % i_number_of_contiguous_data_bytes;

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_current_offset
  );

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_current_offset
  );

  p_sort_element->s_key[p_sort_element->i_key_size++] = (uint8_t)(i16 % 256);
  i_current_offset = (i_current_offset + 1) % i_number_of_contiguous_data_bytes;

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_current_offset
  );
  return 0;
}//end function TSODLULS_add_bytes_to_key_from_uint16()



/**
 * Adding TSO-encoding to the current key
 * From uint32
 */
int TSODLULS_add_bytes_to_key_from_uint32(
  t_TSODLULS_sort_element* p_sort_element,
  uint32_t i32,
  int8_t i_number_of_lex_padding_bytes_before,
  int8_t i_number_of_contrelex_padding_bytes_before,
  int8_t i_number_of_lex_padding_bytes_after,
  int8_t i_number_of_contrelex_padding_bytes_after,
  int8_t i_number_of_contiguous_data_bytes,
  int8_t i_current_offset
){
  size_t i_size_needed = 4;
  int i_result = 0;

  i_result = TSODLULS_check_padding_parameters(
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_number_of_contiguous_data_bytes,
      i_current_offset
  );
  if(i_result != 0){
    return i_result;
  }

  i_size_needed = TSODLULS_compute_size_needed(
      4,
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_number_of_contiguous_data_bytes,
      i_current_offset
  );

  i_result = TSODLULS_element_allocate_space_for_key(
      p_sort_element,
      i_size_needed
  );
  if(i_result != 0){
    return i_result;
  }

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_current_offset
  );

  p_sort_element->s_key[p_sort_element->i_key_size++] = (uint8_t)(i32 >> 24);
  i_current_offset = (i_current_offset + 1) % i_number_of_contiguous_data_bytes;

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_current_offset
  );

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_current_offset
  );

  p_sort_element->s_key[p_sort_element->i_key_size++] = (uint8_t)((i32 >> 16) % 256);
  i_current_offset = (i_current_offset + 1) % i_number_of_contiguous_data_bytes;

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_current_offset
  );

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_current_offset
  );

  p_sort_element->s_key[p_sort_element->i_key_size++] = (uint8_t)((i32 >> 8) % 256);
  i_current_offset = (i_current_offset + 1) % i_number_of_contiguous_data_bytes;

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_current_offset
  );

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_current_offset
  );

  p_sort_element->s_key[p_sort_element->i_key_size++] = (uint8_t)(i32 % 256);
  i_current_offset = (i_current_offset + 1) % i_number_of_contiguous_data_bytes;

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_current_offset
  );
  return 0;
}//end function TSODLULS_add_bytes_to_key_from_uint32()



/**
 * Adding TSO-encoding to the current key
 * From uint64
 */
int TSODLULS_add_bytes_to_key_from_uint64(
  t_TSODLULS_sort_element* p_sort_element,
  uint64_t i64,
  int8_t i_number_of_lex_padding_bytes_before,
  int8_t i_number_of_contrelex_padding_bytes_before,
  int8_t i_number_of_lex_padding_bytes_after,
  int8_t i_number_of_contrelex_padding_bytes_after,
  int8_t i_number_of_contiguous_data_bytes,
  int8_t i_current_offset
){
  size_t i_size_needed = 8;
  int i_result = 0;

  i_result = TSODLULS_check_padding_parameters(
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_number_of_contiguous_data_bytes,
      i_current_offset
  );
  if(i_result != 0){
    return i_result;
  }

  i_size_needed = TSODLULS_compute_size_needed(
      8,
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_number_of_contiguous_data_bytes,
      i_current_offset
  );

  i_result = TSODLULS_element_allocate_space_for_key(
      p_sort_element,
      i_size_needed
  );
  if(i_result != 0){
    return i_result;
  }

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_current_offset
  );

  p_sort_element->s_key[p_sort_element->i_key_size++] = (uint8_t)(i64 >> 56);
  i_current_offset = (i_current_offset + 1) % i_number_of_contiguous_data_bytes;

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_current_offset
  );

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_current_offset
  );

  p_sort_element->s_key[p_sort_element->i_key_size++] = (uint8_t)((i64 >> 48) % 256);
  i_current_offset = (i_current_offset + 1) % i_number_of_contiguous_data_bytes;

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_current_offset
  );

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_current_offset
  );

  p_sort_element->s_key[p_sort_element->i_key_size++] = (uint8_t)((i64 >> 40) % 256);
  i_current_offset = (i_current_offset + 1) % i_number_of_contiguous_data_bytes;

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_current_offset
  );

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_current_offset
  );

  p_sort_element->s_key[p_sort_element->i_key_size++] = (uint8_t)((i64 >> 32) % 256);
  i_current_offset = (i_current_offset + 1) % i_number_of_contiguous_data_bytes;

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_current_offset
  );

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_current_offset
  );

  p_sort_element->s_key[p_sort_element->i_key_size++] = (uint8_t)((i64 >> 24) % 256);
  i_current_offset = (i_current_offset + 1) % i_number_of_contiguous_data_bytes;

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_current_offset
  );

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_current_offset
  );

  p_sort_element->s_key[p_sort_element->i_key_size++] = (uint8_t)((i64 >> 16) % 256);
  i_current_offset = (i_current_offset + 1) % i_number_of_contiguous_data_bytes;

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_current_offset
  );

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_current_offset
  );

  p_sort_element->s_key[p_sort_element->i_key_size++] = (uint8_t)((i64 >> 8) % 256);
  i_current_offset = (i_current_offset + 1) % i_number_of_contiguous_data_bytes;

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_current_offset
  );

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_before,
      i_number_of_contrelex_padding_bytes_before,
      i_current_offset
  );

  p_sort_element->s_key[p_sort_element->i_key_size++] = (uint8_t)(i64 % 256);
  i_current_offset = (i_current_offset + 1) % i_number_of_contiguous_data_bytes;

  TSODLULS_padd(
      p_sort_element,
      i_number_of_lex_padding_bytes_after,
      i_number_of_contrelex_padding_bytes_after,
      i_current_offset
  );
  return 0;
}//end function TSODLULS_add_bytes_to_key_from_uint64()



