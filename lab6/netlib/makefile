INCL = -I../include
FLAGS = -c -O3 
EXTRA = 
cc = gcc

all :	netlib.o wall_clock.o archive ranl move

wall_clock.o : wall_clock.c
	$(cc) $(INCL) $(FLAGS) wall_clock.c $(TAIL)
netlib.o : netlib.c $(TAIL)
	$(cc) $(INCL) $(FLAGS)  netlib.c $(TAIL)
archive : 
	ar rcv libb.a *.o
ranl:
move :
	mv libb.a ../obj/libsng.a
	/bin/rm -f *.o
