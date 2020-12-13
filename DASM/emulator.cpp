#include "emulator.h"

using namespace std;
using namespace istr_set;

Emulator::Emulator() : Emulator( 0x100 ) { };

Emulator::Emulator( std::size_t mem_size ) : memory( mem_size ) {
    A = 0;
    B = 0;
    program_counter = 0;
    opcode = 0;
    operand = 0;
    flagRegister.set(true);
}

Emulator::Emulator( std::string filename, std::size_t mem_size ) : Emulator( mem_size ) {
    loadFromFile( filename );
    //dumpMemoryToScreen( memory, memory_size );
}

std::size_t Emulator::getMemorySize() const {
    return memory.getSize();
}

bool Emulator::loadFromFile( std::string filename ) {
    char current = 0;
    size_t i = 0;
    ifstream source( filename, ios::binary | ios::in );
    if ( !source ) return false;
    while ( source ) {
        if( !isInRange<size_t>( i, 0, memory.getSize() - 1, true ) ) {
           throw( Error( E_INVALID_ACCESS_TO_MEMORY, "" ) );
        }
        source.get( current );
        memory.writeDataType<byte>( current, i );
        ++i;
    }
    memory.writeDataType<byte>( 0, i-1 );
    return true;
}

void Emulator::execute() {
    #ifdef DEBUG
    cout << "EXECUTION STARTED." << endl;
    cout << "Memory:\t\t" << memory.getSize() << " Byte." << endl;
    #endif // DEBUG_MODE
    do {
        opcode = memory.readDataType<byte>( program_counter );
        operand = memory.loadFromMemory( program_counter + 1, istr_set::getOperandSize( opcode ) );
        #ifdef DEBUG
        cout << "next istruction:" << endl;
        cout << "\tOpcode: \t\t" << hex << (int)opcode << dec << endl;
        cout << "\tOperand: \t\t" << hex << (int)operand << dec << endl;
        #endif // DEBUG_MODE
        switch ( opcode ) {
            case INP:
                #ifdef DEBUG
                cout << "INPUT: ";
                #endif // DEBUG
                cin >> A;
                program_counter++;
                break;
            case OPCODE::OUT:
                #ifdef DEBUG
                cout << "OUTPUT: ";
                #endif // DEBUG
                cout << A << endl;
                program_counter++;
                break;
            case OPCODE::SOUT:
                {
                    size_t string_size = memory.readDataType<byte>(operand);
                    #ifdef DEBUG
                    cout << "STRING OUTPUT: ";
                    #endif // DEBUG
                    for( size_t i = operand + 1; i < string_size + operand + 1; ++i ) {
                        cout << memory.readDataType<byte>( i );
                    }
                    program_counter += ADDRESS_SIZE + 1;
                }
                break;
            case OPCODE::LDA:
                A = memory.readDataType<int32_t>( operand );
                program_counter += ADDRESS_SIZE + 1;
                break;
            case OPCODE::LDB:
                B = memory.readDataType<int32_t>( operand );
                program_counter += ADDRESS_SIZE + 1;
                break;
            case OPCODE::LDAC:
                A = operand;
                program_counter += INT_SIZE + 1;
                break;
            case OPCODE::LDBC:
                B = operand;
                program_counter += INT_SIZE + 1;
                break;
            case OPCODE::STA:
                memory.writeDataType<int32_t>( A, operand );
                program_counter += ADDRESS_SIZE + 1;
                break;
            case OPCODE::STB:
                memory.writeDataType<int32_t>( B, operand );
                program_counter += ADDRESS_SIZE + 1;
                break;
            case OPCODE::ADD:
                A = A + B;
                program_counter++;
                break;
            case OPCODE::MUL:
                A = A * B;
                program_counter++;
                break;
            case OPCODE::DIV:
                if ( B == 0 ) {
                    throw( Error( E_DIVISION_BY_ZERO, "Tentativo di divisione per zero" ) );
                }
                A = A / B;
                program_counter++;
                break;
            case OPCODE::SUB:
                A = A - B;
                program_counter++;
                break;
            case OPCODE::MOD:
                A = A % B;
                program_counter++;
                break;
            case OPCODE::OR:
                A = A | B;
                program_counter++;
                break;
            case OPCODE::XOR:
                A = A ^ B;
                program_counter++;
                break;
            case OPCODE::AND:
                A = A & B;
                program_counter++;
                break;

            case OPCODE::BCM:
                A = ~A;
                program_counter++;
                break;
            case OPCODE::RSH:
                A >>= 2;
                program_counter++;
                break;
            case OPCODE::LSH:
                A <<= 2;
                program_counter++;
                break;
            case OPCODE::CMP:
                {
                    int temp = A - B;
                    if ( temp == 0 ) {
                        flagRegister.set( ZERO_FLAG, true );
                    } else {
                        flagRegister.set( ZERO_FLAG, false );
                    }
                    if ( temp < 0 ) {
                        flagRegister.set( SIGN_FLAG, true );
                    } else {
                        flagRegister.set( SIGN_FLAG, false );
                    }
                    program_counter++;
                }
                break;
            case OPCODE::JE:
                if ( flagRegister[ZERO_FLAG] ) {
                    program_counter = operand;
                } else {
                    program_counter += ADDRESS_SIZE + 1;
                }
                break;
            case OPCODE::JNE:
                if ( !flagRegister[ZERO_FLAG] ) {
                    program_counter = operand;
                } else {
                    program_counter += ADDRESS_SIZE + 1;
                }
                break;
            case OPCODE::JG:
                if ( !flagRegister[SIGN_FLAG] ) {
                    program_counter = operand;
                } else {
                    program_counter += ADDRESS_SIZE + 1;
                }
                break;
            case OPCODE::JGE:
                if ( !flagRegister[SIGN_FLAG] || flagRegister[ZERO_FLAG] ) {
                    program_counter = operand;
                } else {
                    program_counter += ADDRESS_SIZE + 1;
                }
                break;
            case OPCODE::JL:
                if ( flagRegister[SIGN_FLAG] ) {
                    program_counter = operand;
                } else {
                    program_counter += ADDRESS_SIZE + 1;
                }
                break;
            case OPCODE::JLE:
                if ( flagRegister[SIGN_FLAG] || flagRegister[ZERO_FLAG] ) {
                    program_counter = operand;
                } else {
                    program_counter += ADDRESS_SIZE + 1;
                }
                break;
            case OPCODE::JMP:
                program_counter = operand;
                break;
        }

    } while ( opcode != OPCODE::HALT );

}


void Emulator::dumpMemoryToScreen( byte* mem, std::size_t mem_size ) {
    int count = 0x0;
    cout << "=====MEMORY DUMP=====\n\n\t";
    for( int i = 0; i < 0x10; ++i ) {
        cout.width(5);
        cout << left << i;
    }
    cout << endl;
    for ( size_t i = 0; i < mem_size; ++i ) {
        if  ( i % 0x10 == 0 ) {
            cout << endl << hex << left << count << "\t";
            count += 0x10;
        }
        cout.width(4);
        cout <<std::left<< (int)mem[i] << " ";
    }
    cout << "\nMEMORY SIZE:\t\t\t" << dec << mem_size << "BYTE.\n========================================================0" << endl;
}











