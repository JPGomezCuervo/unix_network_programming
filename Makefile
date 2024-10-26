CC = gcc
CFLAGS = -Wall -ggdb
LIBS = ./lib/err.c ./include/err.h ./include/unp.h

daytimetcpcli: ./chap_1/intro/daytimetcpcli.c
	$(CC) $(CFLAGS) -o ./chap_1/intro/a.out $< $(LIBS)

clean:
	rm -f ./chap_1/intro/a.out *.o
