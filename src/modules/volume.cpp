#include "../modules.h"
#include <string>

std::string get_volume() {
	// PipeWire
	std::string out = exec("wpctl get-volume @DEFAULT_AUDIO_SINK@ 2>/dev/null");
	if (!out.empty()) {
		auto c = out.rfind(' ');
		if (c != std::string::npos) {
			std::string pct = out.substr(c + 1);
			if (!pct.empty() && pct.back() == '\n') pct.pop_back();
			try {
				float val = std::stof(pct);
				int p = (int)(val * 100);
				std::string result = std::to_string(p) + "%";
				if (out.find("[Muted]") != std::string::npos)
					result += " [Muted]";
				return result;
			} catch (...) {}
		}
	}

	// PulseAudio (deprecated)
	out = exec("LC_ALL=C pactl get-sink-volume @DEFAULT_SINK@ 2>/dev/null");
	if (!out.empty()) {
		auto pos = out.find('/');
		if (pos != std::string::npos) {
			auto pos2 = out.find('/', pos + 1);
			if (pos2 != std::string::npos) {
				std::string pct = out.substr(pos + 1, pos2 - pos - 1);
				auto s = pct.find_first_not_of(' ');
				if (s != std::string::npos) pct = pct.substr(s);
				std::string mute = exec("LC_ALL=C pactl get-sink-mute @DEFAULT_SINK@ 2>/dev/null");
				if (!mute.empty() && mute.find("Mute: yes") != std::string::npos)
					return pct + " [Muted]";
				return pct;
			}
		}
	}

	// Also (also deprecated for this project)
	out = exec("amixer get Master 2>/dev/null");
	if (!out.empty()) {
		auto lb = out.find('[');
		if (lb != std::string::npos) {
			auto rb = out.find(']', lb);
			if (rb != std::string::npos) {
				std::string pct = out.substr(lb + 1, rb - lb - 1);
				if (out.find("[off]") != std::string::npos || out.find("[0%]") != std::string::npos)
					return "0% [Muted]";
				return pct;
			}
		}
	}

	return "No audio device found";
}
