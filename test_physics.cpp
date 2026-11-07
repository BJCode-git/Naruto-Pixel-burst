// Unit tests for Physics Engine

#include "catch.hpp"
#include "Little_Physics_Engine.h"
#include <SFML/Graphics.hpp>

TEST_CASE("Physics engine calculates parabolic trajectory", "[physics]") {
    SECTION("Jump trajectory calculation") {
        sf::Vector2f position(0, 0);
        sf::Vector2f result = Jump_Parabole(position);
        
        // Just check that it doesn't crash and returns reasonable values
        REQUIRE(result.x == 0);
        REQUIRE(result.y == 0);
    }
}