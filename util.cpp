#include <chrono>

#include "util.h"

extern "C"
long long Util_getCurrentTime() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}