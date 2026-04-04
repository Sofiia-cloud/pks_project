#ifndef CODE_PARSER_H
#define CODE_PARSER_H

#include <string>
#include <vector>

struct ProjectData {
    std::string projectName;
    // Добавьте поля по мере необходимости
};

class CodeParser {
public:
    ProjectData parse(const std::vector<std::string>& files);
};

#endif