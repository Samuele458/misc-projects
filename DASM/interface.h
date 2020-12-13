#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "assembler.h"



#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

unsigned int isUInt( std::string number_str );

class Interface {
    public:
        Interface();
        Interface( std::string* header_str, bool clear = true );
        Interface( const Interface& other );
        Interface& operator=( const Interface& other );

        virtual void show();

        std::string* getHeader() const;
        void setHeader( std::string* header_str );
        bool getClearScreenMode() const;
        void setClearScreenMode( bool mode );

        static void clear_screen();
    protected:
        bool clear_screen_mode;
        std::string* header;
};

typedef void(*func_pointer)();

class Menu : public Interface {
    public:
        Menu();
        Menu( std::string* header_str,
              std::string* menu_message_str,
              std::vector<std::string*> options_list,
              func_pointer* functions_array,
              bool clear = true );
        Menu( const Menu& other );
        Menu& operator=( const Menu& other );

        void show() override;

        void setMenuMessageStr( std::string* menu_message_str );
        std::string* getMenuMessageStr() const;
        std::vector<std::string*> getOptionsList() const;
        void setOptionsList( std::vector<std::string*> options_list );
        void setFunctions( func_pointer* f_pointers );
        func_pointer* getFunctions() const;
//        void setExitMode( bool mode );
//        bool getExitMode() const;
    protected:
        std::string* menu_message;
        std::vector<std::string*> options;
        func_pointer* functions;
        bool exit_mode;
};

class TextPage : public Interface {
    public:
        TextPage();
        TextPage( std::string* header_str,
                  std::string* text_str,
                  size_t line_lenght,
                  bool clear = true );
        TextPage( const TextPage& other );
        TextPage& operator=( const TextPage& other );
        void show() override;
        std::string* getText() const;
        void setText( std::string* text_str );
        size_t getMaxLineLenght() const;
        void setMaxLineLenght( const size_t line_lenght );
    protected:
        std::string* text;
        size_t max_line_lenght;
};


enum LANGUAGE : unsigned int {
    ITALIAN,
    ENGLISH,
    LANGUAGE_NUM
};

enum STRINGS : unsigned int {
    DASM_INTRO,
    DASM_DESCRIPTION,
    MAIN_MENU_TEXT,
    COMPILE,
    RUN,
    COMPILE_AND_RUN,
    CHANGE_LANGUAGE,
    ABOUT_DASM,
    EXIT,
    FILE_TO_COMPILE,
    COULD_NOT_OPEN_FILE,
    FILE_TO_SAVE,
    SELECT_LANGUAGE,
    GO_BACK,
    CONTINUE,
    FILE_COMPILED,
    EXECUTION_STARTED,
    EXECUTION_ENDED,
    STRINGS_SIZE
};

class LanguageManager {
    public:
        static void loadLanguages();
        static void setLanguage( LANGUAGE language_id );
        static std::string* getString( int string_id );
    private:
        static void tokenize( std::string filename, std::vector<std::string>& strings );
        static std::vector<std::string> italian_strings;
        static std::vector<std::string> english_strings;
        static std::vector<std::string> current_language;
};


class DasmInterface {
public:
    DasmInterface() { LanguageManager::loadLanguages();
                        LanguageManager::setLanguage( ENGLISH ); };
    void show();

    ~DasmInterface() { };
private:
    //main menu
    static void compile();
    static void run();
    static void compile_and_run();
    static void change_language();
    static void about_dasm();

    //menu change_language
    static void italian_lanaguage();
    static void english_langauge();

    //scrivere inetrafccia


};




#endif // INTERFACE_H_INCLUDED
