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



function getSSignatureForFunctionAndParameters(
  $arrFunctionData,
  $sParameters
){
  static $arrArgumentsByCellType = array(
    'direct' => "  void* arr_elements,\n"
               ."  size_t i_number_of_elements,\n"
               ."  size_t i_element_size,\n"
               ."  t_comparison_function fn_comparison\n",
    'long' => "  t_TSODLULS_sort_element* arr_elements,\n"
             ."  size_t i_number_of_elements\n",
    'short' => array(
      false => "  t_TSODLULS_sort_element__short* arr_elements,\n"
              ."  size_t i_number_of_elements\n",
      'direct' => "  t_TSODLULS_sort_element__short* arr_elements,\n"
                 ."  size_t i_number_of_elements,\n"
                 ."  uint8_t i_max_length\n",
    ),
  );
  $sArguments = $arrArgumentsByCellType[$arrFunctionData['celltype']];
  if($arrFunctionData['celltype'] === 'short'){
    $sArguments = $sArguments[$arrFunctionData['size']];
  }
  return $arrFunctionData['return_type'].' '.$arrFunctionData['function'].$sParameters."(\n"
        .$sArguments
        .")";
}//end function getSSignatureForFunctionAndParameters()



function getSHeaderForFunctionAndParameters(
  $arrFunctionData,
  $sParameters
){
  return getSSignatureForFunctionAndParameters($arrFunctionData, $sParameters).";\n\n\n\n";
}//end function getSHeaderForFunctionAndParameters()



function getSCodeForFunctionAndParametersValues(
  $arrFunctionData,
  $arrParameters,
  $sParameters
){
  $sCode = getSSignatureForFunctionAndParameters($arrFunctionData, $sParameters)."{\n";
  $arrMacraffVariables = array();
  for($i = 0, $iMax = count($arrParameters); $i < $iMax; ++$i){
    $sArgs = '';
    if(isset($arrFunctionData['parameters'][$i]['macro_args'])){
      for($j = 0, $jMax = $arrFunctionData['parameters'][$i]['macro_args']; $j < $jMax; ++$j){
        if($j === 0){
          $sArgs .= '(';
        }
        else{
          $sArgs .= ',';
        }
        $sArgs .= 'a'.$j;
      }
      $sArgs .= ')';
    }
    $sCode .= '  #define '.$arrFunctionData['parameters'][$i]['macro'].$sArgs.' ';
    if(is_array($arrParameters[$i])){
      $sCode .= $arrParameters[$i]['value_for_macro_def'];
    }
    else{
      $sCode .= $arrParameters[$i];
    }
    $sCode .= $sArgs."\n";

    if(is_array($arrParameters[$i]) && isset($arrParameters[$i]['macraff_variables'])){
      $arrMacraffVariables = array_merge($arrMacraffVariables,  $arrParameters[$i]['macraff_variables']);
    }
  }

  $arrMacraffVariables = array_unique($arrMacraffVariables);
  if(count($arrMacraffVariables) > 0){
    $sCode .= '  '.implode("\n  ", $arrMacraffVariables)."\n";
  }

  $sCode .= '  #include "./b/body_'.$arrFunctionData['function'].'.c"'."\n";
  for($i = 0, $iMax = count($arrParameters); $i < $iMax; ++$i){
    $sCode .= '  #undef '.$arrFunctionData['parameters'][$i]['macro']."\n";
  }
  $sCode .= '}//end function '.$arrFunctionData['function'].$sParameters."()\n\n\n\n";
  return $sCode;
}//end function getSCodeForFunctionAndParametersValues()



function callGenerateCompetitorsForFunctionsNames($arrSFunctionsNames){
  $sCompetitor = "competitor";
  if(count($arrSFunctionsNames) > 1){
    $sCompetitor .= 's';
  }
  $sCompetitorsList = implode(" ", $arrSFunctionsNames);
  echo "Generating ".$sCompetitor." ".$sCompetitorsList."\n";
  chdir('../../competitor_algorithms/code_generation/');
  $iReturnCode = 0;
  $arrSOutput = array();
  exec(
    'php generateCompetitors.php '.$sCompetitorsList,
    $arrSOutput,
    $iReturnCode
  );
  if($iReturnCode !== 0){
    foreach($arrSOutput as $sLine){
      echo $sLine, "\n";
    }
    die("The generation of the ".$sCompetitor." failed.\n");
  }
  echo "The generation of the ".$sCompetitor." succeeded.\n";
}//end function callGenerateCompetitorsForFunctionsNames()



?>

