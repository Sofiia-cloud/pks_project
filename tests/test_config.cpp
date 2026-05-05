#include <gtest/gtest.h>
#include "ConfigManager.h"

class ConfigManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        auto& config = ConfigManager::getInstance();
        config.setInputPath("");
        config.setOutputPath("");
        config.setRecursiveMode(false);
    }
};

TEST_F(ConfigManagerTest, SetAndGetInputPath) {
    auto& config = ConfigManager::getInstance();
    config.setInputPath("/home/user/project");
    EXPECT_EQ(config.getInputPath(), "/home/user/project");
}

TEST_F(ConfigManagerTest, SetAndGetOutputPath) {
    auto& config = ConfigManager::getInstance();
    config.setOutputPath("/home/user/docs");
    EXPECT_EQ(config.getOutputPath(), "/home/user/docs");
}

TEST_F(ConfigManagerTest, SetAndGetRecursiveMode) {
    auto& config = ConfigManager::getInstance();
    config.setRecursiveMode(true);
    EXPECT_TRUE(config.getRecursiveMode());
    config.setRecursiveMode(false);
    EXPECT_FALSE(config.getRecursiveMode());
}

TEST_F(ConfigManagerTest, DefaultValues) {
    auto& config = ConfigManager::getInstance();
    EXPECT_EQ(config.getInputPath(), "");
    EXPECT_EQ(config.getOutputPath(), "");
    EXPECT_FALSE(config.getRecursiveMode());
}

TEST_F(ConfigManagerTest, EmptyStrings) {
    auto& config = ConfigManager::getInstance();
    config.setInputPath("");
    config.setOutputPath("");
    EXPECT_EQ(config.getInputPath(), "");
    EXPECT_EQ(config.getOutputPath(), "");
}

TEST_F(ConfigManagerTest, SingletonInstance) {
    auto& config1 = ConfigManager::getInstance();
    auto& config2 = ConfigManager::getInstance();
    EXPECT_EQ(&config1, &config2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}