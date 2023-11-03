//
// Created by nudelerde on 12.08.23.
//

asm(R"(
.global __multiboot_header
.section .multiboot_header, "ad"

.align 8
__multiboot_header:
    .int 0xe85250d6 # multiboot2
    .int 0 # protected mode i386
    .int __multiboot_header_end - __multiboot_header
    .int 0x100000000 - (0xe85250d6 + 0 + (__multiboot_header_end - __multiboot_header))

    .word 0
    .word 0
    .int 8
__multiboot_header_end:
)");