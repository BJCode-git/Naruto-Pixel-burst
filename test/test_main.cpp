#include <gtest/gtest.h>

// Test unitaire basique pour vérifier que le setup fonctionne
TEST(ExampleTest, BasicTest) {
    EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}