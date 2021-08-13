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
  p_cell1 = p_first_cell;
  while((++p_cell1) <= p_last_cell){
    int b_do_while = 1;
    p_cell2 = p_cell1;
    //while(p_cell1->i_key < p_cell2->i_key){
    while(b_do_while){
      --p_cell2;
      if(p_cell2 < p_first_cell){
        break;
      }
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
          b_do_while = 1;
          break;
        }
      }
    }
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
  }
}
#endif

