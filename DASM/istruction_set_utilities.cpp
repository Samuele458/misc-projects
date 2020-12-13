#include "istruction_set_utilities.h"

using namespace std;

int istr_set::getCommandOpcode( std::string command_text ) {
    vector<string> commands_list = {"HLT",
                                    "INP",
                                    "OUT",
                                    "SOUT",
                                    "LDAC",
                                    "LDBC",
                                    "LDA",
                                    "LDB",
                                    "STA",
                                    "STB",
                                    "ADD",
                                    "MUL",
                                    "DIV",
                                    "SUB",
                                    "MOD",
                                    "OR",
                                    "XOR",
                                    "AND",
                                    "BCM",
                                    "RSH",
                                    "LSH",
                                    "CMP",
                                    "JE",
                                    "JNE",
                                    "JG",
                                    "JGE",
                                    "JL",
                                    "JLE",
                                    "JMP" };
    std::vector<string>::iterator it = std::find( commands_list.begin(), commands_list.end(), command_text );
    if ( it == commands_list.end() ) {
        return NOT_FOUND;
    }
    return std::distance( commands_list.begin(), it );
}

std::size_t istr_set::getOperandSize( byte op ) {
    int dims[istr_set::OPCODE::ISTRUCTION_SET_SIZE] = {   0,
                                                0,
                                                0,
                                                2,
                                                4,
                                                4,
                                                2,
                                                2,
                                                2,
                                                2,
                                                0,
                                                0,
                                                0,
                                                0,
                                                0,
                                                0,
                                                0,
                                                0,
                                                0,
                                                0,
                                                0,
                                                0,
                                                2,
                                                2,
                                                2,
                                                2,
                                                2,
                                                2,
                                                2   };
    if ( op > 0 && op < istr_set::OPCODE::ISTRUCTION_SET_SIZE )
        return dims[op-1];
    else throw( 1 );
}

int istr_set::getSectionCode( std::string section_text ) {
    vector<string> section_list = { ".PROGRAM",
                                    ".DATA" };
    std::vector<string>::iterator it = std::find( section_list.begin(), section_list.end(), section_text );
    if ( it == section_list.end() ) {
        return NOT_FOUND;
    }
    return std::distance( section_list.begin(), it );
}


int istr_set::getDefCode( std::string def_text ) {
    vector<string> def_list = { "DB",
                                "DW",
                                "DD" };
    std::vector<string>::iterator it = std::find( def_list.begin(), def_list.end(), def_text );
    if ( it == def_list.end() ) {
        return NOT_FOUND;
    }
    return std::distance( def_list.begin(), it );
}
