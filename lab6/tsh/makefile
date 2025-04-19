SYS_LINK=-L/usr/lib
INCS = -I../include
OBJS = ../obj 
FLAGS = -g 
cc = gcc

all : tshlib.o tsh tshtest launch

tsh : tsh.c 
	$(cc) $(EXTRA) $(INCS) $(FLAGS) -o tsh tsh.c -L$(OBJS) -lsng

tshtest : tshtest.c 
	$(cc) $(EXTRA) $(INCS) $(FLAGS) -o tshtest tshtest.c -L$(OBJS) -lsng
	
launch : launch.c 
	$(cc) $(EXTRA) $(INCS) $(FLAGS) -o launch launch.c -L$(OBJS) -lsng
	
tshlib.o: tshlib.c
	$(cc) $(INCS) $(FLAGS) -c tshlib.c -o tshlib.o