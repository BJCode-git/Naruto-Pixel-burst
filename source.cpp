#include "source.h"

sf::RectangleShape PB_Rect(int x, int y, int width, int height){
    sf::RectangleShape object(sf::Vector2f(width,height));
    object.setPosition(x,y);
    object.setFillColor(sf::Color(255,0,0,255));
    return object;
}

void gestion_clavier(sf::Transformable &object,sf::Keyboard::Key code,int speed){

    switch(code){
        case sf::Keyboard::Left:
            object.move(-speed,0);
            break;
        case sf::Keyboard::Right:
            object.move(speed,0);
            break;
        case sf::Keyboard::Up:
            object.move(0,-speed);
            break;
        case sf::Keyboard::Down:
            object.move(0,speed);
            break;
    }
}
