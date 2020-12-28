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
This file contains general remarks about the functional macros in this library
and includes the files defining them.
Most of the functions available in this library are available as as "macraff",
i.e. a macro with affectation.
If you have a function
  int foo(type1 param1, type2 param2);
,
the corresponding macraff is
  foo__macraff(int paramAff, type1 param1, type2 param2)
Macraffs use auxiliary variables that you need to declare in the calling function.
If it is possible to code the macro without computing twice the parameters
and returning the correct value, then the macro is available as a simple macro.

Examples:
int foo(int i){
  return i << 1;
}
will become a macro
#define foo__macro(i) \
  ((i) << 1)

but 

int foo(int i, int j){
  return (i < j ? i : j);
}
will become a macraff
#define foo__macraff(k, i, j) \
  TSODLULS_macraff_i = (i);\
  TSODLULS_macraff_j = (j);\
  (k) = (TSODLULS_macraff_i < TSODLULS_macraff_j ? TSODLULS_macraff_i : TSODLULS_macraff_j);\

The comment before a function tells if it is available as a macro or as a macraff.
If the return type is void but auxiliary variables need to be declared,
 we still classify the macro with the macraffs, because of the affectations of the parameters.
*/

//#include "TSODLULS_comparison__macro.h"
#include "TSODLULS_finite_orders__macro.h"
#include "TSODLULS_misc__macro.h"
#include "TSODLULS_padding__macro.h"
//#include "TSODLULS_sorting_long_orders__macro.h"
//#include "TSODLULS_sorting_short_orders__macro.h"

/*
The macraffs in this library use the following auxiliary variables:
  union ieee754_float TSODLULS_macraff_ieee754_float;
  union ieee754_double TSODLULS_macraff_ieee754_double;
  uint8_t TSODLULS_macraff_ui8;
  uint8_t TSODLULS_macraff_ui8_2;
  uint8_t TSODLULS_macraff_ui8_3;
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
  t_TSODLULS_sort_element* TSODLULS_macraff_arr_elements;
  t_TSODLULS_sort_element** TSODLULS_macraff_p_arr_elements;
  t_TSODLULS_sort_element__short* TSODLULS_macraff_p_sort_element__short;
  t_TSODLULS_sort_element__short** TSODLULS_macraff_p_arr_elements__short;
  void* TSODLULS_macraff_p_void;
*/

#define TSODLULS_free(pointer) \
  free(pointer);\
  (pointer) = NULL;

#define TSODLULS_min_exp(x, y) ((x) < (y) ? (x) : (y))


