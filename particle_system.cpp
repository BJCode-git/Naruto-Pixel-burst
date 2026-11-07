#include "particle_system.h"
#include <iostream>

ParticleSystem::ParticleSystem(sf::Window* parent_window) 
    : parent(parent_window), vertex_array_initialized(false)
{
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::add_particle(const sf::Vector2f& position, 
                                  const sf::Vector2f& velocity, 
                                  const sf::Color& color, 
                                  float lifetime)
{
    Particle particle;
    particle.position = position;
    particle.velocity = velocity;
    particle.color = color;
    particle.lifetime = lifetime;
    particle.max_lifetime = lifetime;
    particle.active = true;
    
    particles.push_back(particle);
}

void ParticleSystem::update(float deltaTime)
{
    for (auto& particle : particles) {
        if (particle.active) {
            particle.position += particle.velocity * deltaTime;
            particle.lifetime -= deltaTime;
            
            // Deactivate particle if lifetime is over
            if (particle.lifetime <= 0) {
                particle.active = false;
            }
        }
    }
    
    // Remove inactive particles
    particles.erase(
        std::remove_if(particles.begin(), particles.end(),
            [](const Particle& p) { return !p.active; }),
        particles.end()
    );
}

void ParticleSystem::draw(sf::RenderWindow& window)
{
    // Create vertex array if not initialized
    if (!vertex_array_initialized) {
        vertex_array.setPrimitiveType(sf::Points);
        vertex_array_initialized = true;
    }
    
    // Clear existing vertices
    vertex_array.clear();
    
    // Add active particles to vertex array
    for (const auto& particle : particles) {
        if (particle.active) {
            sf::Vertex vertex;
            vertex.position = particle.position;
            vertex.color = particle.color;
            vertex_array.append(vertex);
        }
    }
    
    // Draw particle system
    if (vertex_array.getVertexCount() > 0) {
        window.draw(vertex_array);
    }
}

int ParticleSystem::get_particle_count() const
{
    return particles.size();
}