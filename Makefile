all: lexer.o Stack.o main.o helper.o hash.o hashpjw.o Str.o parser.o
	gcc -g lexer.o Stack.o main.o helper.o hash.o hashpjw.o Str.o parser.o -o xmake

parser.o: parser.c
	gcc -g -c parser.c

lexer.o: lexer.c
	gcc -g -c lexer.c

main.o: main.c
	gcc -g -c main.c

helper.o: helper.c
	gcc -g -c helper.c

hash.o: hash.c
	gcc -g -c hash.c

hashpjw.o: hashpjw.c
	gcc -g -c hashpjw.c

Str.o: Str.c
	gcc -g -c Str.c

Stack.o: Stack.c
	gcc -g -c Stack.c

clean:
	rm -f *.o
