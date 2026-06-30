#include "../modules.h"
#include <string>
#include <fstream>

static std::string read_sys(const std::string& path) {
	std::ifstream f(path);
	std::string val;
	if (f >> val) return val;
	return "";
}

std::string get_battery() {
	for (int i = 0; i <= 1; i++) {
		std::string base = "/sys/class/power_supply/BAT" + std::to_string(i);

		std::string cap = read_sys(base + "/capacity");
		if (cap.empty()) continue;

		std::string status = read_sys(base + "/status");

		std::string result = cap + "%";

		if (!status.empty()) {
			if (status == "Charging") result += " [Charging]";
			else if (status == "Discharging") result += " [Discharging]";
			else if (status == "Not charging") result += " [Not charging]";
			else if (status == "Full") result += " [Full";
			else result += " [" + status + "]";

		}

		return result;
	}

	return "No battery";
}
