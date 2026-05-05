#ifndef FILE_SCANNER_H
#define FILE_SCANNER_H

#include <string>
#include <vector>

class FileScanner {
public:
    FileScanner();
    ~FileScanner();
    
    std::vector<std::string> scan(const std::string& path);
    
private:
    bool isSourceFile(const std::string& filename);
    void scanDirectory(const std::string& path, std::vector<std::string>& result);
};

#endif