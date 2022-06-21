
CC = gcc

demo. :  demo.c
	$(CC) -o demo demo.c -I /usr/local/include/hiredis -L /usr/local/lib -lhiredis
 
clean:
	rm -f  demo