CC=gcc
CXX=g++

SRC_BACK_DIR = back
TEST_DIR = gtest
GTEST_DIR = /home/googletest/googletest/googletest
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

# QT_PROJECT_NAME = front
# QT_PROJECT_FOLDER = ./$(QT_PROJECT_NAME)
# QT_PRO = $(QT_PROJECT_NAME).pro
# QT_MAKEFILE = $(QT_PROJECT_NAME)_Makefile
# QT_BUILD_FOLDER = build
# QT_APP_FOLDER = ../App
# DIST_FOLDER_NAME = SmartCalc-1.0

all: calc.a test run

# install: generate_make
# 	@echo "Building application..."
# 	@cd ./$(QT_BUILD_FOLDER) && make -sf $(QT_MAKEFILE)
# 	@echo "Application builded."
# 	@echo -n "Moving application to folder \"$(QT_APP_FOLDER)\"..."
# 	@mkdir ./$(QT_APP_FOLDER)
# ifeq ($(OS), Darwin)
# 	@mv ./$(QT_BUILD_FOLDER)/$(QT_PROJECT_NAME).app/Contents/MacOS/SmartCalc ./$(QT_APP_FOLDER)/Smart_Calc.app
# else
# 	@mv ./$(QT_BUILD_FOLDER)/$(QT_PROJECT_NAME) ./$(QT_APP_FOLDER)/Smart_Calc
# endif
# 	@echo " Done."
# 	@echo -n "Deleting build folder..."
# 	@rm -rf $(QT_BUILD_FOLDER)
# 	@echo " Done."
# 	@echo "Installation complete!"

# generate_make:
# 	@qmake $(QT_PROJECT_FOLDER)/$(QT_PRO) -o ./$(QT_BUILD_FOLDER)/$(QT_MAKEFILE)
# 	@rm -rf .qmake.stash

# uninstall:
# 	@echo -n "Uninstalling application..."
# 	@rm -rf $(QT_APP_FOLDER)
# 	@echo " Done"

# TAR_DIR = SmartCalc_v1.0_v1.0_Archive

# dist:
# 	rm -Rf $(TAR_DIR)
# 	mkdir $(TAR_DIR)
# 	mkdir $(TAR_DIR)/src
# 	cp $(SRC_BACK_DIR)/* $(SRC_FRONT_DIR)/* $(TAR_DIR)/src
# 	tar cvzf $(TAR_DIR).tgz $(TAR_DIR)
# 	mv $(TAR_DIR).tgz ..
# 	rm -Rf $(TAR_DIR)

# dvi:
# 	doxygen Doxyfile
# ifeq ($(shell uname), Linux) 
# 	@firefox html/index.html
# else
# 	@open html/index.html
# endif


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


#test: $(OBJS_TEST) calc.a
#	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o test.out
#	./test.out
#
#${BUILD_TEST_DIR}/%.o: %.c
#	@mkdir -p $(dir $@)
#	$(CC) $(LDFLAGS) -c $< -o $@

run: entry.c calc.a
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o run.out
	./run.out


gcov_report:
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(SRC_BACK) $(TEST_DIR)/*.cpp $(LDFLAGS) -o gcov_main
	./gcov_main
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report
	rm -Rf *.gcda *.cov *.gcno *.info
ifeq ($(shell uname), Linux) 
	@firefox gcov_report/index.html
else
	@open gcov_report/index.html
endif


codestyle:
	clang-format -i --style=google $(SRC_BACK_DIR)/*.c $(TEST_DIR)/*.c
	clang-format -i --style=google $(SRC_BACK_DIR)/*.h $(TEST_DIR)/*.h
	clang-format -i --style=google $(SRC_FRONT_DIR)/*.h $(SRC_FRONT_DIR)/*.h


clean: 
	rm -f *.gcda *.gcov *.o *.gcno
	rm -f *.a
	rm -rf $(BUILD_DIR) $(BUILD_TEST_DIR)
	rm -rf gcov_report gcov_main
	rm -rf *.out *.info ../*.tgz
	rm -rf html latex
	rm -f $(TEST_DIR)/*.o
