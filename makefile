LDIR=./lib
11:
	gcc main1.c -o 1 -Llib -linfodef -lrandombytes -lm
12:
	gcc main2.c -o 2 -Llib -linfodef -lrandombytes -lm
13:
	gcc main3.c -o 3 -Llib -linfodef -lrandombytes -lm 
14:
	gcc main4.c -o 4 -Llib -linfodef -lrandombytes -lm

bib:
	gcc -c 1.c 2.c 3.c 4.c
	ar -rc $(LDIR)/libinfodef.a 1.o 2.o 3.o 4.o
	rm 1.o 2.o 3.o 4.o
