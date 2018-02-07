#include <iostream>
#include "Log.hpp"

Log* Log::m_instance = nullptr;
std::ofstream Log::m_logFile;

Log& Log::getInstance() {
    if(m_instance == nullptr) {
        m_instance = new Log(LOG_FILENAME);
    }

    return *m_instance;
}

void Log::close() {
    if(m_instance != nullptr) {
#ifdef DEBUG
        std::cout << "CLOSE LOG" << std::endl;
#endif
        m_logFile.close();
        delete m_instance;
        m_instance = nullptr;
    }
}

Log& Log::operator<<(const bool &boolean) {
    std::string boolean_str;
    if (boolean == true) {
        boolean_str = "true";
    }
    else {
        boolean_str = "false";
    }

    LOG << boolean_str;
    return *this;
}

Log& Log::operator<<(const Loggable &logClass) {
//    std::cout << logClass.toString();
//    m_logFile << logClass.toString();
    return *this;
}

Log::Log(const std::string filename) {
    m_logFile.open(filename);
}

Log::Log(const Log &log) : Log(LOG_FILENAME) {

}

Log::~Log() {

}
