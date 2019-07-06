CC=gcc
LIBS=-lm

ccalc: ccalc.c
	$(CC) -g ccalc.c -o ccalc $(LIBS)
