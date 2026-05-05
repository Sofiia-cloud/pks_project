/**
 * Сценарий 2: Проверка include guard
 */

#include <iostream>
#include <fstream>

int main() {
    std::cout << "=== Сценарий 2: Проверка include guard ===\n\n";
    
    std::string headerCode = R"(
#ifndef MY_HEADER_H
#define MY_HEADER_H

/**
 * @brief Моя функция
 */
void myFunction();

#endif
)";
    
    std::ofstream header("myheader.h");
    header << headerCode;
    header.close();
    
    // Проверяем, что guard присутствует
    std::ifstream readHeader("myheader.h");
    std::string content((std::istreambuf_iterator<char>(readHeader)),
                         std::istreambuf_iterator<char>());
    
    bool hasIfndef = content.find("#ifndef") != std::string::npos;
    bool hasDefine = content.find("#define") != std::string::npos;
    bool hasEndif = content.find("#endif") != std::string::npos;
    
    if (hasIfndef && hasDefine && hasEndif) {
        std::cout << "✅ Include guard присутствует\n";
    } else {
        std::cout << "❌ Include guard отсутствует\n";
    }
    
    std::remove("myheader.h");
    return 0;
}