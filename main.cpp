#define PREFIX "../SFML/"
#include "personnage.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <QDebug>

using namespace sf;

int main(int argc, char **argv)
{
    // Gestion fenetre
    for(int i=0;i<argc;i++){
        std::cout<<"arg "<<i<<" : "<<**argv<<" // ";
    }

    sf::RenderWindow  window;
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(25);
    window.create(sf::VideoMode(800, 600), "Naruto Pixel Burst", sf::Style::Default);

    sf::View view(sf::FloatRect(0.f, 0.f, 709.f, 401.f));
    window.setView(view);
    //view.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));

    sf::Image icon;
    if(icon.loadFromFile(PREFIX"naruto48px.png"))
        window.setIcon(48,48,icon.getPixelsPtr());

    // debug joystick

    if(sf::Joystick::isConnected(0)){
        sf::Joystick::Identification id=sf::Joystick::getIdentification(0);
        std::cout<<"Device name : "<<id.name.toAnsiString()<<std::endl;
        std::cout<<"Product Id : "<<id.productId<<std::endl;
        std::cout<<"Vendor Id : "<<id.vendorId<<std::endl;
    }


    // Gestion musique

    sf::Music music;
    if (!music.openFromFile(PREFIX"assets/musics/Wind-8bit.wav"))
        //D:\\Sprites\\Sound Effects\\Converted\\Yes-Roundabout.flac
        std::cout<<"Impossible de charger le fichier"<<std::endl;
    else{
        music.play();
        music.setLoop(true);
        music.setVolume(10);
    }

    // Gestion Background

    sf::Image background;
    sf::Texture texture_bg;
    sf::Sprite sprite_bg;
    if(!background.loadFromFile(PREFIX"assets/backgrounds/ValleyOfthEnd-0.png"))
        std::cout<<"Chargement impossible"<<std::endl;
    else
        texture_bg.loadFromImage(background);
    sprite_bg.setTexture(texture_bg);

    // Gestion personnage jouable

    Personnage Minato= Personnage(&window,PREFIX"assets/sprites/hokage_minato_namikaze.png", sf::Color(0,128,0));
    Minato.get_sprite()->setPosition(0,background.getSize().y-90);

    FrameAnimation moveX{{
                              sf::IntRect( 405, 596, 45, 57),
                              sf::IntRect( 460, 596, 53, 59),
                              sf::IntRect( 520, 597, 56, 58),
                              sf::IntRect( 591, 597, 50, 58),
                              sf::IntRect( 647, 597, 55, 58),
                              sf::IntRect( 716, 597, 59, 58)
                            }};
    Minato.set_animations({{Dir_X,moveX},
                           {Dir_Jutsu,{{
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
                               },true,sf::seconds(3.0)}
                            },
                           {Dir_Up,{{
                                        sf::IntRect( 12, 591, 35, 63),
                                        sf::IntRect( 53, 591, 35, 63),
                                        sf::IntRect( 112, 592, 50, 63),
                                        sf::IntRect( 176, 590, 50, 65),
                                        sf::IntRect( 244, 609, 34, 46),
                                        sf::IntRect( 298, 611, 31, 44)
                                      }}
                           },
                           {Dir_Stance,{{
                                            sf::IntRect( 9, 485, 32, 70),
                                            sf::IntRect( 46, 485, 32, 70),
                                            sf::IntRect( 84, 485, 32, 70),
                                            sf::IntRect( 126, 485, 32, 70),
                                          }}
                           },
                           {Dir_Down,{{
                                          sf::IntRect( 354, 483, 34, 73),
                                          sf::IntRect( 403, 483, 32, 72),
                                          sf::IntRect( 317, 484, 32, 70)
                                         }}
                           },
                           {

                           }
                          });
    // Perso test pour collision
        Personnage test(&window,PREFIX"assets/sprites/test2.png", sf::Color(255,255,255));
        test.set_orientation(Gauche);
        test.set_animations({
                                {Dir_X,{{
                                        sf::IntRect( 2, 99, 25, 43),
                                        sf::IntRect( 34, 99, 25, 43),
                                        sf::IntRect( 98, 99, 25, 43)
                                       }}
                                },
                                {Dir_Stance,{{sf::IntRect( 2, 99, 25, 43)}}

                                }
                            });
        test.get_sprite()->setPosition(background.getSize().x-90,background.getSize().y-90);
    // Gestion collision

    // Gestion FPS global

    bool updateFPS=true, dir_changed=true;
    sf::Clock temps,clock;
    float fpsCount=0,switchFPS=50,fpsSpeed=500;


    while(window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event))
        {

            switch (event.type) {

                case sf::Event::Closed :
                    window.close();
                break;

                case sf::Event::KeyPressed:
                    dir_changed=Minato.animeperso_on_Event(event.key.code);
                    test.animeperso_on_Event(event.key.code);
                break;

                case sf::Event::JoystickButtonPressed:
                    Minato.animeperso_on_Event(true,event.joystickButton.button);
                break;
                case sf::Event::JoystickMoved:
                    Minato.animeperso_on_Event(false,0,event.joystickMove.position,event.joystickMove.axis);
                break;

            }

        }

        if(updateFPS )
            fpsCount += fpsSpeed *temps.restart().asSeconds();
        else
            fpsCount=0;

        if(fpsCount>=switchFPS || dir_changed){
            dir_changed=false;
            fpsCount=0;
             ++test;
            clock.restart();
            do{
                sf::Clock clock2;
                do{

                }while(clock2.getElapsedTime()>sf::milliseconds(10));
                window.draw(sprite_bg);
                window.draw(*Minato.get_sprite());//21
                window.display();
                window.clear(sf::Color::Black);
            }
            while(++Minato>clock.getElapsedTime()+sf::milliseconds(5000));
        }
        window.draw(sprite_bg);
        window.draw(*test.get_sprite());
        window.draw(*Minato.get_sprite());
        window.display();
        window.clear(sf::Color::Black);
    }

    return EXIT_SUCCESS;
}
// RVB 0,128,0
