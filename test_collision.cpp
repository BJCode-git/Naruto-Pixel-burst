/*
 * File:   test_collision.cpp
 * Author: Julien
 *
 * Created on November 7, 2026, 7:06 PM
 */

#include "catch.hpp"
#include <SFML/Graphics.hpp>
#include "Collision.h"

TEST_CASE("Collision functions work correctly", "[collision]") {
    // Create a simple window for testing
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    
    // Create simple textures for testing
    sf::Texture texture1, texture2;
    sf::Sprite sprite1, sprite2;
    
    // Create simple textures
    sf::Image img1, img2;
    img1.create(50, 50, sf::Color::Red);
    img2.create(50, 50, sf::Color::Blue);
    
    texture1.loadFromImage(img1);
    texture2.loadFromImage(img2);
    
    sprite1.setTexture(texture1);
    sprite2.setTexture(texture2);
    
    SECTION("CircleTest detects collision correctly") {
        // Set positions for sprites that should collide
        sprite1.setPosition(0, 0);
        sprite2.setPosition(40, 40);
        
        // Test with sprites that should collide
        bool result = Collision::CircleTest(sprite1, sprite2);
        REQUIRE(result == true);
    }
    
    SECTION("CircleTest detects no collision correctly") {
        // Set positions for sprites that won't collide
        sprite1.setPosition(0, 0);
        sprite2.setPosition(100, 100);
        
        // Test with sprites that should NOT collide
        bool result = Collision::CircleTest(sprite1, sprite2);
        REQUIRE(result == false);
    }
    
    SECTION("BoundingBoxTest detects collision correctly") {
        // Set positions for sprites that should collide
        sprite1.setPosition(0, 0);
        sprite2.setPosition(40, 40);
        
        // Test with sprites that should collide
        bool result = Collision::BoundingBoxTest(sprite1, sprite2);
        REQUIRE(result == true);
    }
    
    SECTION("BoundingBoxTest detects no collision correctly") {
        // Set positions for sprites that won't collide
        sprite1.setPosition(0, 0);
        sprite2.setPosition(100, 100);
        
        // Test with sprites that should NOT collide
        bool result = Collision::BoundingBoxTest(sprite1, sprite2);
        REQUIRE(result == false);
    }
    
    SECTION("PixelPerfectTest detects collision correctly") {
        // Set positions for sprites that should collide
        sprite1.setPosition(0, 0);
        sprite2.setPosition(40, 40);
        
        // Test with sprites that should collide (using default alpha limit of 0)
        bool result = Collision::PixelPerfectTest(sprite1, sprite2, 0);
        REQUIRE(result == true);
    }
}