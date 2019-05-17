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

©Copyright 2018-2019 Laurent Lyaudet
*/
/*
Explanations for this benchmark:
- n random strings are generated and time to sort these strings with two algorithms are compared.
  Sorting is done with two settings : raw string sorting, and sorting with collation that matches the alphabetical order.

Each sort is measured with the preparation time if needed.
n starts at value 1 and is multiplied by two until it reaches n_max.

*/

#include "../test_functions.c"
#include "../../competitor_algorithms/TSODLULS__competitor.h"


int main(int argc, char *argv[]){

  int i_result = 0;
  unsigned int i_seed = time(0);
  srand(i_seed);
  printf("Seed: %u\n", i_seed);

  size_t i;
  size_t j;
  size_t k;

  //arrays
  //size_t i_number_of_elements = 1;
  size_t i_number_of_elements = @iNumberOfElementsMin@;//Your choice
  //size_t i_number_of_elements_max = 1024;//2^10
  //size_t i_number_of_elements_max = 1048576;//2^20
  //size_t i_number_of_elements_max = 33554432;//2^25
  size_t i_number_of_elements_max = @iNumberOfElementsMax@;//Your choice
  t_TSODLULS_oString* arr_os_strings_seed = NULL;
  t_TSODLULS_oString** arr_p_os_strings_result1 = NULL;
  t_TSODLULS_sort_element* arr_cells = NULL;

  size_t i_min_length_of_string = @iMinLengthOfString@;
  size_t i_max_length_of_string = @iMaxLengthOfString@;
  size_t i_length_of_common_prefix = @iLengthOfCommonPrefix@;
  size_t i_length_padding_multiplicator = 1;
  size_t i_length_padding_increment = 0;
  int8_t i_number_of_lex_padding_bytes_before = 0;
  int8_t i_number_of_contrelex_padding_bytes_before = 0;
  int8_t i_number_of_lex_padding_bytes_after = 0;
  int8_t i_number_of_contrelex_padding_bytes_after = 0;
  t_TSODLULS_oString os_common_prefix;
  uint8_t i_current_bit_level_offset = 0;

  //copy-pasted from TSODLULS__macro.h
  union ieee754_float TSODLULS_macraff_ieee754_float;
  union ieee754_double TSODLULS_macraff_ieee754_double;
  uint8_t TSODLULS_macraff_ui8;
  uint8_t TSODLULS_macraff_ui8_2;
  uint8_t TSODLULS_macraff_ui8_3;
  uint16_t TSODLULS_macraff_ui16;
  uint32_t TSODLULS_macraff_ui32;
  uint64_t TSODLULS_macraff_ui64;
  int8_t TSODLULS_macraff_i8;
  int8_t TSODLULS_macraff_i8_2;
  int8_t TSODLULS_macraff_i8_3;
  int8_t TSODLULS_macraff_i8_4;
  int8_t TSODLULS_macraff_i8_5;
  int8_t TSODLULS_macraff_i8_6;
  int8_t TSODLULS_macraff_i8_7;
  int8_t TSODLULS_macraff_i8_8;
  int8_t TSODLULS_macraff_i8_9;
  int8_t TSODLULS_macraff_i8_10;
  int8_t TSODLULS_macraff_i8_11;
  int8_t TSODLULS_macraff_i8_12;
  int16_t TSODLULS_macraff_i16;
  int32_t TSODLULS_macraff_i32;
  int64_t TSODLULS_macraff_i64;
  int TSODLULS_macraff_i;
  size_t TSODLULS_macraff_isize;
  size_t TSODLULS_macraff_isize_2;
  size_t TSODLULS_macraff_isize_3;
  size_t TSODLULS_macraff_isize_4;
  t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element;
  t_TSODLULS_sort_element* TSODLULS_macraff_p_sort_element_2;
  t_TSODLULS_sort_element* TSODLULS_macraff_arr_elements;
  t_TSODLULS_sort_element** TSODLULS_macraff_p_arr_elements;
  t_TSODLULS_sort_element__short* TSODLULS_macraff_p_sort_element__short;
  t_TSODLULS_sort_element__short** TSODLULS_macraff_p_arr_elements__short;
  void* TSODLULS_macraff_p_void;

  struct timespec start, finish;
  double f_elapsed_time = 0.0;

  printf("RAND_MAX is %d\n", RAND_MAX);
  if(RAND_MAX != INT32_MAX){
    printf("This is not the expected value. Results may have more bias.\n");
  }

  printf(
      "|n               "
      //string without collation
      "| swoc algo1     "
      "| swoc algo2     "
      //string with collation
      "| swc algo1      "
      "| swc algo2      "
      "|\n"
  );
  for(i = 0; i < 5; ++i){
    printf("-----------------");
  }
  printf("-\n");

  if(i_min_length_of_string == 0){
    /*
    Not needed, because of depth 1 of the tree structured order definition (one lex node),
    it is sufficient to add a starting byte set to 0 (string of length 0) or 1 (longer string)
    i_number_of_lex_padding_bytes_before = -1;
    i_number_of_contrelex_padding_bytes_before = -1;
    i_length_padding_multiplicator += 1;
    */
    i_length_padding_increment = 1;
  }

  if(i_min_length_of_string != i_max_length_of_string){
    i_number_of_lex_padding_bytes_after = -1;
    i_number_of_contrelex_padding_bytes_after = -1;
    i_length_padding_multiplicator += 1;
  }

  if(i_length_of_common_prefix > 0){
    os_common_prefix.s_string = calloc(i_length_of_common_prefix, sizeof(char));
    if(os_common_prefix.s_string == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      goto free;
    }
    os_common_prefix.i_string_size = 0;
    os_common_prefix.i_allocated_size = i_length_of_common_prefix;
    for(j = 0; j < i_length_of_common_prefix; ++j){
      os_common_prefix.s_string[j] = get_random_printable_ascii_char();
      ++(os_common_prefix.i_string_size);
    }
  }

  while(i_number_of_elements <= i_number_of_elements_max){
    do{
      printf("|%016lu", i_number_of_elements);

      arr_os_strings_seed = calloc(i_number_of_elements, sizeof(t_TSODLULS_oString));
      if(arr_os_strings_seed == NULL){
        i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
        break;
      }

      //allocating the strings
      for(i = 0; i < i_number_of_elements; ++i){
        k = i_min_length_of_string;
        if(i_max_length_of_string > i_min_length_of_string){
          k += (rand() % (i_max_length_of_string - i_min_length_of_string + 1));
        }
        arr_os_strings_seed[i].s_string = calloc(k, sizeof(char));
        if(arr_os_strings_seed[i].s_string == NULL){
          i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
          break;
        }
        arr_os_strings_seed[i].i_string_size = 0;
        arr_os_strings_seed[i].i_allocated_size = k;
        //and filling each string
        for(j = 0; j < i_length_of_common_prefix; ++j){
          arr_os_strings_seed[i].s_string[j] = os_common_prefix.s_string[j];
          ++(arr_os_strings_seed[i].i_string_size);
        }

        for(j = arr_os_strings_seed[i].i_string_size; j < k; ++j){
          arr_os_strings_seed[i].s_string[j] = get_random_printable_ascii_char();
          ++(arr_os_strings_seed[i].i_string_size);
        }
      }
      if(i_result != 0){
        break;
      }


      //sorting without collation
      arr_p_os_strings_result1 = calloc(i_number_of_elements, sizeof(t_TSODLULS_oString*));
      if(arr_p_os_strings_result1 == NULL){
        i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
        break;
      }

      PHP__INCLUDE_BENCHMARK_CODE_FOR_CHOSEN_ALGORITHMS__string_without_collation

      TSODLULS_free(arr_p_os_strings_result1);


      //sorting with collation
      arr_p_os_strings_result1 = calloc(i_number_of_elements, sizeof(t_TSODLULS_oString*));
      if(arr_p_os_strings_result1 == NULL){
        i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
        break;
      }

      PHP__INCLUDE_BENCHMARK_CODE_FOR_CHOSEN_ALGORITHMS__string_with_collation

      TSODLULS_free(arr_p_os_strings_result1);

    }
    while(0);

    free_array_of_strings(&arr_os_strings_seed, i_number_of_elements);
    if(arr_p_os_strings_result1 != NULL){ TSODLULS_free(arr_p_os_strings_result1); }
    if(arr_cells != NULL){
      for(i = 0; i < i_number_of_elements; ++i){
        TSODLULS_free_key__macraff(&(arr_cells[i]));
      }
      TSODLULS_free(arr_cells);
    }

    i_number_of_elements = i_number_of_elements << 1;

    if(i_result != 0){
      break;
    }

    printf("|\n");
    for(i = 0; i < 5; ++i){
      printf("-----------------");
    }
    printf("-\n");
  }//end while(i_number_of_elements <= i_number_of_elements_max)

  free:
  if(i_length_of_common_prefix > 0
    && os_common_prefix.s_string != NULL
  ){
    TSODLULS_free(os_common_prefix.s_string);
  }

  return i_result;
}//end function main()



