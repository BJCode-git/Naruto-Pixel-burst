#ifndef LITTLE_PHYSICS_ENGINE_H
#define LITTLE_PHYSICS_ENGINE_H
#define PI 3.14159265

#include <cmath>
#include <SFML/Graphics.hpp>

sf::Vector2f Jump_Parabole(sf::Vector2f position);

class foncteur{
public:
    foncteur();
    ~foncteur();
    float operator^(int n);
};

namespace M{
    template <typename T>
    T operator^(T x,int n){
        switch(n){
            case 0:
                return T();
            break;
            case 1 :
                return x;
            break;
            default:
                return x^(n-1);
        }
    }
}

#endif // LITTLE_PHYSICS_ENGINE_H
