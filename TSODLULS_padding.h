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



