#include "person.h"

Person::Person() : Person( "NAME", "SURNAME", Date(), "123456789", "EMAIL@EMAIL.COM" ) { }

Person::Person( std::string nameStr, std::string surnameStr, Date birthDateValue, std::string telephoneStr, std::string emailStr ) {
    nameStr = toLowerString( nameStr );
    toUpperCharInString( &nameStr, 0 );
    name = nameStr;
    surnameStr = toLowerString( surnameStr );
    toUpperCharInString( &surnameStr, 0 );
    surname = surnameStr;
    birthDate = birthDateValue;
    telephone = telephoneStr;
    email = emailStr;
}

Person::Person( const Person& other ) {
    name = other.getName();
    surname = other.getSurname();
    birthDate = other.getBirthdate();
    telephone = other.getTelephone();
    email = other.getEmail();
}

Person& Person::operator=( const Person& other ) {
    name = other.getName();
    surname = other.getSurname();
    birthDate = other.getBirthdate();
    telephone = other.getTelephone();
    email = other.getEmail();
    return *this;
}


void Person::setName( std::string nameStr ) {
    nameStr = toLowerString( nameStr );
    toUpperCharInString( &nameStr, 0 );
    name = nameStr;
}

std::string Person::getName() const {
    return name;
}

void Person::setSurname( std::string surnameStr ) {
    surnameStr = toLowerString( surnameStr );
    toUpperCharInString( &surnameStr, 0 );
    surname = surnameStr;
}

std::string Person::getSurname() const {
    return surname;
}

void Person::setBirthdate( unsigned int dayValue, unsigned int monthValue, unsigned int yearValue ) {
    birthDate.setDay( dayValue );
    birthDate.setMonth( monthValue );
    birthDate.setYear( yearValue );
}

void Person::setBirthdate( Date birthdateValue ) {
    birthDate = birthdateValue;
}

Date Person::getBirthdate() const {
    return birthDate;
}

void Person::setTelephone( std::string telephoneStr ) {
    telephone = telephoneStr;
}

std::string Person::getTelephone() const {
    return telephone;
}

void Person::setEmail( std::string emailStr ) {
    email = emailStr;
}

std::string Person::getEmail() const {
    return email;
}

bool operator==( const Person& x, const Person& y ) {
    bool result = true;
    Date xbirth = x.getBirthdate();
    Date ybirth = y.getBirthdate();
    switch ( Person::ParameterToCompare ) {
        case NAME:
            result = x.getName() == y.getName();
            break;
        case SURNAME:
            result = x.getSurname() == y.getSurname();
            break;
        case BIRTHDATE:
            result = ( xbirth == ybirth );
            break;
        case TELEPHONE:
            result = x.getTelephone() == y.getTelephone();
            break;
        case EMAIL:
            result = x.getEmail() == y.getEmail();
            break;
    }
    return result;
}

bool operator<( const Person& x, const Person& y ) {
    bool result = true;
    Date xbirth = x.getBirthdate();
    Date ybirth = y.getBirthdate();
    switch ( Person::ParameterToCompare ) {
        case NAME:
            result = x.getName() < y.getName();
            break;
        case SURNAME:
            result = x.getSurname() < y.getSurname();
            break;
        case BIRTHDATE:
            result = xbirth < ybirth;
            break;
        case TELEPHONE:
            result = x.getTelephone() < y.getTelephone();
            break;
        case EMAIL:
            result = x.getEmail() < y.getEmail();
            break;
    }
    return result;
}

bool operator>( const Person& x, const Person& y ) {
    return y < x;
}

bool operator<=( const Person& x, const Person& y ) {
    return ( x < y ) || ( x == y );
}

bool operator>=( const Person& x, const Person& y ) {
    return ( x > y ) || ( x == y );
}


comparisonParameter Person::ParameterToCompare = NAME;
