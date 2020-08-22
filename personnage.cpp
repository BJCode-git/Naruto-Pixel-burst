#include "personnage.h"

Personnage::Personnage(){

}

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

    sf::Image img;
    img.loadFromFile("D:\\Sprites\\hokage_minato_namikaze.png");
    for (unsigned int a=0; a<img.getSize().x; a++)
    {
        for (unsigned int b=0; b<img.getSize().y; b++)
        {
                if (img.getPixel(a,b) == sf::Color(0,128,0)){
                    img.setPixel(a,b, sf::Color::Transparent);
                    //std::cout<<"pixel identifié";
                }
        }
    }
    perso->loadFromImage(img);
    Personnage::perso= perso;
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
    delete sprite_perso;
    delete perso;
}

bool Personnage::loadFromFile(std::string filename, sf::Color color_to_clear){

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
    std::cout<<"setTextureRect"<<std::endl;
}

bool Personnage::animeperso(sf::Keyboard::Key code){
    Dir_perso old_dir=Dir;
    switch(code){
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

void Personnage::attack(Personnage &target){
   target.set_pv(target.get_pv()-4*strength);
}
