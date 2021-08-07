#This file is part of TSODLULS library.
#
#TSODLULS is free software: you can redistribute it and/or modify
#it under the terms of the GNU Lesser General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#TSODLULS is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU Lesser General Public License for more details.
#
#You should have received a copy of the GNU Lesser General Public License
#along with TSODLULS.  If not, see <http://www.gnu.org/licenses/>.
#
#©Copyright 2018-2021 Laurent Lyaudet

CC=gcc

CFLAGS=-Wall -O3

VERSION=0_2_0

OBJECTS-DIRECTORY=../../build_temp/C/

LIB-DIRECTORY=../../build_final/bin/

FUNCTIONS-BODIES-DIRECTORY=competitor_algorithms/b/

#The headers that are actually needed for the library
HEADERS=./TSODLULS.h ./TSODLULS__macro.h ./TSODLULS_finite_orders__macro.h ./TSODLULS_misc__macro.h ./TSODLULS_padding__macro.h

HEADERS-COMPETITOR=$(HEADERS) ./competitor_algorithms/TSODLULS__competitor.h

OBJECTS-STATIC=$(OBJECTS-DIRECTORY)TSODLULS_finite_orders.o \
               $(OBJECTS-DIRECTORY)TSODLULS_sorting_long_orders.o \
               $(OBJECTS-DIRECTORY)TSODLULS_sorting_short_orders.o \
               $(OBJECTS-DIRECTORY)TSODLULS_comparison.o \
               $(OBJECTS-DIRECTORY)TSODLULS_misc.o \
               $(OBJECTS-DIRECTORY)TSODLULS_padding.o

OBJECTS-DYNAMIC=$(OBJECTS-DIRECTORY)TSODLULS_finite_orders_dyn.o \
                $(OBJECTS-DIRECTORY)TSODLULS_sorting_long_orders_dyn.o \
                $(OBJECTS-DIRECTORY)TSODLULS_sorting_short_orders_dyn.o \
                $(OBJECTS-DIRECTORY)TSODLULS_comparison_dyn.o \
                $(OBJECTS-DIRECTORY)TSODLULS_misc_dyn.o \
                $(OBJECTS-DIRECTORY)TSODLULS_padding_dyn.o

OBJECTS-STATIC-COMPETITOR=$(OBJECTS-DIRECTORY)TSODLULS_finite_orders__competitor.o \
                          $(OBJECTS-DIRECTORY)TSODLULS_sorting_comparison_callback__competitor.o \
                          $(OBJECTS-DIRECTORY)TSODLULS_sorting_long_orders__competitor.o \
                          $(OBJECTS-DIRECTORY)TSODLULS_sorting_short_orders__competitor.o \
                          $(OBJECTS-DIRECTORY)TSODLULS_comparison__competitor.o \
                          $(OBJECTS-DIRECTORY)TSODLULS_misc__competitor.o \
                          $(OBJECTS-DIRECTORY)TSODLULS_padding__competitor.o

FUNCTIONS-BODIES-SORTING-COMPARISON-CALLBACK=$(FUNCTIONS-BODIES-DIRECTORY)body_TSODLULS_qsort__comparison_callback.c

FUNCTIONS-BODIES-SORTING-LONG=$(FUNCTIONS-BODIES-DIRECTORY)body_TSODLULS_qsort_inlined__long.c \
                              $(FUNCTIONS-BODIES-DIRECTORY)body_TSODLULS_sort_radix8_count_insertion__mark1.c \
                              $(FUNCTIONS-BODIES-DIRECTORY)body_TSODLULS_sort_radix8_count_insertion__mark2.c \
                              $(FUNCTIONS-BODIES-DIRECTORY)body_TSODLULS_sort_radix8_count_insertion__mark3.c \
                              $(FUNCTIONS-BODIES-DIRECTORY)body_TSODLULS_sort_radix8_count_insertion__mark4.c \
                              $(FUNCTIONS-BODIES-DIRECTORY)body_TSODLULS_sort_radix8_count__mark1.c

FUNCTIONS-BODIES-SORTING-SHORT=$(FUNCTIONS-BODIES-DIRECTORY)body_TSODLULS_qsort_inlined__short.c \
                               $(FUNCTIONS-BODIES-DIRECTORY)body_TSODLULS_sort_radix8_count_insertion__short__mark1.c \
                               $(FUNCTIONS-BODIES-DIRECTORY)body_TSODLULS_sort_radix8_count_insertion__short__mark2.c \
                               $(FUNCTIONS-BODIES-DIRECTORY)body_TSODLULS_sort_radix8_count_insertion__short__mark3.c \
                               $(FUNCTIONS-BODIES-DIRECTORY)body_TSODLULS_sort_radix8_count_insertion__short__mark4.c \
                               $(FUNCTIONS-BODIES-DIRECTORY)body_TSODLULS_sort_radix8_count_insertion__short__mark5.c \
                               $(FUNCTIONS-BODIES-DIRECTORY)body_TSODLULS_sort_radix8_count_insertion__short__mark6.c \
                               $(FUNCTIONS-BODIES-DIRECTORY)body_TSODLULS_sort_radix8_count_qsort__short.c \
                               $(FUNCTIONS-BODIES-DIRECTORY)body_TSODLULS_sort_radix8_count__short__mark1.c \
                               $(FUNCTIONS-BODIES-DIRECTORY)body_TSODLULS_sort_radix8_count__short__mark2.c \
                               $(FUNCTIONS-BODIES-DIRECTORY)body_TSODLULS_sort_radix8_count__short__mark3.c

FUNCTIONS-BODIES=$(FUNCTIONS-BODIES-SORTING-COMPARISON-CALLBACK) \
                 $(FUNCTIONS-BODIES-SORTING-LONG) \
                 $(FUNCTIONS-BODIES-SORTING-SHORT)

.PHONY: run-tests run-tests-dynamic clean run-benchmarks run-benchmarks-dynamic


#-----------------------------------------------------------
#Build library
#-----------------------------------------------------------
build: build-static build-dynamic build-static-with-competitor-algorithms


#Static library
build-static: $(LIB-DIRECTORY)libTSODLULS_$(VERSION).a

$(LIB-DIRECTORY)libTSODLULS_$(VERSION).a: $(OBJECTS-STATIC)
	ar -rcs $(LIB-DIRECTORY)libTSODLULS_$(VERSION).a $(OBJECTS-STATIC)
#	ar -rc ./bin/libTSODLULS_$(VERSION).a ./bin/TSODLULS_finite_orders.o
#	ranlib ./bin/libTSODLULS_$(VERSION).a

$(OBJECTS-DIRECTORY)TSODLULS_finite_orders.o: $(HEADERS) ./TSODLULS_finite_orders.c
	$(CC) $(CFLAGS) -c ./TSODLULS_finite_orders.c -o $(OBJECTS-DIRECTORY)TSODLULS_finite_orders.o

$(OBJECTS-DIRECTORY)TSODLULS_sorting_long_orders.o: $(HEADERS) ./TSODLULS_sorting_long_orders.c $(FUNCTIONS-BODIES-SORTING-LONG)
	$(CC) $(CFLAGS) -c ./TSODLULS_sorting_long_orders.c -o $(OBJECTS-DIRECTORY)TSODLULS_sorting_long_orders.o

$(OBJECTS-DIRECTORY)TSODLULS_sorting_short_orders.o: $(HEADERS) ./TSODLULS_sorting_short_orders.c $(FUNCTIONS-BODIES-SORTING-SHORT)
	$(CC) $(CFLAGS) -c ./TSODLULS_sorting_short_orders.c -o $(OBJECTS-DIRECTORY)TSODLULS_sorting_short_orders.o

$(OBJECTS-DIRECTORY)TSODLULS_comparison.o: $(HEADERS) ./TSODLULS_comparison.c
	$(CC) $(CFLAGS) -c ./TSODLULS_comparison.c -o $(OBJECTS-DIRECTORY)TSODLULS_comparison.o

$(OBJECTS-DIRECTORY)TSODLULS_misc.o: $(HEADERS) ./TSODLULS_misc.c
	$(CC) $(CFLAGS) -c ./TSODLULS_misc.c -o $(OBJECTS-DIRECTORY)TSODLULS_misc.o

$(OBJECTS-DIRECTORY)TSODLULS_padding.o: $(HEADERS) ./TSODLULS_padding.c
	$(CC) $(CFLAGS) -c ./TSODLULS_padding.c -o $(OBJECTS-DIRECTORY)TSODLULS_padding.o

#Dynamic library
build-dynamic: $(LIB-DIRECTORY)libTSODLULS_$(VERSION).so

$(LIB-DIRECTORY)libTSODLULS_$(VERSION).so: $(OBJECTS-DYNAMIC)
	$(CC) -shared -o $(LIB-DIRECTORY)libTSODLULS_$(VERSION).so $(OBJECTS-DYNAMIC)

$(OBJECTS-DIRECTORY)TSODLULS_finite_orders_dyn.o: $(HEADERS) ./TSODLULS_finite_orders.c
	$(CC) $(CFLAGS) -fPIC -c ./TSODLULS_finite_orders.c -o $(OBJECTS-DIRECTORY)TSODLULS_finite_orders_dyn.o

$(OBJECTS-DIRECTORY)TSODLULS_sorting_long_orders_dyn.o: $(HEADERS) ./TSODLULS_sorting_long_orders.c $(FUNCTIONS-BODIES-SORTING-LONG)
	$(CC) $(CFLAGS) -fPIC -c ./TSODLULS_sorting_long_orders.c -o $(OBJECTS-DIRECTORY)TSODLULS_sorting_long_orders_dyn.o

$(OBJECTS-DIRECTORY)TSODLULS_sorting_short_orders_dyn.o: $(HEADERS) ./TSODLULS_sorting_short_orders.c $(FUNCTIONS-BODIES-SORTING-SHORT)
	$(CC) $(CFLAGS) -fPIC -c ./TSODLULS_sorting_short_orders.c -o $(OBJECTS-DIRECTORY)TSODLULS_sorting_short_orders_dyn.o

$(OBJECTS-DIRECTORY)TSODLULS_comparison_dyn.o: $(HEADERS) ./TSODLULS_comparison.c
	$(CC) $(CFLAGS) -fPIC -c ./TSODLULS_comparison.c -o $(OBJECTS-DIRECTORY)TSODLULS_comparison_dyn.o

$(OBJECTS-DIRECTORY)TSODLULS_misc_dyn.o: $(HEADERS) ./TSODLULS_misc.c
	$(CC) $(CFLAGS) -fPIC -c ./TSODLULS_misc.c -o $(OBJECTS-DIRECTORY)TSODLULS_misc_dyn.o

$(OBJECTS-DIRECTORY)TSODLULS_padding_dyn.o: $(HEADERS) ./TSODLULS_padding.c
	$(CC) $(CFLAGS) -fPIC -c ./TSODLULS_padding.c -o $(OBJECTS-DIRECTORY)TSODLULS_padding_dyn.o

#Static library with competitor algorithms
#This static library is used for custom tests and benchmarks for testing and comparing
#competitor algorithms and their variants.
build-static-with-competitor-algorithms: $(LIB-DIRECTORY)libTSODLULS_with_competitor_algorithms_$(VERSION).a

$(LIB-DIRECTORY)libTSODLULS_with_competitor_algorithms_$(VERSION).a: $(OBJECTS-STATIC) $(OBJECTS-STATIC-COMPETITOR)
	ar -rcs $(LIB-DIRECTORY)libTSODLULS_with_competitor_algorithms_$(VERSION).a $(OBJECTS-STATIC) $(OBJECTS-STATIC-COMPETITOR)

$(OBJECTS-DIRECTORY)TSODLULS_finite_orders__competitor.o: $(HEADERS-COMPETITOR) ./competitor_algorithms/TSODLULS_finite_orders__competitor.c
	$(CC) $(CFLAGS) -c ./competitor_algorithms/TSODLULS_finite_orders__competitor.c -o $(OBJECTS-DIRECTORY)TSODLULS_finite_orders__competitor.o

$(OBJECTS-DIRECTORY)TSODLULS_sorting_comparison_callback__competitor.o: $(HEADERS-COMPETITOR) ./competitor_algorithms/TSODLULS_sorting_comparison_callback__competitor.c ./competitor_algorithms/TSODLULS_sorting_comparison_callback__competitor__generated.c $(FUNCTIONS-BODIES-SORTING-COMPARISON-CALLBACK)
	$(CC) $(CFLAGS) -c ./competitor_algorithms/TSODLULS_sorting_comparison_callback__competitor.c -o $(OBJECTS-DIRECTORY)TSODLULS_sorting_comparison_callback__competitor.o

$(OBJECTS-DIRECTORY)TSODLULS_sorting_long_orders__competitor.o: $(HEADERS-COMPETITOR) ./competitor_algorithms/TSODLULS_sorting_long_orders__competitor.c ./competitor_algorithms/TSODLULS_sorting_long_orders__competitor__generated.c $(FUNCTIONS-BODIES-SORTING-LONG)
	$(CC) $(CFLAGS) -c ./competitor_algorithms/TSODLULS_sorting_long_orders__competitor.c -o $(OBJECTS-DIRECTORY)TSODLULS_sorting_long_orders__competitor.o

$(OBJECTS-DIRECTORY)TSODLULS_sorting_short_orders__competitor.o: $(HEADERS-COMPETITOR) ./competitor_algorithms/TSODLULS_sorting_short_orders__competitor.c ./competitor_algorithms/TSODLULS_sorting_short_orders__competitor__generated.c $(FUNCTIONS-BODIES-SORTING-SHORT)
	$(CC) $(CFLAGS) -c ./competitor_algorithms/TSODLULS_sorting_short_orders__competitor.c -o $(OBJECTS-DIRECTORY)TSODLULS_sorting_short_orders__competitor.o

$(OBJECTS-DIRECTORY)TSODLULS_comparison__competitor.o: $(HEADERS-COMPETITOR) ./competitor_algorithms/TSODLULS_comparison__competitor.c
	$(CC) $(CFLAGS) -c ./competitor_algorithms/TSODLULS_comparison__competitor.c -o $(OBJECTS-DIRECTORY)TSODLULS_comparison__competitor.o

$(OBJECTS-DIRECTORY)TSODLULS_misc__competitor.o: $(HEADERS-COMPETITOR) ./competitor_algorithms/TSODLULS_misc__competitor.c
	$(CC) $(CFLAGS) -c ./competitor_algorithms/TSODLULS_misc__competitor.c -o $(OBJECTS-DIRECTORY)TSODLULS_misc__competitor.o

$(OBJECTS-DIRECTORY)TSODLULS_padding__competitor.o: $(HEADERS-COMPETITOR) ./competitor_algorithms/TSODLULS_padding__competitor.c
	$(CC) $(CFLAGS) -c ./competitor_algorithms/TSODLULS_padding__competitor.c -o $(OBJECTS-DIRECTORY)TSODLULS_padding__competitor.o

#-----------------------------------------------------------
#Build tests
#-----------------------------------------------------------
build-tests: build-test1 build-test2


#Test 1
build-test1: ./tests_benchmarks/test1/test1.exe ./tests_benchmarks/test1/test1_dyn.exe

#static linking requires the library to come after the test object
./tests_benchmarks/test1/test1.exe: $(LIB-DIRECTORY)libTSODLULS_$(VERSION).a ./tests_benchmarks/test1/test1.o
	$(CC) -static -L$(LIB-DIRECTORY) ./tests_benchmarks/test1/test1.o -lTSODLULS_$(VERSION) -o ./tests_benchmarks/test1/test1.exe

./tests_benchmarks/test1/test1_dyn.exe: $(LIB-DIRECTORY)libTSODLULS_$(VERSION).so ./tests_benchmarks/test1/test1.o
	$(CC) -L$(LIB-DIRECTORY) -lTSODLULS_$(VERSION) ./tests_benchmarks/test1/test1.o -o ./tests_benchmarks/test1/test1_dyn.exe

./tests_benchmarks/test1/test1.o: $(HEADERS) ./tests_benchmarks/test_functions.c ./tests_benchmarks/test_macros.c ./tests_benchmarks/test1/test1.c
	$(CC) $(CFLAGS) -c ./tests_benchmarks/test1/test1.c -o ./tests_benchmarks/test1/test1.o


#Test 2
build-test2: ./tests_benchmarks/test2/test2.exe ./tests_benchmarks/test2/test2_dyn.exe

#static linking requires the library to come after the test object
./tests_benchmarks/test2/test2.exe: $(LIB-DIRECTORY)libTSODLULS_$(VERSION).a ./tests_benchmarks/test2/test2.o
	$(CC) -static -L$(LIB-DIRECTORY) ./tests_benchmarks/test2/test2.o -lTSODLULS_$(VERSION) -o ./tests_benchmarks/test2/test2.exe

./tests_benchmarks/test2/test2_dyn.exe: $(LIB-DIRECTORY)libTSODLULS_$(VERSION).so ./tests_benchmarks/test2/test2.o
	$(CC) -L$(LIB-DIRECTORY) -lTSODLULS_$(VERSION) ./tests_benchmarks/test2/test2.o -o ./tests_benchmarks/test2/test2_dyn.exe

./tests_benchmarks/test2/test2.o: $(HEADERS) ./tests_benchmarks/test_functions.c ./tests_benchmarks/test_macros.c ./tests_benchmarks/test2/test2.c
	$(CC) $(CFLAGS) -c ./tests_benchmarks/test2/test2.c -o ./tests_benchmarks/test2/test2.o



#-----------------------------------------------------------
#Install
#-----------------------------------------------------------
install: /usr/lib/libTSODLULS_$(VERSION).so

/usr/lib/libTSODLULS_$(VERSION).so: $(LIB-DIRECTORY)libTSODLULS_$(VERSION).so
	cp -p $(LIB-DIRECTORY)libTSODLULS_$(VERSION).so /usr/lib
	chmod 755 /usr/lib/libTSODLULS_$(VERSION).so



#-----------------------------------------------------------
#Run tests
#-----------------------------------------------------------
test: build-tests run-tests

run-tests: build-tests
	cd ./tests_benchmarks/test1/ && echo "\nTest1:" && ./test1.exe && cd ../..
	cd ./tests_benchmarks/test2/ && echo "\nTest2:" && ./test2.exe && cd ../..

run-tests-dynamic: build-tests install
	cd ./tests_benchmarks/test1/ && echo "\nTest1 dyn:" && ./test1_dyn.exe && cd ../..
	cd ./tests_benchmarks/test2/ && echo "\nTest2 dyn:" && ./test2_dyn.exe && cd ../..



#-----------------------------------------------------------
#Build benchmarks
#-----------------------------------------------------------
build-benchmarks: build-benchmark1


#Benchmark 1
build-benchmark1: ./tests_benchmarks/benchmark1/benchmark1.exe ./tests_benchmarks/benchmark1/benchmark1_dyn.exe

#static linking requires the library to come after the test object
./tests_benchmarks/benchmark1/benchmark1.exe: $(LIB-DIRECTORY)libTSODLULS_$(VERSION).a ./tests_benchmarks/benchmark1/benchmark1.o
	$(CC) -static -L$(LIB-DIRECTORY) ./tests_benchmarks/benchmark1/benchmark1.o -lTSODLULS_$(VERSION) -o ./tests_benchmarks/benchmark1/benchmark1.exe

./tests_benchmarks/benchmark1/benchmark1_dyn.exe: $(LIB-DIRECTORY)libTSODLULS_$(VERSION).so ./tests_benchmarks/benchmark1/benchmark1.o
	$(CC) -L$(LIB-DIRECTORY) -lTSODLULS_$(VERSION) ./tests_benchmarks/benchmark1/benchmark1.o -o ./tests_benchmarks/benchmark1/benchmark1_dyn.exe

./tests_benchmarks/benchmark1/benchmark1.o: $(HEADERS) ./tests_benchmarks/test_functions.c ./tests_benchmarks/test_macros.c ./tests_benchmarks/benchmark1/benchmark1.c
	$(CC) $(CFLAGS) -c ./tests_benchmarks/benchmark1/benchmark1.c -o ./tests_benchmarks/benchmark1/benchmark1.o



#-----------------------------------------------------------
#Run benchmarks
#-----------------------------------------------------------
benchmarks: build-benchmarks run-benchmarks

run-benchmarks: build-benchmarks
	cd ./tests_benchmarks/benchmark1/ && echo "\nBenchmark1:" && ./benchmark1.exe && cd ../..

run-benchmarks-dynamic: build-benchmarks install
	cd ./tests_benchmarks/benchmark1/ && echo "\nBenchmark1 dyn:" && ./benchmark1_dyn.exe && cd ../..



#-----------------------------------------------------------
#Custom tests and benchmarks
#You should not run these commands.
#The PHP files in the custom tests and benchmarks will call these commands in due time.
#-----------------------------------------------------------
#Test custom
build-test-custom: ./tests_benchmarks/test_custom/test_custom.exe

#static linking requires the library to come after the test object
./tests_benchmarks/test_custom/test_custom.exe: $(LIB-DIRECTORY)libTSODLULS_with_competitor_algorithms_$(VERSION).a ./tests_benchmarks/test_custom/test_custom.o
	$(CC) -static -L$(LIB-DIRECTORY) ./tests_benchmarks/test_custom/test_custom.o -lTSODLULS_with_competitor_algorithms_$(VERSION) -o ./tests_benchmarks/test_custom/test_custom.exe

./tests_benchmarks/test_custom/test_custom.o: $(HEADERS-COMPETITOR) ./tests_benchmarks/test_functions.c ./tests_benchmarks/test_macros.c ./tests_benchmarks/test_custom/test_custom.c
	$(CC) -O3 -c ./tests_benchmarks/test_custom/test_custom.c -o ./tests_benchmarks/test_custom/test_custom.o

#Test custom for strings
build-test-custom-strings: ./tests_benchmarks/test_custom_strings/test_custom_strings.exe

#static linking requires the library to come after the test object
./tests_benchmarks/test_custom_strings/test_custom_strings.exe: $(LIB-DIRECTORY)libTSODLULS_with_competitor_algorithms_$(VERSION).a ./tests_benchmarks/test_custom_strings/test_custom_strings.o
	$(CC) -static -L$(LIB-DIRECTORY) ./tests_benchmarks/test_custom_strings/test_custom_strings.o -lTSODLULS_with_competitor_algorithms_$(VERSION) -o ./tests_benchmarks/test_custom_strings/test_custom_strings.exe

./tests_benchmarks/test_custom_strings/test_custom_strings.o: $(HEADERS-COMPETITOR) ./tests_benchmarks/test_functions.c ./tests_benchmarks/test_macros.c ./tests_benchmarks/test_custom_strings/test_custom_strings.c
	$(CC) -O3 -c ./tests_benchmarks/test_custom_strings/test_custom_strings.c -o ./tests_benchmarks/test_custom_strings/test_custom_strings.o

#Benchmark custom
build-benchmark-custom: ./tests_benchmarks/benchmark_custom/benchmark_custom.exe

#static linking requires the library to come after the test object
./tests_benchmarks/benchmark_custom/benchmark_custom.exe: $(LIB-DIRECTORY)libTSODLULS_with_competitor_algorithms_$(VERSION).a ./tests_benchmarks/benchmark_custom/benchmark_custom.o
	$(CC) -static -L$(LIB-DIRECTORY) ./tests_benchmarks/benchmark_custom/benchmark_custom.o -lTSODLULS_with_competitor_algorithms_$(VERSION) -o ./tests_benchmarks/benchmark_custom/benchmark_custom.exe

./tests_benchmarks/benchmark_custom/benchmark_custom.o: $(HEADERS-COMPETITOR) ./tests_benchmarks/test_functions.c ./tests_benchmarks/test_macros.c ./tests_benchmarks/benchmark_custom/benchmark_custom.c
	$(CC) -O3 -c ./tests_benchmarks/benchmark_custom/benchmark_custom.c -o ./tests_benchmarks/benchmark_custom/benchmark_custom.o

#Benchmark custom for strings
build-benchmark-custom-strings: ./tests_benchmarks/benchmark_custom_strings/benchmark_custom_strings.exe

#static linking requires the library to come after the test object
./tests_benchmarks/benchmark_custom_strings/benchmark_custom_strings.exe: $(LIB-DIRECTORY)libTSODLULS_with_competitor_algorithms_$(VERSION).a ./tests_benchmarks/benchmark_custom_strings/benchmark_custom_strings.o
	$(CC) -static -L$(LIB-DIRECTORY) ./tests_benchmarks/benchmark_custom_strings/benchmark_custom_strings.o -lTSODLULS_with_competitor_algorithms_$(VERSION) -o ./tests_benchmarks/benchmark_custom_strings/benchmark_custom_strings.exe

./tests_benchmarks/benchmark_custom_strings/benchmark_custom_strings.o: $(HEADERS-COMPETITOR) ./tests_benchmarks/test_functions.c ./tests_benchmarks/test_macros.c ./tests_benchmarks/benchmark_custom_strings/benchmark_custom_strings.c
	$(CC) -O3 -c ./tests_benchmarks/benchmark_custom_strings/benchmark_custom_strings.c -o ./tests_benchmarks/benchmark_custom_strings/benchmark_custom_strings.o



#-----------------------------------------------------------
#Clean
#-----------------------------------------------------------
clean:
	rm -f $(OBJECTS-DIRECTORY)*
	rm -f ./tests_benchmarks/test1/*.o ./tests_benchmarks/test1/*.exe ./tests_benchmarks/test1/*.test_result
	rm -f ./tests_benchmarks/test2/*.o ./tests_benchmarks/test2/*.exe ./tests_benchmarks/test2/*.test_result
	rm -f ./tests_benchmarks/test_custom/*.o ./tests_benchmarks/test_custom/*.exe ./tests_benchmarks/test_custom/*.test_result ./tests_benchmarks/test_custom/*.c
	rm -f ./tests_benchmarks/test_custom_strings/*.o ./tests_benchmarks/test_custom_strings/*.exe ./tests_benchmarks/test_custom_strings/*.test_result ./tests_benchmarks/test_custom_strings/*.c
	rm -f ./tests_benchmarks/benchmark1/*.o ./tests_benchmarks/benchmark1/*.exe ./tests_benchmarks/benchmark1/*.test_result
	rm -f ./tests_benchmarks/benchmark_custom/*.o ./tests_benchmarks/benchmark_custom/*.exe ./tests_benchmarks/benchmark_custom/*.test_result ./tests_benchmarks/benchmark_custom/*.c
	rm -f ./tests_benchmarks/benchmark_custom_strings/*.o ./tests_benchmarks/benchmark_custom_strings/*.exe ./tests_benchmarks/benchmark_custom_strings/*.test_result ./tests_benchmarks/benchmark_custom_strings/*.c



