/*  This file is a part of 2DWorld - The Generic 2D Game Engine
    Copyright (C) 2014  James Nakano

    2DWorld is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    2DWorld is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the rest of 2DWorld.  If not, see <http://www.gnu.org/licenses/>.*/

#ifndef PHYSICS_H
#define PHYSICS_H
#include "clickable_object.h"
#include "tangible_object.h"
#include "physics_vector.h"

//A physics object has physical properties and inherits the ability to detect collision from the tangible object class
class physics_object: public clickable_object, public tangible_object
{
    public:
    static point2f origin;
    float mass;
    float delta_time[6];/*each element of this array represents how much time a change in a direction or velocity took
    0:change in x, 1:change in y, 2:change in velocity x, 3:change in velocity y, 4:change in angle, 5:change in angular velocity*/
    float start_time[6];//same as above except it stores the start times
    float stop_time[6];//same as above except it stores the stop times
    physics_vector velocity[2];// index 0:initial velocity, index 1: final velocity
    float angular_velocity[2];
    physics_vector acceleration;
    float angular_acceleration;
    physics_vector momentum;
    float angular_momentum;
    physics_vector force;
    void calc_delta_time();
    void calc_velocity();
    void calc_acceleration();
    void calc_force();
    void calc_momentum();
    void calc_momentum(physics_object p);
    void inertia();
    void physics();
    void update();
    void save();
    physics_object();
};
#endif // PHYSICS_H
