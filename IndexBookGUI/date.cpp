#include <iostream>
#include "date.h"

Date::Date() : Date( 1, 1, 1900 ) { }

Date::Date( unsigned int dayValue, unsigned int monthValue, unsigned int yearValue ) {
    day = dayValue;
    month = monthValue;
    year = yearValue;
}

Date& Date::operator=( const Date& other ) {
    day = other.getDay();
    month = other.getMonth();
    year = other.getYear();
    return *this;
}

Date::Date( const Date& other ) {
    day = other.getDay();
    month = other.getMonth();
    year = other.getYear();
}

void Date::setDay( unsigned int dayValue ) {
    day = dayValue;
}

unsigned int Date::getDay() const {
    return day;
}

void Date::setMonth( unsigned int monthValue ) {
    month = monthValue;
}

unsigned int Date::getMonth() const {
    return month;
}

void Date::setYear( unsigned int yearValue ) {
    year = yearValue;
}

unsigned int Date::getYear() const {
    return year;
}

std::string Date::getStringDate() {
    std::string dateValue = std::to_string(day) + " / " + std::to_string( month ) + " / " + std::to_string( year );
    return dateValue;
}

std::ostream& operator<<(std::ostream& output, const Date &d ) {
    std::string strMonth = "";
    if ( d.getMonth() < 10 ) {
        strMonth = "0";
    }
    std::cout << d.getDay() << " / " << strMonth << d.getMonth() << " / " << d.getYear();
    return output;
}

bool operator==( Date& x, Date& y ) {
    return x.getDay() == y.getDay() && x.getMonth() == y.getMonth() && x.getYear() == y.getYear();
}

bool operator>( Date& x, Date& y ) {
    if ( x.getYear() > y.getYear() ) {
        return true;
    } else if ( x.getYear() == y.getYear() ) {
        if ( x.getMonth() > y.getMonth() ) {
            return true;
        } else if ( x.getMonth() == y.getMonth() ) {
            if ( x.getDay() > y.getDay() ) {
                return true;
            }
        }
    }
    return false;
}

bool operator<( Date& x, Date& y ) {
    return y > x;
}

bool operator>=( Date& x, Date& y ) {
    return ( x > y ) || ( x == y );
}

bool operator<=( Date& x, Date& y ) {
    return ( x < y ) || ( x == y );
}
