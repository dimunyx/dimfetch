#include "../modules.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/utsname.h>
#include <cstdio>
#include <memory>
#include <array>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

std::string get_monitor_info() {
	for (const auto& entry : fs::directory_iterator("/sys/class/drm")) {
		auto path = entry.path();

		if (!fs::is_directory(path)) continue;

		auto status_path = path / "status";
		auto edid_path   = path / "edid";

		if (!fs::exists(status_path) || !fs::exists(edid_path))
			continue;

		if (read_file(status_path) != "connected")
			continue;

		// ===== EDID decode =====
		std::string out = exec(
			("edid-decode " + edid_path.string()).c_str()
		);

		if (out.empty())
			continue;

		// ===== 1. Model =====
		std::string model = "Unknown";

		size_t mpos = out.find("Alphanumeric Data String:");
		if (mpos != std::string::npos) {
			size_t start = out.find('\'', mpos);
			size_t end   = out.find('\'', start + 1);

			if (start != std::string::npos && end != std::string::npos)
				model = out.substr(start + 1, end - start - 1);
		}

		// ===== 2. Resolution + Hz =====
		std::string res = "Unknown";
		std::string hz  = "0";

		size_t dtd = out.find("DTD 1:");
		if (dtd != std::string::npos) {
			std::string line = out.substr(dtd);

			std::stringstream ss(line);
			std::string tmp;

			ss >> tmp; // DTD
			ss >> tmp; // 1:
			ss >> res; // 1920x1080
			ss >> hz;  // 60.051077
		}

		if (hz.find('.') != std::string::npos)
			hz = hz.substr(0, hz.find('.'));

		return model + " (" + res + "@" + hz + "Hz)";
	}

	return "No monitor";
}
