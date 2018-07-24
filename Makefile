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
#©Copyright 2018 Laurent Lyaudet

CC=gcc
CFLAGS=-Wall -O
VERSION=0_1_0

.PHONY: run-tests run-tests-dynamic clean run-benchmarks run-benchmarks-dynamic


#-----------------------------------------------------------
#Build library
#-----------------------------------------------------------
build: build-static build-dynamic


#Static library
build-static: ./bin/libTSODLULS_$(VERSION).a

./bin/libTSODLULS_$(VERSION).a: ./bin/TSODLULS_finite_orders.o
	ar -rcs ./bin/libTSODLULS_$(VERSION).a ./bin/TSODLULS_finite_orders.o
#	ar -rc ./bin/libTSODLULS_$(VERSION).a ./bin/TSODLULS_finite_orders.o
#	ranlib ./bin/libTSODLULS_$(VERSION).a

./bin/TSODLULS_finite_orders.o: ./TSODLULS.h ./TSODLULS_finite_orders.c
	$(CC) $(CFLAGS) -c ./TSODLULS_finite_orders.c -o ./bin/TSODLULS_finite_orders.o


#Dynamic library
build-dynamic: ./bin/libTSODLULS_$(VERSION).so

./bin/libTSODLULS_$(VERSION).so: ./bin/TSODLULS_finite_orders_dyn.o
	$(CC) -shared -o ./bin/libTSODLULS_$(VERSION).so ./bin/TSODLULS_finite_orders_dyn.o

./bin/TSODLULS_finite_orders_dyn.o: ./TSODLULS.h ./TSODLULS_finite_orders.c
	$(CC) $(CFLAGS) -fPIC -c ./TSODLULS_finite_orders.c -o ./bin/TSODLULS_finite_orders_dyn.o



#-----------------------------------------------------------
#Build tests
#-----------------------------------------------------------
build-tests: build-test1


#Test 1
build-test1: ./tests_benchmarks/test1/test1.exe ./tests_benchmarks/test1/test1_dyn.exe

#static linking requires the library to come after the test object
./tests_benchmarks/test1/test1.exe: ./bin/libTSODLULS_$(VERSION).a ./tests_benchmarks/test1/test1.o
	$(CC) -static -L./bin/ ./tests_benchmarks/test1/test1.o -lTSODLULS_$(VERSION) -o ./tests_benchmarks/test1/test1.exe

./tests_benchmarks/test1/test1_dyn.exe: ./bin/libTSODLULS_$(VERSION).so ./tests_benchmarks/test1/test1.o
	$(CC) -L./bin/ -lTSODLULS_$(VERSION) ./tests_benchmarks/test1/test1.o -o ./tests_benchmarks/test1/test1_dyn.exe

./tests_benchmarks/test1/test1.o: ./TSODLULS.h ./tests_benchmarks/test_functions.c ./tests_benchmarks/test1/test1.c
	$(CC) $(CFLAGS) -c ./tests_benchmarks/test1/test1.c -o ./tests_benchmarks/test1/test1.o



#-----------------------------------------------------------
#Install
#-----------------------------------------------------------
install: /usr/lib/libTSODLULS_$(VERSION).so

/usr/lib/libTSODLULS_$(VERSION).so: ./bin/libTSODLULS_$(VERSION).so
	cp -p ./bin/libTSODLULS_$(VERSION).so /usr/lib
	chmod 755 /usr/lib/libTSODLULS_$(VERSION).so



#-----------------------------------------------------------
#Run tests
#-----------------------------------------------------------
test: build-tests run-tests

run-tests:
	cd ./tests_benchmarks/test1/ && echo "\nTest1:" && ./test1.exe && cd ../..

run-tests-dynamic: install
	cd ./tests_benchmarks/test1/ && echo "\nTest1 dyn:" && ./test1_dyn.exe && cd ../..



#-----------------------------------------------------------
#Build benchmarks
#-----------------------------------------------------------
build-benchmarks: build-benchmark1


#Benchmark 1
build-benchmark1: ./tests_benchmarks/benchmark1/benchmark1.exe ./tests_benchmarks/benchmark1/benchmark1_dyn.exe

#static linking requires the library to come after the test object
./tests_benchmarks/benchmark1/benchmark1.exe: ./bin/libTSODLULS_$(VERSION).a ./tests_benchmarks/benchmark1/benchmark1.o
	$(CC) -static -L./bin/ ./tests_benchmarks/benchmark1/benchmark1.o -lTSODLULS_$(VERSION) -o ./tests_benchmarks/benchmark1/benchmark1.exe

./tests_benchmarks/benchmark1/benchmark1_dyn.exe: ./bin/libTSODLULS_$(VERSION).so ./tests_benchmarks/benchmark1/benchmark1.o
	$(CC) -L./bin/ -lTSODLULS_$(VERSION) ./tests_benchmarks/benchmark1/benchmark1.o -o ./tests_benchmarks/benchmark1/benchmark1_dyn.exe

./tests_benchmarks/benchmark1/benchmark1.o: ./TSODLULS.h ./tests_benchmarks/test_functions.c ./tests_benchmarks/benchmark1/benchmark1.c
	$(CC) $(CFLAGS) -c ./tests_benchmarks/benchmark1/benchmark1.c -o ./tests_benchmarks/benchmark1/benchmark1.o



#-----------------------------------------------------------
#Run benchmarks
#-----------------------------------------------------------
benchmarks: build-benchmarks run-benchmarks

run-benchmarks:
	cd ./tests_benchmarks/benchmark1/ && echo "\nBenchmark1:" && ./benchmark1.exe && cd ../..

run-benchmarks-dynamic: install
	cd ./tests_benchmarks/benchmark1/ && echo "\nBenchmark1 dyn:" && ./benchmark1_dyn.exe && cd ../..



#-----------------------------------------------------------
#Clean
#-----------------------------------------------------------
clean:
	rm -f ./bin/*
	rm -f ./tests_benchmarks/test1/*.o ./tests_benchmarks/test1/*.exe ./tests_benchmarks/test1/*.test_result
	rm -f ./tests_benchmarks/benchmark1/*.o ./tests_benchmarks/benchmark1/*.exe ./tests_benchmarks/benchmark1/*.test_result
