#ifndef CHARACTER_SELECTION_H
#define CHARACTER_SELECTION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class CharacterSelection
{
public:
    CharacterSelection(sf::Window* parent_window);
    ~CharacterSelection();
    
    void add_character(const std::string& sprite_path, const std::string& name);
    void select_character(int index);
    void next_character();
    void previous_character();
    
    int get_character_count() const;
    const std::string& get_selected_character_name() const;
    sf::Sprite* get_selected_character() const;
    
private:
    sf::Window* parent;
    std::vector<std::pair<std::string, std::string>> characters; // sprite_path, name
    int selected_index;
    sf::Texture* selected_texture;
    sf::Sprite* selected_sprite;
};

#endif // CHARACTER_SELECTION_H