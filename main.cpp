#define PREFIX "../SFML/"
#include "personnage.h"
#include "character_selection.h"
#include "arena.h"
#include "particle_system.h"
#include "3d_effects.h"
#include "settings.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <QDebug>
#include <vector>

using namespace sf;

enum GameState {
    MENU,
    CHARACTER_SELECT,
    ARENA_SELECT,
    PLAYING,
    GAME_OVER
};

int main(int argc, char **argv)
{
    // Create global settings instance
    Settings settings;
    
    // Gestion fenetre
    for(int i=0;i<argc;i++){
        std::cout<<"arg "<<i<<" : "<<**argv<<" // ";
    }

    sf::RenderWindow window;
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    window.create(sf::VideoMode(800, 600), "Naruto Pixel Burst", sf::Style::Default);

    sf::View view(sf::FloatRect(0.f, 0.f, 800.f, 600.f));
    window.setView(view);

    sf::Image icon;
    if(icon.loadFromFile(PREFIX"naruto48px.png"))
        window.setIcon(48,48,icon.getPixelsPtr());

    // Debug joystick
    if(sf::Joystick::isConnected(0)){
        sf::Joystick::Identification id=sf::Joystick::getIdentification(0);
        std::cout<<"Device name : "<<id.name.toAnsiString()<<std::endl;
        std::cout<<"Product Id : "<<id.productId<<std::endl;
        std::cout<<"Vendor Id : "<<id.vendorId<<std::endl;
    }

    // Gestion musique
    sf::Music music;
    if (!music.openFromFile(PREFIX"assets/musics/Wind-8bit.wav"))
        std::cout<<"Impossible de charger le fichier"<<std::endl;
    else{
        music.play();
        music.setLoop(true);
        music.setVolume(10);
    }

    // Game state management
    GameState current_state = CHARACTER_SELECT;
    
    // Character selection system
    CharacterSelection char_select(&window);
    char_select.add_character(PREFIX"assets/sprites/hokage_minato_namikaze.png", "Minato");
    char_select.add_character(PREFIX"assets/sprites/test2.png", "Test Character");
    char_select.select_character(0);
    
    // Arena system
    Arena arena(&window, PREFIX"assets/backgrounds/ValleyOfthEnd-0.png");
    arena.add_parallax_layer(PREFIX"assets/backgrounds/ValleyOfthEnd-1.png", 0.5f);
    arena.add_parallax_layer(PREFIX"assets/backgrounds/ValleyOfthEnd-2.png", 0.3f);
    
    // Particle system
    ParticleSystem particle_system(&window);
    
    // 3D effects system
    ThreeDEffects three_d_effects(&window);
    
    // Create player character
    Personnage player(&window, PREFIX"assets/sprites/hokage_minato_namikaze.png", sf::Color(0,128,0));
    player.get_sprite()->setPosition(200, 400);
    
    // Create enemy character
    Personnage enemy(&window, PREFIX"assets/sprites/test2.png", sf::Color(255,0,0));
    enemy.set_orientation(Gauche);
    enemy.get_sprite()->setPosition(600, 400);
    
    // Animation setup for player
    FrameAnimation moveX{{
                              sf::IntRect( 405, 596, 45, 57),
                              sf::IntRect( 460, 596, 53, 59),
                              sf::IntRect( 520, 597, 56, 58),
                              sf::IntRect( 591, 597, 50, 58),
                              sf::IntRect( 647, 597, 55, 58),
                              sf::IntRect( 716, 597, 59, 58)
                            }};
    
    FrameAnimation jutsuAnimation{{
                               sf::IntRect(26,2105, 44, 63),
                               sf::IntRect(78, 2105, 74, 60),
                               sf::IntRect(168, 2105, 78, 61),
                               sf::IntRect(260, 2105, 72, 61),
                               sf::IntRect(352, 2106, 59, 61),
                               sf::IntRect(433, 2106, 56, 61),
                               sf::IntRect( 510, 2106, 57, 61),

                               sf::IntRect(584, 2105, 57, 61),
                               sf::IntRect(657, 2106, 57, 61),
                               sf::IntRect(739, 2106, 62, 61),
                               sf::IntRect( 822, 2103, 56, 55),

                               sf::IntRect(15, 2272, 53, 66),
                               sf::IntRect(76, 2275, 37, 59),
                               sf::IntRect(130, 2276, 37, 59),
                               sf::IntRect( 184, 2275, 40, 60),
                               sf::IntRect( 233, 2279, 75, 48),
                               sf::IntRect( 317, 2282, 83, 48),
                               sf::IntRect( 406, 2264, 132, 67),

                               sf::IntRect( 547, 2264, 133, 71),
                               sf::IntRect( 233, 2279, 75, 48),
                               sf::IntRect( 701, 2249, 141, 87)
                               },true,sf::seconds(3.0)};
    
    FrameAnimation upAnimation{{
                               sf::IntRect( 12, 591, 35, 63),
                               sf::IntRect( 53, 591, 35, 63),
                               sf::IntRect( 112, 592, 50, 63),
                               sf::IntRect( 176, 590, 50, 65),
                               sf::IntRect( 244, 609, 34, 46),
                               sf::IntRect( 298, 611, 31, 44)
                             }};
    
    FrameAnimation stanceAnimation{{
                                   sf::IntRect( 9, 485, 32, 70),
                                   sf::IntRect( 46, 485, 32, 70),
                                   sf::IntRect( 84, 485, 32, 70),
                                   sf::IntRect( 126, 485, 32, 70),
                                 }};
    
    FrameAnimation downAnimation{{
                                  sf::IntRect( 354, 483, 34, 73),
                                  sf::IntRect( 403, 483, 32, 72),
                                  sf::IntRect( 317, 484, 32, 70)
                                }};
    
    player.set_animations({{Dir_X, moveX},
                           {Dir_Jutsu, jutsuAnimation},
                           {Dir_Up, upAnimation},
                           {Dir_Stance, stanceAnimation},
                           {Dir_Down, downAnimation}
                          });
    
    // Animation setup for enemy
    FrameAnimation enemyMoveX{{
                                  sf::IntRect( 2, 99, 25, 43),
                                  sf::IntRect( 34, 99, 25, 43),
                                  sf::IntRect( 98, 99, 25, 43)
                                }};
    
    FrameAnimation enemyStance{{
                                  sf::IntRect( 2, 99, 25, 43)
                                }};
    
    enemy.set_animations({{Dir_X, enemyMoveX},
                          {Dir_Stance, enemyStance}
                         });
    
    // Game loop
    sf::Clock game_clock;
    
    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed :
                    window.close();
                    break;
                    
                case sf::Event::KeyPressed:
                    if (current_state == CHARACTER_SELECT) {
                        if (event.key.code == sf::Keyboard::Right) {
                            char_select.next_character();
                        } else if (event.key.code == sf::Keyboard::Left) {
                            char_select.previous_character();
                        } else if (event.key.code == sf::Keyboard::Return) {
                            current_state = ARENA_SELECT;
                        }
                    } else if (current_state == ARENA_SELECT) {
                        if (event.key.code == sf::Keyboard::Return) {
                            current_state = PLAYING;
                        }
                    } else if (current_state == PLAYING) {
                        player.animeperso_on_Event(event.key.code);
                    }
                    break;
                    
                case sf::Event::JoystickButtonPressed:
                    if (current_state == PLAYING) {
                        player.animeperso_on_Event(true, event.joystickButton.button);
                    }
                    break;
                    
                case sf::Event::JoystickMoved:
                    if (current_state == PLAYING) {
                        player.animeperso_on_Event(false, 0, event.joystickMove.position, event.joystickMove.axis);
                    }
                    break;
            }
        }
        
        // Update game logic based on current state
        float delta_time = game_clock.restart().asSeconds();
        
        if (current_state == PLAYING) {
            // Update characters
            player++;// Update animation
            enemy++;// Update animation
            
            // Simple AI for enemy
            if (enemy.get_sprite()->getPosition().x > player.get_sprite()->getPosition().x) {
                enemy.get_sprite()->move(-100 * delta_time, 0);
            } else {
                enemy.get_sprite()->move(100 * delta_time, 0);
            }
            
            // Simple combat - attack when close
            sf::Vector2f player_pos = player.get_sprite()->getPosition();
            sf::Vector2f enemy_pos = enemy.get_sprite()->getPosition();
            float distance = sqrt(pow(player_pos.x - enemy_pos.x, 2) + pow(player_pos.y - enemy_pos.y, 2));
            
            if (distance < 100 && rand() % 100 < 2) { // 2% chance to attack when close
                // Create attack effect
                particle_system.add_particle(
                    enemy_pos,
                    sf::Vector2f(rand() % 100 - 50, rand() % 100 - 50),
                    sf::Color::Yellow,
                    1.0f
                );
                
                // Create 3D effect
                three_d_effects.add_3d_effect(
                    enemy_pos,
                    20.0f,
                    sf::Color::Yellow,
                    0.5f
                );
                
                // Simple damage to player
                player.set_pv(player.get_pv() - 10);
                
                if (player.get_pv() <= 0) {
                    current_state = GAME_OVER;
                }
            }
            
            // Update particle system and 3D effects
            particle_system.update(delta_time);
            three_d_effects.update(delta_time);
            
            // Update arena
            arena.update(delta_time);
        }
        
        // Draw everything
        window.clear(sf::Color::Black);
        
        if (current_state == CHARACTER_SELECT) {
            // Draw character selection menu
            window.draw(*char_select.get_selected_character());
            // Add UI elements for selection
            sf::Text text;
            text.setString("Select Character: " + char_select.get_selected_character_name());
            text.setFont(sf::Font());
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::White);
            text.setPosition(10, 10);
            window.draw(text);
        } else if (current_state == ARENA_SELECT) {
            // Draw arena selection menu
            arena.draw(window);
            sf::Text text;
            text.setString("Select Arena");
            text.setFont(sf::Font());
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::White);
            text.setPosition(10, 10);
            window.draw(text);
        } else if (current_state == PLAYING) {
            // Draw game world
            arena.draw(window);
            window.draw(*player.get_sprite());
            window.draw(*enemy.get_sprite());
            
            // Draw effects
            particle_system.draw(window);
            three_d_effects.draw(window);
            
            // Draw UI
            sf::Text pv_text;
            pv_text.setString("Player HP: " + std::to_string(player.get_pv()));
            pv_text.setFont(sf::Font());
            pv_text.setCharacterSize(24);
            pv_text.setFillColor(sf::Color::White);
            pv_text.setPosition(10, 10);
            window.draw(pv_text);
        } else if (current_state == GAME_OVER) {
            // Draw game over screen
            sf::Text text;
            text.setString("GAME OVER");
            text.setFont(sf::Font());
            text.setCharacterSize(48);
            text.setFillColor(sf::Color::Red);
            text.setPosition(300, 250);
            window.draw(text);
        }
        
        window.display();
    }
    
    return EXIT_SUCCESS;
}
// RVB 0,128,0
