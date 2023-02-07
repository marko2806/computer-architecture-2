#include <iostream>

int potprogram_c(int n) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        res += i;
    }
    return res;
}

extern "C" int potprogram_asm(int) asm("potprogram_asm");

int main() {
    for (int i = 0; i < 20; i++) {
        int test = rand() % 50;
        std::cout << "C++: " << potprogram_c(test) << std::endl;
        std::cout << "ASM: " << potprogram_asm(test) << std::endl;
    }
    return 0;
}