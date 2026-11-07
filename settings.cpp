#include "settings.h"

Settings::Settings(){
    loadDefaultSettings();
    loadFromFile();
}

Settings::~Settings(){

}

void Settings::loadDefaultSettings(){
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
    
    volume = 100;
}

void Settings::loadFromFile(){
    std::ifstream file("settings.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.find("volume=") == 0) {
                volume = std::stoi(line.substr(7));
            }
        }
        file.close();
    }
}

void Settings::saveToFile(){
    std::ofstream file("settings.txt");
    if (file.is_open()) {
        file << "volume=" << volume << std::endl;
        file.close();
    }
}

keyboard_command Settings::kb_action(sf::Keyboard::Key k){
    auto it = key_cmd.find(k);
    if (it != key_cmd.end()) {
        return it->second;
    }
    return static_cast<keyboard_command>(-1); // Return invalid command
};

joystick_command Settings::joy_action(unsigned int button){
    auto it = joy_cmd.find(button);
    if (it != joy_cmd.end()) {
        return it->second;
    }
    return static_cast<joystick_command>(-1); // Return invalid command
}