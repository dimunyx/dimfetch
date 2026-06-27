#ifndef MODULES_H
#define MODULES_H

#include <string>

std::string get_os();
std::string get_pc_model();
std::string get_monitor_info();
std::string get_kernel();
std::string get_terminal();
std::string get_wm();
std::string get_cpu();
std::string get_gpu();
std::string get_memory();
std::string exec(const char* cmd);
std::string read_file(const std::string& path);

#endif
