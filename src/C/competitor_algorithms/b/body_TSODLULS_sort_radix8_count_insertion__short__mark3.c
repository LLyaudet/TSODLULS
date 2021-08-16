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

©Copyright 2018-2021 Laurent Lyaudet
*/
/**
 * Sorting functions for short nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements to sort is at most TSODLULS_MAX_THRESH, we use insertion sort
 * A variant with single memory allocation adapted to the max-depth.
 * No insertion sort if there is more than TSODLULS_MAX_THRESH elements and it is 8 bits datatype.
 * Simplified inner loops ( if(i_max_length > current_instance.i_depth + 1) )
 */
//int TSODLULS_sort_radix8_count_insertion__short__mark3(
//  t_TSODLULS_sort_element__short* arr_elements,
//  size_t i_number_of_elements,
//  uint8_t i_max_length
//){
//  #define TSODLULS_MAX_THRESH 5
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

  if(i_number_of_elements <= TSODLULS_MAX_THRESH){
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

  //This is depth first in a tree of degree 256 and depth at most i_max_length - 1,
  //so we will not need more that (i_max_length - 1) * 256
  //We also doesn't need more than i_number_of_elements / (TSODLULS_MAX_THRESH + 1) because of the use of insertion sort
  if(i_max_length - 1 > 0){
    arr_instances = calloc(
        TSODLULS_min_exp((i_max_length - 1) * 256, i_number_of_elements / (TSODLULS_MAX_THRESH + 1)),
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
      if(i_max_length > current_instance.i_depth + 1){
        for(int i = 0; i < 256; ++i){
          if(arr_counts[i] > TSODLULS_MAX_THRESH){//nothing to do for at most TSODLULS_MAX_THRESH elements, result is in original array
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
      if(i_max_length > current_instance.i_depth + 1){
        for(int i = 0; i < 256; ++i){
          if(arr_counts[i] > TSODLULS_MAX_THRESH){
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
      else{
        for(int i = 0; i < 256; ++i){
          if(arr_counts[i] > 0){//we still need to copy data in original array
            memcpy(
              &(arr_elements[current_instance.i_offset_first + arr_offsets[i] - arr_counts[i]]),
              &(arr_elements_copy[current_instance.i_offset_first + arr_offsets[i] - arr_counts[i]]),
              arr_counts[i] * sizeof(t_TSODLULS_sort_element__short)
            );
          }
        }//end for(int i = 0; i < 256; ++i)
      }
    }

    if(i_current_instance == 0){
      break;
    }

    current_instance = arr_instances[--i_current_instance];
  }//end while(true)

  TSODLULS_free(arr_elements_copy);
  TSODLULS_free(arr_instances);

  if(i_max_length == 1){
    return 0;
  }

  /* Once the arr_elements array is partially sorted by radix sort the rest
     is completely sorted using insertion sort, since this is efficient
     for partitions below MAX_THRESH size. arr_elements points to the beginning
     of the array to sort, and END_PTR points at the very last element in
     the array (*not* one beyond it!). */

  label_insertion_sort:
  #if TSODLULS_MAX_THRESH > 1
  {
    #define TSODLULS_OPTIMIZE_INSERTION_SORT_WITHOUT_THRESHOLD 0
    t_TSODLULS_sort_element__short* const start_ptr = arr_elements;
    t_TSODLULS_sort_element__short* const end_ptr = &start_ptr[(i_number_of_elements - 1)];
    #include TSODLULS_INSERTION_SORT_TEMPLATE_WITH_THRESHOLD
    #undef TSODLULS_OPTIMIZE_INSERTION_SORT_WITHOUT_THRESHOLD
  }
  #endif

  return 0;
//}//end function TSODLULS_sort_radix8_count_insertion__short__mark3()

