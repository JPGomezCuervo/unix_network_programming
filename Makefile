CC = gcc
CFLAGS = -Wall -ggdb -I./include
LIBS = ./lib/err.c 
LIBS2 = ./lib/socket.c 

daytimetcpcli: ./chap_1/intro/daytimetcpcli.c
	$(CC) $(CFLAGS) -o ./chap_1/intro/daytimetcpcli.out $< $(LIBS)

daytimetcpsrv: ./chap_1/intro/daytimetcpsrv.c
	$(CC) $(CFLAGS) -o ./chap_1/intro/daytimetcpsrv.out $< $(LIBS) $(LIBS2)

clean:
	rm -f ./chap_1/intro/*.out *.o
