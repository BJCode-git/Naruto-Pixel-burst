#include "3d_effects.h"
#include <iostream>

ThreeDEffects::ThreeDEffects(sf::Window* parent_window) 
    : parent(parent_window)
{
}

ThreeDEffects::~ThreeDEffects()
{
}

void ThreeDEffects::add_3d_effect(const sf::Vector2f& position, 
                                  float size, 
                                  const sf::Color& color, 
                                  float duration)
{
    ThreeDEffect effect;
    effect.position = position;
    effect.size = size;
    effect.color = color;
    effect.lifetime = duration;
    effect.max_lifetime = duration;
    effect.active = true;
    
    effects.push_back(effect);
}

void ThreeDEffects::update(float deltaTime)
{
    for (auto& effect : effects) {
        if (effect.active) {
            effect.lifetime -= deltaTime;
            
            // Deactivate effect if lifetime is over
            if (effect.lifetime <= 0) {
                effect.active = false;
            }
        }
    }
    
    // Remove inactive effects
    effects.erase(
        std::remove_if(effects.begin(), effects.end(),
            [](const ThreeDEffect& e) { return !e.active; }),
        effects.end()
    );
}

void ThreeDEffects::draw(sf::RenderWindow& window)
{
    // Simple 3D effect - glow effect using multiple circles
    for (const auto& effect : effects) {
        if (effect.active) {
            // Create a glow effect by drawing multiple circles
            for (int i = 0; i < 3; i++) {
                float radius = effect.size * (1.0f + i * 0.3f);
                sf::CircleShape circle(radius);
                circle.setFillColor(sf::Color(effect.color.r, effect.color.g, effect.color.b, effect.color.a / (i + 1)));
                circle.setOrigin(radius, radius);
                circle.setPosition(effect.position);
                window.draw(circle);
            }
        }
    }
}

int ThreeDEffects::get_effect_count() const
{
    return effects.size();
}