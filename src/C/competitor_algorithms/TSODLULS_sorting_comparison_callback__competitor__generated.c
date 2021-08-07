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

//This file was generated by generateCompetitors.php script.



#include "TSODLULS__competitor.h"

#define TSODLULS_STACK_SIZE  (CHAR_BIT * sizeof(size_t))
#define TSODLULS_PUSH(low, high)  ((void) ((top->p_low = (low)), (top->p_high = (high)), ++top))
#define TSODLULS_POP(low, high)  ((void) (--top, (low = top->p_low), (high = top->p_high)))
#define TSODLULS_STACK_NOT_EMPTY  (stack < top)



/**
 * Sorting functions using a comparison callback for arbitrary data structures.
 * Qsort from glibc with minor modifications.
 */
int TSODLULS_qsort__comparison_callback_3(
  void* arr_elements,
  size_t i_number_of_elements,
  size_t i_element_size,
  t_comparison_function fn_comparison
){
  #define TSODLULS_MAX_THRESH 3
  #include "./b/body_TSODLULS_qsort__comparison_callback.c"
  #undef TSODLULS_MAX_THRESH
}//end function TSODLULS_qsort__comparison_callback_3()



/**
 * Sorting functions using a comparison callback for arbitrary data structures.
 * Qsort from glibc with minor modifications.
 */
int TSODLULS_qsort__comparison_callback_4(
  void* arr_elements,
  size_t i_number_of_elements,
  size_t i_element_size,
  t_comparison_function fn_comparison
){
  #define TSODLULS_MAX_THRESH 4
  #include "./b/body_TSODLULS_qsort__comparison_callback.c"
  #undef TSODLULS_MAX_THRESH
}//end function TSODLULS_qsort__comparison_callback_4()



/**
 * Sorting functions using a comparison callback for arbitrary data structures.
 * Qsort from glibc with minor modifications.
 */
int TSODLULS_qsort__comparison_callback_5(
  void* arr_elements,
  size_t i_number_of_elements,
  size_t i_element_size,
  t_comparison_function fn_comparison
){
  #define TSODLULS_MAX_THRESH 5
  #include "./b/body_TSODLULS_qsort__comparison_callback.c"
  #undef TSODLULS_MAX_THRESH
}//end function TSODLULS_qsort__comparison_callback_5()



/**
 * Sorting functions using a comparison callback for arbitrary data structures.
 * Qsort from glibc with minor modifications.
 */
int TSODLULS_qsort__comparison_callback_6(
  void* arr_elements,
  size_t i_number_of_elements,
  size_t i_element_size,
  t_comparison_function fn_comparison
){
  #define TSODLULS_MAX_THRESH 6
  #include "./b/body_TSODLULS_qsort__comparison_callback.c"
  #undef TSODLULS_MAX_THRESH
}//end function TSODLULS_qsort__comparison_callback_6()



/**
 * Sorting functions using a comparison callback for arbitrary data structures.
 * Qsort from glibc with minor modifications.
 */
int TSODLULS_qsort__comparison_callback_7(
  void* arr_elements,
  size_t i_number_of_elements,
  size_t i_element_size,
  t_comparison_function fn_comparison
){
  #define TSODLULS_MAX_THRESH 7
  #include "./b/body_TSODLULS_qsort__comparison_callback.c"
  #undef TSODLULS_MAX_THRESH
}//end function TSODLULS_qsort__comparison_callback_7()



/**
 * Sorting functions using a comparison callback for arbitrary data structures.
 * Qsort from glibc with minor modifications.
 */
int TSODLULS_qsort__comparison_callback_8(
  void* arr_elements,
  size_t i_number_of_elements,
  size_t i_element_size,
  t_comparison_function fn_comparison
){
  #define TSODLULS_MAX_THRESH 8
  #include "./b/body_TSODLULS_qsort__comparison_callback.c"
  #undef TSODLULS_MAX_THRESH
}//end function TSODLULS_qsort__comparison_callback_8()




#undef TSODLULS_STACK_SIZE
#undef TSODLULS_PUSH
#undef TSODLULS_POP
#undef TSODLULS_STACK_NOT_EMPTY
