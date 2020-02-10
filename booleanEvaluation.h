#ifndef _booleanEvaluation_h
#define _booleanEvaluation_h

#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "booleanWithError.h"

char *evaluatePostfix( char *str );
char *postfixToInfix( char *str );

#endif
