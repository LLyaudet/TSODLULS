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

Most of the code here is from glibc:
  Written by Douglas C. Schmidt (schmidt@ics.uci.edu).
  Copyright (C) 1991-2018 Free Software Foundation, Inc.

Modifications in this library:
©Copyright 2018-2021 Laurent Lyaudet
*/
/*
If you consider tuning this algorithm, you should consult first:
Engineering a sort function; Jon Bentley and M. Douglas McIlroy;
Software - Practice and Experience; Vol. 23 (11), 1249-1265, 1993.
*/
/*
If you want to understand this function body, please look first at stdlib/qsort.c in glibc library
(the code below was partly copy-pasted from version 2.27 of glibc).
*/

/**
 * Sorting functions using a comparison callback for arbitrary data structures.
 * Qsort from glibc with minor modifications.
 */
//int TSODLULS_qsort__comparison_callback(
//  void* arr_elements,
//  size_t i_number_of_elements,
//  size_t i_element_size,
//  t_comparison_function fn_comparison
//){
//  #define TSODLULS_MAX_THRESH 5
//  #define TSODLULS_SWAP_VAR(a0,a1,a2) TSODLULS_SWAP_VAR_1(a0,a1,a2)
  char* base_ptr = (char*) arr_elements;

  const size_t max_threshold_size = (TSODLULS_MAX_THRESH - 1) * i_element_size;
  /*
  -1 because it is used in offsets (4 elements -> 3 offsets).
  I saw this bug when testing with TSODLULS_MAX_THRESH = 1.
  Insertion sort does not use this at the end except for finding the smallest element in first threshold.
  Overestimating the first threshold and the size of parts for insertion does not yield a functional bug.
  Thus only because I added "#if TSODLULS_MAX_THRESH > 1" before insertion sort yielded a bug.
  There was a mismatch between the initial line "if(i_number_of_elements > TSODLULS_MAX_THRESH){"
  just below (at most TSODLULS_MAX_THRESH elements for insertion sort)
  and the further lines "if((size_t)(right_ptr - lo) <= max_threshold_size){"
  (at most TSODLULS_MAX_THRESH + 1 elements before correction for insertion sort).
  This mismatch does exist in glibc qsort at time of writing.
  */

  if(i_number_of_elements < 2){//this is an optimization over glibc qsort! :P >< >< ><
    /* Avoid lossage with unsigned arithmetic below.  */
    return 0;
  }

  if(i_number_of_elements > TSODLULS_MAX_THRESH){
    char* lo = base_ptr;
    char* hi = &lo[(i_number_of_elements - 1) * i_element_size];
    t_TSODLULS_qsort_stack_node__comparison_callback stack[TSODLULS_STACK_SIZE];
    t_TSODLULS_qsort_stack_node__comparison_callback* top = stack;

    TSODLULS_PUSH(NULL, NULL);

    while(TSODLULS_STACK_NOT_EMPTY){
      char* left_ptr;
      char* right_ptr;

      /* Select median value from among LO, MID, and HI. Rearrange
      LO and HI so the three values are sorted. This lowers the
      probability of picking a pathological pivot value and
      skips a comparison for both the LEFT_PTR and RIGHT_PTR in
      the while loops. */

      char* mid = lo + i_element_size * ((hi - lo) / i_element_size >> 1);
      #if TSODLULS_MAX_THRESH <= 1
      if(mid == lo){//2 elements
        if((*fn_comparison) ((void *) hi, (void *) lo) < 0){
          TSODLULS_SWAP_VAR(hi, lo, i_element_size);
        }
        TSODLULS_POP (lo, hi);
        continue;
      }
      #endif

      if((*fn_comparison) ((void *) mid, (void *) lo) < 0){
        TSODLULS_SWAP_VAR(mid, lo, i_element_size);
      }
      if((*fn_comparison) ((void *) hi, (void *) mid) < 0){
        TSODLULS_SWAP_VAR(mid, hi, i_element_size);
        if((*fn_comparison) ((void *) mid, (void *) lo) < 0){
          TSODLULS_SWAP_VAR(mid, lo, i_element_size);
        }
      }
      #if TSODLULS_MAX_THRESH <= 2
      if((hi - lo) / i_element_size == 2){//3 elements
        TSODLULS_POP (lo, hi);
        continue;
      }
      #endif

      left_ptr  = lo + i_element_size;
      right_ptr = hi - i_element_size;

      /* Here's the famous ``collapse the walls'' section of quicksort.
         Gotta like those tight inner loops!  They are the main reason
         that this algorithm runs much faster than others. */
      do{
        while((*fn_comparison) ((void *) left_ptr, (void *) mid) < 0){
          left_ptr += i_element_size;
        }

        while((*fn_comparison) ((void *) mid, (void *) right_ptr) < 0){
          right_ptr -= i_element_size;
        }

        if(left_ptr < right_ptr){
          TSODLULS_SWAP_VAR(left_ptr, right_ptr, i_element_size);
          if(mid == left_ptr){
            mid = right_ptr;
          }
          else if(mid == right_ptr){
            mid = left_ptr;
          }
          left_ptr += i_element_size;
          right_ptr -= i_element_size;
        }
        else if (left_ptr == right_ptr){
          left_ptr += i_element_size;
          right_ptr -= i_element_size;
          break;
        }
      }
      while (left_ptr <= right_ptr);
      // lo <= right_ptr < left_ptr <= hi
      // [lo, left_ptr[ at most *mid
      // ]right_ptr, hi] at least *mid
      // right_ptr + 1 or 2 = left_ptr
      // if right_ptr + 2 = left_ptr, *(right_ptr + 1) = *mid
      // hence [lo, right_ptr] at most *mid, [left_ptr, hi] at least *mid and ]right_ptr, left_ptr[ = *mid

      /* Set up pointers for next iteration.  First determine whether
         left and right partitions are below the threshold size.  If so,
         ignore one or both.  Otherwise, push the larger partition's
         bounds on the stack and continue sorting the smaller one. */

      if((size_t)(right_ptr - lo) <= max_threshold_size){
        if ((size_t) (hi - left_ptr) <= max_threshold_size){
          /* Ignore both small partitions. */
          TSODLULS_POP (lo, hi);
        }
        else{
        /* Ignore small left partition. */
          lo = left_ptr;
        }
      }
      else if ((size_t) (hi - left_ptr) <= max_threshold_size){
        /* Ignore small right partition. */
        hi = right_ptr;
      }
      else if ((right_ptr - lo) > (hi - left_ptr)){
        /* Push larger left partition indices. */
        TSODLULS_PUSH (lo, right_ptr);
        lo = left_ptr;
      }
      else{
        /* Push larger right partition indices. */
        TSODLULS_PUSH (left_ptr, hi);
        hi = right_ptr;
      }
    }//end while(TSODLULS_STACK_NOT_EMPTY)
  }//end if(i_number_of_elements > TSODLULS_MAX_THRESH)

  /* Once the BASE_PTR array is partially sorted by quicksort the rest
     is completely sorted using insertion sort, since this is efficient
     for partitions below MAX_THRESH size. BASE_PTR points to the beginning
     of the array to sort, and END_PTR points at the very last element in
     the array (*not* one beyond it!). */
  #if TSODLULS_MAX_THRESH > 1
  {
    char* const end_ptr = &base_ptr[i_element_size * (i_number_of_elements - 1)];
    char* tmp_ptr = base_ptr;
    char* thresh = TSODLULS_min_exp(end_ptr, base_ptr + max_threshold_size);
    char* run_ptr;

    /* Find smallest element in first threshold and place it at the
       array's beginning.  This is the smallest array element,
       and the operation speeds up insertion sort's inner loop. */

    for(run_ptr = tmp_ptr + i_element_size; run_ptr <= thresh; run_ptr += i_element_size){
      if((*fn_comparison) ((void *) run_ptr, (void *) tmp_ptr) < 0){
        tmp_ptr = run_ptr;
      }
    }

    if(tmp_ptr != base_ptr){
      TSODLULS_SWAP_VAR(tmp_ptr, base_ptr, i_element_size);
    }

    /* Insertion sort, running from left-hand-side up to right-hand-side.  */
    run_ptr = base_ptr + i_element_size;
    while((run_ptr += i_element_size) <= end_ptr){
      tmp_ptr = run_ptr - i_element_size;
      while((*fn_comparison) ((void *) run_ptr, (void *) tmp_ptr) < 0){
        tmp_ptr -= i_element_size;
      }
      tmp_ptr += i_element_size;
      if(tmp_ptr != run_ptr){
        char* trav;

        trav = run_ptr + i_element_size;
        while(--trav >= run_ptr){
          char c = *trav;
          char* hi;
          char* lo;
          for (hi = lo = trav; (lo -= i_element_size) >= tmp_ptr; hi = lo){
            *hi = *lo;
          }
          *hi = c;
        }
      }
    }
  }
  #endif
  return 0;
//}//end function TSODLULS_qsort_inlined__short_MAX_THRESH

