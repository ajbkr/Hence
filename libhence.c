#include <stdlib.h>	/* EXIT_FAILURE, NULL, exit(), strtol() */
#include <string.h>	/* strcmp(), strlen(), strncpy() */
#include <stdio.h>	/* fprintf(), printf(), snprintf(), stderr */

#include "libhence.h"

#define STACK_SIZE      1024

static char Stack[STACK_SIZE][256];
static int Stack_ptr = STACK_SIZE;

#define HENCE_FALSE     "0"
#define HENCE_TRUE      "1"

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

void __lcall__(void)
{
    char *name;

    name = __pop__();
    if (strcmp(name, "and") == 0) {
        hence_and();
    } else if (strcmp(name, "bitwise_and") == 0) {
        hence_bitwise_and();
    } else if (strcmp(name, "bitwise_not") == 0) {
        hence_bitwise_not();
    } else if (strcmp(name, "bitwise_or") == 0) {
        hence_bitwise_or();
    } else if (strcmp(name, "bitwise_shift_left") == 0) {
        hence_bitwise_shift_left();
    } else if (strcmp(name, "bitwise_shift_right") == 0) {
        hence_bitwise_shift_right();
    } else if (strcmp(name, "bitwise_xor") == 0) {
        hence_bitwise_xor();
    } else if (strcmp(name, "call") == 0) {
        hence_call();
    } else if (strcmp(name, "concatenate") == 0) {
        hence_concatenate();
    } else if (strcmp(name, "depth") == 0) {
        hence_depth();
    } else if (strcmp(name, "divide") == 0) {
        hence_divide();
    } else if (strcmp(name, "drop") == 0) {
        hence_drop();
    } else if (strcmp(name, "equal") == 0) {
        hence_equal();
    } else if (strcmp(name, "if") == 0) {
        hence_if();
    } else if (strcmp(name, "json_rpc") == 0) {
        hence_json_rpc();
    } else if (strcmp(name, "length") == 0) {
        hence_length();
    } else if (strcmp(name, "less_than") == 0) {
        hence_less_than();
    } else if (strcmp(name, "modulo") == 0) {
        hence_modulo();
    } else if (strcmp(name, "multiply") == 0) {
        hence_multiply();
    } else if (strcmp(name, "not") == 0) {
        hence_not();
    } else if (strcmp(name, "or") == 0) {
        hence_or();
    } else if (strcmp(name, "pick") == 0) {
        hence_pick();
    } else if (strcmp(name, "print") == 0) {
        hence_print();
    } else if (strcmp(name, "rotate") == 0) {
        hence_rotate();
    } else if (strcmp(name, "subtract") == 0) {
        hence_subtract();
    } else if (strcmp(name, "swap") == 0) {
        hence_swap();
    } else if (strcmp(name, "target") == 0) {
        hence_target();
    } else if (strcmp(name, "while") == 0) {
        hence_while();
    } else {
        runtime_error(NULL);
    }
}

void __depth__(void)
{
    static char s[12];  /* [\-][0-9]{1,10}\0 */

    (void) snprintf(s, sizeof(char) * 12, "%d", STACK_SIZE - Stack_ptr);
    __push__(s);
}

char *__pop__(void)
{
    if (Stack_ptr >= STACK_SIZE) {
        runtime_error("stack underflow");
    }
    return Stack[Stack_ptr++];
}

void __push__(char *s)
{
    if (Stack_ptr < 0) {
        runtime_error("stack overflow");
    }
    (void) strncpy(Stack[--Stack_ptr], s, 255);
    Stack[Stack_ptr][255] = '\0';
}

void hence_and(void)
{
    static char x[256], y[256];

    (void) strncpy(y, __pop__(), 255);
    y[255] = '\0';
    (void) strncpy(x, __pop__(), 255);
    x[255] = '\0';
    __push__((strcmp(x, HENCE_FALSE) != 0 && strcmp(y, HENCE_FALSE) != 0) ?
        (HENCE_TRUE) : (HENCE_FALSE));
}

void hence_bitwise_and(void)
{
    static char s[12];  /* [\-][0-9]{1,10}\0 */
    int x, y;

    y = (int) strtol(__pop__(), NULL, 10);
    x = (int) strtol(__pop__(), NULL, 10);
    (void) snprintf(s, sizeof(char) * 12, "%d", x & y);
    __push__(s);
}

void hence_bitwise_not(void)
{
    static char s[12];  /* [\-][0-9]{1,10}\0 */
    int x;

    x = (int) strtol(__pop__(), NULL, 10);
    (void) snprintf(s, sizeof(char) * 12, "%d", ~x);
    __push__(s);
}

void hence_bitwise_or(void)
{
    static char s[12];  /* [\-][0-9]{1,10}\0 */
    int x, y;

    y = (int) strtol(__pop__(), NULL, 10);
    x = (int) strtol(__pop__(), NULL, 10);
    (void) snprintf(s, sizeof(char) * 12, "%d", x | y);
    __push__(s);
}

void hence_bitwise_shift_left(void)
{
    static char s[12];  /* [\-][0-9]{1,10}\0 */
    int x, y;

    y = (int) strtol(__pop__(), NULL, 10);
    x = (int) strtol(__pop__(), NULL, 10);
    (void) snprintf(s, sizeof(char) * 12, "%d", y << x);
    __push__(s);
}

void hence_bitwise_shift_right(void)
{
    static char s[12];  /* [\-][0-9]{1,10}\0 */
    int x, y;

    y = (int) strtol(__pop__(), NULL, 10);
    x = (int) strtol(__pop__(), NULL, 10);
    (void) snprintf(s, sizeof(char) * 12, "%d", y >> x);
    __push__(s);
}

void hence_bitwise_xor(void)
{
    static char s[12];  /* [\-][0-9]{1,10}\0 */
    int x, y;

    y = (int) strtol(__pop__(), NULL, 10);
    x = (int) strtol(__pop__(), NULL, 10);
    (void) snprintf(s, sizeof(char) * 12, "%d", x ^ y);
    __push__(s);
}

void hence_call(void)
{
    char *x;
    int i;

    x = __pop__();
    i = 0;
    while (Functions[i].name != NULL) {
        if (strcmp(x, Functions[i].name) == 0) {
            Functions[i].func();
            return;
        }
        ++i;
    }
    runtime_error(NULL);
}

void hence_concatenate(void)
{
    static char x[256], y[256];
    static char s[256];

    (void) strncpy(y, __pop__(), 255);
    y[255] = '\0';
    (void) strncpy(x, __pop__(), 255);
    x[255] = '\0';
    (void) snprintf(s, sizeof(char) * 256, "%s%s", y, x);
    __push__(s);
}

void hence_depth(void)
{
    __depth__();
}

void hence_divide(void)
{
    static char s[12];  /* [\-][0-9]{1,10}\0 */
    int x, y;

    y = (int) strtol(__pop__(), NULL, 10);
    x = (int) strtol(__pop__(), NULL, 10);
    (void) snprintf(s, sizeof(char) * 12, "%d", y / x);
    __push__(s);
}

void hence_drop(void)
{
    (void) __pop__();
}

void hence_equal(void)
{
    static char x[256], y[256];

    (void) strncpy(y,  __pop__(), 255);
    y[255] = '\0';
    (void) strncpy(x,  __pop__(), 255);
    x[255] = '\0';
    __push__((strcmp(x, y) == 0) ? (HENCE_TRUE) : (HENCE_FALSE));
}

void hence_if(void)
{
    static char cond_func[256], true_func[256], false_func[256];
    static char result[256];
    int i;

    (void) strncpy(cond_func,  __pop__(), 255);
    cond_func[255] = '\0';
    (void) strncpy(true_func,  __pop__(), 255);
    true_func[255] = '\0';
    (void) strncpy(false_func, __pop__(), 255);
    false_func[255] = '\0';

    i = 0;
    while (Functions[i].name != NULL) {
        if (strcmp(cond_func, Functions[i].name) == 0) {
            Functions[i].func();
            break;
        }
        ++i;
    }
    if (Functions[i].name == NULL) {
        runtime_error(NULL);
    }
    (void) strncpy(result, __pop__(), 255);
    result[255] = '\0';
    if (strcmp(result, HENCE_FALSE) != 0) {
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
    } else {
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
    }
}

void hence_json_rpc(void)
{
    /* ... */
}

void hence_length(void)
{
    static char s[12];  /* [\-][0-9]{1,10}\0 */
    int x;

    x = strlen(__pop__());
    (void) snprintf(s, sizeof(char) * 12, "%d", x);
    __push__(s);
}

void hence_less_than(void)
{
    int x, y;

    y = (int) strtol(__pop__(), NULL, 10);
    x = (int) strtol(__pop__(), NULL, 10);
    __push__((y < x) ? (HENCE_TRUE) : (HENCE_FALSE));
}

void hence_modulo(void)
{
    static char s[12];  /* [\-][0-9]{1,10}\0 */
    int x, y;

    y = (int) strtol(__pop__(), NULL, 10);
    x = (int) strtol(__pop__(), NULL, 10);
    (void) snprintf(s, sizeof(char) * 12, "%d", y % x);
    __push__(s);
}

void hence_multiply(void)
{
    static char s[12];  /* [\-][0-9]{1,10}\0 */
    int x, y;

    y = (int) strtol(__pop__(), NULL, 10);
    x = (int) strtol(__pop__(), NULL, 10);
    (void) snprintf(s, sizeof(char) * 12, "%d", x * y);
    __push__(s);
}

void hence_not(void)
{
    __push__((strcmp(__pop__(), HENCE_FALSE) != 0) ? (HENCE_FALSE) :
        (HENCE_TRUE));
}

void hence_or(void)
{
    static char x[256], y[256];

    (void) strncpy(y, __pop__(), 255);
    y[255] = '\0';
    (void) strncpy(x, __pop__(), 255);
    x[255] = '\0';
    __push__((strcmp(x, HENCE_FALSE) != 0 || strcmp(y, HENCE_FALSE) != 0) ?
        (HENCE_TRUE) : (HENCE_FALSE));
}

void hence_pick(void)
{
    static char v[256][256];
    int i, n;

    n = (int) strtol(__pop__(), NULL, 10);
    if (n < 0 || n > 255) {
        runtime_error(NULL);
    }
    ++n;
    for (i = 0; i < n; ++i) {
        (void) strncpy(v[i], __pop__(), 255);
        v[i][255] = '\0';
    }
    for (i = n - 1; i >= 0; --i) {
        __push__(v[i]);
    }
    __push__(v[n - 1]);
}

void hence_print(void)
{
    (void) printf("%s", __pop__());
}

void hence_rotate(void)
{
    static char x[256], y[256], z[256];

    (void) strncpy(z, __pop__(), 255);
    z[255] = '\0';
    (void) strncpy(y, __pop__(), 255);
    y[255] = '\0';
    (void) strncpy(x, __pop__(), 255);
    x[255] = '\0';
    __push__(y);
    __push__(z);
    __push__(x);
}

void hence_subtract(void)
{
    static char s[12];  /* [\-][0-9]{1,10}\0 */
    int x, y;

    y = (int) strtol(__pop__(), NULL, 10);
    x = (int) strtol(__pop__(), NULL, 10);
    (void) snprintf(s, sizeof(char) * 12, "%d", x - y);
    __push__(s);
}

void hence_swap(void)
{
    static char x[256], y[256];

    (void) strncpy(y, __pop__(), 255);
    y[255] = '\0';
    (void) strncpy(x, __pop__(), 255);
    x[255] = '\0';
    __push__(y);
    __push__(x);
}

void hence_target(void)
{
    __push__("c");
}

void hence_while(void)
{
    static char cond_func[256], loop_func[256];
    static char result[256];
    int i, j;

    (void) strncpy(cond_func,  __pop__(), 255);
    cond_func[255] = '\0';
    (void) strncpy(loop_func,  __pop__(), 255);
    loop_func[255] = '\0';

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
    Functions[i].func();
    (void) strncpy(result, __pop__(), 255);
    result[255] = '\0';

    while (strcmp(result, HENCE_FALSE) != 0) {
        Functions[j].func();

        Functions[i].func();
        (void) strncpy(result, __pop__(), 255);
        result[255] = '\0';
    }
}
