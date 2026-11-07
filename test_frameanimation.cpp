// Unit tests for Naruto Pixel Burst components
// Test file for FrameAnimation class

#include "catch.hpp"
#include "frameanimation.h"
#include <SFML/Graphics.hpp>

TEST_CASE("FrameAnimation works correctly", "[frameanimation]") {
    // Create a simple animation with 3 frames
    std::vector<sf::IntRect> frames = {
        sf::IntRect(0, 0, 32, 32),
        sf::IntRect(32, 0, 32, 32),
        sf::IntRect(64, 0, 32, 32)
    };
    
    FrameAnimation anim(frames);
    
    SECTION("Animation starts at first frame") {
        sf::IntRect firstFrame = anim.next();
        REQUIRE(firstFrame.left == 0);
        REQUIRE(firstFrame.top == 0);
        REQUIRE(firstFrame.width == 32);
        REQUIRE(firstFrame.height == 32);
    }
    
    SECTION("Animation cycles through frames") {
        sf::IntRect frame1 = anim.next();
        sf::IntRect frame2 = anim.next();
        sf::IntRect frame3 = anim.next();
        
        REQUIRE(frame1.left == 0);
        REQUIRE(frame2.left == 32);
        REQUIRE(frame3.left == 64);
    }
    
    SECTION("Animation loops correctly") {
        // Advance through all frames
        anim.next(); // frame 1
        anim.next(); // frame 2
        anim.next(); // frame 3
        
        // Now it should loop back to frame 1
        sf::IntRect loopFrame = anim.next();
        REQUIRE(loopFrame.left == 0);
    }
}