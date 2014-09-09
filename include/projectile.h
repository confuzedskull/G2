#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "physics_object.h"

//A projectile collides with other physics objects
class projectile: public physics_object
{
    public:
    int range;//how far the projectile can go until it resets
    int power;//how much damage the projectile will make
    bool fired;//marks the object as being shot or not
    void reset();//puts the projectile back at its source
    void fire(object source);//an object fires a projectile
    void update();//updates the projectile's values
    projectile();
};
#endif // PROJECTILE_H
