#include "ConfigManager.h"

ConfigManager* ConfigManager::instance = nullptr;

ConfigManager& ConfigManager::getInstance() {
    if (instance == nullptr) {
        instance = new ConfigManager();
    }
    return *instance;
}