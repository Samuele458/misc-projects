/*
 * Autore:      Samuele Girgenti
 * Data:        26/12/19
 * File:        error.h
 * Descrizione: Implementazione dei possibili errori
 *
 */
#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED
#include <iostream>
#include <string>
#include <cstdint>


//codice di ogni errore dell'emulatore e dell'assempler (lexer e parser).
enum  ERROR_ID : unsigned int {
    E_DIVISION_BY_ZERO,
    E_UNKNOWN_OPCODE,
    E_INVALID_ACCESS_TO_MEMORY,
    E_OVERFLOW,
    E_FILE_NOT_OPENED,

    P_INVALID_COMMAND,
    P_INVALID_LABEL,
    P_INVALID_OPERAND,
    P_HALT_NOT_FOUND,
    P_INVALID_SECTION,
    P_UNDEFINED_REFERENCE,
    P_MULTIPLE_DECLARATION,
    L_INVALID_SECTION,
    L_UNKNOWN_LEXEME,
    L_SYNTAX_ERROR,
    L_INVALID_ADDRESS,
    L_INVALID_CONSTANT,
    L_LEXEME_NOT_FOUND
};

/*
 *  Classe:         Error
 *  Descrizione:    classe per la gestione dei messaggi di errore
 */
class Error {
    public:
        //costruttore di default
        Error();

        //costruttore con id dell'errore e testo dell' errore in ingresso
        Error( int id, std::string text );

        //costruttore di copia
        Error( const Error& other );

        //operatore di assegnazione
        Error& operator=( const Error& other );

        //Metodi getter setter
        void setId( int id );
        void setText( std::string text );
        int getId() const;
        std::string getText() const;
    protected:
        int error_id;
        std::string error_text;
};

#endif // ERROR_H_INCLUDED
