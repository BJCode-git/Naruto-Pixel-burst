#define PREFIX "../SFML/"
#include "personnage.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <QDebug>

using namespace sf;

int main(int argv, char **argc)
{
    // Gestion fenetre

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

    sf::Sprite sprite_perso;
    sf::Texture perso;
    Personnage Minato= Personnage(&sprite_perso,&perso);
    Minato.loadFromFile(PREFIX"assets/sprites/hokage_minato_namikaze.png", sf::Color(0,128,0));
    sprite_perso.setPosition(0,background.getSize().y-90);

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
            clock.restart();
            do{

                sf::Clock clock2;
                do{

                }while(clock2.getElapsedTime()>sf::milliseconds(10));
                window.draw(sprite_bg);
                window.draw(sprite_perso);//21
                window.display();
                window.clear(sf::Color::Black);
            }
            while(++Minato>clock.getElapsedTime()+sf::milliseconds(5000));
        }
        window.draw(sprite_bg);
        window.draw(sprite_perso);
        window.display();
        window.clear(sf::Color::Black);
    }

    return EXIT_SUCCESS;
}
// RVB 0,128,0
