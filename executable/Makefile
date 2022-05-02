CFLAGS=-g -Wall -O0 -std=gnu11 -I.
LDFLAGS=-L. -lrsa
.PHONY: all rsa victim attacker

all: rsa victim attacker

rsa: rsa.o
	gcc -shared -fPIC -o librsa.so $^

rsa.o: rsa.c rsa.h
	gcc $(CFLAGS) -fPIC rsa.c -c -o $@

victim: rsa victim.c
	gcc $(CFLAGS) victim.c  -o victim $(LDFLAGS)

attacker: rsa attacker.c 
	gcc $(CFLAGS) attacker.c -o attacker $(LDFLAGS)

clean:
	rm -f *.o victim attacker librsa.so