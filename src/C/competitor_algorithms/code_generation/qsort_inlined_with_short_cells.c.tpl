/*
This file is part of TSODLULS.

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

Most of the code here is from glibc:
  Written by Douglas C. Schmidt (schmidt@ics.uci.edu).
  Copyright (C) 1991-2018 Free Software Foundation, Inc.

Modifications in this library:
©Copyright 2018-2020 Laurent Lyaudet
*/
/*
If you want to understand this template, please look first at stdlib/qsort.c in glibc library
(the code below was partly copy-pasted from version 2.27 of glibc).
This template uses the following template variable:
  @iNumberOfElementsForInsertionSort@
It corresponds to the C constant MAX_THRESH in glibc.
*/
BEGIN_TPL
/**
 * Sorting functions for short nextified strings
 * Qsort from glibc inlined with short cells.
 */
int TSODLULS_qsort_inlined__short_@iNumberOfElementsForInsertionSort@(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements
){
  #define TSODLULS_MAX_THRESH @iNumberOfElementsForInsertionSort@
  #include "./b/body_TSODLULS_qsort_inlined__short.c"
  #undef TSODLULS_MAX_THRESH
}//end function TSODLULS_qsort_inlined__short_@iNumberOfElementsForInsertionSort@



END_TPL

