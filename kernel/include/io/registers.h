//
// Created by nudelerde on 03.11.23.
//

#pragma once

#include <types/int.h>

namespace CrOs4::IO {

inline void halt() {
    asm("hlt");
}

inline void out8(uint16_t port, uint8_t value) {
    asm volatile("outb %0, %1"
                 :
                 : "a"(value), "Nd"(port));
}

inline void out16(uint16_t port, uint16_t value) {
    asm volatile("outw %0, %1"
                 :
                 : "a"(value), "Nd"(port));
}

inline void out32(uint16_t port, uint32_t value) {
    asm volatile("outl %0, %1"
                 :
                 : "a"(value), "Nd"(port));
}

inline uint8_t in8(uint16_t port) {
    uint8_t value;
    asm volatile("inb %1, %0"
                 : "=a"(value)
                 : "Nd"(port));
    return value;
}

inline uint16_t in16(uint16_t port) {
    uint16_t value;
    asm volatile("inw %1, %0"
                 : "=a"(value)
                 : "Nd"(port));
    return value;
}

inline uint32_t in32(uint16_t port) {
    uint32_t value;
    asm volatile("inl %1, %0"
                 : "=a"(value)
                 : "Nd"(port));
    return value;
}

inline uint64_t cr0() {
    uint64_t value;
    asm volatile("mov %%cr0, %0"
                 : "=r"(value));
    return value;
}

inline uint64_t cr2() {
    uint64_t value;
    asm volatile("mov %%cr2, %0"
                 : "=r"(value));
    return value;
}

inline uint64_t cr3() {
    uint64_t value;
    asm volatile("mov %%cr3, %0"
                 : "=r"(value));
    return value;
}

inline uint64_t cr4() {
    uint64_t value;
    asm volatile("mov %%cr4, %0"
                 : "=r"(value));
    return value;
}

inline void cr0(uint64_t value) {
    asm volatile("mov %0, %%cr0"
                 :
                 : "r"(value));
}

inline void cr2(uint64_t value) {
    asm volatile("mov %0, %%cr2"
                 :
                 : "r"(value));
}

inline void cr3(uint64_t value) {
    asm volatile("mov %0, %%cr3"
                 :
                 : "r"(value));
}

inline void cr4(uint64_t value) {
    asm volatile("mov %0, %%cr4"
                 :
                 : "r"(value));
}

}