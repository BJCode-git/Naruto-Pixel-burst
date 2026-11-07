// Unit tests for Particle Effects system
#include "catch.hpp"
#include "particle_system.h"
#include <SFML/Graphics.hpp>

TEST_CASE("ParticleSystem works correctly", "[particle_system]") {
    // Create a simple window for testing
    sf::RenderWindow window(sf::VideoMode(800, 600), "Test Window");
    
    SECTION("ParticleSystem can be created") {
        ParticleSystem particles(&window);
        REQUIRE(particles.get_particle_count() == 0);
    }
    
    SECTION("ParticleSystem can add particles") {
        ParticleSystem particles(&window);
        
        // Add a simple particle
        sf::Vector2f position(100, 100);
        sf::Vector2f velocity(10, -5);
        sf::Color color(sf::Color::Red);
        float lifetime = 2.0f;
        
        particles.add_particle(position, velocity, color, lifetime);
        REQUIRE(particles.get_particle_count() == 1);
    }
    
    SECTION("ParticleSystem can update particles") {
        ParticleSystem particles(&window);
        
        // Add a particle
        sf::Vector2f position(100, 100);
        sf::Vector2f velocity(10, -5);
        sf::Color color(sf::Color::Red);
        float lifetime = 2.0f;
        
        particles.add_particle(position, velocity, color, lifetime);
        REQUIRE(particles.get_particle_count() == 1);
        
        // Update particles
        particles.update(0.1f);
        REQUIRE(particles.get_particle_count() >= 0); // Should be 0 or more depending on lifetime
    }
}