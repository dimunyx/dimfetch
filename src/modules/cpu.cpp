#include "../modules.h"

#include <fstream>
#include <string>

std::string get_cpu() {
	std::ifstream file("/proc/cpuinfo");
	std::string line, model, cores;
	unsigned int threads = 0;
	while (std::getline(file, line)) {
		if (line.rfind("processor", 0) == 0) ++threads;
		if (model.empty() && (line.rfind("model name", 0) == 0 || line.rfind("Hardware", 0) == 0)) {
			auto colon = line.find(':');
			if (colon != std::string::npos) model = line.substr(colon + 1);
		}
		if (cores.empty() && line.rfind("cpu cores", 0) == 0) {
			auto colon = line.find(':');
			if (colon != std::string::npos) cores = line.substr(colon + 1);
		}
	}
	if (model.empty()) return "Unknown CPU";
	auto start = model.find_first_not_of(" \t");
	if (start != std::string::npos) model.erase(0, start);
	auto end = model.find_first_of("\r\n\t");
	if (end != std::string::npos) model.erase(end);
	auto suffix = model.find(" with ");
	if (suffix != std::string::npos) model.erase(suffix);
	suffix = model.find(" @ ");
	if (suffix != std::string::npos) model.erase(suffix);
	if (!cores.empty() && threads > 0) {
		auto first = cores.find_first_not_of(" \t");
		if (first != std::string::npos) cores.erase(0, first);
		model += " (" + cores + "c/" + std::to_string(threads) + "t)";
	} else if (threads > 0) {
		model += " (" + std::to_string(threads) + " threads)";
	}
	return model;
}
