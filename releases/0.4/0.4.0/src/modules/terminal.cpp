#include "../modules.h"
#include <string>
#include <unistd.h>
#include <cstdlib>

static std::string get_term_version(const std::string& pid_str) {
    std::string cmd = std::string("readlink -f /proc/") + pid_str + "/exe 2>/dev/null";
    std::string binary = exec(cmd.c_str());
    if (!binary.empty() && binary.back() == '\n') binary.pop_back();
    if (binary.empty()) return "";

    cmd = "\"" + binary + "\" --version 2>/dev/null";
    std::string out = exec(cmd.c_str());
    if (out.empty()) return "";

    auto nl = out.find('\n');
    if (nl != std::string::npos) out = out.substr(0, nl);
    if (!out.empty() && out.back() == '\n') out.pop_back();
    if (!out.empty() && out.back() == '\r') out.pop_back();

    for (size_t i = 0; i + 1 < out.size(); i++) {
        if (std::isdigit(out[i]) && out[i + 1] == '.') {
            size_t s = i;
            while (i < out.size() && (std::isdigit(out[i]) || out[i] == '.')) i++;
            return out.substr(s, i - s);
        }
    }
    return "";
}

std::string get_terminal() {
    pid_t shell_pid = getppid();
    std::string stat_path = "/proc/" + std::to_string(shell_pid) + "/stat";
    std::string stat = read_file(stat_path);

    if (!stat.empty()) {
        auto close_paren = stat.rfind(')');
        if (close_paren != std::string::npos) {
            auto after = close_paren + 2;
            auto state_end = stat.find(' ', after);
            if (state_end != std::string::npos) {
                auto ppid_start = state_end + 1;
                auto ppid_end = stat.find(' ', ppid_start);
                std::string ppid_str = stat.substr(ppid_start, ppid_end - ppid_start);
                std::string comm_path = "/proc/" + ppid_str + "/comm";
                std::string term = read_file(comm_path);
                if (!term.empty()) {
                    std::string ver = get_term_version(ppid_str);
                    if (!ver.empty()) return term + " " + ver;
                    return term;
                }
            }
        }
    }

    const char* tp = std::getenv("TERM_PROGRAM");
    if (tp) return tp;

    const char* term_env = std::getenv("TERM");
    if (term_env) return term_env;

    return "Unknown";
}
