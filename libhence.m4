define(`for',`ifelse($#,0,``$0'',`ifelse(eval($2<$3),1,
    `pushdef(`$1',$2)$4`'popdef(`$1')$0(`$1',incr($2),$3,`$4')')')')dnl
dnl
define(STACK_SIZE,10)dnl
define(HEAP_ELEMENT_SIZE,40)dnl
dnl
define(NUM_CALL_NATIVE_FUNCS,31*1.25)dnl
dnl
define(HENCE_FALSE,0)dnl
define(HENCE_TRUE,1)dnl
dnl
define(__stklen__,32)dnl
dnl
ifelse(`
 *
 * popb -- pop a byte from the stack (into V0)
 *
')dnl
define(popb,`ld i,__stk__
    add i,ve
    ld v0,[i]
    add ve,1')dnl
dnl
ifelse(`
 *
 * popw -- pop a word from the stack (into V0:V1)
 *
')dnl
define(popw,`ld i,__stk__
    add i,ve
    ld v1,[i]
    add ve,2')dnl
dnl
ifelse(`
 *
 * pushb -- push a byte (in V0) onto the stack
 *
')dnl
define(pushb,`ld i,__stk__
    add ve,255	; VE = VE - 1
    add i,ve
    ld [i],v0')dnl
dnl
ifelse(`
 *
 * pushw -- push a word (in V0:V1) onto the stack
 *
')dnl
define(pushw,`ld i,__stk__
    add ve,254	; VE = VE - 2
    add i,ve
    ld [i],v1')dnl
dnl
ifelse(`
 *
 * prolog -- function prologue (make stack frame for procedure parameters)
 *
')dnl
define(prolog,`ld v0,vd
    pushb	; push frame pointer
    ld vd,ve	; assign stack pointer to frame pointer
ifelse($1,`0',`',`    add ve,eval(256-$1)	; allocate local vars (VE = VE - $1)')')dnl
dnl
ifelse(`
 *
 * epilog -- function epilogue (high level procedure exit)
 *
')dnl
define(epilog,`ld ve,vd	; assign frame pointer to stack pointer
    popb	; pop frame pointer
    ld vd,v0
    ret')dnl
dnl
ifelse(`
 *
 * fpeekb -- get a byte relative to frame pointer (into V0)
 *
')dnl
define(fpeekb,`ld i,__stk__
    ld vc,ifelse(eval($1<0),1,eval(256+$1),$1)
    add vc,vd
    add i,vc
    ld v0,[i]')dnl
dnl
ifelse(`
 *
 * fpokeb -- set a byte (held in V0) relative to frame pointer
 *
')dnl
define(fpokeb,`ld i,__stk__
    ld vc,ifelse(eval($1<0),1,eval(256+$1),$1)
    add vc,vd
    add i,vc
    ld [i],v0')dnl
dnl
start:
    ld ve,__stklen__	; initialise stack pointer

    ld v0,#ab
    pushb
    call foo
    add ve,1

;    call main

halt:
    jp halt

foo:
    prolog(2)

    ld v0,#42
    fpokeb(-1)

    ld v0,#69
    fpokeb(-2)

    fpeekb(-1)

    fpeekb(-2)

    fpeekb(1)

    epilog

__stk__:
for(`x',0,__stklen__,`    db 0
')dnl

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
    db 0	; i
    db 0
    db 0	; flags

')dnl
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

hence_and:
    ret

hence_beep:
    ld v0,30	; 1/2 second
    ld st,v0
    ret

hence_bitwise_and:
    ret

hence_bitwise_not:
    ret

hence_bitwise_or:
    ret

hence_bitwise_shift_left:
    ret

hence_bitwise_shift_right:
    ret

hence_bitwise_xor:
    ret

hence_call:
    ret

hence_concatenate:
    ret

hence_debug:
    ret

hence_depth:
    call __depth__
    ret

hence_divide:
    ret

hence_drop:
    call __pop__
    ret

hence_equal:
    ret

hence_exit:
    ret

hence_if:
    ret

hence_json_rpc:
    ld i,hence_json_rpc_L1
    jp hence_json_rpc_L2
hence_json_rpc_L1:
    db 106	; j
    db 115	; s
    db 111	; o
    db 110	; n
    db 45	; -
    db 114	; r
    db 112	; p
    db 99	; c
    db 32	; SPACE
    db 110	; n
    db 111	; o
    db 116	; t
    db 32	; SPACE
    db 105	; i
    db 109	; m
    db 112	; p
    db 108	; l
    db 101	; e
    db 109	; m
    db 101	; e
    db 110	; n
    db 116	; t
    db 101	; e
    db 100	; d
    db 0	; NUL
hence_json_rpc_L2:
    call runtime_error
    ret

hence_length:
    ret

hence_less_than:
    ret

hence_modulo:
    ret

hence_not:
    ret

hence_or:
    ret

hence_pick:
    ret

hence_read_line:
    ret

hence_roll:
    ret

hence_substring:
    ret

hence_subtract:
    ret

hence_target:
    ld i,hence_target_L1
    jp hence_target_L2
hence_target_L1:
    db 99	; c
    db 104	; h
    db 56	; 8
    db 0	; NUL
hence_target_L2:
    call __push__
    ret

hence_while:
    ret

hence_write:
    ret
