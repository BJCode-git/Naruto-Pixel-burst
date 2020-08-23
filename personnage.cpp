#include "personnage.h"

extern Settings settings;

Personnage::Personnage(  sf::Sprite *sprite_perso,
                         sf::Texture *perso,
                         int width,
                         int height,
                         unsigned int pv,
                         unsigned int chakra,
                         unsigned char strength,
                         unsigned char magic,
                         unsigned char defense,
                         unsigned char magical_defense,
                         unsigned char speed,
                         unsigned char limit_break)
{
    Personnage::sprite_perso= sprite_perso;
    Personnage::perso= perso;
    perso->setSmooth(true);
    Personnage::width= width;
    Personnage::height= height;

    Personnage::pv=pv;
    Personnage::chakra=chakra;
    Personnage::strength=strength;
    Personnage::magic=magic;
    Personnage::defense=defense;
    Personnage::magical_defense=magical_defense;
    Personnage::speed=speed;
    Personnage::limit_break=limit_break;

    invulnerability=false;
    //Personnage::anim=sf::Vector2i(1,Dir_Right);
    xpos=animation_geometry[Dir_Right][0];
    Dir=Dir_Right;
}

Personnage::~Personnage(){
//    delete sprite_perso;
//    delete perso;
}

bool Personnage::loadFromFile(std::string filename, sf::Color color_to_clear){
    sf::Image img;
    if(!img.loadFromFile(filename))
        return false;
    for (unsigned int a=0; a<img.getSize().x; a++)
    {
        for (unsigned int b=0; b<img.getSize().y; b++)
        {
                if (img.getPixel(a,b) == color_to_clear){
                    img.setPixel(a,b, sf::Color::Transparent);
                    //std::cout<<"pixel identifié";
                }
        }
    }
    perso->loadFromImage(img);
    sprite_perso->setTexture(*perso);
}

unsigned int Personnage::get_pv(void){
    return pv;
}
unsigned int Personnage::get_chakra(void){
    return chakra;
}

void Personnage::set_pv(unsigned int pv){
    Personnage::pv=pv;
}
void Personnage::set_chakra(unsigned int chakra){
    Personnage::chakra=chakra;
}

void Personnage::set_animation_geometry(std::map<Dir_perso,Tuple> map){
    animation_geometry=map;
}


void Personnage::operator++(void){
    xpos+=width+animation_geometry[Dir][3];//width //3
    //animation_geometry[Dir][xbegin,xend,y]
    if(xpos >= animation_geometry[Dir][1])
        xpos=animation_geometry[Dir][0];
    sprite_perso->setTextureRect(sf::IntRect(xpos,animation_geometry[Dir][2],width,height));
    //std::cout<<"setTextureRect"<<std::endl;
}

void Personnage::attack(Personnage &target){
   target.set_pv(target.get_pv()-4*strength);
}

bool Personnage::animeperso(sf::Keyboard::Key code){
    Dir_perso old_dir=Dir;
    /*
    std::map<sf::Keyboard::Key ,keyboard_command> cmd={
        {sf::Keyboard::Left, moveLeft},
        {sf::Keyboard::Right, moveRight},
        {sf::Keyboard::Up, Jump},
        {sf::Keyboard::Down, Crounch}
    };*/

    keyboard_command temp = settings.kb_action(code); //cmd[code];
    switch(temp){
        case moveLeft:
            Dir=Dir_Left;//Left;
            sprite_perso->move(-speed*3,0);
        break;
        case moveRight:
            Dir=Dir_Right;
            sprite_perso->move(speed*3,0);
        break;
        case Jump:
            Dir=Dir_Up;
            sprite_perso->move(0,-speed*3);
        break;
        case Crounch:
            Dir=Dir_Down;
            sprite_perso->move(0,speed*3);
        break;
    }
    if(old_dir!=Dir)
        return true;
    return false;

}

bool Personnage::animeperso(bool button_pressed,unsigned int button,float joystick_position, sf::Joystick::Axis axe){
    Dir_perso old_dir=Dir;
    if (button_pressed){
         joystick_command temp = settings.joy_action(button_pressed);
         switch(temp){
             case joySquare:
                 Dir=Dir_Left;//Left;
                 sprite_perso->move(-speed*3,0);
             break;
             case joyTriangle:
                 Dir=Dir_Right;
                 sprite_perso->move(speed*3,0);
             break;
             case joyCircle:
                 Dir=Dir_Down;
                 sprite_perso->move(0,speed*3);
             break;

             case joyJutsu:
                 Dir=Dir_Right;
                 sprite_perso->move(speed*3,0);
             break;
             case joyThrow:
                 Dir=Dir_Up;
                 sprite_perso->move(0,-speed*3);
             break;
             case joyTeleport:
                 Dir=Dir_Down;
                 sprite_perso->move(0,speed*3);
             break;
         }
    }
    else{
        switch(axe){
            case sf::Joystick::Axis::X:
                if (joystick_position>20.0){
                    Dir=Dir_Left;//Left;
                    sprite_perso->move(-speed*3,0);
                }
                else if(joystick_position<-20.0){
                    Dir=Dir_Right;
                    sprite_perso->move(speed*3,0);
                }
            break;
            case sf::Joystick::Axis::Y:
                if (joystick_position>20.0){
                    Dir=Dir_Down;
                    sprite_perso->move(0,speed*3);
                }
                else if(joystick_position<-20.0){
                    Dir=Dir_Up;
                    sprite_perso->move(0,-speed*3);
                }
            break;
        }
    }
    if(old_dir!=Dir)
        return true;
    return false;
}


