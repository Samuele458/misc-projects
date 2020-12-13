#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <utility>
#include <functional>
#include "emulator.h"
#include "error.h"
#include "istruction_set_utilities.h"
#include "general.h"


//Tipi di token.
enum class TOKEN_TYPE {
    NOT_DEFINED,
    LABEL,
    COMMAND,
    ADDRESS,
    LABEL_ADDRESS,
    CONST_VALUE,
    FILE_ENDED,
    SECTION,
    DEF,
    STRING,
    LEFT_SQUARE_BRACKET,
    RIGHT_SQUARE_BRACKET,
    TOKENS_NUM
};

/*
 * namespcae Lex:   Comprende classi e funzioni riguardanti
 *                  l'analisi lessicale (Lex::Lexer) e
 *                  l'analisi sintattica (Lex::Parser)
 */
namespace Lex{


    /*
     *  Classe:             Token
     *  Descrizione:        Gestione di un Token
     */
    class Token {
        public:
            //costruisce l'istanza con TAG(ovvero un'enum TOKEN_TYPE), e testo del token
            Token( TOKEN_TYPE token_tag, std::string token_text );

            //costruttore di copia
            Token( const Token& other );

            //operatore di assegnazione
            Token& operator=( const Token& other );

            //metodi GETTER / SETTER
            void setTag( TOKEN_TYPE token_tag );
            TOKEN_TYPE getTag() const;
            std::string getText() const;
            void setText( std::string token_text );
        protected:
            TOKEN_TYPE tag;         //TAG del token, ovvero un'enum TOKEN_TYPE
            std::string text;       //Testo del token
    };



    /*
     *  Classe: Lexer
     *  Scopo:  Implementazione e gestione di un semplice analizzatore lessicale
     *
     */
    class Lexer {
        public:
            Lexer();
            Lexer( std::string filename_str );
            bool isSourceFileOpened();
            bool setSourceFile( std::string filename_str );

            //Analizza il file in ingresso generando una sequenza di token.
            void scan();

            //Restituisce il Vector di Token.
            std::vector<Lex::Token> getTokens() const;

            //restituisce il nome del filename
            std::string getSourceFilename() const;
        protected:
            //legge il carattere successivo del file.
            //quando si raggiunge l'EOF, readch() non fa nulla.
            void readch();
            char current;                           //carattere corrente
            std::vector<Lex::Token> tokens;         //Vector dei Token
            std::string source_code_filename;       //filename del codice Assembly
            std::fstream code;                      //File assembly in input
            Token nextToken();                      //restituisce il token successivo. Ignora commenti, NL, TAB e SPACE.
    };




    /*
     *  Classe:         SymbolTable
     *  Descrizione:    Gestione della tabella dei simboli per le label
     */
    class SymbolTable {
        public:
            //costruttore di default
            SymbolTable() {};

            //costruttore di copia
            SymbolTable( const SymbolTable& other );

            //operatore di assegnazione
            SymbolTable& operator=( const SymbolTable& other );

            //Metodi GETTER  /  SETTER
            bool addLabel( std::string text_str, size_t address_value );
            int getAddress( std::string text_str );

        private:
            std::vector<std::string> text;          //testo della label
            std::vector<size_t> address;            //indirizzo della labels

    };


    /*
     *  Classe: Parser
     *  Descrizione:    Analizzatore sintattico.
     *                  Analizza i token provenienti dal lexer
     *                  e ne verifica la sintassi. Scrive il codice
     *                  eseguibile su file.
     */
    class Parser {
        public:
            //costruttore di default
            Parser();

            //Costruttore con Vector di token
            Parser( std::vector<Lex::Token> tokens_vector );

            void outputToFile( std::string filename );

            void setTokens( std::vector<Lex::Token> tok_vec );

            //Analisi sintattica
            void parse();

        protected:
            size_t position_counter;        //posizione di scrittura attuale
            byte opcode;                    //codice operativo attuale
            int def;                        //define memory attuale

            size_t count;                   //posizione del token attuale
            SymbolTable table;              //tabella dei simboli
            std::vector<Lex::Token> tokens; //Vector di token
            std::vector<byte> program;      //programma in output
            std::vector<std::pair<size_t,std::string>> references;  //riferimenti da risolvere

            //indica se e' stato rilevato il comando HALT.
            //se alla fine dell'analisi sintattica non viene rilevato
            //si lancerà un errore.
            bool program_halt;

            //match dei costrutti e generazione del codice macchina
            void match_label(  bool obligatory = false);
            void match_command();
            void match_operand();
            void match_def();
            void match_string();
    };
}

class Assembler {
public:
    Assembler() : lexical_analyzer(), syntax_analyzer() { }
    Assembler( std::string asm_code_filename );
    bool set_asm_file( std::string asm_code_filename );
    bool is_asm_file_opened();
    void build();
    bool write_machine_code_to_file( std::string out_filename );

private:
    Lex::Lexer lexical_analyzer;
    Lex::Parser syntax_analyzer;
};

#endif // ASSEMBLER_H_INCLUDED

