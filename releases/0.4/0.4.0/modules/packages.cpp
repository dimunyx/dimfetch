#include "../modules.h"
#include <string>
#include <cstdlib>
#include <fstream>

std::string get_packages() {
    	std::string result;

    	// emerge (Gentoo)
    	std::string count = exec("ls -d /var/db/pkg/*/* 2>/dev/null | wc -l");
    	if (!count.empty() && count.back() == '\n') count.pop_back();
    	if (!count.empty() && count != "0")
        	result = count + " (portage)";

    	// pacman (Arch)
    	if (result.empty()) {
        	count = exec("pacman -Q 2>/dev/null | wc -l");
        	if (!count.empty() && count.back() == '\n') count.pop_back();
        	if (!count.empty() && count != "0")
         	   	result = count + " (pacman)";
    	}

    	// flatpak
    	std::string fcnt = exec("flatpak list --app 2>/dev/null | wc -l");
    	if (!fcnt.empty() && fcnt.back() == '\n') fcnt.pop_back();
    	if (!fcnt.empty() && fcnt != "0") {
        	if (!result.empty()) result += ", ";
        	result += fcnt + " (flatpak)";
    	}

    	if (!result.empty()) return result;
    	return "Unknown";
}
