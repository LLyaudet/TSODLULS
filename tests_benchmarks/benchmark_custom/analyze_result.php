<?php
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
  'uint16' => 4,
  'uint32' => 6,
  'uint64' => 8,
  'int8' => 10,
  'int16' => 12,
  'int32' => 14,
  'int64' => 16,
  'float' => 18,
  'double' => 20,
);

foreach($arrTests as $sTest => $iFirstColumn){
  echo "\nFor test $sTest : \n";

  foreach($arrSLines as $i => $sLine){
    $arrSValues = explode('|', $sLine);
    $iNumberOfElements = (int)$arrSValues[1];
    $fCurrentBestAlgo1 = max((float)$arrSValues[$iFirstColumn], 0.0000001);
    $fCurrentBestAlgo2 = max((float)$arrSValues[$iFirstColumn + 1], 0.0000001);
    echo " - with $iNumberOfElements elements : \n";
    if($fCurrentBestAlgo1 == $fCurrentBestAlgo2){
      echo "     it's a draw with $fCurrentBestAlgo2 seconds.\n";
    }
    elseif($fCurrentBestAlgo1 < $fCurrentBestAlgo2){
      echo "     algo1 wins over algo2\n",
           "     with $fCurrentBestAlgo1 seconds against $fCurrentBestAlgo2 (",
           ($fCurrentBestAlgo2 / $fCurrentBestAlgo1), " faster).\n";
    }
    else{
      echo "     algo2 wins over algo1\n",
           "     with $fCurrentBestAlgo2 seconds against $fCurrentBestAlgo1 (",
           ($fCurrentBestAlgo1 / $fCurrentBestAlgo2), " faster).\n";
    }
  }//end foreach($arrSLines as $i => $sLine)

}//end foreach($arrTests as $sTest => $arrColumns)


?>
