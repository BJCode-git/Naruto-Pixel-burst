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
        settings.setValue("customized",false);
    }
    else{

        joy_cmd={
//            {settings.value("Horizontal",sf::Joystick::X).toInt(), joyHorizontal},
//            {settings.value("Vertical",sf::Joystick::Y).toInt(), joyVertical},
            {settings.value("joyDash",6).toInt(), joyDash},

            {settings.value("joySquare",0).toInt(), joySquare},
            {settings.value("joyTriangle",1).toInt(), joyTriangle},
            {settings.value("joyCircle",2).toInt(), joyCircle},

            {settings.value("joyJutsu",3).toInt(), joyJutsu},
            {settings.value("joyThrow",4).toInt(), joyThrow},
            {settings.value("joyTeleport",5).toInt(), joyTeleport},
        };
    }

    settings.endGroup();

}

Settings::~Settings(){

}

keyboard_command Settings::kb_action(sf::Keyboard::Key k){

    return key_cmd[k];
};

joystick_command Settings::joy_action(unsigned int button){
    return joy_cmd[button];
}


