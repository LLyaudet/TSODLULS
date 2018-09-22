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
/*
Explanations for this test:
- 1024 random uint64 are generated and for the following sets,
  it is tested that glibc quicksort (direct and on TSODLULS cells)
  and TSODLULS sort yield the same result for sorting.
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



int main(int argc, char *argv[]){

  int i_result = 0;
  unsigned int i_seed = time(0);
  //i_seed = 1534188456;//bug with floats
  //i_seed = 1534274833;//bug with doubles
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

    i_result = TSODLULS_init_array_of_elements(&arr_cells, i_number_of_elements);
    if(i_result != 0){
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

    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
      i_result = TSODLULS_add_bytes_to_key_from_uint8(&(arr_cells[i]), arr_ui_8_seed[i], 0, 0);
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_ui_8_seed[i]);
    }
    if(i_result != 0){
      break;
    }
    qsort(arr_cells, i_number_of_elements, sizeof(t_TSODLULS_sort_element), (&TSODLULS_compare_uint8_in_cell));
    for(i = 0; i < i_number_of_elements; ++i){
      arr_ui_8_result2[i] = *((uint8_t*)(arr_cells[i].p_object));
      if(arr_ui_8_result2[i] != arr_ui_8_result1[i]){
        printf("qsort direct and in_cell gave different results (uint8)\n");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }

    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
      i_result = TSODLULS_add_bytes_to_key_from_uint8(&(arr_cells[i]), arr_ui_8_seed[i], 0, 0);
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_ui_8_seed[i]);
    }
    if(i_result != 0){
      break;
    }
    TSODLULS_sort(arr_cells, i_number_of_elements);
    for(i = 0; i < i_number_of_elements; ++i){
      arr_ui_8_result2[i] = *((uint8_t*)(arr_cells[i].p_object));
      if(arr_ui_8_result2[i] != arr_ui_8_result1[i]){
        printf("qsort and TSODLULS sort gave different results (uint8)\n");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }

    free(arr_ui_8_seed);
    arr_ui_8_seed = NULL;
    free(arr_ui_8_result1);
    arr_ui_8_result1 = NULL;
    free(arr_ui_8_result2);
    arr_ui_8_result2 = NULL;


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

    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
      i_result = TSODLULS_add_bytes_to_key_from_uint16(&(arr_cells[i]), arr_ui_16_seed[i], 0, 0);
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_ui_16_seed[i]);
    }
    if(i_result != 0){
      break;
    }
    qsort(arr_cells, i_number_of_elements, sizeof(t_TSODLULS_sort_element), (&TSODLULS_compare_uint16_in_cell));
    for(i = 0; i < i_number_of_elements; ++i){
      arr_ui_16_result2[i] = *((uint16_t*)(arr_cells[i].p_object));
      if(arr_ui_16_result2[i] != arr_ui_16_result1[i]){
        printf("qsort direct and in_cell gave different results (uint16)\n");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }

    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
      i_result = TSODLULS_add_bytes_to_key_from_uint16(&(arr_cells[i]), arr_ui_16_seed[i], 0, 0);
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_ui_16_seed[i]);
    }
    if(i_result != 0){
      break;
    }
    TSODLULS_sort(arr_cells, i_number_of_elements);
    for(i = 0; i < i_number_of_elements; ++i){
      arr_ui_16_result2[i] = *((uint16_t*)(arr_cells[i].p_object));
      if(arr_ui_16_result2[i] != arr_ui_16_result1[i]){
        printf("qsort and TSODLULS sort gave different results (uint16)\n");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }

    free(arr_ui_16_seed);
    arr_ui_16_seed = NULL;
    free(arr_ui_16_result1);
    arr_ui_16_result1 = NULL;
    free(arr_ui_16_result2);
    arr_ui_16_result2 = NULL;


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

    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
      i_result = TSODLULS_add_bytes_to_key_from_uint32(&(arr_cells[i]), arr_ui_32_seed[i], 0, 0);
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_ui_32_seed[i]);
    }
    if(i_result != 0){
      break;
    }
    qsort(arr_cells, i_number_of_elements, sizeof(t_TSODLULS_sort_element), (&TSODLULS_compare_uint32_in_cell));
    for(i = 0; i < i_number_of_elements; ++i){
      arr_ui_32_result2[i] = *((uint32_t*)(arr_cells[i].p_object));
      if(arr_ui_32_result2[i] != arr_ui_32_result1[i]){
        printf("qsort direct and in_cell gave different results (uint32)\n");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }

    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
      i_result = TSODLULS_add_bytes_to_key_from_uint32(&(arr_cells[i]), arr_ui_32_seed[i], 0, 0);
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_ui_32_seed[i]);
    }
    if(i_result != 0){
      break;
    }
    TSODLULS_sort(arr_cells, i_number_of_elements);
    for(i = 0; i < i_number_of_elements; ++i){
      arr_ui_32_result2[i] = *((uint32_t*)(arr_cells[i].p_object));
      if(arr_ui_32_result2[i] != arr_ui_32_result1[i]){
        printf("qsort and TSODLULS sort gave different results (uint32)\n");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }

    free(arr_ui_32_seed);
    arr_ui_32_seed = NULL;
    free(arr_ui_32_result1);
    arr_ui_32_result1 = NULL;
    free(arr_ui_32_result2);
    arr_ui_32_result2 = NULL;


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

    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
      i_result = TSODLULS_add_bytes_to_key_from_uint64(&(arr_cells[i]), arr_ui_64_seed[i], 0, 0);
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_ui_64_seed[i]);
    }
    if(i_result != 0){
      break;
    }
    qsort(arr_cells, i_number_of_elements, sizeof(t_TSODLULS_sort_element), (&TSODLULS_compare_uint64_in_cell));
    for(i = 0; i < i_number_of_elements; ++i){
      arr_ui_64_result2[i] = *((uint64_t*)(arr_cells[i].p_object));
      if(arr_ui_64_result2[i] != arr_ui_64_result1[i]){
        printf("qsort direct and in_cell gave different results (uint64)\n");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }

    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
      i_result = TSODLULS_add_bytes_to_key_from_uint64(&(arr_cells[i]), arr_ui_64_seed[i], 0, 0);
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_ui_64_seed[i]);
    }
    if(i_result != 0){
      break;
    }
    TSODLULS_sort(arr_cells, i_number_of_elements);
    for(i = 0; i < i_number_of_elements; ++i){
      arr_ui_64_result2[i] = *((uint64_t*)(arr_cells[i].p_object));
      if(arr_ui_64_result2[i] != arr_ui_64_result1[i]){
        printf("qsort and TSODLULS sort gave different results (uint64)\n");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }

    free(arr_ui_64_seed);
    arr_ui_64_seed = NULL;
    free(arr_ui_64_result1);
    arr_ui_64_result1 = NULL;
    free(arr_ui_64_result2);
    arr_ui_64_result2 = NULL;



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

    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
      i_result = TSODLULS_add_bytes_to_key_from_uint8(
          &(arr_cells[i]),
          TSODLULS_get_uint8_from_int8(arr_i_8_seed[i]),
          0,
          0
      );
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_i_8_seed[i]);
    }
    if(i_result != 0){
      break;
    }
    qsort(arr_cells, i_number_of_elements, sizeof(t_TSODLULS_sort_element), (&TSODLULS_compare_uint8_in_cell));
    for(i = 0; i < i_number_of_elements; ++i){
      arr_i_8_result2[i] = *((int8_t*)(arr_cells[i].p_object));
      if(arr_i_8_result2[i] != arr_i_8_result1[i]){
        printf("qsort direct and in_cell gave different results (int8)\n");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }

    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
      i_result = TSODLULS_add_bytes_to_key_from_uint8(
          &(arr_cells[i]),
          TSODLULS_get_uint8_from_int8(arr_i_8_seed[i]),
          0,
          0
      );
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_i_8_seed[i]);
    }
    if(i_result != 0){
      break;
    }
    TSODLULS_sort(arr_cells, i_number_of_elements);
    for(i = 0; i < i_number_of_elements; ++i){
      arr_i_8_result2[i] = *((int8_t*)(arr_cells[i].p_object));
      if(arr_i_8_result2[i] != arr_i_8_result1[i]){
        printf("qsort and TSODLULS sort gave different results (int8)\n");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }

    free(arr_i_8_seed);
    arr_i_8_seed = NULL;
    free(arr_i_8_result1);
    arr_i_8_result1 = NULL;
    free(arr_i_8_result2);
    arr_i_8_result2 = NULL;


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

    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
      i_result = TSODLULS_add_bytes_to_key_from_uint16(
          &(arr_cells[i]),
          TSODLULS_get_uint16_from_int16(arr_i_16_seed[i]),
          0,
          0
      );
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_i_16_seed[i]);
    }
    if(i_result != 0){
      break;
    }
    qsort(arr_cells, i_number_of_elements, sizeof(t_TSODLULS_sort_element), (&TSODLULS_compare_uint16_in_cell));
    for(i = 0; i < i_number_of_elements; ++i){
      arr_i_16_result2[i] = *((int16_t*)(arr_cells[i].p_object));
      if(arr_i_16_result2[i] != arr_i_16_result1[i]){
        printf("qsort direct and in_cell gave different results (int16)\n");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }

    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
      i_result = TSODLULS_add_bytes_to_key_from_uint16(
          &(arr_cells[i]),
          TSODLULS_get_uint16_from_int16(arr_i_16_seed[i]),
          0,
          0
      );
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_i_16_seed[i]);
    }
    if(i_result != 0){
      break;
    }
    TSODLULS_sort(arr_cells, i_number_of_elements);
    for(i = 0; i < i_number_of_elements; ++i){
      arr_i_16_result2[i] = *((int16_t*)(arr_cells[i].p_object));
      if(arr_i_16_result2[i] != arr_i_16_result1[i]){
        printf("qsort and TSODLULS sort gave different results (int16)\n");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }

    free(arr_i_16_seed);
    arr_i_16_seed = NULL;
    free(arr_i_16_result1);
    arr_i_16_result1 = NULL;
    free(arr_i_16_result2);
    arr_i_16_result2 = NULL;


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

    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
      i_result = TSODLULS_add_bytes_to_key_from_uint32(
          &(arr_cells[i]),
          TSODLULS_get_uint32_from_int32(arr_i_32_seed[i]),
          0,
          0
      );
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_i_32_seed[i]);
    }
    if(i_result != 0){
      break;
    }
    qsort(arr_cells, i_number_of_elements, sizeof(t_TSODLULS_sort_element), (&TSODLULS_compare_uint32_in_cell));
    for(i = 0; i < i_number_of_elements; ++i){
      arr_i_32_result2[i] = *((int32_t*)(arr_cells[i].p_object));
      if(arr_i_32_result2[i] != arr_i_32_result1[i]){
        printf("qsort direct and in_cell gave different results (int32)\n");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }

    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
      i_result = TSODLULS_add_bytes_to_key_from_uint32(
          &(arr_cells[i]),
          TSODLULS_get_uint32_from_int32(arr_i_32_seed[i]),
          0,
          0
      );
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_i_32_seed[i]);
    }
    if(i_result != 0){
      break;
    }
    TSODLULS_sort(arr_cells, i_number_of_elements);
    for(i = 0; i < i_number_of_elements; ++i){
      arr_i_32_result2[i] = *((int32_t*)(arr_cells[i].p_object));
      if(arr_i_32_result2[i] != arr_i_32_result1[i]){
        printf("qsort and TSODLULS sort gave different results (int32)\n");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }

    free(arr_i_32_seed);
    arr_i_32_seed = NULL;
    free(arr_i_32_result1);
    arr_i_32_result1 = NULL;
    free(arr_i_32_result2);
    arr_i_32_result2 = NULL;


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

    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
      i_result = TSODLULS_add_bytes_to_key_from_uint64(
          &(arr_cells[i]),
          TSODLULS_get_uint64_from_int64(arr_i_64_seed[i]),
          0,
          0
      );
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_i_64_seed[i]);
    }
    if(i_result != 0){
      break;
    }
    qsort(arr_cells, i_number_of_elements, sizeof(t_TSODLULS_sort_element), (&TSODLULS_compare_uint64_in_cell));
    for(i = 0; i < i_number_of_elements; ++i){
      arr_i_64_result2[i] = *((int64_t*)(arr_cells[i].p_object));
      if(arr_i_64_result2[i] != arr_i_64_result1[i]){
        printf("qsort direct and in_cell gave different results (int64)\n");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }

    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
      i_result = TSODLULS_add_bytes_to_key_from_uint64(
          &(arr_cells[i]),
          TSODLULS_get_uint64_from_int64(arr_i_64_seed[i]),
          0,
          0
      );
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_i_64_seed[i]);
    }
    if(i_result != 0){
      break;
    }
    TSODLULS_sort(arr_cells, i_number_of_elements);
    for(i = 0; i < i_number_of_elements; ++i){
      arr_i_64_result2[i] = *((int64_t*)(arr_cells[i].p_object));
      if(arr_i_64_result2[i] != arr_i_64_result1[i]){
        printf("qsort and TSODLULS sort gave different results (int64)\n");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }

    free(arr_i_64_seed);
    arr_i_64_seed = NULL;
    free(arr_i_64_result1);
    arr_i_64_result1 = NULL;
    free(arr_i_64_result2);
    arr_i_64_result2 = NULL;


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

    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
      i_result = TSODLULS_add_bytes_to_key_from_uint32(
          &(arr_cells[i]),
          TSODLULS_get_uint_from_float(arr_f_float_seed[i]),
          0,
          0
      );
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_f_float_seed[i]);
    }
    if(i_result != 0){
      break;
    }
    qsort(arr_cells, i_number_of_elements, sizeof(t_TSODLULS_sort_element), (&TSODLULS_compare_uint32_in_cell));
    for(i = 0; i < i_number_of_elements; ++i){
      arr_f_float_result2[i] = *((float*)(arr_cells[i].p_object));
      //printf("%f %f\n", arr_f_float_result1[i], arr_f_float_result2[i]);
      //if(arr_f_float_result2[i] != arr_f_float_result1[i]){
      //any comparison with nan or -nan float numbers will say that they are different
      //You have to compare using the bijection with uint32
      if(TSODLULS_get_uint_from_float(arr_f_float_result2[i])
           != TSODLULS_get_uint_from_float(arr_f_float_result1[i])
      ){
        printf("qsort direct and in_cell gave different results (float)\n");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }

    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
      i_result = TSODLULS_add_bytes_to_key_from_uint32(
          &(arr_cells[i]),
          TSODLULS_get_uint_from_float(arr_f_float_seed[i]),
          0,
          0
      );
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_f_float_seed[i]);
    }
    if(i_result != 0){
      break;
    }
    TSODLULS_sort(arr_cells, i_number_of_elements);
    for(i = 0; i < i_number_of_elements; ++i){
      arr_f_float_result2[i] = *((float*)(arr_cells[i].p_object));
      //if(arr_f_float_result2[i] != arr_f_float_result1[i]){
      //any comparison with nan or -nan float numbers will say that they are different
      //You have to compare using the bijection with uint32
      if(TSODLULS_get_uint_from_float(arr_f_float_result2[i])
           != TSODLULS_get_uint_from_float(arr_f_float_result1[i])
      ){
        printf("qsort and TSODLULS sort gave different results (float)\n");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }

    free(arr_f_float_seed);
    arr_f_float_seed = NULL;
    free(arr_f_float_result1);
    arr_f_float_result1 = NULL;
    free(arr_f_float_result2);
    arr_f_float_result2 = NULL;


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

    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
      i_result = TSODLULS_add_bytes_to_key_from_uint64(
          &(arr_cells[i]),
          TSODLULS_get_uint_from_double(arr_f_double_seed[i]),
          0,
          0
      );
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_f_double_seed[i]);
    }
    if(i_result != 0){
      break;
    }
    qsort(arr_cells, i_number_of_elements, sizeof(t_TSODLULS_sort_element), (&TSODLULS_compare_uint64_in_cell));
    for(i = 0; i < i_number_of_elements; ++i){
      arr_f_double_result2[i] = *((double*)(arr_cells[i].p_object));
      //if(arr_f_double_result2[i] != arr_f_double_result1[i]){
      //any comparison with nan or -nan double numbers will say that they are different
      //You have to compare using the bijection with uint64
      if(TSODLULS_get_uint_from_double(arr_f_double_result2[i])
           != TSODLULS_get_uint_from_double(arr_f_double_result1[i])
      ){
        printf("qsort direct and in_cell gave different results (double)\n");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }

    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
      i_result = TSODLULS_add_bytes_to_key_from_uint64(
          &(arr_cells[i]),
          TSODLULS_get_uint_from_double(arr_f_double_seed[i]),
          0,
          0
      );
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_f_double_seed[i]);
    }
    if(i_result != 0){
      break;
    }
    TSODLULS_sort(arr_cells, i_number_of_elements);
    for(i = 0; i < i_number_of_elements; ++i){
      arr_f_double_result2[i] = *((double*)(arr_cells[i].p_object));
      //if(arr_f_double_result2[i] != arr_f_double_result1[i]){
      //any comparison with nan or -nan double numbers will say that they are different
      //You have to compare using the bijection with uint64
      if(TSODLULS_get_uint_from_double(arr_f_double_result2[i])
           != TSODLULS_get_uint_from_double(arr_f_double_result1[i])
      ){
        printf("qsort and TSODLULS sort gave different results (double)\n");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }

    free(arr_f_double_seed);
    arr_f_double_seed = NULL;
    free(arr_f_double_result1);
    arr_f_double_result1 = NULL;
    free(arr_f_double_result2);
    arr_f_double_result2 = NULL;


    printf("Test 2 succeded.\n");
  }
  while(0);

  if(arr_seeds64 != NULL){ free(arr_seeds64); }
  if(arr_ui_8_seed != NULL){ free(arr_ui_8_seed); }
  if(arr_ui_8_result1 != NULL){ free(arr_ui_8_result1); }
  if(arr_ui_8_result2 != NULL){ free(arr_ui_8_result2); }
  if(arr_ui_16_seed != NULL){ free(arr_ui_16_seed); }
  if(arr_ui_16_result1 != NULL){ free(arr_ui_16_result1); }
  if(arr_ui_16_result2 != NULL){ free(arr_ui_16_result2); }
  if(arr_ui_32_seed != NULL){ free(arr_ui_32_seed); }
  if(arr_ui_32_result1 != NULL){ free(arr_ui_32_result1); }
  if(arr_ui_32_result2 != NULL){ free(arr_ui_32_result2); }
  if(arr_ui_64_seed != NULL){ free(arr_ui_64_seed); }
  if(arr_ui_64_result1 != NULL){ free(arr_ui_64_result1); }
  if(arr_ui_64_result2 != NULL){ free(arr_ui_64_result2); }
  if(arr_i_8_seed != NULL){ free(arr_i_8_seed); }
  if(arr_i_8_result1 != NULL){ free(arr_i_8_result1); }
  if(arr_i_8_result2 != NULL){ free(arr_i_8_result2); }
  if(arr_i_16_seed != NULL){ free(arr_i_16_seed); }
  if(arr_i_16_result1 != NULL){ free(arr_i_16_result1); }
  if(arr_i_16_result2 != NULL){ free(arr_i_16_result2); }
  if(arr_i_32_seed != NULL){ free(arr_i_32_seed); }
  if(arr_i_32_result1 != NULL){ free(arr_i_32_result1); }
  if(arr_i_32_result2 != NULL){ free(arr_i_32_result2); }
  if(arr_i_64_seed != NULL){ free(arr_i_64_seed); }
  if(arr_i_64_result1 != NULL){ free(arr_i_64_result1); }
  if(arr_i_64_result2 != NULL){ free(arr_i_64_result2); }
  if(arr_f_float_seed != NULL){ free(arr_f_float_seed); }
  if(arr_f_float_result1 != NULL){ free(arr_f_float_result1); }
  if(arr_f_float_result2 != NULL){ free(arr_f_float_result2); }
  if(arr_f_double_seed != NULL){ free(arr_f_double_seed); }
  if(arr_f_double_result1 != NULL){ free(arr_f_double_result1); }
  if(arr_f_double_result2 != NULL){ free(arr_f_double_result2); }
  if(arr_cells != NULL){
    for(i = 0; i < i_number_of_elements; ++i){
      TSODLULS_free_key(&(arr_cells[i]));
    }
    free(arr_cells);
  }

  return i_result;
}//end function main()



