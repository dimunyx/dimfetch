#include "../modules.h"
#include <string>
#include <fstream>
#include <cmath>

std::string get_memory() {
	std::ifstream f("/proc/meminfo");
	std::string line;
	unsigned long long total = 0, avail = 0;

	while (std::getline(f, line)) {
		if (line.find("MemTotal:") == 0) {
			sscanf(line.c_str(), "MemTotal: %llu kB", &total);
		}
		if (line.find("MemAvailable:") == 0) {
			sscanf(line.c_str(), "MemAvailable: %llu kB", &avail);
		}
		if (total && avail) break;
	}

	if (!total) return "Unknown";

	auto to_gib = [](unsigned long long kb) -> double {
		return static_cast<double>(kb) / 1048576.0;
	};

	double used = to_gib(total - avail);
	double tot = to_gib(total);

	char buf[32];
	snprintf(buf, sizeof(buf), "%.1f GB / %.1f GB", used, tot);
	return buf;
}
