#include "../modules.h"
#include <string>
#include <fstream>

std::string get_cpu() {
	std::ifstream f("/proc/cpuinfo");
	std::string line, model, cores, threads;

	while (std::getline(f, line)) {
		if (model.empty() && line.find("model name") == 0) {
			auto c = line.find(':');
			if (c != std::string::npos) model = line.substr(c + 2);
		}
		if (cores.empty() && line.find("cpu cores") == 0) {
			auto c = line.find(':');
			if (c != std::string::npos) cores = line.substr(c + 2);
		}
		if (threads.empty() && line.find("siblings") == 0) {
			auto c = line.find(':');
			if (c != std::string::npos) threads = line.substr(c + 2);
		}
		if (!model.empty() && !cores.empty() && !threads.empty()) break;
	}

	if (model.empty()) return "Unknown CPU";

	auto wg = model.find(" with ");
	if (wg != std::string::npos) model = model.substr(0, wg);
	auto at = model.find(" @ ");
	if (at != std::string::npos) model = model.substr(0, at);

	if (!cores.empty() && !threads.empty())
		model += " (" + cores + "c/" + threads + "t)";

	return model;
}
