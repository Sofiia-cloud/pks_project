#include "CodeParser.h"
#include "Token.h"
#include "../utils/Logger.h"
#include <fstream>
#include <regex>
#include <filesystem>

ProjectData CodeParser::parse(const std::vector<std::string>& files) {
    ProjectData data;
    data.projectName = "DoxygenLite Project";
    
    for (const auto& file : files) {
        std::ifstream stream(file);
        if (!stream.is_open()) {
            Logger::getInstance().warning("Cannot open file: " + file);
            continue;
        }
        
        std::string content((std::istreambuf_iterator<char>(stream)),
                             std::istreambuf_iterator<char>());
        
        // Поиск классов
        std::regex classRegex(R"(class\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*(?::\s*[a-zA-Z_][a-zA-Z0-9_]*)?\s*\{)");
        std::smatch classMatch;
        std::string::const_iterator classSearchStart(content.cbegin());
        
        while (std::regex_search(classSearchStart, content.cend(), classMatch, classRegex)) {
            ClassInfo cls;
            cls.name = classMatch[1].str();
            
            // Ищем методы внутри класса
            std::string classContent = classMatch[0].str();
            std::regex methodRegex(R"((?:/\*\*[^*]*\*+/)?\s*([a-zA-Z_][a-zA-Z0-9_]*)\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*\([^)]*\)\s*\{?)");
            std::smatch methodMatch;
            std::string::const_iterator methodSearchStart(classContent.cbegin());
            
            while (std::regex_search(methodSearchStart, classContent.cend(), methodMatch, methodRegex)) {
                FunctionInfo func;
                func.name = methodMatch[2].str();
                func.returnType = methodMatch[1].str();
                cls.methods.push_back(func);
                methodSearchStart = methodMatch[0].second;
            }
            
            data.classes.push_back(cls);
            classSearchStart = classMatch[0].second;
        }
        
        // Поиск функций
        std::regex funcRegex(R"(/\*\*([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*\*/\s*([a-zA-Z_][a-zA-Z0-9_]*)\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*\([^)]*\)\s*\{?)");
        
        std::smatch funcMatch;
        std::string::const_iterator funcSearchStart(content.cbegin());
        
        while (std::regex_search(funcSearchStart, content.cend(), funcMatch, funcRegex)) {
            FunctionInfo func;
            func.name = funcMatch[5].str();
            func.returnType = funcMatch[4].str();
            
            std::string comment = funcMatch[0].str();
            
            // Извлечение @brief
            std::regex briefRegex(R"(@brief\s+([^\n@]*))");
            std::smatch briefMatch;
            if (std::regex_search(comment, briefMatch, briefRegex)) {
                func.brief = briefMatch[1].str();
            }
            
            // Извлечение @param
            std::regex paramRegex(R"(@param\s+([^\s]+)\s+([^\n@]*))");
            std::string params;
            auto paramBegin = std::sregex_iterator(comment.begin(), comment.end(), paramRegex);
            auto paramEnd = std::sregex_iterator();
            for (auto it = paramBegin; it != paramEnd; ++it) {
                if (!params.empty()) params += ", ";
                params += (*it)[1].str() + ": " + (*it)[2].str();
            }
            func.paramDesc = params;
            
            // Извлечение @return
            std::regex returnRegex(R"(@return\s+([^\n@]*))");
            std::smatch returnMatch;
            if (std::regex_search(comment, returnMatch, returnRegex)) {
                func.returnDesc = returnMatch[1].str();
            }
            
            data.functions.push_back(func);
            funcSearchStart = funcMatch[0].second;
        }
        
        Logger::getInstance().log("Parsed: " + file + " (" + 
            std::to_string(data.functions.size()) + " functions, " + 
            std::to_string(data.classes.size()) + " classes)");
    }
    
    return data;
}