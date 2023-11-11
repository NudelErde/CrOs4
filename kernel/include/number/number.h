//
// Created by nudelerde on 04.11.23.
//

#pragma once

namespace CrOs4::Num {
template<typename T>
constexpr T max(T a, T b) {
    return a > b ? a : b;
}

template<typename T>
constexpr T min(T a, T b) {
    return a < b ? a : b;
}
}