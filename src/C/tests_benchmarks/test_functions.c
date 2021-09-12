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

#include <unistd.h>
#include <time.h>
#include "../TSODLULS.h"
#include "test_macros.c"


#define close_file(file) {\
  another_return = fclose(file);\
  if(another_return != 0){\
    printf("Couldn't close file.\n");\
  }\
}


int mydiff(char* s_filename1, char* s_filename2){
  FILE* file1 = NULL;
  FILE* file2 = NULL;
  int i_result = 0;//no difference
  int c1;//that's a char but getc returns an int
  int c2;//that's a char but getc returns an int
  int another_return;

  file1 = fopen(s_filename1, "r");
  if(file1 == NULL){
    return I_ERROR__COULD_NOT_OPEN_FILE;
  }

  file2 = fopen(s_filename2, "r");
  if(file2 == NULL){
    close_file(file1);
    return I_ERROR__COULD_NOT_OPEN_FILE;
  }

  do{
    c1 = getc(file1);
    c2 = getc(file2);
    if(c1 != c2){
      i_result = 1;
      break;
    }
  }
  while(c1 != EOF && c2 != EOF);

  close_file(file1);
  close_file(file2);
  return i_result;
}



int from_file_to_string(
  char* s_filename,
  unsigned char** p_s_string,
  size_t* p_i_string_length
){
  FILE* file;
  size_t some_return;
  int another_return;
  long int yet_another_return;

  file = fopen(s_filename, "r");
  if(file == NULL){
    printf("Couldn't open file to convert to string.\n");
    return I_ERROR__COULD_NOT_OPEN_FILE;
  }
  another_return = fseek(file, 0, SEEK_END);
  if(another_return != 0){
    printf("Couldn't seek end of file.\n");
    return I_ERROR__COULD_NOT_SEEK_FILE;
  }
  yet_another_return = ftell(file);
  if(yet_another_return < 0){
    printf("Couldn't tell file.\n");
    return I_ERROR__COULD_NOT_TELL_FILE;
  }
  *p_i_string_length = (size_t) yet_another_return;
  another_return = fseek(file, 0, SEEK_SET);
  if(another_return != 0){
    printf("Couldn't seek beginning of file.\n");
    return I_ERROR__COULD_NOT_SEEK_FILE;
  }
  *p_s_string = malloc(*p_i_string_length);
  if(*p_s_string == NULL){
    printf("Couldn't allocate string.\n");
    close_file(file);
    return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
  }
  some_return = fread(*p_s_string, 1, *p_i_string_length, file);
  if(some_return != *p_i_string_length){
    printf(
      "fread failed to read all the file: expected:%zu got:%zu.\n",
      *p_i_string_length,
      some_return
    );
    return I_ERROR__COULD_NOT_READ_FILE;
  }
  close_file(file);
  return 0;
}



int from_string_to_file(
  char* s_filename,
  unsigned char* s_string,
  size_t i_string_length
){
  FILE* file;
  int another_return;
  file = fopen(s_filename, "w");
  if(file == NULL){
    printf("Couldn't open file to dump string to.\n");
    return I_ERROR__COULD_NOT_OPEN_FILE;
  }
  for(size_t i = 0; i < i_string_length; ++i){
    if(fputc(s_string[i], file) == EOF){
      close_file(file);
      return I_ERROR__COULD_NOT_WRITE_CHARACTER;
    }
  }
  close_file(file);
  return 0;
}



void print_bits_for(void * p_data, size_t i_data_size){
  unsigned char* p_data_char = NULL;
  if(p_data == NULL){
    printf("Pointer to data is null.\n");
    return;
  }

  p_data_char = (unsigned char*) p_data;
  for(size_t i = i_data_size; i > 0; --i){//little endian
    for(int j = 7; j >= 0; --j){
      if((p_data_char[i - 1] >> j) & 1){
        printf("1");
      }
      else{
        printf("0");
      }
    }
    printf(" ");
  }

}



uint8_t get_random_uint8(){
  return (uint8_t)rand();
}



uint16_t get_random_uint16(){
  return (uint16_t)rand();
}



uint32_t get_random_uint32(){
  //we assume glibc rand with rand max on 31 bits
  return ((uint32_t)rand()) + ((((uint32_t)rand()) % 2) << 31);
}



uint64_t get_random_uint64(){
  //we assume glibc rand with rand max on 31 bits
  return ((uint64_t)rand()) + (((uint64_t)rand()) << 31) + ((((uint64_t)rand()) % 4) << 62);
}



char get_random_printable_ascii_char(){
  uint8_t i_random = get_random_uint8() % (126 - 32 + 1);
  return ((char)i_random) + ' ';
}



uint8_t convert_custom_collation_on_printable_ascii_char(char c){
  //print an ascii table found on Internet to understand this function
  //invalid characters are sent on space ' '
  if(c < 32 || c > 126){
    return (uint8_t) ' ';
  }
  //special characters come first
  if(c < 48){
    return (uint8_t) c;
  }
  if(c > 57 && c < 65){
    return ((uint8_t) c) - 10;//skipping the digits
  }
  if(c > 90 && c < 97){
    return ((uint8_t) c) - 10 - 26;//skipping the digits and the capital letters
  }
  if(c > 122){
    return ((uint8_t) c) - 10 - 52;//skipping the digits and the letters
  }
  //then digits
  if(c > 47 && c < 58){
    return ((uint8_t) c) + (65 - 57 - 1) + (97 - 90 - 1) + (127 - 122 - 1);//shifting after the special characters
  }
  //then letters (AaBbCc...)
  if(c >= 'A' && c <= 'Z'){
    return ((uint8_t) c - 'A') * 2
         + (126 - 32 + 1) - 52; //number of printable characters minus number of letters
  }
  //if(c >= 'a' && c <= 'z'){
    return ((uint8_t) c - 'a') * 2 + 1
         + (126 - 32 + 1) - 52; //number of printable characters minus number of letters
  //}
}//end function convert_custom_collation_on_printable_ascii_char()



int compare_custom_collation_on_printable_ascii_char(char a, char b){
  uint8_t c = convert_custom_collation_on_printable_ascii_char(a);
  uint8_t d = convert_custom_collation_on_printable_ascii_char(b);
  return (c > d) - (c < d);
}



typedef struct{
  size_t i_string_size;
  size_t i_allocated_size;
  char* s_string;
} t_TSODLULS_oString;//prefix "os" associated for object-string



void init_string(
  t_TSODLULS_oString* p_os_string
){
  p_os_string->s_string = NULL;
  p_os_string->i_string_size = 0;
  p_os_string->i_allocated_size = 0;
}



int init_array_of_strings(
  t_TSODLULS_oString** p_arr_os_strings,
  size_t i_number_of_elements
){
  size_t i;
  *p_arr_os_strings = calloc(i_number_of_elements, sizeof(t_TSODLULS_oString));
  if(*p_arr_os_strings == NULL){
    return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
  }

  for(i = 0; i < i_number_of_elements; ++i){
    init_string( &((*p_arr_os_strings)[i]) );
  }
  return 0;
}



int copy_string_as_primitive_datatype(
  t_TSODLULS_oString os_string_old,
  t_TSODLULS_oString* p_os_string_new
){
  size_t i;
  if(p_os_string_new->s_string != NULL){
    free(p_os_string_new->s_string);
    p_os_string_new->s_string = NULL;
    p_os_string_new->i_string_size = 0;
    p_os_string_new->i_allocated_size = 0;
  }
  p_os_string_new->s_string = calloc(os_string_old.i_string_size, sizeof(char));
  if(p_os_string_new->s_string == NULL){
    return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
  }
  p_os_string_new->i_string_size = 0;
  p_os_string_new->i_allocated_size = os_string_old.i_string_size;
  //filling the new string
  for(i = 0; i < os_string_old.i_string_size; ++i){
    p_os_string_new->s_string[i] = os_string_old.s_string[i];
  }
  p_os_string_new->i_string_size = os_string_old.i_string_size;
  return 0;
}



int copy_array_of_strings(
  t_TSODLULS_oString* arr_os_strings_old,
  size_t i_number_of_elements,
  t_TSODLULS_oString** p_arr_os_strings_new,
  uint8_t i_copy_mode //0: primitive datatype mode, 1: shared string mode
){
  size_t i;
  int i_result = 0;
  i_result = init_array_of_strings(p_arr_os_strings_new, i_number_of_elements);
  if(i_result != 0){
    return i_result;
  }

  for(i = 0; i < i_number_of_elements; ++i){
    if(i_copy_mode == 0){
      i_result = copy_string_as_primitive_datatype(
          arr_os_strings_old[i],
          &((*p_arr_os_strings_new)[i])
      );
    }
    else if(i_copy_mode == 1){
      (*p_arr_os_strings_new)[i] = arr_os_strings_old[i];
    }
    if(i_result != 0){
      break;
    }
  }
  return i_result;
}//end function copy_array_of_strings()



void free_array_of_strings(
  t_TSODLULS_oString** p_arr_os_strings,
  size_t i_number_of_elements
){
  size_t i;
  if(*p_arr_os_strings != NULL){
    for(i = 0; i < i_number_of_elements; ++i){
      if((*p_arr_os_strings)[i].s_string != NULL){
        TSODLULS_free((*p_arr_os_strings)[i].s_string);
      }
    }
    TSODLULS_free(*p_arr_os_strings);
  }
}



int compare_p_os_string_without_collation(const void *a, const void *b){
  const t_TSODLULS_oString c = (const t_TSODLULS_oString) **((t_TSODLULS_oString**)a);
  const t_TSODLULS_oString d = (const t_TSODLULS_oString) **((t_TSODLULS_oString**)b);
  int i_result = 0;
  size_t i;
  size_t i_max;
  i_max = c.i_string_size;
  if(d.i_string_size < i_max){
    i_max = d.i_string_size;
  }
  for(i = 0; i < i_max; ++i){
    i_result = ((int)(c.s_string[i])) - ((int)(d.s_string[i]));
    if(i_result != 0){
      return i_result;
    }
  }
  return (c.i_string_size > d.i_string_size) - (c.i_string_size < d.i_string_size);
}



int compare_p_os_string_with_collation(const void *a, const void *b){
  const t_TSODLULS_oString c = (const t_TSODLULS_oString) **((t_TSODLULS_oString**)a);
  const t_TSODLULS_oString d = (const t_TSODLULS_oString) **((t_TSODLULS_oString**)b);
  int i_result = 0;
  size_t i;
  size_t i_max;
  i_max = c.i_string_size;
  if(d.i_string_size < i_max){
    i_max = d.i_string_size;
  }
  for(i = 0; i < i_max; ++i){
    i_result = compare_custom_collation_on_printable_ascii_char(c.s_string[i], d.s_string[i]);
    if(i_result != 0){
      return i_result;
    }
  }
  return (c.i_string_size > d.i_string_size) - (c.i_string_size < d.i_string_size);
}



void print_bits_for_string(t_TSODLULS_oString* p_os_string){
  unsigned char* p_data_char = NULL;
  if(p_os_string->s_string == NULL){
    printf("String is null.\n");
    return;
  }

  p_data_char = (unsigned char*) p_os_string->s_string;
  for(size_t i = 0; i < p_os_string->i_string_size; ++i){
    for(int j = 7; j >= 0; --j){
      if((p_data_char[i] >> j) & 1){
        printf("1");
      }
      else{
        printf("0");
      }
    }
    printf(" ");
  }
  printf("\n");
}



void print_bits_for_key(t_TSODLULS_sort_element* p_sort_element){
  unsigned char* p_data_char = NULL;
  if(p_sort_element->s_key == NULL){
    printf("Key is null.\n");
    return;
  }

  p_data_char = (unsigned char*) p_sort_element->s_key;
  for(size_t i = 0; i < p_sort_element->i_key_size; ++i){
    for(int j = 7; j >= 0; --j){
      if((p_data_char[i] >> j) & 1){
        printf("1");
      }
      else{
        printf("0");
      }
    }
    printf(" ");
  }
  printf("\n");
}



