#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED
#include "date.h"
#include "string_processing.h"

enum comparisonParameter{ NAME, SURNAME, BIRTHDATE, TELEPHONE, EMAIL };

class Person {
    public:
        Person();
        Person( std::string nameStr, std::string surnameStr, Date birthDateValue, std::string telephoneStr, std::string emailStr );
        Person( const Person& other );
        Person& operator=( const Person& other );

        void setName( std::string nameStr );
        std::string getName() const;
        void setSurname( std::string surnameStr );
        std::string getSurname() const;
        void setBirthdate( unsigned int dayValue, unsigned int monthValue, unsigned int yearValue );
        void setBirthdate( Date birthdateValue );
        Date getBirthdate() const;
        void setTelephone( std::string telephoneStr );
        std::string getTelephone() const;
        void setEmail( std::string emailStr );
        std::string getEmail() const;
        static comparisonParameter ParameterToCompare;
    private:
        std::string name;
        std::string surname;
        Date birthDate;
        std::string telephone;
        std::string email;

};

bool operator==( const Person& x, const Person& y );
bool operator<( const Person& x, const Person& y );
bool operator>( const Person& x, const Person& y );
bool operator<=( const Person& x, const Person& y );
bool operator>=( const Person& x, const Person& y );


#endif // PERSON_H_INCLUDED
