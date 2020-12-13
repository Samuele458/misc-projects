# DASM (Dummy Assembler)
DASM (Dummy Assembler) is a fictitious assembler for a hypothetical CPU. The assembler receives the assembly code from a file and transforms it into a hypothetical machine language which is interpreted and executed by an emulator.

## "CPU" Specification

There are just two 32-bit registers: **A** and **B**. All data manipulation has to be done between A, B, and memory.

There can be 2 sections in each DASM file:
 -   .PROGRAM: Contains the instructions
 -   .DATA: contains string or specification declarations

## Instructions set
|INSTRUCION|DESCRIPTION|
|--|--|
|  HLT| End of execution |
|  OUT   |  Output of A |
|  SOUT  |  Output of a string |
|  LDAC  |  Loading in A of an immediate value |
|  LDBC  |  Loading in B of an immediate value |
|  LDA   |  Loading A from memory |
|  LDB|   Loading B from memory |
|  STA   |  Storage of A in memory |
|  STB   |  Storage of B in memory |
|  ADD   |  Sum between A and B |
|  MUL   |  Multiplication of A by B |
|  DIV   |  Division between A and B |
|  SUB   |  Subtraction between A and B |
|  MOD   |  Rest of integer division of A by B |
|  OR    |  OR bitwise between A and B |
|  XOR   |  XOR bitwise between A and B |
|  AND   |  AND bitwise between A and B |
|  BCM   |  Complement of A |
|  RSH   |  Bit shift to the right of A |
|  LSH   |  Bit shift to the left of A |
|  CMP   |  Comparison between A and B to set the FLAG |
|  JE    |  A == B |
|  JNE   |  A != B |
|  JG    |  A > B |
|  JGE   |   A >= B |
|  JL    |   A < B |
|  JLE   |    A <= B |
|  JMP   |   Unconditional jump |


## How to use DASM

