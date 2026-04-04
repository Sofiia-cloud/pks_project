#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <string>

class ConfigManager {
private:
    // Приватный конструктор (Singleton)
    ConfigManager() = default;
    
    // Запрет копирования
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;
    
    static ConfigManager* instance;
    
    std::string inputPath;
    std::string outputPath;
    bool recursiveMode;
    
public:
    static ConfigManager& getInstance();
    
    void setInputPath(const std::string& path) { inputPath = path; }
    std::string getInputPath() const { return inputPath; }
    
    void setOutputPath(const std::string& path) { outputPath = path; }
    std::string getOutputPath() const { return outputPath; }
    
    void setRecursiveMode(bool mode) { recursiveMode = mode; }
    bool getRecursiveMode() const { return recursiveMode; }
};

#endif