//
// Created by nudelerde on 03.11.23.
//

#include <types/int.h>

#pragma once

#define read_symbol(symbol) [](){uint64_t res; asm volatile("movabsq $" symbol ", %0": "=r"(res)); return res;}()

namespace CrOs4::Memory {

struct virtual_address_t {
    uint64_t raw;
    template<typename T>
    T* as() {
        return reinterpret_cast<T*>(raw);
    }
};


struct physical_address_t {
    uint64_t raw;
    virtual_address_t asVirtual() {
        return virtual_address_t {raw + 0xffff800000000000};
    }
};

} // namespace CrOs4::Memory