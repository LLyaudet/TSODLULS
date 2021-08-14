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

include('competitorsListByFile.php');
include('competitorsParameters.php');
include('competitorsGeneration.php');


$arrSFunctionNamesToFilter = array_slice($argv, 1);
if(!empty($arrSFunctionNamesToFilter)
  && in_array('TSODLULS_sort_radix8_count_qsort__short', $arrSFunctionNamesToFilter)
  && !in_array('TSODLULS_qsort_inlined__short_5_1', $arrSFunctionNamesToFilter)
){
  $arrSFunctionNamesToFilter []= 'TSODLULS_qsort_inlined__short_5_1';
}

$sLicense = file_get_contents('TSODLULS_license.tpl');

foreach($arrArrCompetitorsListByFile as $sFile => $arrFileData){
  $sHeaderContent =
      $sLicense
     ."\n//This file was generated by generateCompetitors.php script.\n\n\n\n"
     .$arrFileData['header_head']
  ;
  $sCodeContent =
      $sLicense
     ."\n//This file was generated by generateCompetitors.php script.\n\n\n\n"
     .$arrFileData['code_head']
  ;
  foreach($arrFileData['functions'] as $arrFunctionData){
    $sFunctionComment = "/**\n"
                       .$arrFileData['functions_section_header']
                       .$arrFunctionData['function_comment']
                       ." */\n";
    if(!isset($arrFunctionData['parameters'])){
      if(empty($arrSFunctionNamesToFilter)
        || in_array($arrFunctionData['function'], $arrSFunctionNamesToFilter)
      ){
        $sHeaderContent .= $sFunctionComment.getSHeaderForFunctionAndParameters(
           $arrFunctionData,
           ''
        );
        $sCodeContent .= $sFunctionComment.getSCodeForFunctionAndParametersValues(
           $arrFunctionData,
           [],
           ''
        );
      }
      continue;
    }
    $arrCurrentParameters = array();
    $iMaxParameters = count($arrFunctionData['parameters']) - 1;
    for($i = 0; $i <= $iMaxParameters; ++$i){
      $arrCurrentParameters[$i] = getNextParameterValue(
          null,
          $arrFunctionData['parameters'][$i]
      );
    }
    if(empty($arrSFunctionNamesToFilter)
      || in_array(getFunctionNameWithParameters($arrFunctionData, $arrCurrentParameters), $arrSFunctionNamesToFilter)
    ){
      $sParameters = getSParametersStringForFunctionName($arrCurrentParameters);
      $sHeaderContent .= $sFunctionComment.getSHeaderForFunctionAndParameters(
          $arrFunctionData,
          $sParameters
      );
      $sCodeContent .= $sFunctionComment.getSCodeForFunctionAndParametersValues(
          $arrFunctionData,
          $arrCurrentParameters,
          $sParameters
      );
    }

    $iCurrentParameterIndex = $iMaxParameters;
    while(true){
      $arrCurrentParameters[$iCurrentParameterIndex] = getNextParameterValue(
          $arrCurrentParameters[$iCurrentParameterIndex],
          $arrFunctionData['parameters'][$iCurrentParameterIndex]
      );
      if($arrCurrentParameters[$iCurrentParameterIndex] === null){
        if($iCurrentParameterIndex === 0){
          break;
        }
        --$iCurrentParameterIndex;
      }
      else{
        if($iCurrentParameterIndex === $iMaxParameters){
          if(empty($arrSFunctionNamesToFilter)
            || in_array(getFunctionNameWithParameters($arrFunctionData, $arrCurrentParameters), $arrSFunctionNamesToFilter)
          ){
            $sParameters = getSParametersStringForFunctionName($arrCurrentParameters);
            $sHeaderContent .= $sFunctionComment.getSHeaderForFunctionAndParameters(
                $arrFunctionData,
                $sParameters
            );
            $sCodeContent .= $sFunctionComment.getSCodeForFunctionAndParametersValues(
                $arrFunctionData,
                $arrCurrentParameters,
                $sParameters
            );
          }
        }
        else{
          ++$iCurrentParameterIndex;
        }
      }
    }
  }//end foreach($arrFileData['functions'] as $arrFunctionData)

  $sHeaderContent .= $arrFileData['header_tail'];
  $sCodeContent .= $arrFileData['code_tail'];

  if(!file_put_contents('../'.$sFile.'.h', $sHeaderContent)){
    die('Writing file ../'.$sFile.'.h failed.');
  }

  if(!file_put_contents('../'.$sFile.'.c', $sCodeContent)){
    die('Writing file ../'.$sFile.'.c failed.');
  }
}//end foreach($arrArrCompetitorsListByFile as $sFile => $arrFileData)

?>

