#include "rstring.h"

/* Generate a random string */
std::string randString(size_t length) {
#ifdef DEBUG
    _log("randString called");
#endif
    std::string str("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(str.begin(), str.end(), generator);
    return str.substr(0, length);
}