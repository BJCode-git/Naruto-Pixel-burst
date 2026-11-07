// Unit tests for Arena system with parallax effects
#include "catch.hpp"
#include "arena.h"
#include <SFML/Graphics.hpp>

TEST_CASE("Arena works correctly", "[arena]") {
    // Create a simple window for testing
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    
    SECTION("Arena can be created") {
        Arena arena(&window, "../assets/backgrounds/ValleyOfthEnd-0.png");
        REQUIRE(arena.get_background() != nullptr);
    }
    
    SECTION("Arena handles parallax layers") {
        Arena arena(&window, "../assets/backgrounds/ValleyOfthEnd-0.png");
        
        // Add some parallax layers
        arena.add_parallax_layer("../assets/backgrounds/ValleyOfthEnd-0.png", 0.5f);
        arena.add_parallax_layer("../assets/backgrounds/ValleyOfthEnd-0.png", 0.3f);
        
        REQUIRE(arena.get_parallax_layer_count() == 2);
    }
}