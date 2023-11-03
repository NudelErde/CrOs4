//
// Created by nudelerde on 12.08.23.
//

asm(R"(
.global __trampoline

.section .text
.align 4096
.code16
.type __trampoline, @function
__trampoline:
    jmp __trampoline

)");
