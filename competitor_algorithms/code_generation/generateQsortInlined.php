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

©Copyright 2018 Laurent Lyaudet
*/


$sTemplateFile = file_get_contents('qsort_inlined_with_short_cells.c.tpl');
if(strpos($sTemplateFile, 'BEGIN_TPL') === false){
  die("The template file qsort_inlined_with_short_cells.c.tpl does not contain the template beginning token.\n");
}
//removing everything before BEGIN_TPL
$sTemplateFile = substr($sTemplateFile, strpos($sTemplateFile, 'BEGIN_TPL') + strlen('BEGIN_TPL'));

if(strpos($sTemplateFile, 'END_TPL') === false){
  die("The template file qsort_inlined_with_short_cells.c.tpl does not contain the template end token.\n");
}
//removing everything after END_TPL
$sTemplateFile = substr($sTemplateFile, 0, strpos($sTemplateFile, 'END_TPL'));
//echo $sTemplateFile;

$sLicense = file_get_contents('TSODLULS_license.tpl');
$sHeaderContent = $sLicense."\n//This file was generated by generateQsortInlined.php script.\n";
$sCodeContent = $sLicense."\n//This file was generated by generateQsortInlined.php script.\n"
               ."#include \"TSODLULS__competitor.h\"\n\n";
$iMinThreshold = 3;
$iMaxThreshold = 8;
for($i = $iMinThreshold; $i <= $iMaxThreshold; ++$i){
  $sHeaderContent .= "\n"
      ."/**\n"
      ." * Sorting functions for short nextified strings\n"
      ." * Qsort from glibc inlined with short cells.\n"
      ." */\n"
      ."int TSODLULS_qsort_inlined__short_".$i."(\n"
      ."  t_TSODLULS_sort_element__short* arr_elements,\n"
      ."  size_t i_number_of_elements\n"
      .");\n\n\n"
  ;

  $sCodeContent .= str_replace('@iNumberOfElementsForInsertionSort@', (string)$i, $sTemplateFile);
}

if(!file_put_contents('../TSODLULS__competitor__generated_qsort.h', $sHeaderContent)){
  die('Writing file ../TSODLULS__competitor__generated_qsort.h failed.');
}

if(!file_put_contents('../TSODLULS__competitor__generated_qsort.c', $sCodeContent)){
  die('Writing file ../TSODLULS__competitor__generated_qsort.c failed.');
}

?>