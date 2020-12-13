#include "memory.h"

Memory::Memory() : Memory( 0x100 ) { }

Memory::Memory( size_t size_value ) {
    size = size_value;
    container = new byte[size];
}

Memory::Memory( const Memory& other ) {
    size = other.size;
    container = new byte[size];
    for ( size_t i = 0; i < size; ++i ) {
        container[i] = other.container[i];
    }
}

Memory& Memory::operator=( const Memory& other ) {
    size = other.size;
    container = new byte[size];
    for ( size_t i = 0; i < size; ++i ) {
        container[i] = other.container[i];
    }
    return *this;
}

void Memory::resize( size_t new_size ) {
    size = new_size;
    byte* hold = new byte[size];
    for( size_t i = 0; i < size; ++i ) {
        hold[i] = container[i];
    }
    delete[] container;
    container = hold;
}

byte* Memory::getMemory() {
    return container;
}

byte* Memory::getMemoryAlias() {
    byte* hold = new byte[size];
    for( size_t i = 0; i < size; ++i ) {
        hold[i] = container[i];
    }
    return hold;
}

int Memory::loadFromMemory( size_t start_position, unsigned int byte_to_load ) {
    int temp = 0;
    for (size_t i = 0; i < byte_to_load; ++i ) {
        temp += container[start_position++];
        if( i != byte_to_load - 1 ) {
            temp <<= 8;
        }
    }
    return temp;
}

size_t Memory::getSize() const {
    return size;
}

byte* Memory::readData( size_t dims, size_t start_position ) {
    byte* temp = new byte[dims];
    for ( size_t i = 0; i < dims; ++i ) {
        temp[i] = container[start_position+i];
    }
    return temp;
}

void Memory::writeData( byte* data, size_t data_size, size_t start_position ) {
    for ( size_t i = 0; i < data_size; ++i ) {
        container[start_position + i] = data[i];
    }
}

Memory::~Memory() {
    delete[] container;
}

