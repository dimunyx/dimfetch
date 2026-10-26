#include "../modules.h"
#include <string>
#include <sys/statvfs.h>
#include <cstdio>

std::string get_disk() {
	struct statvfs buf;
	if (statvfs("/", &buf) != 0) return "Unknown";

	unsigned long long total = (unsigned long long)buf.f_blocks * buf.f_frsize;
	if (total == 0) return "Unknown";
	unsigned long long available = (unsigned long long)buf.f_bavail * buf.f_frsize;
	unsigned long long used = total > available ? total - available : 0;

	double total_gb = (double)total / (1024.0 * 1024.0 * 1024.0);
	double used_gb = (double)used / (1024.0 * 1024.0 * 1024.0);
	int pct = (int)((double)used / (double)total * 100.0);

	char buf_out[64];
	snprintf(buf_out, sizeof(buf_out), "%.1f GB / %.1f GB (%d%%)", used_gb, total_gb, pct);
	return buf_out;
}
