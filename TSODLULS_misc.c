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
 * Miscellaneous functions
 * Initialize a TSODLULS element
 * Available as a macraff (see TSODLULS_misc__macro.h).
 */
void TSODLULS_init_element(t_TSODLULS_sort_element* p_element){
  p_element->p_object = NULL;
  p_element->s_key = NULL;
  p_element->i_key_size = 0;
  p_element->i_allocated_size = 0;
}//end function TSODLULS_init_element()



/**
 * Miscellaneous functions
 * Free the key of a TSODLULS element (if necessary) and reinitializes the corresponding fields
 * Available as a macraff (see TSODLULS_misc__macro.h).
 */
void TSODLULS_free_key(t_TSODLULS_sort_element* p_element){
  if(p_element->s_key != NULL){
    TSODLULS_free(p_element->s_key);
    p_element->i_key_size = 0;
    p_element->i_allocated_size = 0;
  }
}//end function TSODLULS_free_key()



/**
 * Miscellaneous functions
 * Initialize an array of TSODLULS elements
 * Available as a macraff (see TSODLULS_misc__macro.h).
 */
int TSODLULS_init_array_of_elements(
  t_TSODLULS_sort_element** p_arr_elements,
  size_t i_number_of_elements
){
  t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element;
  *p_arr_elements = calloc(i_number_of_elements, sizeof(t_TSODLULS_sort_element));
  if(*p_arr_elements == NULL){
    return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
  }
  for(size_t i = 0; i < i_number_of_elements; ++i){
    TSODLULS_init_element__macraff(&((*p_arr_elements)[i]));
  }
  return 0;
}//end function TSODLULS_init_array_of_elements()



/**
 * Miscellaneous functions
 * Free the keys of all TSODLULS elements in an array
 * Available as a macraff (see TSODLULS_misc__macro.h).
 */
void TSODLULS_free_keys_in_array_of_elements(
  t_TSODLULS_sort_element* arr_elements,
  size_t i_number_of_elements
){
  t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element;
  for(size_t i = 0; i < i_number_of_elements; ++i){
    TSODLULS_free_key__macraff(&(arr_elements[i]));
  }
}//end function TSODLULS_free_keys_in_array_of_elements()



/**
 * Miscellaneous functions
 * (Re)Allocate space for the key of a TSODLULS element
 * Available as a macraff (see TSODLULS_misc__macro.h).
 */
int TSODLULS_element_allocate_space_for_key(
  t_TSODLULS_sort_element* p_sort_element,
  size_t i_size_needed
){
  size_t i_number_of_elements_for_realloc = 0;
  void* p_for_realloc = NULL;

  if(p_sort_element->i_allocated_size == 0){
    p_sort_element->s_key = calloc(i_size_needed, sizeof(uint8_t));
    if(p_sort_element ==  NULL){
      return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
    }
    p_sort_element->i_allocated_size = i_size_needed;
    return 0;
  }
  if(p_sort_element->i_allocated_size - p_sort_element->i_key_size >= i_size_needed){
    return 0;
  }

  i_number_of_elements_for_realloc = p_sort_element->i_allocated_size;
  do{
    i_number_of_elements_for_realloc = i_number_of_elements_for_realloc << 1;
    if(i_number_of_elements_for_realloc <= p_sort_element->i_allocated_size){
      return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
    }
  }
  while(i_number_of_elements_for_realloc - p_sort_element->i_key_size < i_size_needed);

  if(i_number_of_elements_for_realloc * sizeof(uint8_t) <= i_number_of_elements_for_realloc){
    return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
  }

  p_for_realloc = realloc(
      p_sort_element->s_key,
      i_number_of_elements_for_realloc * sizeof(uint8_t)
  );
  if(p_for_realloc == NULL){
    return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
  }
  p_sort_element->s_key = (uint8_t*) p_for_realloc;
  p_sort_element->i_allocated_size = i_number_of_elements_for_realloc;
  return 0;
}//end function TSODLULS_element_allocate_space_for_key()



/**
 * Miscellaneous functions
 * Initialize a TSODLULS element for short orders
 * Available as a macraff (see TSODLULS_misc__macro.h).
 */
void TSODLULS_init_element__short(t_TSODLULS_sort_element__short* p_element){
  p_element->p_object = NULL;
  p_element->i_key = 0;
}//end function TSODLULS_init_element__short()



/**
 * Miscellaneous functions
 * Initialize an array of TSODLULS elements for short orders
 * Available as a macraff (see TSODLULS_misc__macro.h).
 */
int TSODLULS_init_array_of_elements__short(
  t_TSODLULS_sort_element__short** p_arr_elements,
  size_t i_number_of_elements
){
  t_TSODLULS_sort_element__short* TSODLULS_macraff_p_sort_element__short;
  *p_arr_elements = calloc(i_number_of_elements, sizeof(t_TSODLULS_sort_element__short));
  if(*p_arr_elements == NULL){
    return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
  }
  for(size_t i = 0; i < i_number_of_elements; ++i){
    TSODLULS_init_element__short__macraff(&((*p_arr_elements)[i]));
  }
  return 0;
}//end function TSODLULS_init_array_of_elements()



