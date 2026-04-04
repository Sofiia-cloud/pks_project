// src/scanner/FileScanner.cpp
#include "FileScanner.h"
#include <iostream>
#include <filesystem>  // C++17 стандартная библиотека, не требует установки
#include <string>
#include <vector>

namespace fs = std::filesystem;

FileScanner::FileScanner() {}

FileScanner::~FileScanner() {}

bool FileScanner::isSourceFile(const std::string& filename) {
    std::vector<std::string> extensions = {".cpp", ".h", ".c", ".hpp", ".cc", ".cxx"};
    for (const auto& ext : extensions) {
        if (filename.length() >= ext.length() &&
            filename.compare(filename.length() - ext.length(), ext.length(), ext) == 0) {
            return true;
        }
    }
    return false;
}

void FileScanner::scanDirectory(const std::string& path, std::vector<std::string>& result) {
    try {
        fs::path dirPath(path);
        if (!fs::exists(dirPath) || !fs::is_directory(dirPath)) {
            std::cerr << "Error: " << path << " is not a valid directory" << std::endl;
            return;
        }
        
        for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {
            if (fs::is_regular_file(entry.path())) {
                std::string filename = entry.path().string();
                if (isSourceFile(filename)) {
                    result.push_back(filename);
                    std::cout << "Found: " << filename << std::endl;
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
}

std::vector<std::string> FileScanner::scan(const std::string& path) {
    std::vector<std::string> result;
    scanDirectory(path, result);
    return result;
}