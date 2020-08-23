#ifndef SOURCE_H
#define SOURCE_H

#include <SFML/Graphics.hpp>

sf::RectangleShape PB_Rect(int x, int y, int width, int height);
void gestion_clavier(sf::Transformable &object,sf::Keyboard::Key code,int speed=5);

#endif // SOURCE_H
