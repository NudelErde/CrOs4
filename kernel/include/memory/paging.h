//
// Created by nudelerde on 04.11.23.
//

#pragma once

#include <memory/address.h>
#include <types/optional.h>
#include <types/result.h>

namespace CrOs4::Memory {

class Pagetable {
public:

    struct flags {

    };

    struct page_entry_t {
        virtual_address_t virtualBase;
        physical_address_t physicalBase;
        size_t size;
        flags flags;
    };

    enum class map_error_t {
        invalid_size,
        invalid_remap
    };

    Types::Optional<physical_address_t> getPhysicalAddress(virtual_address_t virtualAddress);
    Types::Optional<page_entry_t> getPageEntry(virtual_address_t virtualAddress);
    Types::Result<void, map_error_t> mapPage(page_entry_t pageEntry, bool remap = false);

    static Pagetable getCurrent();

private:
    physical_address_t level4PageTableAddress;

    Pagetable() = default;
};

}