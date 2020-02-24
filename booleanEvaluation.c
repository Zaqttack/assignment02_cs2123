#include <stdio.h>
#include <stdlib.h>
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
    //declaring all variables
    int index = 0;
    int count;
    char **result;
    Stack *postFixStack;
    char *op1, *op2;

    //counting the number of tokens in the string
    count = countTokens(str);
    //result array is the new string created by tokens
    result = tokenizeString(str);

    postFixStack = createStack();

    while(index < count) {
        if(strcmp(result[index], "T") == 0 || strcmp(result[index], "F") == 0) {
            push(postFixStack, result[index]);
            index++;
        }
        else if(strcmp(result[index], "NOT") == 0) {
            op1 = pop(postFixStack);
            if(strcmp(op1, "T") == 0)
                strcpy(op1, "F");
            else 
                strcpy(op1, "T");

            push(postFixStack, op1);
            index++;
        }
        else if(strcmp(result[index], "AND") == 0 ||
                strcmp(result[index], "NAND") == 0 ||
                strcmp(result[index], "OR") == 0 ||
                strcmp(result[index], "NOR") == 0 ||
                strcmp(result[index], "XOR") == 0 ||
                strcmp(result[index], "COND") == 0 ||
                strcmp(result[index], "BICOND") == 0) 
        {
            op2 = pop(postFixStack);
            op1 = pop(postFixStack);
            if(op1 == NULL || op2 == NULL)
                return booleanToString(ERROR);

            if(strcmp(result[index], "AND") == 0)
                strcpy(op1, booleanToString(stringToBoolean(op1) && stringToBoolean(op2)));
            else if(strcmp(result[index], "NAND") == 0)
                strcpy(op1, booleanToString(!(stringToBoolean(op1) && stringToBoolean(op2))));
            else if(strcmp(result[index], "OR") == 0)
                strcpy(op1, booleanToString(stringToBoolean(op1) || stringToBoolean(op2)));
            else if(strcmp(result[index], "NOR") == 0)
                strcpy(op1, booleanToString(!(stringToBoolean(op1) || stringToBoolean(op2))));
            else if(strcmp(result[index], "XOR") == 0)
                strcpy(op1, booleanToString(stringToBoolean(op1) != stringToBoolean(op2)));
            else if(strcmp(result[index], "COND") == 0)
                strcpy(op1, booleanToString((!stringToBoolean(op1)) || stringToBoolean(op2)));
            else if(strcmp(result[index], "BICOND") == 0)
                strcpy(op1, booleanToString(stringToBoolean(op1) == stringToBoolean(op2)));

            push(postFixStack, op1);

            free(op2);
            index++;
        }
        
    }
    op1 = pop(postFixStack);

    if(!isEmpty(postFixStack))
        return booleanToString(ERROR);

    return op1;
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
    //declaring all variables
    int index = 0;
    int count;
    char **result;
    Stack *postFixToInfixStack;
    char *op1, *op2, *evaluation;

    //counting the number of tokens in the string
    count = countTokens(str);
    //result array is the new string created by tokens
    result = tokenizeString(str);

    postFixToInfixStack = createStack();

    while(index < count) {
        if(strcmp(result[index], "T") == 0 || strcmp(result[index], "F") == 0) {
            push(postFixToInfixStack, result[index]);
            index++;
        }
        else if(strcmp(result[index], "NOT") == 0) {
            op1 = pop(postFixToInfixStack);
            if(op1 == NULL)
                return "E";

            evaluation = (char*)malloc(sizeof(char));

            evaluation = concatenateString(op1, "blank", result[index]);

            push(postFixToInfixStack, evaluation);

            free(op1);
            index++;
        }
        else if(strcmp(result[index], "AND") == 0 ||
                strcmp(result[index], "NAND") == 0 ||
                strcmp(result[index], "OR") == 0 ||
                strcmp(result[index], "NOR") == 0 ||
                strcmp(result[index], "XOR") == 0 ||
                strcmp(result[index], "COND") == 0 ||
                strcmp(result[index], "BICOND") == 0) 
        {
            op2 = pop(postFixToInfixStack);
            op1 = pop(postFixToInfixStack);

            if(op1 == NULL || op2 == NULL)
                return "E";

            evaluation = concatenateString(op1, op2, result[index]);

            push(postFixToInfixStack, evaluation);

            free(op1);
            free(op2);
            index++;
        }
    }
    evaluation = (char*)malloc(sizeof(char));
    evaluation = pop(postFixToInfixStack);

    if(!isEmpty(postFixToInfixStack))
        return booleanToString(ERROR);

    return evaluation;
}

/* countTokens
 * input: a zero terminated string
 * output: The number of space separated tokens in str
 *
 */
int countTokens( char *str ){
    int cnt = 0;                        //number of tokens found
    int strLength = strlen( str );      //length of the string str
    int index = 1;                      //location in str

    //if str starts with a token, increment cnt
    if( str[0]!=' ' )
        cnt++;

    //Loop through all of the remaining chars in str
    while( index<strLength ) {

        //If you've found the start of a token increment cnt
        //(i.e., prior char = ' ' and current char is not = ' ')
        if( str[index-1]==' ' && str[index]!=' ' ) {
            cnt++;
        }
        index++;
    }

    return cnt;
}

/* tokenizeString
 * input: a zero terminated string
 * output: an array of dynamically strings which contains the ' ' separated tokens of str
 *
 * Note: This function mallocs space.  The caller is responsible for freeing this malloc-ed array of strings.
 */
char **tokenizeString( char *str ){

    int strLength = strlen( str );
    int cnt = countTokens( str );
    int index = 0;     //current index into str
    int curToken = 0;  //current token index to be added

    char *buffer = (char *)malloc( sizeof(char)*(strLength+1) );
    char **arrTokens = (char **)malloc( sizeof(char*)*cnt );
    if( buffer==NULL || arrTokens==NULL )
        exit(-1);

    while( index<strLength ){
        int bufferIndex=0;  //current buffer index

        //Skip space characters
        while( index<strLength && str[index]==' ' )
            index++;

        //if no new token found, leave the loop
        if(index == strLength)
            break;

        //Copy the next token into buffer
        while( index<strLength && str[index]!=' ' ){
            buffer[bufferIndex] = str[index];
            index++;
            bufferIndex++;
        }
        buffer[bufferIndex] = '\0'; //Put null terminator at end of buffer string

        //malloc space for most recent token
        arrTokens[curToken] = (char *)malloc( sizeof(char)*(bufferIndex+1) );
        if( arrTokens[curToken]==NULL )
            exit(-1);

        //copy buffer into the array of tokens
        strcpy( arrTokens[curToken], buffer );

        curToken++;
    }
    free(buffer);

    return arrTokens;
}

/* concatenateString
 * input: two operation values and their operation
 * output: a single concatenated string to be pushed to the stack
 */
char *concatenateString(char *op1, char *op2, char *operation) {
    char *evaluation = (char*)malloc(sizeof(char));

    strcpy(evaluation, "");

    if(strcmp(operation, "NOT") == 0) {
        strcat(evaluation, "( NOT ");
        strcat(evaluation, op1);
        strcat(evaluation, " )");
    }
    if(strcmp(operation, "AND") == 0) {
        strcat(evaluation, "( ");
        strcat(evaluation, op1);
        strcat(evaluation, " AND ");
        strcat(evaluation, op2);
        strcat(evaluation, " )");
    }
    else if(strcmp(operation, "NAND") == 0) {
        strcat(evaluation, "( ");
        strcat(evaluation, op1);
        strcat(evaluation, " NAND ");
        strcat(evaluation, op2);
        strcat(evaluation, " )");
    }
    else if(strcmp(operation, "OR") == 0) {
        strcat(evaluation, "( ");
        strcat(evaluation, op1);
        strcat(evaluation, " OR ");
        strcat(evaluation, op2);
        strcat(evaluation, " )");
    }
    else if(strcmp(operation, "NOR") == 0) {
        strcat(evaluation, "( ");
        strcat(evaluation, op1);
        strcat(evaluation, " NOR ");
        strcat(evaluation, op2);
        strcat(evaluation, " )");
    }
    else if(strcmp(operation, "XOR") == 0) {
        strcat(evaluation, "( ");
        strcat(evaluation, op1);
        strcat(evaluation, " XOR ");
        strcat(evaluation, op2);
        strcat(evaluation, " )");
    }
    else if(strcmp(operation, "COND") == 0) {
        strcat(evaluation, "( ");
        strcat(evaluation, op1);
        strcat(evaluation, " COND ");
        strcat(evaluation, op2);
        strcat(evaluation, " )");
    }
    else if(strcmp(operation, "BICOND") == 0) {
        strcat(evaluation, "( ");
        strcat(evaluation, op1);
        strcat(evaluation, " BICOND ");
        strcat(evaluation, op2);
        strcat(evaluation, " )");
    }

    return evaluation;
}