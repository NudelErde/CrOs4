//
// Created by nudelerde on 04.11.23.
//

#pragma once

#include <number/number.h>

namespace CrOs4::Types {

template<typename ReturnType, typename ErrorType>
class Result {
public:

    bool hasValue() {
        return _hasValue;
    }

    bool hasError() {
        return _hasError;
    }

    ReturnType getValue() {
        return _value;
    }

    ErrorType getError() {
        return _error;
    }

    explicit Result(ReturnType value) : _hasValue(true), _hasError(false), _value(value) {}
    explicit Result(ErrorType error) : _hasValue(false), _hasError(true), _error(error) {}

    operator bool () const {
        return _hasValue;
    }

    ReturnType operator*() const {
        return _value;
    }

    ReturnType* operator->() const {
        return &_value;
    }

private:
    bool _hasValue;
    bool _hasError;
    union {
        [[maybe_unused]] char raw[Num::max(sizeof(ReturnType), sizeof(ErrorType))];
        ReturnType _value;
        ErrorType _error;
    };
};

template<typename ErrorType>
class Result<void, ErrorType> {
public:

    bool hasValue() {
        return !_hasError;
    }

    bool hasError() {
        return _hasError;
    }

    ErrorType getError() {
        return _error;
    }

    explicit Result() : _hasError(false) {}
    explicit Result(ErrorType error) : _hasError(true), _error(error) {}

    operator bool () const {
        return !_hasError;
    }
private:
    bool _hasError;
    union {
        [[maybe_unused]] char raw[sizeof(ErrorType)];
        ErrorType _error;
    };
};

}