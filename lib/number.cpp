#include "number.h"
#include "string"
#include <cstring>

uint2022_t from_uint(uint32_t i) {
    uint2022_t result;
    while (i > 0) {
        result.chunk[result.number_of_indexes] = i % result.base;
        i = i / result.base;
        result.number_of_indexes--;
    }
    result.number_of_indexes = 67;
    return result;
}

uint2022_t from_string(const char *buff) {
    uint2022_t result;
    std::string str;
    for (int i = (int) strlen(buff) - 1; i >= 0; --i) {
        str = buff[i] + str;
        if (str.length() == 9) {
            result.chunk[result.number_of_indexes] = std::stoi(str);
            result.number_of_indexes--;
            str = "";
        }
    }
    if (str.length() != 0)
        result.chunk[result.number_of_indexes] = std::stoi(str);
    result.number_of_indexes = 67;
    return result;
}

uint2022_t operator+(const uint2022_t &lhs, const uint2022_t &rhs) {
    uint2022_t result;
    int remainder = 0;
    int sum;
    for (char i = result.number_of_indexes; i >= 0; --i) {
        sum = lhs.chunk[i] + rhs.chunk[i] + remainder;
        result.chunk[i] = sum % result.base;
        remainder = sum / result.base;
    }
    return result;
}

uint2022_t operator-(const uint2022_t &lhs, const uint2022_t &rhs) {
    uint2022_t result;
    int remainder = 0;
    int subst;
    for (char i = result.number_of_indexes; i >= 0; --i) {
        subst = lhs.chunk[i] - rhs.chunk[i] - remainder;
        if (subst < 0) {
            result.chunk[i] = result.base + subst;
            remainder = 1;
        } else {
            result.chunk[i] = subst;
            remainder = 0;
        }
    }
    return result;
}

uint2022_t operator*(const uint2022_t &lhs, const uint2022_t &rhs) {
    uint2022_t result;
    int remainder = 0;
    char bias = -1;
    uint64_t mult;
    for (char i = result.number_of_indexes; i >= 0; --i) {
        bias++;
        for (char j = result.number_of_indexes; j - bias >= 0; --j) {
            if(lhs.chunk[j] == 0 && rhs.chunk[i] == 0)continue;
            mult = (uint64_t)rhs.chunk[i] * lhs.chunk[j] + remainder + result.chunk[j - bias];
            result.chunk[j - bias] = mult % result.base;
            remainder = mult / result.base;
        }
    }
    return result;

}

uint2022_t operator/(const uint2022_t &lhs, const uint2022_t &rhs) {
    return uint2022_t();
}

bool operator==(const uint2022_t &lhs, const uint2022_t &rhs) {
    for (char i = 0; i < 68; ++i) {
        if (lhs.chunk[i] != rhs.chunk[i]) return false;
    }
    return true;
}

bool operator!=(const uint2022_t &lhs, const uint2022_t &rhs) {
    return !(lhs == rhs);
}

std::ostream &operator<<(std::ostream &stream, const uint2022_t &value) {
    bool not_a_zero = false;
    for (int i = 0; i <= value.number_of_indexes; ++i) {
        if(value.chunk[i] != 0){
            stream << value.chunk[i];
            not_a_zero = true;
        } else if(not_a_zero){
            stream << "000000000";
        }
    }
    if(!not_a_zero){
        stream << '0';
    }
    return stream;
}
