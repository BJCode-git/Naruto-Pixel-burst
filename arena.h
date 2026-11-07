#ifndef ARENA_H
#define ARENA_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Arena
{
public:
    Arena(sf::Window* parent_window, const std::string& background_path);
    ~Arena();
    
    void add_parallax_layer(const std::string& layer_path, float speed);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    
    sf::Sprite* get_background() const;
    int get_parallax_layer_count() const;
    
private:
    sf::Window* parent;
    sf::Texture* background_texture;
    sf::Sprite* background_sprite;
    std::vector<std::pair<sf::Texture*, float>> parallax_layers; // texture, scroll_speed
    std::vector<sf::Sprite*> parallax_sprites;
    
    // Parallax background movement
    float background_scroll_x;
    float background_scroll_y;
};

#endif // ARENA_H