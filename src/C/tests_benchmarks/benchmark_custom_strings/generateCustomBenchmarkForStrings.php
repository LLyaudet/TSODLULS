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

$sMessage = "Hello, please choose a first algorithm to benchmark\n"
           ." (input the number before the name and press return).\n\n";

$arrDataAlgorithm1 = getArrChoiceOfAlgorithmsWithParameters($sMessage, true)[0];

$bWithMacraff1 = false;
if($arrDataAlgorithm1['celltype'] != 'direct'){
  $bWithMacraff1 = getBChoiceForMacraff();
}

$bWithBitLevelPadding1 = false;
if($arrDataAlgorithm1['celltype'] === 'long'){
  $bWithBitLevelPadding1 = getBChoiceForBitLevelPadding();
}

$sMessage = "Hello, please choose a second algorithm to benchmark\n"
           ." (input the number before the name and press return).\n\n";

$arrDataAlgorithm2 = getArrChoiceOfAlgorithmsWithParameters($sMessage, true)[0];

$bWithMacraff2 = false;
if($arrDataAlgorithm2['celltype'] != 'direct'){
  $bWithMacraff2 = getBChoiceForMacraff();
}

$bWithBitLevelPadding2 = false;
if($arrDataAlgorithm2['celltype'] === 'long'){
  $bWithBitLevelPadding2 = getBChoiceForBitLevelPadding();
}

$iNumberOfElementsMin = getINumberOfElementsMin();
$iNumberOfElementsMax = getINumberOfElementsMax();
$iMinLengthOfString = getIMinLengthOfString();
$iMaxLengthOfString = getIMaxLengthOfString();
$iLengthOfCommonPrefix = getILengthOfCommonPrefix($iMinLengthOfString);

echo $arrDataAlgorithm1['name'], ($bWithMacraff1 ? " with macraffs" : ""), ($bWithBitLevelPadding1 ? " with bit level padding" : ""), " and ",
     $arrDataAlgorithm2['name'], ($bWithMacraff2 ? " with macraffs" : ""), ($bWithBitLevelPadding2 ? " with bit level padding" : ""),
     " will be compared with a number of strings",
     " between $iNumberOfElementsMin and $iNumberOfElementsMax.\n",
     "Each string will have length between $iMinLengthOfString and $iMaxLengthOfString,",
     " and a common prefix of length $iLengthOfCommonPrefix.\n";

include('../../competitor_algorithms/code_generation/competitorsGeneration.php');
chdir('../../competitor_algorithms/code_generation/');
callGenerateCompetitorsForFunctionsNames(array(
  $arrDataAlgorithm1['name'],
  $arrDataAlgorithm2['name']
));
chdir('../../tests_benchmarks/benchmark_custom_strings/');

include('../generatingFunctionsString.php');

echo "Generating file benchmark_custom_strings.c\n";
$sCustomBenchmark = file_get_contents('./benchmark_custom_strings.c.tpl');
if($sCustomBenchmark == ''){
  die("The template file benchmark_custom_strings.c.tpl was not found, or couldn't be read, or was empty.\n");
}

if(strpos($sCustomBenchmark, '@iNumberOfElementsMin@') === false){
  die("The template file benchmark_custom_strings.c.tpl does not contain the insertion token @iNumberOfElementsMin@.\n");
}
$sCustomBenchmark = str_replace('@iNumberOfElementsMin@', (string)$iNumberOfElementsMin, $sCustomBenchmark);

if(strpos($sCustomBenchmark, '@iNumberOfElementsMax@') === false){
  die("The template file benchmark_custom_strings.c.tpl does not contain the insertion token @iNumberOfElementsMax@.\n");
}
$sCustomBenchmark = str_replace('@iNumberOfElementsMax@', (string)$iNumberOfElementsMax, $sCustomBenchmark);

if(strpos($sCustomBenchmark, '@iMinLengthOfString@') === false){
  die("The template file test_custom_strings.c.tpl does not contain the insertion token @iMinLengthOfString@.\n");
}
$sCustomBenchmark = str_replace('@iMinLengthOfString@', (string)$iMinLengthOfString, $sCustomBenchmark);

if(strpos($sCustomBenchmark, '@iMaxLengthOfString@') === false){
  die("The template file test_custom_strings.c.tpl does not contain the insertion token @iMaxLengthOfString@.\n");
}
$sCustomBenchmark = str_replace('@iMaxLengthOfString@', (string)$iMaxLengthOfString, $sCustomBenchmark);

if(strpos($sCustomBenchmark, '@iLengthOfCommonPrefix@') === false){
  die("The template file test_custom_strings.c.tpl does not contain the insertion token @iLengthOfCommonPrefix@.\n");
}
$sCustomBenchmark = str_replace('@iLengthOfCommonPrefix@', (string)$iLengthOfCommonPrefix, $sCustomBenchmark);

foreach($arrSubTests as $sSubTest => $arrDataSubTest){
  if(strpos($sCustomBenchmark, 'PHP__INCLUDE_BENCHMARK_CODE_FOR_CHOSEN_ALGORITHMS__'.$sSubTest) === false){
    die("The template file benchmark_custom_strings.c.tpl does not contain the insertion token for sorting ".$sSubTest.".\n");
  }
  $sFragment = getComparingFragmentFor($arrDataAlgorithm1, $sSubTest, $bWithMacraff1, $bWithBitLevelPadding1)
         ."\n".getComparingFragmentFor($arrDataAlgorithm2, $sSubTest, $bWithMacraff2, $bWithBitLevelPadding2);
  $sCustomBenchmark = str_replace('PHP__INCLUDE_BENCHMARK_CODE_FOR_CHOSEN_ALGORITHMS__'.$sSubTest, $sFragment, $sCustomBenchmark);
}
if(file_put_contents('./benchmark_custom_strings.c', $sCustomBenchmark) == 0){
  die("The file benchmark_custom_strings.c could not be saved.\n");
}
echo "The file benchmark_custom_strings.c was generated.\n";

echo "Compiling.\n";
chdir('../..');
$iReturnCode = 0;
$arrSOutput = array();
exec('make build-benchmark-custom-strings', $arrSOutput, $iReturnCode);
if($iReturnCode !== 0){
  echo "The compilation failed.\n";
  foreach($arrSOutput as $sLine){
    echo $sLine, "\n";
  }
  die("The compilation failed.\n");
}
echo "The compilation succeeded.\n";

chdir('tests_benchmarks/benchmark_custom_strings/');
$iReturnCode = 0;
$arrSOutput = array();
exec('./benchmark_custom_strings.exe', $arrSOutput, $iReturnCode);
if($iReturnCode !== 0){
  echo "Custom benchmark failed.\n";
}
else{
  echo "Custom benchmark succeeded.\n";
}

$sLastResult = '';
foreach($arrSOutput as $sLine){
  echo $sLine, "\n";
  $sLastResult .= $sLine."\n";
}

if(file_put_contents('./last_result.txt', $sLastResult) == 0){
  die("The file last_result.txt could not be saved.\n");
}

$iReturnCode = 0;
$arrSOutput = array();
exec('php analyze_result.php ./last_result.txt', $arrSOutput, $iReturnCode);
if($iReturnCode !== 0){
  echo "Analysis failed.\n";
}
else{
  echo "Analysis succeeded.\n";
}

$sLastAnalysis = '';
foreach($arrSOutput as $sLine){
  echo $sLine, "\n";
  $sLastAnalysis .= $sLine."\n";
}

if(file_put_contents('./last_analysis.txt', $sLastAnalysis) == 0){
  die("The file last_analysis.txt could not be saved.\n");
}

?>
