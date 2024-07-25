program: main.o route-records.o route-records.h
	gcc -Wall -g main.o route-records.o -o program

main.o: main.c
	gcc -Wall -c main.c -o main.o

route-records.o: route-records.c
	gcc -Wall -c route-records.c -o route-records.o

clean:
	rm *.o *.exe