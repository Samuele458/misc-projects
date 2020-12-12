#include <stdio.h>
#include <time.h>
#include <locale.h>

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

//-----costanti varie
#define MEMORY_SIZE 100
#define STRING_SIZE 80
#define MIN -0xFFFF
#define MAX 0xFFFF
#define SENTINEL -0x99999

void load( int memory[ MEMORY_SIZE ], int *instructionCounter );
void execute( int memory[ MEMORY_SIZE ], int *accumulator, int *instructionCounter, int *instructionRegister, int *operationCode, int *operand );
void dump( int memory[ MEMORY_SIZE ], int *accumulator, int *instructionCounter, int *instructionRegister, int *operationCode, int *operand );

int main( void ) {

    int memory[ MEMORY_SIZE ] = { 0 };
    int accumulator = +0000;
    int instructionCounter = 00;
    int instructionRegister = +0000;
    int operationCode = 00;
    int operand = 00;

    printf( "*** Welcome to Simpletron! ***\n"
            "*** Please enter the name of the file where   ***\n"
            "*** the program il located. ***\n" );

    load( memory, &instructionCounter );
    execute( memory, &accumulator, &instructionCounter, &instructionRegister, &operationCode, &operand );
    dump( memory, &accumulator, &instructionCounter, &instructionRegister, &operationCode, &operand );
}

void load( int memory[ MEMORY_SIZE ], int *instructionCounter ) {
    char fileName[ 30 ];
    FILE *programPtr;
    printf( "File Name:\n? " );
    scanf( "%s", fileName );

    size_t x;

    if( ( programPtr = fopen( fileName, "r" ) ) == NULL ) {
        printf( "File could not be opened.\n" );
    } else {
        while( !feof( programPtr ) ) {
            fscanf( programPtr ,"%X", &memory[ *instructionCounter ] );
            ++*instructionCounter;
            printf( ">%X<\n", memory[ *instructionCounter - 1 ] );
        }
    }
    *instructionCounter = 0;

}

void execute( int memory[ MEMORY_SIZE ], int *accumulator, int *instructionCounter, int *instructionRegister, int *operationCode, int *operand ) {
    void getstring ( char string[ STRING_SIZE ] );
    void readString(int memory[ MEMORY_SIZE ], const char string[ MEMORY_SIZE ], int startLocation );
    void printString( int memory[ MEMORY_SIZE ], int startLocation );
    int hold_elevate;
    char string[ STRING_SIZE ] = { 0 };
    int string_count = 0;
    int character;
    do {
        size_t elevateCount;
        *instructionRegister = memory[ *instructionCounter ];
        *operationCode = *instructionRegister / 0x100;
        *operand = *instructionRegister % 0x100;
        switch ( *operationCode ) {
            case READ:
                printf( "? " );
                scanf( "%d", &memory[ *operand ] );
                break;
            case WRITE:
                printf( "%d\n", memory[ *operand] );
                break;
            case READ_STRING:
                getstring( string );
                readString( memory, string, *operand );
                break;
            case PRINT_STRING:
                printString( memory, *operand );
                break;
            case NEW_LINE:
                puts( "" );
                break;
            case LOAD:
                *accumulator = memory[ *operand ];
                break;
            case STORE:
                memory[ *operand ] = *accumulator;
                break;
            case ADD:
                if ( *accumulator + memory[ *operand ] <= MAX ) {
                    *accumulator += memory[ *operand ];
                } else {
                    *operationCode = HALT;
                    printf( "\n*** Number bigger than 9999 ***\n"
                            "*** Simpletron execution abnormally terminated ***\n" );
                }
                break;
            case SUBTRACT:
                if ( *accumulator - memory[ *operand ] >= MIN ) {
                    *accumulator -= memory[ *operand ];
                } else {
                    *operationCode = HALT;
                    printf( "\n*** Number smaller than -9999 ***\n"
                            "*** Simpletron execution abnormally terminated ***\n" );
                }
                break;
            case DIVIDE:
                if ( memory[ *operand ] != 0 ) {
                    *accumulator /= memory[ *operand ];
                } else {
                    *operationCode = HALT;
                    printf( "\n*** Attempt to divide by zero ***\n"
                            "*** Simpletron execution abnormally terminated ***\n" );
                }
                break;
            case REST:
                if ( memory[ *operand ] != 0 ) {
                    *accumulator %= memory[ *operand ];
                } else {
                    *operationCode = HALT;
                    printf( "\n*** Attempt to divide by zero ***\n"
                            "*** Simpletron execution abnormally terminated ***\n" );
                }
                break;
            case MULTIPLY:
                if ( *accumulator * memory[ *operand ] <= MAX ) {
                    *accumulator *= memory[ *operand ];
                } else {
                    *operationCode = HALT;
                    printf( "\n*** Number bigger than 9999 ***\n"
                            "*** Simpletron execution abnormally terminated ***\n" );
                }
                break;
            case ELEVATE:
                //printf( "%d -- %d\n", *accumulator, memory[ *operand ] );
                hold_elevate = *accumulator;
                //if( *operand )
                for ( elevateCount = 1; elevateCount < memory[ *operand ]; ++elevateCount ) {
                    *accumulator = *accumulator * hold_elevate;
                }
                break;
            case BRANCH:
                *instructionCounter = *operand - 1;
                break;
            case BRANCHNEG:
                if ( *accumulator <= - 1 ) {
                    *instructionCounter = *operand - 1;
                }
                break;
            case BRANCHZERO:
                if ( *accumulator == 0 ) {
                    *instructionCounter = *operand - 1;
                }
                break;
            case HALT:
                printf( "\n*** Simpletron execution terminated ***\n" );
                break;
            default:
                *operationCode = HALT;
                printf( "\n*** Invalid command ***\n"
                        "*** Simpletron execution abnormally terminated ***\n" );
                break;
        }
        if ( *operationCode != HALT ) {
            *instructionCounter += 1;
        }
    } while ( *operationCode != HALT );
}

void dump( int memory[ MEMORY_SIZE ], int *accumulator, int *instructionCounter, int *instructionRegister, int *operationCode, int *operand ) {
    int count;
    FILE *dumpFile;
    char data[ 100 ];
    time_t dataTime = time( NULL );
    struct tm *tp = localtime ( &dataTime );

    printf( "REGISTERS:\n"
            "Accumulator\t\t+%04X\n"
            "instructionCounter\t%02d\n"
            "instructionRegister\t+%04X\n"
            "operationCode\t\t%02d\n"
            "operand\t\t\t%02d\n\n", *accumulator, *instructionCounter, *instructionRegister, *operationCode, *operand );
    printf( "MEMORY:\n   " );

    for ( count = 0; count < 10; ++count ) {
        printf ( "%7X", count );
    }

    for ( count = 0; count < MEMORY_SIZE; ++count ) {
        if ( count % 10 == 0 ) {
            puts ( "" );
            printf( "%3X", count);
        }
        printf( "%s%04x", memory[ count ] < 0 ? "  " : "  +", memory[ count ] );
    }
    puts( "" );

    setlocale (LC_ALL, "");
    strftime ( data, 100, "dumps/%H:%M %d %B %Y.dat", tp);
    if ( ( dumpFile = fopen( data, "w" ) ) == NULL ) {
        printf( "Dump File could not be opened.\n" );
    } else {
        fprintf( dumpFile, "REGISTERS:\n"
                "Accumulator\t\t+%04X\n"
                "instructionCounter\t%02d\n"
                "instructionRegister\t+%04X\n"
                "operationCode\t\t%02d\n"
                "operand\t\t\t%02d\n\n", *accumulator, *instructionCounter, *instructionRegister, *operationCode, *operand );
        fprintf( dumpFile, "MEMORY:\n   " );

        for ( count = 0; count < 10; ++count ) {
            fprintf ( dumpFile, "%7X", count );
        }

        for ( count = 0; count < MEMORY_SIZE; ++count ) {
            if ( count % 10 == 0 ) {
                fprintf( dumpFile, "\n%3X", count);
            }
            fprintf( dumpFile, "%s%04x", memory[ count ] < 0 ? "  " : "  +", memory[ count ] );
        }
        fprintf( dumpFile, "\n" );
    }

}

void readString( int memory[ MEMORY_SIZE ], const char string[ 100 ],  int startLocation ) {
    int length = 0;
    int locationCount = 0;
    while ( string[ length ] != '\0' ) {
        length += 0x1;
    }
    memory[ startLocation ] = ( length * 0x100 ) + string[ locationCount ];
    ++locationCount;
    while ( length >= 0x2 ) {
        memory[ ++startLocation ] = ( string[ locationCount ] * 0x100 ) + string[ locationCount + 1 ];
        locationCount += 2;
        length -= 0x2;
    }
}

void printString( int memory[ MEMORY_SIZE ], int startLocation ) {
    int length = 0;
    int locationCount = 0;

    length = memory[ startLocation ] / 0x100;
    printf( "%c", memory[ startLocation ] % 0x100 );

    while ( length >= 0x2 ) {
        printf( "%c", memory[ ++startLocation ] / 0x100 );
        printf( "%c", memory[ startLocation ] % 0x100 );
        length -= 2;
    }
}

void getstring ( char string[ STRING_SIZE ] ) {
    int character = getchar();
    int string_count = 0;

    printf( "String ? " );
    character = ( getchar() );
    while( string_count < STRING_SIZE - 1 && character != '\n' ) {
        string[ string_count++ ] = character;
        character = getchar();
    }
    string[ string_count ] = '\0';

}
