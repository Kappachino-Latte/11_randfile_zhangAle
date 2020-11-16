all: main.o
	gcc -o randomfile main.o
	
main.o: main.c
	gcc -c main.c
	
run:
	./randomfile
	
clear:
	rm *.o
