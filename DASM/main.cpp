#include <iostream>
#include "emulator.h"
#include "istruction_set_utilities.h"
#include "assembler.h"
#include "interface.h"

using namespace std;
using namespace Lex;

int main ( int argc, char** argv ) {


//    cout << sizeof(assembler)<<endl<<sizeof(Lexer)<<endl<<sizeof(Parser);


//cout << "primo" << endl;
//    cin.clear();
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
//    cout << "fine" << endl;

    try {
        DasmInterface ui;
        LanguageManager::setLanguage(ENGLISH);
        Interface::clear_screen();
        ui.show();
        if ( argc == 1 ) {
            ui.show();
        } else if( argc == 3 ) {
            Lexer a(argv[1]);
            a.scan();
            Parser b( a.getTokens() );
            b.parse();
            b.outputToFile( argv[2] );
            Emulator c( argv[2], 0x10000 );
            c.execute();
        } else {
            cout << "Invalid arguments." << endl;
            cout << "No arguments: Open interface" << endl;
            cout << "2 arguments: source code assembly and output machine code filename" << endl;
        }

    }
    catch ( Error err ) {
        cout << "\n\nError found. Execution ended. Reason:" << endl;
        switch( err.getId() ) {
            case E_FILE_NOT_OPENED:
                cout << "Could non open executable file.";
                break;
            case E_INVALID_ACCESS_TO_MEMORY:
                cout << "Invalid access to memory.";
                break;
            case E_DIVISION_BY_ZERO:
                cout << "Attempt to divide by zero.";
                break;
            case L_UNKNOWN_LEXEME:
                cout << "Lexical Error. Unknown Lexeme \"" << err.getText() << "\".";
                break;
            case L_LEXEME_NOT_FOUND:
                cout << err.getText() << " Lexeme not found.";
                break;
            case L_INVALID_SECTION:
                cout << "Invalid section \"" << err.getText() << "\".";
                break;
            case P_INVALID_COMMAND:
                cout << "Invalid token \"" << err.getText() << "\". Expected command instead of \"" << err.getText() << "\" token.";
                break;
            case P_INVALID_LABEL:
                cout << "Invalid token \"" << err.getText() << "\". Expected label instead of \"" << err.getText() << "\" token.";
                break;
            case P_UNDEFINED_REFERENCE:
                cout << "Undefined reference for label \"" << err.getText() << "\".";
                break;
            case P_MULTIPLE_DECLARATION:
                cout << "Multiple declaration for label \"" << err.getText() << "\".";
                break;
            case P_INVALID_OPERAND:
                cout << "Invalid operand \"" << err.getText() << "\".";
                break;
            case P_HALT_NOT_FOUND:
                cout << "\"HLT\" command not found.";
                break;
            case P_INVALID_SECTION:
                cout << "Invalid section \"" << err.getText() << "\".";
                break;
            default:
                cout << "Unknown error" << endl;
        }
        cout << endl << endl;
    }


}
