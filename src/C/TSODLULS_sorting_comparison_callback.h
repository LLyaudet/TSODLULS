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

//------------------------------------------------------------------------------------
//Sorting orders with comparison callback
//------------------------------------------------------------------------------------
/**
 * Sorting functions using a comparison callback for arbitrary data structures.
 * The current state of the art sorting function using comparison callback.
 * Its implementation may change without warning.
 */
int TSODLULS_sort__comparison_callback(
  void* arr_elements,
  size_t i_number_of_elements,
  size_t i_element_size,
  t_comparison_function fn_comparison
);



/**
 * Sorting functions using a comparison callback for arbitrary data structures.
 * The current state of the art stable sorting function using comparison callback.
 * Its implementation may change without warning.
 */
int TSODLULS_sort_stable__comparison_callback(
  void* arr_elements,
  size_t i_number_of_elements,
  size_t i_element_size,
  t_comparison_function fn_comparison
);



/**
 * Sorting functions using a comparison callback for arbitrary data structures.
 * The current state of the art logspace sorting function using comparison callback.
 * Its implementation may change without warning.
 */
int TSODLULS_sort_logspace__comparison_callback(
  void* arr_elements,
  size_t i_number_of_elements,
  size_t i_element_size,
  t_comparison_function fn_comparison
);



/**
 * Sorting functions using a comparison callback for arbitrary data structures.
 * The current state of the art stable logspace sorting function using comparison callback.
 * Its implementation may change without warning.
 */
int TSODLULS_sort_stable_logspace__comparison_callback(
  void* arr_elements,
  size_t i_number_of_elements,
  size_t i_element_size,
  t_comparison_function fn_comparison
);



#define TSODLULS_COMPARE_CALL_SIMPLE(a, b) ((*fn_comparison) ((void *) a, (void *) b))
#define TSODLULS_COMPARE_CALL_REENTRANT(a, b) ((*fn_comparison) ((void *) a, (void *) b, context))

#define TSODLULS_COMPARE_TYPE_SIMPLE t_comparison_function
#define TSODLULS_COMPARE_TYPE_REENTRANT t_reentrant_comparison_function

#define TSODLULS_COMPARE_TIM_SORT_MERGE_STATE_SIMPLE t_TSODLULS_Tim_sort_merge_state__comparison_callback
#define TSODLULS_COMPARE_TIM_SORT_MERGE_STATE_REENTRANT t_TSODLULS_Tim_sort_merge_state__reentrant_comparison_callback



