#ifndef PHYSICS_H
#define PHYSICS_H
#include "tangible_object.h"
#include "vector2f.h"

class physics_object: public tangible_object
{
    public:
    float mass;
    float delta_time[4];//each element of array represents how much time a change in a direction or velocity took
    //0:change in x, 1:change in velocity, 2:change in velocity x, 3:change in velocity y
    float start_time[4];
    float stop_time[4];
    vector2f velocity[2];// 0:initial velocity, 1: final velocity
    vector2f acceleration;
    vector2f momentum;
    vector2f force;
    int solidity;//a value from 1 to 5 that indicates the density of the object
    void set_resting();
    void calc_delta_time();
    void calc_velocity();
    void calc_acceleration();
    void calc_force();
    void calc_momentum();
    void inertia();
    void friction();
    void physics();
    physics_object();

};

#endif // PHYSICS_H

