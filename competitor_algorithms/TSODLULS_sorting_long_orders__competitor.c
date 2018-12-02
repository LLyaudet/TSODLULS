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
 * Sorting functions for long nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 */
int TSODLULS_sort_radix8_count__mark1(t_TSODLULS_sort_element* arr_elements, size_t i_number_of_elements){
  int i_number_of_distinct_bytes = 0;
  size_t arr_counts[256];
  size_t arr_offsets[256];
  uint8_t i_current_octet = 0;
  t_TSODLULS_sort_element* arr_elements_copy = NULL;
  t_TSODLULS_radix_instance current_instance;
  t_TSODLULS_radix_instance* arr_instances = NULL;
  size_t i_max_number_of_instances = 0;
  size_t i_current_instance = 0;
  void* p_for_realloc = NULL;
  size_t i_size_for_realloc = 0;

  if(i_number_of_elements < 1){
    return 0;//nothing to sort
  }

  current_instance.i_offset_first = 0;
  current_instance.i_offset_last = i_number_of_elements - 1;
  current_instance.i_depth = 0;
  current_instance.b_copy = 0;

  arr_elements_copy = calloc(i_number_of_elements, sizeof(t_TSODLULS_sort_element));
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
        i_current_octet = arr_elements_copy[i].s_key[current_instance.i_depth];
        ++arr_counts[i_current_octet];
      }
    }
    else{
      for(size_t i = current_instance.i_offset_first; i <= current_instance.i_offset_last; ++i){
        i_current_octet = arr_elements[i].s_key[current_instance.i_depth];
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
      if(arr_elements[current_instance.i_offset_first].i_key_size <= current_instance.i_depth){
        if(current_instance.b_copy){
          memcpy(
            &(arr_elements[current_instance.i_offset_first]),
            &(arr_elements_copy[current_instance.i_offset_first]),
            (current_instance.i_offset_last - current_instance.i_offset_first + 1) * sizeof(t_TSODLULS_sort_element)
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
        i_current_octet = arr_elements_copy[i].s_key[current_instance.i_depth];
        arr_elements[current_instance.i_offset_first + arr_offsets[i_current_octet]] = arr_elements_copy[i];
        ++arr_offsets[i_current_octet];
      }
      //instances creation
      for(int i = 0; i < 256; ++i){
        if(arr_counts[i] > 1//nothing to do for one element, result is in original array
          //for nextified strings this test can be done on only one element
          && arr_elements[current_instance.i_offset_first + arr_offsets[i] - 1].i_key_size
               > current_instance.i_depth + 1
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
        i_current_octet = arr_elements[i].s_key[current_instance.i_depth];
        arr_elements_copy[current_instance.i_offset_first + arr_offsets[i_current_octet]] = arr_elements[i];
        ++arr_offsets[i_current_octet];
      }
      //instances creation
      for(int i = 0; i < 256; ++i){
        if(arr_counts[i] > 1
          //for nextified strings this test can be done on only one element
          && arr_elements_copy[current_instance.i_offset_first + arr_offsets[i] - 1].i_key_size
               > current_instance.i_depth + 1
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
            arr_counts[i] * sizeof(t_TSODLULS_sort_element)
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
}//end function TSODLULS_sort_radix8_count__mark1()



