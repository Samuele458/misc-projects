dasm: assembler.o emulator.o error.o general.o interface.o memory.o istruction_set_utilities.o main.o
	g++ assembler.o emulator.o error.o general.o interface.o memory.o istruction_set_utilities.o main.o -o dasm

assembler.o : assembler.cpp
	g++ -c assembler.cpp

emulator.o : emulator.cpp
	g++ -c emulator.cpp

error.o : error.cpp
	g++ -c error.cpp

general.o : general.cpp
	g++ -c general.cpp

interface.o : interface.cpp
	g++ -c interface.cpp

istruction_set_utilities.o : istruction_set_utilities.cpp
	g++ -c istruction_set_utilities.cpp


memory.o : memory.cpp
	g++ -c memory.cpp

main.o : main.cpp
	g++ -c main.cpp
