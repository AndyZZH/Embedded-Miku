#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string.h>

#include "util.h"

extern "C"
long long Util_getCurrentTime() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}


// Adapted from:
// https://stackoverflow.com/questions/17816966/how-print-current-time-in-c11
char *Util_CurrentTimeStr() {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%c");
    return strdup(ss.str().c_str());
}