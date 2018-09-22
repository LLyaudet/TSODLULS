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
 * Comparison function
 * uint8 pointers
 */
int TSODLULS_compare_uint8_direct(const void *a, const void *b){
  const uint8_t *c = (const uint8_t *) a;
  const uint8_t *d = (const uint8_t *) b;
  return (*c > *d) - (*c < *d);
}//end function TSODLULS_compare_uint8_direct()



/**
 * Comparison function
 * uint16 pointers
 */
int TSODLULS_compare_uint16_direct(const void *a, const void *b){
  const uint16_t *c = (const uint16_t *) a;
  const uint16_t *d = (const uint16_t *) b;
  return (*c > *d) - (*c < *d);
}//end function TSODLULS_compare_uint16_direct()



/**
 * Comparison function
 * uint32 pointers
 */
int TSODLULS_compare_uint32_direct(const void *a, const void *b){
  const uint32_t *c = (const uint32_t *) a;
  const uint32_t *d = (const uint32_t *) b;
  return (*c > *d) - (*c < *d);
}//end function TSODLULS_compare_uint32_direct()



/**
 * Comparison function
 * uint64 pointers
 */
int TSODLULS_compare_uint64_direct(const void *a, const void *b){
  const uint64_t *c = (const uint64_t *) a;
  const uint64_t *d = (const uint64_t *) b;
  return (*c > *d) - (*c < *d);
}//end function TSODLULS_compare_uint64_direct()



/**
 * Comparison function
 * int8 pointers
 */
int TSODLULS_compare_int8_direct(const void *a, const void *b){
  const int8_t *c = (const int8_t *) a;
  const int8_t *d = (const int8_t *) b;
  return (*c > *d) - (*c < *d);
}//end function TSODLULS_compare_int8_direct()



/**
 * Comparison function
 * int16 pointers
 */
int TSODLULS_compare_int16_direct(const void *a, const void *b){
  const int16_t *c = (const int16_t *) a;
  const int16_t *d = (const int16_t *) b;
  return (*c > *d) - (*c < *d);
}//end function TSODLULS_compare_int16_direct()



/**
 * Comparison function
 * int32 pointers
 */
int TSODLULS_compare_int32_direct(const void *a, const void *b){
  const int32_t *c = (const int32_t *) a;
  const int32_t *d = (const int32_t *) b;
  return (*c > *d) - (*c < *d);
}//end function TSODLULS_compare_int32_direct()



/**
 * Comparison function
 * int64 pointers
 */
int TSODLULS_compare_int64_direct(const void *a, const void *b){
  const int64_t *c = (const int64_t *) a;
  const int64_t *d = (const int64_t *) b;
  return (*c > *d) - (*c < *d);
}//end function TSODLULS_compare_int64_direct()



/**
 * Comparison function
 * float pointers
 */
int TSODLULS_compare_float_direct(const void *a, const void *b){
  const float *c = (const float *) a;
  const float *d = (const float *) b;
  //return (*c > *d) - (*c < *d);
  //there is a bug in float comparison!
  //(or maybe it is a feature than (-)nan are never more than, equal to, or less than other numbers)
  //uncomment previous line and try test2 with the random seed 1534188456 for example
  //at least on my laptop with core i5, it gets an -nan
  //that is sorted after positive numbers and before negative numbers
  //so that the array is not correctly sorted even if you only look at the float that are different from nan or -nan.
  //I don't know if the bug is in gcc or in the i5 processor, or if it is a feature in IEEE spec.
  union ieee754_float temp_c;
  union ieee754_float temp_d;
  temp_c.f = *c;
  temp_d.f = *d;
  //negative first
  if(temp_c.ieee.negative == 1){
    if(temp_d.ieee.negative == 1){
      if(temp_c.ieee.exponent != temp_d.ieee.exponent){
        //inverse formula because of negativity
        return (temp_d.ieee.exponent > temp_c.ieee.exponent) - (temp_d.ieee.exponent < temp_c.ieee.exponent);
      }
      //inverse formula because of negativity
      return (temp_d.ieee.mantissa > temp_c.ieee.mantissa) - (temp_d.ieee.mantissa < temp_c.ieee.mantissa);
    }
    return -1;
  }
  else{
    if(temp_d.ieee.negative == 1){
      return 1;
    }
    if(temp_c.ieee.exponent != temp_d.ieee.exponent){
      return (temp_c.ieee.exponent > temp_d.ieee.exponent) - (temp_c.ieee.exponent < temp_d.ieee.exponent);
    }
    return (temp_c.ieee.mantissa > temp_d.ieee.mantissa) - (temp_c.ieee.mantissa < temp_d.ieee.mantissa);
  }
}//end function TSODLULS_compare_float_direct()



/**
 * Comparison function
 * double pointers
 */
int TSODLULS_compare_double_direct(const void *a, const void *b){
  const double *c = (const double *) a;
  const double *d = (const double *) b;
  //return (*c > *d) - (*c < *d);
  //there is a bug in double comparison!
  //(or maybe it is a feature than (-)nan are never more than, equal to, or less than other numbers)
  //uncomment previous line and try test2 with the random seed 1534274833 for example
  union ieee754_double temp_c;
  union ieee754_double temp_d;
  temp_c.d = *c;
  temp_d.d = *d;
  //negative first
  if(temp_c.ieee.negative == 1){
    if(temp_d.ieee.negative == 1){
      if(temp_c.ieee.exponent != temp_d.ieee.exponent){
        //inverse formula because of negativity
        return (temp_d.ieee.exponent > temp_c.ieee.exponent) - (temp_d.ieee.exponent < temp_c.ieee.exponent);
      }
      if(temp_c.ieee.mantissa0 != temp_d.ieee.mantissa0){
        //inverse formula because of negativity
        return (temp_d.ieee.mantissa0 > temp_c.ieee.mantissa0) - (temp_d.ieee.mantissa0 < temp_c.ieee.mantissa0);
      }
      //inverse formula because of negativity
      return (temp_d.ieee.mantissa1 > temp_c.ieee.mantissa1) - (temp_d.ieee.mantissa1 < temp_c.ieee.mantissa1);
    }
    return -1;
  }
  else{
    if(temp_d.ieee.negative == 1){
      return 1;
    }
    if(temp_c.ieee.exponent != temp_d.ieee.exponent){
      return (temp_c.ieee.exponent > temp_d.ieee.exponent) - (temp_c.ieee.exponent < temp_d.ieee.exponent);
    }
    if(temp_c.ieee.mantissa0 != temp_d.ieee.mantissa0){
      return (temp_c.ieee.mantissa0 > temp_d.ieee.mantissa0) - (temp_c.ieee.mantissa0 < temp_d.ieee.mantissa0);
    }
    return (temp_c.ieee.mantissa1 > temp_d.ieee.mantissa1) - (temp_c.ieee.mantissa1 < temp_d.ieee.mantissa1);
  }
}//end function TSODLULS_compare_double_direct()



/**
 * Comparison function
 * uint8 in TSODLULS cell
 */
int TSODLULS_compare_uint8_in_cell(const void *a, const void *b){
  const t_TSODLULS_sort_element *c = (const t_TSODLULS_sort_element *) a;
  const t_TSODLULS_sort_element *d = (const t_TSODLULS_sort_element *) b;
  return (*(c->s_key) > *(d->s_key)) - (*(c->s_key) < *(d->s_key));
}//end function TSODLULS_compare_uint8_in_cell()



/**
 * Comparison function
 * uint16 in TSODLULS cell
 */
int TSODLULS_compare_uint16_in_cell(const void *a, const void *b){
  const t_TSODLULS_sort_element *c = (const t_TSODLULS_sort_element *) a;
  const t_TSODLULS_sort_element *d = (const t_TSODLULS_sort_element *) b;
  uint16_t ui16_c;
  uint16_t ui16_d;
  ui16_c = *((uint16_t*)c->s_key);
  ui16_d = *((uint16_t*)d->s_key);
  #if __BYTE_ORDER == __LITTLE_ENDIAN
    ui16_c = bswap_16(ui16_c);
    ui16_d = bswap_16(ui16_d);
  #endif
  return (ui16_c > ui16_d) - (ui16_c < ui16_d);
}//end function TSODLULS_compare_uint16_in_cell()



/**
 * Comparison function
 * uint32 in TSODLULS cell
 */
int TSODLULS_compare_uint32_in_cell(const void *a, const void *b){
  const t_TSODLULS_sort_element *c = (const t_TSODLULS_sort_element *) a;
  const t_TSODLULS_sort_element *d = (const t_TSODLULS_sort_element *) b;
  uint32_t ui32_c;
  uint32_t ui32_d;
  ui32_c = *((uint32_t*)c->s_key);
  ui32_d = *((uint32_t*)d->s_key);
  #if __BYTE_ORDER == __LITTLE_ENDIAN
    ui32_c = bswap_32(ui32_c);
    ui32_d = bswap_32(ui32_d);
  #endif
  return (ui32_c > ui32_d) - (ui32_c < ui32_d);
}//end function TSODLULS_compare_uint32_in_cell()



/**
 * Comparison function
 * uint64 in TSODLULS cell
 */
int TSODLULS_compare_uint64_in_cell(const void *a, const void *b){
  const t_TSODLULS_sort_element *c = (const t_TSODLULS_sort_element *) a;
  const t_TSODLULS_sort_element *d = (const t_TSODLULS_sort_element *) b;
  uint64_t ui64_c;
  uint64_t ui64_d;
  ui64_c = *((uint64_t*)c->s_key);
  ui64_d = *((uint64_t*)d->s_key);
  #if __BYTE_ORDER == __LITTLE_ENDIAN
    ui64_c = bswap_64(ui64_c);
    ui64_d = bswap_64(ui64_d);
  #endif
  return (ui64_c > ui64_d) - (ui64_c < ui64_d);
}//end function TSODLULS_compare_uint64_in_cell()



/**
 * Comparison function
 * nextified key in TSODLULS cell
 */
int TSODLULS_compare_nextified_key_in_cell(const void *a, const void *b){
  const t_TSODLULS_sort_element *c = (const t_TSODLULS_sort_element *) a;
  const t_TSODLULS_sort_element *d = (const t_TSODLULS_sort_element *) b;
  int i_result = 0;
  size_t i;
  size_t i_max;
  i_max = c->i_key_size;
  if(d->i_key_size < i_max){
    i_max = d->i_key_size;
  }
  for(i = 0; i < i_max; ++i){
    i_result = ((int)(c->s_key[i])) - ((int)(d->s_key[i]));
    if(i_result != 0){
      break;
    }
  }
  return i_result;
}//end function TSODLULS_compare_nextified_key_in_cell()



