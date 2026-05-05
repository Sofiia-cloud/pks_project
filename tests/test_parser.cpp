#include <gtest/gtest.h>
#include "CodeParser.h"
#include <fstream>

class ParserTest : public ::testing::Test {
protected:
    void SetUp() override {
        createTestFile("test.cpp", content);
    }

    void TearDown() override {
        std::remove("test.cpp");
    }

    void createTestFile(const std::string& name, const std::string& content) {
        std::ofstream file(name);
        file << content;
    }

    std::string content;
};

TEST_F(ParserTest, SimpleFunctionWithComment) {
    content = R"(
        /**
         * @brief Вычисляет сумму двух чисел
         * @param a Первое число
         * @param b Второе число
         * @return Сумма a и b
         */
        int sum(int a, int b) {
            return a + b;
        }
    )";
    createTestFile("test.cpp", content);
    
    CodeParser parser;
    std::vector<std::string> files = {"test.cpp"};
    auto data = parser.parse(files);
    
    EXPECT_GT(data.functions.size(), 0);
}

TEST_F(ParserTest, ClassWithMethods) {
    content = R"(
        class Calculator {
            /**
             * @brief Добавляет два числа
             */
            int add(int a, int b) { return a + b; }
        };
    )";
    createTestFile("test.cpp", content);
    
    CodeParser parser;
    std::vector<std::string> files = {"test.cpp"};
    auto data = parser.parse(files);
    
    EXPECT_GT(data.classes.size(), 0);
}

TEST_F(ParserTest, EmptyFile) {
    content = "";
    createTestFile("test.cpp", content);
    
    CodeParser parser;
    std::vector<std::string> files = {"test.cpp"};
    auto data = parser.parse(files);
    
    EXPECT_TRUE(data.classes.empty());
    EXPECT_TRUE(data.functions.empty());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}