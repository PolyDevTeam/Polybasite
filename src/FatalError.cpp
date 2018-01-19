#include "Log.hpp"
#include "FatalError.hpp"

FatalError::FatalError() {
    LOG << "[FATAL] " << what() << '\n';
    LOG.close();
}

FatalError::~FatalError() {

}

const char* FatalError::what() const throw() {
    return "Unknown fatal error";
}
