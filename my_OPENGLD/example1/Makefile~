test:
	make build;
	make run;

build:
	gcc -c hello.c;
	gcc hello.o -o hello;
	gcc -I"/usr/include/SDL" -c main.c
	gcc  main.o -lSDL -o main


run:
	./hello;
	./main;
clean:
	-rm hello;
	-rm hello.o;
