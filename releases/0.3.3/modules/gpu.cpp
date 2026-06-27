#include "../modules.h"
#include <string>
#include <cstdlib>
#include <cctype>

static std::string read_vram(const std::string& path) {
	std::string val = read_file(path);
    	if (val.empty()) return "";
    	unsigned long long bytes = std::stoull(val);
    	unsigned long long mb = bytes / (1024 * 1024);
    	if (mb >= 1024) return std::to_string(mb / 1024) + " GB";
    	return std::to_string(mb) + " MB";
}

static std::string parse_vendor(const std::string& line) {
    	if (line.find("[AMD") != std::string::npos) return "AMD";
    	if (line.find("[NVIDIA") != std::string::npos || line.find("NVIDIA") != std::string::npos) return "NVIDIA";
    	if (line.find("[Intel") != std::string::npos || line.find("Intel Corporation") != std::string::npos) return "Intel";
	return "";
}

static std::string parse_model(const std::string& line) {
    	auto br = line.rfind(']');
    	if (br == std::string::npos) return "";
	std::string rest = line.substr(br + 1);
    	auto s = rest.find_first_not_of(' ');
    	if (s == std::string::npos) return "";
    	rest = rest.substr(s);
    	auto rev = rest.find(" (rev");
    	if (rev != std::string::npos) rest = rest.substr(0, rev);
    	if (!rest.empty() && rest.back() == '\n') rest.pop_back();
    	auto sub = rest.find(" [");
    	if (sub != std::string::npos) rest = rest.substr(0, sub);
    	return rest;
}

std::string get_gpu() {
    	std::string lspci = exec("lspci 2>/dev/null | grep -iE 'VGA|3D|Display' | head -1");
    	if (lspci.empty()) return "Unknown GPU";

    	std::string vendor = parse_vendor(lspci);
    	std::string model = parse_model(lspci);
    	std::string type;

    	if (lspci.find("VGA") != std::string::npos) {
        	if (vendor == "AMD" || vendor == "Intel") type = "Integrated";
        	else type = "Discrete";
    	} else {
        	type = "Discrete";
    	}

    	std::string result;
    	if (!vendor.empty()) result = vendor + " " + model;
    	else result = model;
    	if (!result.empty()) result += " [" + type + "]";

    	std::string vram;
    	std::string paths[] = {
        	"/sys/class/drm/card0/device/mem_info_vram_total",
        	"/sys/class/drm/card1/device/mem_info_vram_total",
    	};
    	for (const auto& p : paths) {
        	vram = read_vram(p);
        	if (!vram.empty()) break;
    	}
    	if (!vram.empty()) result += " (" + vram + ")";

    	return result.empty() ? "Unknown GPU" : result;
}
