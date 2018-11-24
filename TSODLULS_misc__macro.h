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
/*
This file contains macraffs corresponding to the functions in TSODLULS_misc.c.
It is more pleasant to look at the source code there than to read the macros and macraffs here.
The macraffs in this file use the following auxiliary variables:
  t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element;
  t_TSODLULS_sort_element* TSODLULS_macraff_arr_elements;
  t_TSODLULS_sort_element** TSODLULS_macraff_p_arr_elements;
  size_t TSODLULS_macraff_isize;
  size_t TSODLULS_macraff_isize_2;
  void* TSODLULS_macraff_p_void;
*/



//------------------------------------------------------------------------------------
//External macros
//------------------------------------------------------------------------------------
/**
 * Miscellaneous functions
 * Initialize a TSODLULS element
 * This macraff requires the following auxiliary variable:
 *   t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element;
 */
#define TSODLULS_init_element__macraff(p_element) \
do{\
  TSODLULS_macraff_p_sort_element = (p_element);\
  TSODLULS_macraff_p_sort_element->p_object = NULL;\
  TSODLULS_macraff_p_sort_element->s_key = NULL;\
  TSODLULS_macraff_p_sort_element->i_key_size = 0;\
  TSODLULS_macraff_p_sort_element->i_allocated_size = 0;\
}while(0);



/**
 * Miscellaneous functions
 * Free the key of a TSODLULS element (if necessary) and reinitializes the corresponding fields
 * This macraff requires the following auxiliary variable:
 *   t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element;
 */
#define TSODLULS_free_key__macraff(p_element) \
do{\
  TSODLULS_macraff_p_sort_element = (p_element);\
  if(TSODLULS_macraff_p_sort_element->s_key != NULL){\
    free(TSODLULS_macraff_p_sort_element->s_key);\
    TSODLULS_macraff_p_sort_element->s_key = NULL;\
    TSODLULS_macraff_p_sort_element->i_key_size = 0;\
    TSODLULS_macraff_p_sort_element->i_allocated_size = 0;\
  }\
}while(0);



/**
 * Miscellaneous functions
 * Initialize an array of TSODLULS elements
 * This macraff requires the following auxiliary variables:
 *   t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element;
 *   t_TSODLULS_sort_element** TSODLULS_macraff_p_arr_elements;
 *   size_t TSODLULS_macraff_isize;
 *   size_t TSODLULS_macraff_isize_2;
 */
#define TSODLULS_init_array_of_elements__macraff(\
  i_aff,\
  p_arr_elements,\
  i_number_of_elements\
) \
do{\
  TSODLULS_macraff_p_arr_elements = (p_arr_elements);\
  TSODLULS_macraff_isize = (i_number_of_elements);\
  *TSODLULS_macraff_p_arr_elements = calloc(TSODLULS_macraff_isize, sizeof(t_TSODLULS_sort_element));\
  if(*TSODLULS_macraff_p_arr_elements == NULL){\
    (i_aff) = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;\
    break;\
  }\
  for(TSODLULS_macraff_isize_2 = 0; TSODLULS_macraff_isize_2 < TSODLULS_macraff_isize; ++TSODLULS_macraff_isize_2){\
    TSODLULS_init_element__macraff(&((*TSODLULS_macraff_p_arr_elements)[TSODLULS_macraff_isize_2]));\
  }\
  (i_aff) = 0;\
}while(0);



/**
 * Miscellaneous functions
 * Free the keys of all TSODLULS elements in an array
 * This macraff requires the following auxiliary variables:
 *   t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element;
 *   t_TSODLULS_sort_element* TSODLULS_macraff_arr_elements;
 *   size_t TSODLULS_macraff_isize;
 *   size_t TSODLULS_macraff_isize_2;
 */
#define TSODLULS_free_keys_in_array_of_elements__macraff(\
  arr_elements,\
  i_number_of_elements\
) \
do{\
  TSODLULS_macraff_arr_elements = (arr_elements);\
  TSODLULS_macraff_isize = (i_number_of_elements);\
  for(TSODLULS_macraff_isize_2 = 0; TSODLULS_macraff_isize_2 < TSODLULS_macraff_isize; ++TSODLULS_macraff_isize_2){\
    TSODLULS_free_key__macraff(&(TSODLULS_macraff_arr_elements[TSODLULS_macraff_isize_2]));\
  }\
}while(0);



/**
 * Miscellaneous functions
 * (Re)Allocate space for the key of a TSODLULS element
 * This macraff requires the following auxiliary variables:
 *   t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element;
 *   size_t TSODLULS_macraff_isize;
 *   size_t TSODLULS_macraff_isize_2;
 *   void* TSODLULS_macraff_p_void;
 */
#define TSODLULS_element_allocate_space_for_key__macraff(\
  i_aff,\
  p_sort_element,\
  i_size_needed\
) \
do{\
  TSODLULS_macraff_p_sort_element = (p_sort_element);\
  TSODLULS_macraff_isize = (i_size_needed);\
  TSODLULS_macraff_isize_2 = 0;\
  TSODLULS_macraff_p_void = NULL;\
\
  if(TSODLULS_macraff_p_sort_element->i_allocated_size == 0){\
    TSODLULS_macraff_p_sort_element->s_key = calloc(TSODLULS_macraff_isize, sizeof(uint8_t));\
    if(TSODLULS_macraff_p_sort_element ==  NULL){\
      (i_aff) = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;\
      break;\
    }\
    TSODLULS_macraff_p_sort_element->i_allocated_size = TSODLULS_macraff_isize;\
    (i_aff) = 0;\
    break;\
  }\
  if(TSODLULS_macraff_p_sort_element->i_allocated_size - TSODLULS_macraff_p_sort_element->i_key_size >= TSODLULS_macraff_isize){\
    (i_aff) = 0;\
    break;\
  }\
\
  TSODLULS_macraff_isize_2 = TSODLULS_macraff_p_sort_element->i_allocated_size;\
  do{\
    TSODLULS_macraff_isize_2 = TSODLULS_macraff_isize_2 << 1;\
    if(TSODLULS_macraff_isize_2 <= TSODLULS_macraff_p_sort_element->i_allocated_size){\
      (i_aff) = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;\
      break;\
    }\
  }\
  while(TSODLULS_macraff_isize_2 - TSODLULS_macraff_p_sort_element->i_key_size < TSODLULS_macraff_isize);\
\
  if(TSODLULS_macraff_isize_2 * sizeof(uint8_t) <= TSODLULS_macraff_isize_2){\
    (i_aff) = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;\
    break;\
  }\
\
  TSODLULS_macraff_p_void = realloc(\
      TSODLULS_macraff_p_sort_element->s_key,\
      TSODLULS_macraff_isize_2 * sizeof(uint8_t)\
  );\
  if(TSODLULS_macraff_p_void == NULL){\
    (i_aff) = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;\
    break;\
  }\
  TSODLULS_macraff_p_sort_element->s_key = (uint8_t*) TSODLULS_macraff_p_void;\
  TSODLULS_macraff_p_sort_element->i_allocated_size = TSODLULS_macraff_isize_2;\
  (i_aff) = 0;\
}while(0);



