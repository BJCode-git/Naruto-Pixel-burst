#include "settings.h"

Settings::Settings()
{
    QSettings settings= QSettings("BJ-Productions", "Naruto Pixel Burst");

    volume=settings.value("volume",100).toInt();

    settings.beginGroup("Keyboard");
    if(!settings.value("customized",false).toBool()){
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
        settings.setValue("customized",false);
    }
    else{

        key_cmd={
            {settings.value("moveLeft",sf::Keyboard::Left).toInt(), moveLeft},
            {settings.value("moveRight",sf::Keyboard::Right).toInt(), moveRight},
            {settings.value("Jump",sf::Keyboard::Up).toInt(), Jump},
            {settings.value("Dash",sf::Keyboard::A).toInt(), Dash},
            {settings.value("Crounch",sf::Keyboard::Down).toInt(), Crounch},

            {settings.value("Square",sf::Keyboard::Q).toInt(), Square},
            {settings.value("Triangle",sf::Keyboard::Z).toInt(), Triangle},
            {settings.value("Circle",sf::Keyboard::D).toInt(), Circle},

            {settings.value("Jutsu",sf::Keyboard::Space).toInt(), Jutsu},
            {settings.value("Throw",sf::Keyboard::F).toInt(), Throw},
            {settings.value("Teleport",sf::Keyboard::R).toInt(), Teleport},
        };
    }

    settings.endGroup();

    settings.beginGroup("Joystick");
    if(!settings.value("customized",false).toBool()){
        joy_cmd={

            {joyHorizontal,sf::Joystick::X},
            {joyVertical,sf::Joystick::Y},
            {joyDash,6},

            {joySquare,0},
            {joyTriangle,1},
            {joyCircle,2},

            {joyJutsu,3},
            {joyThrow,4},
            {joyTeleport,5}
        };
        settings.setValue("customized",false);
    }
    else{

        joy_cmd={
            {joyHorizontal, settings.value("Horizontal",sf::Joystick::X).toInt()},
            {joyVertical, settings.value("Vertical",sf::Joystick::Y).toInt()},
            {joyDash, settings.value("joyDash",6).toInt()},

            {joySquare, settings.value("joySquare",0).toInt()},
            {joyTriangle, settings.value("joyTriangle",1).toInt()},
            {joyCircle, settings.value("joyCircle",2).toInt()},

            {joyJutsu, settings.value("joyJutsu",3).toInt()},
            {joyThrow, settings.value("joyThrow",4).toInt()},
            {joyTeleport, settings.value("joyTeleport",5).toInt()}
        };
    }

    settings.endGroup();

}

Settings::~Settings(){

}

void* Settings::operator[](unsigned int i) {
    switch(i){
        case 0:
            return &key_cmd;
        case 1:
            return &joy_cmd;
        default:
            return nullptr;
    }
}

keyboard_command Settings::kb_action(sf::Keyboard::Key k){
    std::cout<<"key_cmd : "<<this[0][1]<<" / real val"<<key_cmd[k];
    return key_cmd[k];
};

int Settings::joy_action(joystick_command cmd){
    return joy_cmd[cmd];
}
