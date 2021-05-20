#
# Makefile
# Practica4
#
# Created by Beatriz Paulina Garcia Salgado
#

CC = gcc
CPPFLAGS = -Wall -fopenmp

Practica4: Main.o ParallelMatrix.o
	$(CC) $(CPPFLAGS) -o $@ $^

%o:%.c
	$(CC) $(CPPFLAGS) -c $<

clean:
	rm *.o
	rm Practica4
