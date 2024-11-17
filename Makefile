CC = gcc
CFLAGS = -Wall -ggdb -I./include
LIB = ./include/unp.h
LIBS = ./lib/err.c ./lib/socket.c ./lib/sock_ntop.c ./lib/libwrap.c ./lib/writen.c ./lib/readline.c

daytimetcpcli: ./chap_1/intro/daytimetcpcli.c
	$(CC) $(CFLAGS) -o ./chap_1/intro/daytimetcpcli.out $< $(LIBS)

daytimetcpsrv: ./chap_1/intro/daytimetcpsrv.c
	$(CC) $(CFLAGS) -o ./chap_1/intro/daytimetcpsrv.out $<  $(LIBS) 

tcpsrv01: ./chap_5/tcpsrv01.c ./chap_5/str_echo.c
	$(CC) $(CFLAGS) -o ./chap_5/tcpsrv01.out $^  $(LIBS)

tcpcli01: ./chap_5/tcpcli01.c ./chap_5/str_cli.c
	$(CC) $(CFLAGS) -o ./chap_5/tcpcli01.out $^  $(LIBS)

clean:
	rm -f ./chap_1/intro/*.out ./chap_5/*.out *.o
