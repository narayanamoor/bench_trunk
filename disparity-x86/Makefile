#Makefile written by Amin
HOME = /research/jalal
CC = gcc
LIBS = -lpthread

COMMON_DIR=common
INPUT=fullhd
INCLUDES= -I$(COMMON_DIR)

CHECK=CHECK #change CHECK to something else for not checking the output
GEN_OUT=NO_GENERATE_OUTPUT #change GENERATE_OUTPUT to something else for not generating the output. This overwrites the expected_C.txt in data directory, so be careful not ruin your expected data.
#put -O2 later in CFLAGS @mona
CFLAGS=-ggdb3 -DGCC -D$(CHECK) -D$(GEN_OUT) -D$(INPUT) -lm -O0 $(INCLUDES) -static 
GFLAGS=-DGCC -D$(CHECK) -D$(GEN_OUT) -D$(INPUT) -lm -O0 -g $(INCLUDES) -static 

COMMON_SRC=$(wildcard $(COMMON_DIR)/*.c) $(wildcard $(COMMON_DIR)/*.h)
COMMON_SRC_C=$(wildcard $(COMMON_DIR)/*.c)
SRC=$(wildcard *.c)

all: disparity

disparity: 
	$(CC) -pg $(SRC) $(COMMON_SRC_C) --coverage -fprofile-arcs -ftest-coverage  -lgcov -o $@ $^ $(CFLAGS) $(LIBS)

#mser-debug: $(SRC) $(COMMON_SRC)
#       $(CC) -o $@ $^ $(GFLAGS) $(LIBS)

clean: 
	rm -rf *.o *.gcda *.gcno *.gcov; rm -f disparity; rm -f disparity-debug

