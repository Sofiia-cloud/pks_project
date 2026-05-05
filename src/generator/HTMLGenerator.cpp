#include "HTMLGenerator.h"
#include "../parser/CodeParser.h"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void HTMLGenerator::generate(const ProjectData& data, const std::string& outputPath) {
    fs::create_directories(outputPath);
    
    std::ofstream file(outputPath + "/index.html");
    file << "<!DOCTYPE html>\n";
    file << "<html>\n<head>\n";
    file << "<title>" << data.projectName << " - Documentation</title>\n";
    file << "<style>\n";
    file << "body { font-family: Arial; margin: 40px; background-color: #f5f5f5; }\n";
    file << "h1 { color: #6a0bff; }\n";
    file << ".function { background: white; border: 1px solid #ddd; margin: 10px 0; padding: 15px; border-radius: 8px; }\n";
    file << ".function-name { font-weight: bold; color: #6a0bff; font-size: 18px; }\n";
    file << ".brief { color: green; margin: 5px 0; }\n";
    file << ".params { color: #666; margin: 5px 0; }\n";
    file << ".returns { color: #6a0bff; margin: 5px 0; }\n";
    file << "</style>\n";
    file << "</head>\n<body>\n";
    
    file << "<h1>" << data.projectName << "</h1>\n";
    file << "<h2>Functions (" << data.functions.size() << ")</h2>\n";
    
    for (const auto& func : data.functions) {
        file << "<div class='function'>\n";
        file << "<div class='function-name'>" << func.name << "()</div>\n";
        if (!func.brief.empty()) {
            file << "<div class='brief'>📝 " << func.brief << "</div>\n";
        }
        if (!func.paramDesc.empty()) {
            file << "<div class='params'>📥 Parameters: " << func.paramDesc << "</div>\n";
        }
        if (!func.returnDesc.empty()) {
            file << "<div class='returns'>📤 Returns: " << func.returnDesc << "</div>\n";
        }
        file << "</div>\n";
    }
    
    file << "</body>\n</html>\n";
    file.close();
}