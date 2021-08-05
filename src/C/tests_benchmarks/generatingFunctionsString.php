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



$arrSubTests = array(
  'string_without_collation' => array(
      'array_substring' => 'p_os_strings',
      'size' => 'sizeof(t_TSODLULS_oString*)',
      'collation' => false,
  ),
  'string_with_collation' => array(
      'array_substring' => 'p_os_strings',
      'size' => 'sizeof(t_TSODLULS_oString*)',
      'collation' => true,
  ),
);



function getInitFragmentForDirect($sSubTest, $iResult, $bMacraff){
  return '
    for(i = 0; i < i_number_of_elements; ++i){
      arr_p_os_strings_result'.$iResult.'[i] = &(arr_os_strings_seed[i]);
    }
  ';
}//end function getInitFragmentForDirect()



function getInitFragmentForLongCells($sSubTest, $iResult, $bMacraff, $bWithBitLevelPadding){
  global $arrSubTests;

  if($arrSubTests[$sSubTest]['collation']){
    $sGetByte = 'convert_custom_collation_on_printable_ascii_char(arr_os_strings_seed[i].s_string[j])';
  }
  else{
    $sGetByte = '(uint8_t)arr_os_strings_seed[i].s_string[j]';
  }

  if($bWithBitLevelPadding){
    $sSizeAllocated = 'arr_os_strings_seed[i].i_string_size + ((arr_os_strings_seed[i].i_string_size + 7) / 8) + i_length_padding_increment';
    $sInit = 'i_current_bit_level_offset = 0;';
    if($bMacraff){
      $sAdding = '
          TSODLULS_add_bits_with_bit_level_offset__macraff(
              i_current_bit_level_offset,
              &(arr_cells[i]),
              '.$sGetByte.',//data
              8,
              i_current_bit_level_offset
          );
          TSODLULS_add_bits_with_bit_level_offset__macraff(
              i_current_bit_level_offset,
              &(arr_cells[i]),
              128,//padding
              1,
              i_current_bit_level_offset
          );'
      ;
    }
    else{
      $sAdding = '
          i_current_bit_level_offset = TSODLULS_add_bits_with_bit_level_offset(
              &(arr_cells[i]),
              '.$sGetByte.',//data
              8,
              i_current_bit_level_offset
          );
          i_current_bit_level_offset = TSODLULS_add_bits_with_bit_level_offset(
              &(arr_cells[i]),
              128,//padding
              1,
              i_current_bit_level_offset
          );'
      ;
    }
    $sAfter = '
      if(arr_os_strings_seed[i].i_string_size > 0){
        if(i_current_bit_level_offset == 0){
          arr_cells[i].s_key[arr_cells[i].i_key_size - 1] &= ~((uint8_t) 1);
        }
        else{
          arr_cells[i].s_key[arr_cells[i].i_key_size - 1] &= ~(((uint8_t) 1) << (8 - i_current_bit_level_offset));
        }
      }'
    ;
  }
  else{
    $sSizeAllocated = '(arr_os_strings_seed[i].i_string_size * i_length_padding_multiplicator) + i_length_padding_increment';
    $sInit = '';
    if($bMacraff){
      $sAdding = '
        TSODLULS_add_bytes_to_key_from_uint8__macraff(
            i_result,
            &(arr_cells[i]),
            '.$sGetByte.',
            i_number_of_lex_padding_bytes_before,
            i_number_of_contrelex_padding_bytes_before,
            i_number_of_lex_padding_bytes_after,
            i_number_of_contrelex_padding_bytes_after,
            1,
            0
        );'
      ;
    }
    else{
      $sAdding = '
        i_result = TSODLULS_add_bytes_to_key_from_uint8(
            &(arr_cells[i]),
            '.$sGetByte.',
            i_number_of_lex_padding_bytes_before,
            i_number_of_contrelex_padding_bytes_before,
            i_number_of_lex_padding_bytes_after,
            i_number_of_contrelex_padding_bytes_after,
            1,
            0
        );'
      ;
    }
    $sAfter = '
      if(arr_os_strings_seed[i].i_string_size > 0){
        i_result = TSODLULS_decrease_last_lex_padding(
          &(arr_cells[i]),
          i_number_of_lex_padding_bytes_after,
          i_number_of_contrelex_padding_bytes_after
        );
        if(i_result != 0){
          break;
        }
      }'
    ;
  }

  if($bMacraff){
    return '
    TSODLULS_init_array_of_elements__macraff(i_result, &arr_cells, i_number_of_elements);
    if(i_result != 0){
      break;
    }
    //printf("Avant\n");
    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_element_allocate_space_for_key__macraff(
        i_result,
        &(arr_cells[i]),
        '.$sSizeAllocated.'
      );
      if(i_result != 0){
        break;
      }
      if(i_min_length_of_string == 0){
        if(arr_os_strings_seed[i].i_string_size == 0){
          arr_cells[i].s_key[arr_cells[i].i_key_size++] = 0;
        }
        else{
          arr_cells[i].s_key[arr_cells[i].i_key_size++] = 1;
        }
      }
      '.$sInit.'
      for(j = 0; j < arr_os_strings_seed[i].i_string_size; ++j){
        '.$sAdding.'
        if(i_result != 0){
          break;
        }
      }
      if(i_result != 0){
        break;
      }
      '.$sAfter.'
      arr_cells[i].p_object = &(arr_os_strings_seed[i]);
      /*
      print_bits_for_key(&(arr_cells[i]));
      print_bits_for_string(&(arr_os_strings_seed[i]));
      */
    }
    if(i_result != 0){
      break;
    }';
  }
  else{
    return '
    i_result = TSODLULS_init_array_of_elements(&arr_cells, i_number_of_elements);
    if(i_result != 0){
      break;
    }
    //printf("Avant\n");
    for(i = 0; i < i_number_of_elements; ++i){
      i_result = TSODLULS_element_allocate_space_for_key(
        &(arr_cells[i]),
        '.$sSizeAllocated.'
      );
      if(i_result != 0){
        break;
      }
      if(i_min_length_of_string == 0){
        if(arr_os_strings_seed[i].i_string_size == 0){
          arr_cells[i].s_key[arr_cells[i].i_key_size++] = 0;
        }
        else{
          arr_cells[i].s_key[arr_cells[i].i_key_size++] = 1;
        }
      }
      '.$sInit.'
      for(j = 0; j < arr_os_strings_seed[i].i_string_size; ++j){
        '.$sAdding.'
        if(i_result != 0){
          break;
        }
      }
      if(i_result != 0){
        break;
      }
      '.$sAfter.'
      arr_cells[i].p_object = &(arr_os_strings_seed[i]);
      /*
      print_bits_for_key(&(arr_cells[i]));
      print_bits_for_string(&(arr_os_strings_seed[i]));
      print_bits_for(&(arr_cells[i].i_key_size), 8);
      printf("\n");
      */
    }
    if(i_result != 0){
      break;
    }';
  }
}//end function getInitFragmentForLongCells()



function getSortFunctionCall($arrDataAlgorithm, $sSubTest, $iResult){
  global $arrSubTests;

  $sFunctionCall = $arrDataAlgorithm['function'].'(';
  $sCellType = $arrDataAlgorithm['celltype'];
  switch($sCellType){
    case 'direct':
      $sFunctionCall .= 'arr_'.$arrSubTests[$sSubTest]['array_substring'].'_result'.$iResult;
    break;

    case 'long':
      $sFunctionCall .= 'arr_cells';
    break;

    default:
    die("Unknown celltype ".$sCellType."\n");
  }
  $sFunctionCall .= ', i_number_of_elements';
  if($arrDataAlgorithm['size'] !== false){
    switch($arrDataAlgorithm['size']){
      case 'direct':
        $sFunctionCall .= ', '.$arrSubTests[$sSubTest]['size'];
      break;

      case 'cell':
        switch($sCellType){
          case 'direct':
            $sFunctionCall .= ', '.$arrSubTests[$sSubTest]['size'];
          break;

          case 'long':
            $sFunctionCall .= ', sizeof(t_TSODLULS_sort_element)';
          break;

          default:
          die("Unknown celltype ".$sCellType."\n");
        }
      break;

      default:
      die("Unknown size type ".$arrDataAlgorithm['size']."\n");
    }
  }

  if($arrDataAlgorithm['comparison'] !== false){
    switch($arrDataAlgorithm['comparison']){
      case 'direct':
        $sFunctionCall .= ', (&compare_p_os_'.$sSubTest.')';
      break;

      case 'long':
        $sFunctionCall .= ', (&TSODLULS_compare_nextified_key_in_cell)';
      break;

      default:
      die("Unknown comparison type ".$arrDataAlgorithm['comparison']."\n");
    }
  }

  return $sFunctionCall.');';
}//end function getSortFunctionCall()



function getPostFragmentForLongCells($sSubTest, $iResult, $bMacraff){
  global $arrSubTests;

  return '
    //printf("Apres\n");
    for(i = 0; i < i_number_of_elements; ++i){
      arr_'.$arrSubTests[$sSubTest]['array_substring'].'_result'.$iResult.'[i] = arr_cells[i].p_object;
      /*
      print_bits_for_key(&(arr_cells[i]));
      print_bits_for_string(arr_'.$arrSubTests[$sSubTest]['array_substring'].'_result'.$iResult.'[i]);
      printf("\n");
      */
    }
    TSODLULS_free_keys_in_array_of_elements'.($bMacraff ? '__macraff' : '').'(arr_cells, i_number_of_elements);
    TSODLULS_free(arr_cells);
  ';
}//end function getPostFragmentForLongCells()



function getTestingFragmentFor($arrDataAlgorithm, $sSubTest, $bMacraff, $bWithBitLevelPadding){
  global $arrSubTests;

  $sFragment = '';
  $sCellType = $arrDataAlgorithm['celltype'];
  //Init
  switch($sCellType){
    case 'direct':
      $sFragment .= getInitFragmentForDirect($sSubTest, 2, $bMacraff);
    break;

    case 'long':
      $sFragment .= getInitFragmentForLongCells($sSubTest, 2, $bMacraff, $bWithBitLevelPadding);
    break;

    default:
    die("Unknown celltype ".$sCellType."\n");
  }
  //Sorting
  $sFragment .= "\n".getSortFunctionCall($arrDataAlgorithm, $sSubTest, 2);
  //Post-processing
  switch($sCellType){
    case 'direct':
      //nothing to do
    break;

    case 'long':
      $sFragment .= "\n".getPostFragmentForLongCells($sSubTest, 2, $bMacraff);
    break;

    default:
    die("Unknown celltype ".$sCellType."\n");
  }
  //Comparing
  $sFragment .= '
    for(i = 0; i < i_number_of_elements; ++i){
      if(arr_'.$arrSubTests[$sSubTest]['array_substring'].'_result2[i] != arr_'.$arrSubTests[$sSubTest]['array_substring'].'_result1[i]){
        //If the strings are not the same object, we must check wether they contain the same string
        if(compare_p_os_'.$sSubTest.'(
              &(arr_'.$arrSubTests[$sSubTest]['array_substring'].'_result2[i]),
              &(arr_'.$arrSubTests[$sSubTest]['array_substring'].'_result1[i])
           ) != 0
        ){
          print_bits_for_string(arr_'.$arrSubTests[$sSubTest]['array_substring'].'_result1[i]);
          print_bits_for_string(arr_'.$arrSubTests[$sSubTest]['array_substring'].'_result2[i]);
          printf("qsort direct and '.$arrDataAlgorithm['name']
               .($bMacraff ? ' (macraff)' : '').' gave different results ('.$sSubTest.')\n");
          i_result = -1;
          break;
        }
      }
    }
    if(i_result != 0){
      break;
    }
  ';
  return $sFragment;
}//end function getTestingFragmentFor()



function getComparingFragmentFor($arrDataAlgorithm, $sSubTest, $bMacraff, $bWithBitLevelPadding){
  $sFragment = '';
  $sCellType = $arrDataAlgorithm['celltype'];
  $sInitTimer = "clock_gettime(CLOCK_MONOTONIC, &start);";
  //Init
  switch($sCellType){
    case 'direct':
      $sFragment .= getInitFragmentForDirect($sSubTest, 1, $bMacraff);
      //Init fragment for direct is not counted as preparation time for fair comparison
      $sFragment .= "\n".$sInitTimer;
    break;

    case 'long':
      $sFragment .= $sInitTimer;
      $sFragment .= "\n".getInitFragmentForLongCells($sSubTest, 1, $bMacraff, $bWithBitLevelPadding);
    break;

    default:
    die("Unknown celltype ".$sCellType."\n");
  }
  //Sorting
  $sFragment .= "\n".getSortFunctionCall($arrDataAlgorithm, $sSubTest, 1);
  //Post-processing
  switch($sCellType){
    case 'direct':
      //nothing to do
    break;

    case 'long':
      $sFragment .= "\n".getPostFragmentForLongCells($sSubTest, 1, $bMacraff);
    break;

    default:
    die("Unknown celltype ".$sCellType."\n");
  }
  //Time result
  $sFragment .= "\nTSODLULS_code_fragment_print_time();";
  return $sFragment;
}//end function getComparingFragmentFor()



