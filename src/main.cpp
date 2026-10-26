#include "modules.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace {
constexpr const char* reset = "\033[0m";
constexpr const char* label_color = "\033[38;2;32;159;181m";
constexpr const char* logo_color = "\033[38;2;32;159;181m";

struct DistroLogo {
	std::vector<std::string> lines;
};

DistroLogo get_distro_logo(const std::string& os) {
	if (os.find("Arch") != std::string::npos) return {{
		"              ⣸⣇              ", "             ⢰⣿⣿⡆             ",
		"            ⢠⣿⣿⣿⣿⡄            ", "            ⢿⣿⣿⣿⣿⣿⡄           ",
		"          ⢀⣷⣤⣙⢻⣿⣿⣿⣿⡀          ", "         ⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀         ",
		"        ⢠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡄        ", "       ⢠⣿⣿⣿⣿⣿⡿⠛⠛⠿⣿⣿⣿⣿⣿⡄       ",
		"      ⢠⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠙⣿⣿⣿⣿⣿⡄      ", "     ⣰⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⠿⣆     ",
		"    ⣴⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣷⣦⡀    ", "  ⢀⣾⣿⣿⠿⠟⠛⠋⠉⠉⠀⠀⠀⠀⠀⠀⠉⠉⠙⠛⠻⠿⣿⣿⣷⡀  ",
		" ⣠⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ⠈⠙⠻⣄ "
	}};
	if (os.find("Gentoo") != std::string::npos) return {{
		"          -/oyddmdhs+:.              ", "      -odNMMMMMMMMNNmhy+-`           ",
		"    -yNMMMMMMMMMMMNNNmmdhy+-         ", "  `omMMMMMMMMMMMMNmdmmmmddhhy/`      ",
		"  omMMMMMMMMMMMNhhyyyohmdddhhhdo`    ", " .ydMMMMMMMMMMdhs++so/smdddhhhhdm+`  ",
		"  oyhdmNMMMMMMMNdyooydmddddhhhhyhNd. ", "   :oyhhdNNMMMMMMMNNNmmdddhhhhhyymMh ",
		"     .:+sydNMMMMMNNNmmmdddhhhhhhmMmy ", "        /mMMMMMMNNNmmmdddhhhhhmMNhs: ",
		"     `oNMMMMMMMNNNmmmddddhhdmMNhs+`  ", "   `sNMMMMMMMMNNNmmmdddddmNMmhs/.    ",
		"  /NMMMMMMMMNNNNmmmdddmNMNdso:`      ", " +MMMMMMMNNNNNmmmmdmNMNdso/-         ",
		" yMMNNNNNNNmmmmmNNMmhs+/-`           ", " /hMMNNNNNNNNMNdhs++/-`              ",
		" `/ohdmmddhys+++/:.`                 ", "   `-//////:--.                      "
	}};
	return {{"Your distribution is not supported yet!"}};
}

size_t utf8_length(const std::string& value) {
	size_t count = 0;
	for (unsigned char ch : value) if ((ch & 0xc0) != 0x80) ++count;
	return count;
}

void print_logo() {
	const auto os = get_os();
	const auto logo = get_distro_logo(os);
	const std::vector<std::pair<std::string, std::string>> rows = {
		{"", os}, {"󰌢", get_pc_model()}, {"󱂬", get_wm()}, {"󰾲", get_cpu()},
		{"󰍛", get_gpu()}, {"", get_disk()}, {"", get_uptime()}, {"", get_memory()},
		{"", get_kernel()}, {"󰍹", get_monitor_info()}, {"󰁹", get_battery()}, {"", get_terminal()},
		{"󱆃", get_shell()}, {"󰏗", get_packages()}, {"󰃞", get_brightness()}, {"󰕾", get_volume()},
		{"", get_sys_init()}, {"", get_version()}
	};
	const size_t height = std::max(logo.lines.size(), rows.size());
	size_t logo_width = 0;
	for (const auto& line : logo.lines) logo_width = std::max(logo_width, utf8_length(line));
	for (size_t i = 0; i < height; ++i) {
		if (i < logo.lines.size()) std::cout << logo_color << logo.lines[i] << reset;
		else std::cout << std::string(logo_width, ' ');
		if (i < rows.size()) std::cout << "   " << label_color << ' ' << rows[i].first << " -> " << reset << rows[i].second;
		std::cout << '\n';
	}
}
}

int main(int argc, char* argv[]) {
	for (int i = 1; i < argc; ++i) {
		const std::string arg = argv[i];
		if (arg == "-h" || arg == "--help") {
			std::cout << "Usage: " << argv[0] << " [-h|--help] [-v|--version]\n";
			return 0;
		}
		if (arg == "-v" || arg == "--version") {
			std::cout << "dimfetch " << DIMFETCH_VERSION << "\nA minimalistic fetch made by dimunyx\n";
			return 0;
		}
		std::cerr << "Unknown option: " << arg << "\nTry '" << argv[0] << " --help' for usage.\n";
		return 2;
	}
	print_logo();
	return 0;
}
