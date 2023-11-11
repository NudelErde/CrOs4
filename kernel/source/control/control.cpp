//
// Created by nudelerde on 03.11.23.
//

#include <control/control.h>
#include <io/registers.h>
#include <memory/memory.h>
#include <memory/physical.h>

namespace CrOs4::Control {

static void init_bss() {
    auto bss_start = read_symbol("__bss_start__");
    auto bss_end = read_symbol("__bss_end__");
    size_t bss_size = bss_end - bss_start;
    memset((void*)bss_start, 0, bss_size);
}

[[noreturn]] void enterMainCPU(Memory::physical_address_t multiboot_info) {
    init_bss();
    Memory::PhysicalManager::init();
    while (true) {
        IO::halt();
    }
}

} // namespace CrOs4::Control