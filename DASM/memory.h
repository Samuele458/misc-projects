/*
 * Autore:      Samuele Girgenti
 * Data:        25/12/19
 * File:        memory.h
 * Descrizione: Gestione e implementazione di un container di
 *              byte utilizzato dall'emulatore come memoria.
 */
#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED
#include <iostream>
#include <fstream>
#include "istruction_set_utilities.h"

/*
 *  Clase:          Memory
 *  Descrizione:    container di byte per la gestione della memoria
 *                  utilizzata dall'emulatore
 */
class Memory {
    public:
        Memory();                                   //Costruttore di default
        Memory( size_t size_value );                //Costruttore con la dimensione (in byte) della memoria
        Memory( const Memory& other );              //Costruttore di copia
        Memory& operator=( const Memory& other );   //operatore di assegnazione
        void resize( size_t new_size );             //ridimensionamento della memoria

        //Metodi GETTER
        size_t getSize() const;
        byte* getMemory();
        byte* getMemoryAlias();


        //gestione della memoria
        /*
         *  loadFromMemory( N, X ) :
         *  restituisce come intero N byte a partire dalla posizione X
         */
        int loadFromMemory( size_t start_position, unsigned int byte_to_load );

        //restituisce una porzione di memoria. restituisce un signolo byte se dims == 1.
        byte* readData( size_t dims, size_t start_position );

        //scrive una porzione di dati in a partire da una precisa locazione di memoria
        void writeData( byte* data, size_t data_size, size_t start_position );

        //leggere un numero di tipo T dalla memoria
        template <class T>
        T readDataType( size_t start_position ) {
            size_t data_size = sizeof(T);
            T temp = 0;
            for ( size_t i = 0; i < data_size; ++i ) {
                temp += container[start_position++];
                if( i != data_size - 1 ) {
                    temp <<= 8;
                }
            }
            return temp;
        }

        //scrivere un numero di tipo T dalla memoria
        template <class T>
        void writeDataType( T data, size_t start_position ) {
            size_t data_size = sizeof( T );
            start_position += data_size - 1;
            for( size_t i = 0; i < data_size; ++i ) {
                container[start_position--] = data % 0x100;
                data /= 0x100;
            }
        }
        ~Memory();
    private:
        byte* container;        //array di byte
        size_t size;            //dimensione dell'array
};

#endif // MEMORY_H_INCLUDED
