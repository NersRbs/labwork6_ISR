#include <lib/number.h>
#include <iostream>
#include <string>

int main() {
    uint2022_t value1;
    uint2022_t value2;
    uint2022_t value3;
    uint2022_t a = from_string(
            "21 165 857 639 861 524 596");
    value1 = from_string(
            "200000000000000000000000000000000000000100000000000000000000000");
    std::cout << value1;
}
