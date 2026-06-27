#include <iostream>
#include <vector>
#include <string>
#include "modules.h"

struct Color {
	static constexpr const char* reset  = "\033[0m";
	static constexpr const char* bold   = "\033[1m";
	static constexpr const char* red    = "\033[31m";
	static constexpr const char* green  = "\033[32m";
	static constexpr const char* yellow = "\033[33m";
	static constexpr const char* blue   = "\033[34m";
	static constexpr const char* purple = "\033[35m";
	static constexpr const char* gentoo_blue = "\033[38;2;32;159;181m";
	static constexpr const char* white  = "\033[37m";
	static constexpr const char* label  = "\033[38;2;32;159;181m";
};

struct DistroLogo {
	std::vector<std::string> lines;
	std::vector<const char*> colors;
};

DistroLogo get_distro_logo(const std::string& os) {
	if (os.find("Arch") != std::string::npos) {
		return {{
			"              ⣸⣇              ",
			"             ⢰⣿⣿⡆             ",
			"            ⢠⣿⣿⣿⣿⡄            ",
			"            ⢿⣿⣿⣿⣿⣿⡄           ",
			"          ⢀⣷⣤⣙⢻⣿⣿⣿⣿⡀          ",
			"         ⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀         ",
			"        ⢠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡄        ",
			"       ⢠⣿⣿⣿⣿⣿⡿⠛⠛⠿⣿⣿⣿⣿⣿⡄       ",
			"      ⢠⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠙⣿⣿⣿⣿⣿⡄      ",
			"     ⣰⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⠿⣆     ",
			"    ⣴⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣷⣦⡀    ",
			"  ⢀⣾⣿⣿⠿⠟⠛⠋⠉⠉⠀⠀⠀⠀⠀⠀⠉⠉⠙⠛⠻⠿⣿⣿⣷⡀  ",
			" ⣠⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ⠈⠙⠻⣄ ",
		}, { Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue }};
	}
	if (os.find("Gentoo") != std::string::npos) {
		return {{
			"          -/oyddmdhs+:.              ",
			"      -odNMMMMMMMMNNmhy+-`           ",
			"    -yNMMMMMMMMMMMNNNmmdhy+-         ",
			"  `omMMMMMMMMMMMMNmdmmmmddhhy/`      ",
			"  omMMMMMMMMMMMN      hmdddhhhdo`    ",
			" .ydMMMMMMMMMMd        mdddhhhhdm+`  ",
			"  oyhdmNMMMMMMMN     dmddddhhhhyhNd. ",
			"   :oyhhdNNMMMMMMMNNNmmdddhhhhhyymMh ",
			"     .:+sydNMMMMMNNNmmmdddhhhhhhmMmy ",
			"        /mMMMMMMNNNmmmdddhhhhhmMNhs: ",
			"     `oNMMMMMMMNNNmmmddddhhdmMNhs+`  ",
			"   `sNMMMMMMMMNNNmmmdddddmNMmhs/.    ",
			"  /NMMMMMMMMNNNNmmmdddmNMNdso:`      ",
			" +MMMMMMMNNNNNmmmmdmNMNdso/-         ",
			" yMMNNNNNNNmmmmmNNMmhs+/-`           ",
			" /hMMNNNNNNNNMNdhs++/-`              ",
			" `/ohdmmddhys+++/:.`                 ",
			"   `-//////:--.                      ",
		}, { Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue, Color::gentoo_blue }};
	}
	return {{"Your distribution is not supported yet!"}, {Color::green}};
}

void print_logo() {
	auto os = get_os();
	auto pc = get_pc_model();
	auto mon = get_monitor_info();
	auto kernel = get_kernel();
	auto dlogo = get_distro_logo(os);
	for (size_t i = 0; i < dlogo.lines.size(); i++) {
		std::cout << dlogo.colors[i % dlogo.colors.size()] << dlogo.lines[i] << Color::reset;
		if (i == 0) std::cout << "   " << Color::label << " OS -> " << Color::reset << os;
		else if (i == 1) std::cout << "   " << Color::label << " PC -> " << Color::reset << pc;
		else if (i == 2) std::cout << "   " << Color::label << " Monitor -> " << Color::reset << mon;
		else if (i == 3) std::cout << "   " << Color::label << " Kernel -> " << Color::reset << kernel;
		std::cout << "\n";
	}
}

int main(int argc, char* argv[]) {
	if (argc > 1) {
		std::string arg = argv[1];
		if (arg == "-h" || arg == "--help") {
			std::cout << "Usage: " << argv[0] << " [-h | --help] [-v | --version]\n";
			return 0;
		}
		if (arg == "-v" || arg == "--version") {
			std::cout << "dimfetch 0.3.2\n";
			std::cout << "A minimalistic fetch made by dimunyx \n";
			return 0;
		}
	}
	print_logo();
	return 0;
}
