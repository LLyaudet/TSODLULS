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

//This file was generated by generateQsortInlined.php script.
#include "TSODLULS__competitor.h"



#define STACK_SIZE  (CHAR_BIT * sizeof(size_t))
#define PUSH(low, high)  ((void) ((top->p_low = (low)), (top->p_high = (high)), ++top))
#define  POP(low, high)  ((void) (--top, (low = top->p_low), (high = top->p_high)))
#define  STACK_NOT_EMPTY  (stack < top)

/**
 * Sorting functions for short nextified strings
 * Qsort from glibc inlined with short cells.
 */
int TSODLULS_qsort_inlined__short_3(
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

  if(i_number_of_elements > 3){
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

      if((size_t)(right_ptr - lo) <= 3){
        if ((size_t) (hi - left_ptr) <= 3){
          /* Ignore both small partitions. */
          POP (lo, hi);
        }
        else{
        /* Ignore small left partition. */
          lo = left_ptr;
        }
      }
      else if ((size_t) (hi - left_ptr) <= 3){
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
  }//end if(i_number_of_elements > 3)

  /* Once the BASE_PTR array is partially sorted by quicksort the rest
     is completely sorted using insertion sort, since this is efficient
     for partitions below MAX_THRESH size. BASE_PTR points to the beginning
     of the array to sort, and END_PTR points at the very last element in
     the array (*not* one beyond it!). */

#define min(x, y) ((x) < (y) ? (x) : (y))

  {
    t_TSODLULS_sort_element__short* const end_ptr = &base_ptr[(i_number_of_elements - 1)];
    t_TSODLULS_sort_element__short* tmp_ptr = base_ptr;
    t_TSODLULS_sort_element__short* thresh = min(end_ptr, base_ptr + 3);
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
}//end function TSODLULS_qsort_inlined__short_3





#define STACK_SIZE  (CHAR_BIT * sizeof(size_t))
#define PUSH(low, high)  ((void) ((top->p_low = (low)), (top->p_high = (high)), ++top))
#define  POP(low, high)  ((void) (--top, (low = top->p_low), (high = top->p_high)))
#define  STACK_NOT_EMPTY  (stack < top)

/**
 * Sorting functions for short nextified strings
 * Qsort from glibc inlined with short cells.
 */
int TSODLULS_qsort_inlined__short_4(
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
}//end function TSODLULS_qsort_inlined__short_4





#define STACK_SIZE  (CHAR_BIT * sizeof(size_t))
#define PUSH(low, high)  ((void) ((top->p_low = (low)), (top->p_high = (high)), ++top))
#define  POP(low, high)  ((void) (--top, (low = top->p_low), (high = top->p_high)))
#define  STACK_NOT_EMPTY  (stack < top)

/**
 * Sorting functions for short nextified strings
 * Qsort from glibc inlined with short cells.
 */
int TSODLULS_qsort_inlined__short_5(
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

  if(i_number_of_elements > 5){
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

      if((size_t)(right_ptr - lo) <= 5){
        if ((size_t) (hi - left_ptr) <= 5){
          /* Ignore both small partitions. */
          POP (lo, hi);
        }
        else{
        /* Ignore small left partition. */
          lo = left_ptr;
        }
      }
      else if ((size_t) (hi - left_ptr) <= 5){
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
  }//end if(i_number_of_elements > 5)

  /* Once the BASE_PTR array is partially sorted by quicksort the rest
     is completely sorted using insertion sort, since this is efficient
     for partitions below MAX_THRESH size. BASE_PTR points to the beginning
     of the array to sort, and END_PTR points at the very last element in
     the array (*not* one beyond it!). */

#define min(x, y) ((x) < (y) ? (x) : (y))

  {
    t_TSODLULS_sort_element__short* const end_ptr = &base_ptr[(i_number_of_elements - 1)];
    t_TSODLULS_sort_element__short* tmp_ptr = base_ptr;
    t_TSODLULS_sort_element__short* thresh = min(end_ptr, base_ptr + 5);
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
}//end function TSODLULS_qsort_inlined__short_5





#define STACK_SIZE  (CHAR_BIT * sizeof(size_t))
#define PUSH(low, high)  ((void) ((top->p_low = (low)), (top->p_high = (high)), ++top))
#define  POP(low, high)  ((void) (--top, (low = top->p_low), (high = top->p_high)))
#define  STACK_NOT_EMPTY  (stack < top)

/**
 * Sorting functions for short nextified strings
 * Qsort from glibc inlined with short cells.
 */
int TSODLULS_qsort_inlined__short_6(
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

  if(i_number_of_elements > 6){
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

      if((size_t)(right_ptr - lo) <= 6){
        if ((size_t) (hi - left_ptr) <= 6){
          /* Ignore both small partitions. */
          POP (lo, hi);
        }
        else{
        /* Ignore small left partition. */
          lo = left_ptr;
        }
      }
      else if ((size_t) (hi - left_ptr) <= 6){
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
  }//end if(i_number_of_elements > 6)

  /* Once the BASE_PTR array is partially sorted by quicksort the rest
     is completely sorted using insertion sort, since this is efficient
     for partitions below MAX_THRESH size. BASE_PTR points to the beginning
     of the array to sort, and END_PTR points at the very last element in
     the array (*not* one beyond it!). */

#define min(x, y) ((x) < (y) ? (x) : (y))

  {
    t_TSODLULS_sort_element__short* const end_ptr = &base_ptr[(i_number_of_elements - 1)];
    t_TSODLULS_sort_element__short* tmp_ptr = base_ptr;
    t_TSODLULS_sort_element__short* thresh = min(end_ptr, base_ptr + 6);
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
}//end function TSODLULS_qsort_inlined__short_6





#define STACK_SIZE  (CHAR_BIT * sizeof(size_t))
#define PUSH(low, high)  ((void) ((top->p_low = (low)), (top->p_high = (high)), ++top))
#define  POP(low, high)  ((void) (--top, (low = top->p_low), (high = top->p_high)))
#define  STACK_NOT_EMPTY  (stack < top)

/**
 * Sorting functions for short nextified strings
 * Qsort from glibc inlined with short cells.
 */
int TSODLULS_qsort_inlined__short_7(
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

  if(i_number_of_elements > 7){
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

      if((size_t)(right_ptr - lo) <= 7){
        if ((size_t) (hi - left_ptr) <= 7){
          /* Ignore both small partitions. */
          POP (lo, hi);
        }
        else{
        /* Ignore small left partition. */
          lo = left_ptr;
        }
      }
      else if ((size_t) (hi - left_ptr) <= 7){
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
  }//end if(i_number_of_elements > 7)

  /* Once the BASE_PTR array is partially sorted by quicksort the rest
     is completely sorted using insertion sort, since this is efficient
     for partitions below MAX_THRESH size. BASE_PTR points to the beginning
     of the array to sort, and END_PTR points at the very last element in
     the array (*not* one beyond it!). */

#define min(x, y) ((x) < (y) ? (x) : (y))

  {
    t_TSODLULS_sort_element__short* const end_ptr = &base_ptr[(i_number_of_elements - 1)];
    t_TSODLULS_sort_element__short* tmp_ptr = base_ptr;
    t_TSODLULS_sort_element__short* thresh = min(end_ptr, base_ptr + 7);
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
}//end function TSODLULS_qsort_inlined__short_7





#define STACK_SIZE  (CHAR_BIT * sizeof(size_t))
#define PUSH(low, high)  ((void) ((top->p_low = (low)), (top->p_high = (high)), ++top))
#define  POP(low, high)  ((void) (--top, (low = top->p_low), (high = top->p_high)))
#define  STACK_NOT_EMPTY  (stack < top)

/**
 * Sorting functions for short nextified strings
 * Qsort from glibc inlined with short cells.
 */
int TSODLULS_qsort_inlined__short_8(
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

  if(i_number_of_elements > 8){
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

      if((size_t)(right_ptr - lo) <= 8){
        if ((size_t) (hi - left_ptr) <= 8){
          /* Ignore both small partitions. */
          POP (lo, hi);
        }
        else{
        /* Ignore small left partition. */
          lo = left_ptr;
        }
      }
      else if ((size_t) (hi - left_ptr) <= 8){
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
  }//end if(i_number_of_elements > 8)

  /* Once the BASE_PTR array is partially sorted by quicksort the rest
     is completely sorted using insertion sort, since this is efficient
     for partitions below MAX_THRESH size. BASE_PTR points to the beginning
     of the array to sort, and END_PTR points at the very last element in
     the array (*not* one beyond it!). */

#define min(x, y) ((x) < (y) ? (x) : (y))

  {
    t_TSODLULS_sort_element__short* const end_ptr = &base_ptr[(i_number_of_elements - 1)];
    t_TSODLULS_sort_element__short* tmp_ptr = base_ptr;
    t_TSODLULS_sort_element__short* thresh = min(end_ptr, base_ptr + 8);
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
}//end function TSODLULS_qsort_inlined__short_8



