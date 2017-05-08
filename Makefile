all: lexer.o main.o helper.o hash.o hashpjw.o Str.o
	gcc -g lexer.o main.o helper.o hash.o hashpjw.o Str.o -o xmake

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

clean:
	rm -f *.o
