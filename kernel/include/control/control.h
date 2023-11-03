//
// Created by nudelerde on 03.11.23.
//

#pragma once

#include <memory/address.h>

namespace CrOs4::Control {

[[noreturn]] void enterMainCPU(Memory::physical_address_t multiboot_info);

}