/**
 * Сценарий 1: Базовая генерация документации
 * 
 * Шаги:
 * 1. Создать тестовый файл с комментариями
 * 2. Запустить сканер для поиска файлов
 * 3. Запустить парсер для извлечения комментариев
 * 4. Запустить генератор HTML
 * 5. Проверить, что HTML файл создан
 */

#include <iostream>
#include <fstream>
#include <filesystem>
#include "../src/scanner/FileScanner.h"
#include "../src/parser/CodeParser.h"
#include "../src/generator/HTMLGenerator.h"
#include "../src/utils/ConfigManager.h"

namespace fs = std::filesystem;

int main() {
    std::cout << "=== Сценарий 1: Базовая генерация документации ===\n\n";
    
    // 1. Создаём тестовый файл
    std::string testCode = R"(
        /**
         * @brief Приветствие пользователя
         * @param name Имя пользователя
         */
        void greet(const std::string& name) {
            std::cout << "Hello, " << name << "!" << std::endl;
        }
        
        /// @brief Основная функция программы
        int main() {
            greet("World");
            return 0;
        }
    )";
    
    std::ofstream testFile("sample.cpp");
    testFile << testCode;
    testFile.close();
    
    // 2. Сканируем файлы
    FileScanner scanner;
    auto files = scanner.scan(".");
    std::cout << "Найдено файлов: " << files.size() << std::endl;
    
    // 3. Парсим
    CodeParser parser;
    auto data = parser.parse(files);
    std::cout << "Извлечено функций: " << data.functions.size() << std::endl;
    
    // 4. Генерируем HTML
    HTMLGenerator generator;
    generator.generate(data, "./docs");
    std::cout << "Документация сгенерирована в ./docs\n";
    
    // 5. Проверяем результат
    if (fs::exists("./docs/index.html")) {
        std::cout << "✅ index.html создан успешно!\n";
    } else {
        std::cout << "❌ Ошибка: index.html не создан\n";
        return 1;
    }
    
    // Очистка
    fs::remove("sample.cpp");
    fs::remove_all("./docs");
    
    return 0;
}