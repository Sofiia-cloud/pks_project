#ifndef CODE_PARSER_H
#define CODE_PARSER_H

#include <string>
#include <vector>

struct FunctionInfo {
    std::string name;
    std::string returnType;
    std::vector<std::string> params;
    std::string brief;
    std::string paramDesc;
    std::string returnDesc;
};

struct ClassInfo {
    std::string name;
    std::vector<FunctionInfo> methods;
    std::string brief;
};

struct ProjectData {
    std::string projectName;
    std::vector<FunctionInfo> functions;
    std::vector<ClassInfo> classes;
    std::vector<std::string> comments;
};

class CodeParser {
public:
    ProjectData parse(const std::vector<std::string>& files);
};

#endif