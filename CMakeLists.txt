cmake_minimum_required(VERSION 3.10)

# Решение проблемы с длинными путями
set(CMAKE_OBJECT_PATH_MAX 512)

project(DoxygenLite VERSION 1.0.0)

# Установка стандарта C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Выходная директория для бинарных файлов
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Проверяем существование файлов перед добавлением
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/scanner/FileScanner.cpp)
    add_library(scanner_lib STATIC
        src/scanner/FileScanner.cpp
    )
    target_include_directories(scanner_lib PUBLIC src/scanner)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/parser/CodeParser.cpp)
    add_library(parser_lib STATIC
        src/parser/CodeParser.cpp
        src/parser/Token.cpp
    )
    target_include_directories(parser_lib PUBLIC src/parser)
endif()

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/generator/HTMLGenerator.cpp)
    add_library(generator_lib STATIC
        src/generator/HTMLGenerator.cpp
    )
    target_include_directories(generator_lib PUBLIC src/generator)
endif()

# Создаём utils_lib только если есть файлы
set(UTILS_SOURCES "")
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/ConfigManager.cpp)
    list(APPEND UTILS_SOURCES src/utils/ConfigManager.cpp)
endif()
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/Logger.cpp)
    list(APPEND UTILS_SOURCES src/utils/Logger.cpp)
endif()

if(UTILS_SOURCES)
    add_library(utils_lib STATIC ${UTILS_SOURCES})
    target_include_directories(utils_lib PUBLIC src/utils)
endif()

# Главный исполняемый файл
add_executable(${PROJECT_NAME} src/main.cpp)

# Линковка существующих библиотек
if(TARGET scanner_lib)
    target_link_libraries(${PROJECT_NAME} PRIVATE scanner_lib)
endif()
if(TARGET parser_lib)
    target_link_libraries(${PROJECT_NAME} PRIVATE parser_lib)
endif()
if(TARGET generator_lib)
    target_link_libraries(${PROJECT_NAME} PRIVATE generator_lib)
endif()
if(TARGET utils_lib)
    target_link_libraries(${PROJECT_NAME} PRIVATE utils_lib)
endif()

# Подключение заголовков
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Флаги компилятора
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Выводим информацию о сборке
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")