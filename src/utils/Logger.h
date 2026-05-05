#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>

class Logger {
private:
    static Logger* instance;
    bool verboseMode;
    
    Logger() : verboseMode(true) {}
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    
public:
    static Logger& getInstance() {
        if (!instance) {
            instance = new Logger();
        }
        return *instance;
    }
    
    void log(const std::string& message) {
        if (verboseMode) {
            std::cout << "[INFO] " << message << std::endl;
        }
    }
    
    void error(const std::string& message) {
        std::cerr << "[ERROR] " << message << std::endl;
    }
    
    void warning(const std::string& message) {
        std::cerr << "[WARNING] " << message << std::endl;
    }
    
    void setVerbose(bool verbose) { verboseMode = verbose; }
};

#endif