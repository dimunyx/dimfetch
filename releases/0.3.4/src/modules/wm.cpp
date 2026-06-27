#include "../modules.h"
#include <string>
#include <cstdlib>
#include <cctype>

static std::string extract_version(const std::string& cmd) {
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

static std::string detect_backend() {
	const char* session = std::getenv("XDG_SESSION_TYPE");
	if (session) {
		std::string s = session;
		if (s == "x11" || s == "wayland" || s == "tty") return s;
	}
	if (std::getenv("WAYLAND_DISPLAY")) return "wayland";
	if (std::getenv("DISPLAY")) return "x11";
	return "tty";
}

std::string get_wm() {
	std::string backend = detect_backend();
	std::string name, ver;

	const char* de = std::getenv("XDG_CURRENT_DESKTOP");
	if (de) {
		name = de;
		ver = extract_version(name + " --version 2>/dev/null");
		if (!ver.empty()) return name + " " + ver + " (" + backend + ")";
		return name + " (" + backend + ")";
	}

	if (backend == "x11") {
		std::string out = exec("wmctrl -m 2>/dev/null | grep 'Name:' | sed 's/.*Name: //'");
		if (!out.empty() && out.back() == '\n') out.pop_back();
		if (!out.empty()) {
			name = out;
			ver = extract_version(name + " --version 2>/dev/null");
			if (ver.empty()) return name + " " + ver + " (x11)";
			return name + " (x11)";
		}
	}

	std::string ps_cmd = "ps -eo comm= 2>/dev/null | grep -iwE 'Hyprland|sway|river|wayfire|dwl|hikari|weston|i3|bspwm|dwm|qtile|herbstluftwm|mango|fluxbox|icewm|awesome|xmonad|openbox' | head -1";
	std::string proc = exec(ps_cmd.c_str());
	if (!proc.empty() && proc.back() == '\n') proc.pop_back();
	if (!proc.empty()) {
		name = proc;
		if (name == "Hyprland") {
			ver = extract_version("hyprctl version 2>/dev/null | head -1");
		} else {
    			ver = extract_version(name + " --version 2>/dev/null");
    			if (ver.empty()) ver = extract_version(name + " -version 2>/dev/null");
		}
		if (!ver.empty()) return name + " " + ver + " (" + backend + ")";
		return name + " (" + backend + ")";
	}

	const char* ds = std::getenv("DESKTOP_SESSION");
	if (ds) return std::string(ds) + " (" + backend + ")";

	if (backend != "tty") return backend;
	return "Unknown";
}
