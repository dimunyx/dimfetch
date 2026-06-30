#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/utsname.h>

struct Color {
    static constexpr const char* reset  = "\033[0m";
    static constexpr const char* bold   = "\033[1m";
    static constexpr const char* red    = "\033[31m";
    static constexpr const char* green  = "\033[32m";
    static constexpr const char* yellow = "\033[33m";
    static constexpr const char* blue   = "\033[34m";
    static constexpr const char* purple = "\033[35m";
    static constexpr const char* cyan   = "\033[36m";
    static constexpr const char* white  = "\033[37m";
    static constexpr const char* label  = "\033[38;2;137;180;250m";
};

std::string get_os() {
    std::ifstream f("/etc/os-release");
    if (!f.good()) return "Linux";
    std::string line;
    while (std::getline(f, line)) {
        if (line.find("PRETTY_NAME=") == 0) {
	    auto v = line.substr(12);
	    if (!v.empty() && (v.front() == '"' || v.front() == '\''))
	        v = v.substr(1);
	    if (!v.empty() && (v.back() == '"' || v.back() == '\''))
	        v.pop_back();
            if (v == "Arch Linux") {
                struct utsname u;
                uname(&u);
                v += std::string(" ") + u.machine;
            }
            return v;
        }
    }
    return "Linux";
}

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
        }, {
            Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan
        }};
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
	}, {
	    Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan, Color::cyan
	}};
    }
    return {{
        "       ____       ",
        "    __/  /_       ",
        "   / _  __/       ",
        "   \\_/  \\_        ",
        "    /  /_/        ",
        "   /_____/        ",
    }, {
        Color::green, Color::green, Color::green,
        Color::green, Color::green, Color::green
    }};
}

void print_logo() {
    auto os = get_os();
    auto dlogo = get_distro_logo(os);
    std::vector<std::string> logo;
    for (size_t i = 0; i < dlogo.lines.size(); i++)
        logo.push_back(std::string(dlogo.colors[i]) + dlogo.lines[i] + Color::reset);

    for (auto& l : logo)
        std::cout << l << "\n";
    std::cout << Color::label << "    OS: " << Color::reset << os << "\n";
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "-h" || arg == "--help") {
            std::cout << "Usage: " << argv[0] << " [-h | --help] [-v | --version]\n";
            return 0;
        }
        if (arg == "-v" || arg == "--version") {
            std::cout << "dimfetch 0.3.1\n";
	    std::cout << "Minimalistic fetch written in C++\n";
            return 0;
        }
    }
    print_logo();
    return 0;
}
