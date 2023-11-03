//
// Created by nudelerde on 03.11.23.
//

#include <control/control.h>
#include <io/registers.h>

namespace CrOs4::Control {

[[noreturn]] void enterMainCPU(Memory::physical_address_t multiboot_info) {
    while (true) {
        IO::halt();
    }
}

} // namespace CrOs4::Control