# CPU
Two main parts:
1. **Control Unit** (a finite state machine)
2. **Data Path**, comprised of:
    - arithmetic logic unit (ALU)
    - register i.e. data

Control unit sends signals to the data path to control and manipulate data and then uses status signals from the data path to decide which states to traverse in its FSM.

Stuff to do encoded in instructions, each instruction being carried out in 3 steps by the control unit: **fetch**, **decode**, **execute**.

## Data path
- comprised of the registers + ALU
- controlled by the **control unit**

### Registers
- instruction register: holds current binary code of the instruction to be executed by the control unit FSM
- memory address register: puts stuff on the address bus such that you can read stuff from memory
- program counter: holds the address of the current instruction that's being executed in program memory; gets incremented through the program's memory as instructions are executed
- general purpose registers: move stuff from memory to them and from them into the memory while the program is being executed
- condition code register: holds status codes providing info about the state of the CPU:
    - holds negative or zero flags
    - two's complement overflow flags
    - carry flags
    - interrupt flags
    - low-power mode flags
    - ...(NZVC flags)

### ALU
- does all addition, subtraction + boolean logic operations

# Memory
- holds data + program memory
- maps I/O ports such that everything can be accessed from the same base address, all present in the **memory map**
    - 8bit CPU, so 8 bits to represent any address, so 256 addressed in total
        - each address points to another 8 bit object, so an example of a memory map would be:
            - **program memory**:: x00 --> x7F: 128 * 8 bits = 128 bytes
            - **data memory**:: x80 --> xDF: 96 * 8 bits = 96 bytes
            - **IO (outputs)**:: xE0 --> xEF: 16 ports
            - **IO (inputs)**:: xF0 --> xFF: 16 ports
- talks with the CPU with 3 buses:
    - address (from CPU)
    - data (to CPU)
    - control (from CPU, to control read/write access)

# Instructions
- all possible instructions understood by the CPU come from the **instruction set**
    - can be verbose to support many operations: CISC (Complex Instruction Set Computer) i.e. what Intel x86-64 is
    - or simple, requiring less circuitry: RISC (Reduced Instruction Set Computer) i.e. what ARM is
- instruction: **opcode** **operand**
    - **opcode**: unique binary code given to each instruction, this binary code being called a **mnemonic**
    - **operand**: args to instruction
- program memory contains instructions, for example:
|address|content|instruction no.|
|----|--------|-----------------
|x00|opcode1| instruction #1
|x01|operand1|
|----|--------|-----------------
|x02|opcode2| instruction #2
----|--------|-----------------
|x03|opcode3| instruction #3
|x04|operand2|
|x05|operand3|
----|--------|-----------------
## Instruction addressing modes
... i.e. the way in which the operand of an instruction is used:
- immediate i.e. use the value of the operand as it's given, so here the operand is the constant
- direct addressing i.e. the operand is an address at which some constant can be found (in data memory) -- so read required, content is fetched and then put into a register
- inherent addressing i.e. the instruction contains no operands, just the opcode (for example, incrementing a certain register does not require an opcode)
- indexed addressing i.e. there are two operands, one which contains the base index + a constant added on top of the base to fetch the exact address

## Types of Instructions
### Load and Stores
- load: load data directly from the memory (through some addressing mode) and put it into a register
- store: move stuff from the CPU register into memory (address goes on address bus, stuff to put into memory goes on the data bus)
### Data Manipulations
- done by the ALU only on the registers so only inherent addressing is used (only opcode, no operand as you can encode on which registers you act directly in the instruction mnemonic i.e. ADD_A_B == registers A+B)
- updates the condition code register with status of the executed operation
### Branches
- basically puts the value (latches) of the operand in the program counter register

Two types:
- unconditional: **program counter register** updated no matter what
- conditional: **program counter register** is updated only if a condition is true
    - that condition comes from the status flags set in the **condition code register** (CCR)
    - ex: execute only if Z (zero) flag is present in CCR
