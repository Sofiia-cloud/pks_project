#include <gtest/gtest.h>
#include "Logger.h"
#include <sstream>
#include <iostream>

class LoggerTest : public ::testing::Test {
protected:
    void SetUp() override {
        oldCout = std::cout.rdbuf(stream.rdbuf());
        oldCerr = std::cerr.rdbuf(stream.rdbuf());
        Logger::getInstance().setVerbose(true);
    }

    void TearDown() override {
        std::cout.rdbuf(oldCout);
        std::cerr.rdbuf(oldCerr);
    }

    std::stringstream stream;
    std::streambuf* oldCout;
    std::streambuf* oldCerr;
};

TEST_F(LoggerTest, LogMessage) {
    Logger::getInstance().log("Test message");
    std::string output = stream.str();
    EXPECT_TRUE(output.find("[INFO] Test message") != std::string::npos);
}

TEST_F(LoggerTest, ErrorMessage) {
    Logger::getInstance().error("Test error");
    std::string output = stream.str();
    EXPECT_TRUE(output.find("[ERROR] Test error") != std::string::npos);
}

TEST_F(LoggerTest, WarningMessage) {
    Logger::getInstance().warning("Test warning");
    std::string output = stream.str();
    EXPECT_TRUE(output.find("[WARNING] Test warning") != std::string::npos);
}

TEST_F(LoggerTest, EmptyMessage) {
    Logger::getInstance().log("");
    std::string output = stream.str();
    EXPECT_TRUE(output.find("[INFO] ") != std::string::npos);
}

TEST_F(LoggerTest, LongMessage) {
    std::string longMsg(1000, 'A');
    Logger::getInstance().log(longMsg);
    std::string output = stream.str();
    EXPECT_TRUE(output.find(longMsg) != std::string::npos);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}