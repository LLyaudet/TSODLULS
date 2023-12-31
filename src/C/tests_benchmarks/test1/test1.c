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

©Copyright 2018-2023 Laurent Lyaudet
*/
/*
Explanations for this test:
All 2^32 32 bits integers are converted to float and back to check that conversion is one to one.
i_max couples of 32 bits integers are randomly chosen,
and it is tested that comparison between them yields the same result
as comparison between the corresponding floats.

i_max 64 bits integers are randomly chosen,
and are converted to double and back to check that conversion is one to one.
i_max couples of 64 bits integers are randomly chosen,
and it is tested that comparison between them yields the same result
as comparison between the corresponding doubles.

All 2^8 8 bits integers are converted to signed 8 bits integers and back to check that conversion is one to one.
All 2^16 couples of 8 bits integers are generated,
and it is tested that comparison between them yields the same result
as comparison between the corresponding signed integers.

All 2^16 16 bits integers are converted to signed 16 bits integers and back to check that conversion is one to one.
All 2^32 couples of 16 bits integers are generated,
and it is tested that comparison between them yields the same result
as comparison between the corresponding signed integers.

All 2^32 32 bits integers are converted to signed 32 bits integers and back to check that conversion is one to one.
i_max couples of 32 bits integers are randomly chosen,
and it is tested that comparison between them yields the same result
as comparison between the corresponding signed integers.

i_max 64 bits integers are randomly chosen,
and are converted to signed integers and back to check that conversion is one to one.
i_max couples of 64 bits integers are randomly chosen,
and it is tested that comparison between them yields the same result
as comparison between the corresponding signed integers.

All these tests are performed twice: one time with the functions in TSODLULS_finite_orders.c,
and one more time with the macraffs in TSODLULS_finite_orders__macro.h.
*/

#include "../test_functions.c"



int main(int argc, char *argv[]){

  int i_result = 0;
  srand(time(0));

  uint64_t i;
  uint64_t j;
  uint64_t i_max = 1000000000;

  uint8_t ui_8;
  uint8_t ui_8_2;
  uint16_t ui_16;
  uint16_t ui_16_2;
  uint32_t ui_32;
  uint32_t ui_32_2;
  uint64_t ui_64;
  uint64_t ui_64_2;
  int8_t i_8;
  int8_t i_8_2;
  int16_t i_16;
  int16_t i_16_2;
  int32_t i_32;
  int32_t i_32_2;
  int64_t i_64;
  int64_t i_64_2;
  float f_float;
  float f_float_2;
  double f_double;
  double f_double_2;

  //macraffs variables
  union ieee754_float TSODLULS_macraff_ieee754_float;
  union ieee754_double TSODLULS_macraff_ieee754_double;
  uint8_t TSODLULS_macraff_ui8;
  uint16_t TSODLULS_macraff_ui16;
  uint32_t TSODLULS_macraff_ui32;
  uint64_t TSODLULS_macraff_ui64;
  int8_t TSODLULS_macraff_i8;
  int16_t TSODLULS_macraff_i16;
  int32_t TSODLULS_macraff_i32;
  int64_t TSODLULS_macraff_i64;

  do{
    /*
    f_double = INFINITY;
    printf(" %f : ", f_double);
    print_bits_for(&f_double, sizeof(f_double));
    printf("\n");
    */

    printf("RAND_MAX is %d\n", RAND_MAX);

    //------------------------------------------------------------------------------------
    //Testing uint vs float/double
    //------------------------------------------------------------------------------------
    for(i = 0; i <= UINT32_MAX; ++i){
      ui_32 = (uint32_t)i;
      f_float = TSODLULS_get_float_from_uint(ui_32);
      ui_32_2 = TSODLULS_get_uint_from_float(f_float);
      if(ui_32 != ui_32_2){
        printf("%u has been converted to %f and back to %u\n.", ui_32, f_float, ui_32_2);
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and floats works.\n");

    for(i = 0; i <= UINT32_MAX; ++i){
      ui_32 = (uint32_t)i;
      TSODLULS_get_float_from_uint__macraff(f_float, ui_32);
      TSODLULS_get_uint_from_float__macraff(ui_32_2, f_float);
      if(ui_32 != ui_32_2){
        printf("%u has been converted to %f and back to %u\n.", ui_32, f_float, ui_32_2);
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and floats works (macraffs).\n");

    for(i = 0; i < i_max; ++i){
      ui_32 = (uint32_t)rand();
      ui_32_2 = (uint32_t)rand();
      //with glibc we're missing one bit of randomness, we do exhaustive search on it
      if((i & 1) > 0){
        ui_32 += (((uint32_t)1) << 31);
      }
      if((i & 2) > 0){
        ui_32_2 += (((uint32_t)1) << 31);
      }
      f_float = TSODLULS_get_float_from_uint(ui_32);
      f_float_2 = TSODLULS_get_float_from_uint(ui_32_2);

      //nan floats are never !=, <=, or >=
      //hence we check that the order on the unsigned integers is a linear extension
      //of the partial order on floats
      if(
           (ui_32 == ui_32_2 && f_float != f_float_2)
        || (ui_32 > ui_32_2 && f_float <= f_float_2)
        || (ui_32 < ui_32_2 && f_float >= f_float_2)
      ){
        printf("%u has been converted to %f\n.", ui_32, f_float);
        printf("%u has been converted to %f\n.", ui_32_2, f_float_2);
        printf("Order is not preserved.");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and floats preserves the order.\n");

    for(i = 0; i < i_max; ++i){
      ui_32 = (uint32_t)rand();
      ui_32_2 = (uint32_t)rand();
      //with glibc we're missing one bit of randomness, we do exhaustive search on it
      if((i & 1) > 0){
        ui_32 += (((uint32_t)1) << 31);
      }
      if((i & 2) > 0){
        ui_32_2 += (((uint32_t)1) << 31);
      }
      TSODLULS_get_float_from_uint__macraff(f_float, ui_32);
      TSODLULS_get_float_from_uint__macraff(f_float_2, ui_32_2);

      //nan floats are never !=, <=, or >=
      //hence we check that the order on the unsigned integers is a linear extension
      //of the partial order on floats
      if(
           (ui_32 == ui_32_2 && f_float != f_float_2)
        || (ui_32 > ui_32_2 && f_float <= f_float_2)
        || (ui_32 < ui_32_2 && f_float >= f_float_2)
      ){
        printf("%u has been converted to %f\n.", ui_32, f_float);
        printf("%u has been converted to %f\n.", ui_32_2, f_float_2);
        printf("Order is not preserved.");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and floats preserves the order (macraffs).\n");

    for(i = 0; i < i_max; ++i){
      ui_32 = (uint32_t)rand();
      ui_32_2 = (uint32_t)rand();
      //with glibc we're missing one bit of randomness, we do exhaustive search on it
      if((i & 1) > 0){
        ui_32 += (((uint32_t)1) << 31);
      }
      if((i & 2) > 0){
        ui_32_2 += (((uint32_t)1) << 31);
      }

      ui_64 = (((uint64_t) ui_32) << 32) + ((uint64_t) ui_32_2);

      f_double = TSODLULS_get_double_from_uint(ui_64);
      ui_64_2 = TSODLULS_get_uint_from_double(f_double);
      if(ui_64 != ui_64_2){
        printf(
            "%lu has been converted to %f and back to %lu\n.",
            ui_64,
            f_double,
            ui_64_2
        );
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and doubles works.\n");

    for(i = 0; i < i_max; ++i){
      ui_32 = (uint32_t)rand();
      ui_32_2 = (uint32_t)rand();
      //with glibc we're missing one bit of randomness, we do exhaustive search on it
      if((i & 1) > 0){
        ui_32 += (((uint32_t)1) << 31);
      }
      if((i & 2) > 0){
        ui_32_2 += (((uint32_t)1) << 31);
      }

      ui_64 = (((uint64_t) ui_32) << 32) + ((uint64_t) ui_32_2);

      TSODLULS_get_double_from_uint__macraff(f_double, ui_64);
      TSODLULS_get_uint_from_double__macraff(ui_64_2, f_double);
      if(ui_64 != ui_64_2){
        printf(
            "%lu has been converted to %f and back to %lu\n.",
            ui_64,
            f_double,
            ui_64_2
        );
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and doubles works (macraffs).\n");

    for(i = 0; i < i_max; ++i){
      ui_32 = (uint32_t)rand();
      ui_32_2 = (uint32_t)rand();
      //with glibc we're missing one bit of randomness, we do exhaustive search on it
      if((i & 1) > 0){
        ui_32 += (((uint32_t)1) << 31);
      }
      if((i & 2) > 0){
        ui_32_2 += (((uint32_t)1) << 31);
      }
      ui_64 = (((uint64_t) ui_32) << 32) + ((uint64_t) ui_32_2);
      f_double = TSODLULS_get_double_from_uint(ui_64);

      ui_32 = (uint32_t)rand();
      ui_32_2 = (uint32_t)rand();
      //with glibc we're missing one bit of randomness, we do exhaustive search on it
      if((i & 4) > 0){
        ui_32 += (((uint32_t)1) << 31);
      }
      if((i & 8) > 0){
        ui_32_2 += (((uint32_t)1) << 31);
      }
      ui_64_2 = (((uint64_t) ui_32) << 32) + ((uint64_t) ui_32_2);
      f_double_2 = TSODLULS_get_double_from_uint(ui_64_2);

      //nan doubles are never !=, <=, or >=
      //hence we check that the order on the unsigned integers is a linear extension
      //of the partial order on doubles
      if(
           (ui_64 == ui_64_2 && f_double != f_double_2)
        || (ui_64 > ui_64_2 && f_double <= f_double_2)
        || (ui_64 < ui_64_2 && f_double >= f_double_2)
      ){
        printf("%lu has been converted to %f\n.", ui_64, f_double);
        printf("%lu has been converted to %f\n.", ui_64_2, f_double_2);
        printf("Order is not preserved.");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and doubles preserves the order.\n");

    for(i = 0; i < i_max; ++i){
      ui_32 = (uint32_t)rand();
      ui_32_2 = (uint32_t)rand();
      //with glibc we're missing one bit of randomness, we do exhaustive search on it
      if((i & 1) > 0){
        ui_32 += (((uint32_t)1) << 31);
      }
      if((i & 2) > 0){
        ui_32_2 += (((uint32_t)1) << 31);
      }
      ui_64 = (((uint64_t) ui_32) << 32) + ((uint64_t) ui_32_2);
      TSODLULS_get_double_from_uint__macraff(f_double, ui_64);

      ui_32 = (uint32_t)rand();
      ui_32_2 = (uint32_t)rand();
      //with glibc we're missing one bit of randomness, we do exhaustive search on it
      if((i & 4) > 0){
        ui_32 += (((uint32_t)1) << 31);
      }
      if((i & 8) > 0){
        ui_32_2 += (((uint32_t)1) << 31);
      }
      ui_64_2 = (((uint64_t) ui_32) << 32) + ((uint64_t) ui_32_2);
      TSODLULS_get_double_from_uint__macraff(f_double_2, ui_64_2);

      //nan doubles are never !=, <=, or >=
      //hence we check that the order on the unsigned integers is a linear extension
      //of the partial order on doubles
      if(
           (ui_64 == ui_64_2 && f_double != f_double_2)
        || (ui_64 > ui_64_2 && f_double <= f_double_2)
        || (ui_64 < ui_64_2 && f_double >= f_double_2)
      ){
        printf("%lu has been converted to %f\n.", ui_64, f_double);
        printf("%lu has been converted to %f\n.", ui_64_2, f_double_2);
        printf("Order is not preserved.");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and doubles preserves the order (macraffs).\n");



    //------------------------------------------------------------------------------------
    //Testing uint vs int
    //------------------------------------------------------------------------------------
    for(i = 0; i <= UINT8_MAX; ++i){
      ui_8 = (uint8_t)i;
      i_8 = TSODLULS_get_int8_from_uint8(ui_8);
      ui_8_2 = TSODLULS_get_uint8_from_int8(i_8);
      if(ui_8 != ui_8_2){
        printf("%u has been converted to %d and back to %u\n.", ui_8, i_8, ui_8_2);
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and signed integers (8) works.\n");

    for(i = 0; i <= UINT8_MAX; ++i){
      ui_8 = (uint8_t)i;
      TSODLULS_get_int8_from_uint8__macraff(i_8, ui_8);
      TSODLULS_get_uint8_from_int8__macraff(ui_8_2, i_8);
      if(ui_8 != ui_8_2){
        printf("%u has been converted to %d and back to %u\n.", ui_8, i_8, ui_8_2);
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and signed integers (8) works (macraffs).\n");

    for(i = 0; i <= UINT8_MAX; ++i){
      ui_8 = (uint8_t)i;
      i_8 = TSODLULS_get_int8_from_uint8(ui_8);
      for(j = 0; j <= UINT8_MAX; ++j){
        ui_8_2 = (uint8_t)j;
        i_8_2 = TSODLULS_get_int8_from_uint8(ui_8_2);
        if(
             (ui_8 == ui_8_2 && i_8 != i_8_2)
          || (ui_8 > ui_8_2 && i_8 <= i_8_2)
          || (ui_8 < ui_8_2 && i_8 >= i_8_2)
        ){
          printf("%u has been converted to %d\n.", ui_8, i_8);
          printf("%u has been converted to %d\n.", ui_8_2, i_8_2);
          printf("Order is not preserved.");
          i_result = -1;
          break;
        }
      }
      if(i_result != 0){
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and signed integers (8) preserves the order.\n");

    for(i = 0; i <= UINT8_MAX; ++i){
      ui_8 = (uint8_t)i;
      TSODLULS_get_int8_from_uint8__macraff(i_8, ui_8);
      for(j = 0; j <= UINT8_MAX; ++j){
        ui_8_2 = (uint8_t)j;
        TSODLULS_get_int8_from_uint8__macraff(i_8_2, ui_8_2);
        if(
             (ui_8 == ui_8_2 && i_8 != i_8_2)
          || (ui_8 > ui_8_2 && i_8 <= i_8_2)
          || (ui_8 < ui_8_2 && i_8 >= i_8_2)
        ){
          printf("%u has been converted to %d\n.", ui_8, i_8);
          printf("%u has been converted to %d\n.", ui_8_2, i_8_2);
          printf("Order is not preserved.");
          i_result = -1;
          break;
        }
      }
      if(i_result != 0){
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and signed integers (8) preserves the order (macraffs).\n");

    for(i = 0; i <= UINT16_MAX; ++i){
      ui_16 = (uint16_t)i;
      i_16 = TSODLULS_get_int16_from_uint16(ui_16);
      ui_16_2 = TSODLULS_get_uint16_from_int16(i_16);
      if(ui_16 != ui_16_2){
        printf("%u has been converted to %d and back to %u\n.", ui_16, i_16, ui_16_2);
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and signed integers (16) works.\n");

    for(i = 0; i <= UINT16_MAX; ++i){
      ui_16 = (uint16_t)i;
      TSODLULS_get_int16_from_uint16__macraff(i_16, ui_16);
      TSODLULS_get_uint16_from_int16__macraff(ui_16_2, i_16);
      if(ui_16 != ui_16_2){
        printf("%u has been converted to %d and back to %u\n.", ui_16, i_16, ui_16_2);
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and signed integers (16) works (macraffs).\n");

    for(i = 0; i <= UINT16_MAX; ++i){
      ui_16 = (uint16_t)i;
      i_16 = TSODLULS_get_int16_from_uint16(ui_16);
      for(j = 0; j <= UINT16_MAX; ++j){
        ui_16_2 = (uint16_t)j;
        i_16_2 = TSODLULS_get_int16_from_uint16(ui_16_2);
        if(
             (ui_16 == ui_16_2 && i_16 != i_16_2)
          || (ui_16 > ui_16_2 && i_16 <= i_16_2)
          || (ui_16 < ui_16_2 && i_16 >= i_16_2)
        ){
          printf("%u has been converted to %d\n.", ui_16, i_16);
          printf("%u has been converted to %d\n.", ui_16_2, i_16_2);
          printf("Order is not preserved.");
          i_result = -1;
          break;
        }
      }
      if(i_result != 0){
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and signed integers (16) preserves the order.\n");

    for(i = 0; i <= UINT16_MAX; ++i){
      ui_16 = (uint16_t)i;
      TSODLULS_get_int16_from_uint16__macraff(i_16, ui_16);
      for(j = 0; j <= UINT16_MAX; ++j){
        ui_16_2 = (uint16_t)j;
        TSODLULS_get_int16_from_uint16__macraff(i_16_2, ui_16_2);
        if(
             (ui_16 == ui_16_2 && i_16 != i_16_2)
          || (ui_16 > ui_16_2 && i_16 <= i_16_2)
          || (ui_16 < ui_16_2 && i_16 >= i_16_2)
        ){
          printf("%u has been converted to %d\n.", ui_16, i_16);
          printf("%u has been converted to %d\n.", ui_16_2, i_16_2);
          printf("Order is not preserved.");
          i_result = -1;
          break;
        }
      }
      if(i_result != 0){
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and signed integers (16) preserves the order (macraffs).\n");

    for(i = 0; i <= UINT32_MAX; ++i){
      ui_32 = (uint32_t)i;
      i_32 = TSODLULS_get_int32_from_uint32(ui_32);
      ui_32_2 = TSODLULS_get_uint32_from_int32(i_32);
      if(ui_32 != ui_32_2){
        printf("%u has been converted to %d and back to %u\n.", ui_32, i_32, ui_32_2);
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and signed integers (32) works.\n");

    for(i = 0; i <= UINT32_MAX; ++i){
      ui_32 = (uint32_t)i;
      TSODLULS_get_int32_from_uint32__macraff(i_32, ui_32);
      TSODLULS_get_uint32_from_int32__macraff(ui_32_2, i_32);
      if(ui_32 != ui_32_2){
        printf("%u has been converted to %d and back to %u\n.", ui_32, i_32, ui_32_2);
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and signed integers (32) works (macraffs).\n");

    for(i = 0; i < i_max; ++i){
      ui_32 = (uint32_t)rand();
      ui_32_2 = (uint32_t)rand();
      //with glibc we're missing one bit of randomness, we do exhaustive search on it
      if((i & 1) > 0){
        ui_32 += (((uint32_t)1) << 31);
      }
      if((i & 2) > 0){
        ui_32_2 += (((uint32_t)1) << 31);
      }
      i_32 = TSODLULS_get_int32_from_uint32(ui_32);
      i_32_2 = TSODLULS_get_int32_from_uint32(ui_32_2);

      if(
           (ui_32 == ui_32_2 && i_32 != i_32_2)
        || (ui_32 > ui_32_2 && i_32 <= i_32_2)
        || (ui_32 < ui_32_2 && i_32 >= i_32_2)
      ){
        printf("%u has been converted to %d\n.", ui_32, i_32);
        printf("%u has been converted to %d\n.", ui_32_2, i_32_2);
        printf("Order is not preserved.");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and signed integers (32) preserves the order.\n");

    for(i = 0; i < i_max; ++i){
      ui_32 = (uint32_t)rand();
      ui_32_2 = (uint32_t)rand();
      //with glibc we're missing one bit of randomness, we do exhaustive search on it
      if((i & 1) > 0){
        ui_32 += (((uint32_t)1) << 31);
      }
      if((i & 2) > 0){
        ui_32_2 += (((uint32_t)1) << 31);
      }
      TSODLULS_get_int32_from_uint32__macraff(i_32, ui_32);
      TSODLULS_get_int32_from_uint32__macraff(i_32_2, ui_32_2);

      if(
           (ui_32 == ui_32_2 && i_32 != i_32_2)
        || (ui_32 > ui_32_2 && i_32 <= i_32_2)
        || (ui_32 < ui_32_2 && i_32 >= i_32_2)
      ){
        printf("%u has been converted to %d\n.", ui_32, i_32);
        printf("%u has been converted to %d\n.", ui_32_2, i_32_2);
        printf("Order is not preserved.");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and signed integers (32) preserves the order (macraffs).\n");

    for(i = 0; i < i_max; ++i){
      ui_32 = (uint32_t)rand();
      ui_32_2 = (uint32_t)rand();
      //with glibc we're missing one bit of randomness, we do exhaustive search on it
      if((i & 1) > 0){
        ui_32 += (((uint32_t)1) << 31);
      }
      if((i & 2) > 0){
        ui_32_2 += (((uint32_t)1) << 31);
      }

      ui_64 = (((uint64_t) ui_32) << 32) + ((uint64_t) ui_32_2);

      i_64 = TSODLULS_get_int64_from_uint64(ui_64);
      ui_64_2 = TSODLULS_get_uint64_from_int64(i_64);
      if(ui_64 != ui_64_2){
        printf(
            "%lu has been converted to %ld and back to %lu\n.",
            ui_64,
            i_64,
            ui_64_2
        );
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and signed integers (64) works.\n");

    for(i = 0; i < i_max; ++i){
      ui_32 = (uint32_t)rand();
      ui_32_2 = (uint32_t)rand();
      //with glibc we're missing one bit of randomness, we do exhaustive search on it
      if((i & 1) > 0){
        ui_32 += (((uint32_t)1) << 31);
      }
      if((i & 2) > 0){
        ui_32_2 += (((uint32_t)1) << 31);
      }

      ui_64 = (((uint64_t) ui_32) << 32) + ((uint64_t) ui_32_2);

      TSODLULS_get_int64_from_uint64__macraff(i_64, ui_64);
      TSODLULS_get_uint64_from_int64__macraff(ui_64_2, i_64);
      if(ui_64 != ui_64_2){
        printf(
            "%lu has been converted to %ld and back to %lu\n.",
            ui_64,
            i_64,
            ui_64_2
        );
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and signed integers (64) works (macraffs).\n");

    for(i = 0; i < i_max; ++i){
      ui_32 = (uint32_t)rand();
      ui_32_2 = (uint32_t)rand();
      //with glibc we're missing one bit of randomness, we do exhaustive search on it
      if((i & 1) > 0){
        ui_32 += (((uint32_t)1) << 31);
      }
      if((i & 2) > 0){
        ui_32_2 += (((uint32_t)1) << 31);
      }
      ui_64 = (((uint64_t) ui_32) << 32) + ((uint64_t) ui_32_2);
      i_64 = TSODLULS_get_int64_from_uint64(ui_64);

      ui_32 = (uint32_t)rand();
      ui_32_2 = (uint32_t)rand();
      //with glibc we're missing one bit of randomness, we do exhaustive search on it
      if((i & 4) > 0){
        ui_32 += (((uint32_t)1) << 31);
      }
      if((i & 8) > 0){
        ui_32_2 += (((uint32_t)1) << 31);
      }
      ui_64_2 = (((uint64_t) ui_32) << 32) + ((uint64_t) ui_32_2);
      i_64_2 = TSODLULS_get_int64_from_uint64(ui_64_2);

      if(
           (ui_64 == ui_64_2 && i_64 != i_64_2)
        || (ui_64 > ui_64_2 && i_64 <= i_64_2)
        || (ui_64 < ui_64_2 && i_64 >= i_64_2)
      ){
        printf("%lu has been converted to %ld\n.", ui_64, i_64);
        printf("%lu has been converted to %ld\n.", ui_64_2, i_64_2);
        printf("Order is not preserved.");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and signed integers (64) preserves the order.\n");

    for(i = 0; i < i_max; ++i){
      ui_32 = (uint32_t)rand();
      ui_32_2 = (uint32_t)rand();
      //with glibc we're missing one bit of randomness, we do exhaustive search on it
      if((i & 1) > 0){
        ui_32 += (((uint32_t)1) << 31);
      }
      if((i & 2) > 0){
        ui_32_2 += (((uint32_t)1) << 31);
      }
      ui_64 = (((uint64_t) ui_32) << 32) + ((uint64_t) ui_32_2);
      TSODLULS_get_int64_from_uint64__macraff(i_64, ui_64);

      ui_32 = (uint32_t)rand();
      ui_32_2 = (uint32_t)rand();
      //with glibc we're missing one bit of randomness, we do exhaustive search on it
      if((i & 4) > 0){
        ui_32 += (((uint32_t)1) << 31);
      }
      if((i & 8) > 0){
        ui_32_2 += (((uint32_t)1) << 31);
      }
      ui_64_2 = (((uint64_t) ui_32) << 32) + ((uint64_t) ui_32_2);
      TSODLULS_get_int64_from_uint64__macraff(i_64_2, ui_64_2);

      if(
           (ui_64 == ui_64_2 && i_64 != i_64_2)
        || (ui_64 > ui_64_2 && i_64 <= i_64_2)
        || (ui_64 < ui_64_2 && i_64 >= i_64_2)
      ){
        printf("%lu has been converted to %ld\n.", ui_64, i_64);
        printf("%lu has been converted to %ld\n.", ui_64_2, i_64_2);
        printf("Order is not preserved.");
        i_result = -1;
        break;
      }
    }
    if(i_result != 0){
      break;
    }
    printf("The one to one mapping between integers and signed integers (64) preserves the order (macraffs).\n");

  }
  while(0);

  return i_result;
}//end function main()



