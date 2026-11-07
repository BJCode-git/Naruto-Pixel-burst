#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

struct Particle
{
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Color color;
    float lifetime;
    float max_lifetime;
    bool active;
};

class ParticleSystem
{
public:
    ParticleSystem(sf::Window* parent_window);
    ~ParticleSystem();
    
    void add_particle(const sf::Vector2f& position, 
                      const sf::Vector2f& velocity, 
                      const sf::Color& color, 
                      float lifetime);
    
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    
    int get_particle_count() const;
    
private:
    sf::Window* parent;
    std::vector<Particle> particles;
    sf::VertexArray vertex_array;
    bool vertex_array_initialized;
};

#endif // PARTICLE_SYSTEM_H