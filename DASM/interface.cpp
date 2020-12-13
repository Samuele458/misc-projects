#include "interface.h"

using namespace std;


int isUnsignedNumber( std::string number_str ) {
    for( size_t i = 0; i < number_str.size(); ++i ) {
        if( !isdigit( number_str.at(i) ) ) {
            return -1;
        }
    }
    return std::stoi( number_str );
}


Interface::Interface() {
    header = new std::string;
}

Interface::Interface( std::string* header_str, bool clear ) {
    header = header_str;
    clear_screen_mode = clear;
}

Interface::Interface( const Interface& other ) {
    header = other.header;
    clear_screen_mode = other.clear_screen_mode;
}

Interface& Interface::operator=( const Interface& other ) {
    header = other.header;
    clear_screen_mode = other.clear_screen_mode;
    return *this;
}

void Interface::show() {
    if( clear_screen_mode )
        clear_screen();
    cout << *header << endl << endl << endl;
}

std::string* Interface::getHeader() const {
    return header;
}

void Interface::setHeader( std::string* header_str ) {
    header = header_str;
}

void Interface::clear_screen() {
    system( CLEAR_SCREEN );
    return;
}

bool Interface::getClearScreenMode() const {
    return clear_screen_mode;
}

void Interface::setClearScreenMode( bool mode ) {
    clear_screen_mode = mode;
}


//--------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------


Menu::Menu() : Interface() { }

Menu::Menu( std::string* header_str,
            std::string* menu_message_str,
            std::vector<std::string*> options_list,
            func_pointer* functions_array,
            bool clear ) :
            Interface( header_str, clear ),
            menu_message( menu_message_str ),
            options( options_list ),
            functions( functions_array )
{  }

Menu::Menu( const Menu& other ) : Interface( other ) {
    menu_message = other.menu_message;
    options = other.options;
    functions = other.functions;
}

Menu& Menu::operator=( const Menu& other ) {
    Interface::operator=( other );
    header = other.header;
    menu_message = other.menu_message;
    options = other.options;
    functions = other.functions;
    return *this;
}

void Menu::show() {
    string answer_str = "";
    unsigned int answer = 1;

    while( answer != options.size() ) {
        Interface::show();
        if( answer < 1 || answer > options.size() ){
            cout << "\tWRONG ANSWER!" << endl << endl;
        }
        cout << *menu_message << endl << endl;
        for( size_t i = 0; i < options.size(); ++i ) {
            cout << i + 1 << ".\t" << *(options.at( i )) << endl;
        }

        cout << endl << endl << " ? >  ";
        cin >> answer_str;
        cin.clear();
        cin.sync();
        answer = isUnsignedNumber( answer_str );
        if( answer >= 1 && answer <= options.size() ) {
            if( answer != options.size() )
                functions[answer-1]();
        }
    }
}

void Menu::setMenuMessageStr( std::string* menu_message_str) {
    menu_message = menu_message_str;
}

std::string* Menu::getMenuMessageStr() const {
    return menu_message;
}

std::vector<std::string*> Menu::getOptionsList() const {
    return options;
}

void Menu::setOptionsList( std::vector<std::string*> options_list ) {
    options = options_list;
}

void Menu::setFunctions( func_pointer* f_pointers ) {
    functions = f_pointers;
}

func_pointer* Menu::getFunctions() const {
    return functions;
}

//void Menu::setExitMode( bool mode ) {
//    exit_mode = mode;
//}
//
//bool Menu::getExitMode() const {
//    return exit_mode;
//}

//==========================================================
//==========================================================

TextPage::TextPage() : Interface() { }

TextPage::TextPage( std::string* header_str,
                    std::string* text_str,
                    size_t line_lenght,
                    bool clear ) :
                    Interface( header_str, clear ),
                    text( text_str ),
                    max_line_lenght( line_lenght )
{   }

TextPage::TextPage( const TextPage& other ) : Interface( other ) {
    text = other.text;
    max_line_lenght = other.max_line_lenght;
}

TextPage& TextPage::operator=( const TextPage& other ) {
    Interface::operator=( other );
    text = other.text;
    max_line_lenght = other.max_line_lenght;
    return *this;
}

void TextPage::show() {
    Interface::show();

    bool end_line_found = false;
    size_t current_line_lenght = 1;
    cout << "  ";
    for( size_t i = 0; i < text->size(); ++i ) {
        if( current_line_lenght  % max_line_lenght == 0 ) {
            end_line_found = true;
        }
        if( text->at( i ) == ' ' ) {
            if( end_line_found ) {
                cout << endl << "  ";
                end_line_found = false;
                current_line_lenght = 0;
                ++i;
            }
        }

        cout << text->at( i );

        if( text->at( i ) == '\n' ) {
            current_line_lenght = 1;
            cout << "  ";
        }
        current_line_lenght++;
    }
    cout << endl << endl << endl << '\t' << *LanguageManager::getString( CONTINUE );
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    while (std::cin.get()!='\n');
}

std::string* TextPage::getText() const {
    return text;
}

void TextPage::setText( std::string* text_str ) {
    text = text_str;
}

size_t TextPage::getMaxLineLenght() const {
    return max_line_lenght;
}

void TextPage::setMaxLineLenght( const size_t line_lenght ) {
    max_line_lenght = line_lenght;
}

//================================================================================================00
//================================================================================================00

std::vector<std::string> LanguageManager::italian_strings = { };
std::vector<std::string> LanguageManager::english_strings = { };
std::vector<std::string> LanguageManager::current_language = { };

void LanguageManager::setLanguage( LANGUAGE language_id ) {
    if ( language_id == ITALIAN )
        current_language = italian_strings;
    else
        current_language = english_strings;
}

void LanguageManager::tokenize( std::string filename, std::vector<std::string>& strings ) {
    ifstream file( filename );
    if( file.is_open() ) {
        string token = "";
        char current = 0;
        while( !file.eof() ) {
            file.get( current );
            if( current == '|' && !file.eof() ) {
                strings.push_back( token );
                token = "";

            } else if( !file.eof() ) {
                token += current;
            }
        }

        if( token != "" ) {
            strings.push_back( token );
        }
    }
}

void LanguageManager::loadLanguages() {
    tokenize( "italian.dat", LanguageManager::italian_strings );
    tokenize( "english.dat", LanguageManager::english_strings );
}

std::string* LanguageManager::getString( int string_id ) {
    return &current_language.at( string_id );
}




void DasmInterface::show() {
    vector<string*> main_menu_options = { LanguageManager::getString( COMPILE ),
                                         LanguageManager::getString( RUN ),
                                         LanguageManager::getString( COMPILE_AND_RUN ),
                                         LanguageManager::getString( CHANGE_LANGUAGE ),
                                         LanguageManager::getString( ABOUT_DASM ),
                                         LanguageManager::getString( EXIT ) };
    func_pointer functions[5] = { compile,
                                  run,
                                  compile_and_run,
                                  change_language,
                                  about_dasm };

    Menu main_menu( LanguageManager::getString( DASM_INTRO ),
                    LanguageManager::getString( MAIN_MENU_TEXT ),
                    main_menu_options,
                    functions );

    main_menu.show();

}

void DasmInterface::compile() {
    Assembler _asm;
    std::string filename;
    Interface::clear_screen();
    do {

        cout << *LanguageManager::getString( FILE_TO_COMPILE );
        cin >> filename;
        Interface::clear_screen();
        if( !_asm.set_asm_file( filename ) ) {
            cout << replace_string( *LanguageManager::getString( COULD_NOT_OPEN_FILE ), '$', filename ) << endl;
        }

    } while( !_asm.is_asm_file_opened() );
    cout << " " << *LanguageManager::getString( FILE_COMPILED ) << endl;
    _asm.build();
    cout << *LanguageManager::getString( FILE_TO_SAVE );
    cin >> filename;
    _asm.write_machine_code_to_file( filename );
}

void DasmInterface::run() {
    Emulator emu( 0x10000 );
    string filename;
    bool opened;
    Interface::clear_screen();
    do {

        cout << *LanguageManager::getString( FILE_TO_SAVE );
        cin >> filename;
        opened = emu.loadFromFile( filename );
        Interface::clear_screen();
        if( !opened ) {
            cout << replace_string( *LanguageManager::getString( COULD_NOT_OPEN_FILE ), '$', filename ) << endl;
        }
    } while( !opened );
    emu.loadFromFile( filename );
    Interface::clear_screen();
    cout << " " << *LanguageManager::getString( EXECUTION_STARTED ) << endl << endl;
    emu.execute();
    cout << endl << " " << *LanguageManager::getString( EXECUTION_ENDED ) << endl;
    cout << endl << endl << endl << '\t' << *LanguageManager::getString( CONTINUE );
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    while (std::cin.get()!='\n');
}

void DasmInterface::compile_and_run() {
    Assembler _asm;
    std::string filename;
    Interface::clear_screen();
    do {
        cout << *LanguageManager::getString( FILE_TO_COMPILE );
        cin >> filename;
        Interface::clear_screen();
        if( !_asm.set_asm_file( filename ) ) {
            cout << replace_string( *LanguageManager::getString( COULD_NOT_OPEN_FILE ), '$', filename ) << endl;
        }
    } while( !_asm.is_asm_file_opened() );
    _asm.build();
    Interface::clear_screen();
    cout << " " << *LanguageManager::getString( FILE_COMPILED ) << endl;
    cout << *LanguageManager::getString( FILE_TO_SAVE );
    cin >> filename;
    _asm.write_machine_code_to_file( filename );
    Interface::clear_screen();
    Emulator c( filename, 0x10000 );
    cout << " " << *LanguageManager::getString( EXECUTION_STARTED ) << endl << endl;
    c.execute();
    cout << endl << " " << *LanguageManager::getString( EXECUTION_ENDED ) << endl;
    cout << endl << endl << endl << '\t' << *LanguageManager::getString( CONTINUE );



    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    while (std::cin.get()!='\n');



}

void DasmInterface::change_language() {
    vector<string*> languages = { new string("Italiano"), new string("English"), LanguageManager::getString( GO_BACK ) };
    func_pointer langs_functions[2] = { italian_lanaguage,
                                        english_langauge };
    Menu language_menu( LanguageManager::getString( DASM_INTRO ),
                        LanguageManager::getString( SELECT_LANGUAGE ),
                        languages,
                        langs_functions );
    language_menu.show();
}

void DasmInterface::about_dasm() {
    TextPage dasm_info( LanguageManager::getString( ABOUT_DASM ), LanguageManager::getString( DASM_DESCRIPTION ),60 );

    dasm_info.show();
}

void DasmInterface::italian_lanaguage() {
    LanguageManager::setLanguage( ITALIAN );

}

void DasmInterface::english_langauge() {
    LanguageManager::setLanguage( ENGLISH );
}
