#ifndef BYNARY_SEARCH_H_INCLUDED
#define BYNARY_SEARCH_H_INCLUDED
#include "quick_sort.h"
#include "searching.h"

namespace ArrayUtilities {
    template <class T>
    class BinarySearch;
}
template <class T>
class ArrayUtilities::BinarySearch : public Searching<T> {
    public:
        BinarySearch( ArrayUtilities::Array<T>* arrayPtr, T value );
        BinarySearch( ArrayUtilities::Array<T>* arrayPtr );
        BinarySearch( ArrayUtilities::Array<T> arrayValue, T value );
        BinarySearch( ArrayUtilities::Array<T> arrayValue );
        virtual void search( T value );
        virtual void search();
    private:
        int binarySearchArray( unsigned int left, unsigned int right );
};

template <class T>
ArrayUtilities::BinarySearch<T>::BinarySearch( ArrayUtilities::Array<T>* arrayPtr, T value ) : Searching<T>( arrayPtr, value ) { }

template <class T>
ArrayUtilities::BinarySearch<T>::BinarySearch( ArrayUtilities::Array<T>* arrayPtr ) : Searching<T>( arrayPtr, *new T ) { }

template <class T>
ArrayUtilities::BinarySearch<T>::BinarySearch( ArrayUtilities::Array<T> arrayValue, T value ) : Searching<T>( arrayValue, value ) { }

template <class T>
ArrayUtilities::BinarySearch<T>::BinarySearch( ArrayUtilities::Array<T> arrayValue ) : Searching<T>( arrayValue, *new T ) { }

template <class T>
void ArrayUtilities::BinarySearch<T>::search( T value ) {
    QuickSort<T> BSsort( BinarySearch<T>::arrayToAnalyze, true );
    BSsort.sortArray();
    BinarySearch<T>::position = binarySearchArray( 0, BinarySearch<T>::arrayToAnalyze->getArraySize() - 1 );

}

template <class T>
void ArrayUtilities::BinarySearch<T>::search() {
    search( BinarySearch<T>::valueToSearch );
}

template <class T>
int ArrayUtilities::BinarySearch<T>::binarySearchArray( unsigned int left, unsigned int right ) {
    if( right >= left ) {
        unsigned int middle = ( left + right ) / 2;
        if( BinarySearch<T>::arrayToAnalyze->readElement( middle ) == BinarySearch<T>::valueToSearch ) {
            return middle;
        }
        if( BinarySearch<T>::arrayToAnalyze->readElement( middle ) > BinarySearch<T>::valueToSearch ) {
            return binarySearchArray( left, middle - 1 );
        }
        return binarySearchArray( middle + 1, right );
    }
    return BinarySearch<T>::valueNotFound;
}

#endif // BYNARY_SEARCH_H_INCLUDED
