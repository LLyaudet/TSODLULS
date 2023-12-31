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

include('../sortingAlgorithmsList.php');
include('../../competitor_algorithms/code_generation/competitorsParameters.php');

function getArrChoiceOfAlgorithms($sMessage, $bNotShortCells = false, $bAll = false){
  global $arrArrSortingAlgorithms;

  $arrArrSortingAlgorithmsFiltered = $arrArrSortingAlgorithms;
  if($bNotShortCells){
    foreach($arrArrSortingAlgorithmsFiltered as $key => $arr){
      if($arr['celltype'] === 'short'){
        unset($arrArrSortingAlgorithmsFiltered[$key]);
      }
    }
  }

  $iChosenAlgorithm = 0;
  do{
    echo $sMessage;

    $i = 0;
    foreach($arrArrSortingAlgorithmsFiltered as $sName => $arrDataAlgorithm){
      ++$i;
      echo "[$i] ", $sName, "\n";
    }

    if($bAll){
      echo "[all] all algorithms (don't do this if you have no time, there are tens of algorithms that becomes thousands of variants with the combinations of parameters.)\n";
    }

    $input = readline();

    if($bAll && $input === 'all'){
      $iChosenAlgorithm = -1;
    }
    else{
      if(!ctype_digit($input)){
        echo "Invalid input. Please input a positive integer.\n";
        continue;
      }
      $input = (int)$input;
      if($input <= 0 || $input > $i){
        echo "Invalid input. Please input a positive integer in the range [1,$i].\n";
        continue;
      }
      $iChosenAlgorithm = $input;
    }
  }
  while($iChosenAlgorithm === 0);

  if($iChosenAlgorithm === -1){
    echo "You selected all algorithms.\n";
    return $arrArrSortingAlgorithmsFiltered;
  }

  $i = 0;
  foreach($arrArrSortingAlgorithmsFiltered as $sName => $arrDataAlgorithm){
    ++$i;
    if($i === $iChosenAlgorithm){
      break;//$sName and $arrData are correct
    }
  }

  echo "You selected [$iChosenAlgorithm] $sName.\n";
  return array($arrDataAlgorithm);
}//end function getArrChoiceOfAlgorithms()



function getArrChoiceOfAlgorithmsWithParameters($sMessage, $bNotShortCells = false, $bAll = false){
  $arrAlgorithms = getArrChoiceOfAlgorithms($sMessage, $bNotShortCells, $bAll);
  $bAllAlgorithmsSelected = count($arrAlgorithms) > 1;
  $arrFinalListOfAlgorithms = array();
  foreach($arrAlgorithms as $arrFunctionData){
    if(!isset($arrFunctionData['parameters'])){
      $arrFinalListOfAlgorithms []= $arrFunctionData;
      continue;
    }
    if($bAllAlgorithmsSelected){
      $arrArrParametersChoices = getAllChoicesForParameters($arrFunctionData['parameters']);
    }
    else{
      $arrArrParametersChoices = getArrArrChoicesForParameters($arrFunctionData['parameters'], !$bAll);
    }
    $iMaxParameters = count($arrFunctionData['parameters']) - 1;
    $iNumberOfParametersValuesCombinations = 1;
    for($i = 0; $i <= $iMaxParameters; ++$i){
      $iNumberOfParametersValuesCombinations *= count($arrArrParametersChoices[$i]);
    }
    for($j = 0; $j < $iNumberOfParametersValuesCombinations; ++$j){
      $arrCurrentParametersValues = array();
      $k = $j;
      for($i = 0; $i <= $iMaxParameters; ++$i){
        $arrCurrentParametersValues []= $arrArrParametersChoices[$i][$k % count($arrArrParametersChoices[$i])];
        $k /= count($arrArrParametersChoices[$i]);
      }
      $arrDataAlgorithmCopy = $arrFunctionData;
      $arrDataAlgorithmCopy['name'] = getFunctionNameWithParameters($arrFunctionData, $arrCurrentParametersValues);
      $arrDataAlgorithmCopy['function'] = $arrDataAlgorithmCopy['name'];
      $arrFinalListOfAlgorithms []= $arrDataAlgorithmCopy;
    }
  }
  return $arrFinalListOfAlgorithms;
}//end function getArrChoiceOfAlgorithmsWithParameters()



function getBChoiceForMacraff(){
  do{
    echo "Would-you like to benchmark it using macraffs ? [y/n]\n";
    $input = readline();
    if($input === 'y'){
      return true;
    }
    if($input === 'n'){
      return false;
    }
    echo "Type 'y' or 'n' please.\n";
  }
  while(true);
}//end function getBChoiceForMacraff()



function getINumberOfElementsMin(){
  do{
    echo "What will be the minimum number of elements to sort for this benchmark ? [default: 1]\n";
    $input = readline();
    if($input === ''){
      return 1;
    }
    if(ctype_digit($input)
      && strlen($input) < 14
      && ((int)$input) >= 1
    ){
      return (int)$input;
    }
    echo "Type a number between 1 and 9 999 999 999 999 or hit return for default value of 1.\n";
  }
  while(true);
}//end function getINumberOfElementsMin()



function getINumberOfElementsMax(){
  do{
    echo "The number of elements to be sorted will be multiplied by two at each round,",
         " until it exceeds the maximum number.\n";
    echo "What will be the maximum number of elements to sort for this benchmark ? [default: 1048576]\n";
    $input = readline();
    if($input === ''){
      return 1048576;
    }
    if(ctype_digit($input)
      && strlen($input) < 14
      && ((int)$input) >= 1
    ){
      return (int)$input;
    }
    echo "Type a number between 1 and 9 999 999 999 999 or hit return for default value of 1048576.\n";
  }
  while(true);
}//end function getINumberOfElementsMax()



function getIMinLengthOfString(){
  do{
    echo "What will be the minimum length of strings to sort for this test/benchmark ? [default: 1] (0 is a valid choice)\n";
    $input = readline();
    if($input === ''){
      return 1;
    }
    if(ctype_digit($input)
      && strlen($input) < 8
    ){
      return (int)$input;
    }
    echo "Type a number between 0 and 9 999 999 or hit return for default value of 1.\n";
  }
  while(true);
}//end function getIMinLengthOfString()



function getIMaxLengthOfString(){
  do{
    echo "What will be the maximum length of strings to sort for this test/benchmark ? [default: 128]\n";
    $input = readline();
    if($input === ''){
      return 128;
    }
    if(ctype_digit($input)
      && strlen($input) < 8
      && ((int)$input) >= 1
    ){
      return (int)$input;
    }
    echo "Type a number between 1 and 9 999 999 or hit return for default value of 128.\n";
  }
  while(true);
}//end function getIMaxLengthOfString()



function getILengthOfCommonPrefix($iMinLengthOfString){
  if($iMinLengthOfString == 0){
    return 0;
  }
  do{
    echo "What will be the length of the common prefix of strings to sort for this test/benchmark ? [default: 0]\n";
    echo "It must be at most the minimum length of $iMinLengthOfString that you chose.\n";
    $input = readline();
    if($input === ''){
      return 0;
    }
    if(ctype_digit($input)
      && strlen($input) < 8
      && ((int)$input) <= $iMinLengthOfString
    ){
      return (int)$input;
    }
    echo "Type a number between 0 and $iMinLengthOfString or hit return for default value of 0.\n";
  }
  while(true);
}//end function getILengthOfCommonPrefix()



function getBChoiceForBitLevelPadding(){
  do{
    echo "Would-you like to test/benchmark it using bit-level padding ? [y/n]\n";
    $input = readline();
    if($input === 'y'){
      return true;
    }
    if($input === 'n'){
      return false;
    }
    echo "Type 'y' or 'n' please.\n";
  }
  while(true);
}//end function getBChoiceForBitLevelPadding()



function getArrIFromS($s, $iMinValue, $iMaxValue){
  $arrSInputs = explode(',', $s);
  $arrResult = array();
  foreach($arrSInputs as $sInput){
    $sInput = trim($sInput);
    if(!ctype_digit($sInput)
      || strlen($sInput) > 18
      || ((int)$sInput) < $iMinValue
      || ((int)$sInput) > $iMaxValue
    ){
      echo "Invalid input. Please input a positive integer in the range ["
          .$iMinValue.",".$iMaxValue."].\n";
      return false;
    }
    $arrResult []= (int)$sInput;
  }
  return $arrResult;
}//end function getArrIFromS()



function getArrIChoiceForIntegerRangeParameter($arrParameter, $bOnlyOneValue){
  do{
    echo "Please, set the value of parameter ".$arrParameter['macro'].".\n";
    echo "Type an integer between ".$arrParameter['min_value']
        ." and ".$arrParameter['max_value']." [default: ".$arrParameter['default']."].\n";
    if(!$bOnlyOneValue){
      echo "You may also type \"all\" for testing or benchmarking all the range values,\n"
          ." or you may type a list of two or more integers like \""
          .$arrParameter['min_value'].", ".($arrParameter['min_value'] + 1)."\".\n";
    }
    $input = readline();
    if($input === ''){
      return array($arrParameter['default']);
    }
    if($input === 'all'){
      if($bOnlyOneValue){
        echo "Invalid input. Only one value must be given.\n";
        continue;
      }
      return range($arrParameter['min_value'], $arrParameter['max_value']);
    }

    $arr = getArrIFromS($input, $arrParameter['min_value'], $arrParameter['max_value']);
    if($arr !== false){
      if($bOnlyOneValue && count($arr) > 1){
        echo "Invalid input. Only one value must be given.\n";
        continue;
      }
      return $arr;
    }
  }
  while(true);
}//end function getArrIChoiceForIntegerRangeParameter()



function getArrChoiceForEnumParameter($arrParameter, $bOnlyOneValue){
  $sMessage = (
    "Please, set the value of parameter ".$arrParameter['macro'].".\n"
   ."Possible values:\n"
  );
  for($i = 0, $iMax = count($arrParameter['values']); $i < $iMax; ++$i){
    $sMessage .= "  [".($i+1)."] ".$arrParameter['values'][$i]['value_for_macro_def']."\n";
  }
  $sMessage .= "Type an integer between 1 and ".$iMax." [default: ".$arrParameter['default']."]\n";
  if(!$bOnlyOneValue){
    $sMessage .= (
      "You may also type \"all\" for testing or benchmarking all the enum values,\n"
     ." or you may type a list of two or more integers like \"1,2\" for the corresponding enum values.\n"
    );
  }

  do{
    echo $sMessage;
    $input = readline();
    if($input === ''){
      return array($arrParameter['values'][$arrParameter['default'] - 1]);
    }
    if($input === 'all'){
      if($bOnlyOneValue){
        echo "Invalid input. Only one value must be given.\n";
        continue;
      }
      return $arrParameter['values'];
    }

    $arr = getArrIFromS($input, 1, $iMax);
    if($arr !== false){
      if($bOnlyOneValue && count($arr) > 1){
        echo "Invalid input. Only one value must be given.\n";
        continue;
      }
      $arrValues = array();
      foreach($arr as $i){
        $arrValues []= $arrParameter['values'][$i - 1];
      }
      return $arrValues;
    }

  }
  while(true);
}//end function getArrChoiceForEnumParameter()



function getAllChoicesForParameters($arrParameters){
  $arrArrParametersChoices = array();
  foreach($arrParameters as $arrParameter){
    switch($arrParameter['type']){
      case 'integer_range':
        $arrArrParametersChoices []= range($arrParameter['min_value'], $arrParameter['max_value']);
      break;
      case 'enum':
        $arrArrParametersChoices []= $arrParameter['values'];
      break;
    }
  }
  return $arrArrParametersChoices;
}//end function getAllChoicesForParameters()



function getArrArrChoicesForParameters($arrParameters, $bOnlyOneValue){
  $arrArrParametersChoices = array();
  if(!$bOnlyOneValue){
    do{
      echo "Would-you like to test/benchmark it using all possible parameters ? [y/N]\n";
      $input = readline();
      if($input === 'y'){
        return getAllChoicesForParameters($arrParameters);
      }
      if(in_array($input, array('n', 'N', ''))){
        break;
      }
      echo "Type 'y' or 'n' please.\n";
    }
    while(true);
  }
  foreach($arrParameters as $arrParameter){
    switch($arrParameter['type']){
      case 'integer_range':
        $arrArrParametersChoices []= getArrIChoiceForIntegerRangeParameter(
          $arrParameter,
          $bOnlyOneValue
        );
      break;
      case 'enum':
        $arrArrParametersChoices []= getArrChoiceForEnumParameter(
          $arrParameter,
          $bOnlyOneValue
        );
      break;
    }
  }
  return $arrArrParametersChoices;
}//end function getArrArrChoicesForParameters()



