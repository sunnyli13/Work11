main: work11.o
	gcc -o work11 work11.c

work11.o: work11.c
	gcc -c work11.c

clean: 
	rm *.o

run: 
	./work11