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

include('../getUserChoiceFunctions.php');

$sMessage = "Hello, please choose an algorithm to test\n"
           ." (input the number before the name and press return).\n"
           ."The test will compare the sorted array obtained with qsort direct\n"
           ." and the one obtained with the algorithm you selected.\n\n";

$arrArrDataAlgorithm = getArrChoiceOfAlgorithmsWithParameters($sMessage, true, true);

if(count($arrArrDataAlgorithm) > 1){
  $bWithBitLevelPadding = 'both';
}
else{
  $bWithBitLevelPadding = false;
  if($arrArrDataAlgorithm[0]['celltype'] === 'long'){
    $bWithBitLevelPadding = getBChoiceForBitLevelPadding();
  }
}

$iMinLengthOfString = getIMinLengthOfString();
$iMaxLengthOfString = getIMaxLengthOfString();
$iLengthOfCommonPrefix = getILengthOfCommonPrefix($iMinLengthOfString);

include('../generatingFunctionsString.php');

foreach($arrArrDataAlgorithm as $arrDataAlgorithm){
  if($bWithBitLevelPadding === 'both'){
    build_and_run_test_for_algorithm_data(
      $arrDataAlgorithm,
      false,
      $iMinLengthOfString,
      $iMaxLengthOfString,
      $iLengthOfCommonPrefix
    );
    if($arrDataAlgorithm['celltype'] === 'long'){
      build_and_run_test_for_algorithm_data(
        $arrDataAlgorithm,
        true,
        $iMinLengthOfString,
        $iMaxLengthOfString,
        $iLengthOfCommonPrefix
      );
    }
  }
  else{
    build_and_run_test_for_algorithm_data(
      $arrDataAlgorithm,
      $bWithBitLevelPadding,
      $iMinLengthOfString,
      $iMaxLengthOfString,
      $iLengthOfCommonPrefix
    );
  }
}



function build_and_run_test_for_algorithm_data(
  $arrDataAlgorithm,
  $bWithBitLevelPadding,
  $iMinLengthOfString,
  $iMaxLengthOfString,
  $iLengthOfCommonPrefix
){

  global $arrSubTests;

  $sName = $arrDataAlgorithm['name'];
  if($bWithBitLevelPadding){
    $sBitLevelPadding = 'with bit-level padding';
  }
  else{
    $sBitLevelPadding = 'without bit-level padding';
  }

  echo "Generating file test_custom_strings.c for $sName $sBitLevelPadding\n";
  $sCustomTest = file_get_contents('./test_custom_strings.c.tpl');
  if($sCustomTest == ''){
    die("The template file test_custom_strings.c.tpl was not found, or couldn't be read, or was empty.\n");
  }

  if(strpos($sCustomTest, '@iMinLengthOfString@') === false){
    die("The template file test_custom_strings.c.tpl does not contain the insertion token @iMinLengthOfString@.\n");
  }
  $sCustomTest = str_replace('@iMinLengthOfString@', (string)$iMinLengthOfString, $sCustomTest);

  if(strpos($sCustomTest, '@iMaxLengthOfString@') === false){
    die("The template file test_custom_strings.c.tpl does not contain the insertion token @iMaxLengthOfString@.\n");
  }
  $sCustomTest = str_replace('@iMaxLengthOfString@', (string)$iMaxLengthOfString, $sCustomTest);

  if(strpos($sCustomTest, '@iLengthOfCommonPrefix@') === false){
    die("The template file test_custom_strings.c.tpl does not contain the insertion token @iLengthOfCommonPrefix@.\n");
  }
  $sCustomTest = str_replace('@iLengthOfCommonPrefix@', (string)$iLengthOfCommonPrefix, $sCustomTest);


  foreach($arrSubTests as $sSubTest => $arrDataSubTest){
    if(strpos($sCustomTest, 'PHP__INCLUDE_TEST_CODE_FOR_CHOSEN_ALGORITHM__'.$sSubTest) === false){
      die("The template file test_custom_strings.c.tpl does not contain the insertion token for sorting ".$sSubTest.".\n");
    }
    $sFragment = getTestingFragmentFor($arrDataAlgorithm, $sSubTest, false, $bWithBitLevelPadding);
    if($arrDataAlgorithm['celltype'] !== 'direct'){
      $sFragment .= "\n    ".getTestingFragmentFor($arrDataAlgorithm, $sSubTest, true, $bWithBitLevelPadding);
    }
    $sCustomTest = str_replace('PHP__INCLUDE_TEST_CODE_FOR_CHOSEN_ALGORITHM__'.$sSubTest, $sFragment, $sCustomTest);
  }
  if(file_put_contents('./test_custom_strings.c', $sCustomTest) == 0){
    die("The file test_custom_strings.c could not be saved.\n");
  }
  echo "The file test_custom_strings.c was generated.\n";

  echo "Compiling.\n";
  chdir('../..');
  $iReturnCode = 0;
  $arrSOutput = array();
  exec('make build-test-custom-strings', $arrSOutput, $iReturnCode);
  if($iReturnCode !== 0){
    echo "The compilation failed.\n";
    foreach($arrSOutput as $sLine){
      echo $sLine, "\n";
    }
    die("The compilation failed.\n");
  }
  echo "The compilation succeeded.\n";

  chdir('tests_benchmarks/test_custom_strings/');
  $iReturnCode = 0;
  $arrSOutput = array();
  exec('./test_custom_strings.exe', $arrSOutput, $iReturnCode);
  if($iReturnCode !== 0){
    echo "Custom test failed.\n";
  }
  else{
    echo "Custom test succeeded.\n";
  }

  foreach($arrSOutput as $sLine){
    echo $sLine, "\n";
  }
}//end function build_and_run_test_for_algorithm_data()



?>
