#include "index_book.h"

IndexBook::IndexBook() : IndexBook( *new ArrayUtilities::Array<Person> ) { }

IndexBook::IndexBook( ArrayUtilities::Array<Person> PeopleArray ) {
    People = PeopleArray;
    PeopleSize = PeopleArray.getArraySize();
}

IndexBook::IndexBook( std::string inputFileName ) {
    PeopleSize = 0;
    std::ifstream iFile( inputFileName );
    std::string currentLineStr;
    std::string intermediate;
    People.setWritingPosition( 0 );
    ArrayUtilities::Array<std::string> informationsArray( 7 );
    ArrayUtilities::Array<Person> temp( 100 );

    if( iFile.is_open() ) {
        currentLineStr = "";
        while ( getline( iFile, currentLineStr ) ) {
            if ( currentLineStr != "" ) {
                std::stringstream check( currentLineStr );
                informationsArray.writeElement( intermediate );
                for ( unsigned int i = 0; i < 7; ++i ) {
                    getline( check, intermediate, '|' );
                    informationsArray.writeElement( intermediate, i);
                }
                temp.writeElement( Person( informationsArray.readElement( 0 ), informationsArray.readElement( 1 ), Date( std::stoi( informationsArray.readElement( 2 ) ), std::stoi( informationsArray.readElement( 3 ) ), std::stoi( informationsArray.readElement( 4 ) ) ),informationsArray.readElement( 5 ), informationsArray.readElement( 6 ) ) );

                ++PeopleSize;
            }
        }
        People = *new ArrayUtilities::Array<Person>( PeopleSize );
        for ( unsigned int i = 0; i < PeopleSize; ++i ) {
            People.writeElement(  temp.readElement( i ), i );
        }
        iFile.close();
    } else {
        People = *new ArrayUtilities::Array<Person>( PeopleSize );
    }
}

IndexBook::IndexBook( const IndexBook& other ) {
    People = other.People;
    PeopleSize = other.PeopleSize;
}

IndexBook& IndexBook::operator=( const IndexBook& other ) {
    People = other.People;
    PeopleSize = other.PeopleSize;
    return *this;
}

void IndexBook::save( std::string outputFileName ) {
    std::ofstream oFile( outputFileName, std::ios_base::out | std::ios_base::trunc );
    if( oFile.is_open() ) {
        for ( unsigned int i = 0; i < PeopleSize; ++i ) {
            oFile << People.readElement( i ).getName() << "|" << People.readElement( i ).getSurname() << "|" << People.readElement( i ).getBirthdate().getDay() << "|" << People.readElement( i ).getBirthdate().getMonth() << "|" << People.readElement( i ).getBirthdate().getYear() << "|" << People.readElement( i ).getTelephone() << "|" << People.readElement( i ).getEmail() << "\n";
        }
        oFile.close();
    }
}

void IndexBook::addPerson( Person value, int position ) {
    if ( position == -1 ) {
        PeopleSize++;
        ArrayUtilities::Array<Person> hold;
        hold = People;
        People = *new ArrayUtilities::Array<Person>( PeopleSize );
        for ( unsigned int i = 0; i < PeopleSize - 1; ++i ) {
            People.writeElement( hold.readElement( i ), i );
        }
        People.writeElement( value, PeopleSize - 1 );
    } else {
        People.writeElement( value, static_cast<unsigned int>( position ) );
    }
}

unsigned int IndexBook::getPeopleNumber() {
    return PeopleSize;
}

void IndexBook::sortIndex( bool mode ) {
    ArrayUtilities::QuickSort<Person> QuickSortIndex( People, mode );
    QuickSortIndex.sortArray();
    People = QuickSortIndex.getArrayValue();
}

int IndexBook::searchPerson( std::string nameStr, std::string surnameStr ) {
    nameStr = toLowerString( nameStr );
    toUpperCharInString( &nameStr, 0 );
    surnameStr = toLowerString( surnameStr );
    toUpperCharInString( &surnameStr, 0 );

    ArrayUtilities::Array<bool> nameCheck( PeopleSize );
    ArrayUtilities::Array<bool> surnameCheck( PeopleSize );
    ArrayUtilities::Array<bool> resultCheck( PeopleSize );

    for ( unsigned int i = 0; i < PeopleSize; ++i ) {
        if ( nameStr == People.readElement( i ).getName() ) {
            nameCheck.writeElement( true, i );
        } else {
            nameCheck.writeElement( false, i );
        }
        if ( surnameStr == People.readElement( i ).getSurname() ) {
            surnameCheck.writeElement( true, i );
        } else {
            surnameCheck.writeElement( false, i );
        }
        resultCheck.writeElement( nameCheck.readElement( i ) && surnameCheck.readElement( i ) );
        if ( resultCheck.readElement( i ) == true ) {
            return ( static_cast<int> ( i ) );
        }
    }
    return -1;



    /*
    ArrayUtilities::Array<std::string> PersonNames( PeopleSize );
    ArrayUtilities::Array<std::string> PersonSurnames( PeopleSize );
    Person::ParameterToCompare = NAME;
    sortIndex( true );

    for ( unsigned int i = 0; i < PeopleSize; ++i ) {
        PersonNames.writeElement( People.readElement( i ).getName() , i );
    }
    Person::ParameterToCompare = SURNAME;
    sortIndex( true );
    for ( unsigned int i = 0; i < PeopleSize; ++i ) {
        PersonSurnames.writeElement( People.readElement( i ).getSurname() , i );
    }
    ArrayUtilities::BinarySearch<std::string> searchName( PersonNames, nameStr );
    ArrayUtilities::BinarySearch<std::string> searchSurname( PersonSurnames, surnameStr );
    searchName.search();
    searchSurname.search();

    if ( searchName.getPos() != -1 && searchSurname.getPos() != -1 ) {
        if ( People.readElement( searchSurname.getPos() ).getName() == nameStr ) {
            return searchSurname.getPos();
        }
    }

    return -1; */
}

Person IndexBook::getPerson( unsigned int position ) {
    if ( position <= PeopleSize ) {
        return People.readElement( position );
    } else {
        return Person();
    }
}

ArrayUtilities::Array<Person> IndexBook::getPersonArray() {
    return People;
}

bool IndexBook::removePerson( unsigned int position ) {
    if ( position <= People.getArraySize() ) {
        ArrayUtilities::Array<Person> holdPeople( People.getArraySize() - 1 );
        holdPeople.setWritingPosition( 0 );
        for( unsigned int i = 0; i < People.getArraySize(); ++i ) {
            if ( i != position ) {
                holdPeople.writeElement( People.readElement( i ) );
            }
        }
        People = holdPeople;
        PeopleSize = People.getArraySize();
        return true;
    } else {
        return false;
    }
}
