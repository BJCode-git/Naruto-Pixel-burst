//#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

//#include "source.h"
#include "personnage.h"


sf::RenderWindow  window;
sf::Sprite sprite_perso;
sf::Texture perso;
Personnage Minato= Personnage(&sprite_perso,&perso,55,70);//35,48);

//enum Dir{Up=650-2*48,Down=650,Right=650+48,Left=650-48};
enum Dir{Down,Left,Right,Up};
sf::Vector2i anim(1,Down);
int speed=3;
bool updateFPS=true, dir_changed=true;
sf::Clock temps;
float fpsCount=0,switchFPS=50,fpsSpeed=500;


void animeperso(sf::Sprite &object,sf::Keyboard::Key code,int speed=5){
    int old_dir=anim.y;
    switch(code){
        case sf::Keyboard::Left:
            anim.y=Left;//Left;
            object.move(-speed,0);
            break;
        case sf::Keyboard::Right:
            anim.y=Right;
            object.move(speed,0);
            break;
        case sf::Keyboard::Up:
            anim.y=Up;
            object.move(0,-speed);
            break;
        case sf::Keyboard::Down:
            anim.y=Down;
            object.move(0,speed);
            break;
    }
    if(old_dir!=anim.y)
        dir_changed=true;
}

int main(int argv, char **argc)
{
    window.create(sf::VideoMode(800, 600), "SFML", sf::Style::Default);
    //enum Dir_perso{Dir_Up,Dir_Down,Dir_Left,Dir_Right};

    std::map<Dir_perso,Tuple> map;

    map = { {Dir_Up,{10,335,590,18}},
            {Dir_Down,{440,310,485}},
            {Dir_Left,{405,790,590,5}},
            {Dir_Right,{405,790,590,5}}
          };

    /*
    map = { {Dir_Up,{10,560,525,29}},
            {Dir_Down,{15,565,655,29}},
            {Dir_Left,{18,790,590,29}},
            {Dir_Right,{15,790,718,29}}
          };
    */
    Minato.set_animation_geometry(map);
    /*
    if(!perso.loadFromFile("D:\\Sprites\\test2.png"))
        //D:\\Sprites\\hokage_minato_namikaze.png
        //sf::IntRect(405,596,46,64)

        std::cout<<"Erreur chargement image."<<std::endl;
    perso.setSmooth(true);
    sprite_perso.setTexture(perso);
    */
    /*
    if(!perso.loadFromFile("D:\\Sprites\\hokage_minato_namikaze.png"))
        //hokage_minato_namikaze
        std::cout<<"Erreur chargement image."<<std::endl;
    */
    perso.setSmooth(true);
    sprite_perso.setTexture(perso);

    sf::Image background;
    sf::Texture texture_bg;
    sf::Sprite sprite_bg;
    if(!background.loadFromFile("D:\\Sprites\\ValleyOfthEnd\\ValleyOfthEnd-0.png"))
        std::cout<<"Chargement impossible"<<std::endl;
    else
        texture_bg.loadFromImage(background);
    sprite_bg.setTexture(texture_bg);
    /*
    sf::Font font;
    if (!font.loadFromFile("D:\\my_Programs\\Qt5\\SFML\\Roboto-Regular.ttf"))
        std::cerr<<"Font pas chargé"<<std::endl;

    sf::Text text("",font,24);
    text.setFillColor(sf::Color::Green);
    text.setStyle(sf::Text::Bold);
    */
    sf::Music music;
    if (!music.openFromFile("D:\\Sprites\\Sound Effects\\Converted\\Yes-Roundabout.flac"))
        //return EXIT_FAILURE;
        std::cout<<"Impossible de charger le fichier"<<std::endl;
    else{
        //music.play();
        music.setLoop(true);
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

                    //animeperso(sprite_perso,event.key.code);
                    dir_changed=Minato.animeperso(event.key.code);
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
                    /*
                    anim.x++;
                    if(anim.x * 32 >= perso.getSize().x)
                        anim.x=0;
                    sprite_perso.setTextureRect(sf::IntRect(anim.x*32,anim.y*48,32,48));
                    */
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
