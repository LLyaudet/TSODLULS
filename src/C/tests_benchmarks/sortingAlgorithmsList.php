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
//This file is used with custom tests and benchmarks

$arrArrSortingAlgorithms = array(
  'qsort direct' => array(
    'name' => 'qsort direct',
    'function' => 'qsort',
    'celltype' => 'direct',//When celltype is not direct, macraffs are available
    'size' => 'cell',
    'comparison' => 'direct',//When activated, comparison matches the celltype
    'stable' => false,
  ),
  'qsort long cells' => array(
    'name' => 'qsort long cells',
    'function' => 'qsort',
    'celltype' => 'long',
    'size' => 'cell',
    'comparison' => 'long',
    'stable' => false,
  ),
  'qsort short cells' => array(
    'name' => 'qsort short cells',
    'function' => 'qsort',
    'celltype' => 'short',
    'size' => 'cell',
    'comparison' => 'short',
    'stable' => false,
  ),
  'TSODLULS sort long cells' => array(
    'name' => 'TSODLULS sort long cells',
    'function' => 'TSODLULS_sort',
    'celltype' => 'long',
    'size' => false,
    'comparison' => false,
    'stable' => false,
  ),
  'TSODLULS sort short cells' => array(
    'name' => 'TSODLULS sort short cells',
    'function' => 'TSODLULS_sort__short',
    'celltype' => 'short',
    'size' => 'direct',
    'comparison' => false,
    'stable' => false,
  ),
  'TSODLULS sort stable long cells' => array(
    'name' => 'TSODLULS sort stable long cells',
    'function' => 'TSODLULS_sort_stable',
    'celltype' => 'long',
    'size' => false,
    'comparison' => false,
    'stable' => true,
  ),
  'TSODLULS sort stable short cells' => array(
    'name' => 'TSODLULS sort stable short cells',
    'function' => 'TSODLULS_sort_stable__short',
    'celltype' => 'short',
    'size' => 'direct',
    'comparison' => false,
    'stable' => true,
  ),
  'TSODLULS_sort_radix8_count' => array(
    'name' => 'TSODLULS_sort_radix8_count',
    'function' => 'TSODLULS_sort_radix8_count',
    'celltype' => 'long',
    'size' => false,
    'comparison' => false,
    'stable' => true,
  ),
  'TSODLULS_sort_radix8_count__mark1' => array(
    'name' => 'TSODLULS_sort_radix8_count__mark1',
    'function' => 'TSODLULS_sort_radix8_count__mark1',
    'celltype' => 'long',
    'size' => false,
    'comparison' => false,
    'stable' => true,
  ),
  'TSODLULS_sort_radix8_count__short' => array(
    'name' => 'TSODLULS_sort_radix8_count__short',
    'function' => 'TSODLULS_sort_radix8_count__short',
    'celltype' => 'short',
    'size' => 'direct',
    'comparison' => false,
    'stable' => true,
  ),
  'TSODLULS_sort_radix8_count__short__mark1' => array(
    'name' => 'TSODLULS_sort_radix8_count__short__mark1',
    'function' => 'TSODLULS_sort_radix8_count__short__mark1',
    'celltype' => 'short',
    'size' => 'direct',
    'comparison' => false,
    'stable' => true,
  ),
  'TSODLULS_sort_radix8_count__short__mark2' => array(
    'name' => 'TSODLULS_sort_radix8_count__short__mark2',
    'function' => 'TSODLULS_sort_radix8_count__short__mark2',
    'celltype' => 'short',
    'size' => 'direct',
    'comparison' => false,
    'stable' => true,
  ),
  'TSODLULS_sort_radix8_count__short__mark3' => array(
    'name' => 'TSODLULS_sort_radix8_count__short__mark3',
    'function' => 'TSODLULS_sort_radix8_count__short__mark3',
    'celltype' => 'short',
    'size' => 'direct',
    'comparison' => false,
    'stable' => true,
  ),
  'TSODLULS_qsort_inlined__short' => array(
    'name' => 'TSODLULS_qsort_inlined__short',
    'function' => 'TSODLULS_qsort_inlined__short',
    'celltype' => 'short',
    'size' => false,
    'comparison' => false,
    'stable' => false,
  ),
  'TSODLULS_sort_radix8_count_qsort__short' => array(
    'name' => 'TSODLULS_sort_radix8_count_qsort__short',
    'function' => 'TSODLULS_sort_radix8_count_qsort__short',
    'celltype' => 'short',
    'size' => 'direct',
    'comparison' => false,
    'stable' => false,
  ),
  'TSODLULS_sort_radix8_count_insertion__short' => array(
    'name' => 'TSODLULS_sort_radix8_count_insertion__short',
    'function' => 'TSODLULS_sort_radix8_count_insertion__short',
    'celltype' => 'short',
    'size' => 'direct',
    'comparison' => false,
    'stable' => true,
  ),
  'TSODLULS_sort_radix8_count_insertion__short__mark1' => array(
    'name' => 'TSODLULS_sort_radix8_count_insertion__short__mark1',
    'function' => 'TSODLULS_sort_radix8_count_insertion__short__mark1',
    'celltype' => 'short',
    'size' => 'direct',
    'comparison' => false,
    'stable' => true,
  ),
  'TSODLULS_sort_radix8_count_insertion__short__mark2' => array(
    'name' => 'TSODLULS_sort_radix8_count_insertion__short__mark2',
    'function' => 'TSODLULS_sort_radix8_count_insertion__short__mark2',
    'celltype' => 'short',
    'size' => 'direct',
    'comparison' => false,
    'stable' => true,
  ),
  'TSODLULS_sort_radix8_count_insertion__short__mark3' => array(
    'name' => 'TSODLULS_sort_radix8_count_insertion__short__mark3',
    'function' => 'TSODLULS_sort_radix8_count_insertion__short__mark3',
    'celltype' => 'short',
    'size' => 'direct',
    'comparison' => false,
    'stable' => true,
  ),
  'TSODLULS_sort_radix8_count_insertion__short__mark4' => array(
    'name' => 'TSODLULS_sort_radix8_count_insertion__short__mark4',
    'function' => 'TSODLULS_sort_radix8_count_insertion__short__mark4',
    'celltype' => 'short',
    'size' => 'direct',
    'comparison' => false,
    'stable' => true,
  ),
  'TSODLULS_sort_radix8_count_insertion__short__mark5' => array(
    'name' => 'TSODLULS_sort_radix8_count_insertion__short__mark5',
    'function' => 'TSODLULS_sort_radix8_count_insertion__short__mark5',
    'celltype' => 'short',
    'size' => 'direct',
    'comparison' => false,
    'stable' => true,
  ),
  'TSODLULS_sort_radix8_count_insertion__short__mark6' => array(
    'name' => 'TSODLULS_sort_radix8_count_insertion__short__mark6',
    'function' => 'TSODLULS_sort_radix8_count_insertion__short__mark6',
    'celltype' => 'short',
    'size' => 'direct',
    'comparison' => false,
    'stable' => true,
  ),
  'TSODLULS_sort_radix8_count_insertion' => array(
    'name' => 'TSODLULS_sort_radix8_count_insertion',
    'function' => 'TSODLULS_sort_radix8_count_insertion',
    'celltype' => 'long',
    'size' => false,
    'comparison' => false,
    'stable' => true,
  ),
  'TSODLULS_sort_radix8_count_insertion__mark1' => array(
    'name' => 'TSODLULS_sort_radix8_count_insertion__mark1',
    'function' => 'TSODLULS_sort_radix8_count_insertion__mark1',
    'celltype' => 'long',
    'size' => false,
    'comparison' => false,
    'stable' => true,
  ),
  'TSODLULS_sort_radix8_count_insertion__mark2' => array(
    'name' => 'TSODLULS_sort_radix8_count_insertion__mark2',
    'function' => 'TSODLULS_sort_radix8_count_insertion__mark2',
    'celltype' => 'long',
    'size' => false,
    'comparison' => false,
    'stable' => true,
  ),
  'TSODLULS_sort_radix8_count_insertion__mark3' => array(
    'name' => 'TSODLULS_sort_radix8_count_insertion__mark3',
    'function' => 'TSODLULS_sort_radix8_count_insertion__mark3',
    'celltype' => 'long',
    'size' => false,
    'comparison' => false,
    'stable' => true,
  ),
  'TSODLULS_sort_radix8_count_insertion__mark4' => array(
    'name' => 'TSODLULS_sort_radix8_count_insertion__mark4',
    'function' => 'TSODLULS_sort_radix8_count_insertion__mark4',
    'celltype' => 'long',
    'size' => false,
    'comparison' => false,
    'stable' => true,
  ),
);

$iMinThreshold = 3;
$iMaxThreshold = 8;
for($i = $iMinThreshold; $i <= $iMaxThreshold; ++$i){
  $arrArrSortingAlgorithms['TSODLULS_qsort_inlined__short_'.$i] = array(
    'name' => 'TSODLULS_qsort_inlined__short_'.$i,
    'function' => 'TSODLULS_qsort_inlined__short_'.$i,
    'celltype' => 'short',
    'size' => false,
    'comparison' => false,
    'stable' => false,
  );
}
for($i = $iMinThreshold; $i <= $iMaxThreshold; ++$i){
  $arrArrSortingAlgorithms['TSODLULS_qsort_inlined__long_'.$i] = array(
    'name' => 'TSODLULS_qsort_inlined__long_'.$i,
    'function' => 'TSODLULS_qsort_inlined__long_'.$i,
    'celltype' => 'long',
    'size' => false,
    'comparison' => false,
    'stable' => false,
  );
}
for($j = 1; $j <= 6; ++$j){
  for($i = $iMinThreshold; $i <= $iMaxThreshold; ++$i){
    $arrArrSortingAlgorithms['TSODLULS_qsort__comparison_callback_'.$i.'_'.$j] = array(
      'name' => 'TSODLULS_qsort__comparison_callback_'.$i.'_'.$j,
      'function' => 'TSODLULS_qsort__comparison_callback_'.$i.'_'.$j,
      'celltype' => 'direct',
      'size' => 'cell',
      'comparison' => 'direct',
      'stable' => false,
    );
  }
}

?>
