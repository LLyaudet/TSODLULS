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



#if TSODLULS_MAX_THRESH_SEQUEL <= 2
p_cell1 = &(arr_elements[current_instance.i_offset_first + arr_offsets[i] - 2]);
p_cell2 = p_cell1 + 1;
for(
  size_t j = current_instance.i_depth + 1, j_max = TSODLULS_min_exp(p_cell1->i_key_size, p_cell2->i_key_size);
  j < j_max;
  ++j
){
  if(p_cell2->s_key[j] < p_cell1->s_key[j]){
    tmp_cell = *p_cell1; *p_cell1 = *p_cell2; *p_cell2 = tmp_cell;//swapping
    break;
  }
  if(p_cell2->s_key[j] > p_cell1->s_key[j]){
    break;
  }
}
#else
{
  //Last element
  t_TSODLULS_sort_element* const p_last_cell = &(arr_elements[current_instance.i_offset_first + arr_offsets[i] - 1]);
  //First element
  //t_TSODLULS_sort_element* const p_first_cell = &(arr_elements[current_instance.i_offset_first + arr_offsets[i] - arr_counts[i]]);
  t_TSODLULS_sort_element* const p_first_cell = p_last_cell - arr_counts[i] + 1;
  //p_cell1 = run_ptr
  p_cell2 = p_first_cell;//tmp_ptr

  /* Insertion sort, running from left-hand-side up to right-hand-side.  */
  p_cell1 = p_first_cell + 1;
  do{
    int b_do_while;
    p_cell2 = p_cell1 - 1;
    do{
      b_do_while = 0;
      //nextified strings
      for(
        size_t j = current_instance.i_depth + 1, j_max = TSODLULS_min_exp(p_cell1->i_key_size, p_cell2->i_key_size);
        j < j_max;
        ++j
      ){
        if(p_cell2->s_key[j] < p_cell1->s_key[j]){
          break;
        }
        if(p_cell2->s_key[j] > p_cell1->s_key[j]){
          --p_cell2;
          if(p_cell2 >= p_first_cell){
            b_do_while = 1;
          }
          break;
        }
      }
    }while(b_do_while);
    ++p_cell2;
    if(p_cell2 != p_cell1){
      tmp_cell = *p_cell1;
      t_TSODLULS_sort_element* high;
      t_TSODLULS_sort_element* low;
      for(high = low = p_cell1; (--low) >= p_cell2; high = low){
        *high = *low;
      }
      *high = tmp_cell;
    }
  }while((++p_cell1) <= p_last_cell);
}
#endif

