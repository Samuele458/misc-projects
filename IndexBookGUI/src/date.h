#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED
#include <iostream>

class Date {
    public:
        Date();
        Date( unsigned int dayValue, unsigned int monthValue, unsigned int yearValue );
        Date( const Date& other );
        Date& operator=( const Date& other );

        void setDay( unsigned int dayValue );
        unsigned int getDay() const;
        void setMonth( unsigned int monthValue );
        unsigned int getMonth() const ;
        void setYear( unsigned int yearValue );
        unsigned int getYear() const;
        std::string getStringDate();

    protected:
        unsigned int day;
        unsigned int month;
        unsigned int year;
};

std::ostream& operator<<(std::ostream& output, const Date& d );

bool operator==( Date& x, Date& y );
bool operator>( Date& x, Date& y );
bool operator<( Date& x, Date& y );
bool operator>=( Date& x, Date& y );
bool operator<=( Date& x, Date& y );


#endif // DATE_H_INCLUDED
