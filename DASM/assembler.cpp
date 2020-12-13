#include "assembler.h"
#include "general.h"

using namespace std;
using namespace Lex;
using namespace istr_set;

Lexer::Lexer() {
    current = 0;
}

Lexer::Lexer( std::string filename_str ) : code( filename_str ) {
    source_code_filename = filename_str;
    current = 0;
}

bool Lexer::isSourceFileOpened() {
    return code.is_open();
}

bool Lexer::setSourceFile( std::string filename_str ) {
    code = std::fstream( filename_str );
    return isSourceFileOpened();
}


Token Lexer::nextToken() {
    std::string buffer = "";   //memorizza temporaneamente il testo del token
    TOKEN_TYPE type = TOKEN_TYPE::NOT_DEFINED;
    bool token_found = false;

    int opcode;
    int section;
    int def;

    code.get( current );
    while ( !token_found ) {
        buffer = "";

        if( ( current == '\n' || current == ' ' || current == '\t' ) && !code.eof() )
            code.get( current );
        if( current == ';' ) {
            while( current != '\n' && !code.eof() ) {
                code.get( current );
            }
        }

        if ( !code.eof() ) {
            switch( current ) {
                case '[':
                    type = TOKEN_TYPE::LEFT_SQUARE_BRACKET;
                    buffer += current;
                    token_found = true;
                    break;
                case ']':
                    type = TOKEN_TYPE::RIGHT_SQUARE_BRACKET;
                    buffer += current;
                    token_found = true;
                    break;
            }
        }
        if( isdigit( current ) && !code.eof() ) {
            while( isalnum( current ) && !code.eof() ) {
                buffer += current;
                code.get( current );
            }
            if ( !code.eof() ) {
                code.putback( current );
            }
            std::pair<bool,int> number = getValue( buffer );
            if( number.first ) {
                buffer = to_string( number.second );
            } else {
                throw( Error( L_UNKNOWN_LEXEME, buffer) );
            }
            type = TOKEN_TYPE::CONST_VALUE;
            token_found = true;
        } else if( isalpha( current ) && !code.eof() ) {
            while( isalnum( current ) && !code.eof() ) {
                if( isalpha( current ) ) {
                    buffer += toupper( current );
                } else {
                    buffer += current;
                }
                code.get( current );
            }
            opcode = getCommandOpcode( buffer );
            def = getDefCode( buffer );
            if ( current == ':' ) {
                type = TOKEN_TYPE::LABEL;
                token_found = true;
            } else if ( opcode != NOT_FOUND ) {
                if ( !code.eof() ) {
                    code.putback( current );
                }
                type = TOKEN_TYPE::COMMAND;
                token_found = true;
            } else if ( def != NOT_FOUND ) {
                if ( !code.eof() ) {
                    code.putback( current );
                }
                type = TOKEN_TYPE::DEF;
                token_found = true;
            } else {
                if ( !code.eof() ) {
                    code.putback( current );
                }
                type = TOKEN_TYPE::LABEL_ADDRESS;
                token_found = true;
            }
        } else if( current == '.' ) {
            do {
                buffer += toupper(current);
                code.get( current );
            } while( isalnum( current )  && !code.eof() );

            if( !code.eof() ) {
                code.putback( current );
            }

            section = getSectionCode( buffer );

            if ( section != NOT_FOUND ) {

                token_found = true;
                type = TOKEN_TYPE::SECTION;

            } else {
                throw( Error( L_INVALID_SECTION, buffer ) );
            }
        } else if ( current == '\"' ) {
            do {

                code.get( current );
                if ( !code.eof() && current != '\"') {
                    buffer += current;
                }
            } while( !code.eof() && current != '\"' );

            if( current == '\"' ) {
                type = TOKEN_TYPE::STRING;
                token_found = true;
                code.get( current );
            }

            if( !code.eof() ) {
                code.putback( current );
            }


        } else if( code.eof() ) {

            buffer = "end";
            type = TOKEN_TYPE::FILE_ENDED;
            token_found = true;

        }

    }

    return Token( type, buffer );



}

void Lexer::scan() {
    #ifdef DEBUG
    cout << "LEXER STARTED ANALYZING THE CODE." << endl;
    #endif // DEBUG_MODE

    while ( !code.eof() ){
        tokens.push_back( nextToken() );
    }
    if ( tokens[tokens.size() - 1].getTag() != TOKEN_TYPE::FILE_ENDED ) {
        tokens.push_back( Token( TOKEN_TYPE::FILE_ENDED, "end" ) );
    }

    #ifdef DEBUG
    for ( size_t i = 0; i < tokens.size(); ++i ) {
        cout <<  "TOKEN " << i << "\t\t--->\t"<< "TAG: " << (int) tokens[i].getTag() << "\t\tTEXT: \"" << tokens[i].getText() << "\"" << endl;
    }
    cout << "LEXICAL ANALYSIS ENDED.\n" << endl;
    #endif // DEBUG
}

std::string Lexer::getSourceFilename() const {
    return source_code_filename;
}

void Lexer::readch() {
    if( !code.eof() )
        code.get(current);
}

std::vector<Lex::Token> Lexer::getTokens() const {
    return tokens;
}

Token::Token( TOKEN_TYPE token_tag, std::string token_text ) {
    tag = token_tag;
    text = token_text;
}

Token::Token( const Token& other ) {
    tag = other.tag;
    text = other.text;
}

Token& Token::operator=( const Token& other ) {
    tag = other.tag;
    text = other.text;
    return *this;
}

void Token::setTag( TOKEN_TYPE token_tag ) {
    tag = token_tag;
}

TOKEN_TYPE Token::getTag() const {
    return tag;
}

string Token::getText() const {
    return text;
}

void Token::setText( string token_text ) {
    text = token_text;
}


SymbolTable::SymbolTable( const SymbolTable& other ) {
    text = other.text;
    address = other.address;
}

SymbolTable& SymbolTable::operator=( const SymbolTable& other ) {
    text = other.text;
    address = other.address;
    return *this;
}

bool SymbolTable::addLabel( std::string text_str, size_t address_value ) {
    vector<string>::iterator it = std::find( text.begin(), text.end(), text_str );
    if ( it != text.end() ) {
        return false;
    } else {
        text.push_back( text_str );
        address.push_back( address_value );
        return true;
    }
}

int SymbolTable::getAddress( std::string text_str ) {
    vector<string>::iterator it = std::find( text.begin(), text.end(), text_str );
    if ( it == text.end() ) {
        return NOT_FOUND;
    } else {
        return address[std::distance(text.begin(), it )];
    }
}

Parser::Parser() {
    position_counter = 0;
    opcode = 0;
    def = 0;
    count = 0;
    program_halt = false;
}

Parser::Parser( std::vector<Lex::Token> tokens_vector ) : Parser() {
    tokens = tokens_vector;
}

void Parser::setTokens( std::vector<Lex::Token> tok_vec ) {
    tokens = tok_vec;
}

void Parser::parse() {
    #ifdef DEBUG
    cout << "PARSER STARTED ANALYZING THE CODE." << endl;
    #endif // DEBUG_MODE

    //il primo token deve esser il Section .PROGRAM
    if( istr_set::getSectionCode( tokens[0].getText() ) != istr_set::SECTION::PROGRAM )
        throw( Error( L_LEXEME_NOT_FOUND, ".PROGRAM SECTION" ) );


    #ifdef DEBUG
    cout << "Token " << count << ": .PROGRAM section MATCHED." << endl;
    #endif // DEBUG_MODE

    ++count; //posizionamento suol secondo token

    //analisi sintattica dei rimanenti token
    while( tokens[count].getTag() != TOKEN_TYPE::FILE_ENDED ) {
        match_label();      //match dell'etichetta SE PRESEENTE
        match_command();    //match del comando
        match_operand();    //match dell'operaando del comando (non fa nulla se
                            //la dimensione dell'operando corrispondente è pari a 0.

        //verifica dell'inizio della Section .DATA
        if( tokens[count].getTag() == TOKEN_TYPE::SECTION ) {
            if ( istr_set::getSectionCode( tokens[count].getText() ) == istr_set::SECTION::DATA ) {
                #ifdef DEBUG
                cout << "TOKEN " << count << ": .DATA SECTION MATCHED." << endl;
                #endif // DEBUG_MODE
                ++count;        //Posizionamento al token successivo al Section .DATA
                while( tokens[count].getTag() != TOKEN_TYPE::FILE_ENDED ) {
                    match_label( true );           //Match della label. Metodo invocato con TRUE poichè la label deve essere presente necessariamente
                    match_def( );                  //Match del define memory
                    match_string();                //match della stringa
                }
            } else {
                throw( Error(P_INVALID_SECTION, tokens[count].getText() ) );
            }
        }
    }
    #ifdef DEBUG
    cout << "TOKENS PARSED." << endl;
    cout << "References to resolve: " << references.size() << "." << endl;
    #endif // DEBUG_MODE

    //Risoluzione dei riferimenti irrisolti
    for( size_t i = 0; i < references.size(); ++i ) {
        int address = table.getAddress( references.at(i).second );
        size_t pos = references.at(i).first + 1;

        //verifica che la label sia realmente
        //presente in memoria al momento della risoluzione
        //dei riferimenti irrisolti
        if( address == NOT_FOUND ) {
            throw( Error( P_UNDEFINED_REFERENCE, references.at(i).second ) );
        }

        //posizionamento dei 16bit dell'indirizzo
        //nel punto corretto del codice eseguibile
        program[pos--] = address % 0x100;
        address /= 0x100;
        program[pos] = address % 0x100;
    }


    if( !program_halt ) {
        throw( Error( P_HALT_NOT_FOUND, "" ) );
    }

    #ifdef DEBUG
    cout << "SYNTACTIC ANALYSIS ENDED.\n" << endl;
    #endif // DEBUG_MODE
}

void Parser::outputToFile( std::string filename ) {
    //Scrittura byte per byte sul file in output
    ofstream out( filename );
    for ( size_t i = 0; i < program.size(); ++i )
    out << program[i];
}

void Parser::match_string() {
    if ( tokens[count].getTag() == TOKEN_TYPE::STRING && tokens[count-1].getText() == "DB" ) {
        #ifdef DEBUG
        cout << "TOKEN " << count << ": String MATCHED.";
        #endif // DEBUG_MODE
        program.push_back( tokens[count].getText().size() );
        string current_string = tokens[count].getText();
        for( size_t i = 0; i < current_string.size(); ++i ) {
            program.push_back( (int)current_string[i] );
        }
        position_counter+=current_string.size() + 1;
        ++count;
    }
}

void Parser::match_label( bool obligatory ) {

    if ( tokens[count].getTag() == TOKEN_TYPE::LABEL ) {

        #ifdef DEBUG
        cout << "TOKEN " << count << ": Label MATCHED." << endl;
        #endif // DEBUG_MODE

        if( !table.addLabel( tokens[count].getText(), position_counter ) ) {
            throw( Error( P_MULTIPLE_DECLARATION, tokens[count].getText() ) );
        }
        ++count;

    } else if( obligatory ) {
        throw( Error( P_INVALID_LABEL, tokens[count].getText() ) );
    }
    #ifdef DEBUG
    cout << "TOKEN " << count << ": Label not MATCHED." << endl;
    #endif // DEBUG_MODE
}

void Parser::match_def() {
    if ( tokens[count].getTag() == TOKEN_TYPE::DEF ) {
        #ifdef DEBUG
        cout << "TOKEN " << count << ": Define Memory MATCHED." << endl;
        #endif // DEBUG_MODE
        def = istr_set::getDefCode( tokens[count].getText() );
        count++;
    }
}

void Parser::match_command() {
    if ( tokens[count].getTag() == TOKEN_TYPE::COMMAND ) {
        #ifdef DEBUG
        cout << "TOKEN " << count << ": Command MATCHED." << endl;
        #endif // DEBUG_MODE
        if( tokens[count].getText() == "HLT" ) {
            program_halt = true;
        }

        opcode = 1+istr_set::getCommandOpcode( tokens[count].getText() );
        program.push_back( opcode );
        position_counter++;
        count++;
    } else {
        throw( Error( P_INVALID_COMMAND, tokens[count].getText() ) );
    }
}


void Parser::match_operand() {
    if( istr_set::getOperandSize( opcode) != 0 ) {
        if ( tokens[count].getTag() == TOKEN_TYPE::LEFT_SQUARE_BRACKET && tokens[count+1].getTag() == TOKEN_TYPE::CONST_VALUE && tokens[count+2].getTag() == TOKEN_TYPE::RIGHT_SQUARE_BRACKET  ) {
            count++;
            #ifdef DEBUG
            cout << "TOKEN " << count << ": Operand MATCHED. Operand Type: ADDRESS (16bit)." << endl;
            #endif // DEBUG_MODE
            //check: dimensione operando e dimensione reale operando
            if ( istr_set::getOperandSize( opcode) != ADDRESS_SIZE ) {
                throw( Error( P_INVALID_OPERAND, tokens[count].getText() ) );
            }
            int temp = std::stoi( tokens[count].getText() );
            size_t pos = position_counter + 1;
            program.resize( program.size()+2);
            program[pos--] = temp % 0x100;
            temp /= 0x100;
            program[pos] = temp % 0x100;
            position_counter += 2;
            ++count;
        } else if ( tokens[count].getTag() == TOKEN_TYPE::CONST_VALUE ) {
            #ifdef DEBUG
            cout << "TOKEN " << count << ": Operand MATCHED. Operand Type: CONST_VALUE (32 bit)." << endl;
            #endif // DEBUG_MODE
            if ( istr_set::getOperandSize( opcode) != INT_SIZE ) {
                throw( Error( P_INVALID_OPERAND,  tokens[count].getText() ) );
            }
            int temp = std::stoi( tokens[count].getText() );
            size_t pos = position_counter + 3;
            //cout << "SCRITTURA ALLA POSIZIONE" << position_counter << endl;
            program.resize( program.size()+4);
            program[pos--] = temp % 0x100;
            temp /= 0x100;
            program[pos--] = temp % 0x100;
            temp /= 0x100;
            program[pos--] = temp % 0x100;
            temp /= 0x100;
            program[pos] = temp % 0x100;
            position_counter += 4;
        } else if ( tokens[count].getTag() == TOKEN_TYPE::LEFT_SQUARE_BRACKET &&
                   tokens[count+1].getTag() == TOKEN_TYPE::LABEL_ADDRESS &&
                   tokens[count+2].getTag() == TOKEN_TYPE::RIGHT_SQUARE_BRACKET  ) {
            ++count;
            #ifdef DEBUG
            cout << "TOKEN " << count << ": Operand MATCHED. Operand Type: LABEL_ADDRESS (16bit)." << endl;
            #endif // DEBUG_MODE
            if ( istr_set::getOperandSize( opcode) != ADDRESS_SIZE ) {
                throw( Error( P_INVALID_OPERAND,  tokens[count].getText() ) );
            }
            program.resize( program.size() + 2 );
            references.push_back( std::pair<size_t,std::string>( position_counter, tokens[count].getText() ) );
            position_counter += 2;
            ++count;
        } else {
            throw( Error( P_INVALID_OPERAND, tokens[count].getText() ) );
        }
        ++count;
    }
}


Assembler::Assembler( std::string asm_code_filename ) : lexical_analyzer( asm_code_filename ) {

}

bool Assembler::set_asm_file( std::string asm_code_filename ) {
    return lexical_analyzer.setSourceFile( asm_code_filename );
}

bool Assembler::is_asm_file_opened() {
    return lexical_analyzer.isSourceFileOpened();
}

void Assembler::build() {
    lexical_analyzer.scan();
    syntax_analyzer.setTokens( lexical_analyzer.getTokens() );
    syntax_analyzer.parse();
}

bool Assembler::write_machine_code_to_file( std::string out_filename ) {
    syntax_analyzer.outputToFile( out_filename  );
    return true;
}

