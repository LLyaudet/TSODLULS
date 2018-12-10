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
//This file is used with custom tests and benchmarks

include('../sortingAlgorithmsList.php');

function getChoiceForAlgorithm($sMessage){
  global $arrArrSortingAlgorithms;
  $iChosenAlgorithm = 0;
  do{
    echo $sMessage;

    $i = 0;
    foreach($arrArrSortingAlgorithms as $sName => $arrDataAlgorithm){
      ++$i;
      echo "[$i] ", $sName, "\n";
    }

    $input = readline();

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
  while($iChosenAlgorithm === 0);

  $i = 0;
  foreach($arrArrSortingAlgorithms as $sName => $arrDataAlgorithm){
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





