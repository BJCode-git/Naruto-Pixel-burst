#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#include <SFML/Graphics.hpp>
#include <iostream>

// Left=71, Right, Up, Down,

const sf::Keyboard::Key cmd[4]={sf::Keyboard::Left,
                           sf::Keyboard::Right,
                           sf::Keyboard::Up,
                           sf::Keyboard::Down
                          };

enum command{
    moveLeft=sf::Keyboard::Left,//=71
    moveRight=sf::Keyboard::Right,
    Jump=sf::Keyboard::Up,
    Crounch=sf::Keyboard::Down,
};

//enum Dir_perso{Dir_Up=585,Dir_Down=480,Dir_Left=585,Dir_Right=585};
enum Dir_perso{Dir_Up=0,Dir_Down,Dir_Left,Dir_Right};

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
    Personnage();
    ~Personnage();

    bool loadFromFile(std::string filename, sf::Color color_to_clear);

    unsigned int get_pv(void);
    unsigned int get_chakra(void);

    void set_pv(unsigned int pv);
    void set_chakra(unsigned int chakra);
    void set_animation_geometry(std::map<Dir_perso,Tuple> map);

    void operator++(void);
    virtual bool animeperso(sf::Keyboard::Key code); // méthode qu'ont peut mettre abstraite pure
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
};

#endif // PERSONNAGE_H
