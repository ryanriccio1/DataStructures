
all: src/Driver.c bin/obj/LinkedList.o bin/obj/Node.o bin/obj/Stack.o bin/obj/Queue.o bin/obj/ConsoleUtil.o
	gcc -Wall -Wextra -pedantic -std=c17 -O3 -I"include" \
	bin/obj/LinkedList.o bin/obj/Node.o \
	bin/obj/Stack.o bin/obj/Queue.o \
	bin/obj/ConsoleUtil.o \
	-g src/Driver.c -o bin/test.exe

bin/obj/LinkedList.o: src/LinkedList.c
	mkdir -p bin/obj
	gcc -Wall -Wextra -pedantic -std=c17 -O3 -I"include" -g -c src/LinkedList.c -o bin/obj/LinkedList.o

bin/obj/Node.o: src/Node.c
	mkdir -p bin/obj
	gcc -Wall -Wextra -pedantic -std=c17 -O3 -I"include" -g -c src/Node.c -o bin/obj/Node.o

bin/obj/Stack.o: src/Stack.c
	mkdir -p bin/obj
	gcc -Wall -Wextra -pedantic -std=c17 -O3 -I"include" -g -c src/Stack.c -o bin/obj/Stack.o
	
bin/obj/Queue.o: src/Queue.c
	mkdir -p bin/obj
	gcc -Wall -Wextra -pedantic -std=c17 -O3 -I"include" -g -c src/Queue.c -o bin/obj/Queue.o

bin/obj/ConsoleUtil.o: src/ConsoleUtil.c
	mkdir -p bin/obj
	gcc -Wall -Wextra -pedantic -std=c17 -O3 -I"include" -g -c src/ConsoleUtil.c -o bin/obj/ConsoleUtil.o

.PHONY: tests
tests: bin/gtest bin/obj/ConsoleUtil.o test/ConsoleUtilTest.cpp bin/obj/LinkedList.o bin/obj/Node.o bin/obj/Stack.o bin/obj/Queue.o test/LinkedListTest.cpp test/StackTest.cpp
	g++ -Wall -Wextra -std=c++17 -pthread -g \
    -I"test/googletest/googletest/include" -I"test/googletest/googlemock/include" \
	-I"include" \
	bin/obj/ConsoleUtil.o test/ConsoleUtilTest.cpp \
	bin/obj/Node.o bin/obj/LinkedList.o test/LinkedListTest.cpp \
	bin/obj/Stack.o test/StackTest.cpp \
	bin/obj/Queue.o test/QueueTest.cpp \
    bin/gtest/libgtest.a bin/gtest/libgtest_main.a \
    -o bin/run_tests.exe

test/googletest:
	git clone https://github.com/google/googletest.git test/googletest

bin/gtest: test/googletest
	g++ -Wall -Wextra -Werror -O3 -std=c++17 -pthread -c \
		-I"test/googletest/googletest/include" -I"test/googletest/googletest" \
		-I"test/googletest/googlemock/include" -I"test/googletest/googlemock" \
		test/googletest/googletest/src/gtest-all.cc \
		test/googletest/googletest/src/gtest_main.cc \
		test/googletest/googlemock/src/gmock-all.cc \
		test/googletest/googlemock/src/gmock_main.cc

	mkdir -p bin/gtest

	mv -t bin/gtest gtest-all.o gtest_main.o gmock-all.o gmock_main.o
	
	ar -rv bin/gtest/libgtest.a bin/gtest/gtest-all.o
	ar -rv bin/gtest/libgtest_main.a bin/gtest/gtest_main.o
	ar -rv bin/gtest/libgmock.a bin/gtest/gmock-all.o
	ar -rv bin/gtest/libgmock_main.a bin/gtest/gmock_main.o

.PHONY: clean
clean: clean-exe clean-obj
.PHONY: clean-all
clean-all: clean-exe clean-obj clean-gtest
.PHONY: clean-exe
clean-exe:
	rm -rf bin/*.exe

.PHONY: clean-obj
clean-obj:
	rm -rf bin/obj

.PHONY: clean-gtest
clean-gtest:
	rm -rf test/googletest
	rm -rf bin/gtest
