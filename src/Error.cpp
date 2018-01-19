#include "Error.hpp"
#include "Log.hpp"

Error::Error() {
    LOG << "[ERROR] " << what() << '\n';
}

Error::~Error() {

}

const char* Error::what() const throw() {
    return "Unknown exception";
}