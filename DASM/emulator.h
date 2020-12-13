/*
 *  Autore: Samuele Gurgenti
 *  Data: 15/12/2019  -  15:50
 *  Descrizione: Emulatore di una cpu.
 */
#ifndef EMULATOR_H_INCLUDED
#define EMULATOR_H_INCLUDED
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <bitset>
#include <iomanip>
#include "istruction_set_utilities.h"
#include "memory.h"
#include "error.h"
#include "general.h"

#define OPCODE_SIZE 1
#define INT_SIZE 4
#define ADDRESS_SIZE 2


//ID delle flag del FLAG REGISTER
enum FLAG {
    SIGN_FLAG = 0,
    ZERO_FLAG,
    OVERFLOW_FLAG,
    FLAG_NUM
};

//errori da gestire
enum class EMULATOR_ERROR {
    UNKNOWN_OPCODE,
    ZERO_DIVISION,
    INVALID_MEMORY_ACCESS,
    FILE_NOT_OPENED
};

/*
 *  Classe:         Emulator
 *  Descrizione:    Implementazione e gestione di
 *                  un emulatore di una semplice cpu
 */
class Emulator {
    public:
        //Costruttore di default
        Emulator();

        //Costruttore con la dimensione della memoria dell'emulatore
        Emulator( std::size_t mem_size );

        //costruttore con nome dell'eseguibile e dimensione della memoria
        Emulator( std::string filename, std::size_t mem_size = 0x100 );

        //metodo GETTER per la dimensione della memoria
        std::size_t getMemorySize() const;

        //carica le istruzioni da file eseguibile
        bool loadFromFile( std::string filename );

        //esegue le istruzioni presenti in memoria
        void execute();

        //dump della memoria a schermo
        static void dumpMemoryToScreen( byte* memory, std::size_t mem_size );
    private:
        Memory memory;                                  //memoria dell'emulatore
        int32_t A;                                      //Registro A
        int32_t B;                                      //Registro B
        unsigned int program_counter;                   //Registro program counter
        byte opcode;                                    //codice oparativo attuale
        int operand;                                    //operando attuale
        std::bitset<FLAG::FLAG_NUM> flagRegister;       //Flag register
        void debugScreen();                             //debug --DA RIMUOVERE O SISTEMARE--
};

#endif // EMULATOR_H_INCLUDED
