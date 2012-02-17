Hence
=====

Hence is an experimental stack-oriented programming language with an
English-like syntax.

NOTE: Heavily work-in-progress!

### Getting Started ###

The experimental Hence compiler, hence, is currently written in PHP for ease of
prototyping.

Use chmod on UNIX-like platforms to make hence executable.

```
$ chmod +x hence
```

#### ANSI C ####

```
$ gcc -c libhence.c
$ ./hence -tc h0.hence hello.hence > hello.c
$ gcc -o hello hello.c libhence.o
$ ./hello
```

#### JavaScript ####

```
$ ./hence -tjs h0.hence hello.hence > hello.js
$ node hello.js
```

#### PHP ####

```
$ ./hence -tphp h0.hence hello.hence > hello.php
$ php hello.php
```

### TODO ###

* Plenty
