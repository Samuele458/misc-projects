#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define LINE_SIZE 200
#define MEMORY 100
#define SML_MEMORY 100
#define CONDITIONAL_OPERATORS 6
#define SIZE 50
#define OPERATORS 6

//operazioni  di I/O
#define READ 0xA
#define WRITE 0xB
#define READ_STRING 0xC
#define PRINT_STRING 0xD
#define NEW_LINE 0xE

//operazioni di caricamento/memorizzazione
#define LOAD 0x14
#define STORE 0x15

//operazioni aritmetiche
#define ADD 0x1E
#define SUBTRACT 0x1F
#define DIVIDE 0x20
#define MULTIPLY 0x21
#define REST 0x22
#define ELEVATE 0x23

//operazioni di trasferimento del controllo
#define BRANCH 0x28
#define BRANCHNEG 0x29
#define BRANCHZERO 0x30
#define HALT 0x31

struct tableEntry {
    int symbol;
    char type;
    int location;
};

struct stackNode {
    int data;
    struct stackNode *nextPtr;
};

enum cmdNames {
    REM = 0, INPUT, LET, PRINT, GOTO, IF, END
};

enum conOperators {
    LESS_THAN = 0, GREATER_THAN, LESS_THAN_OR_EQUAL_TO, GREATER_THAN_OR_EQUAL_TO, EQUAL_TO, NOT_EQUAL_TO
};

typedef struct tableEntry TableEntry;
typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;
typedef enum cmdNames CmdNames;
typedef enum conOperators ConOperators;

void FirstStep( char command[ LINE_SIZE ], TableEntry symbolTable[ MEMORY ], size_t *LocationCounter, size_t *SMLCounter, size_t *SMLBackCounter, int SMLArray[ SML_MEMORY ], int flagsArray[ SML_MEMORY ] );
void makeSymbol( const int symbol, TableEntry symbolTable[ MEMORY ], size_t *locationCounter, size_t *location, int SMLArray[ SML_MEMORY ], const char type );
void makeSMLCommand( int SMLArray[ SML_MEMORY ], unsigned int operator, size_t operand );
size_t symbolGetLocation( const int symbol, const char type, TableEntry symbolTable[ MEMORY ], size_t *SMLBackCounter, int *symbolIsPresent );
size_t isConditionalOperator( const char *operator );
void ifCommand( const size_t operator, const size_t location1, const size_t location2, const size_t gotoLocation, int SMLArray[ SML_MEMORY] );
void outputInFile( FILE *SMLFilePtr, int SMLArray[ SML_MEMORY ] );
size_t gotoCommand( TableEntry symbolTable[ MEMORY ], int flagsArray[ SML_MEMORY ], const size_t SimpleLocation, size_t SMLCounter );
void SecondStep( TableEntry symbolTable[ MEMORY ], int flagsArray[ SML_MEMORY ], int SMLArray[ SML_MEMORY ] );
void push( StackNodePtr *topPtr, int value );
int pop( StackNodePtr *topPtr );
int isEmpty( StackNodePtr topPtr );
void printStack( StackNodePtr topPtr );
int evaluatePostfixExpression( char *expr, TableEntry symbolTable[ MEMORY ], size_t *SMLBackCounter, int *symbolIsPresent, int SMLArray[ SML_MEMORY ] );
int calculate( int SMLArray[ SML_MEMORY ], int op1, int op2, char operator );
int isOperator( char c );
char stackTop( StackNodePtr topPtr );
void convertToPostfix( char infix[], char postfix[] );
int precedence( char operator1, char operator2 );
void getExpression ( char string[ SIZE ] );
void makeExpression( const char command[ LINE_SIZE ], char expression[ LINE_SIZE ] );
void letCommand( size_t variableLocation, char expression[ LINE_SIZE ], TableEntry symbolTable[ MEMORY ], size_t *LocationCounter, size_t *SMLBackCounter, int SMLArray[ SML_MEMORY ] );
void insertConstants( int SMLarray[ SML_MEMORY ], TableEntry symbolTable[ MEMORY ] );

int main( void ) {
    FILE *ProgFilePtr;
    FILE *SMLFilePtr;
    char command[ LINE_SIZE ] = { 0 };
    TableEntry symbolTable[ MEMORY ] = { 0 };
    size_t LocationCounter = 0;
    int SimpletronMemory[ SML_MEMORY ] = { 0 };
    size_t SMLCounter = 0;
    size_t SMLBackCounter = SML_MEMORY - 1;
    int SMLArray[ SML_MEMORY ] = { 0 };
    int flagsArray[ SML_MEMORY ] = { 0 };
    size_t count;

    size_t x;

    if ( ( SMLFilePtr = fopen( "SMLprogram.dat", "w" ) ) == NULL ) {
        puts( "Output file could not be opened." );
    } else {
        if ( ( ProgFilePtr = fopen( "program.txt", "r" ) ) == NULL ) {
            puts( "File could not be opened." );
        } else {
            for ( count = 0; count < SML_MEMORY; ++count ) {
                flagsArray[ count ] = -1;
            }
            while ( fgets( command, LINE_SIZE, ProgFilePtr ) != NULL ) {
                FirstStep( command, symbolTable, &LocationCounter, &SMLCounter, &SMLBackCounter, SMLArray, flagsArray );
            }

            for ( x = 0; x < 100; ++x ) {
                printf( "%5d %-5c %d\n", symbolTable[ x ].symbol, symbolTable[ x ].type, symbolTable[ x ].location );
            }
            SecondStep( symbolTable, flagsArray, SMLArray );
            fclose( ProgFilePtr );

        }
        for ( x = 0; x < 100; ++x ) {
            printf( "%d - %d\n",x,  SMLArray[ x ] );
        }
        insertConstants( SMLArray, symbolTable );
        outputInFile( SMLFilePtr, SMLArray );

        fclose( SMLFilePtr );
    }
}

void FirstStep( char command[ LINE_SIZE ], TableEntry symbolTable[ MEMORY ], size_t *LocationCounter, size_t *SMLCounter, size_t *SMLBackCounter, int SMLArray[ SML_MEMORY ], int flagsArray[ SML_MEMORY ] ) {
    unsigned int CommandLine;
    char commandCopy[ LINE_SIZE ];
    char expression[ LINE_SIZE ];
    int costantNumber;
    char *tokenCommandPtr;
    char *commandsList[ 7 ] = { "rem", "input", "let", "print", "goto", "if", "end\n" };
    char *variable;
    int variableIsPresent = 1;
    size_t location1;
    size_t location2;
    size_t gotoLocation;
    char *varOne;
    char *varTwo;
    char *operator;
    size_t operatorValue;
    size_t *gotoLocationPtr;
    size_t count;
    size_t countTwo;

    CmdNames CmdNamesList;

    if ( command[0] != '\n' ) {
        strcpy( commandCopy, command );
        tokenCommandPtr = strtok( command, " " );
        symbolTable[ *LocationCounter ].symbol = atoi( tokenCommandPtr );
        symbolTable[ *LocationCounter ].type = 'L';
        symbolTable[ *LocationCounter ].location = *SMLCounter;
        ++*LocationCounter;
        tokenCommandPtr = strtok( NULL, " " );
        printf( "<%s>\n", tokenCommandPtr );
        for ( CmdNamesList = REM; strcmp( tokenCommandPtr, commandsList[ CmdNamesList ]) != 0 ; ++CmdNamesList ) {
        }

        switch ( CmdNamesList ) {
            case REM:
                break;
            case INPUT:
                ++*SMLCounter;
                variable = strtok( NULL, " " );

                location1 = symbolGetLocation( *variable, 'V', symbolTable, SMLBackCounter, &variableIsPresent );
                if ( !variableIsPresent ) {
                    makeSymbol( *variable, symbolTable, LocationCounter, &location1, SMLArray, 'V' );
                    ++*LocationCounter;

                }

                makeSMLCommand( SMLArray, READ, location1 );

                break;
            case IF:
                *SMLCounter += 3;
                varOne = strtok( NULL, " " );
                location1 = symbolGetLocation( *varOne, 'V', symbolTable, SMLBackCounter, &variableIsPresent );
                if ( !variableIsPresent ) {
                    makeSymbol( *varOne, symbolTable, LocationCounter, &location1, SMLArray, 'V' );
                    ++*LocationCounter;
                }
                operator = strtok( NULL, " " );
                varTwo = strtok( NULL, " " );
                location2 = symbolGetLocation( *varTwo, 'V', symbolTable, SMLBackCounter, &variableIsPresent );
                if ( !variableIsPresent ) {
                    makeSymbol( *varTwo, symbolTable, LocationCounter, &location2, SMLArray, 'V' );
                    ++*LocationCounter;
                }
                //printf( "%d", strcmp( strtok( NULL, " " ), "goto" ) )
                if ( strcmp( strtok( NULL, " " ), "goto" ) == 0 ) {
                    gotoLocation = atoi( strtok( NULL, " " ) );
                    gotoLocation = gotoCommand( symbolTable, flagsArray, gotoLocation, *SMLCounter - 1 );

                    operatorValue = isConditionalOperator( operator );
                    if ( operatorValue >= 0 && operatorValue <= 5 ) {
                        ifCommand( operatorValue, location1, location2, gotoLocation, SMLArray );
                    }
                }
                break;
            case PRINT:
                ++*SMLCounter;
                variable = strtok( NULL, " " );

                location1 = symbolGetLocation( *variable, 'V',  symbolTable, SMLBackCounter, &variableIsPresent );
                if ( !variableIsPresent ) {
                    makeSymbol( *variable, symbolTable, LocationCounter, &location1, SMLArray, 'V' );
                    ++*LocationCounter;

                }

                makeSMLCommand( SMLArray, WRITE, location1 );
                break;
            case GOTO:
                ++*SMLCounter;
                gotoLocation = atoi( strtok( NULL, " " ) );
                gotoLocation = gotoCommand( symbolTable, flagsArray, gotoLocation, *SMLCounter - 1 );
                makeSMLCommand( SMLArray, BRANCH, gotoLocation );
                break;
            case LET:
                variable = strtok( NULL, " " );


                location1 = symbolGetLocation( *variable, 'V',  symbolTable, SMLBackCounter, &variableIsPresent );  // varibile in cui verrà inserito il risultato
                printf( "VARIEBLE: %c   LOC: %d\n", *variable, location1 );
                if ( !variableIsPresent ) {
                    makeSymbol( *variable, symbolTable, LocationCounter, &location1, SMLArray, 'V' );
                    ++*LocationCounter;
                }

                strtok( NULL, " " );
                for ( count = 0; count < LINE_SIZE; ++count ) {
                    expression[ count ] = 0;
                }
                makeExpression( commandCopy, expression );
                letCommand( location1, expression, symbolTable, LocationCounter, SMLBackCounter, SMLArray );
                break;
            case END:
                ++*SMLCounter;
                makeSMLCommand( SMLArray, HALT, 0 );
                break;
        }
    }
}

void letCommand( size_t variableLocation, char expression[ LINE_SIZE ], TableEntry symbolTable[ MEMORY ], size_t *LocationCounter, size_t *SMLBackCounter, int SMLArray[ SML_MEMORY ] ) {
    size_t count;
    size_t countTwo;
    char number[ 6 ] = { 0 };
    int variableIsPresent = 1;
    size_t location;
    int resultLocation;
    char infix[ SIZE ] = { 0 };
    char postfix[ SIZE ] = { 0 };

    for ( count = 0; expression[ count ] != '\0'; ++count ) {
        if ( isalpha( expression[ count] ) ) {
            location = symbolGetLocation( expression[ count ], 'V',  symbolTable, SMLBackCounter, &variableIsPresent );
            if ( !variableIsPresent ) {
                makeSymbol( expression[ count ], symbolTable, LocationCounter, &location, SMLArray, 'V' );
                ++*LocationCounter;
            }
        } else if ( isdigit( expression[ count ] ) ) {
            //countTwo = 0;
            printf( "EXP: <%s>\n", expression );
            for ( countTwo = 0; countTwo < 6; ++countTwo ) {
                number[ countTwo ] = 0;
            }
            while ( isdigit( expression[ count ] ) ) {
                sprintf( number, "%s%c", number, expression[ count ] );
                ++count;
            }
            --count;
            location = symbolGetLocation( atoi( number ), 'C',  symbolTable, SMLBackCounter, &variableIsPresent );
            printf( "Location: %d\n", location );
            if ( !variableIsPresent ) {
                makeSymbol( atoi( number ), symbolTable, LocationCounter, &location, SMLArray, 'C' );
                ++*LocationCounter;
            }
            //sprintf( number, "%s ", number );
        }
    }
    convertToPostfix( expression, postfix );
    resultLocation = evaluatePostfixExpression( postfix, symbolTable, SMLBackCounter, &variableIsPresent, SMLArray );
    makeSMLCommand( SMLArray, LOAD, resultLocation );
    makeSMLCommand( SMLArray, STORE, variableLocation );
    printf( "POSTFIX: <%s>\n", postfix );
}

void SecondStep( TableEntry symbolTable[ MEMORY ], int flagsArray[ SML_MEMORY ], int SMLArray[ SML_MEMORY ] ) {
    size_t count;
    size_t TableCount;
    size_t location;

    for ( count = 0; count < SML_MEMORY; ++count ) {
        printf( "%d\n", flagsArray[ count ] );
        if ( flagsArray[ count ] != -1 ) {
            TableCount = 0;
            for ( TableCount = 0; TableCount < SML_MEMORY; ++TableCount ) {
                if ( symbolTable[ TableCount ].symbol == flagsArray[ count ] && symbolTable[ TableCount ].type == 'L' ) {
                    printf( "Table count: %d\n", TableCount );
                    printf( "TABLE: %d  %c  %d\nCOMMAND: %X\n", symbolTable[ TableCount ].symbol, symbolTable[ TableCount ].type, symbolTable[ TableCount ].location, SMLArray[ count ] );
                    SMLArray[ count ] = ( ( SMLArray[ count ] / 0x100 ) * 0x100 ) + symbolTable[ TableCount ].location;
                    TableCount = SML_MEMORY - 1;
                }
                ++TableCount;
            }
            //--TableCount;

        }
    }
}

void makeSymbol( const int symbol, TableEntry symbolTable[ MEMORY ], size_t *locationCounter, size_t *location, int SMLArray[ SML_MEMORY ], const char type ) {

    symbolTable[ *locationCounter ].symbol = symbol;
    symbolTable[ *locationCounter ].type = type;
    symbolTable[ *locationCounter ].location = *location;
}

size_t symbolGetLocation( const int symbol, const char type, TableEntry symbolTable[ MEMORY ], size_t *SMLBackCounter, int *symbolIsPresent ) {
    size_t counter;
    size_t holdSMLBC;

    *symbolIsPresent = 0;
    for ( counter = 0; counter < MEMORY; ++counter ) {
        if ( symbolTable[ counter ].type == type && symbolTable[ counter ].symbol == symbol ) {
            *symbolIsPresent = 1;
            return symbolTable[ counter ].location;
        }
    }
    if ( *symbolIsPresent == 0 ) {
        holdSMLBC = *SMLBackCounter;
        --*SMLBackCounter;
        return holdSMLBC;
    }
}

void makeSMLCommand( int SMLArray[ SML_MEMORY ], unsigned int operator, size_t operand ) {
    int command;
    size_t counter;

    command = ( operator * 0x100 ) + operand;
    counter = 0;
    while ( SMLArray[ counter ] != 0 ) {
        ++counter;
    }
    if ( SMLArray[ counter ] == 0 ) {
        SMLArray[ counter ] = command;
    }

}

size_t isConditionalOperator( const char *operator ) {
    char *operators[ CONDITIONAL_OPERATORS ] = { "<", ">", "<=", ">=", "==", "!=" };
    size_t count;
    for ( count = 0; count < CONDITIONAL_OPERATORS; ++count ) {
        if ( strcmp( operator, operators[ count ] ) == 0 ) {
            return count;
        }
    }
}

void ifCommand( const size_t operator, const size_t location1, const size_t location2, const size_t gotoLocation, int SMLArray[ SML_MEMORY ] ) {
    ConOperators OperatorsValues;
    switch ( operator ) {
        case EQUAL_TO:
            makeSMLCommand( SMLArray, LOAD, location1 );
            makeSMLCommand( SMLArray, SUBTRACT, location2 );
            makeSMLCommand( SMLArray, BRANCHZERO, gotoLocation );
            break;
    }
}

void outputInFile( FILE *SMLFilePtr, int SMLArray[ SML_MEMORY ] ) {
    size_t count = 0;

    while ( count < SML_MEMORY ) {
        fprintf( SMLFilePtr, "+%04X\n", SMLArray[ count ] );
        ++count;
    }
}

size_t gotoCommand( TableEntry symbolTable[ MEMORY ], int flagsArray[ SML_MEMORY ], const size_t SimpleLocation, size_t SMLCounter ) {
    size_t count;

    for ( count = 0; count <= SML_MEMORY; ++count ) {
        if ( symbolTable[ count ].symbol == SimpleLocation && symbolTable[ count ].type == 'L' ) {
            return symbolTable[ count ].location;
        }
    }
    printf( "\n>%d<\n", SMLCounter );
    flagsArray[ SMLCounter ] = SimpleLocation;
    return 0;
}

void push( StackNodePtr *topPtr, int value ) {
    StackNodePtr newPtr;

    newPtr = malloc( sizeof( StackNode ) );
    if ( newPtr != NULL ) {
        newPtr->data = value;
        newPtr->nextPtr = *topPtr;
        *topPtr = newPtr;
    } else  {
        printf( "%c not inserted. No memory available.\n", value );
    }
}

int pop( StackNodePtr *topPtr ) {
    StackNodePtr tempPtr;
    int popValue;

    tempPtr = *topPtr;
    popValue = ( *topPtr )->data;
    *topPtr = ( *topPtr )->nextPtr;
    free( tempPtr );
    return popValue;
}

int isEmpty( StackNodePtr topPtr ) {
    return topPtr == NULL;
}

void printStack( StackNodePtr topPtr ) {
    while ( topPtr  != NULL ) {
        printf( "%d", topPtr->data );
        topPtr = topPtr->nextPtr;
    }
}

int evaluatePostfixExpression( char *expr, TableEntry symbolTable[ MEMORY ], size_t *SMLBackCounter, int *symbolIsPresent, int SMLArray[ SML_MEMORY ] ) {
    StackNodePtr stackPtr = NULL;
    size_t count;
    char currentChar;
    int x;
    int y;
    unsigned int nDigits;
    int grade;
    int sum;
    size_t initialDigitCount;

    int valuee;

    count = 0;

    while ( expr[ count ] != '\0' ) {

        currentChar = expr[ count ];
        if ( isdigit( currentChar ) ) {
            initialDigitCount = count;
            nDigits = 1;
            while ( expr[ count ] != ' '  ) {
                ++nDigits;
                ++count;
            }
            --count;
            --nDigits;
            sum = 0;
            grade = 0;
            while ( grade != 1 ) {
                grade = pow ( 10, --nDigits );
                sum += ( expr[ initialDigitCount ] - '0' ) * grade;
                ++initialDigitCount;
            }
            valuee = symbolGetLocation( sum, 'C', symbolTable, SMLBackCounter, symbolIsPresent );
            printf( "VALUE: %d\n", valuee );
            push( &stackPtr, symbolGetLocation( sum, 'C', symbolTable, SMLBackCounter, symbolIsPresent ) );
        } else if ( isalpha( currentChar ) ) {
            puts( "CIAO" );
            push( &stackPtr, symbolGetLocation( currentChar, 'V', symbolTable, SMLBackCounter, symbolIsPresent ) );

        } else if ( isOperator( currentChar ) ) {
            x = pop( &stackPtr );
            y = pop( &stackPtr );
            calculate( SMLArray, y, x, currentChar );
            push( &stackPtr, symbolGetLocation( '!', 'V', symbolTable, SMLBackCounter, symbolIsPresent ) );
            makeSMLCommand( SMLArray, STORE, symbolGetLocation( '!', 'V', symbolTable, SMLBackCounter, symbolIsPresent ) + 0x1 );
            ++*SMLBackCounter;
        }
        ++count;
    }
    puts( "CIAOlo" );
    return pop( &stackPtr );
}

int calculate( int SMLArray[ SML_MEMORY ], int op1, int op2, char operator ) {
    int opeartionCode;



    printf( "LOCONE %d   LOCTWO: %d\n", op1, op2 );
    switch ( operator ) {
        case '+':
            opeartionCode = ADD;
            break;
        case '-':
            opeartionCode = SUBTRACT;
            break;
        case '*':
            opeartionCode = MULTIPLY;
            break;
        case '/':
            opeartionCode = DIVIDE;
            break;
        case '%':
            opeartionCode = REST;
            break;
        case '^':
            opeartionCode = ELEVATE;
            break;
    }
    makeSMLCommand( SMLArray, LOAD, op1 );
    makeSMLCommand( SMLArray, opeartionCode, op2 );

    return 5;
}

int isOperator( char c ) {
    switch ( c ) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
        case '%':
            return 1;
            break;
        default:
            return 0;
            break;
    }
}

char stackTop( StackNodePtr topPtr ) {
    StackNodePtr previousPtr;

    return topPtr->data;
}

void convertToPostfix( char infix[], char postfix[] ) {
    StackNodePtr stackPtr = NULL;
    size_t count;
    char currentChar;

    push( &stackPtr, '(' );
    sprintf( infix, "%s)", infix );

    count = 0;
    while ( !isEmpty( stackPtr ) ) {
        currentChar = infix[ count ];
        if ( isdigit( currentChar ) ) {
            while ( isdigit( infix[ count ] ) ) {
                sprintf( postfix, "%s%c", postfix, infix[ count ] );
                ++count;
            }
            --count;
            sprintf( postfix, "%s ", postfix );
        } else if ( isalpha( infix[ count ] ) ) {
            sprintf( postfix, "%s%c ", postfix, infix[ count ] );
        } else if ( currentChar == '(' ) {
            push( &stackPtr, '(' );
        } else if ( isOperator( currentChar ) ) {
            while ( isOperator( stackTop( stackPtr ) ) && precedence( stackTop( stackPtr ), currentChar ) == 1 || precedence( stackTop( stackPtr ), currentChar ) == 0 ) {
                sprintf( postfix, "%s%c ", postfix, stackTop( stackPtr ) );
                pop( &stackPtr );
            }
            push( &stackPtr, currentChar );
        } else if ( currentChar == ')' ) {
            while ( stackTop( stackPtr ) != '(' ) {
                sprintf( postfix, "%s%c ", postfix, stackTop( stackPtr ) );
                if ( isOperator( stackTop( stackPtr ) ) ) {
                    pop( &stackPtr );
                }
            }
            pop( &stackPtr );
        } else if ( currentChar == ' ' ) {
            //sprintf( postfix, "%s%c", postfix, 'F' );
        }
        ++count;
    }
    //Per vedere i risultati:
    //printf( "infix: %s\n", infix );
    //printf( "postfix: %s\n", postfix );
    //printStack( stackPtr );

}

int precedence( char operator1, char operator2 ) {
    int opPrecedence1;
    int opPrecedence2;
    switch ( operator1 ) {
        case '+':
        case '-':
            opPrecedence1 = 1;
            break;
        case '*':
        case '/':
        case '%':
            opPrecedence1 = 2;
            break;
        case '^':
            opPrecedence1 = 3;
            break;
    }
    switch ( operator2 ) {
        case '+':
        case '-':
            opPrecedence2 = 1;
            break;
        case '*':
        case '/':
        case '%':
            opPrecedence2 = 2;
            break;
        case '^':
            opPrecedence2 = 3;
            break;
    }
    if ( opPrecedence1 < opPrecedence2 ) {
        return -1;
    } else if ( opPrecedence1 == opPrecedence2 ) {
        return 0;
    } else if ( opPrecedence1 > opPrecedence2 ) {
        return 1;
    }
}

void getExpression ( char string[ SIZE ] ) {
    int character;
    int string_count = 0;

    character = ( getchar() );
    while( string_count < SIZE - 1 && character != '\n' ) {
        string[ string_count++ ] = character;
        character = getchar();
    }
    string[ string_count ] = '\0';

}

void makeExpression( const char command[ LINE_SIZE ], char expression[ LINE_SIZE ] ) {
    char commandCopy[ LINE_SIZE ];
    size_t positionCommand;
    size_t positionExpression;
    char curChar;

    strcpy( commandCopy, command );
    strcpy( commandCopy, strchr( commandCopy, '=' ) );
    positionCommand = 0;
    positionExpression = 0;
    while ( commandCopy[ positionCommand ] != '\0' ) {
        curChar = commandCopy[ positionCommand ];
        if ( curChar == '(' || curChar == ')' || isOperator( curChar ) || isdigit( curChar ) || isalpha( curChar ) ) {
            expression[ positionExpression ] =  curChar;
            ++positionExpression;
        }
        ++positionCommand;
    }
    expression[ positionExpression ] == '\0';
}

void insertConstants( int SMLarray[ SML_MEMORY ], TableEntry symbolTable[ MEMORY ] ) {
    size_t count;

    for ( count = 0; count < SML_MEMORY; ++count ) {
        if ( symbolTable[ count ].type == 'C' ) {
            SMLarray[ symbolTable[ count ].location ] = symbolTable[ count ].symbol;
            printf( "loc %d -  %d\n", symbolTable[ count ].location, SMLarray[ symbolTable[ count ].location ] );
        }
    }
}




















