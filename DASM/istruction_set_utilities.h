/*
 * Autore:      Samuele Girgenti
 * Data:        25/12/19
 * File:        istruction_set_utilities.h
 * Descrizione: Informazioni sull'istruction set
 *
 */

#ifndef ISTRUCTION_SET_UTILITIES_H_INCLUDED
#define ISTRUCTION_SET_UTILITIES_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

//Valore massimo per un'intero senza segno a 16 bit.
#define MAX_UINT_16BIT 65535

//Valore massimo per un'intero con segno a 32 bit.
#define MAX_INT_32BIT 2147483647

//Valore minimo per un'intero con segno a 32 bit.
#define MIN_INT_32BIT (-MAX_INT_32BIT-1)


//COMANDO/DEF/SECTION non trovata
#define COMMAND_NOT_FOUND -1
#define NOT_FOUND -1

//byte: minimma unità indirizzabile dall'emulatore.
//per rappresentare il byte si utilizza un char senza segno
//(unsigned per evitare problemi con il COMPLEMENTO A 2)
typedef unsigned char byte;


//namespace per le informazioni del SET ISTRUZIONI
namespace istr_set {
    //Restituisce l'Id dell'opcode della stringa passata alla funzione
    int getCommandOpcode( std::string command_text );

    //Restituisce l'Id del section code della stringa passata alla funzione
    int getSectionCode( std::string section_text );

    //Restituisce l'Id del def code della sctrina passata alla funzione
    int getDefCode( std::string def_text );

    //Restituisce la dimensione dell'operando dell'opcode passato alla funzione
    std::size_t getOperandSize( byte op );

    //codici operativi
    enum OPCODE {
        HALT = 0x1,
        INP,
        OUT,
        SOUT,
        LDAC,
        LDBC,
        LDA,
        LDB,
        STA,
        STB,
        ADD,
        MUL,
        DIV,
        SUB,
        MOD,
        OR,
        XOR,
        AND,
        BCM,
        RSH,
        LSH,
        CMP,
        JE,
        JNE,
        JG,
        JGE,
        JL,
        JLE,
        JMP,
        ISTRUCTION_SET_SIZE
    };

    //Sezioni del programma (program e data)
    enum SECTION {
        PROGRAM,
        DATA,
        SECTIONS_SIZE
    };

    //Memory define
    enum DEF {
        DB,             //DEFINE BYTE
        DW,             //DEFINE WORD
        DD,             //DEFINE DOUBLE WORD
        DEF_SIZE
    };
}


#endif // ISTRUCTION_SET_UTILITIES_H_INCLUDED

