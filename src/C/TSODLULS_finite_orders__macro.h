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
/*
This file contains macraffs corresponding to the functions in TSODLULS_finite_orders.c.
It is more pleasant to look at the source code there than to read the macros and macraffs here.
The macraffs in this file use the following auxiliary variables:
  union ieee754_float TSODLULS_macraff_ieee754_float;
  union ieee754_double TSODLULS_macraff_ieee754_double;
  uint8_t TSODLULS_macraff_ui8;
  uint16_t TSODLULS_macraff_ui16;
  uint32_t TSODLULS_macraff_ui32;
  uint64_t TSODLULS_macraff_ui64;
  int8_t TSODLULS_macraff_i8;
  int8_t TSODLULS_macraff_i8_2;
  int8_t TSODLULS_macraff_i8_3;
  int8_t TSODLULS_macraff_i8_4;
  int8_t TSODLULS_macraff_i8_5;
  int8_t TSODLULS_macraff_i8_6;
  int8_t TSODLULS_macraff_i8_7;
  int8_t TSODLULS_macraff_i8_8;
  int8_t TSODLULS_macraff_i8_9;
  int8_t TSODLULS_macraff_i8_10;
  int8_t TSODLULS_macraff_i8_11;
  int8_t TSODLULS_macraff_i8_12;
  int16_t TSODLULS_macraff_i16;
  int32_t TSODLULS_macraff_i32;
  int64_t TSODLULS_macraff_i64;
  int TSODLULS_macraff_i;
  size_t TSODLULS_macraff_isize;
  size_t TSODLULS_macraff_isize_2;
  size_t TSODLULS_macraff_isize_3;
  size_t TSODLULS_macraff_isize_4;
  t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element;
  t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element_2;
  void* TSODLULS_macraff_p_void;
*/


//------------------------------------------------------------------------------------
//External macros
//------------------------------------------------------------------------------------
/**
 * Conversion of finite orders to unsigned integer types
 * Change a float into an uint32
 * Nan (not a number) are separated into positive and negative nan.
 * The ordering is as follow: -nan, -inf, negative numbers, -0, +0, positive numbers, inf, nan.
 * Use a custom function if you want to detect (-)nan floats and order them differently.
 * This macraff requires the following auxiliary variable:
 *   union ieee754_float TSODLULS_macraff_ieee754_float;
 */
#define TSODLULS_get_uint_from_float__macraff(ui_32_aff, f_float) \
do{\
  TSODLULS_macraff_ieee754_float.f = (f_float);\
  if(TSODLULS_macraff_ieee754_float.ieee.negative == 1){\
    (ui_32_aff) =\
        (((uint32_t)1) << 31)\
      - (  (((uint32_t)TSODLULS_macraff_ieee754_float.ieee.exponent) << 23)\
         + ((uint32_t)TSODLULS_macraff_ieee754_float.ieee.mantissa)\
         + 1\
        )\
    ;\
    break;\
  }\
  (ui_32_aff) =\
      (((uint32_t)1) << 31)\
    + (((uint32_t)TSODLULS_macraff_ieee754_float.ieee.exponent) << 23)\
    + ((uint32_t)TSODLULS_macraff_ieee754_float.ieee.mantissa);\
}while(0);



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint32 to the float encoded by it (see TSODLULS_get_uint_from_float)
 * This macraff requires the following auxiliary variables:
 *   union ieee754_float TSODLULS_macraff_ieee754_float;
 *   uint32_t TSODLULS_macraff_ui32;
 */
#define TSODLULS_get_float_from_uint__macraff(f_float_aff, ui32) \
do{\
  TSODLULS_macraff_ui32 = (ui32);\
  if(TSODLULS_macraff_ui32 < (((uint32_t)1) << 31)){\
    TSODLULS_macraff_ui32 = (((uint32_t)1) << 31) - TSODLULS_macraff_ui32 - 1;\
    TSODLULS_macraff_ieee754_float.ieee.negative = 1;\
  }\
  else{\
    TSODLULS_macraff_ieee754_float.ieee.negative = 0;\
  }\
  TSODLULS_macraff_ieee754_float.ieee.exponent = (TSODLULS_macraff_ui32 >> 23) % (((uint32_t)1) << 8);\
  TSODLULS_macraff_ieee754_float.ieee.mantissa = TSODLULS_macraff_ui32 % (((uint32_t)1) << 23);\
  (f_float_aff) = TSODLULS_macraff_ieee754_float.f;\
}while(0);



/**
 * Conversion of finite orders to unsigned integer types
 * Change a double into an uint64
 * Nan (not a number) are separated into positive and negative nan.
 * The ordering is as follow: -nan, -inf, negative numbers, -0, +0, positive numbers, inf, nan.
 * Use a custom function if you want to detect (-)nan floats and order them differently.
 * This macraff requires the following auxiliary variable:
 *   union ieee754_double TSODLULS_macraff_ieee754_double;
 */
#define TSODLULS_get_uint_from_double__macraff(ui_64_aff, f_double) \
do{\
  TSODLULS_macraff_ieee754_double.d = (f_double);\
  if(TSODLULS_macraff_ieee754_double.ieee.negative == 1){\
    (ui_64_aff) = \
        (((uint64_t)1) << 63)\
      - (  (((uint64_t)TSODLULS_macraff_ieee754_double.ieee.exponent) << 52)\
         + (((uint64_t)TSODLULS_macraff_ieee754_double.ieee.mantissa0) << 32)\
         + ((uint64_t)TSODLULS_macraff_ieee754_double.ieee.mantissa1)\
         + 1\
        )\
    ;\
    break;\
  }\
  (ui_64_aff) = \
      (((uint64_t)1) << 63)\
    + (((uint64_t)TSODLULS_macraff_ieee754_double.ieee.exponent) << 52)\
    + (((uint64_t)TSODLULS_macraff_ieee754_double.ieee.mantissa0) << 32)\
    + ((uint64_t)TSODLULS_macraff_ieee754_double.ieee.mantissa1);\
}while(0);



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint64 to the double encoded by it (see TSODLULS_get_uint_from_double)
 * This macraff requires the following auxiliary variables:
 *   union ieee754_double TSODLULS_macraff_ieee754_double;
 *   uint64_t TSODLULS_macraff_ui64;
 */
#define TSODLULS_get_double_from_uint__macraff(f_double_aff, ui64) \
do{\
  TSODLULS_macraff_ui64 = (ui64);\
  if(TSODLULS_macraff_ui64 < (((uint64_t)1) << 63)){\
    TSODLULS_macraff_ui64 = (((uint64_t)1) << 63) - TSODLULS_macraff_ui64 - 1;\
    TSODLULS_macraff_ieee754_double.ieee.negative = 1;\
  }\
  else{\
    TSODLULS_macraff_ieee754_double.ieee.negative = 0;\
  }\
  TSODLULS_macraff_ieee754_double.ieee.exponent = (TSODLULS_macraff_ui64 >> 52) % (((uint64_t)1) << 11);\
  TSODLULS_macraff_ieee754_double.ieee.mantissa0 = (TSODLULS_macraff_ui64 >> 32) % (((uint64_t)1) << 20);\
  TSODLULS_macraff_ieee754_double.ieee.mantissa1 = TSODLULS_macraff_ui64 % (((uint64_t)1) << 32);\
  (f_double_aff) = TSODLULS_macraff_ieee754_double.d;\
}while(0);



/**
 * Conversion of finite orders to unsigned integer types
 * Change an int8 into an uint8 so that order is preserved
 * This macraff requires the following auxiliary variable:
 *   int8_t TSODLULS_macraff_i8;
 */
#define TSODLULS_get_uint8_from_int8__macraff(ui8_aff, i8) \
do{\
  TSODLULS_macraff_i8 = (i8);\
  if(TSODLULS_macraff_i8 >= 0){\
    (ui8_aff) = ((uint8_t)TSODLULS_macraff_i8) + (((uint8_t)1) << 7);\
    break;\
  }\
  (ui8_aff) =  ((uint8_t)((INT8_MAX + TSODLULS_macraff_i8) + 1));\
}while(0);



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint8 to the int encoded by it (see TSODLULS_get_uint8_from_int8)
 * This macraff requires the following auxiliary variable:
 *   uint8_t TSODLULS_macraff_ui8;
 */
#define TSODLULS_get_int8_from_uint8__macraff(i8_aff, ui8) \
do{\
  TSODLULS_macraff_ui8 = (ui8);\
  if(TSODLULS_macraff_ui8 >= (((uint8_t)1) << 7)){\
    (i8_aff) = ((int8_t) (TSODLULS_macraff_ui8 - (((uint8_t)1) << 7)));\
    break;\
  }\
  (i8_aff) = ((int8_t)((((uint8_t)1) << 7) + TSODLULS_macraff_ui8));\
}while(0);



/**
 * Conversion of finite orders to unsigned integer types
 * Change an int16 into an uint16 so that order is preserved
 * This macraff requires the following auxiliary variable:
 *   int16_t TSODLULS_macraff_i16;
 */
#define TSODLULS_get_uint16_from_int16__macraff(ui16_aff, i16) \
do{\
  TSODLULS_macraff_i16 = (i16);\
  if(TSODLULS_macraff_i16 >= 0){\
    (ui16_aff) = ((uint16_t)TSODLULS_macraff_i16) + (((uint16_t)1) << 15);\
    break;\
  }\
  (ui16_aff) = ((uint16_t)((INT16_MAX + TSODLULS_macraff_i16) + 1));\
}while(0);



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint16 to the int encoded by it (see TSODLULS_get_uint16_from_int16)
 * This macraff requires the following auxiliary variable:
 *   uint16_t TSODLULS_macraff_ui16;
 */
#define TSODLULS_get_int16_from_uint16__macraff(i16_aff, ui16) \
do{\
  TSODLULS_macraff_ui16 = (ui16);\
  if(TSODLULS_macraff_ui16 >= (((uint16_t)1) << 15)){\
    (i16_aff) = ((int16_t) (TSODLULS_macraff_ui16 - (((uint16_t)1) << 15)));\
    break;\
  }\
  (i16_aff) =  ((int16_t)((((uint16_t)1) << 15) + TSODLULS_macraff_ui16));\
}while(0);



/**
 * Conversion of finite orders to unsigned integer types
 * Change an int32 into an uint32 so that order is preserved
 * This macraff requires the following auxiliary variable:
 *   int32_t TSODLULS_macraff_i32;
 */
#define TSODLULS_get_uint32_from_int32__macraff(ui32_aff, i32) \
do{\
  TSODLULS_macraff_i32 = (i32);\
  if(TSODLULS_macraff_i32 >= 0){\
    (ui32_aff) = ((uint32_t)TSODLULS_macraff_i32) + (((uint32_t)1) << 31);\
    break;\
  }\
  (ui32_aff) = ((uint32_t)((INT32_MAX + TSODLULS_macraff_i32) + 1));\
}while(0);



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint32 to the int encoded by it (see TSODLULS_get_uint32_from_int32)
 * This macraff requires the following auxiliary variable:
 *   uint32_t TSODLULS_macraff_ui32;
 */
#define TSODLULS_get_int32_from_uint32__macraff(i32_aff, ui32) \
do{\
  TSODLULS_macraff_ui32 = (ui32);\
  if(TSODLULS_macraff_ui32 >= (((uint32_t)1) << 31)){\
    (i32_aff) = ((int32_t) (TSODLULS_macraff_ui32 - (((uint32_t)1) << 31)));\
    break;\
  }\
  (i32_aff) = ((int32_t)((((uint32_t)1) << 31) + TSODLULS_macraff_ui32));\
}while(0);



/**
 * Conversion of finite orders to unsigned integer types
 * Change an int64 into an uint64 so that order is preserved
 * This macraff requires the following auxiliary variable:
 *   int64_t TSODLULS_macraff_i64;
 */
#define TSODLULS_get_uint64_from_int64__macraff(ui64_aff, i64) \
do{\
  TSODLULS_macraff_i64 = (i64);\
  if(TSODLULS_macraff_i64 >= 0){\
    (ui64_aff) = ((uint64_t)TSODLULS_macraff_i64) + (((uint64_t)1) << 63);\
    break;\
  }\
  (ui64_aff) = ((uint64_t)((INT64_MAX + TSODLULS_macraff_i64) + 1));\
}while(0);



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint64 to the int encoded by it (see TSODLULS_get_uint64_from_int64)
 * This macraff requires the following auxiliary variable:
 *   uint64_t TSODLULS_macraff_ui64;
 */
#define TSODLULS_get_int64_from_uint64__macraff(i64_aff, ui64) \
do{\
  TSODLULS_macraff_ui64 = (ui64);\
  if(TSODLULS_macraff_ui64 >= (((uint64_t)1) << 63)){\
    (i64_aff) = ((int64_t) (TSODLULS_macraff_ui64 - (((uint64_t)1) << 63)));\
    break;\
  }\
  (i64_aff) =  ((int64_t)((((uint64_t)1) << 63) + TSODLULS_macraff_ui64));\
}while(0);



/**
 * Adding TSO-encoding to the current key
 * From uint8
 * This macraff requires the following auxiliary variables:
 *   uint8_t TSODLULS_macraff_ui8;
 *   int8_t TSODLULS_macraff_i8;
 *   int8_t TSODLULS_macraff_i8_2;
 *   int8_t TSODLULS_macraff_i8_3;
 *   int8_t TSODLULS_macraff_i8_4;
 *   int8_t TSODLULS_macraff_i8_5;
 *   int8_t TSODLULS_macraff_i8_6;
 *   int8_t TSODLULS_macraff_i8_7;
 *   int8_t TSODLULS_macraff_i8_8;
 *   int8_t TSODLULS_macraff_i8_9;
 *   int8_t TSODLULS_macraff_i8_10;
 *   int8_t TSODLULS_macraff_i8_11;
 *   int8_t TSODLULS_macraff_i8_12;
 *   int TSODLULS_macraff_i;
 *   size_t TSODLULS_macraff_isize;
 *   size_t TSODLULS_macraff_isize_2;
 *   size_t TSODLULS_macraff_isize_3;
 *   size_t TSODLULS_macraff_isize_4;
 *   t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element;
 *   t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element_2;
 *   void* TSODLULS_macraff_p_void;
 * There are many auxiliary variables because of nested macraffs.
 */
#define TSODLULS_add_bytes_to_key_from_uint8__macraff(\
  i_aff,\
  p_sort_element,\
  i8,\
  i_number_of_lex_padding_bytes_before,\
  i_number_of_contrelex_padding_bytes_before,\
  i_number_of_lex_padding_bytes_after,\
  i_number_of_contrelex_padding_bytes_after,\
  i_number_of_contiguous_data_bytes,\
  i_current_offset\
) \
do{\
  TSODLULS_macraff_p_sort_element_2 = (p_sort_element);\
  TSODLULS_macraff_ui8 = (i8);\
  TSODLULS_macraff_i8_7 = (i_number_of_lex_padding_bytes_before);\
  TSODLULS_macraff_i8_8 = (i_number_of_contrelex_padding_bytes_before);\
  TSODLULS_macraff_i8_9 = (i_number_of_lex_padding_bytes_after);\
  TSODLULS_macraff_i8_10 = (i_number_of_contrelex_padding_bytes_after);\
  TSODLULS_macraff_i8_11 = (i_number_of_contiguous_data_bytes);\
  TSODLULS_macraff_i8_12 = (i_current_offset);\
\
  TSODLULS_macraff_isize_4 = 1;\
  TSODLULS_macraff_i = 0;\
\
  TSODLULS_check_padding_parameters__macraff(\
      TSODLULS_macraff_i,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_11,\
      TSODLULS_macraff_i8_12\
  );\
  if(TSODLULS_macraff_i != 0){\
    (i_aff) = TSODLULS_macraff_i;\
    break;\
  }\
\
  TSODLULS_compute_size_needed__macraff(\
      TSODLULS_macraff_isize_4,\
      1,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_11,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_element_allocate_space_for_key__macraff(\
      TSODLULS_macraff_i,\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_isize_4\
  );\
  if(TSODLULS_macraff_i != 0){\
    (i_aff) = TSODLULS_macraff_i;\
    break;\
  }\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_macraff_p_sort_element_2->s_key[TSODLULS_macraff_p_sort_element_2->i_key_size++] = (uint8_t)TSODLULS_macraff_ui8;\
  TSODLULS_macraff_i8_12 = (TSODLULS_macraff_i8_12 + 1) % TSODLULS_macraff_i8_11;\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_12\
  );\
  (i_aff) = 0;\
}while(0);



/**
 * Adding TSO-encoding to the current key
 * From uint16
 * This macraff requires the following auxiliary variables:
 *   uint16_t TSODLULS_macraff_ui16;
 *   int8_t TSODLULS_macraff_i8;
 *   int8_t TSODLULS_macraff_i8_2;
 *   int8_t TSODLULS_macraff_i8_3;
 *   int8_t TSODLULS_macraff_i8_4;
 *   int8_t TSODLULS_macraff_i8_5;
 *   int8_t TSODLULS_macraff_i8_6;
 *   int8_t TSODLULS_macraff_i8_7;
 *   int8_t TSODLULS_macraff_i8_8;
 *   int8_t TSODLULS_macraff_i8_9;
 *   int8_t TSODLULS_macraff_i8_10;
 *   int8_t TSODLULS_macraff_i8_11;
 *   int8_t TSODLULS_macraff_i8_12;
 *   int TSODLULS_macraff_i;
 *   size_t TSODLULS_macraff_isize;
 *   size_t TSODLULS_macraff_isize_2;
 *   size_t TSODLULS_macraff_isize_3;
 *   size_t TSODLULS_macraff_isize_4;
 *   t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element;
 *   t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element_2;
 *   void* TSODLULS_macraff_p_void;
 * There are many auxiliary variables because of nested macraffs.
 */
#define TSODLULS_add_bytes_to_key_from_uint16__macraff(\
  i_aff,\
  p_sort_element,\
  i16,\
  i_number_of_lex_padding_bytes_before,\
  i_number_of_contrelex_padding_bytes_before,\
  i_number_of_lex_padding_bytes_after,\
  i_number_of_contrelex_padding_bytes_after,\
  i_number_of_contiguous_data_bytes,\
  i_current_offset\
) \
do{\
  TSODLULS_macraff_p_sort_element_2 = (p_sort_element);\
  TSODLULS_macraff_ui16 = (i16);\
  TSODLULS_macraff_i8_7 = (i_number_of_lex_padding_bytes_before);\
  TSODLULS_macraff_i8_8 = (i_number_of_contrelex_padding_bytes_before);\
  TSODLULS_macraff_i8_9 = (i_number_of_lex_padding_bytes_after);\
  TSODLULS_macraff_i8_10 = (i_number_of_contrelex_padding_bytes_after);\
  TSODLULS_macraff_i8_11 = (i_number_of_contiguous_data_bytes);\
  TSODLULS_macraff_i8_12 = (i_current_offset);\
\
  TSODLULS_macraff_isize_4 = 2;\
  TSODLULS_macraff_i = 0;\
\
  TSODLULS_check_padding_parameters__macraff(\
      TSODLULS_macraff_i,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_11,\
      TSODLULS_macraff_i8_12\
  );\
  if(TSODLULS_macraff_i != 0){\
    (i_aff) = TSODLULS_macraff_i;\
    break;\
  }\
\
  TSODLULS_compute_size_needed__macraff(\
      TSODLULS_macraff_isize_4,\
      2,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_11,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_element_allocate_space_for_key__macraff(\
      TSODLULS_macraff_i,\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_isize_4\
  );\
  if(TSODLULS_macraff_i != 0){\
    (i_aff) = TSODLULS_macraff_i;\
    break;\
  }\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_macraff_p_sort_element_2->s_key[TSODLULS_macraff_p_sort_element_2->i_key_size++] = (uint8_t)(TSODLULS_macraff_ui16 >> 8);\
  TSODLULS_macraff_i8_12 = (TSODLULS_macraff_i8_12 + 1) % TSODLULS_macraff_i8_11;\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_macraff_p_sort_element_2->s_key[TSODLULS_macraff_p_sort_element_2->i_key_size++] = (uint8_t)(TSODLULS_macraff_ui16 % 256);\
  TSODLULS_macraff_i8_12 = (TSODLULS_macraff_i8_12 + 1) % TSODLULS_macraff_i8_11;\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_12\
  );\
  (i_aff) = 0;\
}while(0);



/**
 * Adding TSO-encoding to the current key
 * From uint32
 * This macraff requires the following auxiliary variables:
 *   uint32_t TSODLULS_macraff_ui32;
 *   int8_t TSODLULS_macraff_i8;
 *   int8_t TSODLULS_macraff_i8_2;
 *   int8_t TSODLULS_macraff_i8_3;
 *   int8_t TSODLULS_macraff_i8_4;
 *   int8_t TSODLULS_macraff_i8_5;
 *   int8_t TSODLULS_macraff_i8_6;
 *   int8_t TSODLULS_macraff_i8_7;
 *   int8_t TSODLULS_macraff_i8_8;
 *   int8_t TSODLULS_macraff_i8_9;
 *   int8_t TSODLULS_macraff_i8_10;
 *   int8_t TSODLULS_macraff_i8_11;
 *   int8_t TSODLULS_macraff_i8_12;
 *   int TSODLULS_macraff_i;
 *   size_t TSODLULS_macraff_isize;
 *   size_t TSODLULS_macraff_isize_2;
 *   size_t TSODLULS_macraff_isize_3;
 *   size_t TSODLULS_macraff_isize_4;
 *   t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element;
 *   t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element_2;
 *   void* TSODLULS_macraff_p_void;
 * There are many auxiliary variables because of nested macraffs.
 */
#define TSODLULS_add_bytes_to_key_from_uint32__macraff(\
  i_aff,\
  p_sort_element,\
  i32,\
  i_number_of_lex_padding_bytes_before,\
  i_number_of_contrelex_padding_bytes_before,\
  i_number_of_lex_padding_bytes_after,\
  i_number_of_contrelex_padding_bytes_after,\
  i_number_of_contiguous_data_bytes,\
  i_current_offset\
) \
do{\
  TSODLULS_macraff_p_sort_element_2 = (p_sort_element);\
  TSODLULS_macraff_ui32 = (i32);\
  TSODLULS_macraff_i8_7 = (i_number_of_lex_padding_bytes_before);\
  TSODLULS_macraff_i8_8 = (i_number_of_contrelex_padding_bytes_before);\
  TSODLULS_macraff_i8_9 = (i_number_of_lex_padding_bytes_after);\
  TSODLULS_macraff_i8_10 = (i_number_of_contrelex_padding_bytes_after);\
  TSODLULS_macraff_i8_11 = (i_number_of_contiguous_data_bytes);\
  TSODLULS_macraff_i8_12 = (i_current_offset);\
\
  TSODLULS_macraff_isize_4 = 4;\
  TSODLULS_macraff_i = 0;\
\
  TSODLULS_check_padding_parameters__macraff(\
      TSODLULS_macraff_i,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_11,\
      TSODLULS_macraff_i8_12\
  );\
  if(TSODLULS_macraff_i != 0){\
    (i_aff) = TSODLULS_macraff_i;\
    break;\
  }\
\
  TSODLULS_compute_size_needed__macraff(\
      TSODLULS_macraff_isize_4,\
      4,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_11,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_element_allocate_space_for_key__macraff(\
      TSODLULS_macraff_i,\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_isize_4\
  );\
  if(TSODLULS_macraff_i != 0){\
    (i_aff) = TSODLULS_macraff_i;\
    break;\
  }\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_macraff_p_sort_element_2->s_key[TSODLULS_macraff_p_sort_element_2->i_key_size++] = (uint8_t)(TSODLULS_macraff_ui32 >> 24);\
  TSODLULS_macraff_i8_12 = (TSODLULS_macraff_i8_12 + 1) % TSODLULS_macraff_i8_11;\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_macraff_p_sort_element_2->s_key[TSODLULS_macraff_p_sort_element_2->i_key_size++] = (uint8_t)((TSODLULS_macraff_ui32 >> 16) % 256);\
  TSODLULS_macraff_i8_12 = (TSODLULS_macraff_i8_12 + 1) % TSODLULS_macraff_i8_11;\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_macraff_p_sort_element_2->s_key[TSODLULS_macraff_p_sort_element_2->i_key_size++] = (uint8_t)((TSODLULS_macraff_ui32 >> 8) % 256);\
  TSODLULS_macraff_i8_12 = (TSODLULS_macraff_i8_12 + 1) % TSODLULS_macraff_i8_11;\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_macraff_p_sort_element_2->s_key[TSODLULS_macraff_p_sort_element_2->i_key_size++] = (uint8_t)(TSODLULS_macraff_ui32 % 256);\
  TSODLULS_macraff_i8_12 = (TSODLULS_macraff_i8_12 + 1) % TSODLULS_macraff_i8_11;\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_12\
  );\
  (i_aff) = 0;\
}while(0);



/**
 * Adding TSO-encoding to the current key
 * From uint64
 * This macraff requires the following auxiliary variables:
 *   uint64_t TSODLULS_macraff_ui64;
 *   int8_t TSODLULS_macraff_i8;
 *   int8_t TSODLULS_macraff_i8_2;
 *   int8_t TSODLULS_macraff_i8_3;
 *   int8_t TSODLULS_macraff_i8_4;
 *   int8_t TSODLULS_macraff_i8_5;
 *   int8_t TSODLULS_macraff_i8_6;
 *   int8_t TSODLULS_macraff_i8_7;
 *   int8_t TSODLULS_macraff_i8_8;
 *   int8_t TSODLULS_macraff_i8_9;
 *   int8_t TSODLULS_macraff_i8_10;
 *   int8_t TSODLULS_macraff_i8_11;
 *   int8_t TSODLULS_macraff_i8_12;
 *   int TSODLULS_macraff_i;
 *   size_t TSODLULS_macraff_isize;
 *   size_t TSODLULS_macraff_isize_2;
 *   size_t TSODLULS_macraff_isize_3;
 *   size_t TSODLULS_macraff_isize_4;
 *   t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element;
 *   t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element_2;
 *   void* TSODLULS_macraff_p_void;
 * There are many auxiliary variables because of nested macraffs.
 */
#define TSODLULS_add_bytes_to_key_from_uint64__macraff(\
  i_aff,\
  p_sort_element,\
  i64,\
  i_number_of_lex_padding_bytes_before,\
  i_number_of_contrelex_padding_bytes_before,\
  i_number_of_lex_padding_bytes_after,\
  i_number_of_contrelex_padding_bytes_after,\
  i_number_of_contiguous_data_bytes,\
  i_current_offset\
) \
do{\
  TSODLULS_macraff_p_sort_element_2 = (p_sort_element);\
  TSODLULS_macraff_ui64 = (i64);\
  TSODLULS_macraff_i8_7 = (i_number_of_lex_padding_bytes_before);\
  TSODLULS_macraff_i8_8 = (i_number_of_contrelex_padding_bytes_before);\
  TSODLULS_macraff_i8_9 = (i_number_of_lex_padding_bytes_after);\
  TSODLULS_macraff_i8_10 = (i_number_of_contrelex_padding_bytes_after);\
  TSODLULS_macraff_i8_11 = (i_number_of_contiguous_data_bytes);\
  TSODLULS_macraff_i8_12 = (i_current_offset);\
\
  TSODLULS_macraff_isize_4 = 8;\
  TSODLULS_macraff_i = 0;\
\
  TSODLULS_check_padding_parameters__macraff(\
      TSODLULS_macraff_i,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_11,\
      TSODLULS_macraff_i8_12\
  );\
  if(TSODLULS_macraff_i != 0){\
    (i_aff) = TSODLULS_macraff_i;\
    break;\
  }\
\
  TSODLULS_compute_size_needed__macraff(\
      TSODLULS_macraff_isize_4,\
      8,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_11,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_element_allocate_space_for_key__macraff(\
      TSODLULS_macraff_i,\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_isize_4\
  );\
  if(TSODLULS_macraff_i != 0){\
    (i_aff) = TSODLULS_macraff_i;\
    break;\
  }\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_macraff_p_sort_element_2->s_key[TSODLULS_macraff_p_sort_element_2->i_key_size++] = (uint8_t)(TSODLULS_macraff_ui64 >> 56);\
  TSODLULS_macraff_i8_12 = (TSODLULS_macraff_i8_12 + 1) % TSODLULS_macraff_i8_11;\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_macraff_p_sort_element_2->s_key[TSODLULS_macraff_p_sort_element_2->i_key_size++] = (uint8_t)((TSODLULS_macraff_ui64 >> 48) % 256);\
  TSODLULS_macraff_i8_12 = (TSODLULS_macraff_i8_12 + 1) % TSODLULS_macraff_i8_11;\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_macraff_p_sort_element_2->s_key[TSODLULS_macraff_p_sort_element_2->i_key_size++] = (uint8_t)((TSODLULS_macraff_ui64 >> 40) % 256);\
  TSODLULS_macraff_i8_12 = (TSODLULS_macraff_i8_12 + 1) % TSODLULS_macraff_i8_11;\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_macraff_p_sort_element_2->s_key[TSODLULS_macraff_p_sort_element_2->i_key_size++] = (uint8_t)((TSODLULS_macraff_ui64 >> 32) % 256);\
  TSODLULS_macraff_i8_12 = (TSODLULS_macraff_i8_12 + 1) % TSODLULS_macraff_i8_11;\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_macraff_p_sort_element_2->s_key[TSODLULS_macraff_p_sort_element_2->i_key_size++] = (uint8_t)((TSODLULS_macraff_ui64 >> 24) % 256);\
  TSODLULS_macraff_i8_12 = (TSODLULS_macraff_i8_12 + 1) % TSODLULS_macraff_i8_11;\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_macraff_p_sort_element_2->s_key[TSODLULS_macraff_p_sort_element_2->i_key_size++] = (uint8_t)((TSODLULS_macraff_ui64 >> 16) % 256);\
  TSODLULS_macraff_i8_12 = (TSODLULS_macraff_i8_12 + 1) % TSODLULS_macraff_i8_11;\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_macraff_p_sort_element_2->s_key[TSODLULS_macraff_p_sort_element_2->i_key_size++] = (uint8_t)((TSODLULS_macraff_ui64 >> 8) % 256);\
  TSODLULS_macraff_i8_12 = (TSODLULS_macraff_i8_12 + 1) % TSODLULS_macraff_i8_11;\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_7,\
      TSODLULS_macraff_i8_8,\
      TSODLULS_macraff_i8_12\
  );\
\
  TSODLULS_macraff_p_sort_element_2->s_key[TSODLULS_macraff_p_sort_element_2->i_key_size++] = (uint8_t)(TSODLULS_macraff_ui64 % 256);\
  TSODLULS_macraff_i8_12 = (TSODLULS_macraff_i8_12 + 1) % TSODLULS_macraff_i8_11;\
\
  TSODLULS_padd__macraff(\
      TSODLULS_macraff_p_sort_element_2,\
      TSODLULS_macraff_i8_9,\
      TSODLULS_macraff_i8_10,\
      TSODLULS_macraff_i8_12\
  );\
  (i_aff) = 0;\
}while(0);



