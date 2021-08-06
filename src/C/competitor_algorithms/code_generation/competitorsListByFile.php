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

$arrArrCompetitorsListByFile = array(
  'TSODLULS_sorting_comparison_callback__competitor__generated' => array(
    'header_head' => '',
    'header_tail' => '',
    'code_head' => "#include \"TSODLULS__competitor.h\"\n\n"
                  ."#define TSODLULS_STACK_SIZE  (CHAR_BIT * sizeof(size_t))\n"
                  ."#define TSODLULS_PUSH(low, high)  ((void) ((top->p_low = (low)), (top->p_high = (high)), ++top))\n"
                  ."#define TSODLULS_POP(low, high)  ((void) (--top, (low = top->p_low), (high = top->p_high)))\n"
                  ."#define TSODLULS_STACK_NOT_EMPTY  (stack < top)\n\n\n\n",
    'code_tail' => "\n"
                  ."#undef TSODLULS_STACK_SIZE\n"
                  ."#undef TSODLULS_PUSH\n"
                  ."#undef TSODLULS_POP\n"
                  ."#undef TSODLULS_STACK_NOT_EMPTY\n\n",
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
          array('macro' => 'TSODLULS_MAX_THRESH', 'type' => 'integer_range', 'min_value' => 3, 'max_value' => 8,),
        ),
      ),
    ),
  ),
  'TSODLULS_sorting_long_orders__competitor__generated' => array(
    'header_head' => '',
    'header_tail' => '',
    'code_head' => "#include \"TSODLULS__competitor.h\"\n\n"
                  ."#define TSODLULS_STACK_SIZE  (CHAR_BIT * sizeof(size_t))\n"
                  ."#define TSODLULS_PUSH(low, high)  ((void) ((top->p_low = (low)), (top->p_high = (high)), ++top))\n"
                  ."#define TSODLULS_POP(low, high)  ((void) (--top, (low = top->p_low), (high = top->p_high)))\n"
                  ."#define TSODLULS_STACK_NOT_EMPTY  (stack < top)\n\n\n\n",
    'code_tail' => "\n"
                  ."#undef TSODLULS_STACK_SIZE\n"
                  ."#undef TSODLULS_PUSH\n"
                  ."#undef TSODLULS_POP\n"
                  ."#undef TSODLULS_STACK_NOT_EMPTY\n\n",
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
          array('macro' => 'TSODLULS_MAX_THRESH', 'type' => 'integer_range', 'min_value' => 3, 'max_value' => 8,),
        ),
      ),
    ),
  ),
  'TSODLULS_sorting_short_orders__competitor__generated' => array(
    'header_head' => '',
    'header_tail' => '',
    'code_head' => "#include \"TSODLULS__competitor.h\"\n\n"
                  ."#define TSODLULS_STACK_SIZE  (CHAR_BIT * sizeof(size_t))\n"
                  ."#define TSODLULS_PUSH(low, high)  ((void) ((top->p_low = (low)), (top->p_high = (high)), ++top))\n"
                  ."#define TSODLULS_POP(low, high)  ((void) (--top, (low = top->p_low), (high = top->p_high)))\n"
                  ."#define TSODLULS_STACK_NOT_EMPTY  (stack < top)\n\n\n\n",
    'code_tail' => "\n"
                  ."#undef TSODLULS_STACK_SIZE\n"
                  ."#undef TSODLULS_PUSH\n"
                  ."#undef TSODLULS_POP\n"
                  ."#undef TSODLULS_STACK_NOT_EMPTY\n\n",
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
          array('macro' => 'TSODLULS_MAX_THRESH', 'type' => 'integer_range', 'min_value' => 3, 'max_value' => 8,),
        ),
      ),
    ),
  ),
);

?>
