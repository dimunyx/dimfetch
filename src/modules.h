#ifndef MODULES_H
#define MODULES_H

#include <string>

std::string get_os();
std::string get_pc_model();
std::string get_monitor_info();
std::string get_kernel();
std::string exec(const char* cmd);
std::string read_file(const std::string& path);

#endif
