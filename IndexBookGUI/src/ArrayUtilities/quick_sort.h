#ifndef QUICK_SORT_H_INCLUDED
#define QUICK_SORT_H_INCLUDED
#include "sorting.h"


namespace ArrayUtilities {
    template <class T>
    class QuickSort;
}

template <class T>
class ArrayUtilities::QuickSort : public Sorting<T> {
    public:
        QuickSort( ArrayUtilities::Array<T>* arrayPtr );
        QuickSort( ArrayUtilities::Array<T>* arrayPtr, bool mode );
        QuickSort( ArrayUtilities::Array<T> arrayValue );
        QuickSort( ArrayUtilities::Array<T> arrayValue, bool mode );
        virtual void sortArray();

    protected:
        void quickSortArray( unsigned int left, unsigned int right );
};

template <class T>
ArrayUtilities::QuickSort<T>::QuickSort( ArrayUtilities::Array<T>* arrayPtr ) :  Sorting<T>( arrayPtr, true ) { }

template <class T>
ArrayUtilities::QuickSort<T>::QuickSort( ArrayUtilities::Array<T>* arrayPtr, bool mode ) :  Sorting<T>( arrayPtr, mode ) { }

template <class T>
ArrayUtilities::QuickSort<T>::QuickSort( ArrayUtilities::Array<T> arrayValue ) :  Sorting<T>( arrayValue, true ) { }

template <class T>
ArrayUtilities::QuickSort<T>::QuickSort( ArrayUtilities::Array<T> arrayValue, bool mode ) :  Sorting<T>( arrayValue, mode ) { }

template <class T>
void ArrayUtilities::QuickSort<T>::sortArray() {
    quickSortArray( 0, QuickSort<T>::arrayToSort->getArraySize() - 1 );
}


template <class T>
void ArrayUtilities::QuickSort<T>::quickSortArray( unsigned int left, unsigned int right ) {
    unsigned int i = left;
    unsigned int j = right;
    T pivot = QuickSort<T>::arrayToSort->readElement( ( left + right ) / 2 );

    while( i <= j ) {
        if ( QuickSort<T>::sortingMode ) {
            while( QuickSort<T>::arrayToSort->readElement( i ) < pivot ) {
                ++i;
            }

            while ( QuickSort<T>::arrayToSort->readElement( j ) > pivot ) {
                --j;
            }
        } else {
            while( QuickSort<T>::arrayToSort->readElement( i ) > pivot ) {
                ++i;
            }

            while ( QuickSort<T>::arrayToSort->readElement( j ) < pivot ) {
                --j;

            }
        }

        if ( i <= j ) {
            QuickSort<T>::swap( i, j );
            ++i;
            if ( j != 0 )
            --j;
        }
    }

    if ( left < j ) {
        quickSortArray( left, j );
    }
    if ( i < right ) {
        quickSortArray( i, right );
    }
}

#endif // QUICK_SORT_H_INCLUDED
