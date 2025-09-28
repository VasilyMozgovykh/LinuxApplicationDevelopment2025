GENERATES = prog prog-a prog-so liboutput_static.a liboutput.so
TESTS = test_*_param*
TRASH = *.o *~ o.*
CC = cc
FLAGS = -Wall -O3

All: prog prog-a prog-so

prog: prog.o const.o fun.o
	$(CC) $(FLAGS) $^ -o $@

prog-a: prog.o liboutput_static.a
	$(CC) $(FLAGS) -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
	$(CC) $(FLAGS) $^ -o $@

liboutput_static.a: const.o fun.o
	ar -rcs $@ $^

liboutput.so: const.o fun.o
	$(CC) $(FLAGS) -shared $^ -o $@

%.o: %.c
	$(CC) $(FLAGS) -fPIC $< -c -o $@

clean:
	rm -f $(TRASH) $(GENERATES) $(TESTS)

test: prog prog-a prog-so
	echo "Executing prog"
	./prog > test_0_params_prog 2>&1
	./prog arg1 > test_1_param_prog 2>&1
	./prog arg1 arg 2 arg3 > test_3_params_prog 2>&1
	echo "Executing prog-a"
	./prog-a > test_0_params_prog-a 2>&1
	./prog-a arg1 > test_1_param_prog-a 2>&1
	./prog-a arg1 arg 2 arg3 > test_3_params_prog-a 2>&1
	echo "Executing prog-so"
	LD_LIBRARY_PATH=`pwd` ./prog-so > test_0_params_prog-so 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so arg1 > test_1_param_prog-so 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so arg1 arg 2 arg3 > test_3_params_prog-so 2>&1
	echo "Comparing prog* outputs"
	cmp test_0_params_prog test_0_params_prog-a &&\
	cmp test_0_params_prog-a test_0_params_prog-so &&\
	cmp test_0_params_prog-so test_0_params_prog &&\
	cmp test_1_param_prog test_1_param_prog-a &&\
	cmp test_1_param_prog-a test_1_param_prog-so &&\
	cmp test_1_param_prog-so test_1_param_prog &&\
	cmp test_3_params_prog test_3_params_prog-a &&\
	cmp test_3_params_prog-a test_3_params_prog-so &&\
	cmp test_3_params_prog-so test_3_params_prog
