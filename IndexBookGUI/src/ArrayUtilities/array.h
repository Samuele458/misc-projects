#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED
#include "random.h"

namespace ArrayUtilities {
    template <class T>
    class Array;
}

template <class T>
class ArrayUtilities::Array {

    public:

        Array( const T inputArray[], const unsigned int inputArraySize );
        Array();
        Array( const unsigned int inputArraySize );
        Array( const Array<T>& other );
        Array<T>& operator=( const Array<T>& other );
        ~Array();

        T* getArray() const;
        bool writeElement( const T ElementValue, const unsigned int position );
        bool writeElement( const T ElementValue );
        T readElement( const unsigned int position );
        T readElement();
        bool setWritingPosition( const unsigned int position );
        bool setReadingPosition( const unsigned int position );
        unsigned int getWritingPosition() const;
        unsigned int getReadingPosition() const;
        unsigned int getArraySize() const;
        T randomValue();

    protected:
        T* arrayPtr;
        unsigned int arraySize;
        unsigned int writePosition;
        unsigned int readPosition;
};

template <class T>
ArrayUtilities::Array<T>::Array( const T inputArray[], const unsigned int inputArraySize ) {
    arrayPtr = new T[ inputArraySize ];
    arraySize = inputArraySize;
    for( unsigned int countArray = 0; countArray < arraySize; ++countArray ) {
        arrayPtr[ countArray ] = inputArray[ countArray ];
    }
    writePosition = inputArraySize - 1;
    readPosition = inputArraySize - 1;
}

template <class T>
ArrayUtilities::Array<T>::Array() : Array( 10 ) { }

template <class T>
ArrayUtilities::Array<T>::Array( const unsigned int inputArraySize ) {
    arrayPtr = new T[ inputArraySize ];
    arraySize = inputArraySize;
    writePosition = 0;
    readPosition = 0;
}

template <class T>
ArrayUtilities::Array<T>::Array( const Array<T>& other ) {
    arraySize = other.arraySize;
    writePosition = other.writePosition;
    readPosition = other.readPosition;
    arrayPtr = new T[ arraySize ];
    for ( unsigned int i = 0; i < arraySize; ++i ) {
        arrayPtr[i] = other.arrayPtr[i];
    }
}

template <class T>
ArrayUtilities::Array<T>& ArrayUtilities::Array<T>::operator=( const Array<T>& other ) {
    arraySize = other.arraySize;
    writePosition = other.writePosition;
    readPosition = other.readPosition;
    arrayPtr = new T[ arraySize ];
    for ( unsigned int i = 0; i < arraySize; ++i ) {
        arrayPtr[i] = other.arrayPtr[i];
    }
    return *this;
}

template <class T>
ArrayUtilities::Array<T>::~Array() {
    //delete arrayPtr;
}

template <class T>
T* ArrayUtilities::Array<T>::getArray() const {
    return arrayPtr;
}

template <class T>
bool ArrayUtilities::Array<T>::writeElement( const T ElementValue, const unsigned int position ) {
    if ( arrayPtr != nullptr && position < arraySize ) {
        writePosition = position;
        arrayPtr[ writePosition++ ] = ElementValue;
        return true;
    } else {
        return false;
    }
}

template <class T>
bool ArrayUtilities::Array<T>::writeElement( const T ElementValue ) {
    return writeElement( ElementValue, writePosition );
}

template <class T>
T ArrayUtilities::Array<T>::readElement( const unsigned position ) {
    if ( arrayPtr != nullptr && position < arraySize ) {
        readPosition = position;
        return arrayPtr[ readPosition++ ];
    } else {
        return *new T;
    }
}

template <class T>
T ArrayUtilities::Array<T>::readElement() {
    return readElement( readPosition );
}

template <class T>
bool ArrayUtilities::Array<T>::setWritingPosition( const unsigned int position ) {
    if ( position < arraySize ) {
        writePosition = position;
        return true;
    } else {
        return false;
    }
}

template <class T>
bool ArrayUtilities::Array<T>::setReadingPosition( const unsigned int position ) {
    if ( position < arraySize ) {
        readPosition = position;
        return true;
    } else {
        return false;
    }
}

template <class T>
unsigned int ArrayUtilities::Array<T>::getWritingPosition() const {
    return writePosition;
}

template <class T>
unsigned int ArrayUtilities::Array<T>::getReadingPosition() const {
    return readPosition;
}

template <class T>
unsigned int ArrayUtilities::Array<T>::getArraySize() const {
    return arraySize;
}

template <class T>
T ArrayUtilities::Array<T>::randomValue() {
    Numbers::Random randomIndex( 0, arraySize - 1 );

    return arrayPtr[ randomIndex.getRandom() ];
}

#endif // ARRAY_H_INCLUDED
