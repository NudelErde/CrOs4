//
// Created by nudelerde on 04.11.23.
//

#pragma once

namespace CrOs4::Types {

template<typename T>
class Optional {
public:
    Optional() : _hasValue(false) {}

    Optional(T value) : _hasValue(true), _value(value) {}

    bool hasValue() {
        return hasValue;
    }

    T getValue() {
        return _value;
    }

    operator bool () const {
        return _hasValue;
    }

    T operator*() const {
        return _value;
    }

    T* operator->() const {
        return &_value;
    }

private:
    bool _hasValue;
    union {
        [[maybe_unused]] char raw[sizeof(T)];
        T _value;
    };
};

}