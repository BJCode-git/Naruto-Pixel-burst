#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#include <QDebug>
#include <map>
#include <iostream>
#include "settings.h"
#include "frameanimation.h"

// Left=71, Right, Up, Down,


/*
struct Tuple
{
    // animation_geometry[Dir][xbegin,xend,y,distance_between_img]
    int tuple[4];
    int operator[](int i){
        return tuple[i];
    }
};
*/
enum Orientation{
    Gauche=-1,
    Droite=1
};

void operator--(Orientation &o);

class Personnage //Classe qu'ont peut mettre Abstraite
{
public:
    Personnage( sf::Window *parent_window,
                std::string texture_file_name,
                sf::Color color_to_clear);
    /*
               unsigned int pv=10000,
               unsigned int chakra=1000,
               unsigned char strength=1,
               unsigned char magic=1,
               unsigned char defense=1,
               unsigned char magical_defense=1,
               unsigned char speed=1,
               unsigned char limit_break=100);*/
    ~Personnage();

    bool loadFromFile(std::string filename, sf::Color color_to_clear);

    unsigned int get_pv(void);
    unsigned int get_chakra(void);

    void set_pv(unsigned int pv);
    void set_chakra(unsigned int chakra);

    void set_orientation(Orientation o);
    void set_animations(std::map<Dir_perso,FrameAnimation> animations);
    void add_animation(Dir_perso anim, FrameAnimation frames);

    sf::Sprite* get_sprite();

    virtual sf::Time operator++(void);
    virtual bool animeperso_on_Event(sf::Keyboard::Key code); // méthode qu'ont peut mettre abstraite pure
    virtual bool animeperso_on_Event(bool button_pressed,unsigned int button=0,float joystick_position=0, sf::Joystick::Axis axe=sf::Joystick::Axis::X );
    virtual void attack(Personnage &target);

protected:
    //sf::Vector2i anim;
    sf::Window *parent;
    sf::Sprite *sprite_perso;
    sf::Texture *perso;
    Orientation oriente;
    Dir_perso Dir;
    std::map<Dir_perso,FrameAnimation> list_animations;

    unsigned int pv, chakra;
    unsigned char strength, magic, defense, magical_defense, speed, limit_break;

    bool invulnerability;
    bool interrupt;
};

#endif // PERSONNAGE_H
