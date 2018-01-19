#ifndef __LOG_HPP__
#define __LOG_HPP__

#include <iostream>
#include <fstream>
#include "Loggable.hpp"

#define LOG Log::getInstance()
#define LOG_FILENAME "log.txt"

class Log {
public:
    static Log& getInstance();
    static void close();

    // Template method should never be in .cpp file
    // cf : https://tinyurl.com/yak7ub7z
    template <typename T>
    Log& operator<<(const T &val) {
        std::cout << val;
        m_logFile << val;
        return *this;
    }

    Log& operator<<(const bool &boolean);
    Log& operator<<(const Loggable &logClass);

private:
    Log(const std::string filename);
    Log(const Log& log);
    virtual ~Log();

    static Log* m_instance;
    static std::ofstream m_logFile;
};

#endif /* __LOG_HPP__ */