
ENTRY(__start)

MEMORY
{
    MULTIBOOT_HEADER_PV : ORIGIN = 16k, LENGTH = 4k
    TRAMPOLINE_PV : ORIGIN = 0x0, LENGTH = 16k
    START_MEMORY_PV : ORIGIN = 20k, LENGTH = 44k

    KERNEL_MEMORY_P : ORIGIN = 64k, LENGTH = (1024M - ORIGIN(KERNEL_MEMORY_P))

    HIGH_KERNEL_V : ORIGIN = 0xFFFF800000000000 + 64k, LENGTH = LENGTH(KERNEL_MEMORY_P)
}

SECTIONS
{
    .boot : {
        KEEP(*(.multiboot_header))
    } > MULTIBOOT_HEADER_PV
    .startup_text : {
            __startup_text_start__ = .;
            *(.startup_text)
            __startup_text_end__ = .;
    } > START_MEMORY_PV
    .startup : {
        __startup_start__ = .;
        KEEP(*(.startup))
        __startup_end__ = .;
    } > START_MEMORY_PV
    .text : {
        __text_start__ = .;
        *(EXCLUDE_FILE(*trampoline*) .text)
        __text_end__ = .;
    } > HIGH_KERNEL_V AT > KERNEL_MEMORY_P
    .rodata : {
        __rodata_start__ = .;
        *(EXCLUDE_FILE(*trampoline*) .rodata)
        __rodata_end__ = .;
    } > HIGH_KERNEL_V AT > KERNEL_MEMORY_P
    .data : {
        __data_start__ = .;
        *(EXCLUDE_FILE(*trampoline*) .data)
        __data_end__ = .;
    } > HIGH_KERNEL_V AT > KERNEL_MEMORY_P
    .bss : {
        __bss_start__ = .;
        *(EXCLUDE_FILE(*trampoline*) .bss)
        __bss_end__ = .;
    } > HIGH_KERNEL_V AT > KERNEL_MEMORY_P

    .trampoline_text : {
        __trampoline_text_start__ = .;
        *trampoline*(.text)
        __trampoline_text_end__ = .;
    } > TRAMPOLINE_PV

    .trampoline_data : {
        __trampoline_data_start__ = .;
        *trampoline*(.data)
        __trampoline_data_end__ = .;
    } > TRAMPOLINE_PV

    .trampoline_bss : {
        __trampoline_bss_start__ = .;
        *trampoline*(.bss)
        __trampoline_bss_end__ = .;
    } > TRAMPOLINE_PV

    .trampoline_rodata : {
        __trampoline_rodata_start__ = .;
        *trampoline*(.rodata)
        __trampoline_rodata_end__ = .;
    } > TRAMPOLINE_PV

    /DISCARD/ : {
        *(.comment)
        *(.eh_frame)
        *(.note)
        *(.note.gnu.build-id)
    }
}

