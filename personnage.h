#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#include <map>
#include <iostream>
#include "settings.h"

// Left=71, Right, Up, Down,



struct Tuple
{
    // animation_geometry[Dir][xbegin,xend,y,distance_between_img]
    int tuple[4];
    int operator[](int i){
        return tuple[i];
    }
};


class Personnage //Classe qu'ont peut mettre Abstraite
{
public:
    Personnage( sf::Sprite *sprite_perso,sf::Texture *perso, int width,
               int height, unsigned int pv=10000,
               unsigned int chakra=1000,
               unsigned char strength=1,
               unsigned char magic=1,
               unsigned char defense=1,
               unsigned char magical_defense=1,
               unsigned char speed=1,
               unsigned char limit_break=100);
    ~Personnage();

    bool loadFromFile(std::string filename, sf::Color color_to_clear);

    unsigned int get_pv(void);
    unsigned int get_chakra(void);

    void set_pv(unsigned int pv);
    void set_chakra(unsigned int chakra);
    void set_animation_geometry(std::map<Dir_perso,Tuple> map);

    void operator++(void);
    virtual bool animeperso(sf::Keyboard::Key code); // méthode qu'ont peut mettre abstraite pure
    virtual bool animeperso(bool button_pressed,unsigned int button=0,float joystick_position=0, sf::Joystick::Axis axe=sf::Joystick::Axis::X );
    virtual void attack(Personnage &target);

protected:
    //sf::Vector2i anim;
    sf::Sprite *sprite_perso;
    sf::Texture *perso;
    int width;
    int height;
    int xpos;
    Dir_perso Dir;

    std::map<Dir_perso,Tuple> animation_geometry;
    // animation_geometry[Dir][xbegin,xend,y]
    unsigned int pv, chakra;
    unsigned char strength, magic, defense, magical_defense, speed, limit_break;

    bool invulnerability;
    //Settings settings;
};

#endif // PERSONNAGE_H
