#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "stack.h"
#include "booleanEvaluation.h"
#include "booleanWithError.h"

/* evaluatePostfix
 * input: a postfix expression
 * output: T, F, or E
 *
 * Uses a stack to evaluates the postfix expression and returns the result as a string where "T" denotes true and "F" denotes false.
 * If the postfix expression is invalid it returns "E" to denote an error has occurred.
 */
char *evaluatePostfix( char *str )
{

    return booleanToString( ERROR );
}

/* postfixToInfix
 * input: a postfix expression
 * output: the equivalent infix expression
 *
 * Uses a stack to convert str to its equivalent expression in infix.
 * You can assume that the postfix expression is valid
 */
char *postfixToInfix( char *str )
{

    return booleanToString( ERROR );
}
