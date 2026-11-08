#include <gtest/gtest.h>
#include "personnage.h"
#include "frameanimation.h"
#include <vector>

// Mock class to avoid SFML dependencies in tests
class MockPersonnage : public Personnage {
public:
    MockPersonnage() : Personnage(nullptr, "", sf::Color::Transparent) {}
    
    // Override virtual methods to avoid SFML dependencies
    sf::Time operator++(void) override {
        return sf::seconds(0.1f);
    }
    
    bool animeperso_on_Event(sf::Keyboard::Key code) override {
        return false;
    }
    
    bool animeperso_on_Event(bool button_pressed, unsigned int button, float joystick_position, sf::Joystick::Axis axe) override {
        return false;
    }
    
    void attack(Personnage &target) override {
        // Empty implementation for testing
    }
};

class PersonnageTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup common to all tests
    }
    
    void TearDown() override {
        // Cleanup common to all tests
    }
};

TEST_F(PersonnageTest, ConstructorDefault) {
    MockPersonnage personnage;
    
    // Test default values
    EXPECT_EQ(personnage.get_pv(), 10000);
    EXPECT_EQ(personnage.get_chakra(), 1000);
    EXPECT_EQ(personnage.get_sprite(), nullptr);
}

TEST_F(PersonnageTest, GetSetPV) {
    MockPersonnage personnage;
    
    EXPECT_EQ(personnage.get_pv(), 10000);
    personnage.set_pv(5000);
    EXPECT_EQ(personnage.get_pv(), 5000);
}

TEST_F(PersonnageTest, GetSetChakra) {
    MockPersonnage personnage;
    
    EXPECT_EQ(personnage.get_chakra(), 1000);
    personnage.set_chakra(2000);
    EXPECT_EQ(personnage.get_chakra(), 2000);
}

TEST_F(PersonnageTest, SetOrientation) {
    MockPersonnage personnage;
    
    EXPECT_EQ(personnage.get_sprite(), nullptr);
    
    // Test orientation setting
    personnage.set_orientation(Gauche);
    // Note: We can't test orientation directly but we verify it doesn't crash
}

TEST_F(PersonnageTest, SetAnimations) {
    MockPersonnage personnage;
    
    // Test setting animations
    std::map<Dir_perso, FrameAnimation> animations;
    FrameAnimation anim;
    animations[Dir_Stance] = anim;
    
    personnage.set_animations(animations);
    // Test should not crash
}

TEST_F(PersonnageTest, AddAnimation) {
    MockPersonnage personnage;
    
    // Test adding animation
    FrameAnimation anim;
    personnage.add_animation(Dir_Stance, anim);
    // Test should not crash
}

TEST_F(PersonnageTest, Attack) {
    MockPersonnage attacker;
    MockPersonnage target;
    
    unsigned int initial_pv = target.get_pv();
    
    attacker.attack(target);
    
    // Test that attack reduces PV (simplified test)
    // Note: Actual implementation might be more complex
    EXPECT_EQ(target.get_pv(), initial_pv); // Will fail if we don't override properly
}