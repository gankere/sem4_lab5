#include "logger.h"
#include <iostream>

void ConsoleLogger::log(const std::string& msg) {
    std::cout << "[LOG] " << msg << std::endl;
}

FileLogger::FileLogger(const std::string& path) {
    file.open(path, std::ios::app);
}

FileLogger::~FileLogger() {
    if (file.is_open()) file.close();
}

void FileLogger::log(const std::string& msg) {
    if (file.is_open()) {
        file << "[LOG] " << msg << std::endl;
    }
}

ILogger* LoggerFactory::createLogger(bool toFile, const std::string& path) {
    if (toFile) {
        return new FileLogger(path);
    } else {
        return new ConsoleLogger();
    }
}