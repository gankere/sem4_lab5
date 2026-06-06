#pragma once
#include <string>
#include <fstream>

class ILogger {
public:
    virtual ~ILogger() = default;
    virtual void log(const std::string& msg) = 0;
};

// вывод в консоль
class ConsoleLogger : public ILogger {
public:
    void log(const std::string& msg) override;
};

// вывод в файл
class FileLogger : public ILogger {
private:
    std::ofstream file;
public:
    FileLogger(const std::string& path);
    ~FileLogger();
    void log(const std::string& msg) override;
};

class LoggerFactory {
public:
    static ILogger* createLogger(bool toFile, const std::string& path = "app.log");
};