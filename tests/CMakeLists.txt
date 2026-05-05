# tests/CMakeLists.txt

# Тест для FileScanner
add_executable(test_scanner
    test_scanner.cpp
    ../src/scanner/FileScanner.cpp
)
target_link_libraries(test_scanner PRIVATE gtest gtest_main)
target_include_directories(test_scanner PRIVATE ../src/scanner)
add_test(NAME ScannerTest COMMAND test_scanner)

# Тест для ConfigManager
add_executable(test_config
    test_config.cpp
    ../src/utils/ConfigManager.cpp
)
target_link_libraries(test_config PRIVATE gtest gtest_main)
target_include_directories(test_config PRIVATE ../src/utils)
add_test(NAME ConfigTest COMMAND test_config)

# Тест для Logger
add_executable(test_logger
    test_logger.cpp
    ../src/utils/Logger.cpp
)
target_link_libraries(test_logger PRIVATE gtest gtest_main)
target_include_directories(test_logger PRIVATE ../src/utils)
add_test(NAME LoggerTest COMMAND test_logger)

# Тест для CodeParser
add_executable(test_parser
    test_parser.cpp
    ../src/parser/CodeParser.cpp
    ../src/parser/Token.cpp
    ../src/utils/Logger.cpp
    ../src/utils/ConfigManager.cpp
)
target_link_libraries(test_parser PRIVATE gtest gtest_main)
target_include_directories(test_parser PRIVATE ../src/parser ../src/utils)
add_test(NAME ParserTest COMMAND test_parser)