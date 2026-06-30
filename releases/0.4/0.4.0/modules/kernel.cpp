#include "modules.h"
#include <string>

std::string get_kernel() {
    	std::string kernel = exec("uname -r");
    	if (!kernel.empty() && kernel.back() == '\n') {
        	kernel.pop_back();
    	}
    	return kernel.empty() ? "Unknown" : kernel;
}
