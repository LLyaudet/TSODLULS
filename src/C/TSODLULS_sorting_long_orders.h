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
//Sorting long orders
//------------------------------------------------------------------------------------
/**
 * Sorting functions for long nextified strings
 * The current state of the art sorting function for nextified strings.
 * Its implementation may change without warning.
 */
int TSODLULS_sort(t_TSODLULS_sort_element* arr_elements, size_t i_number_of_elements);



/**
 * Sorting functions for long nextified strings
 * The current state of the art stable sorting function for nextified strings.
 * Its implementation may change without warning.
 */
int TSODLULS_sort_stable(t_TSODLULS_sort_element* arr_elements, size_t i_number_of_elements);



