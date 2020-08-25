#include "settings.h"

Settings::Settings():
    parametres("BJ-Productions", "Naruto Pixel Burst")
{

    volume=parametres.value("volume",100).toInt();

    parametres.beginGroup("Keyboard");
    if(!parametres.value("customized",false).toBool()){
        key_cmd={
            {sf::Keyboard::Left, moveLeft},
            {sf::Keyboard::Right, moveRight},
            {sf::Keyboard::Up, Jump},
            {sf::Keyboard::A, Dash},
            {sf::Keyboard::Down, Crounch},

            {sf::Keyboard::Q, Square},
            {sf::Keyboard::Z, Triangle},
            {sf::Keyboard::D, Circle},

            {sf::Keyboard::Space, Jutsu},
            {sf::Keyboard::F, Throw},
            {sf::Keyboard::R, Teleport},
        };
        parametres.setValue("customized",false);
    }
    else{

        key_cmd={
            {parametres.value("moveLeft",sf::Keyboard::Left).toInt(), moveLeft},
            {parametres.value("moveRight",sf::Keyboard::Right).toInt(), moveRight},
            {parametres.value("Jump",sf::Keyboard::Up).toInt(), Jump},
            {parametres.value("Dash",sf::Keyboard::A).toInt(), Dash},
            {parametres.value("Crounch",sf::Keyboard::Down).toInt(), Crounch},

            {parametres.value("Square",sf::Keyboard::Q).toInt(), Square},
            {parametres.value("Triangle",sf::Keyboard::Z).toInt(), Triangle},
            {parametres.value("Circle",sf::Keyboard::D).toInt(), Circle},

            {parametres.value("Jutsu",sf::Keyboard::Space).toInt(), Jutsu},
            {parametres.value("Throw",sf::Keyboard::F).toInt(), Throw},
            {parametres.value("Teleport",sf::Keyboard::R).toInt(), Teleport},
        };
    }

    parametres.endGroup();

    parametres.beginGroup("Joystick");
    if(!parametres.value("customized",false).toBool()){
        joy_cmd={

//            {sf::Joystick::X,joyHorizontal},
//            {sf::Joystick::Y,joyVertical},
            {6,joyDash},

            {0,joySquare},
            {1,joyTriangle},
            {2,joyCircle},

            {3,joyJutsu},
            {4,joyThrow},
            {5,joyTeleport}
        };
        parametres.setValue("customized",false);
    }
    else{

        joy_cmd={
//            {parametres.value("Horizontal",sf::Joystick::X).toInt(), joyHorizontal},
//            {parametres.value("Vertical",sf::Joystick::Y).toInt(), joyVertical},
            {parametres.value("joyDash",6).toInt(), joyDash},

            {parametres.value("joySquare",0).toInt(), joySquare},
            {parametres.value("joyTriangle",1).toInt(), joyTriangle},
            {parametres.value("joyCircle",2).toInt(), joyCircle},

            {parametres.value("joyJutsu",3).toInt(), joyJutsu},
            {parametres.value("joyThrow",4).toInt(), joyThrow},
            {parametres.value("joyTeleport",5).toInt(), joyTeleport},
        };
    }

    parametres.endGroup();

}

Settings::~Settings(){

}

keyboard_command Settings::kb_action(sf::Keyboard::Key k){

    return key_cmd[k];
};

joystick_command Settings::joy_action(unsigned int button){
    return joy_cmd[button];
}


