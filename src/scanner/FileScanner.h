// src/scanner/FileScanner.h
#ifndef FILE_SCANNER_H
#define FILE_SCANNER_H

#include <string>
#include <vector>

class FileScanner {
public:
    FileScanner();
    ~FileScanner();
    
    // Рекурсивный обход директории
    std::vector<std::string> scan(const std::string& path);
    
private:
    // Проверка расширения файла
    bool isSourceFile(const std::string& filename);
    
    // Рекурсивный обход
    void scanDirectory(const std::string& path, std::vector<std::string>& result);
};

#endif