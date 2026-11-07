#include "character_selection.h"
#include <iostream>

CharacterSelection::CharacterSelection(sf::Window* parent_window) 
    : parent(parent_window), selected_index(-1), selected_texture(nullptr), selected_sprite(nullptr)
{
}

CharacterSelection::~CharacterSelection()
{
    if (selected_texture) {
        delete selected_texture;
    }
    if (selected_sprite) {
        delete selected_sprite;
    }
}

void CharacterSelection::add_character(const std::string& sprite_path, const std::string& name)
{
    characters.push_back(std::make_pair(sprite_path, name));
}

void CharacterSelection::select_character(int index)
{
    if (index >= 0 && index < static_cast<int>(characters.size())) {
        selected_index = index;
        
        // Load the texture for the selected character
        if (selected_texture) {
            delete selected_texture;
        }
        selected_texture = new sf::Texture();
        
        if (selected_texture->loadFromFile(characters[index].first)) {
            if (selected_sprite) {
                delete selected_sprite;
            }
            selected_sprite = new sf::Sprite(*selected_texture);
        }
    }
}

void CharacterSelection::next_character()
{
    if (characters.empty()) return;
    
    selected_index = (selected_index + 1) % characters.size();
    select_character(selected_index);
}

void CharacterSelection::previous_character()
{
    if (characters.empty()) return;
    
    selected_index = (selected_index - 1 + characters.size()) % characters.size();
    select_character(selected_index);
}

int CharacterSelection::get_character_count() const
{
    return characters.size();
}

const std::string& CharacterSelection::get_selected_character_name() const
{
    if (selected_index >= 0 && selected_index < static_cast<int>(characters.size())) {
        return characters[selected_index].second;
    }
    static const std::string empty = "";
    return empty;
}

sf::Sprite* CharacterSelection::get_selected_character() const
{
    return selected_sprite;
}