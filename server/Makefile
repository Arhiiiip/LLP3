main: main.o node.o file.o
	gcc main.o node.o file.o -o main -ljson-c -ljsonschema-c -L/usr/local/lib

main.o: main.c user.h
	gcc main.c -c -ljson-c -ljsonschema-c -L/usr/local/lib

node.o: node.h node.c
	gcc node.c -c 

file.o: file.h file.c 
	gcc file.c -c
