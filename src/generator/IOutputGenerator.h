#ifndef I_OUTPUT_GENERATOR_H
#define I_OUTPUT_GENERATOR_H

#include <string>

struct ProjectData;

class IOutputGenerator {
public:
    virtual void generate(const ProjectData& data, const std::string& outputPath) = 0;
    virtual ~IOutputGenerator() = default;
};

#endif