#include <iostream>
#include "scanner/FileScanner.h"
#include "parser/CodeParser.h"
#include "generator/HTMLGenerator.h"
#include "utils/ConfigManager.h"
#include "utils/Logger.h"

int main(int argc, char* argv[]) {
    std::cout << "========================================" << std::endl;
    std::cout << "DoxygenLite - Documentation Generator" << std::endl;
    std::cout << "Version 1.0.0" << std::endl;
    std::cout << "========================================" << std::endl;
    
    auto& config = ConfigManager::getInstance();
    auto& logger = Logger::getInstance();
    
    if (argc > 1) {
        config.setInputPath(argv[1]);
        std::cout << "Input path: " << config.getInputPath() << std::endl;
    } else {
        std::cout << "Usage: " << argv[0] << " <input_path>" << std::endl;
        return 1;
    }
    
    config.setOutputPath("./docs");
    
    FileScanner scanner;
    auto files = scanner.scan(config.getInputPath());
    logger.log("Found " + std::to_string(files.size()) + " files");
    
    CodeParser parser;
    auto data = parser.parse(files);
    
    HTMLGenerator generator;
    generator.generate(data, config.getOutputPath());
    
    logger.log("Documentation generated successfully in " + config.getOutputPath());
    
    return 0;
}