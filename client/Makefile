client: parser.tab.o ast_tree.o array.o client.o lex.yy.o
	gcc parser.tab.o ast_tree.o array.o client.o lex.yy.o -o client -lfl -lm -ljson-c

parser.tab.o: parser.y
	bison -d parser.y
	gcc parser.tab.c -c -lfl

lex.yy.o: lex.yy.c
	gcc lex.yy.c -c -lfl

ast_tree.o: ast_tree.c ast_tree.h array.h
	gcc ast_tree.c -c

array.o: array.c array.h
	gcc array.c -c

client.o: client.c
	gcc client.c -c -ljson-c
