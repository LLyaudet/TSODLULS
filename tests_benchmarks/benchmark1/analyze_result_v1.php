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
if(!isset($argv[1])){
  echo "The filename of the results is missing.\n";
  die(1);
}
$sResults = file_get_contents($argv[1]);
if($sResults === false){
  echo "The file could not be opened.\n";
  die(1);
}
$arrSLines = explode("\n", $sResults);
//We clean the lines
foreach($arrSLines as $i => $sLine){
  if($sLine == '' || $sLine[0] !== '|'){
    unset($arrSLines[$i]);
  }
}

$arrTests = array(
  'uint8' => array(2,3,4),
  'uint16' => array(5,6,7),
  'uint32' => array(8,9,10),
  'uint64' => array(11,12,13),
  'int8' => array(14,15,16),
  'int16' => array(17,18,19),
  'int32' => array(20,21,22),
  'int64' => array(23,24,25),
  'float' => array(26,27,28),
  'double' => array(29,30,31),
);

foreach($arrTests as $sTest => $arrColumns){
  $iFirstTimeTSODLULSSORTFasterThanQSORTDirect = null;
  $iFirstTimeTSODLULSSORTFasterThanQSORTInCell = null;
  $iFirstTimeQSORTInCellFasterThanQSORTDirect = null;
  $iLastTimeQSORTDirectFasterThanTSODLULSSORT = null;
  $iLastTimeQSORTInCellFasterThanTSODLULSSORT = null;
  $iLastTimeQSORTDirectFasterThanQSORTInCell = null;
  foreach($arrSLines as $i => $sLine){
    $arrSValues = explode('|', $sLine);
    $iNumberOfElements = (int)$arrSValues[1];
    if(((float)$arrSValues[$arrColumns[0]]) > ((float)$arrSValues[$arrColumns[2]])
      && ($iFirstTimeTSODLULSSORTFasterThanQSORTDirect === null
         || $iFirstTimeTSODLULSSORTFasterThanQSORTDirect > $iNumberOfElements)
    ){
      $iFirstTimeTSODLULSSORTFasterThanQSORTDirect = $iNumberOfElements;
    }
    if(((float)$arrSValues[$arrColumns[1]]) > ((float)$arrSValues[$arrColumns[2]])
      && ($iFirstTimeTSODLULSSORTFasterThanQSORTInCell === null
         || $iFirstTimeTSODLULSSORTFasterThanQSORTInCell > $iNumberOfElements)
    ){
      $iFirstTimeTSODLULSSORTFasterThanQSORTInCell = $iNumberOfElements;
    }
    if(((float)$arrSValues[$arrColumns[0]]) > ((float)$arrSValues[$arrColumns[1]])
      && ($iFirstTimeQSORTInCellFasterThanQSORTDirect === null
         || $iFirstTimeQSORTInCellFasterThanQSORTDirect > $iNumberOfElements)
    ){
      $iFirstTimeQSORTInCellFasterThanQSORTDirect = $iNumberOfElements;
    }

    if(((float)$arrSValues[$arrColumns[0]]) < ((float)$arrSValues[$arrColumns[2]])
      && ($iLastTimeQSORTDirectFasterThanTSODLULSSORT === null
         || $iLastTimeQSORTDirectFasterThanTSODLULSSORT < $iNumberOfElements)
    ){
      $iLastTimeQSORTDirectFasterThanTSODLULSSORT = $iNumberOfElements;
    }
    if(((float)$arrSValues[$arrColumns[1]]) < ((float)$arrSValues[$arrColumns[2]])
      && ($iLastTimeQSORTInCellFasterThanTSODLULSSORT === null
         || $iLastTimeQSORTInCellFasterThanTSODLULSSORT < $iNumberOfElements)
    ){
      $iLastTimeQSORTInCellFasterThanTSODLULSSORT = $iNumberOfElements;
    }
    if(((float)$arrSValues[$arrColumns[0]]) < ((float)$arrSValues[$arrColumns[1]])
      && ($iLastTimeQSORTDirectFasterThanQSORTInCell === null
         || $iLastTimeQSORTDirectFasterThanQSORTInCell < $iNumberOfElements)
    ){
      $iLastTimeQSORTDirectFasterThanQSORTInCell = $iNumberOfElements;
    }
  }//end foreach($arrSLines as $i => $sLine)

  echo "\nFor test $sTest : \n";
  if($iFirstTimeTSODLULSSORTFasterThanQSORTDirect === null){
    echo "-TSODLULS sort was never faster than qsort direct.\n";
  }
  else{
    echo "-TSODLULS sort was faster than qsort direct for the first time at",
         " $iFirstTimeTSODLULSSORTFasterThanQSORTDirect elements.\n";
    if($iLastTimeQSORTDirectFasterThanTSODLULSSORT === null){
      echo "-qsort direct was never faster than TSODLULS sort.\n";
    }
    else{
      echo "-qsort direct was faster than TSODLULS sort for the last time at",
           " $iLastTimeQSORTDirectFasterThanTSODLULSSORT elements.\n";
    }
  }
  if($iFirstTimeTSODLULSSORTFasterThanQSORTInCell === null){
    echo "-TSODLULS sort was never faster than qsort in cell.\n";
  }
  else{
    echo "-TSODLULS sort was faster than qsort in cell for the first time at",
         " $iFirstTimeTSODLULSSORTFasterThanQSORTInCell elements.\n";
    if($iLastTimeQSORTInCellFasterThanTSODLULSSORT === null){
      echo "-qsort in cell was never faster than TSODLULS sort.\n";
    }
    else{
      echo "-qsort in cell was faster than TSODLULS sort for the last time at",
           " $iLastTimeQSORTInCellFasterThanTSODLULSSORT elements.\n";
    }
  }
  if($iFirstTimeQSORTInCellFasterThanQSORTDirect === null){
    echo "-qsort in cell was never faster than qsort direct.\n";
  }
  else{
    echo "-qsort in cell was faster than qsort direct for the first time at",
         " $iFirstTimeQSORTInCellFasterThanQSORTDirect elements.\n";
    if($iLastTimeQSORTDirectFasterThanQSORTInCell === null){
      echo "-qsort direct was never faster than qsort in cell.\n";
    }
    else{
      echo "-qsort direct was faster than qsort in cell for the last time at",
           " $iLastTimeQSORTDirectFasterThanQSORTInCell elements.\n";
    }
  }
}//end foreach($arrTests as $sTest => $arrColumns)


?>
