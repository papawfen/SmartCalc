CC=g++
CFLAGS= -Wall -Werror -Wextra
COV_FLAGS= -fprofile-arcs -ftest-coverage
ifeq ($(OS), Linux)
	OPEN = xdg-open
	LIBS= -lgtest -lpthread -pthread -lrt -lm -lsubunit
	LEAKS= valgrind --track-origins=yes --leak-check=full  ./test
else
	OPEN = open
	LIBS=-lgtest -lgtest_main -pthread
	LEAKS=leaks --atExit -- ./test
endif


all: clean cpplint test gcov_report  

clean:
	@find . -type f -name "*.a" -delete
	@find . -type f -name "*.o" -delete
	@find . -type f -name "*.out" -delete
	@rm -rf test *.gcda *.gcno gcov_report *.css
	@rm -rf report.functions.html report.html report.s21_smartcalc.c*

test:
	@echo 'test'
	$(CC) $(CFLAGS) smartcalc.cc smartcalc_tests.cc tokens.cc -o test $(LIBS)
	./test

install:
	@make -C build
	@cp -rf build/smartcalc.app ../../../Desktop

dist: clean uninstall
	@rm -rf smartcalc.tar
	@tar -cvf smartcalc.tar *
	
dvi:
	echo "Calculator made by papawfen"
	@open instruction.html

uninstall:
	@rm -rf build/*.o build/*.c build/*.cpp build/*.app build/*.h ../../../Desktop/smartcalc.app

leaks:
	@$(LEAKS)

cpplint:
	cp ../../materials/linters/.clang-format . 
	clang-format -i  *.cc *.h
	clang-format -n *.cc *.h
	rm -rf .clang-format

cppcheck:
	@cppcheck --language=c++ --enable=all --suppress=missingIncludeSystem *.cc *.h


.PHONY: clean linter test gcov_report
