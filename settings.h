#ifndef SETTINGS_H
#define SETTINGS_H
#include <QSettings>
#include <iostream>
#include <SFML/Graphics.hpp>

enum keyboard_command{
    moveLeft=sf::Keyboard::Left,//=71
    moveRight=sf::Keyboard::Right,
    Jump=sf::Keyboard::Up,
    Dash=sf::Keyboard::A,
    Crounch=sf::Keyboard::Down,

    Square=sf::Keyboard::Q,
    Triangle=sf::Keyboard::Z,
    Circle=sf::Keyboard::D,

    Jutsu=sf::Keyboard::Space,
    Throw=sf::Keyboard::F,
    Teleport=sf::Keyboard::R

};

enum joystick_command{

    joyHorizontal=sf::Joystick::X,//=71
    joyVertical=sf::Joystick::Y,
    joyDash=6,

    joySquare=0,
    joyTriangle=1,
    joyCircle=2,

    joyJutsu=3,
    joyThrow=4,
    joyTeleport=5
};

//enum Dir_perso{Dir_Up=585,Dir_Down=480,Dir_Left=585,Dir_Right=585};
enum Dir_perso{Dir_Up=0,Dir_Down,Dir_Left,Dir_Right};

union all_cmd{
    std::map<int ,keyboard_command> keyboard;
    std::map<int,joystick_command> joystick;
};

class Settings
{
public:
    Settings();
    ~Settings();
     void* operator[](unsigned i);
     keyboard_command kb_action(sf::Keyboard::Key k);
     int joy_action(joystick_command cmd);
private:
    QSettings settings;
    int volume;
    //std::map<sf::Keyboard::Key ,keyboard_command> key_cmd;
    std::map<int ,keyboard_command> key_cmd;
    std::map<joystick_command,unsigned int> joy_cmd;
};

#endif // SETTINGS_H
