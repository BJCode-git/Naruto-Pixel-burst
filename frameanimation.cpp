#include "frameanimation.h"
#include <QDebug>

FrameAnimation::FrameAnimation():
    frames()
{
    //current_frame=frames.cbegin();
    i=0;
    continue_animation=false;
    animation_time = sf::seconds(0.0);
}

FrameAnimation::FrameAnimation(std::vector<sf::IntRect> list,bool continuous_animation,sf::Time time):
    frames(list),
    continue_animation(continuous_animation),
    animation_time(time)
{
    //current_frame=frames.cbegin();
    i=0;
}

FrameAnimation::~FrameAnimation()
{
}

void FrameAnimation::setFrameList(std::vector<sf::IntRect> list){
    frames=list;
}

sf::IntRect FrameAnimation::next(void){

     if(i<frames.size()){
          ++i;
         return frames[i-1];
     }
     i=0;
     return frames[frames.size()-1];
}

bool FrameAnimation::is_end(void){
    if (i==0)
        return true;
    return false;
}

sf::Time FrameAnimation::time(){
    return animation_time;
}
