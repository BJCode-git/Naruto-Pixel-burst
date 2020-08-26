#include "Little_Physics_Engine.h"

sf::Vector2f Jump_Parabole(sf::Vector2f position){


    float alpha=PI/3; //angle initial par rapport au sol de jump (fixé arbitrairement à pi/3)
    float vo=10; // vitesse initiale en m/s
    //foncteur x;
   // x^2;
    return sf::Vector2f(position.x,-position.x*(9.10)/2*pow((cos(alpha)*vo),2) + tan(alpha)*position.x);
}
