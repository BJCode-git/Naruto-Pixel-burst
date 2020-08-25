#ifndef FRAMEANIMATION_H
#define FRAMEANIMATION_H
#include "settings.h"
#include <list>

class FrameAnimation
{
public:
    FrameAnimation();
    FrameAnimation(std::vector<sf::IntRect> list,bool continuous_animation=false,sf::Time time=sf::seconds(0.0));
    ~FrameAnimation();

    void setFrameList(std::vector<sf::IntRect> list);
    sf::IntRect next(void);
    bool is_end(void);
    sf::Time time();

private:
    std::vector<sf::IntRect> frames;
    //std::vector<sf::IntRect>::const_iterator current_frame;
    unsigned int i;
    bool continue_animation;
    sf::Time animation_time;
};

#endif // FRAMEANIMATION_H
