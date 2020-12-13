#ifndef SORTING_H_INCLUDED
#define SORTING_H_INCLUDED
#include "array.h"

namespace ArrayUtilities {
    template <class T>
    class Sorting;
}

template <class T>
class ArrayUtilities::Sorting {
    public:
        Sorting( ArrayUtilities::Array<T>* arrayPtr );
        Sorting( ArrayUtilities::Array<T>* arrayPtr, bool mode );
        Sorting( ArrayUtilities::Array<T> arrayValue );
        Sorting( ArrayUtilities::Array<T> arrayValue, bool mode );

        ~Sorting() { }
        ArrayUtilities::Array<T> getArrayValue() const;
        ArrayUtilities::Array<T>* getArrayPtr() const;
        void setSortingMode( bool mode );
        virtual void sortArray() { }
        bool isSorted();
    protected:
        bool sortingMode;
        ArrayUtilities::Array<T>* arrayToSort;
        void swap( unsigned int firstElement, unsigned int secondElement );

};

template <class T>
ArrayUtilities::Sorting<T>::Sorting(  ArrayUtilities::Array<T>* arrayPtr ) : Sorting( arrayPtr, true ) { }

template <class T>
ArrayUtilities::Sorting<T>::Sorting( ArrayUtilities::Array<T>* arrayPtr, bool mode ) {
    arrayToSort = arrayPtr;
    sortingMode = mode;
}

template <class T>
ArrayUtilities::Sorting<T>::Sorting(  ArrayUtilities::Array<T> arrayValue ) : Sorting( arrayValue, true ) { }

template <class T>
ArrayUtilities::Sorting<T>::Sorting( ArrayUtilities::Array<T> arrayValue, bool mode ) {
    arrayToSort = new ArrayUtilities::Array<T>;
    *arrayToSort = arrayValue;
    sortingMode = mode;
}

template <class T>
ArrayUtilities::Array<T> ArrayUtilities::Sorting<T>::getArrayValue() const {
    return *arrayToSort;
}

template <class T>
ArrayUtilities::Array<T>* ArrayUtilities::Sorting<T>::getArrayPtr() const {
    return arrayToSort;
}

template <class T>
void ArrayUtilities::Sorting<T>::setSortingMode( bool mode ) {
    sortingMode = mode;
}

template <class T>
void ArrayUtilities::Sorting<T>::swap( unsigned int firstElement, unsigned int secondElement ) {
    T hold;
    hold = arrayToSort->readElement( firstElement );
    arrayToSort->writeElement( arrayToSort->readElement( secondElement ), firstElement );
    arrayToSort->writeElement( hold , secondElement );

}

template <class T>
bool ArrayUtilities::Sorting<T>::isSorted() {
    bool correctOrder = true;
    unsigned int counter = 0;
    while( correctOrder && counter < arrayToSort->getArraySize() - 1) {
        if ( sortingMode ) {
            if ( arrayToSort->readElement( counter ) > arrayToSort->readElement( counter + 1) ) {
                correctOrder = false;
            }
        } else {
            if ( arrayToSort->readElement( counter ) < arrayToSort->readElement( counter + 1) ) {
                correctOrder = false;
            }

        }
        ++counter;
    }
    return correctOrder;
}

#endif // SORTING_H_INCLUDED
