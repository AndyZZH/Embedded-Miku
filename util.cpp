#include <chrono>

extern "C" {
    #include "util.h"
}

long long Util_getCurrentTime() {
    using namespace std::chrono;
    using cast = duration<long long>;
    return duration_cast<cast>(system_clock::now().time_since_epoch()).count();
}