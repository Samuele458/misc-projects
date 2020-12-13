/*
 * Autore:      Samuele Girgenti
 * Data:        26/12/19
 * File:        general.h
 * Descrizione: Funzioni generiche
 *
 */
#ifndef GENERAL_H_INCLUDED
#define GENERAL_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>
#include <cmath>

/*
 * isInRange(   value,          Valore da verificare
 *              first_limit,    Limite inferiore dell'intervallo
 *              last limit,     Limite superiore dell'intervallo
 *              mode            true = estremi inclusi, false = estremi esclusi
 *          )
 */
template <class T>
bool isInRange( T value, T first_limit, T last_limit, bool mode = false ) {
    if( mode )
        return ( value >= first_limit ) && ( value <= last_limit );
    else
        return ( value > first_limit ) && ( value < last_limit );
}

std::pair<bool,int> getValue( std::string number );

std::string replace_string( std::string string_to_modify, char char_to_replace, std::string replace_with );

#endif // GENERAL_H_INCLUDED
