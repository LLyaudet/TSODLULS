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
/*
This file contains general remarks about the functional macros in this library
and includes the files defining them.
Most of the functions available in this library are available as as "macraff",
i.e. a macro with affectation.
If you have a function
  int foo(type1 param1, type2 param2);
,
the corresponding macraff is
  foo__macraff(int paramAff, type1 param1, type2 param2)
Macraffs use auxiliary variables that you need to declare in the calling function.
If it is possible to code the macro without computing twice the parameters
and returning the correct value, then the macro is available as a simple macro.

Examples:
int foo(int i){
  return i << 1;
}
will become a macro
#define foo__macro(i) \
  ((i) << 1)

but 

int foo(int i, int j){
  return (i < j ? i : j);
}
will become a macraff
#define foo__macraff(k, i, j) \
  TSODLULS_macraff_i = (i);\
  TSODLULS_macraff_j = (j);\
  (k) = (TSODLULS_macraff_i < TSODLULS_macraff_j ? TSODLULS_macraff_i : TSODLULS_macraff_j);\

The comment before a function tells if it is available as a macro or as a macraff.
If the return type is void but auxiliary variables need to be declared,
 we still classify the macro with the macraffs, because of the affectations of the parameters.
*/

//#include "TSODLULS_comparison__macro.h"
#include "TSODLULS_finite_orders__macro.h"
#include "TSODLULS_misc__macro.h"
#include "TSODLULS_padding__macro.h"
//#include "TSODLULS_sorting_long_orders__macro.h"
//#include "TSODLULS_sorting_short_orders__macro.h"

/*
The macraffs in this library use the following auxiliary variables:
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
  char* TSODLULS_macraff_p_char;
  char* TSODLULS_macraff_p_char_2;
  char* TSODLULS_macraff_p_char_3;
  char TSODLULS_macraff_char;
  t_TSODLULS_sizables_union TSODLULS_macraff_sizables_union;
  t_TSODLULS_sizables_pointers_union TSODLULS_macraff_sizables_pointers_union_1;
  t_TSODLULS_sizables_pointers_union TSODLULS_macraff_sizables_pointers_union_2;
  size_t TSODLULS_macraff_i_chunk_size = TSODLULS_CHUNK_SIZE_FOR_SWAP_VAR(i_element_size);
*/

#define TSODLULS_free(pointer) \
  free(pointer);\
  (pointer) = NULL;

#define TSODLULS_min_exp(x, y) ((x) < (y) ? (x) : (y))



#define TSODLULS_STACK_SIZE  (CHAR_BIT * sizeof(size_t))
#define TSODLULS_PUSH(low, high)  ((void) ((top->p_low = (low)), (top->p_high = (high)), ++top))
#define TSODLULS_POP(low, high)  ((void) (--top, (low = top->p_low), (high = top->p_high)))
#define TSODLULS_STACK_NOT_EMPTY  (stack < top)



/*
There is no simple and portable way to have double char, quad char and octo char in C.
Where the interesting feature of char is to be the smallest addressable memory unit.
And I seek other larger addressable memory units handled by the hardware (CPU...).
sizeof is not available in preprocessor.
We take what is available:
__SIZEOF_INT__
__SIZEOF_LONG__
__SIZEOF_LONG_LONG__
__SIZEOF_SHORT__
__SIZEOF_POINTER__
__SIZEOF_FLOAT__
__SIZEOF_DOUBLE__
__SIZEOF_LONG_DOUBLE__
__SIZEOF_SIZE_T__
__SIZEOF_WCHAR_T__
__SIZEOF_WINT_T__
__SIZEOF_PTRDIFF_T__
*/
typedef union {
  char c;
  int i;
  long int l;
  long long int ll;
  short int s;
/*
  void* p;
  float f;
  double d;
  long double ld;
  size_t st;
  wchar_t wc;
  wint_t wi;
  ptrdiff_t pt;
*/
} t_TSODLULS_sizables_union;
typedef union {
  char* c;
  int* i;
  long int* l;
  long long int* ll;
  short int* s;
/*
  void** p;
  float* f;
  double* d;
  long double* ld;
  size_t* st;
  wchar_t* wc;
  wint_t* wi;
  ptrdiff_t* pt;
*/
} t_TSODLULS_sizables_pointers_union;

//Magic numbers constants for a switch
#define TSODLULS_CHAR_SWAP 0
#define TSODLULS_INT_SWAP 1
#define TSODLULS_LONG_INT_SWAP 2
#define TSODLULS_LONG_LONG_INT_SWAP 3
#define TSODLULS_SHORT_INT_SWAP 4

#if __SIZEOF_INT__ == 2
  #define TSODLULS_CHUNK_SIZE_2 TSODLULS_INT_SWAP
#elif __SIZEOF_LONG__ == 2
  #define TSODLULS_CHUNK_SIZE_2 TSODLULS_LONG_INT_SWAP
#elif __SIZEOF_LONG_LONG__ == 2
  #define TSODLULS_CHUNK_SIZE_2 TSODLULS_LONG_LONG_INT_SWAP
#elif __SIZEOF_SHORT__ == 2
  #define TSODLULS_CHUNK_SIZE_2 TSODLULS_SHORT_INT_SWAP
#else
  #define TSODLULS_CHUNK_SIZE_2 TSODLULS_CHAR_SWAP
#endif

#if __SIZEOF_INT__ == 4
  #define TSODLULS_CHUNK_SIZE_4 TSODLULS_INT_SWAP
#elif __SIZEOF_LONG__ == 4
  #define TSODLULS_CHUNK_SIZE_4 TSODLULS_LONG_INT_SWAP
#elif __SIZEOF_LONG_LONG__ == 4
  #define TSODLULS_CHUNK_SIZE_4 TSODLULS_LONG_LONG_INT_SWAP
#elif __SIZEOF_SHORT__ == 4
  #define TSODLULS_CHUNK_SIZE_4 TSODLULS_SHORT_INT_SWAP
#else
  #define TSODLULS_CHUNK_SIZE_4 TSODLULS_CHUNK_SIZE_2
#endif

#if __SIZEOF_INT__ == 8
  #define TSODLULS_CHUNK_SIZE_8 TSODLULS_INT_SWAP
#elif __SIZEOF_LONG__ == 8
  #define TSODLULS_CHUNK_SIZE_8 TSODLULS_LONG_INT_SWAP
#elif __SIZEOF_LONG_LONG__ == 8
  #define TSODLULS_CHUNK_SIZE_8 TSODLULS_LONG_LONG_INT_SWAP
#elif __SIZEOF_SHORT__ == 8
  #define TSODLULS_CHUNK_SIZE_8 TSODLULS_SHORT_INT_SWAP
#else
  #define TSODLULS_CHUNK_SIZE_8 TSODLULS_CHUNK_SIZE_4
#endif



/**
 * Computes the chunk size used for swapping many items of same size
*/
#define TSODLULS_CHUNK_SIZE_FOR_SWAP_VAR(size)\
  (size < 1 ? TSODLULS_CHAR_SWAP : \
    (size & 1 ? TSODLULS_CHAR_SWAP : \
      (size & 2 ? TSODLULS_CHUNK_SIZE_2 : \
        ( size & 4 ? TSODLULS_CHUNK_SIZE_4 : TSODLULS_CHUNK_SIZE_8))))



/**
 * Byte-wise swap two items of size SIZE.
 * This macro is adapted from glibc 2.27.
 * Written by Douglas C. Schmidt (schmidt@ics.uci.edu).
 * Copyright (C) 1991-2018 Free Software Foundation, Inc.
 * (SWAP_VAR for swap varying length cells)
*/
#define TSODLULS_SWAP_VAR_1(a, b, size)\
  do{\
    size_t isize_tsodluls_swap_var = (size);\
    char* p_c_tsodluls_swap_var_1 = (char *) (a);\
    char* p_c_tsodluls_swap_var_2 = (char *) (b);\
    do{\
      char c_tsodluls_swap_var = *p_c_tsodluls_swap_var_1;\
      *p_c_tsodluls_swap_var_1++ = *p_c_tsodluls_swap_var_2;\
      *p_c_tsodluls_swap_var_2++ = c_tsodluls_swap_var;\
    }while(--isize_tsodluls_swap_var > 0);\
  }while(0);



/**
 * Byte-wise swap two items of size SIZE.
 * This macraff requires the following auxiliary variables:
 *   size_t TSODLULS_macraff_isize;
 *   char* TSODLULS_macraff_p_char;
 *   char* TSODLULS_macraff_p_char_2;
 *   char TSODLULS_macraff_char;
*/
#define TSODLULS_SWAP_VAR_2(a, b, size)\
  do{\
    TSODLULS_macraff_isize = (size);\
    TSODLULS_macraff_p_char = (char *) (a);\
    TSODLULS_macraff_p_char_2 = (char *) (b);\
    do{\
      TSODLULS_macraff_char = *TSODLULS_macraff_p_char;\
      *TSODLULS_macraff_p_char++ = *TSODLULS_macraff_p_char_2;\
      *TSODLULS_macraff_p_char_2++ = TSODLULS_macraff_char;\
    }while(--TSODLULS_macraff_isize > 0);\
  }while(0);



/**
 * Byte-wise swap two items of size SIZE.
*/
#define TSODLULS_SWAP_VAR_3(a, b, size)\
  do{\
    char* p_c_tsodluls_swap_var_1 = (char *) (a);\
    char* p_c_tsodluls_swap_var_2 = (char *) (b);\
    char* p_c_tsodluls_swap_var_3 = p_c_tsodluls_swap_var_1 + (size);\
    do{\
      char c_tsodluls_swap_var = *p_c_tsodluls_swap_var_1;\
      *p_c_tsodluls_swap_var_1++ = *p_c_tsodluls_swap_var_2;\
      *p_c_tsodluls_swap_var_2++ = c_tsodluls_swap_var;\
    }while(p_c_tsodluls_swap_var_1 < p_c_tsodluls_swap_var_3);\
  }while(0);



/**
 * Byte-wise swap two items of size SIZE.
 * This macraff requires the following auxiliary variables:
 *   char* TSODLULS_macraff_p_char;
 *   char* TSODLULS_macraff_p_char_2;
 *   char* TSODLULS_macraff_p_char_3;
 *   char TSODLULS_macraff_char;
*/
#define TSODLULS_SWAP_VAR_4(a, b, size)\
  do{\
    TSODLULS_macraff_p_char = (char *) (a);\
    TSODLULS_macraff_p_char_2 = (char *) (b);\
    TSODLULS_macraff_p_char_3 = TSODLULS_macraff_p_char + (size);\
    do{\
      TSODLULS_macraff_char = *TSODLULS_macraff_p_char;\
      *TSODLULS_macraff_p_char++ = *TSODLULS_macraff_p_char_2;\
      *TSODLULS_macraff_p_char_2++ = TSODLULS_macraff_char;\
    }while(TSODLULS_macraff_p_char < TSODLULS_macraff_p_char_3);\
  }while(0);



/**
 * Byte-wise swap two items of size SIZE taking into account chunk_size.
 * It's half a macraff because it needs:
 *   size_t TSODLULS_macraff_i_chunk_size = TSODLULS_CHUNK_SIZE_FOR_SWAP_VAR(i_element_size);
 * that cannot be given as an argument to the macro for compatibility with others SWAP_VAR
 * (adding always a fourth argument yields unused variable notices on compilation).
*/
#define TSODLULS_SWAP_VAR_5(a, b, size)\
  switch(TSODLULS_macraff_i_chunk_size){\
    case TSODLULS_CHAR_SWAP:\
      do{\
        size_t isize_tsodluls_swap_var = (size);\
        char* p_c_tsodluls_swap_var_1 = (char *) (a);\
        char* p_c_tsodluls_swap_var_2 = (char *) (b);\
        do{\
          char c_tsodluls_swap_var_1 = *p_c_tsodluls_swap_var_1;\
          *p_c_tsodluls_swap_var_1++ = *p_c_tsodluls_swap_var_2;\
          *p_c_tsodluls_swap_var_2++ = c_tsodluls_swap_var_1;\
        }while(--isize_tsodluls_swap_var > 0);\
      }while(0);\
    break;\
    case TSODLULS_INT_SWAP:\
      do{\
        size_t isize_tsodluls_swap_var = (size);\
        int* p_i_tsodluls_swap_var_1 = (int *) (a);\
        int* p_i_tsodluls_swap_var_2 = (int *) (b);\
        do{\
          int i_tsodluls_swap_var_1 = *p_i_tsodluls_swap_var_1;\
          *p_i_tsodluls_swap_var_1++ = *p_i_tsodluls_swap_var_2;\
          *p_i_tsodluls_swap_var_2++ = i_tsodluls_swap_var_1;\
        }while((isize_tsodluls_swap_var -= sizeof(int)) > 0);\
      }while(0);\
    break;\
    case TSODLULS_LONG_INT_SWAP:\
      do{\
        size_t isize_tsodluls_swap_var = (size);\
        long int* p_li_tsodluls_swap_var_1 = (long int *) (a);\
        long int* p_li_tsodluls_swap_var_2 = (long int *) (b);\
        do{\
          long int li_tsodluls_swap_var_1 = *p_li_tsodluls_swap_var_1;\
          *p_li_tsodluls_swap_var_1++ = *p_li_tsodluls_swap_var_2;\
          *p_li_tsodluls_swap_var_2++ = li_tsodluls_swap_var_1;\
        }while((isize_tsodluls_swap_var -= sizeof(long int)) > 0);\
      }while(0);\
    break;\
    case TSODLULS_LONG_LONG_INT_SWAP:\
      do{\
        size_t isize_tsodluls_swap_var = (size);\
        long long int* p_lli_tsodluls_swap_var_1 = (long long int *) (a);\
        long long int* p_lli_tsodluls_swap_var_2 = (long long int *) (b);\
        do{\
          long long int lli_tsodluls_swap_var_1 = *p_lli_tsodluls_swap_var_1;\
          *p_lli_tsodluls_swap_var_1++ = *p_lli_tsodluls_swap_var_2;\
          *p_lli_tsodluls_swap_var_2++ = lli_tsodluls_swap_var_1;\
        }while((isize_tsodluls_swap_var -= sizeof(long long int)) > 0);\
      }while(0);\
    break;\
    case TSODLULS_SHORT_INT_SWAP:\
      do{\
        size_t isize_tsodluls_swap_var = (size);\
        short int* p_si_tsodluls_swap_var_1 = (short int *) (a);\
        short int* p_si_tsodluls_swap_var_2 = (short int *) (b);\
        do{\
          short int si_tsodluls_swap_var_1 = *p_si_tsodluls_swap_var_1;\
          *p_si_tsodluls_swap_var_1++ = *p_si_tsodluls_swap_var_2;\
          *p_si_tsodluls_swap_var_2++ = si_tsodluls_swap_var_1;\
        }while((isize_tsodluls_swap_var -= sizeof(short int)) > 0);\
      }while(0);\
    break;\
  }



/**
 * Byte-wise swap two items of size SIZE taking into account chunk_size.
 * A macraff version of TSODLULS_SWAP_VAR_5.
 * This macraff requires the following auxiliary variables:
 *   size_t TSODLULS_macraff_i_chunk_size = TSODLULS_CHUNK_SIZE_FOR_SWAP_VAR(i_element_size);
 *   size_t TSODLULS_macraff_isize;
 *   t_TSODLULS_sizables_union TSODLULS_macraff_sizables_union;
 *   t_TSODLULS_sizables_pointers_union TSODLULS_macraff_sizables_pointers_union_1;
 *   t_TSODLULS_sizables_pointers_union TSODLULS_macraff_sizables_pointers_union_2;
*/
#define TSODLULS_SWAP_VAR_6(a, b, size)\
  do{\
    TSODLULS_macraff_isize = (size);\
    switch(TSODLULS_macraff_i_chunk_size){\
      case TSODLULS_CHAR_SWAP:\
        TSODLULS_macraff_sizables_pointers_union_1.c = (char *) (a);\
        TSODLULS_macraff_sizables_pointers_union_2.c = (char *) (b);\
        do{\
          TSODLULS_macraff_sizables_union.c = *TSODLULS_macraff_sizables_pointers_union_1.c;\
          *TSODLULS_macraff_sizables_pointers_union_1.c++ = *TSODLULS_macraff_sizables_pointers_union_2.c;\
          *TSODLULS_macraff_sizables_pointers_union_2.c++ = TSODLULS_macraff_sizables_union.c;\
        }while(--TSODLULS_macraff_isize > 0);\
      break;\
      case TSODLULS_INT_SWAP:\
        TSODLULS_macraff_sizables_pointers_union_1.i = (int *) (a);\
        TSODLULS_macraff_sizables_pointers_union_2.i = (int *) (b);\
        do{\
          TSODLULS_macraff_sizables_union.i = *TSODLULS_macraff_sizables_pointers_union_1.i;\
          *TSODLULS_macraff_sizables_pointers_union_1.i++ = *TSODLULS_macraff_sizables_pointers_union_2.i;\
          *TSODLULS_macraff_sizables_pointers_union_2.i++ = TSODLULS_macraff_sizables_union.i;\
        }while((TSODLULS_macraff_isize -= sizeof(int)) > 0);\
      break;\
      case TSODLULS_LONG_INT_SWAP:\
        TSODLULS_macraff_sizables_pointers_union_1.l = (long int *) (a);\
        TSODLULS_macraff_sizables_pointers_union_2.l = (long int *) (b);\
        do{\
          TSODLULS_macraff_sizables_union.l = *TSODLULS_macraff_sizables_pointers_union_1.l;\
          *TSODLULS_macraff_sizables_pointers_union_1.l++ = *TSODLULS_macraff_sizables_pointers_union_2.l;\
          *TSODLULS_macraff_sizables_pointers_union_2.l++ = TSODLULS_macraff_sizables_union.l;\
        }while((TSODLULS_macraff_isize -= sizeof(long int)) > 0);\
      break;\
      case TSODLULS_LONG_LONG_INT_SWAP:\
        TSODLULS_macraff_sizables_pointers_union_1.ll = (long long int *) (a);\
        TSODLULS_macraff_sizables_pointers_union_2.ll = (long long int *) (b);\
        do{\
          TSODLULS_macraff_sizables_union.ll = *TSODLULS_macraff_sizables_pointers_union_1.ll;\
          *TSODLULS_macraff_sizables_pointers_union_1.ll++ = *TSODLULS_macraff_sizables_pointers_union_2.ll;\
          *TSODLULS_macraff_sizables_pointers_union_2.ll++ = TSODLULS_macraff_sizables_union.ll;\
        }while((TSODLULS_macraff_isize -= sizeof(long long int)) > 0);\
      break;\
      case TSODLULS_SHORT_INT_SWAP:\
        TSODLULS_macraff_sizables_pointers_union_1.s = (short int *) (a);\
        TSODLULS_macraff_sizables_pointers_union_2.s = (short int *) (b);\
        do{\
          TSODLULS_macraff_sizables_union.s = *TSODLULS_macraff_sizables_pointers_union_1.s;\
          *TSODLULS_macraff_sizables_pointers_union_1.s++ = *TSODLULS_macraff_sizables_pointers_union_2.s;\
          *TSODLULS_macraff_sizables_pointers_union_2.s++ = TSODLULS_macraff_sizables_union.s;\
        }while((TSODLULS_macraff_isize -= sizeof(short int)) > 0);\
      break;\
    }\
  }while(0);\



/**
 * This strategy is from TimSort:
 * See wikipedia and the source code/and the emails by Tim Peter's on the mailing list of Python.
 * It maintains the invariant that any stack element is bigger than the sum of the at most two next stack elements.
 * The upper on the stack, the (exponentially like Fibonacci) lighter.
 * The case i_merge_at > 1 was added to maintain the invariant and correct the upper bound on the number of runs.
 */
#define TSODLULS_natural_merge_main_strategy__Tim_sort \
while(merge_state.i_run_instances_count > 1){\
  size_t i_merge_at = merge_state.i_run_instances_count - 2;\
  if(\
      (i_merge_at > 0\
      && merge_state.arr_run_instances[i_merge_at - 1].i_length <= merge_state.arr_run_instances[i_merge_at].i_length + merge_state.arr_run_instances[i_merge_at + 1].i_length\
      )\
    ||\
      (i_merge_at > 1\
      && merge_state.arr_run_instances[i_merge_at - 2].i_length <= merge_state.arr_run_instances[i_merge_at - 1].i_length + merge_state.arr_run_instances[i_merge_at].i_length\
      )\
  ){\
    if(merge_state.arr_run_instances[i_merge_at - 1].i_length < merge_state.arr_run_instances[i_merge_at + 1].i_length){\
      --i_merge_at;\
    }\
    i_compare_result = TSODLULS_MERGE_TWO_RUNS(&merge_state, i_merge_at);\
    if(i_compare_result != 0){\
      goto clean_and_return_error;\
    }\
  }\
  else if(merge_state.arr_run_instances[i_merge_at].i_length <= merge_state.arr_run_instances[i_merge_at + 1].i_length){\
    i_compare_result = TSODLULS_MERGE_TWO_RUNS(&merge_state, i_merge_at);\
    if(i_compare_result != 0){\
      goto clean_and_return_error;\
    }\
  }\
  else{\
    break;\
  }\
}\



/**
 * This strategy is from ShiversSort:
 * see the research report by Olin Shivers, Georgia Institute of Technology, 2002.
 * It uses bitwise tricks to check condition on floor of logarithms in base 2 of runs lengths.
 * When I benchmark it, it is slightly faster than Tim's sort strategy.
 */
#define TSODLULS_natural_merge_main_strategy__Shivers_sort \
while(merge_state.i_run_instances_count > 1){\
  size_t i_merge_at = merge_state.i_run_instances_count - 2;\
  size_t i_order_of_magnitude = merge_state.arr_run_instances[i_merge_at + 1].i_length;\
  if(i_order_of_magnitude < ((~i_order_of_magnitude) & merge_state.arr_run_instances[i_merge_at].i_length) ){\
    break;\
  }\
  i_compare_result = TSODLULS_MERGE_TWO_RUNS(&merge_state, i_merge_at);\
  if(i_compare_result != 0){\
    goto clean_and_return_error;\
  }\
}\



/**
 * This strategy is from AdaptiveShiversSort:
 * see the articles by Vincent Jugé, for example 1024 Bulletin de la SIF, avril 2020, in French,
 * or the preprint on arXiv or SODA 2020 proceedings.
 * It uses bitwise tricks to check condition on floor of logarithms in base 2 of runs lengths.
 * When I benchmark it, it is slightly faster than Tim's sort strategy.
 * Despite its ressemblance with Shivers's sort,
 * the distinct properties of this strategy make that JugéSort would probably be a better name than AdaptiveShiversSort,
 * or an even better name for the whole algorithm should be TimShiversJugéSort and I must have missed many names ;)
 * With AdaptiveShiversSort we avoid 'é' and diacritics in function names ;P
 */
#define TSODLULS_natural_merge_main_strategy__adaptive_Shivers_sort \
while(merge_state.i_run_instances_count > 2){\
  size_t i_merge_at = merge_state.i_run_instances_count - 3;\
  size_t i_order_of_magnitude = merge_state.arr_run_instances[i_merge_at + 1].i_length | merge_state.arr_run_instances[i_merge_at + 2].i_length;\
  if(i_order_of_magnitude < ((~i_order_of_magnitude) & merge_state.arr_run_instances[i_merge_at].i_length) ){\
    break;\
  }\
  i_compare_result = TSODLULS_MERGE_TWO_RUNS(&merge_state, i_merge_at);\
  if(i_compare_result != 0){\
    goto clean_and_return_error;\
  }\
}\



/**
 * This strategy is from AdaptiveShiversSort:
 * a variant of the previous strategy that is probably closer to what Vincent Jugé intended.
 */
#define TSODLULS_natural_merge_main_strategy__adaptive_Shivers_sort_v2 \
while(merge_state.i_run_instances_count > 2){\
  size_t i_merge_at = merge_state.i_run_instances_count - 3;\
  size_t i_order_of_magnitude = merge_state.arr_run_instances[i_merge_at + 1].i_length | merge_state.arr_run_instances[i_merge_at + 2].i_length;\
  if(i_order_of_magnitude < ((~i_order_of_magnitude) & merge_state.arr_run_instances[i_merge_at].i_length) ){\
    break;\
  }\
  if(merge_state.arr_run_instances[i_merge_at + 2].i_length < merge_state.arr_run_instances[i_merge_at].i_length){\
    ++i_merge_at;\
  }\
  i_compare_result = TSODLULS_MERGE_TWO_RUNS(&merge_state, i_merge_at);\
  if(i_compare_result != 0){\
    goto clean_and_return_error;\
  }\
}\



/**
 * This strategy is from AdaptiveShiversSort:
 * a variant of the previous strategy that is probably not what Vincent Jugé intended,
 * but we test it anyway.
 */
#define TSODLULS_natural_merge_main_strategy__adaptive_Shivers_sort_v3 \
while(merge_state.i_run_instances_count > 2){\
  size_t i_merge_at = merge_state.i_run_instances_count - 2;\
  size_t i_order_of_magnitude = merge_state.arr_run_instances[i_merge_at].i_length | merge_state.arr_run_instances[i_merge_at + 1].i_length;\
  if(i_order_of_magnitude < ((~i_order_of_magnitude) & merge_state.arr_run_instances[i_merge_at - 1].i_length) ){\
    break;\
  }\
  i_compare_result = TSODLULS_MERGE_TWO_RUNS(&merge_state, i_merge_at);\
  if(i_compare_result != 0){\
    goto clean_and_return_error;\
  }\
}\


