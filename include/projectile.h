#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "physics_object.h"

class projectile: public physics_object
{
    public:
    int range;//how far the projectile can go until it resets
    int power;
    bool fired;

    void reset();
    void fire(object source);//an object fires a projectile
    void update();
    projectile();
};

#endif // PROJECTILE_H

