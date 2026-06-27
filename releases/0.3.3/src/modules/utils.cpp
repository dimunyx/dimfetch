#include <string>
#include <fstream>
#include <cstdio>
#include <memory>
#include <array>

std::string read_file(const std::string& path) {
	std::ifstream f(path);
	std::string line;
	if (f && std::getline(f, line)) {
		if (!line.empty() && line.back() == '\n') line.pop_back();
		if (!line.empty() && line.back() == '\r') line.pop_back();
		return line;
	}
	return "";
}

std::string exec(const char* cmd) {
	std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
	if (!pipe) return "";
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	return result;
}
