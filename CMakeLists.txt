cmake_minimum_required(VERSION 3.10)
set(CMAKE_OBJECT_PATH_MAX 512)

project(DoxygenLite VERSION 1.0.0)

# Установка политик для устранения предупреждений
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

# Установка стандарта C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Выходная директория для бинарных файлов
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Опция сборки тестов
option(BUILD_TESTS "Build unit tests" OFF)

# Подключение GoogleTest (только если сборка с тестами)
if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(googletest)
endif()

# Создание библиотек
add_library(scanner_lib STATIC src/scanner/FileScanner.cpp)
add_library(parser_lib STATIC src/parser/CodeParser.cpp src/parser/Token.cpp)
add_library(generator_lib STATIC src/generator/HTMLGenerator.cpp)
add_library(utils_lib STATIC src/utils/Logger.cpp src/utils/ConfigManager.cpp)

# Подключение заголовочных файлов
target_include_directories(scanner_lib PUBLIC src/scanner)
target_include_directories(parser_lib PUBLIC src/parser)
target_include_directories(generator_lib PUBLIC src/generator)
target_include_directories(utils_lib PUBLIC src/utils)

# Линковка библиотек между собой
target_link_libraries(parser_lib PRIVATE utils_lib)

# Главный исполняемый файл
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE scanner_lib parser_lib generator_lib utils_lib)
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Флаги компилятора
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Подключение тестов
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()