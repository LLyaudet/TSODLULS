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

©Copyright 2018-2021 Laurent Lyaudet
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
#include <limits.h>

//------------------------------------------------------------------------------------
//Constants
//------------------------------------------------------------------------------------
#define I_HALF_BYTE -1//sometimes 4 bits are sufficient for padding

//Error codes
//Positive error codes are defined in this library for algorithmical, profile parsing and technical errors
//-general errors
#define I_ERROR__COULD_NOT_OPEN_FILE 1
#define I_ERROR__COULD_NOT_ALLOCATE_MEMORY 2
#define I_ERROR__COULD_NOT_WRITE_CHARACTER 3
//-padding parameters errors
#define I_ERROR__BOTH_LEX_AND_CONTRELEX_PADDING_BYTES_BEFORE_MUST_BE_HALF_BYTES 100
#define I_ERROR__BOTH_LEX_AND_CONTRELEX_PADDING_BYTES_AFTER_MUST_BE_HALF_BYTES 101
#define I_ERROR__NUMBER_OF_LEX_PADDING_BYTES_BEFORE_IS_INVALID 102
#define I_ERROR__NUMBER_OF_CONTRELEX_PADDING_BYTES_BEFORE_IS_INVALID 103
#define I_ERROR__NUMBER_OF_LEX_PADDING_BYTES_AFTER_IS_INVALID 104
#define I_ERROR__NUMBER_OF_CONTRELEX_PADDING_BYTES_AFTER_IS_INVALID 105
#define I_ERROR__NUMBER_OF_CONTIGUOUS_DATA_BYTES_MUST_BE_AT_LEAST_1 106
#define I_ERROR__CURRENT_OFFSET_MUST_BE_AT_LEAST_0 107
#define I_ERROR__CURRENT_OFFSET_MUST_BE_LESS_THAN_THE_NUMBER_OF_CONTIGUOUS_DATA_BYTES 108
//-sorting parameters errors
#define I_ERROR__MAX_LENGTH_SHOULD_BE_POSITIVE 200
#define I_ERROR__MAX_LENGTH_SHOULD_BE_AT_MOST_8 201
//padding increment/decrement on lex or contrelex node errors
#define I_ERROR__COULD_NOT_DECREASE_LEX_MULTIBYTE 300
#define I_ERROR__COULD_NOT_INCREASE_CONTRELEX_MULTIBYTE 301
//Negative error codes are user defined


//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
//Structures
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//External structures
//------------------------------------------------------------------------------------
/**
 * The structure to be sorted by ULS for long orders
 */
typedef struct TSODLULS_sort_element {
  void* p_object;
  size_t i_key_size;
  size_t i_allocated_size;
  uint8_t* s_key;
} t_TSODLULS_sort_element;



/**
 * The structure to be sorted by ULS for short orders
 */
typedef struct TSODLULS_sort_element__short {
  void* p_object;
  uint64_t i_key;
} t_TSODLULS_sort_element__short;



//------------------------------------------------------------------------------------
//Internal structures for the sorting algorithms
//------------------------------------------------------------------------------------
typedef struct TSODLULS_radix_instance {
  size_t i_offset_first;
  size_t i_offset_last;
  size_t i_depth;
  unsigned int b_copy;
} t_TSODLULS_radix_instance;



typedef struct TSODLULS_radix_instance__no_copy {
  size_t i_offset_first;
  size_t i_offset_last;
  size_t i_depth;
} t_TSODLULS_radix_instance__no_copy;



typedef struct {
  t_TSODLULS_sort_element* p_low;
  t_TSODLULS_sort_element* p_high;
} t_TSODLULS_qsort_stack_node;



typedef struct {
  t_TSODLULS_sort_element__short* p_low;
  t_TSODLULS_sort_element__short* p_high;
} t_TSODLULS_qsort_stack_node__short;



//------------------------------------------------------------------------------------
//Conversion of finite orders
//------------------------------------------------------------------------------------
/**
 * Conversion of finite orders to unsigned integer types
 * Change a float into an uint32
 * Nan (not a number) are separated into positive and negative nan.
 * The ordering is as follow: -nan, -inf, negative numbers, -0, +0, positive numbers, inf, nan.
 * Use a custom function if you want to detect (-)nan floats and order them differently.
 * Available as a macraff (see TSODLULS_finite_orders__macro.h).
 */
uint32_t TSODLULS_get_uint_from_float(float f_float);



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint32 to the float encoded by it (see TSODLULS_get_uint_from_float)
 * Available as a macraff (see TSODLULS_finite_orders__macro.h).
 */
float TSODLULS_get_float_from_uint(uint32_t i32);



/**
 * Conversion of finite orders to unsigned integer types
 * Change a double into an uint64
 * Nan (not a number) are separated into positive and negative nan.
 * The ordering is as follow: -nan, -inf, negative numbers, -0, +0, positive numbers, inf, nan.
 * Use a custom function if you want to detect (-)nan floats and order them differently.
 * Available as a macraff (see TSODLULS_finite_orders__macro.h).
 */
uint64_t TSODLULS_get_uint_from_double(double f_double);



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint64 to the double encoded by it (see TSODLULS_get_uint_from_double)
 * Available as a macraff (see TSODLULS_finite_orders__macro.h).
 */
double TSODLULS_get_double_from_uint(uint64_t i64);



/**
 * Conversion of finite orders to unsigned integer types
 * Change an int8 into an uint8 so that order is preserved
 * Available as a macraff (see TSODLULS_finite_orders__macro.h).
 */
uint8_t TSODLULS_get_uint8_from_int8(int8_t i8);



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint8 to the int encoded by it (see TSODLULS_get_uint8_from_int8)
 * Available as a macraff (see TSODLULS_finite_orders__macro.h).
 */
int8_t TSODLULS_get_int8_from_uint8(uint8_t i8);



/**
 * Conversion of finite orders to unsigned integer types
 * Change an int16 into an uint16 so that order is preserved
 * Available as a macraff (see TSODLULS_finite_orders__macro.h).
 */
uint16_t TSODLULS_get_uint16_from_int16(int16_t i16);



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint16 to the int encoded by it (see TSODLULS_get_uint16_from_int16)
 * Available as a macraff (see TSODLULS_finite_orders__macro.h).
 */
int16_t TSODLULS_get_int16_from_uint16(uint16_t i16);



/**
 * Conversion of finite orders to unsigned integer types
 * Change an int32 into an uint32 so that order is preserved
 * Available as a macraff (see TSODLULS_finite_orders__macro.h).
 */
uint32_t TSODLULS_get_uint32_from_int32(int32_t i32);



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint32 to the int encoded by it (see TSODLULS_get_uint32_from_int32)
 * Available as a macraff (see TSODLULS_finite_orders__macro.h).
 */
int32_t TSODLULS_get_int32_from_uint32(uint32_t i32);



/**
 * Conversion of finite orders to unsigned integer types
 * Change an int64 into an uint64 so that order is preserved
 * Available as a macraff (see TSODLULS_finite_orders__macro.h).
 */
uint64_t TSODLULS_get_uint64_from_int64(int64_t i64);



/**
 * Conversion of finite orders to unsigned integer types and back
 * Change an uint64 to the int encoded by it (see TSODLULS_get_uint64_from_int64)
 * Available as a macraff (see TSODLULS_finite_orders__macro.h).
 */
int64_t TSODLULS_get_int64_from_uint64(uint64_t i64);



/**
 * Adding TSO-encoding to the current key
 * From uint8
 * Available as a macraff (see TSODLULS_finite_orders__macro.h).
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
);



/**
 * Adding TSO-encoding to the current key
 * From uint16
 * Available as a macraff (see TSODLULS_finite_orders__macro.h).
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
);



/**
 * Adding TSO-encoding to the current key
 * From uint32
 * Available as a macraff (see TSODLULS_finite_orders__macro.h).
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
);



/**
 * Adding TSO-encoding to the current key
 * From uint64
 * Available as a macraff (see TSODLULS_finite_orders__macro.h).
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
);



//------------------------------------------------------------------------------------
//Sorting long orders
//------------------------------------------------------------------------------------
/**
 * Sorting functions for long nextified strings
 * The current state of the art sorting function for nextified strings.
 * Its implementation may change without warning.
 */
int TSODLULS_sort(t_TSODLULS_sort_element* arr_elements, size_t i_number_of_elements);



/**
 * Sorting functions for long nextified strings
 * The current state of the art stable sorting function for nextified strings.
 * Its implementation may change without warning.
 */
int TSODLULS_sort_stable(t_TSODLULS_sort_element* arr_elements, size_t i_number_of_elements);



/**
 * Sorting functions for long nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 */
int TSODLULS_sort_radix8_count(t_TSODLULS_sort_element* arr_elements, size_t i_number_of_elements);



/**
 * Sorting functions for long nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements to sort is at most: 5 for initial sort or 2 for radix sequel, we use insertion sort
 */
int TSODLULS_sort_radix8_count_insertion(
  t_TSODLULS_sort_element* arr_elements,
  size_t i_number_of_elements
);



//------------------------------------------------------------------------------------
//Sorting short orders
//------------------------------------------------------------------------------------
/**
 * Sorting functions for short nextified strings
 * The current state of the art sorting function for nextified strings.
 * Its implementation may change without warning.
 */
int TSODLULS_sort__short(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
);



/**
 * Sorting functions for short nextified strings
 * The current state of the art stable sorting function for nextified strings.
 * Its implementation may change without warning.
 */
int TSODLULS_sort_stable__short(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
);



/**
 * Sorting functions for short nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 */
int TSODLULS_sort_radix8_count__short(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
);



/**
 * Sorting functions for short nextified strings
 * Qsort from glibc inlined with short cells.
 */
int TSODLULS_qsort_inlined__short(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements
);



/**
 * Sorting functions for short nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements to sort is at most 5, we use insertion sort
 * A variant with single memory allocation adapted to the max-depth.
 * No insertion sort if there is more than 5 elements and it is 8 bits datatype.
 * This is the current best algorithm and it is a stable one :)
 */
int TSODLULS_sort_radix8_count_insertion__short(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
);



//------------------------------------------------------------------------------------
//Comparing
//------------------------------------------------------------------------------------
/**
 * Comparison function
 * uint8 pointers
 */
int TSODLULS_compare_uint8_direct(const void *a, const void *b);



/**
 * Comparison function
 * uint16 pointers
 */
int TSODLULS_compare_uint16_direct(const void *a, const void *b);



/**
 * Comparison function
 * uint32 pointers
 */
int TSODLULS_compare_uint32_direct(const void *a, const void *b);



/**
 * Comparison function
 * uint64 pointers
 */
int TSODLULS_compare_uint64_direct(const void *a, const void *b);



/**
 * Comparison function
 * int8 pointers
 */
int TSODLULS_compare_int8_direct(const void *a, const void *b);


/**
 * Comparison function
 * int16 pointers
 */
int TSODLULS_compare_int16_direct(const void *a, const void *b);



/**
 * Comparison function
 * int32 pointers
 */
int TSODLULS_compare_int32_direct(const void *a, const void *b);



/**
 * Comparison function
 * int64 pointers
 */
int TSODLULS_compare_int64_direct(const void *a, const void *b);



/**
 * Comparison function
 * float pointers
 */
int TSODLULS_compare_float_direct(const void *a, const void *b);



/**
 * Comparison function
 * double pointers
 */
int TSODLULS_compare_double_direct(const void *a, const void *b);



/**
 * Comparison function
 * uint8 in TSODLULS cell
 */
int TSODLULS_compare_uint8_in_cell(const void *a, const void *b);



/**
 * Comparison function
 * uint16 in TSODLULS cell
 */
int TSODLULS_compare_uint16_in_cell(const void *a, const void *b);



/**
 * Comparison function
 * uint32 in TSODLULS cell
 */
int TSODLULS_compare_uint32_in_cell(const void *a, const void *b);



/**
 * Comparison function
 * uint64 in TSODLULS cell
 */
int TSODLULS_compare_uint64_in_cell(const void *a, const void *b);



/**
 * Comparison function
 * nextified key in TSODLULS cell
 */
int TSODLULS_compare_nextified_key_in_cell(const void *a, const void *b);



/**
 * Comparison function
 * nextified key in TSODLULS cell for short orders
 */
int TSODLULS_compare_nextified_key_in_cell__short(const void *a, const void *b);



//------------------------------------------------------------------------------------
//Miscellaneous
//------------------------------------------------------------------------------------
/**
 * Miscellaneous functions
 * Initialize a TSODLULS element
 * Available as a macraff (see TSODLULS_misc__macro.h).
 */
void TSODLULS_init_element(t_TSODLULS_sort_element* p_element);



/**
 * Miscellaneous functions
 * Free the key of a TSODLULS element (if necessary) and reinitializes the corresponding fields
 * Available as a macraff (see TSODLULS_misc__macro.h).
 */
void TSODLULS_free_key(t_TSODLULS_sort_element* p_element);



/**
 * Miscellaneous functions
 * Initialize an array of TSODLULS elements
 * Available as a macraff (see TSODLULS_misc__macro.h).
 */
int TSODLULS_init_array_of_elements(t_TSODLULS_sort_element** p_arr_elements, size_t i_number_of_elements);



/**
 * Miscellaneous functions
 * Free the keys of all TSODLULS elements in an array
 * Available as a macraff (see TSODLULS_misc__macro.h).
 */
void TSODLULS_free_keys_in_array_of_elements(t_TSODLULS_sort_element* arr_elements, size_t i_number_of_elements);



/**
 * Miscellaneous functions
 * (Re)Allocate space for the key of a TSODLULS element
 * Available as a macraff (see TSODLULS_misc__macro.h).
 */
int TSODLULS_element_allocate_space_for_key(
  t_TSODLULS_sort_element* p_sort_element,
  size_t i_size_needed
);



/**
 * Miscellaneous functions
 * Initialize a TSODLULS element for short orders
 * Available as a macraff (see TSODLULS_misc__macro.h).
 */
void TSODLULS_init_element__short(t_TSODLULS_sort_element__short* p_element);



/**
 * Miscellaneous functions
 * Initialize an array of TSODLULS elements for short orders
 * Available as a macraff (see TSODLULS_misc__macro.h).
 */
int TSODLULS_init_array_of_elements__short(
  t_TSODLULS_sort_element__short** p_arr_elements,
  size_t i_number_of_elements
);



//------------------------------------------------------------------------------------
//Padding
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
);



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
);



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
);



/**
 * Padding functions
 * Decrease last lex padding multibyte
 * (Done once at the end of a string for a lex node)
 */
int TSODLULS_decrease_last_lex_padding(
  t_TSODLULS_sort_element* p_sort_element,
  int8_t i_number_of_lex_padding_bytes,
  int8_t i_number_of_contrelex_padding_bytes
);



/**
 * Padding functions
 * Increase last contrelex padding multibyte
 * (Done once at the end of a string for a contrelex node)
 */
int TSODLULS_increase_last_contrelex_padding(
  t_TSODLULS_sort_element* p_sort_element,
  int8_t i_number_of_contrelex_padding_bytes
);



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
);



#include "TSODLULS__macro.h"

#endif
