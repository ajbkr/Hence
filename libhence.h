#ifndef LIBHENCE_H
#define LIBHENCE_H

#include <stdlib.h>     /* NULL, strtol() */

void __lcall__(void);

void __depth__(void);
char *__pop__(void);
void __push__(char *);

void hence_and(void);
void hence_bitwise_and(void);
void hence_bitwise_not(void);
void hence_bitwise_or(void);
void hence_bitwise_shift_left(void);
void hence_bitwise_shift_right(void);
void hence_bitwise_xor(void);
void hence_call(void);
void hence_concatenate(void);
void hence_depth(void);
void hence_divide(void);
void hence_drop(void);
void hence_duplicate(void);
void hence_equal(void);
void hence_if(void);
void hence_json_rpc(void);
void hence_length(void);
void hence_less_than(void);
void hence_modulo(void);
void hence_multiply(void);
void hence_not(void);
void hence_or(void);
void hence_pick(void);
void hence_print(void);
void hence_rotate(void);
void hence_substring(void);
void hence_subtract(void);
void hence_swap(void);
void hence_target(void);
void hence_while(void);

struct Function {
    char *name;
    void (*func)(void);
};

#endif
