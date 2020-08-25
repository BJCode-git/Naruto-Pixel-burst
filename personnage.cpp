#include "personnage.h"

extern Settings settings;

Personnage::Personnage(  sf::Sprite *sprite_perso,
                         sf::Texture *perso,
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

    Personnage::pv=pv;
    Personnage::chakra=chakra;
    Personnage::strength=strength;
    Personnage::magic=magic;
    Personnage::defense=defense;
    Personnage::magical_defense=magical_defense;
    Personnage::speed=speed;
    Personnage::limit_break=limit_break;

    invulnerability=false;

    Dir=Dir_Stance;//Dir_Right;
    interrupt=false;
    FrameAnimation moveX{{
                              sf::IntRect( 405, 596, 45, 57),
                              sf::IntRect( 460, 596, 53, 59),
                              sf::IntRect( 520, 597, 56, 58),
                              sf::IntRect( 591, 597, 50, 58),
                              sf::IntRect( 647, 597, 55, 58),
                              sf::IntRect( 716, 597, 59, 58)
                            }};
    list_animations.insert(std::pair<Dir_perso,FrameAnimation>(Dir_Right,moveX));
    list_animations.insert(std::pair<Dir_perso,FrameAnimation>(Dir_Left,moveX));

    FrameAnimation jutsu{{
    sf::IntRect(26,2105, 44, 63),
    sf::IntRect(78, 2105, 74, 60),
    sf::IntRect(168, 2105, 78, 61),
    sf::IntRect(260, 2105, 72, 61),
    sf::IntRect(352, 2106, 59, 61),
    sf::IntRect(433, 2106, 56, 61),
    sf::IntRect( 510, 2106, 57, 61),

    sf::IntRect(584, 2105, 57, 61),
    sf::IntRect(657, 2106, 57, 61),
    sf::IntRect(739, 2106, 62, 61),
    sf::IntRect( 822, 2103, 56, 55),

    sf::IntRect(15, 2272, 53, 66),
    sf::IntRect(76, 2275, 37, 59),
    sf::IntRect(130, 2276, 37, 59),
    sf::IntRect( 184, 2275, 40, 60),
    sf::IntRect( 233, 2279, 75, 48),
    sf::IntRect( 317, 2282, 83, 48),
    sf::IntRect( 406, 2264, 132, 67),

    sf::IntRect( 547, 2264, 133, 71),
    sf::IntRect( 233, 2279, 75, 48),
    sf::IntRect( 701, 2249, 141, 87)
    },true,sf::seconds(3.0)};
    list_animations.insert(std::pair<Dir_perso,FrameAnimation>(Dir_Jutsu,jutsu));

    FrameAnimation Jump
    {{
     sf::IntRect( 12, 591, 35, 63),
     sf::IntRect( 53, 591, 35, 63),
     sf::IntRect( 112, 592, 50, 63),
     sf::IntRect( 176, 590, 50, 65),
     sf::IntRect( 244, 609, 34, 46),
     sf::IntRect( 298, 611, 31, 44)
   }};
    list_animations.insert(std::pair<Dir_perso,FrameAnimation>(Dir_Up,Jump));

    FrameAnimation Stance
    {{
     sf::IntRect( 9, 485, 32, 70),
     sf::IntRect( 48, 485, 32, 70),
     sf::IntRect( 84, 485, 32, 70),
     sf::IntRect( 126, 485, 32, 70),
   }};
    list_animations.insert(std::pair<Dir_perso,FrameAnimation>(Dir_Stance,Stance));

    FrameAnimation Teleport
    {{
     sf::IntRect( 354, 483, 34, 73),
     sf::IntRect( 403, 483, 32, 72),
     sf::IntRect( 317, 484, 32, 70)
    }};
    list_animations.insert(std::pair<Dir_perso,FrameAnimation>(Dir_Down,Teleport));
    std::cout<<"Perso construit";
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



sf::Time Personnage::operator++(void){
    sf::Time time=list_animations[Dir].time();
    sprite_perso->setTextureRect(list_animations[Dir].next());
    if(list_animations[Dir].is_end())
         Dir=Dir_Stance;

    return time;
}

void Personnage::attack(Personnage &target){
   target.set_pv(target.get_pv()-4*strength);
}

bool Personnage:: animeperso_on_Event(sf::Keyboard::Key code){
    Dir_perso old_dir=Dir;

    keyboard_command temp = settings.kb_action(code); //cmd[code];
    switch(temp){
        case moveLeft:
            Dir=Dir_Left;//Left;
            sprite_perso->move(-speed*5,0);
        break;
        case moveRight:
            Dir=Dir_Right;
            sprite_perso->move(speed*5,0);
        break;
        case Jump:
            Dir=Dir_Up;
            //sprite_perso->move(0,-speed*3);
        break;
        case Crounch:
            Dir=Dir_Down;
            sprite_perso->move(-speed*50,0);
        break;
        case Jutsu:
            Dir=Dir_Jutsu;
        break;
        default:
            Dir=Dir_Stance;
    }
    sf::Vector2f position(sprite_perso->getPosition());
    if(position.x<0)
        sprite_perso->setPosition(0,position.y);
    if(position.y<0)
        sprite_perso->setPosition(position.x,0);
    if(old_dir!=Dir)
        return true;
    return false;
}

bool Personnage:: animeperso_on_Event(bool button_pressed,unsigned int button,float joystick_position, sf::Joystick::Axis axe){
    Dir_perso old_dir=Dir;
    if (button_pressed){
         joystick_command temp = settings.joy_action(button_pressed);
         switch(temp){
             case joySquare:
                 Dir=Dir_Jutsu;//Left;
                 sprite_perso->move(-speed*3,0);
             break;
             case joyTriangle:
                 Dir=Dir_Jutsu;
                 sprite_perso->move(speed*3,0);
             break;
             case joyCircle:
                 Dir=Dir_Jutsu;
                 sprite_perso->move(0,speed*3);
             break;

             case joyJutsu:
                 Dir=Dir_Jutsu;
                 //sprite_perso->move(speed*3,0);
             break;
             case joyThrow:
                 Dir=Dir_Up;
                 sprite_perso->move(0,-speed*3);
             break;
             case joyTeleport:
                 Dir=Dir_Down;
                 sprite_perso->move(0,speed*3);
             break;
             default:
                 Dir=Dir_Stance;
         }
    }
    else{
        switch(axe){
            case sf::Joystick::Axis::X:
                if (joystick_position<-20.0){
                    Dir=Dir_Left;//Left;
                    sprite_perso->move(-speed*3,0);
                }
                else if(joystick_position>20.0){
                    Dir=Dir_Right;
                    sprite_perso->move(speed*3,0);
                }
            break;
            case sf::Joystick::PovX:
            if (joystick_position<-20.0){
                Dir=Dir_Left;//Left;
                sprite_perso->move(-speed*3,0);
            }
            else if(joystick_position>20.0){
                Dir=Dir_Right;
                sprite_perso->move(speed*3,0);
            }
            break;
            case sf::Joystick::Axis::Y:
                if (joystick_position>20.0){
                    Dir=Dir_Down;
                    sprite_perso->move(-speed*50,0);
                }
                else if(joystick_position<-20.0){
                    Dir=Dir_Up;
                    //sprite_perso->move(0,-speed*3);
                }
            break;
            case sf::Joystick::PovY:
                if (joystick_position>20.0){
                    Dir=Dir_Down;
                    //sprite_perso->move(0,speed*3);
                }
                else if(joystick_position<-20.0){
                    Dir=Dir_Up;
                    //sprite_perso->move(0,-speed*3);
                }
            break;
            default:
                Dir=Dir_Stance;
        }
    }
    if(old_dir!=Dir)
        return true;
    return false;
}


