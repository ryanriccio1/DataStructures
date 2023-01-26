
all: src/driver.c bin/obj/linked_list.o bin/obj/node.o bin/obj/console_util.o
	gcc -Wall -Wextra -pedantic -std=c17 -O3 -I"include" \
	bin/obj/linked_list.o bin/obj/node.o bin/obj/console_util.o \
	-g src/driver.c -o bin/test.exe

bin/obj/linked_list.o: src/linked_list.c
	mkdir -p bin/obj
	gcc -Wall -Wextra -pedantic -std=c17 -O3 -I"include" -g -c src/linked_list.c -o bin/obj/linked_list.o

bin/obj/node.o: src/node.c
	mkdir -p bin/obj
	gcc -Wall -Wextra -pedantic -std=c17 -O3 -I"include" -g -c src/node.c -o bin/obj/node.o

bin/obj/console_util.o: src/console_util.c
	mkdir -p bin/obj
	gcc -Wall -Wextra -pedantic -std=c17 -O3 -I"include" -g -c src/console_util.c -o bin/obj/console_util.o

.PHONY: tests
tests: bin/gtest bin/obj/console_util.o test/console_util_test.cpp bin/obj/linked_list.o bin/obj/node.o test/linked_list_test.cpp
	g++ -Wall -Wextra -std=c++17 -pthread -g \
    -I"test/googletest/googletest/include" -I"test/googletest/googlemock/include" \
	-I"include" \
	bin/obj/console_util.o test/console_util_test.cpp \
	bin/obj/node.o bin/obj/linked_list.o test/linked_list_test.cpp \
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
