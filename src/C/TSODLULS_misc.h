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

©Copyright 2018-2023 Laurent Lyaudet
*/

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



