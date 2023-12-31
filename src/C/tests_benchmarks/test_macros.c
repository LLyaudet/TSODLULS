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

©Copyright 2018-2023 Laurent Lyaudet
*/

//------------------------------------------------------------------------------
//uint8
//------------------------------------------------------------------------------

#define TSODLULS_code_fragment_init_long_cells_for_uint8() \
  i_result = TSODLULS_init_array_of_elements(&arr_cells, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    i_result = TSODLULS_add_bytes_to_key_from_uint8(\
        &(arr_cells[i]),\
        arr_ui_8_seed[i],\
        0,\
        0,\
        0,\
        0,\
        1,\
        0\
    );\
    if(i_result != 0){\
      break;\
    }\
    arr_cells[i].p_object = &(arr_ui_8_seed[i]);\
  }\
  if(i_result != 0){\
    break;\
  }



#define TSODLULS_code_fragment_init_long_cells_for_uint8_with_macraffs() \
  TSODLULS_init_array_of_elements__macraff(i_result, &arr_cells, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    TSODLULS_add_bytes_to_key_from_uint8__macraff(\
        i_result,\
        &(arr_cells[i]),\
        arr_ui_8_seed[i],\
        0,\
        0,\
        0,\
        0,\
        1,\
        0\
    );\
    if(i_result != 0){\
      break;\
    }\
    arr_cells[i].p_object = &(arr_ui_8_seed[i]);\
  }\
  if(i_result != 0){\
    break;\
  }



#define TSODLULS_code_fragment_init_short_cells_for_uint8() \
  i_result = TSODLULS_init_array_of_elements__short(&arr_cells__short, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_cells__short[i].i_key = (uint64_t)arr_ui_8_seed[i];\
    arr_cells__short[i].i_key = arr_cells__short[i].i_key << 56;/*putting info on most significant bits*/\
    arr_cells__short[i].p_object = &(arr_ui_8_seed[i]);\
  }



#define TSODLULS_code_fragment_init_short_cells_for_uint8_with_macraffs() \
  TSODLULS_init_array_of_elements__short__macraff(i_result, &arr_cells__short, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_cells__short[i].i_key = (uint64_t)arr_ui_8_seed[i];\
    arr_cells__short[i].i_key = arr_cells__short[i].i_key << 56;/*putting info on most significant bits*/\
    arr_cells__short[i].p_object = &(arr_ui_8_seed[i]);\
  }



#define TSODLULS_code_fragment_fill_result2_with_long_cells_for_uint8() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_8_result2[i] = *((uint8_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result2_with_long_cells_for_uint8_with_macraffs() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_8_result2[i] = *((uint8_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements__macraff(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result2_with_short_cells_for_uint8_no_macraff_needed() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_8_result2[i] = *((uint8_t*)(arr_cells__short[i].p_object));\
  }\
  TSODLULS_free(arr_cells__short);



#define TSODLULS_code_fragment_fill_result1_with_long_cells_for_uint8() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_8_result1[i] = *((uint8_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result1_with_long_cells_for_uint8_with_macraffs() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_8_result1[i] = *((uint8_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements__macraff(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result1_with_short_cells_for_uint8_no_macraff_needed() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_8_result1[i] = *((uint8_t*)(arr_cells__short[i].p_object));\
  }\
  TSODLULS_free(arr_cells__short);



#define TSODLULS_code_fragment_compare_results_for_uint8(message) \
  for(i = 0; i < i_number_of_elements; ++i){\
    if(arr_ui_8_result2[i] != arr_ui_8_result1[i]){\
      printf(message);\
      i_result = -1;\
      break;\
    }\
  }\
  if(i_result != 0){\
    break;\
  }




//------------------------------------------------------------------------------
//uint16
//------------------------------------------------------------------------------

#define TSODLULS_code_fragment_init_long_cells_for_uint16() \
  i_result = TSODLULS_init_array_of_elements(&arr_cells, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    i_result = TSODLULS_add_bytes_to_key_from_uint16(\
        &(arr_cells[i]),\
        arr_ui_16_seed[i],\
        0,\
        0,\
        0,\
        0,\
        2,\
        0\
    );\
    if(i_result != 0){\
      break;\
    }\
    arr_cells[i].p_object = &(arr_ui_16_seed[i]);\
  }\
  if(i_result != 0){\
    break;\
  }



#define TSODLULS_code_fragment_init_long_cells_for_uint16_with_macraffs() \
  TSODLULS_init_array_of_elements__macraff(i_result, &arr_cells, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    TSODLULS_add_bytes_to_key_from_uint16__macraff(\
        i_result,\
        &(arr_cells[i]),\
        arr_ui_16_seed[i],\
        0,\
        0,\
        0,\
        0,\
        2,\
        0\
    );\
    if(i_result != 0){\
      break;\
    }\
    arr_cells[i].p_object = &(arr_ui_16_seed[i]);\
  }\
  if(i_result != 0){\
    break;\
  }



#define TSODLULS_code_fragment_init_short_cells_for_uint16() \
  i_result = TSODLULS_init_array_of_elements__short(&arr_cells__short, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_cells__short[i].i_key = (uint64_t)arr_ui_16_seed[i];\
    arr_cells__short[i].i_key = arr_cells__short[i].i_key << 48;/*putting info on most significant bits*/\
    arr_cells__short[i].p_object = &(arr_ui_16_seed[i]);\
  }



#define TSODLULS_code_fragment_init_short_cells_for_uint16_with_macraffs() \
  TSODLULS_init_array_of_elements__short__macraff(i_result, &arr_cells__short, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_cells__short[i].i_key = (uint64_t)arr_ui_16_seed[i];\
    arr_cells__short[i].i_key = arr_cells__short[i].i_key << 48;/*putting info on most significant bits*/\
    arr_cells__short[i].p_object = &(arr_ui_16_seed[i]);\
  }



#define TSODLULS_code_fragment_fill_result2_with_long_cells_for_uint16() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_16_result2[i] = *((uint16_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result2_with_long_cells_for_uint16_with_macraffs() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_16_result2[i] = *((uint16_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements__macraff(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result2_with_short_cells_for_uint16_no_macraff_needed() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_16_result2[i] = *((uint16_t*)(arr_cells__short[i].p_object));\
  }\
  TSODLULS_free(arr_cells__short);



#define TSODLULS_code_fragment_fill_result1_with_long_cells_for_uint16() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_16_result1[i] = *((uint16_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result1_with_long_cells_for_uint16_with_macraffs() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_16_result1[i] = *((uint16_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements__macraff(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result1_with_short_cells_for_uint16_no_macraff_needed() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_16_result1[i] = *((uint16_t*)(arr_cells__short[i].p_object));\
  }\
  TSODLULS_free(arr_cells__short);



#define TSODLULS_code_fragment_compare_results_for_uint16(message) \
  for(i = 0; i < i_number_of_elements; ++i){\
    if(arr_ui_16_result2[i] != arr_ui_16_result1[i]){\
      printf(message);\
      i_result = -1;\
      break;\
    }\
  }\
  if(i_result != 0){\
    break;\
  }




//------------------------------------------------------------------------------
//uint32
//------------------------------------------------------------------------------

#define TSODLULS_code_fragment_init_long_cells_for_uint32() \
  i_result = TSODLULS_init_array_of_elements(&arr_cells, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    i_result = TSODLULS_add_bytes_to_key_from_uint32(\
        &(arr_cells[i]),\
        arr_ui_32_seed[i],\
        0,\
        0,\
        0,\
        0,\
        4,\
        0\
    );\
    if(i_result != 0){\
      break;\
    }\
    arr_cells[i].p_object = &(arr_ui_32_seed[i]);\
  }\
  if(i_result != 0){\
    break;\
  }



#define TSODLULS_code_fragment_init_long_cells_for_uint32_with_macraffs() \
  TSODLULS_init_array_of_elements__macraff(i_result, &arr_cells, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    TSODLULS_add_bytes_to_key_from_uint32__macraff(\
        i_result,\
        &(arr_cells[i]),\
        arr_ui_32_seed[i],\
        0,\
        0,\
        0,\
        0,\
        4,\
        0\
    );\
    if(i_result != 0){\
      break;\
    }\
    arr_cells[i].p_object = &(arr_ui_32_seed[i]);\
  }\
  if(i_result != 0){\
    break;\
  }



#define TSODLULS_code_fragment_init_short_cells_for_uint32() \
  i_result = TSODLULS_init_array_of_elements__short(&arr_cells__short, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_cells__short[i].i_key = (uint64_t)arr_ui_32_seed[i];\
    arr_cells__short[i].i_key = arr_cells__short[i].i_key << 32;/*putting info on most significant bits*/\
    arr_cells__short[i].p_object = &(arr_ui_32_seed[i]);\
  }



#define TSODLULS_code_fragment_init_short_cells_for_uint32_with_macraffs() \
  TSODLULS_init_array_of_elements__short__macraff(i_result, &arr_cells__short, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_cells__short[i].i_key = (uint64_t)arr_ui_32_seed[i];\
    arr_cells__short[i].i_key = arr_cells__short[i].i_key << 32;/*putting info on most significant bits*/\
    arr_cells__short[i].p_object = &(arr_ui_32_seed[i]);\
  }



#define TSODLULS_code_fragment_fill_result2_with_long_cells_for_uint32() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_32_result2[i] = *((uint32_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result2_with_long_cells_for_uint32_with_macraffs() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_32_result2[i] = *((uint32_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements__macraff(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result2_with_short_cells_for_uint32_no_macraff_needed() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_32_result2[i] = *((uint32_t*)(arr_cells__short[i].p_object));\
  }\
  TSODLULS_free(arr_cells__short);



#define TSODLULS_code_fragment_fill_result1_with_long_cells_for_uint32() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_32_result1[i] = *((uint32_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result1_with_long_cells_for_uint32_with_macraffs() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_32_result1[i] = *((uint32_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements__macraff(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result1_with_short_cells_for_uint32_no_macraff_needed() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_32_result1[i] = *((uint32_t*)(arr_cells__short[i].p_object));\
  }\
  TSODLULS_free(arr_cells__short);



#define TSODLULS_code_fragment_compare_results_for_uint32(message) \
  for(i = 0; i < i_number_of_elements; ++i){\
    if(arr_ui_32_result2[i] != arr_ui_32_result1[i]){\
      printf(message);\
      i_result = -1;\
      break;\
    }\
  }\
  if(i_result != 0){\
    break;\
  }




//------------------------------------------------------------------------------
//uint64
//------------------------------------------------------------------------------

#define TSODLULS_code_fragment_init_long_cells_for_uint64() \
  i_result = TSODLULS_init_array_of_elements(&arr_cells, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    i_result = TSODLULS_add_bytes_to_key_from_uint64(\
        &(arr_cells[i]),\
        arr_ui_64_seed[i],\
        0,\
        0,\
        0,\
        0,\
        8,\
        0\
    );\
    if(i_result != 0){\
      break;\
    }\
    arr_cells[i].p_object = &(arr_ui_64_seed[i]);\
  }\
  if(i_result != 0){\
    break;\
  }



#define TSODLULS_code_fragment_init_long_cells_for_uint64_with_macraffs() \
  TSODLULS_init_array_of_elements__macraff(i_result, &arr_cells, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    TSODLULS_add_bytes_to_key_from_uint64__macraff(\
        i_result,\
        &(arr_cells[i]),\
        arr_ui_64_seed[i],\
        0,\
        0,\
        0,\
        0,\
        8,\
        0\
    );\
    if(i_result != 0){\
      break;\
    }\
    arr_cells[i].p_object = &(arr_ui_64_seed[i]);\
  }\
  if(i_result != 0){\
    break;\
  }



#define TSODLULS_code_fragment_init_short_cells_for_uint64() \
  i_result = TSODLULS_init_array_of_elements__short(&arr_cells__short, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_cells__short[i].i_key = arr_ui_64_seed[i];\
    arr_cells__short[i].p_object = &(arr_ui_64_seed[i]);\
  }



#define TSODLULS_code_fragment_init_short_cells_for_uint64_with_macraffs() \
  TSODLULS_init_array_of_elements__short__macraff(i_result, &arr_cells__short, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_cells__short[i].i_key = arr_ui_64_seed[i];\
    arr_cells__short[i].p_object = &(arr_ui_64_seed[i]);\
  }



#define TSODLULS_code_fragment_fill_result2_with_long_cells_for_uint64() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_64_result2[i] = *((uint64_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result2_with_long_cells_for_uint64_with_macraffs() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_64_result2[i] = *((uint64_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements__macraff(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result2_with_short_cells_for_uint64_no_macraff_needed() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_64_result2[i] = *((uint64_t*)(arr_cells__short[i].p_object));\
  }\
  TSODLULS_free(arr_cells__short);



#define TSODLULS_code_fragment_fill_result1_with_long_cells_for_uint64() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_64_result1[i] = *((uint64_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result1_with_long_cells_for_uint64_with_macraffs() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_64_result1[i] = *((uint64_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements__macraff(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result1_with_short_cells_for_uint64_no_macraff_needed() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_ui_64_result1[i] = *((uint64_t*)(arr_cells__short[i].p_object));\
  }\
  TSODLULS_free(arr_cells__short);



#define TSODLULS_code_fragment_compare_results_for_uint64(message) \
  for(i = 0; i < i_number_of_elements; ++i){\
    if(arr_ui_64_result2[i] != arr_ui_64_result1[i]){\
      printf(message);\
      i_result = -1;\
      break;\
    }\
  }\
  if(i_result != 0){\
    break;\
  }




//------------------------------------------------------------------------------
//int8
//------------------------------------------------------------------------------

#define TSODLULS_code_fragment_init_long_cells_for_int8() \
  i_result = TSODLULS_init_array_of_elements(&arr_cells, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    i_result = TSODLULS_add_bytes_to_key_from_uint8(\
        &(arr_cells[i]),\
        TSODLULS_get_uint8_from_int8(arr_i_8_seed[i]),\
        0,\
        0,\
        0,\
        0,\
        1,\
        0\
    );\
    if(i_result != 0){\
      break;\
    }\
    arr_cells[i].p_object = &(arr_i_8_seed[i]);\
  }\
  if(i_result != 0){\
    break;\
  }



#define TSODLULS_code_fragment_init_long_cells_for_int8_with_macraffs() \
  TSODLULS_init_array_of_elements__macraff(i_result, &arr_cells, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    TSODLULS_get_uint8_from_int8__macraff(ui8, arr_i_8_seed[i]);\
    TSODLULS_add_bytes_to_key_from_uint8__macraff(\
        i_result,\
        &(arr_cells[i]),\
        ui8,\
        0,\
        0,\
        0,\
        0,\
        1,\
        0\
    );\
    if(i_result != 0){\
      break;\
    }\
    arr_cells[i].p_object = &(arr_i_8_seed[i]);\
  }\
  if(i_result != 0){\
    break;\
  }



#define TSODLULS_code_fragment_init_short_cells_for_int8() \
  i_result = TSODLULS_init_array_of_elements__short(&arr_cells__short, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    ui8 = TSODLULS_get_uint8_from_int8(arr_i_8_seed[i]);\
    arr_cells__short[i].i_key = (uint64_t)ui8;\
    arr_cells__short[i].i_key = arr_cells__short[i].i_key << 56;/*putting info on most significant bits*/\
    arr_cells__short[i].p_object = &(arr_i_8_seed[i]);\
  }



#define TSODLULS_code_fragment_init_short_cells_for_int8_with_macraffs() \
  TSODLULS_init_array_of_elements__short__macraff(i_result, &arr_cells__short, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    TSODLULS_get_uint8_from_int8__macraff(ui8, arr_i_8_seed[i]);\
    arr_cells__short[i].i_key = (uint64_t)ui8;\
    arr_cells__short[i].i_key = arr_cells__short[i].i_key << 56;/*putting info on most significant bits*/\
    arr_cells__short[i].p_object = &(arr_i_8_seed[i]);\
  }



#define TSODLULS_code_fragment_fill_result2_with_long_cells_for_int8() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_8_result2[i] = *((int8_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result2_with_long_cells_for_int8_with_macraffs() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_8_result2[i] = *((int8_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements__macraff(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result2_with_short_cells_for_int8_no_macraff_needed() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_8_result2[i] = *((int8_t*)(arr_cells__short[i].p_object));\
  }\
  TSODLULS_free(arr_cells__short);



#define TSODLULS_code_fragment_fill_result1_with_long_cells_for_int8() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_8_result1[i] = *((int8_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result1_with_long_cells_for_int8_with_macraffs() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_8_result1[i] = *((int8_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements__macraff(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result1_with_short_cells_for_int8_no_macraff_needed() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_8_result1[i] = *((int8_t*)(arr_cells__short[i].p_object));\
  }\
  TSODLULS_free(arr_cells__short);



#define TSODLULS_code_fragment_compare_results_for_int8(message) \
  for(i = 0; i < i_number_of_elements; ++i){\
    if(arr_i_8_result2[i] != arr_i_8_result1[i]){\
      printf(message);\
      i_result = -1;\
      break;\
    }\
  }\
  if(i_result != 0){\
    break;\
  }




//------------------------------------------------------------------------------
//int16
//------------------------------------------------------------------------------

#define TSODLULS_code_fragment_init_long_cells_for_int16() \
  i_result = TSODLULS_init_array_of_elements(&arr_cells, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    i_result = TSODLULS_add_bytes_to_key_from_uint16(\
        &(arr_cells[i]),\
        TSODLULS_get_uint16_from_int16(arr_i_16_seed[i]),\
        0,\
        0,\
        0,\
        0,\
        2,\
        0\
    );\
    if(i_result != 0){\
      break;\
    }\
    arr_cells[i].p_object = &(arr_i_16_seed[i]);\
  }\
  if(i_result != 0){\
    break;\
  }



#define TSODLULS_code_fragment_init_long_cells_for_int16_with_macraffs() \
  TSODLULS_init_array_of_elements__macraff(i_result, &arr_cells, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    TSODLULS_get_uint16_from_int16__macraff(ui16, arr_i_16_seed[i]);\
    TSODLULS_add_bytes_to_key_from_uint16__macraff(\
        i_result,\
        &(arr_cells[i]),\
        ui16,\
        0,\
        0,\
        0,\
        0,\
        2,\
        0\
    );\
    if(i_result != 0){\
      break;\
    }\
    arr_cells[i].p_object = &(arr_i_16_seed[i]);\
  }\
  if(i_result != 0){\
    break;\
  }



#define TSODLULS_code_fragment_init_short_cells_for_int16() \
  i_result = TSODLULS_init_array_of_elements__short(&arr_cells__short, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    ui16 = TSODLULS_get_uint16_from_int16(arr_i_16_seed[i]);\
    arr_cells__short[i].i_key = (uint64_t)ui16;\
    arr_cells__short[i].i_key = arr_cells__short[i].i_key << 48;/*putting info on most significant bits*/\
    arr_cells__short[i].p_object = &(arr_i_16_seed[i]);\
  }



#define TSODLULS_code_fragment_init_short_cells_for_int16_with_macraffs() \
  TSODLULS_init_array_of_elements__short__macraff(i_result, &arr_cells__short, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    TSODLULS_get_uint16_from_int16__macraff(ui16, arr_i_16_seed[i]);\
    arr_cells__short[i].i_key = (uint64_t)ui16;\
    arr_cells__short[i].i_key = arr_cells__short[i].i_key << 48;/*putting info on most significant bits*/\
    arr_cells__short[i].p_object = &(arr_i_16_seed[i]);\
  }



#define TSODLULS_code_fragment_fill_result2_with_long_cells_for_int16() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_16_result2[i] = *((int16_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result2_with_long_cells_for_int16_with_macraffs() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_16_result2[i] = *((int16_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements__macraff(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result2_with_short_cells_for_int16_no_macraff_needed() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_16_result2[i] = *((int16_t*)(arr_cells__short[i].p_object));\
  }\
  TSODLULS_free(arr_cells__short);



#define TSODLULS_code_fragment_fill_result1_with_long_cells_for_int16() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_16_result1[i] = *((int16_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result1_with_long_cells_for_int16_with_macraffs() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_16_result1[i] = *((int16_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements__macraff(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result1_with_short_cells_for_int16_no_macraff_needed() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_16_result1[i] = *((int16_t*)(arr_cells__short[i].p_object));\
  }\
  TSODLULS_free(arr_cells__short);



#define TSODLULS_code_fragment_compare_results_for_int16(message) \
  for(i = 0; i < i_number_of_elements; ++i){\
    if(arr_i_16_result2[i] != arr_i_16_result1[i]){\
      printf(message);\
      i_result = -1;\
      break;\
    }\
  }\
  if(i_result != 0){\
    break;\
  }




//------------------------------------------------------------------------------
//int32
//------------------------------------------------------------------------------

#define TSODLULS_code_fragment_init_long_cells_for_int32() \
  i_result = TSODLULS_init_array_of_elements(&arr_cells, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    i_result = TSODLULS_add_bytes_to_key_from_uint32(\
        &(arr_cells[i]),\
        TSODLULS_get_uint32_from_int32(arr_i_32_seed[i]),\
        0,\
        0,\
        0,\
        0,\
        4,\
        0\
    );\
    if(i_result != 0){\
      break;\
    }\
    arr_cells[i].p_object = &(arr_i_32_seed[i]);\
  }\
  if(i_result != 0){\
    break;\
  }



#define TSODLULS_code_fragment_init_long_cells_for_int32_with_macraffs() \
  TSODLULS_init_array_of_elements__macraff(i_result, &arr_cells, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    TSODLULS_get_uint32_from_int32__macraff(ui32, arr_i_32_seed[i]);\
    TSODLULS_add_bytes_to_key_from_uint32__macraff(\
        i_result,\
        &(arr_cells[i]),\
        ui32,\
        0,\
        0,\
        0,\
        0,\
        4,\
        0\
    );\
    if(i_result != 0){\
      break;\
    }\
    arr_cells[i].p_object = &(arr_i_32_seed[i]);\
  }\
  if(i_result != 0){\
    break;\
  }



#define TSODLULS_code_fragment_init_short_cells_for_int32() \
  i_result = TSODLULS_init_array_of_elements__short(&arr_cells__short, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    ui32 = TSODLULS_get_uint32_from_int32(arr_i_32_seed[i]);\
    arr_cells__short[i].i_key = (uint64_t)ui32;\
    arr_cells__short[i].i_key = arr_cells__short[i].i_key << 32;/*putting info on most significant bits*/\
    arr_cells__short[i].p_object = &(arr_i_32_seed[i]);\
  }



#define TSODLULS_code_fragment_init_short_cells_for_int32_with_macraffs() \
  TSODLULS_init_array_of_elements__short__macraff(i_result, &arr_cells__short, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    TSODLULS_get_uint32_from_int32__macraff(ui32, arr_i_32_seed[i]);\
    arr_cells__short[i].i_key = (uint64_t)ui32;\
    arr_cells__short[i].i_key = arr_cells__short[i].i_key << 32;/*putting info on most significant bits*/\
    arr_cells__short[i].p_object = &(arr_i_32_seed[i]);\
  }



#define TSODLULS_code_fragment_fill_result2_with_long_cells_for_int32() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_32_result2[i] = *((int32_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result2_with_long_cells_for_int32_with_macraffs() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_32_result2[i] = *((int32_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements__macraff(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result2_with_short_cells_for_int32_no_macraff_needed() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_32_result2[i] = *((int32_t*)(arr_cells__short[i].p_object));\
  }\
  TSODLULS_free(arr_cells__short);



#define TSODLULS_code_fragment_fill_result1_with_long_cells_for_int32() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_32_result1[i] = *((int32_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result1_with_long_cells_for_int32_with_macraffs() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_32_result1[i] = *((int32_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements__macraff(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result1_with_short_cells_for_int32_no_macraff_needed() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_32_result1[i] = *((int32_t*)(arr_cells__short[i].p_object));\
  }\
  TSODLULS_free(arr_cells__short);



#define TSODLULS_code_fragment_compare_results_for_int32(message) \
  for(i = 0; i < i_number_of_elements; ++i){\
    if(arr_i_32_result2[i] != arr_i_32_result1[i]){\
      printf(message);\
      i_result = -1;\
      break;\
    }\
  }\
  if(i_result != 0){\
    break;\
  }




//------------------------------------------------------------------------------
//int64
//------------------------------------------------------------------------------

#define TSODLULS_code_fragment_init_long_cells_for_int64() \
  i_result = TSODLULS_init_array_of_elements(&arr_cells, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    i_result = TSODLULS_add_bytes_to_key_from_uint64(\
        &(arr_cells[i]),\
        TSODLULS_get_uint64_from_int64(arr_i_64_seed[i]),\
        0,\
        0,\
        0,\
        0,\
        8,\
        0\
    );\
    if(i_result != 0){\
      break;\
    }\
    arr_cells[i].p_object = &(arr_i_64_seed[i]);\
  }\
  if(i_result != 0){\
    break;\
  }



#define TSODLULS_code_fragment_init_long_cells_for_int64_with_macraffs() \
  TSODLULS_init_array_of_elements__macraff(i_result, &arr_cells, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    TSODLULS_get_uint64_from_int64__macraff(ui64, arr_i_64_seed[i]);\
    TSODLULS_add_bytes_to_key_from_uint64__macraff(\
        i_result,\
        &(arr_cells[i]),\
        ui64,\
        0,\
        0,\
        0,\
        0,\
        8,\
        0\
    );\
    if(i_result != 0){\
      break;\
    }\
    arr_cells[i].p_object = &(arr_i_64_seed[i]);\
  }\
  if(i_result != 0){\
    break;\
  }



#define TSODLULS_code_fragment_init_short_cells_for_int64() \
  i_result = TSODLULS_init_array_of_elements__short(&arr_cells__short, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    ui64 = TSODLULS_get_uint64_from_int64(arr_i_64_seed[i]);\
    arr_cells__short[i].i_key = ui64;\
    arr_cells__short[i].p_object = &(arr_i_64_seed[i]);\
  }



#define TSODLULS_code_fragment_init_short_cells_for_int64_with_macraffs() \
  TSODLULS_init_array_of_elements__short__macraff(i_result, &arr_cells__short, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    TSODLULS_get_uint64_from_int64__macraff(ui64, arr_i_64_seed[i]);\
    arr_cells__short[i].i_key = ui64;\
    arr_cells__short[i].p_object = &(arr_i_64_seed[i]);\
  }



#define TSODLULS_code_fragment_fill_result2_with_long_cells_for_int64() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_64_result2[i] = *((int64_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result2_with_long_cells_for_int64_with_macraffs() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_64_result2[i] = *((int64_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements__macraff(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result2_with_short_cells_for_int64_no_macraff_needed() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_64_result2[i] = *((int64_t*)(arr_cells__short[i].p_object));\
  }\
  TSODLULS_free(arr_cells__short);



#define TSODLULS_code_fragment_fill_result1_with_long_cells_for_int64() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_64_result1[i] = *((int64_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result1_with_long_cells_for_int64_with_macraffs() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_64_result1[i] = *((int64_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements__macraff(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result1_with_short_cells_for_int64_no_macraff_needed() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_i_64_result1[i] = *((int64_t*)(arr_cells__short[i].p_object));\
  }\
  TSODLULS_free(arr_cells__short);



#define TSODLULS_code_fragment_compare_results_for_int64(message) \
  for(i = 0; i < i_number_of_elements; ++i){\
    if(arr_i_64_result2[i] != arr_i_64_result1[i]){\
      printf(message);\
      i_result = -1;\
      break;\
    }\
  }\
  if(i_result != 0){\
    break;\
  }




//------------------------------------------------------------------------------
//float
//------------------------------------------------------------------------------

#define TSODLULS_code_fragment_init_long_cells_for_float() \
  i_result = TSODLULS_init_array_of_elements(&arr_cells, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    i_result = TSODLULS_add_bytes_to_key_from_uint32(\
        &(arr_cells[i]),\
        TSODLULS_get_uint_from_float(arr_f_float_seed[i]),\
        0,\
        0,\
        0,\
        0,\
        4,\
        0\
    );\
    if(i_result != 0){\
      break;\
    }\
    arr_cells[i].p_object = &(arr_f_float_seed[i]);\
  }\
  if(i_result != 0){\
    break;\
  }



#define TSODLULS_code_fragment_init_long_cells_for_float_with_macraffs() \
  TSODLULS_init_array_of_elements__macraff(i_result, &arr_cells, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    TSODLULS_get_uint_from_float__macraff(ui32, arr_f_float_seed[i]);\
    TSODLULS_add_bytes_to_key_from_uint32__macraff(\
        i_result,\
        &(arr_cells[i]),\
        ui32,\
        0,\
        0,\
        0,\
        0,\
        4,\
        0\
    );\
    if(i_result != 0){\
      break;\
    }\
    arr_cells[i].p_object = &(arr_f_float_seed[i]);\
  }\
  if(i_result != 0){\
    break;\
  }



#define TSODLULS_code_fragment_init_short_cells_for_float() \
  i_result = TSODLULS_init_array_of_elements__short(&arr_cells__short, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    ui32 = TSODLULS_get_uint_from_float(arr_f_float_seed[i]);\
    arr_cells__short[i].i_key = (uint64_t)ui32;\
    arr_cells__short[i].i_key = arr_cells__short[i].i_key << 32;/*putting info on most significant bits*/\
    arr_cells__short[i].p_object = &(arr_f_float_seed[i]);\
  }



#define TSODLULS_code_fragment_init_short_cells_for_float_with_macraffs() \
  TSODLULS_init_array_of_elements__short__macraff(i_result, &arr_cells__short, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    TSODLULS_get_uint_from_float__macraff(ui32, arr_f_float_seed[i]);\
    arr_cells__short[i].i_key = (uint64_t)ui32;\
    arr_cells__short[i].i_key = arr_cells__short[i].i_key << 32;/*putting info on most significant bits*/\
    arr_cells__short[i].p_object = &(arr_f_float_seed[i]);\
  }



#define TSODLULS_code_fragment_fill_result2_with_long_cells_for_float() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_f_float_result2[i] = *((float*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result2_with_long_cells_for_float_with_macraffs() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_f_float_result2[i] = *((float*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements__macraff(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result2_with_short_cells_for_float_no_macraff_needed() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_f_float_result2[i] = *((float*)(arr_cells__short[i].p_object));\
  }\
  TSODLULS_free(arr_cells__short);



#define TSODLULS_code_fragment_fill_result1_with_long_cells_for_float() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_f_float_result1[i] = *((float_t*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result1_with_long_cells_for_float_with_macraffs() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_f_float_result1[i] = *((float*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements__macraff(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result1_with_short_cells_for_float_no_macraff_needed() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_f_float_result1[i] = *((float*)(arr_cells__short[i].p_object));\
  }\
  TSODLULS_free(arr_cells__short);



#define TSODLULS_code_fragment_compare_results_for_float(message) \
  for(i = 0; i < i_number_of_elements; ++i){\
    /*if(arr_f_float_result2[i] != arr_f_float_result1[i]){
    any comparison with nan or -nan float numbers will say that they are different
    You have to compare using the bijection with uint32*/\
    TSODLULS_get_uint_from_float__macraff(ui32, arr_f_float_result1[i]);\
    TSODLULS_get_uint_from_float__macraff(ui32_2, arr_f_float_result2[i]);\
    if(ui32_2 != ui32){\
      printf(message);\
      i_result = -1;\
      break;\
    }\
  }\
  if(i_result != 0){\
    break;\
  }




//------------------------------------------------------------------------------
//double
//------------------------------------------------------------------------------

#define TSODLULS_code_fragment_init_long_cells_for_double() \
  i_result = TSODLULS_init_array_of_elements(&arr_cells, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    i_result = TSODLULS_add_bytes_to_key_from_uint64(\
        &(arr_cells[i]),\
        TSODLULS_get_uint_from_double(arr_f_double_seed[i]),\
        0,\
        0,\
        0,\
        0,\
        8,\
        0\
    );\
    if(i_result != 0){\
      break;\
    }\
    arr_cells[i].p_object = &(arr_f_double_seed[i]);\
  }\
  if(i_result != 0){\
    break;\
  }



#define TSODLULS_code_fragment_init_long_cells_for_double_with_macraffs() \
  TSODLULS_init_array_of_elements__macraff(i_result, &arr_cells, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    TSODLULS_get_uint_from_double__macraff(ui64, arr_f_double_seed[i]);\
    TSODLULS_add_bytes_to_key_from_uint64__macraff(\
        i_result,\
        &(arr_cells[i]),\
        ui64,\
        0,\
        0,\
        0,\
        0,\
        8,\
        0\
    );\
    if(i_result != 0){\
      break;\
    }\
    arr_cells[i].p_object = &(arr_f_double_seed[i]);\
  }\
  if(i_result != 0){\
    break;\
  }



#define TSODLULS_code_fragment_init_short_cells_for_double() \
  i_result = TSODLULS_init_array_of_elements__short(&arr_cells__short, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    ui64 = TSODLULS_get_uint_from_double(arr_f_double_seed[i]);\
    arr_cells__short[i].i_key = ui64;\
    arr_cells__short[i].p_object = &(arr_f_double_seed[i]);\
  }



#define TSODLULS_code_fragment_init_short_cells_for_double_with_macraffs() \
  TSODLULS_init_array_of_elements__short__macraff(i_result, &arr_cells__short, i_number_of_elements);\
  if(i_result != 0){\
    break;\
  }\
  for(i = 0; i < i_number_of_elements; ++i){\
    TSODLULS_get_uint_from_double__macraff(ui64, arr_f_double_seed[i]);\
    arr_cells__short[i].i_key = ui64;\
    arr_cells__short[i].p_object = &(arr_f_double_seed[i]);\
  }



#define TSODLULS_code_fragment_fill_result2_with_long_cells_for_double() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_f_double_result2[i] = *((double*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result2_with_long_cells_for_double_with_macraffs() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_f_double_result2[i] = *((double*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements__macraff(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result2_with_short_cells_for_double_no_macraff_needed() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_f_double_result2[i] = *((double*)(arr_cells__short[i].p_object));\
  }\
  TSODLULS_free(arr_cells__short);



#define TSODLULS_code_fragment_fill_result1_with_long_cells_for_double() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_f_double_result1[i] = *((double*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result1_with_long_cells_for_double_with_macraffs() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_f_double_result1[i] = *((double*)(arr_cells[i].p_object));\
  }\
  TSODLULS_free_keys_in_array_of_elements__macraff(arr_cells, i_number_of_elements);\
  TSODLULS_free(arr_cells);



#define TSODLULS_code_fragment_fill_result1_with_short_cells_for_double_no_macraff_needed() \
  for(i = 0; i < i_number_of_elements; ++i){\
    arr_f_double_result1[i] = *((double*)(arr_cells__short[i].p_object));\
  }\
  TSODLULS_free(arr_cells__short);



#define TSODLULS_code_fragment_compare_results_for_double(message) \
  for(i = 0; i < i_number_of_elements; ++i){\
    /*if(arr_f_double_result2[i] != arr_f_double_result1[i]){
    any comparison with nan or -nan double numbers will say that they are different
    You have to compare using the bijection with uint64*/\
    TSODLULS_get_uint_from_double__macraff(ui64, arr_f_double_result1[i]);\
    TSODLULS_get_uint_from_double__macraff(ui64_2, arr_f_double_result2[i]);\
    if(ui64_2 != ui64){\
      printf(message);\
      i_result = -1;\
      break;\
    }\
  }\
  if(i_result != 0){\
    break;\
  }




//------------------------------------------------------------------------------
//common
//------------------------------------------------------------------------------

#define TSODLULS_code_fragment_print_time() \
  clock_gettime(CLOCK_MONOTONIC, &finish);\
  f_elapsed_time = finish.tv_sec - start.tv_sec;\
  f_elapsed_time += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;\
  printf("|%016f", f_elapsed_time);


