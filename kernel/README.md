# How code should be formatted in CrOs4::Kernel
# ASM
ASM code should be in a cpp file using the `asm` statement using a raw string (`asm(R"()")`). 

# C++
Structs (only data, everything public) and alias types (idk the real name, using typename_t = int stuff) should be named typename_t.

Classes (data, but can do stuff u know with methods) should be named TypeName.

Special symbols (like x64 entry point or gdt should use __ as prefix)
