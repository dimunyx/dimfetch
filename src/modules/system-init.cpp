#include "../modules.h"
#include <string>

std::string get_sys_init() {
	std::string comm = read_file("/proc/1/comm");
	if (comm.empty()) return "Unknown";

	if (comm == "systemd") {
		std::string ver = exec("systemctl --version 2>/dev/null | head -1");
		if (!ver.empty() && ver.back() == '\n') ver.pop_back();
		auto pos = ver.find('(');
		if (pos != std::string::npos) ver = ver.substr(0, pos);
		if (!ver.empty()) return ver;
		return "systemd";
	}

	if (comm == "openrc" || comm == "openrc-run") {
		std::string ver = exec("openrc --version 2>/dev/null");
		if (!ver.empty()) return ver;
		return "OpenRC";
	}

	if (!comm.empty()) {
		comm[0] = std::toupper(static_cast<unsigned char>(comm[0]));
	}
	return comm;
}
