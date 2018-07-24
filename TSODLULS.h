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
#ifndef DEF_TSODLULS
#define DEF_TSODLULS

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include <endian.h>
#include <ieee754.h>
#include <byteswap.h>

//------------------------------------------------------------------------------------
//Constants
//------------------------------------------------------------------------------------
//Limitations

//Error codes
//Positive error codes are defined in this library for algorithmical, profile parsing and technical errors
#define I_ERROR__COULD_NOT_OPEN_FILE 1
#define I_ERROR__COULD_NOT_ALLOCATE_MEMORY 2
#define I_ERROR__COULD_NOT_WRITE_CHARACTER 3
//Negative error codes are user defined


//------------------------------------------------------------------------------------
//Structures
//------------------------------------------------------------------------------------
/**
 * The structure to be sorted by ULS
 */
typedef struct TSODLULS_sort_element {
  void* p_object;
  size_t i_key_size;
  size_t i_allocated_size;
  unsigned char* s_key;
} t_TSODLULS_sort_element;



//------------------------------------------------------------------------------------
//Conversion of finite orders
//------------------------------------------------------------------------------------
/**
 * Conversion of finite orders to unsigned integer types
 * Change a float into an uint32
 * Nan (not a number) are separated into positive and negative nan.
 * The ordering is as follow : -nan, -inf, negative numbers, -0, +0, positive numbers, inf, nan.
 * Use a custom function if you want to detect (-)nan floats and order them differently.
 */
uint32_t TSODLULS_get_uint_from_float(float f_float);



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint32 to the float encoded by it (see TSODLULS_get_uint_from_float)
 */
float TSODLULS_get_float_from_uint(uint32_t i32);



/**
 * Conversion of finite orders to unsigned integer types
 * Change a float into an uint64
 * Nan (not a number) are separated into positive and negative nan.
 * The ordering is as follow : -nan, -inf, negative numbers, -0, +0, positive numbers, inf, nan.
 * Use a custom function if you want to detect (-)nan floats and order them differently.
 */
uint64_t TSODLULS_get_uint_from_double(double f_double);



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint32 to the float encoded by it (see TSODLULS_get_uint_from_double)
 */
double TSODLULS_get_double_from_uint(uint64_t i64);



/**
 * Conversion of finite orders to unsigned integer types
 * Change an int8 into an uint8 so that order is preserved
 */
uint8_t TSODLULS_get_uint8_from_int8(int8_t i8);



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint8 to the int encoded by it (see TSODLULS_get_uint8_from_int8)
 */
int8_t TSODLULS_get_int8_from_uint8(uint8_t i8);



/**
 * Conversion of finite orders to unsigned integer types
 * Change an int16 into an uint16 so that order is preserved
 */
uint16_t TSODLULS_get_uint16_from_int16(int16_t i16);



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint16 to the int encoded by it (see TSODLULS_get_uint16_from_int16)
 */
int16_t TSODLULS_get_int16_from_uint16(uint16_t i16);



/**
 * Conversion of finite orders to unsigned integer types
 * Change an int32 into an uint32 so that order is preserved
 */
uint32_t TSODLULS_get_uint32_from_int32(int32_t i32);



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint32 to the int encoded by it (see TSODLULS_get_uint32_from_int32)
 */
int32_t TSODLULS_get_int32_from_uint32(uint32_t i32);



/**
 * Conversion of finite orders to unsigned integer types
 * Change an int64 into an uint64 so that order is preserved
 */
uint64_t TSODLULS_get_uint64_from_int64(int64_t i64);



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint64 to the int encoded by it (see TSODLULS_get_uint64_from_int64)
 */
int64_t TSODLULS_get_int64_from_uint64(uint64_t i64);



/**
 * Adding TSO-encoding to the current key
 * From uint8
 */
int TSODLULS_add_bytes_to_key_from_uint8(
  t_TSODLULS_sort_element* p_sort_element,
  uint8_t i8,
  int8_t i_number_of_lex_padding_bytes,
  int8_t i_number_of_contrelex_padding_bytes
);



/**
 * Adding TSO-encoding to the current key
 * From uint16
 */
int TSODLULS_add_bytes_to_key_from_uint16(
  t_TSODLULS_sort_element* p_sort_element,
  uint16_t i16,
  int8_t i_number_of_lex_padding_bytes,
  int8_t i_number_of_contrelex_padding_bytes
);



/**
 * Adding TSO-encoding to the current key
 * From uint32
 */
int TSODLULS_add_bytes_to_key_from_uint32(
  t_TSODLULS_sort_element* p_sort_element,
  uint32_t i32,
  int8_t i_number_of_lex_padding_bytes,
  int8_t i_number_of_contrelex_padding_bytes
);



/**
 * Adding TSO-encoding to the current key
 * From uint64
 */
int TSODLULS_add_bytes_to_key_from_uint64(
  t_TSODLULS_sort_element* p_sort_element,
  uint64_t i64,
  int8_t i_number_of_lex_padding_bytes,
  int8_t i_number_of_contrelex_padding_bytes
);



#endif
