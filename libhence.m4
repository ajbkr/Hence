define(`for',`ifelse($#,0,``$0'',`ifelse(eval($2<$3),1,
    `pushdef(`$1',$2)$4`'popdef(`$1')$0(`$1',incr($2),$3,`$4')')')')dnl
dnl
define(STACK_SIZE,24)dnl
define(HEAP_ELEMENT_SIZE,44)dnl
dnl
define(NUM_CALL_NATIVE_FUNCS,30*1.25)dnl
dnl
define(HENCE_FALSE,0)dnl
define(HENCE_TRUE,1)dnl
dnl
start:
    call main

halt:
    jp halt

Stack:
for(`x',0,STACK_SIZE,`    db 0
')dnl

Stack_ptr:
    db 0

Heap:
for(`x',0,STACK_SIZE,`    db 0	; s
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0
    db 0	; i
    db 0
    db 0	; flags
')

Free_stack:
for(`x',0,STACK_SIZE,`    db 0
')dnl

Free_stack_ptr:
    db 0

Functions:
    ; ...

runtime_error:
    ret

free_stack_pop:
    ret

free_stack_push:
    ret

stack_pop:
    ret

stack_push:
    ret

itoa:
    ret

sprintn:
    ret

Strtol:
    ret

__init__:
    ret

__call_native_init__:
    ret

__call_native_fini__:
    ret

__call_native__:
    ret

__depth__:
    ret

__pop__:
    ret

__push__:
    ret

__pushi__:
    ret
