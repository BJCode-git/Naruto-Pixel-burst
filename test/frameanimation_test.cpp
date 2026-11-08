#include <gtest/gtest.h>
#include "frameanimation.h"
#include <vector>

class FrameAnimationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup common to all tests
    }
    
    void TearDown() override {
        // Cleanup common to all tests
    }
};

TEST_F(FrameAnimationTest, ConstructorDefault) {
    FrameAnimation animation;
    EXPECT_TRUE(animation.is_end());
}

TEST_F(FrameAnimationTest, ConstructorWithFrames) {
    std::vector<sf::IntRect> frames = {
        sf::IntRect(0, 0, 10, 10),
        sf::IntRect(10, 0, 10, 10),
        sf::IntRect(20, 0, 10, 10)
    };
    
    FrameAnimation animation(frames);
    EXPECT_FALSE(animation.is_end());
    EXPECT_EQ(animation.next(), frames[0]);
    EXPECT_EQ(animation.next(), frames[1]);
    EXPECT_EQ(animation.next(), frames[2]);
    EXPECT_TRUE(animation.is_end());
}

TEST_F(FrameAnimationTest, ContinuousAnimation) {
    std::vector<sf::IntRect> frames = {
        sf::IntRect(0, 0, 10, 10),
        sf::IntRect(10, 0, 10, 10)
    };
    
    FrameAnimation animation(frames, true);
    EXPECT_FALSE(animation.is_end());
    
    // Should cycle through frames continuously
    EXPECT_EQ(animation.next(), frames[0]);
    EXPECT_EQ(animation.next(), frames[1]);
    EXPECT_EQ(animation.next(), frames[0]); // Should cycle back
    EXPECT_EQ(animation.next(), frames[1]); // Should cycle again
}

TEST_F(FrameAnimationTest, TimeFunction) {
    std::vector<sf::IntRect> frames = {
        sf::IntRect(0, 0, 10, 10),
        sf::IntRect(10, 0, 10, 10)
    };
    
    FrameAnimation animation(frames, false, sf::seconds(2.0));
    EXPECT_EQ(animation.time(), sf::seconds(2.0));
}