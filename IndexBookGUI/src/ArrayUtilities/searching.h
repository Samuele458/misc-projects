#ifndef SEARCHING_H_INCLUDED
#define SEARCHING_H_INCLUDED
#include "array.h"

namespace ArrayUtilities {
    template <class T>
    class Searching;
}

template <class T>
class ArrayUtilities::Searching {
    public:
        Searching( ArrayUtilities::Array<T>* arrayPtr, T value );
        Searching( ArrayUtilities::Array<T>* arrayPtr );
        Searching( ArrayUtilities::Array<T> arrayValue, T value );
        Searching( ArrayUtilities::Array<T> arrayValue );

        ~Searching() { }

        void setValueToSearch( T value );
        virtual void search( T value ) { }
        virtual void search();
        int getPos();
        static const int valueNotFound = -1;
    protected:
        T valueToSearch;
        int position;
        ArrayUtilities::Array<T>* arrayToAnalyze;

};

template <class T>
ArrayUtilities::Searching<T>::Searching( ArrayUtilities::Array<T>* arrayPtr, T value ) {
    arrayToAnalyze = arrayPtr;
    valueToSearch = value;
    position = valueNotFound;
}

template <class T>
ArrayUtilities::Searching<T>::Searching( ArrayUtilities::Array<T>* arrayPtr ) : Searching( arrayPtr, new T ) { }

template <class T>
ArrayUtilities::Searching<T>::Searching( ArrayUtilities::Array<T> arrayValue, T value ) {
    arrayToAnalyze = new ArrayUtilities::Array<T>;
    *arrayToAnalyze = arrayValue;
    valueToSearch = value;
    position = valueNotFound;
}

template <class T>
ArrayUtilities::Searching<T>::Searching( ArrayUtilities::Array<T> arrayValue ) : Searching( arrayValue, new T ) { }

template <class T>
void ArrayUtilities::Searching<T>::setValueToSearch( T value ) {
    valueToSearch = value;
}

template <class T>
void ArrayUtilities::Searching<T>::search() {
    search( valueToSearch );
}

template <class T>
int ArrayUtilities::Searching<T>::getPos() {
    return position;
}

#endif // SEARCHING_H_INCLUDED
