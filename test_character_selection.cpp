// Unit tests for Character Selection system
#include "catch.hpp"
#include "character_selection.h"
#include <SFML/Graphics.hpp>

TEST_CASE("CharacterSelection works correctly", "[character_selection]") {
    // Create a simple window for testing
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    
    SECTION("CharacterSelection can be created") {
        CharacterSelection selection(&window);
        REQUIRE(selection.get_selected_character() == nullptr);
    }
    
    SECTION("CharacterSelection can add characters") {
        CharacterSelection selection(&window);
        REQUIRE(selection.get_character_count() == 0);
        
        // Add a character
        std::string testSpritePath = "../assets/sprites/test2.png";
        selection.add_character(testSpritePath, "Test Character");
        REQUIRE(selection.get_character_count() == 1);
    }
    
    SECTION("CharacterSelection can select characters") {
        CharacterSelection selection(&window);
        
        // Add characters
        selection.add_character("../assets/sprites/test2.png", "Test Character 1");
        selection.add_character("../assets/sprites/hokage_minato_namikaze.png", "Test Character 2");
        
        REQUIRE(selection.get_character_count() == 2);
        
        // Select first character
        selection.select_character(0);
        REQUIRE(selection.get_selected_character() != nullptr);
        REQUIRE(selection.get_selected_character_name() == "Test Character 1");
    }
}