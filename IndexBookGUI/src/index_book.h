#ifndef INDEX_BOOK_H_INCLUDED
#define INDEX_BOOK_H_INCLUDED
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <string>
#include "person.h"
#include "array_utilities.h"
#include "string_processing.h"



class IndexBook {
    public:
        IndexBook();
        IndexBook( ArrayUtilities::Array<Person> PeopleArray );
        IndexBook( std::string inputFileName );
        IndexBook( const IndexBook& other );
        IndexBook& operator=( const IndexBook& other );
        void save( std::string outputFileName );

        void addPerson( Person value, int position = -1 );
        unsigned int getPeopleNumber();
        void sortIndex( bool mode );
        int searchPerson( std::string nameStr, std::string surnameStr );
        Person getPerson( unsigned int position );
        ArrayUtilities::Array<Person> getPersonArray();
        bool removePerson( unsigned int position );

    protected:
        ArrayUtilities::Array<Person> People;
        unsigned int PeopleSize;
};

#endif // INDEX_BOOK_H_INCLUDED
