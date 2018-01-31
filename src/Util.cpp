#include "Util.hpp"

string Util::extract(string &str, const char delimiter) {
    string result = str.substr(0, str.find(delimiter, 0));
    str = str.substr(str.find(delimiter, 0) + 1, str.length());
    return result;
}