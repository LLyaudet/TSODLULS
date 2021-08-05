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

$arrDataAlgorithm = getChoiceForAlgorithm($sMessage, false, true);

if($arrDataAlgorithm === -1){
  global $arrArrSortingAlgorithms;
  $arrArrDataAlgorithm = $arrArrSortingAlgorithms;
}
else{
  $arrArrDataAlgorithm = array($arrDataAlgorithm);
}

include('../generatingFunctions.php');

foreach($arrArrDataAlgorithm as $arrDataAlgorithm){
  build_and_run_test_for_algorithm_data($arrDataAlgorithm);
}



function build_and_run_test_for_algorithm_data($arrDataAlgorithm){
  global $arrSubTests;
  $sName = $arrDataAlgorithm['name'];

  echo "Generating file test_custom.c for $sName\n";
  $sCustomTest = file_get_contents('./test_custom.c.tpl');
  if($sCustomTest == ''){
    die("The template file test_custom.c.tpl was not found, or couldn't be read, or was empty.\n");
  }
  foreach($arrSubTests as $sSubTest => $arrDataSubTest){
    if(strpos($sCustomTest, 'PHP__INCLUDE_TEST_CODE_FOR_CHOSEN_ALGORITHM__'.$sSubTest) === false){
      die("The template file test_custom.c.tpl does not contain the insertion token for sorting ".$sSubTest.".\n");
    }
    $sFragment = getTestingFragmentFor($arrDataAlgorithm, $sSubTest, false);
    if($arrDataAlgorithm['celltype'] !== 'direct'){
      $sFragment .= "\n    ".getTestingFragmentFor($arrDataAlgorithm, $sSubTest, true);
    }
    $sCustomTest = str_replace('PHP__INCLUDE_TEST_CODE_FOR_CHOSEN_ALGORITHM__'.$sSubTest, $sFragment, $sCustomTest);
  }
  if(file_put_contents('./test_custom.c', $sCustomTest) == 0){
    die("The file test_custom.c could not be saved.\n");
  }
  echo "The file test_custom.c was generated.\n";

  echo "Compiling.\n";
  chdir('../..');
  $iReturnCode = 0;
  $arrSOutput = array();
  exec('make build-test-custom', $arrSOutput, $iReturnCode);
  if($iReturnCode !== 0){
    echo "The compilation failed.\n";
    foreach($arrSOutput as $sLine){
      echo $sLine, "\n";
    }
    die("The compilation failed.\n");
  }
  echo "The compilation succeeded.\n";

  chdir('tests_benchmarks/test_custom/');
  $iReturnCode = 0;
  $arrSOutput = array();
  exec('./test_custom.exe', $arrSOutput, $iReturnCode);
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
