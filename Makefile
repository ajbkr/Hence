hello.ch8: h0.hence hello.hence
	./hence -tch8 h0.hence hello.hence > hello.m4
	m4 hello.m4 > hello.asm
	chasm hello.asm hello.ch8

hello.php: h0.hence hello.hence
	./hence -tphp h0.hence hello.hence > hello.php

hello.js: h0.hence hello.hence
	./hence -tjs h0.hence hello.hence > hello.js

libhence.o: h0.h libhence.c libhence.h
	gcc -o libhence.o -O3 -c libhence.c

hello: h0.hence hello.hence libhence.o
	./hence -tc h0.hence hello.hence > hello.c
	gcc -o hello hello.c libhence.o
	
clean:
	rm -f hello hello.c libhence.o hello.ch8 hello.m4 hello.asm hello.js hello.php
