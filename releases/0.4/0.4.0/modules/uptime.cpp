#include "../modules.h"
#include <string>
#include <fstream>

std::string get_uptime() {
	std::ifstream f("/proc/uptime");
	double seconds;
	if (!(f >> seconds)) return "Unknown";

	int days = (int)seconds / 86400;
	int hours = ((int)seconds % 86400) / 3600;
	int minutes = ((int)seconds % 3600) / 60;

	std::string result;
	if (days > 0) result += std::to_string(days) + "d ";
	if (hours > 0) result += std::to_string(hours) + "h ";
	result += std::to_string(minutes) + "m";

	return result;
}
