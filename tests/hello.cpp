#include <libriscv.h>
#include <iostream>
#include <cstdlib>

int main(int argc, const char** argv) {
    if (argc < 2) {
        std::cout << "USAGE: rv32 {INSTRUCTION}" << std::endl;
        return 1;
    }

	for (int i = 1; i < argc; i++) {
		uint32_t n = strtol(argv[i], nullptr, 0);
		RISCV::DecodedInst di;
		int status = RISCV::Decode(n, &di);
		if (status != RISCV::SUCCESS) 
			return 1;
		std::cout << "Instruction: " << RISCV::ToString(di) << std::endl;
	}
	return 0;
}
