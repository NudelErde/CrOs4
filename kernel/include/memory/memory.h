//
// Created by nudelerde on 05.11.23.
//

#pragma once

#include <types/int.h>

inline void* operator new(size_t, void* p) {
    return p;
}

inline void* operator new[](size_t, void* p) {
    return p;
}

inline void* memcpy(void* dest, const void* src, size_t n) {
    for (size_t i = 0; i < n; i++) {
        ((uint8_t*) dest)[i] = ((uint8_t*) src)[i];
    }
    return dest;
}

inline void* memset(void* dest, int c, size_t n) {
    for (size_t i = 0; i < n; i++) {
        ((uint8_t*) dest)[i] = (uint8_t) c;
    }
    return dest;
}

