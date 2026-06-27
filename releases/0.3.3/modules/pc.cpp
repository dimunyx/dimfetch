#include "modules.h"
#include <string>

std::string get_pc_model() {
	std::string model = read_file("/sys/class/dmi/id/product_version");
	if (model.empty()) model = read_file("/sys/class/dmi/id/product_name");
	return model.empty() ? "Unknown PC" : model;
}
