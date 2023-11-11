//
// Created by nudelerde on 05.11.23.
//

#pragma once

#include <types/int.h>
#include <types/result.h>
#include <memory/address.h>

namespace CrOs4::Memory::PhysicalManager {
    void init();

    struct state_t {
        uint32_t raw;
        [[nodiscard]] bool isFree() const {
            return raw == 0;
        }
        [[nodiscard]] bool isReserved() const {
            return raw == 1;
        }
        [[nodiscard]] bool isPCIConfigSpace() const {
            return raw == 2;
        }
        [[nodiscard]] bool isUsed() const {
            return raw >= 3;
        }
        [[nodiscard]] uint32_t getUsedBy() const {
            return raw - 3;
        }
    };

    enum class element_size_t : uint32_t {
        _4KiB,
        _2MiB,
        _1GiB
    };

    struct element_t {
        uint32_t count : 30;
        element_size_t size : 2;
        state_t state;
    };
    static_assert(sizeof(element_t) == sizeof(uint64_t), "PhysicalManager::element is not 64 bit");

    struct entry_t {
        physical_address_t base;
        element_t element;
    };

    enum class error_t {
        outOfMetaMemory,
        outOfMemory,
        alignmentNotPossible,
        under4GiBNotPossible,
        freeMoreThanUsed,
        useOverflow,
        invalidEntry,
        addressNotManaged,
        unknownError
    };

    Types::Result<entry_t,error_t> findElement(physical_address_t address);
    Types::Result<void, error_t> forceEntry(entry_t entry);
    Types::Result<entry_t, error_t> allocate(uint32_t count, element_size_t alignment, bool under4GiB = false);
    Types::Result<void, error_t> free(entry_t entry, uint32_t freeUsers);
    Types::Result<void, error_t> use(entry_t entry, uint32_t newUsers);
}

