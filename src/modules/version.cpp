#include "../modules.h"
#include <string>

std::string get_version() {
	return std::string("dimfetch ") + DIMFETCH_VERSION;
}
