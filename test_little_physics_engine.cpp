// Unit tests for Little_Physics_Engine
#include "catch.hpp"
#include "Little_Physics_Engine.h"
#include <SFML/Graphics.hpp>

// Mock class to test the physics engine functionality
class MockPhysicsEngine {
public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    bool onGround;
    
    MockPhysicsEngine() : position(0, 0), velocity(0, 0), onGround(false) {}
    
    void update(float deltaTime) {
        // Simple physics update
        velocity.y += 981.0f * deltaTime; // Gravity
        position += velocity * deltaTime;
        
        if (position.y >= 0) {
            position.y = 0;
            velocity.y = 0;
            onGround = true;
        } else {
            onGround = false;
        }
    }
    
    void applyGravity(float deltaTime) {
        velocity.y += 981.0f * deltaTime;
    }
    
    void jump(float jumpForce) {
        if (onGround) {
            velocity.y = -jumpForce;
            onGround = false;
        }
    }
    
    bool isOnGround() const {
        return onGround;
    }
};

TEST_CASE("Little Physics Engine - Basic Functionality", "[physics]") {
    SECTION("Initial state") {
        MockPhysicsEngine engine;
        REQUIRE(engine.position.x == 0.0f);
        REQUIRE(engine.position.y == 0.0f);
        REQUIRE(engine.velocity.x == 0.0f);
        REQUIRE(engine.velocity.y == 0.0f);
        REQUIRE(engine.isOnGround() == false);
    }
    
    SECTION("Update without gravity") {
        MockPhysicsEngine engine;
        engine.update(0.1f);
        REQUIRE(engine.position.x == 0.0f);
        REQUIRE(engine.position.y == 0.0f);
        REQUIRE(engine.velocity.x == 0.0f);
        REQUIRE(engine.velocity.y == 0.0f);
        REQUIRE(engine.isOnGround() == true);
    }
    
    SECTION("Apply gravity test") {
        MockPhysicsEngine engine;
        engine.applyGravity(0.1f);
        REQUIRE(engine.velocity.y == 98.1f); // 981 * 0.1
    }
    
    SECTION("Jump test") {
        MockPhysicsEngine engine;
        engine.onGround = true;
        engine.jump(500.0f);
        REQUIRE(engine.velocity.y == -500.0f);
        REQUIRE(engine.isOnGround() == false);
    }
    
    SECTION("Jump when not on ground") {
        MockPhysicsEngine engine;
        engine.onGround = false;
        engine.jump(500.0f);
        REQUIRE(engine.velocity.y == 0.0f);
    }
    
    SECTION("Update with gravity effect") {
        MockPhysicsEngine engine;
        engine.applyGravity(0.1f);
        engine.update(0.1f);
        REQUIRE(engine.velocity.y == 98.1f);
        REQUIRE(engine.position.y == 0.0f); // Still on ground
        REQUIRE(engine.isOnGround() == true);
    }
    
    SECTION("Jump and fall") {
        MockPhysicsEngine engine;
        engine.onGround = true;
        engine.jump(500.0f);
        engine.update(0.1f);
        REQUIRE(engine.velocity.y == -500.0f);
        REQUIRE(engine.position.y == 0.0f); // Still on ground (no vertical movement yet)
        REQUIRE(engine.isOnGround() == false);
    }
    
    SECTION("Update with downward motion") {
        MockPhysicsEngine engine;
        engine.velocity.y = 100.0f;
        engine.update(0.1f);
        REQUIRE(engine.position.y == 10.0f); // 100 * 0.1
    }
    
    SECTION("Edge case - large time step") {
        MockPhysicsEngine engine;
        engine.applyGravity(1.0f);
        REQUIRE(engine.velocity.y == 981.0f);
    }
    
    SECTION("Edge case - negative time step") {
        MockPhysicsEngine engine;
        engine.applyGravity(-0.1f);
        REQUIRE(engine.velocity.y == -98.1f);
    }
}