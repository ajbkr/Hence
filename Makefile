hello.php: h0.hence hello.hence
	./hence -tphp h0.hence hello.hence > hello.php

hello.js: h0.hence hello.hence
	./hence -tjs h0.hence hello.hence > hello.js

libhence.o: libhence.c
	gcc -o libhence.o -O3 -c libhence.c

hello: h0.hence hello.hence libhence.o
	./hence -tc h0.hence hello.hence > hello.c
	gcc -o hello hello.c libhence.o
	
clean:
	rm -f hello.js hello.php hello.c libhence.o hello