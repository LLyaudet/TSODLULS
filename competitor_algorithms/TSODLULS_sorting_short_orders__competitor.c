/*
This file is part of TSODLULS library.

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

#include "TSODLULS__competitor.h"



//------------------------------------------------------------------------------------
//External functions
//------------------------------------------------------------------------------------
/**
 * Sorting functions for short nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 */
int TSODLULS_sort_radix8_count__short__mark1(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
){
  int i_number_of_distinct_bytes = 0;
  size_t arr_counts[256];
  size_t arr_offsets[256];
  uint8_t i_current_octet = 0;
  uint64_t i_current_key = 0;
  t_TSODLULS_sort_element__short* arr_elements_copy = NULL;
  t_TSODLULS_radix_instance current_instance;
  t_TSODLULS_radix_instance* arr_instances = NULL;
  size_t i_max_number_of_instances = 0;
  size_t i_current_instance = 0;
  void* p_for_realloc = NULL;
  size_t i_size_for_realloc = 0;

  if(i_number_of_elements < 2){
    return 0;//nothing to sort
  }

  if(i_max_length <= 0){
    return I_ERROR__MAX_LENGTH_SHOULD_BE_POSITIVE;
  }

  if(i_max_length > 8){
    return I_ERROR__MAX_LENGTH_SHOULD_BE_AT_MOST_8;
  }

  current_instance.i_offset_first = 0;
  current_instance.i_offset_last = i_number_of_elements - 1;
  current_instance.i_depth = 0;
  current_instance.b_copy = 0;

  arr_elements_copy = calloc(i_number_of_elements, sizeof(t_TSODLULS_sort_element__short));
  if(arr_elements_copy == NULL){
    return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
  }

  arr_instances = calloc(8, sizeof(t_TSODLULS_radix_instance));
  if(arr_instances == NULL){
    TSODLULS_free(arr_elements_copy);
    return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
  }
  i_max_number_of_instances =  8;

  while(1){
    //we initialize the counters
    for(int i = 0; i < 256; ++i){
      arr_counts[i] = 0;
      arr_offsets[i] = 0;
    }
    //we count the bytes with a certain value
    if(current_instance.b_copy){
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_key = arr_elements_copy[i].i_key;
        //if(current_instance.i_depth < 7){
          i_current_key = i_current_key >> ((7 - current_instance.i_depth) * 8);
        //}
        i_current_octet = ((uint8_t) (i_current_key % 256));
        ++arr_counts[i_current_octet];
      }
    }
    else{
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_key = arr_elements[i].i_key;
        i_current_key = i_current_key >> ((7 - current_instance.i_depth) * 8);
        i_current_octet = ((uint8_t) (i_current_key % 256));
        ++arr_counts[i_current_octet];
      }
    }
    //we deduce the offsets
    i_number_of_distinct_bytes = 0;
    for(int i = 0; i < 255; ++i){
      arr_offsets[i+1] = arr_offsets[i] + arr_counts[i];
      if(arr_counts[i] > 0){
        ++i_number_of_distinct_bytes;
      }
    }
    if(arr_counts[255] > 0){
      ++i_number_of_distinct_bytes;
    }

    if(i_number_of_distinct_bytes == 1){
      ++current_instance.i_depth;
      //if we are done sorting this instance and all deeper subinstances
      if(i_max_length <= current_instance.i_depth){
        if(current_instance.b_copy){
          memcpy(
            &(arr_elements[current_instance.i_offset_first]),
            &(arr_elements_copy[current_instance.i_offset_first]),
            (current_instance.i_offset_last - current_instance.i_offset_first + 1) * sizeof(t_TSODLULS_sort_element__short)
          );
        }
        if(i_current_instance == 0){
          break;
        }
        current_instance = arr_instances[--i_current_instance];
      }
      continue;
    }

    if(current_instance.b_copy){
      //sorting
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_key = arr_elements_copy[i].i_key;
        i_current_key = i_current_key >> ((7 - current_instance.i_depth) * 8);
        i_current_octet = ((uint8_t) (i_current_key % 256));
        arr_elements[current_instance.i_offset_first + arr_offsets[i_current_octet]] = arr_elements_copy[i];
        ++arr_offsets[i_current_octet];
      }
      //instances creation
      for(int i = 0; i < 256; ++i){
        if(arr_counts[i] > 1//nothing to do for one element, result is in original array
          //for nextified strings this test can be done on only one element
          && i_max_length > current_instance.i_depth + 1
        ){
          //we allocate more space for the new instance if necessary
          if(i_current_instance == i_max_number_of_instances - 1){
            i_size_for_realloc = i_max_number_of_instances * 2 * sizeof(t_TSODLULS_radix_instance);
            //if we cannot allocate more
            if(i_size_for_realloc <= i_max_number_of_instances * sizeof(t_TSODLULS_radix_instance)){
              TSODLULS_free(arr_elements_copy);
              TSODLULS_free(arr_instances);
              return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
            }
            p_for_realloc = realloc(arr_instances, i_size_for_realloc);
            if(p_for_realloc == NULL){
              TSODLULS_free(arr_elements_copy);
              TSODLULS_free(arr_instances);
              return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
            }
            arr_instances = (t_TSODLULS_radix_instance*)p_for_realloc;
            i_max_number_of_instances *= 2;
          }
          arr_instances[i_current_instance].i_offset_first = current_instance.i_offset_first
                                                           + arr_offsets[i] - arr_counts[i];
          arr_instances[i_current_instance].i_offset_last = current_instance.i_offset_first
                                                          + arr_offsets[i] - 1;
          arr_instances[i_current_instance].i_depth = current_instance.i_depth + 1;
          arr_instances[i_current_instance].b_copy = 0;
          ++i_current_instance;
        }
      }//end for(int i = 0; i < 256; ++i)
    }
    else{
      //sorting
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_key = arr_elements[i].i_key;
        i_current_key = i_current_key >> ((7 - current_instance.i_depth) * 8);
        i_current_octet = ((uint8_t) (i_current_key % 256));
        arr_elements_copy[current_instance.i_offset_first + arr_offsets[i_current_octet]] = arr_elements[i];
        ++arr_offsets[i_current_octet];
      }
      //instances creation
      for(int i = 0; i < 256; ++i){
        if(arr_counts[i] > 1
          //for nextified strings this test can be done on only one element
          && i_max_length > current_instance.i_depth + 1
        ){
          //we allocate more space for the new instance if necessary
          if(i_current_instance == i_max_number_of_instances - 1){
            i_size_for_realloc = i_max_number_of_instances * 2 * sizeof(t_TSODLULS_radix_instance);
            //if we cannot allocate more
            if(i_size_for_realloc <= i_max_number_of_instances * sizeof(t_TSODLULS_radix_instance)){
              TSODLULS_free(arr_elements_copy);
              TSODLULS_free(arr_instances);
              return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
            }
            p_for_realloc = realloc(arr_instances, i_size_for_realloc);
            if(p_for_realloc == NULL){
              TSODLULS_free(arr_elements_copy);
              TSODLULS_free(arr_instances);
              return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
            }
            arr_instances = (t_TSODLULS_radix_instance*)p_for_realloc;
            i_max_number_of_instances *= 2;
          }
          arr_instances[i_current_instance].i_offset_first = current_instance.i_offset_first
                                                           + arr_offsets[i] - arr_counts[i];
          arr_instances[i_current_instance].i_offset_last = current_instance.i_offset_first
                                                          + arr_offsets[i] - 1;
          arr_instances[i_current_instance].i_depth = current_instance.i_depth + 1;
          arr_instances[i_current_instance].b_copy = 1;
          ++i_current_instance;
        }
        else if(arr_counts[i] > 0){//we still need to copy data in original array
          memcpy(
            &(arr_elements[current_instance.i_offset_first + arr_offsets[i] - arr_counts[i]]),
            &(arr_elements_copy[current_instance.i_offset_first + arr_offsets[i] - arr_counts[i]]),
            arr_counts[i] * sizeof(t_TSODLULS_sort_element__short)
          );
        }
      }//end for(int i = 0; i < 256; ++i)
    }

    if(i_current_instance == 0){
      break;
    }

    current_instance = arr_instances[--i_current_instance];
  }//end while(true)

  TSODLULS_free(arr_elements_copy);
  TSODLULS_free(arr_instances);
  return 0;
}//end function TSODLULS_sort_radix8_count__short__mark1()



/**
 * Sorting functions for short nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * A variant with single memory allocation, but it requires a lot of it.
 * It is slightly faster for 32 and 64 bits datatypes, but greatly slower for 8 bits datatypes.
 */
int TSODLULS_sort_radix8_count__short__mark2(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
){
  int i_number_of_distinct_bytes = 0;
  size_t arr_counts[256];
  size_t arr_offsets[256];
  uint8_t i_current_octet = 0;
  uint64_t i_current_key = 0;
  t_TSODLULS_sort_element__short* arr_elements_copy = NULL;
  t_TSODLULS_radix_instance current_instance;
  t_TSODLULS_radix_instance* arr_instances = NULL;
  //size_t i_max_number_of_instances = 0;
  size_t i_current_instance = 0;
  //void* p_for_realloc = NULL;
  //size_t i_size_for_realloc = 0;

  if(i_number_of_elements < 2){
    return 0;//nothing to sort
  }

  if(i_max_length <= 0){
    return I_ERROR__MAX_LENGTH_SHOULD_BE_POSITIVE;
  }

  if(i_max_length > 8){
    return I_ERROR__MAX_LENGTH_SHOULD_BE_AT_MOST_8;
  }

  current_instance.i_offset_first = 0;
  current_instance.i_offset_last = i_number_of_elements - 1;
  current_instance.i_depth = 0;
  current_instance.b_copy = 0;

  arr_elements_copy = calloc(i_number_of_elements, sizeof(t_TSODLULS_sort_element__short));
  if(arr_elements_copy == NULL){
    return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
  }

  //This is depth first in a tree of degree 256 and depth 7, so we will not need more that 7 * 256
  arr_instances = calloc(7 * 256, sizeof(t_TSODLULS_radix_instance));
  if(arr_instances == NULL){
    TSODLULS_free(arr_elements_copy);
    return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
  }
  //i_max_number_of_instances =  8;

  while(1){
    //we initialize the counters
    for(int i = 0; i < 256; ++i){
      arr_counts[i] = 0;
      arr_offsets[i] = 0;
    }
    //we count the bytes with a certain value
    if(current_instance.b_copy){
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_key = arr_elements_copy[i].i_key;
        //if(current_instance.i_depth < 7){
          i_current_key = i_current_key >> ((7 - current_instance.i_depth) * 8);
        //}
        i_current_octet = ((uint8_t) (i_current_key % 256));
        ++arr_counts[i_current_octet];
      }
    }
    else{
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_key = arr_elements[i].i_key;
        i_current_key = i_current_key >> ((7 - current_instance.i_depth) * 8);
        i_current_octet = ((uint8_t) (i_current_key % 256));
        ++arr_counts[i_current_octet];
      }
    }
    //we deduce the offsets
    i_number_of_distinct_bytes = 0;
    for(int i = 0; i < 255; ++i){
      arr_offsets[i+1] = arr_offsets[i] + arr_counts[i];
      if(arr_counts[i] > 0){
        ++i_number_of_distinct_bytes;
      }
    }
    if(arr_counts[255] > 0){
      ++i_number_of_distinct_bytes;
    }

    if(i_number_of_distinct_bytes == 1){
      ++current_instance.i_depth;
      //if we are done sorting this instance and all deeper subinstances
      if(i_max_length <= current_instance.i_depth){
        if(current_instance.b_copy){
          memcpy(
            &(arr_elements[current_instance.i_offset_first]),
            &(arr_elements_copy[current_instance.i_offset_first]),
            (current_instance.i_offset_last - current_instance.i_offset_first + 1) * sizeof(t_TSODLULS_sort_element__short)
          );
        }
        if(i_current_instance == 0){
          break;
        }
        current_instance = arr_instances[--i_current_instance];
      }
      continue;
    }

    if(current_instance.b_copy){
      //sorting
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_key = arr_elements_copy[i].i_key;
        i_current_key = i_current_key >> ((7 - current_instance.i_depth) * 8);
        i_current_octet = ((uint8_t) (i_current_key % 256));
        arr_elements[current_instance.i_offset_first + arr_offsets[i_current_octet]] = arr_elements_copy[i];
        ++arr_offsets[i_current_octet];
      }
      //instances creation
      for(int i = 0; i < 256; ++i){
        if(arr_counts[i] > 1//nothing to do for one element, result is in original array
          //for nextified strings this test can be done on only one element
          && i_max_length > current_instance.i_depth + 1
        ){
          //we allocate more space for the new instance if necessary
          /*not needed anymore
          if(i_current_instance == i_max_number_of_instances - 1){
            i_size_for_realloc = i_max_number_of_instances * 2 * sizeof(t_TSODLULS_radix_instance);
            //if we cannot allocate more
            if(i_size_for_realloc <= i_max_number_of_instances * sizeof(t_TSODLULS_radix_instance)){
              TSODLULS_free(arr_elements_copy);
              TSODLULS_free(arr_instances);
              return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
            }
            p_for_realloc = realloc(arr_instances, i_size_for_realloc);
            if(p_for_realloc == NULL){
              TSODLULS_free(arr_elements_copy);
              TSODLULS_free(arr_instances);
              return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
            }
            arr_instances = (t_TSODLULS_radix_instance*)p_for_realloc;
            i_max_number_of_instances *= 2;
          }
          */
          arr_instances[i_current_instance].i_offset_first = current_instance.i_offset_first
                                                           + arr_offsets[i] - arr_counts[i];
          arr_instances[i_current_instance].i_offset_last = current_instance.i_offset_first
                                                          + arr_offsets[i] - 1;
          arr_instances[i_current_instance].i_depth = current_instance.i_depth + 1;
          arr_instances[i_current_instance].b_copy = 0;
          ++i_current_instance;
        }
      }//end for(int i = 0; i < 256; ++i)
    }
    else{
      //sorting
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_key = arr_elements[i].i_key;
        i_current_key = i_current_key >> ((7 - current_instance.i_depth) * 8);
        i_current_octet = ((uint8_t) (i_current_key % 256));
        arr_elements_copy[current_instance.i_offset_first + arr_offsets[i_current_octet]] = arr_elements[i];
        ++arr_offsets[i_current_octet];
      }
      //instances creation
      for(int i = 0; i < 256; ++i){
        if(arr_counts[i] > 1
          //for nextified strings this test can be done on only one element
          && i_max_length > current_instance.i_depth + 1
        ){
          //we allocate more space for the new instance if necessary
          /*not needed anymore
          if(i_current_instance == i_max_number_of_instances - 1){
            i_size_for_realloc = i_max_number_of_instances * 2 * sizeof(t_TSODLULS_radix_instance);
            //if we cannot allocate more
            if(i_size_for_realloc <= i_max_number_of_instances * sizeof(t_TSODLULS_radix_instance)){
              TSODLULS_free(arr_elements_copy);
              TSODLULS_free(arr_instances);
              return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
            }
            p_for_realloc = realloc(arr_instances, i_size_for_realloc);
            if(p_for_realloc == NULL){
              TSODLULS_free(arr_elements_copy);
              TSODLULS_free(arr_instances);
              return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
            }
            arr_instances = (t_TSODLULS_radix_instance*)p_for_realloc;
            i_max_number_of_instances *= 2;
          }
          */
          arr_instances[i_current_instance].i_offset_first = current_instance.i_offset_first
                                                           + arr_offsets[i] - arr_counts[i];
          arr_instances[i_current_instance].i_offset_last = current_instance.i_offset_first
                                                          + arr_offsets[i] - 1;
          arr_instances[i_current_instance].i_depth = current_instance.i_depth + 1;
          arr_instances[i_current_instance].b_copy = 1;
          ++i_current_instance;
        }
        else if(arr_counts[i] > 0){//we still need to copy data in original array
          memcpy(
            &(arr_elements[current_instance.i_offset_first + arr_offsets[i] - arr_counts[i]]),
            &(arr_elements_copy[current_instance.i_offset_first + arr_offsets[i] - arr_counts[i]]),
            arr_counts[i] * sizeof(t_TSODLULS_sort_element__short)
          );
        }
      }//end for(int i = 0; i < 256; ++i)
    }

    if(i_current_instance == 0){
      break;
    }

    current_instance = arr_instances[--i_current_instance];
  }//end while(true)

  TSODLULS_free(arr_elements_copy);
  TSODLULS_free(arr_instances);
  return 0;
}//end function TSODLULS_sort_radix8_count__short__mark2()



/**
 * Sorting functions for short nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * A variant with single memory allocation adapted to the max-depth.
 * It is slightly faster for 32 and 64 bits datatypes.
 */
int TSODLULS_sort_radix8_count__short__mark3(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
){
  int i_number_of_distinct_bytes = 0;
  size_t arr_counts[256];
  size_t arr_offsets[256];
  uint8_t i_current_octet = 0;
  uint64_t i_current_key = 0;
  t_TSODLULS_sort_element__short* arr_elements_copy = NULL;
  t_TSODLULS_radix_instance current_instance;
  t_TSODLULS_radix_instance* arr_instances = NULL;
  size_t i_current_instance = 0;

  if(i_number_of_elements < 2){
    return 0;//nothing to sort
  }

  if(i_max_length <= 0){
    return I_ERROR__MAX_LENGTH_SHOULD_BE_POSITIVE;
  }

  if(i_max_length > 8){
    return I_ERROR__MAX_LENGTH_SHOULD_BE_AT_MOST_8;
  }

  current_instance.i_offset_first = 0;
  current_instance.i_offset_last = i_number_of_elements - 1;
  current_instance.i_depth = 0;
  current_instance.b_copy = 0;

  arr_elements_copy = calloc(i_number_of_elements, sizeof(t_TSODLULS_sort_element__short));
  if(arr_elements_copy == NULL){
    return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
  }

  //This is depth first in a tree of degree 256 and depth at most i_max_length - 1,
  //so we will not need more that (i_max_length - 1) * 256
  if(i_max_length - 1 > 0){
    arr_instances = calloc((i_max_length - 1) * 256, sizeof(t_TSODLULS_radix_instance));
    if(arr_instances == NULL){
      TSODLULS_free(arr_elements_copy);
      return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
    }
  }

  while(1){
    //we initialize the counters
    for(int i = 0; i < 256; ++i){
      arr_counts[i] = 0;
      arr_offsets[i] = 0;
    }
    //we count the bytes with a certain value
    if(current_instance.b_copy){
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_key = arr_elements_copy[i].i_key;
        //if(current_instance.i_depth < 7){
          i_current_key = i_current_key >> ((7 - current_instance.i_depth) * 8);
        //}
        i_current_octet = ((uint8_t) (i_current_key % 256));
        ++arr_counts[i_current_octet];
      }
    }
    else{
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_key = arr_elements[i].i_key;
        i_current_key = i_current_key >> ((7 - current_instance.i_depth) * 8);
        i_current_octet = ((uint8_t) (i_current_key % 256));
        ++arr_counts[i_current_octet];
      }
    }
    //we deduce the offsets
    i_number_of_distinct_bytes = 0;
    for(int i = 0; i < 255; ++i){
      arr_offsets[i+1] = arr_offsets[i] + arr_counts[i];
      if(arr_counts[i] > 0){
        ++i_number_of_distinct_bytes;
      }
    }
    if(arr_counts[255] > 0){
      ++i_number_of_distinct_bytes;
    }

    if(i_number_of_distinct_bytes == 1){
      ++current_instance.i_depth;
      //if we are done sorting this instance and all deeper subinstances
      if(i_max_length <= current_instance.i_depth){
        if(current_instance.b_copy){
          memcpy(
            &(arr_elements[current_instance.i_offset_first]),
            &(arr_elements_copy[current_instance.i_offset_first]),
            (current_instance.i_offset_last - current_instance.i_offset_first + 1) * sizeof(t_TSODLULS_sort_element__short)
          );
        }
        if(i_current_instance == 0){
          break;
        }
        current_instance = arr_instances[--i_current_instance];
      }
      continue;
    }

    if(current_instance.b_copy){
      //sorting
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_key = arr_elements_copy[i].i_key;
        i_current_key = i_current_key >> ((7 - current_instance.i_depth) * 8);
        i_current_octet = ((uint8_t) (i_current_key % 256));
        arr_elements[current_instance.i_offset_first + arr_offsets[i_current_octet]] = arr_elements_copy[i];
        ++arr_offsets[i_current_octet];
      }
      //instances creation
      for(int i = 0; i < 256; ++i){
        if(arr_counts[i] > 1//nothing to do for one element, result is in original array
          //for nextified strings this test can be done on only one element
          && i_max_length > current_instance.i_depth + 1
        ){
          arr_instances[i_current_instance].i_offset_first = current_instance.i_offset_first
                                                           + arr_offsets[i] - arr_counts[i];
          arr_instances[i_current_instance].i_offset_last = current_instance.i_offset_first
                                                          + arr_offsets[i] - 1;
          arr_instances[i_current_instance].i_depth = current_instance.i_depth + 1;
          arr_instances[i_current_instance].b_copy = 0;
          ++i_current_instance;
        }
      }//end for(int i = 0; i < 256; ++i)
    }
    else{
      //sorting
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_key = arr_elements[i].i_key;
        i_current_key = i_current_key >> ((7 - current_instance.i_depth) * 8);
        i_current_octet = ((uint8_t) (i_current_key % 256));
        arr_elements_copy[current_instance.i_offset_first + arr_offsets[i_current_octet]] = arr_elements[i];
        ++arr_offsets[i_current_octet];
      }
      //instances creation
      for(int i = 0; i < 256; ++i){
        if(arr_counts[i] > 1
          //for nextified strings this test can be done on only one element
          && i_max_length > current_instance.i_depth + 1
        ){
          arr_instances[i_current_instance].i_offset_first = current_instance.i_offset_first
                                                           + arr_offsets[i] - arr_counts[i];
          arr_instances[i_current_instance].i_offset_last = current_instance.i_offset_first
                                                          + arr_offsets[i] - 1;
          arr_instances[i_current_instance].i_depth = current_instance.i_depth + 1;
          arr_instances[i_current_instance].b_copy = 1;
          ++i_current_instance;
        }
        else if(arr_counts[i] > 0){//we still need to copy data in original array
          memcpy(
            &(arr_elements[current_instance.i_offset_first + arr_offsets[i] - arr_counts[i]]),
            &(arr_elements_copy[current_instance.i_offset_first + arr_offsets[i] - arr_counts[i]]),
            arr_counts[i] * sizeof(t_TSODLULS_sort_element__short)
          );
        }
      }//end for(int i = 0; i < 256; ++i)
    }

    if(i_current_instance == 0){
      break;
    }

    current_instance = arr_instances[--i_current_instance];
  }//end while(true)

  TSODLULS_free(arr_elements_copy);
  TSODLULS_free(arr_instances);
  return 0;
}//end function TSODLULS_sort_radix8_count__short__mark3()



/**
 * Sorting functions for short nextified strings
 * A sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements is below some threshold, it uses glibc qsort.
 */
int TSODLULS_sort_radix8_count_qsort__short(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
){
  int i_number_of_distinct_bytes = 0;
  size_t arr_counts[256];
  size_t arr_offsets[256];
  uint8_t i_current_octet = 0;
  uint64_t i_current_key = 0;
  t_TSODLULS_sort_element__short* arr_elements_copy = NULL;
  t_TSODLULS_radix_instance current_instance;
  t_TSODLULS_radix_instance* arr_instances = NULL;
  size_t i_max_number_of_instances = 0;
  size_t i_current_instance = 0;
  void* p_for_realloc = NULL;
  size_t i_size_for_realloc = 0;
  size_t i_threshold = 0;
  int i_result = 0;

  if(i_number_of_elements < 2){
    return 0;//nothing to sort
  }

  if(i_max_length <= 0){
    return I_ERROR__MAX_LENGTH_SHOULD_BE_POSITIVE;
  }

  if(i_max_length > 8){
    return I_ERROR__MAX_LENGTH_SHOULD_BE_AT_MOST_8;
  }

  //The values below are not finely tuned.
  //My experimental approach was not very precise.
  //It was based on the custom benchmark between
  //TSODLULS_sort_radix8_count__short and TSODLULS_qsort_inlined__short.
  //We looked at the results of uint8 and int8 for case 1;
  //we looked at the results of uint16 and int16 for case 2;
  //we looked at the results of uint32 and int32 and floats for case 4;
  //there is a "best result" of radix at 8192
  //(best = worse before and worse after, when you look at powers of two, that's not the real inflexion point)
  //we looked at the results of uint64 and int64 and doubles for case 8;
  //we observed the same "best result".
  //First thresholds we used were (0,) 16, 2048, 3072, 4096, 4096, 4096, 4096, 4096
  #define SET_THRESHOLD(i_number_of_bytes_to_read) \
  switch(i_number_of_bytes_to_read){\
    case 0:\
     i_threshold = 0;/*Threshold will not be used anyway*/\
    break;\
    case 1:\
     i_threshold = 16;\
    break;\
    case 2:\
     i_threshold = 2048;\
    break;\
    case 3:\
     i_threshold = 3072;\
    break;\
    case 4:\
     i_threshold = 4096;\
    break;\
    case 5:\
     i_threshold = 4096;\
    break;\
    case 6:\
     i_threshold = 4096;\
    break;\
    case 7:\
     i_threshold = 4096;\
    break;\
    case 8:\
     i_threshold = 4096;\
    break;\
    default:\
      return I_ERROR__MAX_LENGTH_SHOULD_BE_AT_MOST_8;\
  }

  SET_THRESHOLD(i_max_length)
  if(i_number_of_elements <= i_threshold){
    return TSODLULS_qsort_inlined__short(arr_elements, i_number_of_elements);
  }

  current_instance.i_offset_first = 0;
  current_instance.i_offset_last = i_number_of_elements - 1;
  current_instance.i_depth = 0;
  current_instance.b_copy = 0;

  arr_elements_copy = calloc(i_number_of_elements, sizeof(t_TSODLULS_sort_element__short));
  if(arr_elements_copy == NULL){
    return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
  }

  arr_instances = calloc(8, sizeof(t_TSODLULS_radix_instance));
  if(arr_instances == NULL){
    TSODLULS_free(arr_elements_copy);
    return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
  }
  i_max_number_of_instances =  8;

  while(1){
    //we initialize the counters
    for(int i = 0; i < 256; ++i){
      arr_counts[i] = 0;
      arr_offsets[i] = 0;
    }
    //we count the bytes with a certain value
    if(current_instance.b_copy){
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_key = arr_elements_copy[i].i_key;
        //if(current_instance.i_depth < 7){
          i_current_key = i_current_key >> ((7 - current_instance.i_depth) * 8);
        //}
        i_current_octet = ((uint8_t) (i_current_key % 256));
        ++arr_counts[i_current_octet];
      }
    }
    else{
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_key = arr_elements[i].i_key;
        i_current_key = i_current_key >> ((7 - current_instance.i_depth) * 8);
        i_current_octet = ((uint8_t) (i_current_key % 256));
        ++arr_counts[i_current_octet];
      }
    }
    //we deduce the offsets
    i_number_of_distinct_bytes = 0;
    for(int i = 0; i < 255; ++i){
      arr_offsets[i+1] = arr_offsets[i] + arr_counts[i];
      if(arr_counts[i] > 0){
        ++i_number_of_distinct_bytes;
      }
    }
    if(arr_counts[255] > 0){
      ++i_number_of_distinct_bytes;
    }

    SET_THRESHOLD(i_max_length - current_instance.i_depth)

    if(i_number_of_distinct_bytes == 1){
      ++current_instance.i_depth;
      //if we are done sorting this instance and all deeper subinstances
      if(i_max_length <= current_instance.i_depth
        //Or if this should be done by qsort
        || (current_instance.i_offset_last - current_instance.i_offset_first + 1) <= i_threshold
      ){
        if(current_instance.b_copy){
          memcpy(
            &(arr_elements[current_instance.i_offset_first]),
            &(arr_elements_copy[current_instance.i_offset_first]),
            (current_instance.i_offset_last - current_instance.i_offset_first + 1) * sizeof(t_TSODLULS_sort_element__short)
          );
        }
        if(i_max_length > current_instance.i_depth){
          i_result = TSODLULS_qsort_inlined__short(
              &(arr_elements[current_instance.i_offset_first]),
              (current_instance.i_offset_last - current_instance.i_offset_first + 1)
          );
          if(i_result != 0){
            break;
          }
        }
        if(i_current_instance == 0){
          break;
        }
        current_instance = arr_instances[--i_current_instance];
      }
      continue;
    }

    if(current_instance.b_copy){
      //sorting
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_key = arr_elements_copy[i].i_key;
        i_current_key = i_current_key >> ((7 - current_instance.i_depth) * 8);
        i_current_octet = ((uint8_t) (i_current_key % 256));
        arr_elements[current_instance.i_offset_first + arr_offsets[i_current_octet]] = arr_elements_copy[i];
        ++arr_offsets[i_current_octet];
      }
      //instances creation
      for(int i = 0; i < 256; ++i){
        if(arr_counts[i] > 1//nothing to do for one element, result is in original array
          //for nextified strings this test can be done on only one element
          && i_max_length > current_instance.i_depth + 1
        ){

          //We branch for qsort if needed
          if(arr_counts[i] <= i_threshold){
            i_result = TSODLULS_qsort_inlined__short(
                &(arr_elements[current_instance.i_offset_first + arr_offsets[i] - arr_counts[i]]),
                arr_counts[i]
            );
            if(i_result != 0){
              break;
            }
          }

          //we allocate more space for the new instance if necessary
          if(i_current_instance == i_max_number_of_instances - 1){
            i_size_for_realloc = i_max_number_of_instances * 2 * sizeof(t_TSODLULS_radix_instance);
            //if we cannot allocate more
            if(i_size_for_realloc <= i_max_number_of_instances * sizeof(t_TSODLULS_radix_instance)){
              TSODLULS_free(arr_elements_copy);
              TSODLULS_free(arr_instances);
              return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
            }
            p_for_realloc = realloc(arr_instances, i_size_for_realloc);
            if(p_for_realloc == NULL){
              TSODLULS_free(arr_elements_copy);
              TSODLULS_free(arr_instances);
              return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
            }
            arr_instances = (t_TSODLULS_radix_instance*)p_for_realloc;
            i_max_number_of_instances *= 2;
          }
          arr_instances[i_current_instance].i_offset_first = current_instance.i_offset_first
                                                           + arr_offsets[i] - arr_counts[i];
          arr_instances[i_current_instance].i_offset_last = current_instance.i_offset_first
                                                          + arr_offsets[i] - 1;
          arr_instances[i_current_instance].i_depth = current_instance.i_depth + 1;
          arr_instances[i_current_instance].b_copy = 0;
          ++i_current_instance;
        }
      }//end for(int i = 0; i < 256; ++i)
    }
    else{
      //sorting
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_key = arr_elements[i].i_key;
        i_current_key = i_current_key >> ((7 - current_instance.i_depth) * 8);
        i_current_octet = ((uint8_t) (i_current_key % 256));
        arr_elements_copy[current_instance.i_offset_first + arr_offsets[i_current_octet]] = arr_elements[i];
        ++arr_offsets[i_current_octet];
      }
      //instances creation
      for(int i = 0; i < 256; ++i){
        if(arr_counts[i] > 1
          //for nextified strings this test can be done on only one element
          && i_max_length > current_instance.i_depth + 1
        ){

          //We branch for qsort if needed
          if(arr_counts[i] <= i_threshold){
            memcpy(
              &(arr_elements[current_instance.i_offset_first + arr_offsets[i] - arr_counts[i]]),
              &(arr_elements_copy[current_instance.i_offset_first + arr_offsets[i] - arr_counts[i]]),
              arr_counts[i] * sizeof(t_TSODLULS_sort_element__short)
            );
            i_result = TSODLULS_qsort_inlined__short(
                &(arr_elements[current_instance.i_offset_first + arr_offsets[i] - arr_counts[i]]),
                arr_counts[i]
            );
            if(i_result != 0){
              break;
            }
          }

          //we allocate more space for the new instance if necessary
          if(i_current_instance == i_max_number_of_instances - 1){
            i_size_for_realloc = i_max_number_of_instances * 2 * sizeof(t_TSODLULS_radix_instance);
            //if we cannot allocate more
            if(i_size_for_realloc <= i_max_number_of_instances * sizeof(t_TSODLULS_radix_instance)){
              TSODLULS_free(arr_elements_copy);
              TSODLULS_free(arr_instances);
              return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
            }
            p_for_realloc = realloc(arr_instances, i_size_for_realloc);
            if(p_for_realloc == NULL){
              TSODLULS_free(arr_elements_copy);
              TSODLULS_free(arr_instances);
              return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
            }
            arr_instances = (t_TSODLULS_radix_instance*)p_for_realloc;
            i_max_number_of_instances *= 2;
          }
          arr_instances[i_current_instance].i_offset_first = current_instance.i_offset_first
                                                           + arr_offsets[i] - arr_counts[i];
          arr_instances[i_current_instance].i_offset_last = current_instance.i_offset_first
                                                          + arr_offsets[i] - 1;
          arr_instances[i_current_instance].i_depth = current_instance.i_depth + 1;
          arr_instances[i_current_instance].b_copy = 1;
          ++i_current_instance;
        }
        else if(arr_counts[i] > 0){//we still need to copy data in original array
          memcpy(
            &(arr_elements[current_instance.i_offset_first + arr_offsets[i] - arr_counts[i]]),
            &(arr_elements_copy[current_instance.i_offset_first + arr_offsets[i] - arr_counts[i]]),
            arr_counts[i] * sizeof(t_TSODLULS_sort_element__short)
          );
        }
      }//end for(int i = 0; i < 256; ++i)
    }

    if(i_current_instance == 0){
      break;
    }

    current_instance = arr_instances[--i_current_instance];
  }//end while(true)

  TSODLULS_free(arr_elements_copy);
  TSODLULS_free(arr_instances);
  return i_result;
}//end function TSODLULS_sort_radix8_count_qsort__short()



/**
 * Sorting functions for short nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements to sort is at most 5, we use insertion sort
 * A variant with single memory allocation adapted to the max-depth.
 * This is the current best algorithm and it is a stable one :)
 */
int TSODLULS_sort_radix8_count_insertion__short__mark1(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
){
  int i_number_of_distinct_bytes = 0;
  size_t arr_counts[256];
  size_t arr_offsets[256];
  uint8_t i_current_octet = 0;
  uint64_t i_current_key = 0;
  t_TSODLULS_sort_element__short* arr_elements_copy = NULL;
  t_TSODLULS_radix_instance current_instance;
  t_TSODLULS_radix_instance* arr_instances = NULL;
  size_t i_current_instance = 0;
  t_TSODLULS_sort_element__short tmp_cell;

  if(i_number_of_elements < 2){
    return 0;//nothing to sort
  }

  if(i_number_of_elements <= 5){
    goto label_insertion_sort;
  }

  if(i_max_length <= 0){
    return I_ERROR__MAX_LENGTH_SHOULD_BE_POSITIVE;
  }

  if(i_max_length > 8){
    return I_ERROR__MAX_LENGTH_SHOULD_BE_AT_MOST_8;
  }

  current_instance.i_offset_first = 0;
  current_instance.i_offset_last = i_number_of_elements - 1;
  current_instance.i_depth = 0;
  current_instance.b_copy = 0;

  arr_elements_copy = calloc(i_number_of_elements, sizeof(t_TSODLULS_sort_element__short));
  if(arr_elements_copy == NULL){
    return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
  }

#define min(x, y) ((x) < (y) ? (x) : (y))

  //This is depth first in a tree of degree 256 and depth at most i_max_length - 1,
  //so we will not need more that (i_max_length - 1) * 256
  //We also doesn't need more than i_number_of_elements / 6 because of the use of insertion sort
  if(i_max_length - 1 > 0){
    arr_instances = calloc(
        min((i_max_length - 1) * 256, i_number_of_elements / 6),
        sizeof(t_TSODLULS_radix_instance)
    );
    if(arr_instances == NULL){
      TSODLULS_free(arr_elements_copy);
      return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
    }
  }

  while(1){
    //we initialize the counters
    for(int i = 0; i < 256; ++i){
      arr_counts[i] = 0;
      arr_offsets[i] = 0;
    }
    //we count the bytes with a certain value
    if(current_instance.b_copy){
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_key = arr_elements_copy[i].i_key;
        //if(current_instance.i_depth < 7){
          i_current_key = i_current_key >> ((7 - current_instance.i_depth) * 8);
        //}
        i_current_octet = ((uint8_t) (i_current_key % 256));
        ++arr_counts[i_current_octet];
      }
    }
    else{
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_key = arr_elements[i].i_key;
        i_current_key = i_current_key >> ((7 - current_instance.i_depth) * 8);
        i_current_octet = ((uint8_t) (i_current_key % 256));
        ++arr_counts[i_current_octet];
      }
    }
    //we deduce the offsets
    i_number_of_distinct_bytes = 0;
    for(int i = 0; i < 255; ++i){
      arr_offsets[i+1] = arr_offsets[i] + arr_counts[i];
      if(arr_counts[i] > 0){
        ++i_number_of_distinct_bytes;
      }
    }
    if(arr_counts[255] > 0){
      ++i_number_of_distinct_bytes;
    }

    if(i_number_of_distinct_bytes == 1){
      ++current_instance.i_depth;
      //if we are done sorting this instance and all deeper subinstances
      if(i_max_length <= current_instance.i_depth){
        if(current_instance.b_copy){
          memcpy(
            &(arr_elements[current_instance.i_offset_first]),
            &(arr_elements_copy[current_instance.i_offset_first]),
            (current_instance.i_offset_last - current_instance.i_offset_first + 1) * sizeof(t_TSODLULS_sort_element__short)
          );
        }
        if(i_current_instance == 0){
          break;
        }
        current_instance = arr_instances[--i_current_instance];
      }
      continue;
    }

    if(current_instance.b_copy){
      //sorting
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_key = arr_elements_copy[i].i_key;
        i_current_key = i_current_key >> ((7 - current_instance.i_depth) * 8);
        i_current_octet = ((uint8_t) (i_current_key % 256));
        arr_elements[current_instance.i_offset_first + arr_offsets[i_current_octet]] = arr_elements_copy[i];
        ++arr_offsets[i_current_octet];
      }
      //instances creation
      for(int i = 0; i < 256; ++i){
        if(arr_counts[i] > 5//nothing to do for at most 5 elements, result is in original array
          //for nextified strings this test can be done on only one element
          && i_max_length > current_instance.i_depth + 1
        ){
          arr_instances[i_current_instance].i_offset_first = current_instance.i_offset_first
                                                           + arr_offsets[i] - arr_counts[i];
          arr_instances[i_current_instance].i_offset_last = current_instance.i_offset_first
                                                          + arr_offsets[i] - 1;
          arr_instances[i_current_instance].i_depth = current_instance.i_depth + 1;
          arr_instances[i_current_instance].b_copy = 0;
          ++i_current_instance;
        }
      }//end for(int i = 0; i < 256; ++i)
    }
    else{
      //sorting
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_key = arr_elements[i].i_key;
        i_current_key = i_current_key >> ((7 - current_instance.i_depth) * 8);
        i_current_octet = ((uint8_t) (i_current_key % 256));
        arr_elements_copy[current_instance.i_offset_first + arr_offsets[i_current_octet]] = arr_elements[i];
        ++arr_offsets[i_current_octet];
      }
      //instances creation
      for(int i = 0; i < 256; ++i){
        if(arr_counts[i] > 5
          //for nextified strings this test can be done on only one element
          && i_max_length > current_instance.i_depth + 1
        ){
          arr_instances[i_current_instance].i_offset_first = current_instance.i_offset_first
                                                           + arr_offsets[i] - arr_counts[i];
          arr_instances[i_current_instance].i_offset_last = current_instance.i_offset_first
                                                          + arr_offsets[i] - 1;
          arr_instances[i_current_instance].i_depth = current_instance.i_depth + 1;
          arr_instances[i_current_instance].b_copy = 1;
          ++i_current_instance;
        }
        else if(arr_counts[i] > 0){//we still need to copy data in original array
          memcpy(
            &(arr_elements[current_instance.i_offset_first + arr_offsets[i] - arr_counts[i]]),
            &(arr_elements_copy[current_instance.i_offset_first + arr_offsets[i] - arr_counts[i]]),
            arr_counts[i] * sizeof(t_TSODLULS_sort_element__short)
          );
        }
      }//end for(int i = 0; i < 256; ++i)
    }

    if(i_current_instance == 0){
      break;
    }

    current_instance = arr_instances[--i_current_instance];
  }//end while(true)

  TSODLULS_free(arr_elements_copy);
  TSODLULS_free(arr_instances);

  /* Once the arr_elements array is partially sorted by radix sort the rest
     is completely sorted using insertion sort, since this is efficient
     for partitions below MAX_THRESH size. arr_elements points to the beginning
     of the array to sort, and END_PTR points at the very last element in
     the array (*not* one beyond it!). */

  label_insertion_sort:
  {
    t_TSODLULS_sort_element__short* const end_ptr = &arr_elements[(i_number_of_elements - 1)];
    t_TSODLULS_sort_element__short* tmp_ptr = arr_elements;
    t_TSODLULS_sort_element__short* thresh = min(end_ptr, arr_elements + 5);
    t_TSODLULS_sort_element__short* run_ptr;

    /* Find smallest element in first threshold and place it at the
       array's beginning.  This is the smallest array element,
       and the operation speeds up insertion sort's inner loop. */

    for(run_ptr = tmp_ptr + 1; run_ptr <= thresh; ++run_ptr){
      if(run_ptr->i_key < tmp_ptr->i_key){
        tmp_ptr = run_ptr;
      }
    }

    if(tmp_ptr != arr_elements){
      tmp_cell = *tmp_ptr; *tmp_ptr = *arr_elements; *arr_elements = tmp_cell;//swapping
    }

    /* Insertion sort, running from left-hand-side up to right-hand-side.  */
    run_ptr = arr_elements + 1;
    while((++run_ptr) <= end_ptr){
      tmp_ptr = run_ptr - 1;
      while(run_ptr->i_key < tmp_ptr->i_key){
        --tmp_ptr;
      }
      ++tmp_ptr;
      if(tmp_ptr != run_ptr){
        t_TSODLULS_sort_element__short* trav;

        trav = run_ptr + 1;
        while(--trav >= run_ptr){
          tmp_cell = *trav;
          t_TSODLULS_sort_element__short* hi;
          t_TSODLULS_sort_element__short* lo;
          for (hi = lo = trav; (--lo) >= tmp_ptr; hi = lo){
            *hi = *lo;
          }
          *hi = tmp_cell;
        }
      }
    }
  }

  return 0;
}//end function TSODLULS_sort_radix8_count_insertion__short__mark1()



