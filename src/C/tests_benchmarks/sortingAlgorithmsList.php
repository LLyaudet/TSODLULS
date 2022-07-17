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

©Copyright 2018-2022 Laurent Lyaudet
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
    'logspace' => true,
  ),
  'qsort long cells' => array(
    'name' => 'qsort long cells',
    'function' => 'qsort',
    'celltype' => 'long',
    'size' => 'cell',
    'comparison' => 'long',
    'stable' => false,
    'logspace' => 'pseudo',// the cost of cells is linear but the sorting algorithm uses only logarithmic additional space
  ),
  'qsort short cells' => array(
    'name' => 'qsort short cells',
    'function' => 'qsort',
    'celltype' => 'short',
    'size' => 'cell',
    'comparison' => 'short',
    'stable' => false,
    'logspace' => 'pseudo',
  ),
  'TSODLULS sort comparison callback' => array(
    'name' => 'TSODLULS sort comparison callback',
    'function' => 'TSODLULS_sort__comparison_callback',
    'celltype' => 'direct',
    'size' => 'cell',
    'comparison' => 'direct',
    'stable' => false,
    'logspace' => false,
  ),
  'TSODLULS sort long cells' => array(
    'name' => 'TSODLULS sort long cells',
    'function' => 'TSODLULS_sort',
    'celltype' => 'long',
    'size' => false,
    'comparison' => false,
    'stable' => false,
    'logspace' => false,
  ),
  'TSODLULS sort short cells' => array(
    'name' => 'TSODLULS sort short cells',
    'function' => 'TSODLULS_sort__short',
    'celltype' => 'short',
    'size' => 'direct',
    'comparison' => false,
    'stable' => false,
    'logspace' => false,
  ),
  'TSODLULS sort stable comparison callback' => array(
    'name' => 'TSODLULS sort stable comparison callback',
    'function' => 'TSODLULS_sort_stable__comparison_callback',
    'celltype' => 'direct',
    'size' => 'cell',
    'comparison' => 'direct',
    'stable' => false,
    'logspace' => false,
  ),
  'TSODLULS sort stable long cells' => array(
    'name' => 'TSODLULS sort stable long cells',
    'function' => 'TSODLULS_sort_stable',
    'celltype' => 'long',
    'size' => false,
    'comparison' => false,
    'stable' => true,
    'logspace' => false,
  ),
  'TSODLULS sort stable short cells' => array(
    'name' => 'TSODLULS sort stable short cells',
    'function' => 'TSODLULS_sort_stable__short',
    'celltype' => 'short',
    'size' => 'direct',
    'comparison' => false,
    'stable' => true,
    'logspace' => false,
  ),
  'TSODLULS sort logspace comparison callback' => array(
    'name' => 'TSODLULS sort logspace comparison callback',
    'function' => 'TSODLULS_sort_logspace__comparison_callback',
    'celltype' => 'direct',
    'size' => 'cell',
    'comparison' => 'direct',
    'stable' => false,
    'logspace' => true,
  ),
  'TSODLULS sort stable logspace comparison callback' => array(
    'name' => 'TSODLULS sort stable logspace comparison callback',
    'function' => 'TSODLULS_sort_stable_logspace__comparison_callback',
    'celltype' => 'direct',
    'size' => 'cell',
    'comparison' => 'direct',
    'stable' => false,
    'logspace' => true,
  ),
);


include('../../competitor_algorithms/code_generation/competitorsListByFile.php');
$arrFilesIncluded = array(
  'TSODLULS_sorting_comparison_callback__competitor__generated',
  'TSODLULS_sorting_long_orders__competitor__generated',
  'TSODLULS_sorting_short_orders__competitor__generated',
);
foreach($arrFilesIncluded as $sFile){
  foreach($arrArrCompetitorsListByFile[$sFile]['functions'] as $arrSortingAlgorithm){
    if(!isset($arrSortingAlgorithm['name'])){
      $arrSortingAlgorithm['name'] = $arrSortingAlgorithm['function'];
    }
    $arrArrSortingAlgorithms[$arrSortingAlgorithm['name']] = $arrSortingAlgorithm;
  }
}

?>
