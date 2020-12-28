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

©Copyright 2018-2020 Laurent Lyaudet
*/
/*
Explanations for this test:
- 1024 random uint64 are generated and for the following sets,
  it is tested that glibc quicksort direct and the TSODLULS sorting algorithm
  chosen with generateCustomTest.php yield the same output.
-- they are converted to 1024 random uint8
-- they are converted to 1024 random uint16
-- they are converted to 1024 random uint32
-- they are keeped as 1024 random uint64
-- they are converted to 1024 random int8
-- they are converted to 1024 random int16
-- they are converted to 1024 random int32
-- they are converted to 1024 random int64
-- they are converted to 1024 random floats
-- they are converted to 1024 random doubles
*/

#include "../test_functions.c"
#include "../../competitor_algorithms/TSODLULS__competitor.h"



int main(int argc, char *argv[]){

  int i_result = 0;
  unsigned int i_seed = time(0);
  srand(i_seed);
  printf("Seed: %u\n", i_seed);

  uint64_t i;

  //arrays
  size_t i_number_of_elements = 1024;
  uint64_t* arr_seeds64 = NULL;
  uint8_t* arr_ui_8_seed = NULL;
  uint8_t* arr_ui_8_result1 = NULL;
  uint8_t* arr_ui_8_result2 = NULL;
  uint16_t* arr_ui_16_seed = NULL;
  uint16_t* arr_ui_16_result1 = NULL;
  uint16_t* arr_ui_16_result2 = NULL;
  uint32_t* arr_ui_32_seed = NULL;
  uint32_t* arr_ui_32_result1 = NULL;
  uint32_t* arr_ui_32_result2 = NULL;
  uint64_t* arr_ui_64_seed = NULL;
  uint64_t* arr_ui_64_result1 = NULL;
  uint64_t* arr_ui_64_result2 = NULL;
  int8_t* arr_i_8_seed = NULL;
  int8_t* arr_i_8_result1 = NULL;
  int8_t* arr_i_8_result2 = NULL;
  int16_t* arr_i_16_seed = NULL;
  int16_t* arr_i_16_result1 = NULL;
  int16_t* arr_i_16_result2 = NULL;
  int32_t* arr_i_32_seed = NULL;
  int32_t* arr_i_32_result1 = NULL;
  int32_t* arr_i_32_result2 = NULL;
  int64_t* arr_i_64_seed = NULL;
  int64_t* arr_i_64_result1 = NULL;
  int64_t* arr_i_64_result2 = NULL;
  float* arr_f_float_seed = NULL;
  float* arr_f_float_result1 = NULL;
  float* arr_f_float_result2 = NULL;
  double* arr_f_double_seed = NULL;
  double* arr_f_double_result1 = NULL;
  double* arr_f_double_result2 = NULL;
  t_TSODLULS_sort_element* arr_cells = NULL;
  t_TSODLULS_sort_element__short* arr_cells__short = NULL;

  uint8_t ui8;
  uint16_t ui16;
  uint32_t ui32;
  uint32_t ui32_2;
  uint64_t ui64;
  uint64_t ui64_2;

  //copy-pasted from TSODLULS__macro.h
  union ieee754_float TSODLULS_macraff_ieee754_float;
  union ieee754_double TSODLULS_macraff_ieee754_double;
  uint8_t TSODLULS_macraff_ui8;
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

  do{
    printf("RAND_MAX is %d\n", RAND_MAX);
    if(RAND_MAX != INT32_MAX){
      printf("This is not the expected value. Results may have more bias.\n");
    }

    arr_seeds64 = calloc(i_number_of_elements, sizeof(uint64_t));
    if(arr_seeds64 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    //generating the seeds
    for(i = 0; i < i_number_of_elements; ++i){
      arr_seeds64[i] = get_random_uint64();
    }


    //sorting uint 8
    arr_ui_8_seed = calloc(i_number_of_elements, sizeof(uint8_t));
    if(arr_ui_8_seed == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    arr_ui_8_result1 = calloc(i_number_of_elements, sizeof(uint8_t));
    if(arr_ui_8_result1 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    arr_ui_8_result2 = calloc(i_number_of_elements, sizeof(uint8_t));
    if(arr_ui_8_result2 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    for(i = 0; i < i_number_of_elements; ++i){
      arr_ui_8_seed[i] = (uint8_t)arr_seeds64[i];
    }

    memcpy(
        arr_ui_8_result1,
        arr_ui_8_seed,
        i_number_of_elements * sizeof(uint8_t)
    );
    qsort(arr_ui_8_result1, i_number_of_elements, sizeof(uint8_t), (&TSODLULS_compare_uint8_direct));

    PHP__INCLUDE_TEST_CODE_FOR_CHOSEN_ALGORITHM__uint8

    TSODLULS_free(arr_ui_8_seed);
    TSODLULS_free(arr_ui_8_result1);
    TSODLULS_free(arr_ui_8_result2);


    //sorting uint 16
    arr_ui_16_seed = calloc(i_number_of_elements, sizeof(uint16_t));
    if(arr_ui_16_seed == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    arr_ui_16_result1 = calloc(i_number_of_elements, sizeof(uint16_t));
    if(arr_ui_16_result1 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    arr_ui_16_result2 = calloc(i_number_of_elements, sizeof(uint16_t));
    if(arr_ui_16_result2 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    for(i = 0; i < i_number_of_elements; ++i){
      arr_ui_16_seed[i] = (uint16_t)arr_seeds64[i];
    }

    memcpy(
        arr_ui_16_result1,
        arr_ui_16_seed,
        i_number_of_elements * sizeof(uint16_t)
    );
    qsort(arr_ui_16_result1, i_number_of_elements, sizeof(uint16_t), (&TSODLULS_compare_uint16_direct));

    PHP__INCLUDE_TEST_CODE_FOR_CHOSEN_ALGORITHM__uint16

    TSODLULS_free(arr_ui_16_seed);
    TSODLULS_free(arr_ui_16_result1);
    TSODLULS_free(arr_ui_16_result2);


    //sorting uint 32
    arr_ui_32_seed = calloc(i_number_of_elements, sizeof(uint32_t));
    if(arr_ui_32_seed == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    arr_ui_32_result1 = calloc(i_number_of_elements, sizeof(uint32_t));
    if(arr_ui_32_result1 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    arr_ui_32_result2 = calloc(i_number_of_elements, sizeof(uint32_t));
    if(arr_ui_32_result2 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    for(i = 0; i < i_number_of_elements; ++i){
      arr_ui_32_seed[i] = (uint32_t)arr_seeds64[i];
    }

    memcpy(
        arr_ui_32_result1,
        arr_ui_32_seed,
        i_number_of_elements * sizeof(uint32_t)
    );
    qsort(arr_ui_32_result1, i_number_of_elements, sizeof(uint32_t), (&TSODLULS_compare_uint32_direct));

    PHP__INCLUDE_TEST_CODE_FOR_CHOSEN_ALGORITHM__uint32

    TSODLULS_free(arr_ui_32_seed);
    TSODLULS_free(arr_ui_32_result1);
    TSODLULS_free(arr_ui_32_result2);


    //sorting uint 64
    arr_ui_64_seed = calloc(i_number_of_elements, sizeof(uint64_t));
    if(arr_ui_64_seed == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    arr_ui_64_result1 = calloc(i_number_of_elements, sizeof(uint64_t));
    if(arr_ui_64_result1 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    arr_ui_64_result2 = calloc(i_number_of_elements, sizeof(uint64_t));
    if(arr_ui_64_result2 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    for(i = 0; i < i_number_of_elements; ++i){
      arr_ui_64_seed[i] = (uint64_t)arr_seeds64[i];
    }

    memcpy(
        arr_ui_64_result1,
        arr_ui_64_seed,
        i_number_of_elements * sizeof(uint64_t)
    );
    qsort(arr_ui_64_result1, i_number_of_elements, sizeof(uint64_t), (&TSODLULS_compare_uint64_direct));

    PHP__INCLUDE_TEST_CODE_FOR_CHOSEN_ALGORITHM__uint64

    TSODLULS_free(arr_ui_64_seed);
    TSODLULS_free(arr_ui_64_result1);
    TSODLULS_free(arr_ui_64_result2);



    //sorting int 8
    arr_i_8_seed = calloc(i_number_of_elements, sizeof(int8_t));
    if(arr_i_8_seed == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    arr_i_8_result1 = calloc(i_number_of_elements, sizeof(int8_t));
    if(arr_i_8_result1 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    arr_i_8_result2 = calloc(i_number_of_elements, sizeof(int8_t));
    if(arr_i_8_result2 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    for(i = 0; i < i_number_of_elements; ++i){
      arr_i_8_seed[i] = TSODLULS_get_int8_from_uint8((uint8_t)arr_seeds64[i]);
    }

    memcpy(
        arr_i_8_result1,
        arr_i_8_seed,
        i_number_of_elements * sizeof(int8_t)
    );
    qsort(arr_i_8_result1, i_number_of_elements, sizeof(int8_t), (&TSODLULS_compare_int8_direct));

    PHP__INCLUDE_TEST_CODE_FOR_CHOSEN_ALGORITHM__int8

    TSODLULS_free(arr_i_8_seed);
    TSODLULS_free(arr_i_8_result1);
    TSODLULS_free(arr_i_8_result2);


    //sorting int 16
    arr_i_16_seed = calloc(i_number_of_elements, sizeof(int16_t));
    if(arr_i_16_seed == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    arr_i_16_result1 = calloc(i_number_of_elements, sizeof(int16_t));
    if(arr_i_16_result1 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    arr_i_16_result2 = calloc(i_number_of_elements, sizeof(int16_t));
    if(arr_i_16_result2 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    for(i = 0; i < i_number_of_elements; ++i){
      arr_i_16_seed[i] = TSODLULS_get_int16_from_uint16((uint16_t)arr_seeds64[i]);
    }

    memcpy(
        arr_i_16_result1,
        arr_i_16_seed,
        i_number_of_elements * sizeof(int16_t)
    );
    qsort(arr_i_16_result1, i_number_of_elements, sizeof(int16_t), (&TSODLULS_compare_int16_direct));

    PHP__INCLUDE_TEST_CODE_FOR_CHOSEN_ALGORITHM__int16

    TSODLULS_free(arr_i_16_seed);
    TSODLULS_free(arr_i_16_result1);
    TSODLULS_free(arr_i_16_result2);


    //sorting int 32
    arr_i_32_seed = calloc(i_number_of_elements, sizeof(int32_t));
    if(arr_i_32_seed == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    arr_i_32_result1 = calloc(i_number_of_elements, sizeof(int32_t));
    if(arr_i_32_result1 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    arr_i_32_result2 = calloc(i_number_of_elements, sizeof(int32_t));
    if(arr_i_32_result2 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    for(i = 0; i < i_number_of_elements; ++i){
      arr_i_32_seed[i] = TSODLULS_get_int32_from_uint32((uint32_t)arr_seeds64[i]);
    }

    memcpy(
        arr_i_32_result1,
        arr_i_32_seed,
        i_number_of_elements * sizeof(int32_t)
    );
    qsort(arr_i_32_result1, i_number_of_elements, sizeof(int32_t), (&TSODLULS_compare_int32_direct));

    PHP__INCLUDE_TEST_CODE_FOR_CHOSEN_ALGORITHM__int32

    TSODLULS_free(arr_i_32_seed);
    TSODLULS_free(arr_i_32_result1);
    TSODLULS_free(arr_i_32_result2);


    //sorting int 64
    arr_i_64_seed = calloc(i_number_of_elements, sizeof(int64_t));
    if(arr_i_64_seed == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    arr_i_64_result1 = calloc(i_number_of_elements, sizeof(int64_t));
    if(arr_i_64_result1 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    arr_i_64_result2 = calloc(i_number_of_elements, sizeof(int64_t));
    if(arr_i_64_result2 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    for(i = 0; i < i_number_of_elements; ++i){
      arr_i_64_seed[i] = TSODLULS_get_int64_from_uint64((uint64_t)arr_seeds64[i]);
    }

    memcpy(
        arr_i_64_result1,
        arr_i_64_seed,
        i_number_of_elements * sizeof(int64_t)
    );
    qsort(arr_i_64_result1, i_number_of_elements, sizeof(int64_t), (&TSODLULS_compare_int64_direct));

    PHP__INCLUDE_TEST_CODE_FOR_CHOSEN_ALGORITHM__int64

    TSODLULS_free(arr_i_64_seed);
    TSODLULS_free(arr_i_64_result1);
    TSODLULS_free(arr_i_64_result2);


    //sorting float
    arr_f_float_seed = calloc(i_number_of_elements, sizeof(float));
    if(arr_f_float_seed == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    arr_f_float_result1 = calloc(i_number_of_elements, sizeof(float));
    if(arr_f_float_result1 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    arr_f_float_result2 = calloc(i_number_of_elements, sizeof(float));
    if(arr_f_float_result2 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    for(i = 0; i < i_number_of_elements; ++i){
      arr_f_float_seed[i] = TSODLULS_get_float_from_uint((uint32_t)arr_seeds64[i]);
    }

    memcpy(
        arr_f_float_result1,
        arr_f_float_seed,
        i_number_of_elements * sizeof(float)
    );
    qsort(arr_f_float_result1, i_number_of_elements, sizeof(float), (&TSODLULS_compare_float_direct));

    PHP__INCLUDE_TEST_CODE_FOR_CHOSEN_ALGORITHM__float

    TSODLULS_free(arr_f_float_seed);
    TSODLULS_free(arr_f_float_result1);
    TSODLULS_free(arr_f_float_result2);


    //sorting doubles
    arr_f_double_seed = calloc(i_number_of_elements, sizeof(double));
    if(arr_f_double_seed == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    arr_f_double_result1 = calloc(i_number_of_elements, sizeof(double));
    if(arr_f_double_result1 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    arr_f_double_result2 = calloc(i_number_of_elements, sizeof(double));
    if(arr_f_double_result2 == NULL){
      i_result = I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
      break;
    }

    for(i = 0; i < i_number_of_elements; ++i){
      arr_f_double_seed[i] = TSODLULS_get_double_from_uint((uint64_t)arr_seeds64[i]);
    }

    memcpy(
        arr_f_double_result1,
        arr_f_double_seed,
        i_number_of_elements * sizeof(double)
    );
    qsort(arr_f_double_result1, i_number_of_elements, sizeof(double), (&TSODLULS_compare_double_direct));

    PHP__INCLUDE_TEST_CODE_FOR_CHOSEN_ALGORITHM__double

    TSODLULS_free(arr_f_double_seed);
    TSODLULS_free(arr_f_double_result1);
    TSODLULS_free(arr_f_double_result2);


    printf("Test custom succeeded.\n");
  }
  while(0);

  if(arr_seeds64 != NULL){ TSODLULS_free(arr_seeds64); }
  if(arr_ui_8_seed != NULL){ TSODLULS_free(arr_ui_8_seed); }
  if(arr_ui_8_result1 != NULL){ TSODLULS_free(arr_ui_8_result1); }
  if(arr_ui_8_result2 != NULL){ TSODLULS_free(arr_ui_8_result2); }
  if(arr_ui_16_seed != NULL){ TSODLULS_free(arr_ui_16_seed); }
  if(arr_ui_16_result1 != NULL){ TSODLULS_free(arr_ui_16_result1); }
  if(arr_ui_16_result2 != NULL){ TSODLULS_free(arr_ui_16_result2); }
  if(arr_ui_32_seed != NULL){ TSODLULS_free(arr_ui_32_seed); }
  if(arr_ui_32_result1 != NULL){ TSODLULS_free(arr_ui_32_result1); }
  if(arr_ui_32_result2 != NULL){ TSODLULS_free(arr_ui_32_result2); }
  if(arr_ui_64_seed != NULL){ TSODLULS_free(arr_ui_64_seed); }
  if(arr_ui_64_result1 != NULL){ TSODLULS_free(arr_ui_64_result1); }
  if(arr_ui_64_result2 != NULL){ TSODLULS_free(arr_ui_64_result2); }
  if(arr_i_8_seed != NULL){ TSODLULS_free(arr_i_8_seed); }
  if(arr_i_8_result1 != NULL){ TSODLULS_free(arr_i_8_result1); }
  if(arr_i_8_result2 != NULL){ TSODLULS_free(arr_i_8_result2); }
  if(arr_i_16_seed != NULL){ TSODLULS_free(arr_i_16_seed); }
  if(arr_i_16_result1 != NULL){ TSODLULS_free(arr_i_16_result1); }
  if(arr_i_16_result2 != NULL){ TSODLULS_free(arr_i_16_result2); }
  if(arr_i_32_seed != NULL){ TSODLULS_free(arr_i_32_seed); }
  if(arr_i_32_result1 != NULL){ TSODLULS_free(arr_i_32_result1); }
  if(arr_i_32_result2 != NULL){ TSODLULS_free(arr_i_32_result2); }
  if(arr_i_64_seed != NULL){ TSODLULS_free(arr_i_64_seed); }
  if(arr_i_64_result1 != NULL){ TSODLULS_free(arr_i_64_result1); }
  if(arr_i_64_result2 != NULL){ TSODLULS_free(arr_i_64_result2); }
  if(arr_f_float_seed != NULL){ TSODLULS_free(arr_f_float_seed); }
  if(arr_f_float_result1 != NULL){ TSODLULS_free(arr_f_float_result1); }
  if(arr_f_float_result2 != NULL){ TSODLULS_free(arr_f_float_result2); }
  if(arr_f_double_seed != NULL){ TSODLULS_free(arr_f_double_seed); }
  if(arr_f_double_result1 != NULL){ TSODLULS_free(arr_f_double_result1); }
  if(arr_f_double_result2 != NULL){ TSODLULS_free(arr_f_double_result2); }
  if(arr_cells != NULL){
    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key__macraff(&(arr_cells[i]));
    }
    TSODLULS_free(arr_cells);
  }
  if(arr_cells__short != NULL){
    TSODLULS_free(arr_cells__short);
  }

  return i_result;
}//end function main()



