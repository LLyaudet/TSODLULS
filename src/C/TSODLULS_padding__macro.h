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

©Copyright 2018-2020 Laurent Lyaudet
*/
/*
This file contains macraffs corresponding to the functions in TSODLULS_padding.c.
It is more pleasant to look at the source code there than to read the macros and macraffs here.
The macraffs in this file use the following auxiliary variables:
  uint8_t TSODLULS_macraff_ui8;
  uint8_t TSODLULS_macraff_ui8_2;
  uint8_t TSODLULS_macraff_ui8_3;
  int8_t TSODLULS_macraff_i8;
  int8_t TSODLULS_macraff_i8_2;
  int8_t TSODLULS_macraff_i8_3;
  int8_t TSODLULS_macraff_i8_4;
  int8_t TSODLULS_macraff_i8_5;
  int8_t TSODLULS_macraff_i8_6;
  size_t TSODLULS_macraff_isize;
  size_t TSODLULS_macraff_isize_2;
  size_t TSODLULS_macraff_isize_3;
  t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element;
*/


//------------------------------------------------------------------------------------
//External macros
//------------------------------------------------------------------------------------
/**
 * Padding functions
 * Check padding parameters and return an error code if needed
 * This macraff requires the following auxiliary variables:
 *   int8_t TSODLULS_macraff_i8;
 *   int8_t TSODLULS_macraff_i8_2;
 *   int8_t TSODLULS_macraff_i8_3;
 *   int8_t TSODLULS_macraff_i8_4;
 *   int8_t TSODLULS_macraff_i8_5;
 *   int8_t TSODLULS_macraff_i8_6;
 */
#define TSODLULS_check_padding_parameters__macraff(\
  i_aff,\
  i_number_of_lex_padding_bytes_before,\
  i_number_of_contrelex_padding_bytes_before,\
  i_number_of_lex_padding_bytes_after,\
  i_number_of_contrelex_padding_bytes_after,\
  i_number_of_contiguous_data_bytes,\
  i_current_offset\
) \
do{\
  TSODLULS_macraff_i8 = (i_number_of_lex_padding_bytes_before);\
  TSODLULS_macraff_i8_2 = (i_number_of_contrelex_padding_bytes_before);\
  TSODLULS_macraff_i8_3 = (i_number_of_lex_padding_bytes_after);\
  TSODLULS_macraff_i8_4 = (i_number_of_contrelex_padding_bytes_after);\
  TSODLULS_macraff_i8_5 = (i_number_of_contiguous_data_bytes);\
  TSODLULS_macraff_i8_6 = (i_current_offset);\
  if(TSODLULS_macraff_i8 == I_HALF_BYTE\
    || TSODLULS_macraff_i8_2 == I_HALF_BYTE\
  ){\
    if(TSODLULS_macraff_i8 != I_HALF_BYTE\
      || TSODLULS_macraff_i8_2 != I_HALF_BYTE\
    ){\
      (i_aff) = I_ERROR__BOTH_LEX_AND_CONTRELEX_PADDING_BYTES_BEFORE_MUST_BE_HALF_BYTES;\
      break;\
    }\
  }\
  else{\
    if(TSODLULS_macraff_i8 < 0){\
      (i_aff) = I_ERROR__NUMBER_OF_LEX_PADDING_BYTES_BEFORE_IS_INVALID;\
      break;\
    }\
    if(TSODLULS_macraff_i8_2 < 0){\
      (i_aff) = I_ERROR__NUMBER_OF_CONTRELEX_PADDING_BYTES_BEFORE_IS_INVALID;\
      break;\
    }\
  }\
  if(TSODLULS_macraff_i8_3 == I_HALF_BYTE\
    || TSODLULS_macraff_i8_4 == I_HALF_BYTE\
  ){\
    if(TSODLULS_macraff_i8_3 != I_HALF_BYTE\
      || TSODLULS_macraff_i8_4 != I_HALF_BYTE\
    ){\
      (i_aff) = I_ERROR__BOTH_LEX_AND_CONTRELEX_PADDING_BYTES_AFTER_MUST_BE_HALF_BYTES;\
      break;\
    }\
  }\
  else{\
    if(TSODLULS_macraff_i8_3 < 0){\
      (i_aff) = I_ERROR__NUMBER_OF_LEX_PADDING_BYTES_AFTER_IS_INVALID;\
      break;\
    }\
    if(TSODLULS_macraff_i8_4 < 0){\
      (i_aff) = I_ERROR__NUMBER_OF_CONTRELEX_PADDING_BYTES_AFTER_IS_INVALID;\
      break;\
    }\
  }\
\
  if(TSODLULS_macraff_i8_5 < 1){\
    (i_aff) = I_ERROR__NUMBER_OF_CONTIGUOUS_DATA_BYTES_MUST_BE_AT_LEAST_1;\
    break;\
  }\
  if(TSODLULS_macraff_i8_6 < 0){\
    (i_aff) = I_ERROR__CURRENT_OFFSET_MUST_BE_AT_LEAST_0;\
    break;\
  }\
  if(TSODLULS_macraff_i8_5 <= TSODLULS_macraff_i8_6){\
    (i_aff) = I_ERROR__CURRENT_OFFSET_MUST_BE_LESS_THAN_THE_NUMBER_OF_CONTIGUOUS_DATA_BYTES;\
    break;\
  }\
  (i_aff) = 0;\
}while(0);



/**
 * Padding functions
 * Compute size needed for the data bytes with padding
 * This macraff requires the following auxiliary variables:
 *   int8_t TSODLULS_macraff_i8;
 *   int8_t TSODLULS_macraff_i8_2;
 *   int8_t TSODLULS_macraff_i8_3;
 *   int8_t TSODLULS_macraff_i8_4;
 *   int8_t TSODLULS_macraff_i8_5;
 *   int8_t TSODLULS_macraff_i8_6;
 *   size_t TSODLULS_macraff_isize;
 *   size_t TSODLULS_macraff_isize_2;
 *   size_t TSODLULS_macraff_isize_3;
 */
#define TSODLULS_compute_size_needed__macraff(\
  isize_aff,\
  i_number_of_data_bytes,\
  i_number_of_lex_padding_bytes_before,\
  i_number_of_contrelex_padding_bytes_before,\
  i_number_of_lex_padding_bytes_after,\
  i_number_of_contrelex_padding_bytes_after,\
  i_number_of_contiguous_data_bytes,\
  i_current_offset\
) \
do{\
  TSODLULS_macraff_isize = (i_number_of_data_bytes);\
  TSODLULS_macraff_i8 = (i_number_of_lex_padding_bytes_before);\
  TSODLULS_macraff_i8_2 = (i_number_of_contrelex_padding_bytes_before);\
  TSODLULS_macraff_i8_3 = (i_number_of_lex_padding_bytes_after);\
  TSODLULS_macraff_i8_4 = (i_number_of_contrelex_padding_bytes_after);\
  TSODLULS_macraff_i8_5 = (i_number_of_contiguous_data_bytes);\
  TSODLULS_macraff_i8_6 = (i_current_offset);\
  TSODLULS_macraff_isize_3 = TSODLULS_macraff_isize;\
  for(TSODLULS_macraff_isize_2 = 0; TSODLULS_macraff_isize_2 < TSODLULS_macraff_isize; ++TSODLULS_macraff_isize_2){\
    if( ((TSODLULS_macraff_i8_6 + TSODLULS_macraff_isize_2) % TSODLULS_macraff_i8_5) == 0){\
      if(TSODLULS_macraff_i8 == I_HALF_BYTE){\
        TSODLULS_macraff_isize_3 += 1;\
      }\
      else{\
        TSODLULS_macraff_isize_3 += TSODLULS_macraff_i8;\
        TSODLULS_macraff_isize_3 += TSODLULS_macraff_i8_2;\
      }\
    }\
    if( ((TSODLULS_macraff_i8_6 + TSODLULS_macraff_isize_2 + 1) % TSODLULS_macraff_i8_5) == 0){\
      if(TSODLULS_macraff_i8_3 == I_HALF_BYTE){\
        TSODLULS_macraff_isize_3 += 1;\
      }\
      else{\
        TSODLULS_macraff_isize_3 += TSODLULS_macraff_i8_3;\
        TSODLULS_macraff_isize_3 += TSODLULS_macraff_i8_4;\
      }\
    }\
  }\
  (isize_aff) = TSODLULS_macraff_isize_3;\
}while(0);



/**
 * Padding functions
 * Padd
 * This macraff requires the following auxiliary variables:
 *   int8_t TSODLULS_macraff_i8;
 *   int8_t TSODLULS_macraff_i8_2;
 *   int8_t TSODLULS_macraff_i8_3;
 *   int8_t TSODLULS_macraff_i8_4;
 *   t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element;
 */
#define TSODLULS_padd__macraff(\
  p_sort_element,\
  i_number_of_lex_padding_bytes,\
  i_number_of_contrelex_padding_bytes,\
  i_current_offset\
) \
do{\
  TSODLULS_macraff_p_sort_element = (p_sort_element);\
  TSODLULS_macraff_i8 = (i_number_of_lex_padding_bytes);\
  TSODLULS_macraff_i8_2 = (i_number_of_contrelex_padding_bytes);\
  TSODLULS_macraff_i8_3 = (i_current_offset);\
  if(TSODLULS_macraff_i8_3 == 0){\
    if(TSODLULS_macraff_i8 == I_HALF_BYTE){\
      TSODLULS_macraff_p_sort_element->s_key[TSODLULS_macraff_p_sort_element->i_key_size++] = 240;\
    }\
    else{\
      for(TSODLULS_macraff_i8_4 = 0; TSODLULS_macraff_i8_4 < TSODLULS_macraff_i8; ++TSODLULS_macraff_i8_4){\
        TSODLULS_macraff_p_sort_element->s_key[TSODLULS_macraff_p_sort_element->i_key_size++] = 255;\
      }\
      for(TSODLULS_macraff_i8_4 = 0; TSODLULS_macraff_i8_4 < TSODLULS_macraff_i8_2; ++TSODLULS_macraff_i8_4){\
        TSODLULS_macraff_p_sort_element->s_key[TSODLULS_macraff_p_sort_element->i_key_size++] = 0;\
      }\
    }\
  }\
}while(0);



/**
 * Padding functions
 * Add a few bits to the current key, managing current bit offset
 * and returning new current bit offset
 * This macraff requires the following auxiliary variables:
 *   uint8_t TSODLULS_macraff_ui8;
 *   uint8_t TSODLULS_macraff_ui8_2;
 *   uint8_t TSODLULS_macraff_ui8_3;
 *   t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element;
 */
#define TSODLULS_add_bits_with_bit_level_offset__macraff(\
  i_offset_aff,\
  p_sort_element,\
  i_data_byte,\
  i_number_of_data_bits,\
  i_current_bit_level_offset\
) \
do{\
  TSODLULS_macraff_p_sort_element = (p_sort_element);\
  TSODLULS_macraff_ui8 = (i_data_byte);\
  TSODLULS_macraff_ui8_2 = (i_number_of_data_bits);\
  TSODLULS_macraff_ui8_3 = (i_current_bit_level_offset);\
  if(TSODLULS_macraff_ui8_3 > 0){\
    TSODLULS_macraff_p_sort_element->s_key[TSODLULS_macraff_p_sort_element->i_key_size - 1] |= TSODLULS_macraff_ui8 >> TSODLULS_macraff_ui8_3;\
    if(TSODLULS_macraff_ui8_3 + TSODLULS_macraff_ui8_2 > 8){\
      TSODLULS_macraff_p_sort_element->s_key[TSODLULS_macraff_p_sort_element->i_key_size++] |= TSODLULS_macraff_ui8 << (8 - TSODLULS_macraff_ui8_3);\
    }\
  }\
  else{\
    TSODLULS_macraff_p_sort_element->s_key[TSODLULS_macraff_p_sort_element->i_key_size++] = TSODLULS_macraff_ui8;\
  }\
  (i_offset_aff) = (i_current_bit_level_offset + i_number_of_data_bits) % 8;\
}while(0);



