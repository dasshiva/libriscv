#include <libriscv.h>
#include <iostream>
#include <cstdlib>

int main(int argc, const char** argv) {
    if (argc != 2) {
        std::cout << "USAGE: rv32 {INSTRUCTION}" << std::endl;
        return 1;
    }

    uint32_t n = strtol(argv[1], nullptr, 0);
    return RISCV::Decode(n);
}