CC = gcc
CFLAGS = -Wall -ggdb -I./include
LIB = ./include/unp.h
LIBS = ./lib/err.c ./lib/socket.c ./lib/sock_ntop.c ./lib/libwrap.c  

daytimetcpcli: ./chap_1/intro/daytimetcpcli.c
	$(CC) $(CFLAGS) -o ./chap_1/intro/daytimetcpcli.out $< $(LIBS)

daytimetcpsrv: ./chap_1/intro/daytimetcpsrv.c
	$(CC) $(CFLAGS) -o ./chap_1/intro/daytimetcpsrv.out $<  $(LIBS) 

clean:
	rm -f ./chap_1/intro/*.out *.o
