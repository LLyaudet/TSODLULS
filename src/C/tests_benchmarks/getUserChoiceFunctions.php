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

include('../sortingAlgorithmsList.php');

function getChoiceForAlgorithm($sMessage, $bNotShortCells = false, $bAll = false){
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
      echo "[all] all algorithms\n";
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
    return -1;
  }

  $i = 0;
  foreach($arrArrSortingAlgorithmsFiltered as $sName => $arrDataAlgorithm){
    ++$i;
    if($i === $iChosenAlgorithm){
      break;//$sName and $arrData are correct
    }
  }

  echo "You selected [$iChosenAlgorithm] $sName.\n";
  return $arrDataAlgorithm;
}



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



