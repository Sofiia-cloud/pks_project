#include <iostream>
#include "scanner/FileScanner.h"
#include "parser/CodeParser.h"
#include "generator/HTMLGenerator.h"
#include "utils/ConfigManager.h"

int main(int argc, char* argv[]) {
    std::cout << "DoxygenLite - Documentation Generator" << std::endl;
    std::cout << "Version 1.0.0" << std::endl;
    
    // Пример использования ConfigManager (Singleton)
    auto& config = ConfigManager::getInstance();
    
    if (argc > 1) {
        config.setInputPath(argv[1]);
        std::cout << "Input path: " << config.getInputPath() << std::endl;
    } else {
        std::cout << "Usage: " << argv[0] << " <input_path>" << std::endl;
        return 1;
    }
    
    // Сканирование файлов
    FileScanner scanner;
    auto files = scanner.scan(config.getInputPath());
    std::cout << "Found " << files.size() << " files" << std::endl;
    
    // Парсинг
    CodeParser parser;
    auto data = parser.parse(files);
    
    // Генерация документации
    HTMLGenerator generator;
    generator.generate(data, "./docs");
    
    std::cout << "Documentation generated successfully!" << std::endl;
    return 0;
}