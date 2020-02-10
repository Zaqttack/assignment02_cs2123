#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"
#include "booleanEvaluation.h"

#define BUFFER_SIZE 100
const char DATA_FILE_NAME[] = "postfixTestData.txt";
const char PTI_FILE_NAME[] = "postfixToInfixTestData.txt";

void testFile( const char dataFile[], char *(*f)( char *));
void trimSpaceChars( char *buffer );

int main( int argc, char *argv[] )
{
    printf("\n");
    printf("Test evaluatePostfix: \n");
    printf("----------------------\n\n");
    testFile( DATA_FILE_NAME, evaluatePostfix );

    printf("\n");
    printf("Test postfixToInfix: \n");
    printf("----------------------\n\n");
    testFile( PTI_FILE_NAME, postfixToInfix );

    return 0;
}

/* testFile
 * input: name of input file, function to test
 * output: none
 *
 * Runs the specified function on inputs from the given file.
 * Prints whether the given function returns the correct value
 * This is the only function that prints in your program.
 */
void testFile( const char dataFile[], char *(*f)( char *))
{
    char *strcopy;

    char inputBuffer[BUFFER_SIZE] = "";
    char solutionBuffer[BUFFER_SIZE] = "";
    char *result;


    // Try to open the data file
    FILE *data = fopen( dataFile, "r" );
    if( data==NULL )
    {
        printf("Failed to open input file %s\n", dataFile);
        exit(-1);
    }

    while( TRUE )
    {
        // Read solution line
        if( fgets( solutionBuffer, 100, data )==NULL )
        {
            break;
        }
        trimSpaceChars( solutionBuffer );

        // Read line of operations
        if( fgets( inputBuffer, 100, data )==NULL )
        {
            printf("File formatting incorrect\n");
            break;
        }
        trimSpaceChars( inputBuffer );
        strcopy = (char *)malloc( strlen(inputBuffer)+1 );
        strcpy( strcopy, inputBuffer );

        // process the boolean string
        result = f( strcopy );

        // check if result = provided solution
        if( strcmp(solutionBuffer, result)==0 )
        {
            printf("\"%s\" = %s\nYour solution is correct\n\n", inputBuffer, solutionBuffer);
        }
        else
        {
            printf("\"%s\"\nYour solution is incorrect\n", inputBuffer);
            printf("Expected %s but your function returned %s\n\n", solutionBuffer, result);
        }

        free( result );
        free( strcopy );
    }
    fclose( data );
}

/* trimSpaceChars
 * input: a string
 * output: none
 *
 * Removes leading and trailing white space characters for the string
 */
void trimSpaceChars( char *buffer )
{
    int i=0;
    int j=0;
    //skip leading white space
    while( isspace(buffer[i]) )
        i++;
    while( i<BUFFER_SIZE )
    {
        // Replace the newline with a null char
        if( buffer[i]=='\n' )
        {
            buffer[j]='\0';
            break;
        }
        buffer[j] = buffer[i];
        i++;
        j++;
    }
    j--;
    //truncate trailing white space
    while( isspace(buffer[j]) )
        j--;
    buffer[j+1]='\0';
}


