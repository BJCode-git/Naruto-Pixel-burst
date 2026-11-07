#ifndef _3D_EFFECTS_H
#define _3D_EFFECTS_H

#include <SFML/Graphics.hpp>
#include <vector>

struct ThreeDEffect
{
    sf::Vector2f position;
    float size;
    sf::Color color;
    float lifetime;
    float max_lifetime;
    bool active;
};

class ThreeDEffects
{
public:
    ThreeDEffects(sf::Window* parent_window);
    ~ThreeDEffects();
    
    void add_3d_effect(const sf::Vector2f& position, 
                       float size, 
                       const sf::Color& color, 
                       float duration);
    
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    
    int get_effect_count() const;
    
private:
    sf::Window* parent;
    std::vector<ThreeDEffect> effects;
};

#endif // _3D_EFFECTS_H