all: lab1

lab1: btree.o
	gcc btree.c -o lab1

btree.o: btree.c
	gcc -c btree.c

clean:
	rm -rf *.o lab1
