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

#include "TSODLULS.h"



//------------------------------------------------------------------------------------
//External functions
//------------------------------------------------------------------------------------
/**
 * Sorting functions for short nextified strings
 * The current state of the art sorting function for nextified strings.
 * Its implementation may change without warning.
 */
int TSODLULS_sort__short(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
){
  return TSODLULS_sort_radix8_count_insertion__short(arr_elements, i_number_of_elements, i_max_length);
}//end function TSODLULS_sort()



/**
 * Sorting functions for short nextified strings
 * The current state of the art stable sorting function for nextified strings.
 * Its implementation may change without warning.
 */
int TSODLULS_sort_stable__short(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements,
  uint8_t i_max_length
){
  return TSODLULS_sort_radix8_count_insertion__short(arr_elements, i_number_of_elements, i_max_length);
}//end function TSODLULS_sort_stable()



/**
 * Sorting functions for short nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 */
int TSODLULS_sort_radix8_count__short(
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
}//end function TSODLULS_sort_radix8_count__short()




#define STACK_SIZE  (CHAR_BIT * sizeof(size_t))
#define PUSH(low, high)  ((void) ((top->p_low = (low)), (top->p_high = (high)), ++top))
#define  POP(low, high)  ((void) (--top, (low = top->p_low), (high = top->p_high)))
#define  STACK_NOT_EMPTY  (stack < top)

/**
 * Sorting functions for short nextified strings
 * Qsort from glibc inlined with short cells.
 */
int TSODLULS_qsort_inlined__short(
  t_TSODLULS_sort_element__short* arr_elements,
  size_t i_number_of_elements
){
  t_TSODLULS_sort_element__short* base_ptr = arr_elements;
  t_TSODLULS_sort_element__short tmp_cell;//for swapping

  if(i_number_of_elements < 2){//this is an optimization over glibc qsort! :P >< >< ><
    /* Avoid lossage with unsigned arithmetic below.  */
    return 0;
  }

  if(i_number_of_elements == 2){
    if(arr_elements[1].i_key < arr_elements[0].i_key){
      tmp_cell = arr_elements[1]; arr_elements[1] = arr_elements[0]; arr_elements[0] = tmp_cell;
    }
    return 0;
  }

  if(i_number_of_elements > 4){
    t_TSODLULS_sort_element__short* lo = base_ptr;
    t_TSODLULS_sort_element__short* hi = &lo[(i_number_of_elements - 1)];
    t_TSODLULS_qsort_stack_node__short stack[STACK_SIZE];
    t_TSODLULS_qsort_stack_node__short* top = stack;

    PUSH(NULL, NULL);

    while(STACK_NOT_EMPTY){
      t_TSODLULS_sort_element__short* left_ptr;
      t_TSODLULS_sort_element__short* right_ptr;

      /* Select median value from among LO, MID, and HI. Rearrange
      LO and HI so the three values are sorted. This lowers the
      probability of picking a pathological pivot value and
      skips a comparison for both the LEFT_PTR and RIGHT_PTR in
      the while loops. */

      t_TSODLULS_sort_element__short* mid = lo + ((hi - lo) >> 1);

      if(mid->i_key < lo->i_key){
        tmp_cell = *mid; *mid = *lo; *lo = tmp_cell;//swapping
      }
      if(hi->i_key < mid->i_key){
        tmp_cell = *hi; *hi = *mid; *mid = tmp_cell;//swapping
        if(mid->i_key < lo->i_key){
          tmp_cell = *mid; *mid = *lo; *lo = tmp_cell;//swapping
        }
      }

      left_ptr  = lo + 1;
      right_ptr = hi - 1;

      /* Here's the famous ``collapse the walls'' section of quicksort.
         Gotta like those tight inner loops!  They are the main reason
         that this algorithm runs much faster than others. */
      do{
        while(left_ptr->i_key < mid->i_key){
          ++left_ptr;
        }

        while(right_ptr->i_key > mid->i_key){
          --right_ptr;
        }

        if(left_ptr < right_ptr){
          tmp_cell = *right_ptr; *right_ptr = *left_ptr; *left_ptr = tmp_cell;//swapping
          if(mid == left_ptr){
            mid = right_ptr;
          }
          else if(mid == right_ptr){
            mid = left_ptr;
          }
          ++left_ptr;
          --right_ptr;
        }
        else if (left_ptr == right_ptr){
          ++left_ptr;
          --right_ptr;
          break;
        }
      }
      while (left_ptr <= right_ptr);

      /* Set up pointers for next iteration.  First determine whether
         left and right partitions are below the threshold size.  If so,
         ignore one or both.  Otherwise, push the larger partition's
         bounds on the stack and continue sorting the smaller one. */

      if((size_t)(right_ptr - lo) <= 4){
        if ((size_t) (hi - left_ptr) <= 4){
          /* Ignore both small partitions. */
          POP (lo, hi);
        }
        else{
        /* Ignore small left partition. */
          lo = left_ptr;
        }
      }
      else if ((size_t) (hi - left_ptr) <= 4){
        /* Ignore small right partition. */
        hi = right_ptr;
      }
      else if ((right_ptr - lo) > (hi - left_ptr)){
        /* Push larger left partition indices. */
        PUSH (lo, right_ptr);
        lo = left_ptr;
      }
      else{
        /* Push larger right partition indices. */
        PUSH (left_ptr, hi);
        hi = right_ptr;
      }
    }//end while(STACK_NOT_EMPTY)
  }//end if(i_number_of_elements > 4)

  /* Once the BASE_PTR array is partially sorted by quicksort the rest
     is completely sorted using insertion sort, since this is efficient
     for partitions below MAX_THRESH size. BASE_PTR points to the beginning
     of the array to sort, and END_PTR points at the very last element in
     the array (*not* one beyond it!). */

#define min(x, y) ((x) < (y) ? (x) : (y))

  {
    t_TSODLULS_sort_element__short* const end_ptr = &base_ptr[(i_number_of_elements - 1)];
    t_TSODLULS_sort_element__short* tmp_ptr = base_ptr;
    t_TSODLULS_sort_element__short* thresh = min(end_ptr, base_ptr + 4);
    t_TSODLULS_sort_element__short* run_ptr;

    /* Find smallest element in first threshold and place it at the
       array's beginning.  This is the smallest array element,
       and the operation speeds up insertion sort's inner loop. */

    for(run_ptr = tmp_ptr + 1; run_ptr <= thresh; ++run_ptr){
      if(run_ptr->i_key < tmp_ptr->i_key){
        tmp_ptr = run_ptr;
      }
    }

    if(tmp_ptr != base_ptr){
      tmp_cell = *tmp_ptr; *tmp_ptr = *base_ptr; *base_ptr = tmp_cell;//swapping
    }

    /* Insertion sort, running from left-hand-side up to right-hand-side.  */
    run_ptr = base_ptr + 1;
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
}//end function TSODLULS_qsort_inlined__short



/**
 * Sorting functions for short nextified strings
 * A stable sorting algorithm for nextified strings based on radix sort with octets digits
 * and counting sort as a subroutine.
 * When the number of elements to sort is at most 5, we use insertion sort
 * A variant with single memory allocation adapted to the max-depth.
 * No insertion sort if there is more than 5 elements and it is 8 bits datatype.
 * This is the current best algorithm and it is a stable one :)
 */
int TSODLULS_sort_radix8_count_insertion__short(
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

  if(i_max_length == 1){
    return 0;
  }

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
}//end function TSODLULS_sort_radix8_count_insertion__short()



