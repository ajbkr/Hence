#ifndef LIBHENCE_H
#define LIBHENCE_H

#include <inttypes.h>	/* int16_t, uint8_t */
#include <stdlib.h>     /* NULL, strtol() */

#define STACK_SIZE	10

void runtime_error(const char *msg);

void __init__(void);

void __call_native_init__(void);
void __call_native_fini__(void);
void __call_native__(void);

void __depth__(void);
char *__pop__(void);
void __push__(char *);

void hence_and(void);
void hence_beep(void);
void hence_bitwise_and(void);
void hence_bitwise_not(void);
void hence_bitwise_or(void);
void hence_bitwise_shift_left(void);
void hence_bitwise_shift_right(void);
void hence_bitwise_xor(void);
void hence_call(void);
void hence_concatenate(void);
void hence_debug(void);
void hence_depth(void);
void hence_divide(void);
void hence_drop(void);
void hence_duplicate(void);
void hence_equal(void);
void hence_exit(void);
void hence_if(void);
void hence_json_rpc(void);
void hence_length(void);
void hence_less_than(void);
void hence_modulo(void);
void hence_not(void);
void hence_or(void);
void hence_pick(void);
void hence_read_line(void);
void hence_roll(void);
void hence_substring(void);
void hence_subtract(void);
void hence_target(void);
void hence_while(void);
void hence_write(void);

struct Function {
    char *name;
    void (*func)(void);
};

#define HEAP_ELEMENT_S_SIZE	37

#define HEAP_ELEMENT_FLAGS_S_DIRTY	0
#define HEAP_ELEMENT_FLAGS_I_DIRTY	1

struct Heap_element {
    char s[HEAP_ELEMENT_S_SIZE];
    int16_t i;
    uint8_t flags;
} __attribute__((packed, aligned(4)));

#endif
