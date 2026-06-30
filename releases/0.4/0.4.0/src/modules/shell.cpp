#include "../modules.h"
#include <string>
#include <cstdlib>
#include <cctype>

static std::string basename(const std::string& path) {
	auto pos = path.rfind('/');
	return (pos == std::string::npos) ? path : path.substr(pos + 1);
}

static std::string extract_ver(const std::string& cmd) {
	std::string out = exec(cmd.c_str());
	if (out.empty()) return "";

	auto nl = out.find('\n');
	if (nl != std::string::npos) out = out.substr(0, nl);
	if (!out.empty() && out.back() == '\n') out.pop_back();
	if (!out.empty() && out.back() == '\r') out.pop_back();

	for (size_t i = 0; i + 1 < out.size(); i++) {
		if (std::isdigit(out[i]) && out[i + 1] == '.') {
			size_t s = i;
			while (i < out.size() && (std::isdigit(out[i]) || out[i] == '.')) i++;
			return out.substr(s, i - s);
		}
	}

	return "";
}

std::string get_shell() {
	const char* shell = std::getenv("SHELL");
	if (!shell) return "Unknown";

	std::string name = basename(shell);
	std::string ver = extract_ver(name + " --version 2>/dev/null");

	if (!ver.empty()) return name + " " + ver;
	return name;
}
