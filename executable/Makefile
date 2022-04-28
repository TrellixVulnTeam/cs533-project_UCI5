CFLAGS=-g -Wall -O0 -std=c99
.PHONY: all rsa victim

all: rsa victim

rsa: rsa.o
	gcc -shared -fPIC -o librsa.so $^

rsa.o: rsa.c rsa.h
	gcc $(CFLAGS) -fPIC rsa.c -c -o $@

victim: victim.c
	gcc $(CFLAGS) victim.c  -o victim -L. -lrsa

clean:
	rm -f *.o victim attacker librsa.so