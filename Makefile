#Makefile for OS ex2q1
CFLAGS   = -Wall
LDFLAGS  = -lm  # not really needed for this exercise
ECHO     = echo "going to compile for target $@"
PROG1 = ex2_q1
PROG2 = ex2_q1_helper
PROGS = $(PROG1) $(PROG2)

all: $(PROGS) test
	
ex2_q1: ex2_q1.o ex2_q1_helper.o
	gcc -o ex2_q1 -Wall ex2_q1.c ex2_q1_given.c -lm

ex2_q1.o: ex2_q1.c
	gcc -Wall -c ex2_q1.c

ex2_q1_helper: ex2_q1_helper.o
	gcc -o ex2_q1_helper -Wall ex2_q1_helper.c ex2_q1_given.c -lm

ex2_q1_helper.o: ex2_q1_helper.c
	gcc -Wall -c ex2_q1_helper.c
	
clean:
	rm -vf *.o ${PROGS}  *.tmp  

test: $(PROGS)
	@echo going to run test...
	./$(PROG1) < in.txt 

