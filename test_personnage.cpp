// Unit tests for Personnage class

#include "catch.hpp"
#include "personnage.h"
#include "frameanimation.h"
#include <SFML/Graphics.hpp>

TEST_CASE("Personnage initialization works correctly", "[personnage]") {
    // Create a simple window for testing
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    
    SECTION("Personnage can be created") {
        Personnage test(&window, "../assets/sprites/test2.png", sf::Color::White);
        REQUIRE(test.get_sprite() != nullptr);
    }
}

TEST_CASE("Personnage animation system works", "[personnage]") {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    
    SECTION("Personnage can set animations") {
        Personnage test(&window, "../assets/sprites/test2.png", sf::Color::White);
        
        // Create simple animation frames
        std::vector<sf::IntRect> frames = {
            sf::IntRect(0, 0, 32, 32),
            sf::IntRect(32, 0, 32, 32)
        };
        
        FrameAnimation anim(frames);
        std::map<Dir_perso, FrameAnimation> animations;
        animations[Dir_Stance] = anim;
        
        test.set_animations(animations);
        
        REQUIRE(test.get_sprite() != nullptr);
    }
}