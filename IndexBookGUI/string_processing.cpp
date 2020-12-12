#include "string_processing.h"

std::string toUpperString( std::string str ) {
    for( unsigned int i = 0; i < str.size(); ++i ) {
        str[ i ] = toupper( str[ i ] );
    }
    return str;
}


std::string toLowerString( std::string str ) {
    for( unsigned int i = 0; i < str.size(); ++i ) {
        str[ i ] = tolower( str[ i ] );
    }
    return str;
}

void toUpperCharInString( std::string* str, unsigned int charPos ) {
    std::string holdStr = *str;
    if ( charPos <= str->size() ) {
        holdStr[ charPos ] = toupper( holdStr[ charPos ] );
    }
    *str = holdStr;
}
void toLowerCharInString( std::string* str, unsigned int charPos ) {
    std::string holdStr = *str;
    if ( charPos <= str->size() ) {
        holdStr[ charPos ] = toupper( holdStr[ charPos ] );
    }
    *str = holdStr;
}

int isNumber( std::string answerString ) {
    for ( unsigned int i = 0; i < answerString.size(); ++i ) {
        if ( !isdigit( answerString[ i ] )  ) {
            return -1;
        }
    }
    return std::stoi( answerString );
}
