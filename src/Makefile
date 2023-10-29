CC=gcc
CXX=g++

SRC_BACK_DIR = back
TEST_DIR = gtest
GTEST_DIR = /home/georgy/googletest/googletest/googletest/googletest
GTEST_DIR_SRC = $(GTEST_DIR)/src

SRC_BACK := $(shell find ${SRC_BACK_DIR} -name "*.c" | sed -e 's/\.\///')
SRC_TEST := $(shell find ${TEST_DIR} -name "*.cpp" | sed -e 's/\.\///')

BUILD_DIR = obj
BUILD_TEST_DIR = obj_tests

OBJS_BACK := $(SRC_BACK:%.c=${BUILD_DIR}/%.o)
OBJS_TEST := $(SRC_TEST:%.cpp=%.o)

CFLAGS=-Wall -Wextra -Werror -std=c11
CXXFLAGS+=-g -Wall -Wextra -pthread
LDFLAGS=$(shell pkg-config --cflags --libs check)
GCOVFLAGS=-fprofile-arcs -ftest-coverage
CPPFLAGS+=-isystem $(GTEST_DIR)/include

GTEST_HEADERS=$(GTEST_DIR)/include/gtest/*.h \
	      $(GTEST_DIR)/include/gtest/internal/*.h

GTEST_SRCS_ = $(GTEST_DIR_SRC)/*.cc $(GTEST_DIR_SRC)/*.h $(GTEST_HEADERS)

all: calc.a test

calc.a: $(OBJS_BACK)
	@mkdir -p ${BUILD_DIR}
	ar rc calc.a $(OBJS_BACK)
	ranlib calc.a

${BUILD_DIR}/%.o: %.c
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} -c $< -o $@

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR_SRC)/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR_SRC)/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

$(BUILD_TEST_DIR)/%.o:	$(TEST_DIR)/%.cpp $(GTEST_HEADERS)
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

test:	$(OBJS_TEST)  gtest_main.a calc.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@.out
	./test.out

run: entry.c calc.a
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o run.out
	./run.out


codestyle:
	clang-format -i --style=google $(SRC_BACK_DIR)/*.c $(TEST_DIR)/*.cpp
	clang-format -i --style=google $(SRC_BACK_DIR)/*.h
	clang-format -i --style=google entry.c

clean: 
	rm -f *.gcda *.gcov *.o *.gcno
	rm -f *.a
	rm -rf $(BUILD_DIR) $(BUILD_TEST_DIR)
	rm -rf gcov_report gcov_main
	rm -rf *.out *.info ../*.tgz
	rm -rf html latex
	rm -f $(TEST_DIR)/*.o
