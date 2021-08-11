<?php
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

©Copyright 2018-2021 Laurent Lyaudet
*/

$arrSwapVarParameter = array(
  'macro' => 'TSODLULS_SWAP_VAR',
  'macro_args' => 3,
  'type' => 'enum',
  'values' => array(
    array('index' => 0, 'value_for_macro_def' => 'TSODLULS_SWAP_VAR_1', 'value_for_function_name' => '1'),
    array('index' => 1, 'value_for_macro_def' => 'TSODLULS_SWAP_VAR_2', 'value_for_function_name' => '2',
          'macraff_variables' => array(
            'size_t TSODLULS_macraff_isize;',
            'char* TSODLULS_macraff_p_char;',
            'char* TSODLULS_macraff_p_char_2;',
            'char TSODLULS_macraff_char;',
          ),
    ),
    array('index' => 2, 'value_for_macro_def' => 'TSODLULS_SWAP_VAR_3', 'value_for_function_name' => '3'),
    array('index' => 3, 'value_for_macro_def' => 'TSODLULS_SWAP_VAR_4', 'value_for_function_name' => '4',
          'macraff_variables' => array(
            'char* TSODLULS_macraff_p_char;',
            'char* TSODLULS_macraff_p_char_2;',
            'char* TSODLULS_macraff_p_char_3;',
            'char TSODLULS_macraff_char;',
          ),
    ),
    array('index' => 4, 'value_for_macro_def' => 'TSODLULS_SWAP_VAR_5', 'value_for_function_name' => '5',
          'macraff_variables' => array(
            'size_t TSODLULS_macraff_i_chunk_size = TSODLULS_CHUNK_SIZE_FOR_SWAP_VAR(i_element_size);',
          ),
    ),
    array('index' => 5, 'value_for_macro_def' => 'TSODLULS_SWAP_VAR_6', 'value_for_function_name' => '6',
          'macraff_variables' => array(
            'size_t TSODLULS_macraff_i_chunk_size = TSODLULS_CHUNK_SIZE_FOR_SWAP_VAR(i_element_size);',
            'size_t TSODLULS_macraff_isize;',
            't_TSODLULS_sizables_union TSODLULS_macraff_sizables_union;',
            't_TSODLULS_sizables_pointers_union TSODLULS_macraff_sizables_pointers_union_1;',
            't_TSODLULS_sizables_pointers_union TSODLULS_macraff_sizables_pointers_union_2;',
          ),
    ),
  ),
);


$arrArrCompetitorsListByFile = array(
  'TSODLULS_sorting_comparison_callback__competitor__generated' => array(
    'header_head' => '',
    'header_tail' => '',
    'code_head' => "#include \"TSODLULS__competitor.h\"\n\n\n\n",
    'code_tail' => "",
    'functions_section_header' => " * Sorting functions using a comparison callback for arbitrary data structures.\n",
    'functions' => array(
      array(
        'function' => 'TSODLULS_qsort__comparison_callback',
        'celltype' => 'direct',
        'size' => 'cell',
        'comparison' => 'direct',
        'stable' => false,
        'return_type' => 'int',
        'function_comment' => " * Qsort from glibc with minor modifications.\n",
        'parameters' => array(
          array('macro' => 'TSODLULS_MAX_THRESH', 'type' => 'integer_range', 'min_value' => 1, 'max_value' => 16, 'default' => 4,),
          $arrSwapVarParameter,
        ),
      ),
    ),
  ),
  'TSODLULS_sorting_long_orders__competitor__generated' => array(
    'header_head' => '',
    'header_tail' => '',
    'code_head' => "#include \"TSODLULS__competitor.h\"\n\n\n\n",
    'code_tail' => "",
    'functions_section_header' => " * Sorting functions for long nextified strings\n",
    'functions' => array(
      array(
        'function' => 'TSODLULS_qsort_inlined__long',
        'celltype' => 'long',
        'size' => false,
        'comparison' => false,
        'stable' => false,
        'return_type' => 'int',
        'function_comment' => " * Qsort from glibc inlined with long cells.\n",
        'parameters' => array(
          array('macro' => 'TSODLULS_MAX_THRESH', 'type' => 'integer_range', 'min_value' => 1, 'max_value' => 16, 'default' => 4,),
        ),
      ),
      array(
        'function' => 'TSODLULS_sort_radix8_count_insertion__mark1',
        'celltype' => 'long',
        'size' => false,
        'comparison' => false,
        'stable' => true,
        'return_type' => 'int',
        'function_comment' => (
          " * A stable sorting algorithm for nextified strings based on radix sort with octets digits\n"
         ." * and counting sort as a subroutine.\n"
         ." * When the number of elements to sort is at most TSODLULS_MAX_THRESH (5 for example), we use insertion sort.\n"
        ),
        'parameters' => array(
          array('macro' => 'TSODLULS_MAX_THRESH', 'type' => 'integer_range', 'min_value' => 1, 'max_value' => 16, 'default' => 5,),
        ),
      ),
      array(
        'function' => 'TSODLULS_sort_radix8_count_insertion__mark2',
        'celltype' => 'long',
        'size' => false,
        'comparison' => false,
        'stable' => true,
        'return_type' => 'int',
        'function_comment' => (
          " * A stable sorting algorithm for nextified strings based on radix sort with octets digits\n"
         ." * and counting sort as a subroutine.\n"
         ." * When the number of elements to sort is at most:\n"
         ." *   - TSODLULS_MAX_THRESH (5 for example),\n"
         ." *   - or TSODLULS_MAX_THRESH_SEQUEL (2 for example) for radix sequel,\n"
         ." * we use insertion sort.\n"
        ),
        'parameters' => array(
          array('macro' => 'TSODLULS_MAX_THRESH', 'type' => 'integer_range', 'min_value' => 1, 'max_value' => 16, 'default' => 5,),
          array('macro' => 'TSODLULS_MAX_THRESH_SEQUEL', 'type' => 'integer_range', 'min_value' => 1, 'max_value' => 16, 'default' => 2,),
        ),
      ),
      array(
        'function' => 'TSODLULS_sort_radix8_count_insertion__mark3',
        'celltype' => 'long',
        'size' => false,
        'comparison' => false,
        'stable' => true,
        'return_type' => 'int',
        'function_comment' => (
          " * A stable sorting algorithm for nextified strings based on radix sort with octets digits\n"
         ." * and counting sort as a subroutine.\n"
         ." * When the number of elements to sort is at most:\n"
         ." *   - TSODLULS_MAX_THRESH (5 for example),\n"
         ." *   - or TSODLULS_MAX_THRESH_SEQUEL (2 for example) for radix sequel,\n"
         ." * we use insertion sort.\n"
         ." * No data move if the array is already sorted (code variant).\n"
        ),
        'parameters' => array(
          array('macro' => 'TSODLULS_MAX_THRESH', 'type' => 'integer_range', 'min_value' => 1, 'max_value' => 16, 'default' => 5,),
          array('macro' => 'TSODLULS_MAX_THRESH_SEQUEL', 'type' => 'integer_range', 'min_value' => 1, 'max_value' => 16, 'default' => 2,),
        ),
      ),
      array(
        'function' => 'TSODLULS_sort_radix8_count_insertion__mark4',
        'celltype' => 'long',
        'size' => false,
        'comparison' => false,
        'stable' => true,
        'return_type' => 'int',
        'function_comment' => (
          " * A stable sorting algorithm for nextified strings based on radix sort with octets digits\n"
         ." * and counting sort as a subroutine.\n"
         ." * When the number of elements to sort is at most:\n"
         ." *   - TSODLULS_MAX_THRESH (5 for example),\n"
         ." *   - or TSODLULS_MAX_THRESH_SEQUEL (2 for example) for radix sequel,\n"
         ." * we use insertion sort.\n"
         ." * No data move if the array is already sorted (code variant, double loop).\n"
        ),
        'parameters' => array(
          array('macro' => 'TSODLULS_MAX_THRESH', 'type' => 'integer_range', 'min_value' => 1, 'max_value' => 16, 'default' => 5,),
          array('macro' => 'TSODLULS_MAX_THRESH_SEQUEL', 'type' => 'integer_range', 'min_value' => 1, 'max_value' => 16, 'default' => 2,),
        ),
      ),
    ),
  ),
  'TSODLULS_sorting_short_orders__competitor__generated' => array(
    'header_head' => '',
    'header_tail' => '',
    'code_head' => "#include \"TSODLULS__competitor.h\"\n\n\n\n",
    'code_tail' => "",
    'functions_section_header' => " * Sorting functions for short nextified strings\n",
    'functions' => array(
      array(
        'function' => 'TSODLULS_qsort_inlined__short',
        'celltype' => 'short',
        'size' => false,
        'comparison' => false,
        'stable' => false,
        'return_type' => 'int',
        'function_comment' => " * Qsort from glibc inlined with short cells.\n",
        'parameters' => array(
          array('macro' => 'TSODLULS_MAX_THRESH', 'type' => 'integer_range', 'min_value' => 1, 'max_value' => 16, 'default' => 4,),
        ),
      ),
    ),
  ),
);

?>
