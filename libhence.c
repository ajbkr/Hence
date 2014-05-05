#include <inttypes.h>	/* int16_t, uint8_t */
#include <search.h>	/* hcreate(), hsearch() */
#include <stdlib.h>	/* EXIT_FAILURE, NULL, exit(), strtol() */
#include <string.h>	/* memcpy(), strcmp(), strlen(), strncpy() */
#include <errno.h>	/* errno */
#include <stdio.h>	/* fprintf(), printf(), snprintf(), stderr */

#include "libhence.h"

#define FOREVER	for ( ; ; )

uint8_t Stack[STACK_SIZE];
uint8_t Stack_ptr = STACK_SIZE;

struct Heap_element Heap[STACK_SIZE];

uint8_t Free_stack[STACK_SIZE];
uint8_t Free_stack_ptr = STACK_SIZE;

#define NUM_CALL_NATIVE_FUNCS	30 * 1.25F	/* grep call-native h0.hence |
						   wc -l */

#define HENCE_FALSE     0
#define HENCE_TRUE      1

#define check_stack_underflow()						\
    if (Stack_ptr >= STACK_SIZE) {					\
        runtime_error("stack underflow");				\
    }

#define i_is_dirty(x)	(x->flags & (1 << HEAP_ELEMENT_FLAGS_I_DIRTY))
#define s_is_dirty(x)	(x->flags & (1 << HEAP_ELEMENT_FLAGS_S_DIRTY))

#define clean_i(x)	(x->flags &= ~(1 << HEAP_ELEMENT_FLAGS_I_DIRTY))
#define clean_s(x)	(x->flags &= ~(1 << HEAP_ELEMENT_FLAGS_S_DIRTY))

#define dirty_i(x)	(x->flags |= (1 << HEAP_ELEMENT_FLAGS_I_DIRTY))
#define dirty_s(x)	(x->flags |= (1 << HEAP_ELEMENT_FLAGS_S_DIRTY))

extern struct Function Functions[];

void runtime_error(const char *msg)
{
    if (msg != NULL) {
        (void) fprintf(stderr, "Runtime error: %s\n", msg);
    } else {
        (void) fprintf(stderr, "Runtime error\n");
    }
    exit(EXIT_FAILURE);
}

static uint8_t free_stack_pop(void)
{
    if (Free_stack_ptr >= STACK_SIZE) {
        runtime_error("free stack underflow");
    }
    return Free_stack[Free_stack_ptr++];
}

static void free_stack_push(uint8_t x)
{
    if (Free_stack_ptr < 1) {
        runtime_error("free stack overflow");
    }
    Free_stack[--Free_stack_ptr] = x;
}

static uint8_t stack_pop(void)
{
    check_stack_underflow();
    return Stack[Stack_ptr++];
}

static void stack_push(uint8_t x)
{
    if (Stack_ptr < 1) {
        runtime_error("stack overflow");
    }
    Stack[--Stack_ptr] = x;
}

char *itoa(int value, char *s, int radix)
{
    const char *digits = "0123456789abcdefghijklmnopqrstuvwxyz";
    unsigned long ulvalue = value;
    char *p = s, *q = s;
    char temp;
    if (radix == 10 && value < 0) {
        *p++ = '-';
        q = p;
        ulvalue = -value;
    }
    do {
        *p++ = digits[ulvalue % radix];
        ulvalue /= radix;
    } while (ulvalue > 0);
    *p-- = '\0';
    while (q < p) {
        temp = *q;
        *q++ = *p;
        *p-- = temp;
    }
    return s;
}

static void sprintn(char *s, int n)
{
    (void) itoa(n, s, 10);
}

static long Strtol(const char *nptr, char **endptr, int base)
{
    long l;

    errno = 0;
    l = strtol(nptr, endptr, base);
    if (errno != 0) {
        runtime_error("unable to convert string to integer");
    }
    if (l < -32768 || l > 32767) {
        runtime_error("out of range");
    }
    return l;
}

void __init__(void)
{
    uint8_t i;

    for (i = 0; i < STACK_SIZE; ++i) {
        free_stack_push(i);
    }
}

void __call_native_init__(void)
{
    ENTRY item;

    (void) hcreate(NUM_CALL_NATIVE_FUNCS);

    item.key = "and";
    item.data = hence_and;
    (void) hsearch(item, ENTER);

    item.key = "beep";
    item.data = hence_beep;
    (void) hsearch(item, ENTER);

    item.key = "bitwise-and";
    item.data = hence_bitwise_and;
    (void) hsearch(item, ENTER);

    item.key = "bitwise-not";
    item.data = hence_bitwise_not;
    (void) hsearch(item, ENTER);

    item.key = "bitwise-or";
    item.data = hence_bitwise_or;
    (void) hsearch(item, ENTER);

    item.key = "bitwise-shift-left";
    item.data = hence_bitwise_shift_left;
    (void) hsearch(item, ENTER);

    item.key = "bitwise-shift-right";
    item.data = hence_bitwise_shift_right;
    (void) hsearch(item, ENTER);

    item.key = "bitwise-xor";
    item.data = hence_bitwise_xor;
    (void) hsearch(item, ENTER);

    item.key = "concatenate";
    item.data = hence_concatenate;
    (void) hsearch(item, ENTER);

    item.key = "debug";
    item.data = hence_debug;
    (void) hsearch(item, ENTER);

    item.key = "depth";
    item.data = hence_depth;
    (void) hsearch(item, ENTER);

    item.key = "divide";
    item.data = hence_divide;
    (void) hsearch(item, ENTER);

    item.key = "drop";
    item.data = hence_drop;
    (void) hsearch(item, ENTER);

    item.key = "equal";
    item.data = hence_equal;
    (void) hsearch(item, ENTER);

    item.key = "exit";
    item.data = hence_exit;
    (void) hsearch(item, ENTER);

    item.key = "if";
    item.data = hence_if;
    (void) hsearch(item, ENTER);

    item.key = "json-rpc";
    item.data = hence_json_rpc;
    (void) hsearch(item, ENTER);

    item.key = "length";
    item.data = hence_length;
    (void) hsearch(item, ENTER);

    item.key = "less-than";
    item.data = hence_less_than;
    (void) hsearch(item, ENTER);

    item.key = "modulo";
    item.data = hence_modulo;
    (void) hsearch(item, ENTER);

    item.key = "not";
    item.data = hence_not;
    (void) hsearch(item, ENTER);

    item.key = "or";
    item.data = hence_or;
    (void) hsearch(item, ENTER);

    item.key = "pick";
    item.data = hence_pick;
    (void) hsearch(item, ENTER);

    item.key = "read-line";
    item.data = hence_read_line;
    (void) hsearch(item, ENTER);

    item.key = "roll";
    item.data = hence_roll;
    (void) hsearch(item, ENTER);

    item.key = "substring";
    item.data = hence_substring;
    (void) hsearch(item, ENTER);

    item.key = "subtract";
    item.data = hence_subtract;
    (void) hsearch(item, ENTER);

    item.key = "target";
    item.data = hence_target;
    (void) hsearch(item, ENTER);

    item.key = "while";
    item.data = hence_while;
    (void) hsearch(item, ENTER);

    item.key = "write";
    item.data = hence_write;
    (void) hsearch(item, ENTER);
}

void __call_native_fini__(void)
{
    /**
     * Items added to the hash search table in __call_native_init__() are NOT
     * allocated by malloc(). Given that __call_native_fini__() is only
     * executed when a Hence program has finished executing, there is no
     * current requirement to call hdestroy().
     */
}

void __call_native__(void)
{
    struct Heap_element *s;
    void (*func)(void);
    ENTRY *found_item;
    ENTRY item;

    check_stack_underflow();
    s = &Heap[Stack[Stack_ptr]];
    if (s_is_dirty(s)) {
        sprintn(s->s, s->i);
        clean_s(s);
    }
    item.key = s->s;
    if ( (found_item = hsearch(item, FIND)) != NULL) {
        (void) __pop__();
        func = found_item->data;
        func();
    } else {
        runtime_error(NULL);
    }
}

void __depth__(void)
{
    __pushi__(STACK_SIZE - Stack_ptr);
}

int16_t __popi__(void)
{
    struct Heap_element *e;
    uint8_t x;

    x = stack_pop();
    e = &Heap[x];
    if (i_is_dirty(e)) {
        e->i = (int) Strtol(e->s, NULL, 10);
        clean_i(e);
    }
    free_stack_push(x);
    return Heap[x].i;
}

char *__pop__(void)
{
    uint8_t x;

    x = stack_pop();
    free_stack_push(x);
    return Heap[x].s;
}

void __pushi__(int16_t i)
{
    struct Heap_element *e;
    uint8_t x;

    x = free_stack_pop();
    e = &Heap[x];
    e->i = i;
    clean_i(e);
    dirty_s(e);
    stack_push(x);
}

void __push__(char *s)
{
    struct Heap_element *e;
    uint8_t x;

    x = free_stack_pop();
    e = &Heap[x];
    (void) strncpy(e->s, s, HEAP_ELEMENT_S_SIZE - 1);
    e->s[HEAP_ELEMENT_S_SIZE - 1] = '\0';
    clean_s(e);
    dirty_i(e);
    stack_push(x);
}

void hence_and(void)
{
    struct Heap_element *x, *y;

    check_stack_underflow();
    y = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(y)) {
        y->i = (int) Strtol(y->s, NULL, 10);
        clean_i(y);
    }
    (void) __pop__();

    check_stack_underflow();
    x = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(x)) {
        x->i = (int) Strtol(x->s, NULL, 10);
        clean_i(x);
    }

    x->i = (x->i != HENCE_FALSE && y->i != HENCE_FALSE) ? (HENCE_TRUE) :
        (HENCE_FALSE);
    dirty_s(x);
}

void hence_beep(void)
{
    runtime_error("beep not implemented");
}

void hence_bitwise_and(void)
{
    struct Heap_element *x, *y;

    check_stack_underflow();
    y = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(y)) {
        y->i = (int) Strtol(y->s, NULL, 10);
        clean_i(y);
    }
    (void) __pop__();

    check_stack_underflow();
    x = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(x)) {
        x->i = (int) Strtol(x->s, NULL, 10);
        clean_i(x);
    }

    x->i = x->i & y->i;
    dirty_s(x);
}

void hence_bitwise_not(void)
{
    struct Heap_element *x;

    check_stack_underflow();
    x = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(x)) {
        x->i = (int) Strtol(x->s, NULL, 10);
        clean_i(x);
    }
    x->i = ~x->i;
    dirty_s(x);
}

void hence_bitwise_or(void)
{
    struct Heap_element *x, *y;

    check_stack_underflow();
    y = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(y)) {
        y->i = (int) Strtol(y->s, NULL, 10);
        clean_i(y);
    }
    (void) __pop__();

    check_stack_underflow();
    x = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(x)) {
        x->i = (int) Strtol(x->s, NULL, 10);
        clean_i(x);
    }

    x->i = x->i | y->i;
    dirty_s(x);
}

void hence_bitwise_shift_left(void)
{
    struct Heap_element *x, *y;

    check_stack_underflow();
    y = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(y)) {
        y->i = (int) Strtol(y->s, NULL, 10);
        clean_i(y);
    }
    (void) __pop__();

    check_stack_underflow();
    x = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(x)) {
        x->i = (int) Strtol(x->s, NULL, 10);
        clean_i(x);
    }

    x->i = (y->i << x->i);
    dirty_s(x);
}

void hence_bitwise_shift_right(void)
{
    struct Heap_element *x, *y;

    check_stack_underflow();
    y = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(y)) {
        y->i = (int) Strtol(y->s, NULL, 10);
        clean_i(y);
    }
    (void) __pop__();

    check_stack_underflow();
    x = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(x)) {
        x->i = (int) Strtol(x->s, NULL, 10);
        clean_i(x);
    }

    x->i = (y->i >> x->i);
    dirty_s(x);
}

void hence_bitwise_xor(void)
{
    struct Heap_element *x, *y;

    check_stack_underflow();
    y = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(y)) {
        y->i = (int) Strtol(y->s, NULL, 10);
        clean_i(y);
    }
    (void) __pop__();

    check_stack_underflow();
    x = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(x)) {
        x->i = (int) Strtol(x->s, NULL, 10);
        clean_i(x);
    }

    x->i = x->i ^ y->i;
    dirty_s(x);
}

void hence_concatenate(void)
{
    char s[HEAP_ELEMENT_S_SIZE];
    struct Heap_element *x, *y;

    check_stack_underflow();
    y = &Heap[Stack[Stack_ptr]];
    if (s_is_dirty(y)) {
        sprintn(y->s, y->i);
        clean_s(y);
    }
    (void) __pop__();

    check_stack_underflow();
    x = &Heap[Stack[Stack_ptr]];
    if (s_is_dirty(x)) {
        sprintn(x->s, x->i);
        clean_s(x);
    }

    (void) snprintf(s, sizeof(char) * HEAP_ELEMENT_S_SIZE, "%s%s", y->s, x->s);
    (void) strncpy(x->s, s, HEAP_ELEMENT_S_SIZE - 1);
    x->s[HEAP_ELEMENT_S_SIZE - 1] = '\0';
    dirty_i(x);
}

void hence_debug(void)
{
    struct Heap_element *x;
    uint8_t i;

    (void) printf("[");
    for (i = STACK_SIZE - 1; i >= Stack_ptr; --i) {
        x = &Heap[Stack[i]];
        if (s_is_dirty(x)) {
            sprintn(x->s, x->i);
            clean_s(x);
        }
        (void) printf(" '%s'%s", x->s, (i > Stack_ptr) ? (",") : (""));
    }
    (void) printf("%s]\n", (Stack_ptr != STACK_SIZE) ? (" ") : (""));
}

void hence_depth(void)
{
    __depth__();
}

void hence_divide(void)
{
    struct Heap_element *x, *y;

    check_stack_underflow();
    y = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(y)) {
        y->i = (int) Strtol(y->s, NULL, 10);
        clean_i(y);
    }
    (void) __pop__();

    check_stack_underflow();
    x = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(x)) {
        x->i = (int) Strtol(x->s, NULL, 10);
        clean_i(x);
    }

    x->i = y->i / x->i;
    dirty_s(x);
}

void hence_drop(void)
{
    (void) __pop__();
}

void hence_equal(void)
{
    struct Heap_element *x, *y;

    check_stack_underflow();
    y = &Heap[Stack[Stack_ptr]];
    if (s_is_dirty(y)) {
        sprintn(y->s, y->i);
        clean_s(y);
    }
    (void) __pop__();

    check_stack_underflow();
    x = &Heap[Stack[Stack_ptr]];
    if (s_is_dirty(x)) {
        sprintn(x->s, x->i);
        clean_s(x);
    }

    x->i = (strcmp(x->s, y->s) == 0) ? (HENCE_TRUE) : (HENCE_FALSE);
    clean_i(x);
    dirty_s(x);
}

void hence_exit(void)
{
    struct Heap_element *x;

    check_stack_underflow();
    x = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(x)) {
        x->i = (int) Strtol(x->s, NULL, 10);
        clean_i(x);
    }

    exit(x->i);
    dirty_s(x);
}

void hence_if(void)
{
    char cond_func[HEAP_ELEMENT_S_SIZE], true_func[HEAP_ELEMENT_S_SIZE],
        false_func[HEAP_ELEMENT_S_SIZE];
    char result[HEAP_ELEMENT_S_SIZE];
    struct Heap_element *x, *y, *z, *zz;
    int16_t i;

    check_stack_underflow();
    z = &Heap[Stack[Stack_ptr]];
    if (s_is_dirty(z)) {
        runtime_error("invalid condition function");
    }
    (void) strncpy(cond_func, z->s, HEAP_ELEMENT_S_SIZE - 1);
    cond_func[HEAP_ELEMENT_S_SIZE - 1] = '\0';
    (void) __pop__();

    check_stack_underflow();
    y = &Heap[Stack[Stack_ptr]];
    if (s_is_dirty(y)) {
        runtime_error("invalid true function");
    }
    (void) strncpy(true_func, y->s, HEAP_ELEMENT_S_SIZE - 1);
    true_func[HEAP_ELEMENT_S_SIZE - 1] = '\0';
    (void) __pop__();

    check_stack_underflow();
    x = &Heap[Stack[Stack_ptr]];
    if (s_is_dirty(x)) {
        runtime_error("invalid false function");
    }
    (void) strncpy(false_func, x->s, HEAP_ELEMENT_S_SIZE - 1);
    false_func[HEAP_ELEMENT_S_SIZE - 1] = '\0';
    (void) __pop__();

    i = 0;
    while (Functions[i].name != NULL) {
        if (strcmp(cond_func, Functions[i].name) == 0) {
            Functions[i].func();	/* call cond. func. */
            break;
        }
        ++i;
    }
    if (Functions[i].name == NULL) {
        runtime_error(NULL);
    }

    check_stack_underflow();
    zz = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(zz)) {
        zz->i = (int) Strtol(zz->s, NULL, 10);
        clean_i(zz);
    }
    (void) __pop__();

    if (zz->i == HENCE_FALSE) {
        i = 0;
        while (Functions[i].name != NULL) {
            if (strcmp(false_func, Functions[i].name) == 0) {
                Functions[i].func();
                break;
            }
            ++i;
        }
        if (Functions[i].name == NULL) {
            runtime_error(NULL);
        }
    } else {
        i = 0;
        while (Functions[i].name != NULL) {
            if (strcmp(true_func, Functions[i].name) == 0) {
                Functions[i].func();
                break;
            }
            ++i;
        }
        if (Functions[i].name == NULL) {
            runtime_error(NULL);
        }
    }
}

void hence_json_rpc(void)
{
    runtime_error("json-rpc not implemented");
}

void hence_length(void)
{
    struct Heap_element *x;

    check_stack_underflow();
    x = &Heap[Stack[Stack_ptr]];
    if (s_is_dirty(x)) {
        sprintn(x->s, x->i);
        clean_s(x);
    }

    x->i = strlen(x->s);
    clean_i(x);
    dirty_s(x);
}

void hence_less_than(void)
{
    struct Heap_element *x, *y;

    check_stack_underflow();
    y = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(y)) {
        y->i = (int) Strtol(y->s, NULL, 10);
        clean_i(y);
    }
    (void) __pop__();

    check_stack_underflow();
    x = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(x)) {
        x->i = (int) Strtol(x->s, NULL, 10);
        clean_i(x);
    }

    x->i = (y->i < x->i) ? (HENCE_TRUE) : (HENCE_FALSE);
    dirty_s(x);
}

void hence_modulo(void)
{
    struct Heap_element *x, *y;

    check_stack_underflow();
    y = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(y)) {
        y->i = (int) Strtol(y->s, NULL, 10);
        clean_i(y);
    }
    (void) __pop__();

    check_stack_underflow();
    x = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(x)) {
        x->i = (int) Strtol(x->s, NULL, 10);
        clean_i(x);
    }

    x->i = y->i % x->i;
    clean_i(x);
    dirty_s(x);
}

void hence_not(void)
{
    struct Heap_element *x;

    check_stack_underflow();
    x = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(x)) {
        x->i = (int) Strtol(x->s, NULL, 10);
        clean_i(x);
    }

    x->i = (x->i != HENCE_FALSE) ? (HENCE_FALSE) : (HENCE_TRUE);
    dirty_s(x);
}

void hence_or(void)
{
    struct Heap_element *x, *y;

    check_stack_underflow();
    y = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(y)) {
        y->i = (int) Strtol(y->s, NULL, 10);
        clean_i(y);
    }
    (void) __pop__();

    check_stack_underflow();
    x = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(x)) {
        x->i = (int) Strtol(x->s, NULL, 10);
        clean_i(x);
    }

    x->i = (x->i != HENCE_FALSE || y->i != HENCE_FALSE) ? (HENCE_TRUE) :
        (HENCE_FALSE);
    dirty_s(x);
}

void hence_pick(void)
{
    struct Heap_element *n;

    check_stack_underflow();
    n = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(n)) {
        n->i = (int) Strtol(n->s, NULL, 10);
        clean_i(n);
    }
    if (n->i < 0 || n->i > STACK_SIZE - Stack_ptr - 1) {	/* XXX OK? */
        runtime_error("out of bounds");
    }
    (void) memcpy(n, &Heap[Stack[Stack_ptr + n->i + 1]],
        sizeof(struct Heap_element));
}

void hence_read_line(void)
{
    char s[HEAP_ELEMENT_S_SIZE];
    struct Heap_element *x;

    if (fgets(s, HEAP_ELEMENT_S_SIZE, stdin) == NULL) {
        runtime_error("read error");
    }
    if (s[0] != '\0' && s[strlen(s) - 1] == '\n') {
        s[strlen(s) - 1] = '\0';
    }
    __push__(s);

    x = &Heap[Stack[Stack_ptr]];
    dirty_i(x);
}

void hence_roll(void)
{
    struct Heap_element *n;
/*    int16_t n_i;
    uint8_t i, x;*/
    int i, n_i, x;

    check_stack_underflow();
    n = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(n)) {
        n->i = (int) Strtol(n->s, NULL, 10);
        clean_i(n);
    }
    (void) __pop__();
    if (n->i < 0 || n->i > STACK_SIZE - Stack_ptr - 1) {	/* XXX OK? */
        runtime_error("out of bounds");
    }

    n_i = n->i;
    x = Stack[Stack_ptr + n_i];

    for (i = n_i - 1; i >= 0; --i) {
        Stack[Stack_ptr + i + 1] = Stack[Stack_ptr + i];
    }
    Stack[Stack_ptr] = x;
}

void hence_substring(void)
{
    struct Heap_element *length, *start, *string;
    char result[HEAP_ELEMENT_S_SIZE];

    check_stack_underflow();
    string = &Heap[Stack[Stack_ptr]];
    if (s_is_dirty(string)) {
        sprintn(string->s, string->i);
        clean_s(string);
    }
    (void) __pop__();

    check_stack_underflow();
    start = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(start)) {
        start->i = (int) Strtol(start->s, NULL, 10);
        clean_i(start);
    }
    (void) __pop__();

    check_stack_underflow();
    length = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(length)) {
        length->i = (int) Strtol(length->s, NULL, 10);
        clean_i(length);
    }
    (void) __pop__();

    if (start->i > strlen(string->s) || length->i > HEAP_ELEMENT_S_SIZE - 1) {
        runtime_error(NULL);
    }
    (void) strncpy(result, &string->s[start->i], length->i);
    result[length->i] = result[HEAP_ELEMENT_S_SIZE - 1] = '\0';
    __push__(result);
}

void hence_subtract(void)
{
    struct Heap_element *x, *y;

    check_stack_underflow();
    y = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(y)) {
        y->i = (int) Strtol(y->s, NULL, 10);
        clean_i(y);
    }
    (void) __pop__();

    check_stack_underflow();
    x = &Heap[Stack[Stack_ptr]];
    if (i_is_dirty(x)) {
        x->i = (int) Strtol(x->s, NULL, 10);
        clean_i(x);
    }

    x->i = x->i - y->i;
    dirty_s(x);
}

void hence_target(void)
{
    __push__("c");
}

void hence_while(void)
{
    char cond_func[HEAP_ELEMENT_S_SIZE], loop_func[HEAP_ELEMENT_S_SIZE];
    struct Heap_element *x, *y, *z;
    int i, j;

    check_stack_underflow();
    y = &Heap[Stack[Stack_ptr]];
    if (s_is_dirty(y)) {
        runtime_error("invalid condition function");
    }
    (void) strncpy(cond_func, y->s, HEAP_ELEMENT_S_SIZE - 1);
    cond_func[HEAP_ELEMENT_S_SIZE - 1] = '\0';
    (void) __pop__();

    check_stack_underflow();
    x = &Heap[Stack[Stack_ptr]];
    if (s_is_dirty(x)) {
         runtime_error("invalid loop function");
    }
    (void) strncpy(loop_func, x->s, HEAP_ELEMENT_S_SIZE - 1);
    loop_func[HEAP_ELEMENT_S_SIZE - 1] = '\0';
    (void) __pop__();

    i = 0;
    while (Functions[i].name != NULL) {
        if (strcmp(cond_func, Functions[i].name) == 0) {
            break;
        }
        ++i;
    }
    if (Functions[i].name == NULL) {
        runtime_error(NULL);
    }
    j = 0;
    while (Functions[j].name != NULL) {
        if (strcmp(loop_func, Functions[j].name) == 0) {
            break;
        }
        ++j;
    }
    if (Functions[j].name == NULL) {
        runtime_error(NULL);
    }
    Functions[i].func();	/* call cond. func. */

    FOREVER {
        check_stack_underflow();
        z = &Heap[Stack[Stack_ptr]];
        if (i_is_dirty(z)) {
            z->i = (int) Strtol(z->s, NULL, 10);
            clean_i(z);
        }
        (void) __pop__();

        if (z->i != HENCE_FALSE) {
            Functions[j].func();	/* call loop func. */
            Functions[i].func();	/* call cond. func. */
        } else {
            break;
        }
    }
}

void hence_write(void)
{
    struct Heap_element *s;

    check_stack_underflow();
    s = &Heap[Stack[Stack_ptr]];
    if (s_is_dirty(s)) {
        sprintn(s->s, s->i);
        clean_s(s);
    }
    (void) fprintf(stdout, "%s", __pop__());
}
