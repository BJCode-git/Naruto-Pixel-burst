// Unit tests for Settings class

#include "catch.hpp"
#include "settings.h"
#include <SFML/Graphics.hpp>

TEST_CASE("Settings handles keyboard commands correctly", "[settings]") {
    Settings settings;
    
    SECTION("Keyboard commands map correctly") {
        // Test that the expected keys are mapped to commands
        REQUIRE(settings.kb_action(sf::Keyboard::Left) == moveLeft);
        REQUIRE(settings.kb_action(sf::Keyboard::Right) == moveRight);
        REQUIRE(settings.kb_action(sf::Keyboard::Up) == Jump);
        REQUIRE(settings.kb_action(sf::Keyboard::Down) == Crounch);
        REQUIRE(settings.kb_action(sf::Keyboard::Space) == Jutsu);
    }
}

TEST_CASE("Settings handles joystick commands correctly", "[settings]") {
    Settings settings;
    
    SECTION("Joystick commands map correctly") {
        // Test that the expected buttons are mapped to commands
        REQUIRE(settings.joy_action(0) == joySquare);
        REQUIRE(settings.joy_action(1) == joyTriangle);
        REQUIRE(settings.joy_action(2) == joyCircle);
        REQUIRE(settings.joy_action(3) == joyJutsu);
        REQUIRE(settings.joy_action(4) == joyThrow);
        REQUIRE(settings.joy_action(5) == joyTeleport);
        REQUIRE(settings.joy_action(6) == joyDash);
    }
}