#include "modules.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/utsname.h>
#include <cstdio>
#include <memory>
#include <array>
#include <filesystem>

std::string get_os() {
	std::ifstream f("/etc/os-release");
	if (!f.good()) return "Linux";
	std::string line;
	while (std::getline(f, line)) {
		if (line.find("PRETTY_NAME=") == 0) {
			auto v = line.substr(12);
			if (!v.empty() && (v.front() == '"' || v.front() == '\'')) v = v.substr(1);
			if (!v.empty() && (v.back() == '"' || v.back() == '\'')) v.pop_back();
			if (v == "Gentoo Linux" || v == "Arch Linux") {
				struct utsname u;
				uname(&u);
				v += std::string(" ") + u.machine;
			}
			return v;
		}
	}
	return "Linux";
}
