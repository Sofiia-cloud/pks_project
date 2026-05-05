# tests/scenarios/CMakeLists.txt

add_executable(scenario_basic scenario_basic_generation.cpp)
target_link_libraries(scenario_basic PRIVATE scanner_lib parser_lib generator_lib utils_lib ${Boost_FILESYSTEM_LIBRARY})
target_include_directories(scenario_basic PRIVATE src)

add_executable(scenario_guard scenario_include_guard.cpp)

add_executable(scenario_memory scenario_memory_leak_test.cpp)

# Добавление сценариев в CTest
add_test(NAME BasicGeneration COMMAND scenario_basic)
add_test(NAME IncludeGuard COMMAND scenario_guard)
add_test(NAME MemoryTest COMMAND scenario_memory)