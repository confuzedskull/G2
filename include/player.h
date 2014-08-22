#ifndef PLAYER_H
#define PLAYER_H
#include "clickable_object.h"

class player: public clickable_object
{

    public:
    int health;
    int energy;
    int defense;
    int attack;
    int shield;
    bool action[10];
    /* action 1:resting
    action 2: left
    action 3: right
    action 4: up/forward
    action 5: down/backward
    action 6: jumping
    action 7: falling
    action 8: primary
    action 9: secondary
    */
};
#endif // PLAYER_H

