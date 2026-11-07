#include "arena.h"
#include <iostream>

Arena::Arena(sf::Window* parent_window, const std::string& background_path) 
    : parent(parent_window), background_scroll_x(0.0f), background_scroll_y(0.0f)
{
    // Load main background
    background_texture = new sf::Texture();
    if (background_texture->loadFromFile(background_path)) {
        background_sprite = new sf::Sprite(*background_texture);
    } else {
        background_sprite = nullptr;
    }
}

Arena::~Arena()
{
    if (background_texture) {
        delete background_texture;
    }
    if (background_sprite) {
        delete background_sprite;
    }
    
    // Clean up parallax layers
    for (auto& layer : parallax_layers) {
        delete layer.first;
    }
    for (auto& sprite : parallax_sprites) {
        delete sprite;
    }
}

void Arena::add_parallax_layer(const std::string& layer_path, float speed)
{
    sf::Texture* texture = new sf::Texture();
    if (texture->loadFromFile(layer_path)) {
        parallax_layers.push_back(std::make_pair(texture, speed));
        parallax_sprites.push_back(new sf::Sprite(*texture));
    }
}

void Arena::update(float deltaTime)
{
    // Update background scroll (basic parallax effect)
    background_scroll_x += deltaTime * 0.1f; // Adjust scroll speed as needed
    
    // Update parallax layers
    for (size_t i = 0; i < parallax_layers.size(); ++i) {
        if (i < parallax_sprites.size()) {
            float scroll_x = background_scroll_x * parallax_layers[i].second;
            parallax_sprites[i]->setPosition(-scroll_x, 0);
        }
    }
}

void Arena::draw(sf::RenderWindow& window)
{
    // Draw background
    if (background_sprite) {
        window.draw(*background_sprite);
    }
    
    // Draw parallax layers
    for (auto& sprite : parallax_sprites) {
        if (sprite) {
            window.draw(*sprite);
        }
    }
}

sf::Sprite* Arena::get_background() const
{
    return background_sprite;
}

int Arena::get_parallax_layer_count() const
{
    return parallax_layers.size();
}