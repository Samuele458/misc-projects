#include "general.h"

using namespace std;

std::pair<bool,int> getValue( std::string number ) {
    bool correct = true;
    //bool present;
    size_t last_pos;
    int num = 0;

//    bool id_base = true;
    vector<char> alpha_dec = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    vector<char> alpha_hex = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    vector<char> alpha_oct = { '0', '1', '2', '3', '4', '5', '6', '7' };
    vector<char> alpha_bin = { '0', '1' };
    vector<char> alphabet;
    //int base = 10;

    //porto tutte le eventuali lettere in maiuscole
    for( size_t i = 0; i < number.size(); ++i ) {
        if( isalpha( number[i] ) ) {
            number[i] = toupper( number[i] );
        }
    }

    //verificare che l'ultimo sia D, B, H, o O
    last_pos = number.size() - 2;
    switch ( number[number.size()-1] ) {
        case 'D':
            //base = 10;
            alphabet = alpha_dec;
            break;
        case 'O':
            //base = 8;
            alphabet = alpha_oct;
            break;
        case 'B':
            //base = 2;
            alphabet = alpha_bin;
            break;
        case 'H':
            //base = 16;
            alphabet = alpha_hex;
            break;
        default:
            alphabet = alpha_dec;
            last_pos =  number.size() - 1;
    }

    std::vector<char>::iterator it;
    for( size_t i = 0; i <= last_pos; ++i ) {
        if( std::find( alphabet.begin(), alphabet.end(), number[i] ) == alphabet.end() ) {
            correct = false;
        }
        if( correct ) {
            num = num * alphabet.size() + ( number[i] -'0');
        }
    }
    return std::pair<bool,int>(correct,num);
}

std::string replace_string( std::string string_to_modify, char char_to_replace, std::string replace_with ) {
    std::string hold = "";

    for( size_t i = 0; i < string_to_modify.size(); ++i ) {
        if( string_to_modify.at( i ) == char_to_replace ) {
            hold += replace_with;
        } else {
            hold += string_to_modify.at(i);
        }
    }

    return hold;
}


//int getValue( std::string number );
