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



function getSParametersStringForFunctionName($arrParametersValues){
  $sParameters = '';
  foreach($arrParametersValues as $parameterValue){
    $sParameters .= '_';
    if(is_array($parameterValue)){
      $sParameters .= $parameterValue['value_for_function_name'];
    }
    else{
      $sParameters .= $parameterValue;
    }
  }
  return $sParameters;
}// end function getSParametersStringForFunctionName()



function getFunctionNameWithParameters($arrFunctionData, $arrParametersValues){
  return $arrFunctionData['function'].getSParametersStringForFunctionName($arrParametersValues);
}//end function getFunctionNameWithParameters()



function getNextParameterValue($currentValue, $arrParameterData){
  switch($arrParameterData['type']){
    case 'integer_range':
      if($currentValue === null){
        return $arrParameterData['min_value'];
      }
      if($currentValue + 1 <= $arrParameterData['max_value']){
        return $currentValue + 1;
      }
    break;
    case 'enum':
      if($currentValue === null){
        return $arrParameterData['values'][0];
      }
      if(isset($arrParameterData['values'][$currentValue['index'] + 1])){
        return $arrParameterData['values'][$currentValue['index'] + 1];
      }
    break;
  }
  return null;
}//end function getNextParameterValue()



?>

