#include <iostream>
#include <fstream>

extern "C" {
#include "cfg/cfg_parse.h"
}

int main(int argc, const char** argv) {
	if (argc != 3)
		return 1;

	std::ofstream file(argv[1]);
	if (!file.is_open())
		return 2;

	Config* config;
	int status = ParseConfig(argv[2], &config);
	if(status < 0) {
		std::cout << ErrToString(status);
		return 3;
	}

	file << "#pragma once" << std::endl;
	file.close();
	FreeConfig(config);
	return 0;
}
