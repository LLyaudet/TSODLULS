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
  if($sLine == '' || $sLine[0] !== '|' || substr($sLine, 0, 2) == '|n'){
    unset($arrSLines[$i]);
  }
}

$arrTests = array(
  'uint8' => 2,
  'uint16' => 9,
  'uint32' => 16,
  'uint64' => 23,
  'int8' => 30,
  'int16' => 37,
  'int32' => 44,
  'int64' => 51,
  'float' => 58,
  'double' => 65,
);

$arrSettings = array(
  array('qsort', 'qsort direct'),
  array('qsort', 'qsort in cell'),
  array('qsort', 'qsort in cell with macraffs'),
  array('qsort', 'qsort in short cell with macraffs'),
  array('TSODLULS sort', 'TSODLULS sort in cell'),
  array('TSODLULS sort', 'TSODLULS sort in cell with macraffs'),
  array('TSODLULS sort', 'TSODLULS sort in short cell with macraffs'),
);

foreach($arrTests as $sTest => $iFirstColumn){
  echo "\nFor test $sTest : \n";

  foreach($arrSLines as $i => $sLine){
    $arrSValues = explode('|', $sLine);
    $iNumberOfElements = (int)$arrSValues[1];
    $fCurrentBestQsort = 100000;
    $fCurrentBestTSODLULSSort = 100000;
    $sCurrentBestQsort = '';
    $sCurrentBestTSODLULSSort = '';
    foreach($arrSettings as $i => $arrSetting){
      switch($arrSetting[0]){
        case 'qsort':
          if($fCurrentBestQsort == (float)$arrSValues[$iFirstColumn + $i]){
            $sCurrentBestQsort .= ' '.$arrSetting[1];
          }
          elseif($fCurrentBestQsort > (float)$arrSValues[$iFirstColumn + $i]){
            $sCurrentBestQsort = $arrSetting[1];
            $fCurrentBestQsort = (float)$arrSValues[$iFirstColumn + $i];
          }
        break;

        case 'TSODLULS sort':
          if($fCurrentBestTSODLULSSort == (float)$arrSValues[$iFirstColumn + $i]){
            $sCurrentBestTSODLULSSort .= ' '.$arrSetting[1];
          }
          elseif($fCurrentBestTSODLULSSort > (float)$arrSValues[$iFirstColumn + $i]){
            $sCurrentBestTSODLULSSort = $arrSetting[1];
            $fCurrentBestTSODLULSSort = (float)$arrSValues[$iFirstColumn + $i];
          }
        break;

        default:
          throw new Exception("Unknown setting category : ".$arrSetting[0]);
      }
    }//end foreach($arrSettings as $i => $arrSetting)
    echo " - with $iNumberOfElements elements : \n";
    if($fCurrentBestQsort == $fCurrentBestTSODLULSSort){
      echo "     it's a draw for $sCurrentBestQsort $sCurrentBestTSODLULSSort with $fCurrentBestQsort seconds.\n";
    }
    elseif($fCurrentBestQsort < $fCurrentBestTSODLULSSort){
      echo "     qsort wins ($sCurrentBestQsort)\n     over TSODLULS ($sCurrentBestTSODLULSSort)\n",
           "     with $fCurrentBestQsort seconds against $fCurrentBestTSODLULSSort (",
           ($fCurrentBestTSODLULSSort / $fCurrentBestQsort), " faster).\n";
    }
    else{
      echo "     TSODLULS wins ($sCurrentBestTSODLULSSort)\n      over qsort ($sCurrentBestQsort)\n",
           "     with $fCurrentBestTSODLULSSort seconds against $fCurrentBestQsort (",
           ($fCurrentBestQsort / $fCurrentBestTSODLULSSort), " faster).\n";
    }
  }//end foreach($arrSLines as $i => $sLine)

}//end foreach($arrTests as $sTest => $arrColumns)


?>
