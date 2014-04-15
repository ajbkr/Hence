#ifndef H0_H
#define H0_H

#define PASTER(x,y)		x ## y
#define EVALUATOR(x,y)		PASTER(x, y)
#define FUNCTION_DECL(name)	EVALUATOR(FUNCTION_PREFIX, name)

void FUNCTION_DECL(and)(void);
void FUNCTION_DECL(bitwise_and)(void);
void FUNCTION_DECL(bitwise_not)(void);
void FUNCTION_DECL(bitwise_or)(void);
void FUNCTION_DECL(bitwise_shift_left)(void);
void FUNCTION_DECL(bitwise_shift_right)(void);
void FUNCTION_DECL(bitwise_xor)(void);
void FUNCTION_DECL(call)(void);
void FUNCTION_DECL(concatenate)(void);
void FUNCTION_DECL(debug)(void);
void FUNCTION_DECL(depth)(void);
void FUNCTION_DECL(divide)(void);
void FUNCTION_DECL(drop)(void);
void FUNCTION_DECL(equal)(void);
void FUNCTION_DECL(exit)(void);
void FUNCTION_DECL(if)(void);
void FUNCTION_DECL(json_rpc)(void);
void FUNCTION_DECL(length)(void);
void FUNCTION_DECL(less_than)(void);
void FUNCTION_DECL(modulo)(void);
void FUNCTION_DECL(not)(void);
void FUNCTION_DECL(or)(void);
void FUNCTION_DECL(pick)(void);
void FUNCTION_DECL(read_line)(void);
void FUNCTION_DECL(roll)(void);
void FUNCTION_DECL(substring)(void);
void FUNCTION_DECL(subtract)(void);
void FUNCTION_DECL(target)(void);
void FUNCTION_DECL(while)(void);
void FUNCTION_DECL(write)(void);

/* Synthesised functions */
void FUNCTION_DECL(abort)(void);
void FUNCTION_DECL(absolute)(void);
void FUNCTION_DECL(add)(void);
void FUNCTION_DECL(append)(void);
void FUNCTION_DECL(assign)(void);
void FUNCTION_DECL(decrement)(void);
void FUNCTION_DECL(decrement_variable)(void);
void FUNCTION_DECL(divide_by)(void);
void FUNCTION_DECL(do_nothing)(void);
void FUNCTION_DECL(drop_all)(void);
void FUNCTION_DECL(dump)(void);
void FUNCTION_DECL(duplicate)(void);
void FUNCTION_DECL(false)(void);
void FUNCTION_DECL(get)(void);
void FUNCTION_DECL(greater_than)(void);
void FUNCTION_DECL(greater_than_or_equal)(void);
void FUNCTION_DECL(increment)(void);
void FUNCTION_DECL(increment_variable)(void);
void FUNCTION_DECL(less_than_or_equal)(void);
void FUNCTION_DECL(multiply)(void);
void FUNCTION_DECL(negate)(void);
void FUNCTION_DECL(not_equal)(void);
void FUNCTION_DECL(over)(void);
void FUNCTION_DECL(write_line)(void);
void FUNCTION_DECL(reserve)(void);
void FUNCTION_DECL(rotate)(void);
void FUNCTION_DECL(set)(void);
void FUNCTION_DECL(swap)(void);
void FUNCTION_DECL(true)(void);

#endif
