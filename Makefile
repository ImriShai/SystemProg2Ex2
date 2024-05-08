#!make -f

CXX=clang++
CXXFLAGS=-std=c++14 -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

DEMOSOURCES=Graph.cpp Algorithms.cpp 
TESTSOURCES=Graph.cpp Algorithms.cpp TestCounter.cpp Test.cpp
DEMOOBJECTS=$(subst .cpp,.o,$(DEMOSOURCES))
TESTOBJECTS=$(subst .cpp,.o,$(TESTSOURCES))
.PHONY: all run demo test tidy valgrind clean
all: demo test
run: test
	./$^

demo: Demo.o $(DEMOOBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo

test: TestCounter.o Test.o $(TESTOBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test

tidy:
	clang-tidy $(DEMOSOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test Demo
