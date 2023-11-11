//
// Created by nudelerde on 12.08.23.
//

#include <control/control.h>
#include <types/int.h>

using namespace CrOs4;

extern "C" [[maybe_unused]] [[noreturn]] void __stack_chk_fail() {
    while(true) asm("hlt");
}

extern "C" [[maybe_unused]] [[noreturn]] void __cxa_pure_virtual() {
    while (true) asm("hlt");
}

extern "C" [[maybe_unused]] [[noreturn]] void __enter_cpp(uint64_t multiboot_info) {
    Control::enterMainCPU(Memory::physical_address_t {multiboot_info});
    while (true) continue;
}

asm(R"(
.global __start
.section .text

.type __start64, @function
.code64
.align 16
__start_64:
    call __enter_cpp
    hlt
    jmp __start_64


.section .startup_text, "ax"
.code64
__start_64_relay:
    mov $0b10000, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    movabsq $__start_64, %rax
    jmp* %rax

.type __start, @function
.code32
.align 16
__start:
    cli
    mov $__start_stack_end, %esp
    push %ebx
    call __clear
    mov $__hello_string, %esi
    call __print
    call __check_if_x64
    pop %ebx
    call __go_to_x64

    jmp __32fail

__go_to_x64:
    push %ebx
    mov $__page_level_4, %eax
    mov %eax, %cr3

    mov %cr4, %eax
    or $(0x1 << 5), %eax
    mov %eax, %cr4

    mov $0xC0000080, %ecx
    rdmsr
    or $(0x1 << 8), %eax
    wrmsr

    mov %cr0, %eax
    or $(0x1 << 31), %eax
    mov %eax, %cr0

    pop %edi

    lgdt __gdt_end
    jmp $0b1000, $__start_64_relay

    ret

__check_if_x64:
    pushfl
    pop %eax
    mov %eax, %ecx
    xor $(1 << 21), %eax
    push %eax
    popfl
    pushfl
    pop %eax
    push %ecx
    popfl
    cmp %eax, %ecx
    je __x64_not_supported

    mov $0x80000000, %eax
    cpuid
    cmp $0x80000001, %eax
    jb __x64_not_supported
    mov $0x80000001, %eax
    cpuid
    test $(1 << 29), %edx
    jz __x64_not_supported
    mov $__x64_supported_string, %esi
    call __print
    ret

__x64_not_supported:
    mov $__x64_not_supported_string, %esi
    call __print
    jmp __32fail

__32fail:
    hlt
    jmp __32fail

__clear:
    movl $0, (__cursor)
    mov $0x0, %eax
    mov $0xb8000, %edi
    mov $0x2000, %ecx
    rep stosw
    ret

__print:
    mov $0xB8000, %edi
    add (__cursor), %edi
__print_loop:
    mov (%esi), %al
    mov $0x0F, %ah
    cmp $0, %al
    je __print_end
    cmp $'\n', %al
    je __print_next_line
    mov %ax, (%edi)
    add $2, %edi
    add $1, %esi
    jmp __print_loop
__print_next_line:
    sub $0xB8000, %edi
    mov %edi, (__cursor)
    add $0xB8000, %edi
    call __next_line
    mov $0xB8000, %edi
    add (__cursor), %edi
    add $1, %esi
    jmp __print_loop
__print_end:
    sub $0xB8000, %edi
    mov %edi, (__cursor)
    ret

__next_line:
    push %eax
    push %ecx
    mov (__cursor), %eax

    leal    159(%eax), %ecx
    movl    $1717986919, %eax
    imull   %ecx
    sarl    $31, %ecx
    sarl    $6, %edx
    subl    %ecx, %edx
    leal    (%edx,%edx,4), %eax
    sall    $5, %eax

    mov %eax, (__cursor)
    pop %ecx
    pop %eax
    ret

.section .startup, "aw"
__cursor:
    .int 0x0
__hello_string:
    .string "Starting CrOs4! 32bit start!\n"
__x64_not_supported_string:
    .string "x64 is not supported!\n"
__x64_supported_string:
    .string "x64 is supported!\n"

__start_stack:
    .skip 0x1000
    .align 8
__start_stack_end:
    .quad 0

.align 0x1000
__page_level_4:
    .quad __page_level_3_low_1gb_identity_map + ((1 << 0) | (1 << 1))
    .zero 0x7F8
    .quad __page_level_3_kernel_1gb_identity_map + ((1 << 0) | (1 << 1))
    .zero 0x7F8

.align 0x1000
__page_level_3_low_1gb_identity_map:
    .quad (1 << 0) | (1 << 1) | (1 << 7) | 0x0
    .zero 0xFF8 # rest of table is 0

.align 0x1000
__page_level_3_kernel_1gb_identity_map:
    .quad (1 << 0) | (1 << 1) | (1 << 7) | 0x0
    .zero 0xFF8 # rest of table is 0
.align 0x1000
__gdt:
    .quad 0
    .quad (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53) # code segment
    .quad (1 << 41) | (1 << 44) | (1 << 47) # data segment
    .quad (1 << 43) | (1 << 44) | (1 << 45) | (1 << 46) | (1 << 47) | (1 << 53) # ring 3 code segment
    .quad (1 << 41) | (1 << 44) | (1 << 45) | (1 << 46) | (1 << 47) # ring 3 data segment
.align 0x1000
__gdt_end:
    .word __gdt_end - __gdt - 1
    .quad __gdt
)");
