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

©Copyright 2018-2023 Laurent Lyaudet
*/
//This file is used with custom tests and benchmarks

$arrSubTests = array(
  'uint8' => array(
      'type' => 'uint8_t',
      'array_substring' => 'ui_8',
      'size' => 1,
  ),
  'uint16' => array(
      'type' => 'uint16_t',
      'array_substring' => 'ui_16',
      'size' => 2,
  ),
  'uint32' => array(
      'type' => 'uint32_t',
      'array_substring' => 'ui_32',
      'size' => 4,
  ),
  'uint64' => array(
      'type' => 'uint64_t',
      'array_substring' => 'ui_64',
      'size' => 8,
  ),
  'int8' => array(
      'type' => 'int8_t',
      'array_substring' => 'i_8',
      'size' => 1,
  ),
  'int16' => array(
      'type' => 'int16_t',
      'array_substring' => 'i_16',
      'size' => 2,
  ),
  'int32' => array(
      'type' => 'int32_t',
      'array_substring' => 'i_32',
      'size' => 4,
  ),
  'int64' => array(
      'type' => 'int64_t',
      'array_substring' => 'i_64',
      'size' => 8,
  ),
  'float' => array(
      'type' => 'float',
      'array_substring' => 'f_float',
      'size' => 4,
  ),
  'double' => array(
      'type' => 'double',
      'array_substring' => 'f_double',
      'size' => 8,
  ),
);



function getInitFragmentForDirect($sSubTest, $iResult, $bMacraff){
  global $arrSubTests;
  $sArraySubstring = $arrSubTests[$sSubTest]['array_substring'];
  return 'memcpy(arr_'.$sArraySubstring.'_result'.$iResult.', arr_'.$sArraySubstring.'_seed, i_number_of_elements * sizeof('.$arrSubTests[$sSubTest]['type'].'));';
}//end function getInitFragmentForDirect()



function getInitFragmentForLongCells($sSubTest, $iResult, $bMacraff){
  return 'TSODLULS_code_fragment_init_long_cells_for_'.$sSubTest
        .($bMacraff ? '_with_macraffs' : '')
        .'();';
}//end function getInitFragmentForLongCells()



function getInitFragmentForShortCells($sSubTest, $iResult, $bMacraff){
  return 'TSODLULS_code_fragment_init_short_cells_for_'.$sSubTest
        .($bMacraff ? '_with_macraffs' : '')
        .'();';
}//end function getInitFragmentForShortCells()



function getSortFunctionCall($arrDataAlgorithm, $sSubTest, $iResult){
  global $arrSubTests;

  $sFunctionCall = $arrDataAlgorithm['function'].'(';
  $sCellType = $arrDataAlgorithm['celltype'];
  switch($sCellType){
    case 'direct':
      $sFunctionCall .= 'arr_'.$arrSubTests[$sSubTest]['array_substring'].'_result'.$iResult;
    break;

    case 'long':
      $sFunctionCall .= 'arr_cells';
    break;

    case 'short':
      $sFunctionCall .= 'arr_cells__short';
    break;

    default:
    die("Unknown celltype ".$sCellType."\n");
  }
  $sFunctionCall .= ', i_number_of_elements';
  if($arrDataAlgorithm['size'] !== false){
    switch($arrDataAlgorithm['size']){
      case 'direct':
        $sFunctionCall .= ', '.$arrSubTests[$sSubTest]['size'];
      break;

      case 'cell':
        switch($sCellType){
          case 'direct':
            $sFunctionCall .= ', '.$arrSubTests[$sSubTest]['size'];
          break;

          case 'long':
            $sFunctionCall .= ', sizeof(t_TSODLULS_sort_element)';
          break;

          case 'short':
            $sFunctionCall .= ', sizeof(t_TSODLULS_sort_element__short)';
          break;

          default:
          die("Unknown celltype ".$sCellType."\n");
        }
      break;

      default:
      die("Unknown size type ".$arrDataAlgorithm['size']."\n");
    }
  }

  if($arrDataAlgorithm['comparison'] !== false){
    switch($arrDataAlgorithm['comparison']){
      case 'direct':
        $sFunctionCall .= ', (&TSODLULS_compare_'.$sSubTest.'_direct)';
      break;

      case 'long':
        $sFunctionCall .= ', (&TSODLULS_compare_uint'.($arrSubTests[$sSubTest]['size'] * 8).'_in_cell)';
      break;

      case 'short':
        $sFunctionCall .= ', ((&TSODLULS_compare_nextified_key_in_cell__short))';
      break;

      default:
      die("Unknown comparison type ".$arrDataAlgorithm['comparison']."\n");
    }
  }

  return $sFunctionCall.');';
}//end function getSortFunctionCall()



function getPostFragmentForLongCells($sSubTest, $iResult, $bMacraff){
  return 'TSODLULS_code_fragment_fill_result'.$iResult.'_with_long_cells_for_'.$sSubTest
        .($bMacraff ? '_with_macraffs' : '')
        .'();';
}//end function getPostFragmentForLongCells()



function getPostFragmentForShortCells($sSubTest, $iResult, $bMacraff){
  return 'TSODLULS_code_fragment_fill_result'.$iResult.'_with_short_cells_for_'.$sSubTest
        .'_no_macraff_needed'//($bMacraff ? '_with_macraffs' : '')
        .'();';
}//end function getPostFragmentForShortCells()



function getTestingFragmentFor($arrDataAlgorithm, $sSubTest, $bMacraff){
  $sFragment = '';
  $sCellType = $arrDataAlgorithm['celltype'];
  //Init
  switch($sCellType){
    case 'direct':
      $sFragment .= getInitFragmentForDirect($sSubTest, 2, $bMacraff);
    break;

    case 'long':
      $sFragment .= getInitFragmentForLongCells($sSubTest, 2, $bMacraff);
    break;

    case 'short':
      $sFragment .= getInitFragmentForShortCells($sSubTest, 2, $bMacraff);
    break;

    default:
    die("Unknown celltype ".$sCellType."\n");
  }
  //Sorting
  $sFragment .= "\n".getSortFunctionCall($arrDataAlgorithm, $sSubTest, 2);
  //Post-processing
  switch($sCellType){
    case 'direct':
      //nothing to do
    break;

    case 'long':
      $sFragment .= "\n".getPostFragmentForLongCells($sSubTest, 2, $bMacraff);
    break;

    case 'short':
      $sFragment .= "\n".getPostFragmentForShortCells($sSubTest, 2, $bMacraff);
    break;

    default:
    die("Unknown celltype ".$sCellType."\n");
  }
  //Comparing
  $sFragment .= "\nTSODLULS_code_fragment_compare_results_for_".$sSubTest
               ."(\"qsort direct and ".$arrDataAlgorithm['name']
               .($bMacraff ? " (macraff)" : "")." gave different results (".$sSubTest.")\\n\");\n";
  return $sFragment;
}//end function getTestingFragmentFor()



function getComparingFragmentFor($arrDataAlgorithm, $sSubTest, $bMacraff){
  $sFragment = '';
  $sCellType = $arrDataAlgorithm['celltype'];
  $sInitTimer = "clock_gettime(CLOCK_MONOTONIC, &start);";
  //Init
  switch($sCellType){
    case 'direct':
      $sFragment .= getInitFragmentForDirect($sSubTest, 1, $bMacraff);
      //Init fragment for direct is not counted as preparation time for fair comparison
      $sFragment .= "\n".$sInitTimer;
    break;

    case 'long':
      $sFragment .= $sInitTimer;
      $sFragment .= "\n".getInitFragmentForLongCells($sSubTest, 1, $bMacraff);
    break;

    case 'short':
      $sFragment .= $sInitTimer;
      $sFragment .= "\n".getInitFragmentForShortCells($sSubTest, 1, $bMacraff);
    break;

    default:
    die("Unknown celltype ".$sCellType."\n");
  }
  //Sorting
  $sFragment .= "\n".getSortFunctionCall($arrDataAlgorithm, $sSubTest, 1);
  //Post-processing
  switch($sCellType){
    case 'direct':
      //nothing to do
    break;

    case 'long':
      $sFragment .= "\n".getPostFragmentForLongCells($sSubTest, 1, $bMacraff);
    break;

    case 'short':
      $sFragment .= "\n".getPostFragmentForShortCells($sSubTest, 1, $bMacraff);
    break;

    default:
    die("Unknown celltype ".$sCellType."\n");
  }
  //Time result
  $sFragment .= "\nTSODLULS_code_fragment_print_time();";
  return $sFragment;
}//end function getComparingFragmentFor()



