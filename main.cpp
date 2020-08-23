#define PREFIX "../SFML/"
#include "personnage.h"
#include <SFML/Audio.hpp>
#include <iostream>


int main(int argv, char **argc)
{
    sf::RenderWindow  window;
    sf::Sprite sprite_perso;
    sf::Texture perso;
    Personnage Minato= Personnage(&sprite_perso,&perso,55,70);

    int speed=3;
    bool updateFPS=true, dir_changed=true;
    sf::Clock temps;
    float fpsCount=0,switchFPS=50,fpsSpeed=500;

    window.create(sf::VideoMode(800, 600), "Naruto Pixel Burst", sf::Style::Default);

    if(sf::Joystick::isConnected(0)){
        sf::Joystick::Identification id=sf::Joystick::getIdentification(0);
        std::cout<<"Device name : "<<id.name.toAnsiString()<<std::endl;
        std::cout<<"Product Id : "<<id.productId<<std::endl;
        std::cout<<"Vendor Id : "<<id.vendorId<<std::endl;
    }


    sf::Image icon;
    if(icon.loadFromFile(PREFIX"naruto48px.png"))
        window.setIcon(48,48,icon.getPixelsPtr());

    std::map<Dir_perso,Tuple> map;

    map = { {Dir_Up,{10,335,590,18}},
            {Dir_Down,{440,310,485}},
            {Dir_Left,{405,790,590,5}},
            {Dir_Right,{405,790,590,5}}
          };

    Minato.set_animation_geometry(map);
    Minato.loadFromFile(PREFIX"assets/sprites/hokage_minato_namikaze.png", sf::Color(0,128,0));

    sf::Image background;
    sf::Texture texture_bg;
    sf::Sprite sprite_bg;
    if(!background.loadFromFile(PREFIX"assets/backgrounds/ValleyOfthEnd-0.png"))
        std::cout<<"Chargement impossible"<<std::endl;
    else
        texture_bg.loadFromImage(background);
    sprite_bg.setTexture(texture_bg);

    sf::Music music;
    if (!music.openFromFile(PREFIX"assets/musics/The_Offspring_All_I_Want_8_bit.flac"))
        //D:\\Sprites\\Sound Effects\\Converted\\Yes-Roundabout.flac
        std::cout<<"Impossible de charger le fichier"<<std::endl;
    else{
        music.play();
        music.setLoop(true);
        music.setVolume(10);
    }

    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(25);
    while(window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event))
        {

            // évènement "fermeture demandée" : on ferme la fenêtre
            switch (event.type) {

                case sf::Event::Closed :
                    window.close();
                break;

                case sf::Event::KeyPressed:
                    dir_changed=Minato.animeperso(event.key.code);
                break;

                case sf::Event::JoystickButtonPressed:
                    Minato.animeperso(true,event.joystickButton.button);
                break;
                case sf::Event::JoystickMoved:
                    Minato.animeperso(false,0,event.joystickMove.position,event.joystickMove.axis);
                break;
                /*
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button==sf::Mouse::Left){
                        rect->setPosition(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y);
                    }
                break;
                */
            }

                if(updateFPS )
                    fpsCount += fpsSpeed *temps.restart().asSeconds();
                else
                    fpsCount=0;
                if(fpsCount>=switchFPS || dir_changed){
                    dir_changed=false;
                    fpsCount=0;
                    ++Minato;
                }
                window.draw(sprite_bg);
                window.draw(sprite_perso);
                window.display();
                window.clear(sf::Color::Black);
        }
    }

    return EXIT_SUCCESS;
}
// RVB 0,128,0
