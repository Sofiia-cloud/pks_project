#ifndef HTML_GENERATOR_H
#define HTML_GENERATOR_H

#include <string>

struct ProjectData;

class HTMLGenerator {
public:
    void generate(const ProjectData& data, const std::string& outputPath);
};

#endif