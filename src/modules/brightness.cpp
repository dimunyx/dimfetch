#include "../modules.h"
#include <string>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

std::string get_brightness() {
    	std::string base = "/sys/class/backlight";

    	if (!fs::exists(base)) return "No backlight device";

    	for (const auto& entry : fs::directory_iterator(base)) {
        	auto name = entry.path().filename().string();
        	if (name.find("acpi_video") != std::string::npos) continue;

        	std::string dir = entry.path().string();

        	std::ifstream fmax(dir + "/max_brightness");
        	std::ifstream fcur(dir + "/brightness");

        	int max_val = -1, cur_val = -1;
        	if (!(fmax >> max_val) || !(fcur >> cur_val) || max_val <= 0)
            		continue;

        	int pct = (cur_val * 100) / max_val;
        	if (pct > 100) pct = 100;
        	if (pct < 0) pct = 0;

        	return std::to_string(pct) + "%";
    	}

    	return "No backlight device";
}
