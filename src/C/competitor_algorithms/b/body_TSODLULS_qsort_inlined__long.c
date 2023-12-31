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
©Copyright 2018-2023 Laurent Lyaudet
*/
/*
If you want to understand this function body, please look first at stdlib/qsort.c in glibc library
(the code below was partly copy-pasted from version 2.27 of glibc).
*/

/**
 * Sorting functions for long nextified strings
 * Qsort from glibc inlined with long cells.
 */
//int TSODLULS_qsort_inlined__long(
//  t_TSODLULS_sort_element__long* arr_elements,
//  size_t i_number_of_elements
//){
//  #define TSODLULS_MAX_THRESH 5
  t_TSODLULS_sort_element* base_ptr = arr_elements;
  t_TSODLULS_sort_element tmp_cell;//for swapping
  size_t i__compare;
  size_t i_max__compare;
  int i_result__compare;
  int b_continue;

  if(i_number_of_elements < 2){//this is an optimization over glibc qsort! :P >< >< ><
    /* Avoid lossage with unsigned arithmetic below.  */
    return 0;
  }

  if(i_number_of_elements == 2){
    TSODLULS_set_min_length__macraff(i_max__compare, &(arr_elements[0]), &(arr_elements[1]));
    for(i__compare = 0; i__compare < i_max__compare; ++i__compare){
      i_result__compare = ((int)(arr_elements[0].s_key[i__compare])) - ((int)(arr_elements[1].s_key[i__compare]));
      if(i_result__compare != 0){
        if(i_result__compare > 0){
          tmp_cell = arr_elements[1]; arr_elements[1] = arr_elements[0]; arr_elements[0] = tmp_cell;
        }
        break;
      }
    }
    return 0;
  }

  if(i_number_of_elements > TSODLULS_MAX_THRESH){
    t_TSODLULS_sort_element* lo = base_ptr;
    t_TSODLULS_sort_element* hi = &lo[(i_number_of_elements - 1)];
    t_TSODLULS_qsort_stack_node stack[TSODLULS_STACK_SIZE];
    t_TSODLULS_qsort_stack_node* top = stack;

    TSODLULS_PUSH(NULL, NULL);

    while(TSODLULS_STACK_NOT_EMPTY){
      t_TSODLULS_sort_element* left_ptr;
      t_TSODLULS_sort_element* right_ptr;

      /* Select median value from among LO, MID, and HI. Rearrange
      LO and HI so the three values are sorted. This lowers the
      probability of picking a pathological pivot value and
      skips a comparison for both the LEFT_PTR and RIGHT_PTR in
      the while loops. */

      t_TSODLULS_sort_element* mid = lo + ((hi - lo) >> 1);
      #if TSODLULS_MAX_THRESH <= 1
      if(mid == lo){//2 elements
        // swapping low and high if needed
        TSODLULS_set_min_length__macraff(i_max__compare, lo, hi);
        for(i__compare = 0; i__compare < i_max__compare; ++i__compare){
          i_result__compare = ((int)(lo->s_key[i__compare])) - ((int)(hi->s_key[i__compare]));
          if(i_result__compare != 0){
            if(i_result__compare > 0){
              tmp_cell = *hi; *hi = *lo; *lo = tmp_cell;//swapping
            }
            break;
          }
        }
        TSODLULS_POP (lo, hi);
        continue;
      }
      #endif

      // swapping low and middle if needed
      TSODLULS_set_min_length__macraff(i_max__compare, lo, mid);
      for(i__compare = 0; i__compare < i_max__compare; ++i__compare){
        i_result__compare = ((int)(lo->s_key[i__compare])) - ((int)(mid->s_key[i__compare]));
        if(i_result__compare != 0){
          if(i_result__compare > 0){
            tmp_cell = *mid; *mid = *lo; *lo = tmp_cell;//swapping
          }
          break;
        }
      }

      // swapping high and middle if needed
      TSODLULS_set_min_length__macraff(i_max__compare, mid, hi);
      for(i__compare = 0; i__compare < i_max__compare; ++i__compare){
        i_result__compare = ((int)(mid->s_key[i__compare])) - ((int)(hi->s_key[i__compare]));
        if(i_result__compare != 0){
          if(i_result__compare > 0){
            tmp_cell = *hi; *hi = *mid; *mid = tmp_cell;//swapping

            // swapping low and new middle if needed
            TSODLULS_set_min_length__macraff(i_max__compare, lo, mid);
            for(i__compare = 0; i__compare < i_max__compare; ++i__compare){
              i_result__compare = ((int)(lo->s_key[i__compare])) - ((int)(mid->s_key[i__compare]));
              if(i_result__compare != 0){
                if(i_result__compare > 0){
                  tmp_cell = *mid; *mid = *lo; *lo = tmp_cell;//swapping
                }
                break;
              }
            }

          }
          break;
        }
      }
      #if TSODLULS_MAX_THRESH <= 2
      if((hi - lo) == 2){//3 elements
        TSODLULS_POP (lo, hi);
        continue;
      }
      #endif

      left_ptr  = lo + 1;
      right_ptr = hi - 1;

      /* Here's the famous ``collapse the walls'' section of quicksort.
         Gotta like those tight inner loops!  They are the main reason
         that this algorithm runs much faster than others. */
      do{
        b_continue = 1;
        while(b_continue > 0){
          b_continue = 0;
          TSODLULS_set_min_length__macraff(i_max__compare, left_ptr, mid);
          for(i__compare = 0; i__compare < i_max__compare; ++i__compare){
            i_result__compare = ((int)(left_ptr->s_key[i__compare])) - ((int)(mid->s_key[i__compare]));
            if(i_result__compare != 0){
              if(i_result__compare < 0){
                b_continue = 1;
                ++left_ptr;
              }
              break;
            }
          }
        }

        b_continue = 1;
        while(b_continue > 0){
          b_continue = 0;
          TSODLULS_set_min_length__macraff(i_max__compare, right_ptr, mid);
          for(i__compare = 0; i__compare < i_max__compare; ++i__compare){
            i_result__compare = ((int)(right_ptr->s_key[i__compare])) - ((int)(mid->s_key[i__compare]));
            if(i_result__compare != 0){
              if(i_result__compare > 0){
                b_continue = 1;
                --right_ptr;
              }
              break;
            }
          }
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

      if((right_ptr - lo) < TSODLULS_MAX_THRESH){
        if((hi - left_ptr) < TSODLULS_MAX_THRESH){
          /* Ignore both small partitions. */
          TSODLULS_POP (lo, hi);
        }
        else{
        /* Ignore small left partition. */
          lo = left_ptr;
        }
      }
      else if((hi - left_ptr) < TSODLULS_MAX_THRESH){
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
    #define TSODLULS_OPTIMIZE_INSERTION_SORT_WITHOUT_THRESHOLD 0
    t_TSODLULS_sort_element* const start_ptr = arr_elements;
    t_TSODLULS_sort_element* const end_ptr = &start_ptr[(i_number_of_elements - 1)];
    #include TSODLULS_INSERTION_SORT_TEMPLATE_WITH_THRESHOLD
    #undef TSODLULS_OPTIMIZE_INSERTION_SORT_WITHOUT_THRESHOLD
  }
  #endif
  return 0;
//}//end function TSODLULS_qsort_inlined__long_MAX_THRESH

