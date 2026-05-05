#include <gtest/gtest.h>
#include "FileScanner.h"
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

class FileScannerTest : public ::testing::Test {
protected:
    void SetUp() override {
        testDir = "test_files";
        if (!fs::exists(testDir)) {
            fs::create_directory(testDir);
        }
    }

    void TearDown() override {
        fs::remove_all(testDir);
    }

    void createFile(const std::string& name) {
        std::ofstream file(testDir + "/" + name);
        file << "test content";
    }

    std::string testDir;
};

// ✅ Добавляем макросы TEST_F
TEST_F(FileScannerTest, EmptyDirectory) {
    FileScanner scanner;
    auto files = scanner.scan(testDir);
    EXPECT_EQ(files.size(), 0);
}

TEST_F(FileScannerTest, SingleCppFile) {
    createFile("test.cpp");
    FileScanner scanner;
    auto files = scanner.scan(testDir);
    EXPECT_EQ(files.size(), 1);
    EXPECT_TRUE(files[0].find("test.cpp") != std::string::npos);
}

TEST_F(FileScannerTest, SingleHFile) {
    createFile("test.h");
    FileScanner scanner;
    auto files = scanner.scan(testDir);
    EXPECT_EQ(files.size(), 1);
}

TEST_F(FileScannerTest, MultipleFiles) {
    createFile("a.cpp");
    createFile("b.h");
    createFile("c.txt");
    createFile("d.hpp");
    FileScanner scanner;
    auto files = scanner.scan(testDir);
    EXPECT_EQ(files.size(), 3);
}

TEST_F(FileScannerTest, RecursiveScan) {
    fs::create_directory(testDir + "/subdir");
    createFile("subdir/test.cpp");
    FileScanner scanner;
    auto files = scanner.scan(testDir);
    EXPECT_EQ(files.size(), 1);
}

TEST_F(FileScannerTest, NonExistentDirectory) {
    FileScanner scanner;
    auto files = scanner.scan("nonexistent_dir");
    EXPECT_EQ(files.size(), 0);
}

TEST_F(FileScannerTest, IgnoreWrongExtensions) {
    createFile("test.js");
    createFile("test.py");
    createFile("test.go");
    FileScanner scanner;
    auto files = scanner.scan(testDir);
    EXPECT_EQ(files.size(), 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}