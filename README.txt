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

©Copyright 2018-2020 Laurent Lyaudet

----------------------------------------------------------------------------
Preamble
----------------------------------------------------------------------------
This folder contains the source code of the library TSODLULS
(Tree Structured Orders Definition Language, Universal Lexicographic Sort).

This library provides functions to:
 - lexicographicalize keys for sorting,
 - parse TSODL (Tree Structured Orders Definition Language)
   and generate C code from a TSOD (Tree Structured Order Definition) to lexicographicalize the keys,
 - sort string using (Contre)Lexicographic or Next order.

To understand the theory behind this library you can read our article:
"A class of orders with linear? time sorting algorithm"

A very short abstract of our article is "Everything is lexicographic.".
It means that, probably for all orders from real world examples,
you can efficiently convert the objects to be sorted into strings that need to be sorted
with lexicographic order.
(In fact, we even prove that lexicographic order is not needed
 and that "Next" partial order is sufficient.)
Lexicographic order or "Next" partial order can be efficiently sorted in
linear time using a variant of radix sort
(if you assume RAM model of computation with constant size and time
for pointers/sizes and arithmetic on pointers/sizes).
Each element/object is sorted according to a key
(that key may be complex, not necessarily a primitive data type).
The lexicographic key has size that is linear in the size of the original key.
The sorting algorithm is linear time with respect to the sum of the sizes of the key,
not necessarily with respect to the number of elements to sort.
When the sum of the sizes of the key (the size of the instance) is great enough,
radix sort is faster than qsort.


----------------------------------------------------------------------------
Lexicographicalizing or "nextifying"
----------------------------------------------------------------------------

A simple case of lexicographicalization is for finite orders (see TSODLULS_finite_orders.h/c).
Some finite orders are already lexicographicalized when you look at the bits in the processor/RAM.
It is the case for unsigned integers with big-endianness.
If your processor is little-endian, you need to swap the bytes and that's it.
For other finite orders, you convert them first to unsigned integers
 in a way that respects the original order.
As an example, signed integers on 8 bits are converted to unsigned integers on 8 bits so that
-128 becomes 0, -127 becomes 1, ..., -1 becomes 127, 0 becomes 128,
 1 becomes 129, ..., 126 becomes 254, 127 becomes 255.
You can do the same thing for signed integers on 16/32/64 bits.
You can also do the same thing between float and 32-bits unsigned integers,
 and between double and 64-bits unsigned integers,
but it is more complicated (you may look at the source code in TSODLULS_finite_orders.c).

For orders that are more complex than finite orders, you need to manage a string and add bytes
to that string according to the lexicographicalization process (see our article, please).
This may require padding (see TSODLULS_padding.c).

Adding bytes to the lexicographic key from primitive data types (finite orders) can be done
using the functions TSODLULS_add_bytes_to_key_from_uint... in TSODLULS_finite_orders.c.
For this you must give padding parameters.
These parameters will depend of the order you want to sort by.


----------------------------------------------------------------------------
Sorting
----------------------------------------------------------------------------

Sorting algorithms suited for "nextified" keys are available in TSODLULS_sorting_long_orders.c
and in TSODLULS_sorting_short_orders.c.
We plan to add new "best-in-class" algorithms there, for general/stable sorting.


----------------------------------------------------------------------------
Short and long orders
----------------------------------------------------------------------------

Because the keys are strings, we can distinguish between "short" orders,
where the keys are at most 64 bits long, and "long" orders where the keys
may be longer than 64 bits.
It is somewhat arbitrary to put the limit at 64 bits but it corresponds to
current hardware characteristics.
Because of this distinction, the cells of the array to be sorted may be of two types:
short cells with a pointer to the object to be sorted and a 64-bit unsigned integer key,
long cells with a pointer to the object to be sorted and a pointer to a string key
(a counter for the real size of the key and a counter for the allocated size of the key).
Initialization and allocation of the cells are helped by the functions in
TSODLULS_misc.c


----------------------------------------------------------------------------
Comparison functions
----------------------------------------------------------------------------

With the classical "comparison function" paradigm, you need comparison black box
functions to sort objects. Some comparison functions are available in
TSDLULS_comparison.c. They are needed for tests and benchmarks and also because
we aim at generating most efficient code. It means that using comparison model in
some cases will be needed.


----------------------------------------------------------------------------
Code style
----------------------------------------------------------------------------

This library contains code in C and also helper scripts in PHP.
We use the following code style:
- loose Systems Hungarian notation for variables (see wikipedia):
  -- i before an integer
  -- c before a character
  -- s before a string (pointer to char)
  -- f before a floating point number (float, double, etc.)
  -- arr before an array
  -- p before a pointer
- snake case in C code for variables and functions:
  - i_number_of_elements
  - c_current_byte
  - s_name (this is a pointer for an array)
  - f_weigth
  - arr_i_elements for an array of integers (this is also a pointer for an array)
  - p_i_number_of_elements (it may be the parameter of a function that returns
      an error code and initializes the number of elements)
- camel case in PHP code for variable and functions:
  - iNumberOfElements
  - cCurrentByte
  - sName
  - fWeigth
  - arrIElements for an array of integers
- when needed we use "strict" Systems Hungarian notation,
  this is useful in tests and benchmarks where we have all primitive data types in one place.
  Instead of creating variable names, we just abbreviate the data types:
  - ui_8 or ui8 for some unsigned integer on 8 bits
  - i_32_2 or i32_2 for some signed integer on 32 bits and name i_32 or i32 was already taken...
- We use two spaces indent without tabs.
- We try to avoid long lines using frequent line returns:
  -- with single indent when continuing a line of "declarative" or condition code
     (function signature and condition in an "if")
  -- with double indent when continuing a line of "imperative" code (function call, expression).
- We see "blocks" as triangles (when they are too big to fit in one line):

  ------->
         /
        /
       /
      /
     /
    /
   /
  /

  The first arrow (ok it's poor ascii art ;P) is horizontal from left to right,
  and the second arrow is diagonal from upright to downleft (it slices through the code).

  Examples of blocks:
  -- function signature
    void foo(             <--------- header of the block (horizontal arrow)
      type1 param1,       <--------- content of the block (sliced through by the diagonal arrow)
      type2 param2,       <--------- content of the block (sliced through by the diagonal arrow)
    );                    <--------- end of the block (end of the diagonal arrow)
  -- function call
    foo(                  <--------- header of the block (horizontal arrow)
        param1,           <--------- content of the block (sliced through by the diagonal arrow)
        param2,           <--------- content of the block (sliced through by the diagonal arrow)
    );                    <--------- end of the block (end of the diagonal arrow)
  -- if condition
    if(condition1         <--------- header of the block (horizontal arrow)
      && condition2       <--------- content of the block (sliced through by the diagonal arrow)
      && condition3       <--------- content of the block (sliced through by the diagonal arrow)
    ){                    <--------- end of the block (end of the diagonal arrow), this is also the header of the next block
  -- function body or if body
    ){                    <--------- header of the block (horizontal arrow), this is also the end of the previous block
      doSomething1;       <--------- content of the block (sliced through by the diagonal arrow)
      doSomething2;       <--------- content of the block (sliced through by the diagonal arrow)
      return something;   <--------- content of the block (sliced through by the diagonal arrow)
    }                     <--------- end of the block (end of the diagonal arrow)

    or else body

    else{                 <--------- header of the block (horizontal arrow)
      doSomething1;       <--------- content of the block (sliced through by the diagonal arrow)
      doSomething2;       <--------- content of the block (sliced through by the diagonal arrow)
      return something;   <--------- content of the block (sliced through by the diagonal arrow)
    }                     <--------- end of the block (end of the diagonal arrow)

  As you can see, each header of a block ends with a '(' or a '{'.
  Thus these characters are at the end of one line, not at the beginning.
  The end of one block (function signature, if condition)
  may be merged with the beginning of the next block.
  Since one block may fit in one line, one line may contain a full block
  plus the header line of another block.

  Examples of merged blocks:
  void foo(type1 param1){ <--- merging
    doSomething1;
    doSomething2;
    return something;
  }

  void foo(
    type1 param1,
    type2 param2
  ){  <----- merging
    doSomething1;
    doSomething2;
    return something;
  }

  if(condition1){ <--- merging
    doSomething1;
  }

  if(condition1
    || condition2
  ){ <--- merging
    doSomething1;
  }
  We do not merge "} else {".

- We see conditions in "if" as boolean circuits rotated counter clockwise by an angle of 90°.
                     ___________
                    |  AND = && |
                     -----------
                     /         \
           _________/           \_________
          | OR = || |           |condition1|
           ---------             ----------
              / \
   __________/   \_________
  |condition3|  |condition2|
   ----------    ----------

  Rotating as we do it:
  if(condition1
    && (condition2
       || condition3)
  ){

  Rotating would be clearer with extra space:
  if(  condition1
    && (
          condition2
       ||
          condition3
       )
  ){
  Note that we naturally tend to use 3 spaces indent for this because || and && are two characters wide.
  Note also that the "circuit" may use unbounded fan-in gates, like:
       (
          condition1
       ||
          condition2
       ||
          condition3
       ...
       ||
          conditionN
       )
  for a single OR-gate with fan-in N.

- Either a function has no error case and it may return a "real" result,
or a function has some error cases and its return type is an int containing
an error code. The int is 0 if no error occurred and some constant explained
in TSODLULS.h otherwise. When we still need that the function returns something
more than its error code, we use parameters of the function with pointers.


----------------------------------------------------------------------------
Library map
----------------------------------------------------------------------------
There is one header file TSODLULS.h containing all the external constants
(Error codes, etc.), structures and the function signatures of the library.
For those that do not like scrolling in one file,
separate header files containing the signatures of the functions in one C file
of the library are available:
 - TSODLULS_comparison.h
 - TSODLULS_finite_orders.h
 - TSODLULS_misc.h
 - TSODLULS_padding.h
 - TSODLULS_sorting_long_orders.h
 - TSODLULS_sorting_short orders.h
These headers files are here for reference but must not be used (use TSODLULS.h).
The code of the functions is available in the following files:
 - TSODLULS_comparison.c comparison function for various primitive datatypes and cells of this library
 - TSODLULS_finite_orders.c converting primitive datatypes into unsigned integers while preserving order
 - TSODLULS_misc.c helper functions for using arrays of TSODLULS cells
 - TSODLULS_padding.c padding the lexicographic keys
 - TSODLULS_sorting_long_orders.c the sorting algorithms for long orders
 - TSODLULS_sorting_short_orders.c the sorting algorithms for short orders
Some of the functions are also available as macro in the following files:
 - //not needed yet TSODLULS_comparison__macro.h
 - TSODLULS_finite_orders__macro.h
 - TSODLULS_misc__macro.h
 - TSODLULS_padding__macro.h
 - //not needed yet TSODLULS_sorting_long_orders__macro.h and TSODLULS_sorting_short_orders__macro.h
All these files are included in the file TSODLULS__macro.h.
The file TSODLULS__macro.h explains conventions and guides for using TSODLSULS macros.
The comment before a function tells whether it is available as a macro.

There is a Makefile that you can run with "make", in order to:
- build the library both statically and dynamically
- install the dynamic library in /usr/lib/
- build and run tests
- build and run benchmarks (beware it will use around 1G of RAM)
- clean the folder of compilation and test results

Folder bin contains some of the results of compilation.
It just contains a .gitignore by default.

COPYING contains the license GPL3.
COPYING.LESSER contains the license LGPL3.

The folder "tests_benchmarks" contains the files "test_functions.c"
(mainly for generating random variables), "test_macros.c", and a folder for each
test/benchmark.
In each test/benchmark, there is a .c file containing the related code
and that describes the purpose of the test/benchmark.
Some tests or benchmarks may use helper scripts in PHP (for analyzing the results, etc.).

The folder "competitor_algorithms" contains variants of algorithms/implementations
that were tested and benchmarked. Its structure is similar to the library .c and .h files
(TSODLULS.h has an equivalent TSODLULS__competitor.h file,
TSODLULS_sorting_long_orders.c has an equivalent TSODLULS_sorting_long_orders__competitor.c file, etc.).
The makefile has a rule to construct a variant of the static library with all competitor algorithms.
This static library is used for custom tests and benchmarks for testing and comparing
competitor algorithms and their variants.
The main library should contain the best implementations of the best competitor algorithms.
It applies to sorting algorithms but also to the other functions of the library,
as soon as many variants emerged.


----------------------------------------------------------------------------
Environments
----------------------------------------------------------------------------
This library has been tested on Debian 9.4
with gcc version 6.3.0 20170516 (Debian 6.3.0-18+deb9u1)
and glibc.
We use file endian.h in glibc that is not available everywhere.
If you can email me for helping make this library more portable, please do.


----------------------------------------------------------------------------
Hello world - Using the library
----------------------------------------------------------------------------
Using the library for sorting 32-bits signed integers can be done as follow:
 - assume you have an array of 32-bits signed integers
    int32_t* arr_i32;
   with a number of elements
    size_t i_number_of_elements;
 - fill it with your data
 - then you need a loop for converting the 32-bits signed integers into an array of cells
 containing a pointer to the original signed integer and an unsigned integer.
    t_TSODLULS_sort_element* arr_cells = NULL;
    i_result = TSODLULS_init_array_of_elements(&arr_cells, i_number_of_elements);
    if(i_result != 0){
      return i_result;//error occurred
    }
    for(size_t i = 0; i < i_number_of_elements; ++i){
      i_result = TSODLULS_add_bytes_to_key_from_uint32(
          &(arr_cells[i]),
          TSODLULS_get_uint32_from_int32(arr_i32[i]),
          0,//no padding
          0,//no padding
          0,//no padding
          0,//no padding
          4,//4 contiguous bytes
          0//no offset
      );
      if(i_result != 0){
        break;
      }
      arr_cells[i].p_object = &(arr_i32[i]);
    }
    if(i_result != 0){
      return i_result;//error occurred
    }
 - then you can sort:
    TSODLULS_sort(arr_cells, i_number_of_elements);
 - and fill the result:
    for(i = 0; i < i_number_of_elements; ++i){
      arr_i32_result[i] = *((int32_t*)(arr_cells[i].p_object));
    }
 - More examples are available in tests and benchmarks.



----------------------------------------------------------------------------
Hello world - Designing new sorting algorithms
----------------------------------------------------------------------------
We created an architecture within this library so that it is easy to prototype
and benchmark a new sorting algorithm. For this purpose, we use a few PHP
helper scripts.
Let us give an example that you can follow in order to get started.
We will explain how we went from algorithm TSODLULS_sort_radix8_count__short__mark2
to TSODLULS_sort_radix8_count__short__mark3.

1°)First step
First you can find TSODLULS_sort_radix8_count__short__mark2 in
./competitor_algorithms/TSODLULS_sorting_short_orders__competitor.c
Open this file and copy-paste the code of the function
TSODLULS_sort_radix8_count__short__mark2 and rename it
TSODLULS_sort_radix8_count__short__MyMark.
In the code of TSODLULS_sort_radix8_count__short__MyMark,
replace
  arr_instances = calloc(7 * 256, sizeof(t_TSODLULS_radix_instance));
  if(arr_instances == NULL){
    TSODLULS_free(arr_elements_copy);
    return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
  }
by
  if(i_max_length - 1 > 0){
    arr_instances = calloc((i_max_length - 1) * 256, sizeof(t_TSODLULS_radix_instance));
    if(arr_instances == NULL){
      TSODLULS_free(arr_elements_copy);
      return I_ERROR__COULD_NOT_ALLOCATE_MEMORY;
    }
  }
Save and that's it for this file.

2°)Second step
You need to modify the header file now.
Open ./competitor_algorithms/TSODLULS__competitor.h
and copy-paste the declaration of TSODLULS_sort_radix8_count__short__mark2
just below and rename it TSODLULS_sort_radix8_count__short__MyMark.

3°)Third step
You need to declare your algorithm in the list of competitor
algorithms for PHP helper scripts.
Open ./tests_benchmarks/sortingAlgorithmsList.php and copy-paste
  'TSODLULS_sort_radix8_count__short__mark2' => array(
    'name' => 'TSODLULS_sort_radix8_count__short__mark2',
    'function' => 'TSODLULS_sort_radix8_count__short__mark2',
    'celltype' => 'short',
    'size' => 'direct',
    'comparison' => false,
    'stable' => true,
  ),
just below, renaming as usual:
  'TSODLULS_sort_radix8_count__short__MyMark' => array(//Here it must be a unique key
    'name' => 'TSODLULS_sort_radix8_count__short__MyMark',//You can put anything here as long as you recognize your algorithm
    'function' => 'TSODLULS_sort_radix8_count__short__MyMark',//Spell it correctly
    'celltype' => 'short',//it works on short cells, there are direct, short and long cells
    'size' => 'direct',//the number of bytes of the primitive datatypes will be added as a parameter to the function call
    'comparison' => false,//no comparison function will be added as a parameter to the function call
    'stable' => true,//this algorithm is a stable one, information only (no feature related yet)
  ),

4°)Fourth step
Ready to test and benchmark your algorithm?
Let's go!
a)Test
Open a terminal and cd in ./tests_benchmarks/test_custom/
Run the command
  php generateCustomTest.php
and choose your algorithm.
b)Benchmark
Open a terminal and cd in ./tests_benchmarks/benchmark_custom/
Run the command
  php generateCustomBenchmark.php
and choose your algorithm and its competitor.
You can select 'y' when asked if you want to use macraffs.

Et voilà ! Happy hacking :)

PS: If you use the custom benchmark, you will notice that when two algorithms are close,
the second algorithm you choose is slightly faster (except for some range with int8 test).
This is probably because of cache memory.
That's what we noticed on our laptop but your mileage may vary.
Anyway we suggest you launch the custom benchmark twice
(choosing the two algorithms in both orders).

