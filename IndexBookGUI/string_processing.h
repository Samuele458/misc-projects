#ifndef STRING_PROCESSING_H_INCLUDED
#define STRING_PROCESSING_H_INCLUDED
#include <string>
#include <iostream>
#include <cstring>

std::string toUpperString( std::string str );
std::string toLowerString( std::string str );
void toUpperCharInString( std::string* str, unsigned int charPos );
void toLowerCharInString( std::string* str, unsigned int charPos );
int isNumber( std::string answerString );

#endif // STRING_PROCESSING_H_INCLUDED
