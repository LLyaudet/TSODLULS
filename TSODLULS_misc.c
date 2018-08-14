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
 */
void TSODLULS_free_key(t_TSODLULS_sort_element* p_element){
  if(p_element->s_key != NULL){
    free(p_element->s_key);
    p_element->s_key = NULL;
    p_element->i_key_size = 0;
    p_element->i_allocated_size = 0;
  }
}//end function TSODLULS_free_key()



/**
 * Miscellaneous functions
 * Initialize an array of TSODLULS elements
 */
int TSODLULS_init_array_of_elements(t_TSODLULS_sort_element** p_arr_elements, size_t i_number_of_elements){
  *p_arr_elements =  calloc(i_number_of_elements, sizeof(t_TSODLULS_sort_element));
  if(*p_arr_elements == NULL){
    return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
  }
  for(size_t i = 0; i < i_number_of_elements; ++i){
    TSODLULS_init_element(&((*p_arr_elements)[i]));
  }
  return 0;
}//end function TSODLULS_init_array_of_elements()



/**
 * Miscellaneous functions
 * Free the keys of all TSODLULS elements in an array
 */
void TSODLULS_free_keys_in_array_of_elements(t_TSODLULS_sort_element* arr_elements, size_t i_number_of_elements){
  for(size_t i = 0; i < i_number_of_elements; ++i){
    TSODLULS_free_key(&(arr_elements[i]));
  }
}//end function TSODLULS_free_keys_in_array_of_elements()



