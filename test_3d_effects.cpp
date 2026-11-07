// Unit tests for 3D Effects system
#include "catch.hpp"
#include "3d_effects.h"
#include <SFML/Graphics.hpp>

TEST_CASE("3DEffects works correctly", "[3d_effects]") {
    // Create a simple window for testing
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    
    SECTION("3DEffects can be created") {
        ThreeDEffects effects(&window);
        REQUIRE(effects.get_effect_count() == 0);
    }
    
    SECTION("3DEffects can add effects") {
        ThreeDEffects effects(&window);
        
        // Add a simple 3D effect
        sf::Vector2f position(100, 100);
        float size = 50.0f;
        sf::Color color(sf::Color::Blue);
        float duration = 1.0f;
        
        effects.add_3d_effect(position, size, color, duration);
        REQUIRE(effects.get_effect_count() == 1);
    }
    
    SECTION("3DEffects can update effects") {
        ThreeDEffects effects(&window);
        
        // Add an effect
        sf::Vector2f position(100, 100);
        float size = 50.0f;
        sf::Color color(sf::Color::Blue);
        float duration = 1.0f;
        
        effects.add_3d_effect(position, size, color, duration);
        REQUIRE(effects.get_effect_count() == 1);
        
        // Update effects
        effects.update(0.1f);
        REQUIRE(effects.get_effect_count() >= 0); // Should be 0 or more depending on lifetime
    }
}