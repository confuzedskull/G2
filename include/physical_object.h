/*  This file is a part of G2 - The Generic 2D Game Engine
    Copyright (C) 2014  James Nakano

    G2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    G2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the rest of G2.  If not, see <http://www.gnu.org/licenses/>.*/

#ifndef PHYSICAL_H
#define PHYSICAL_H
#include "smart_object.h"
#include "pvector.h"
#include "point.h"

//A physics object has physical properties and inherits the ability to detect collision from the smart object class
class physical_object: public smart_object
{
protected:
    point2f rest_position;
    float rest_rotation;//the rotation of the object at rest
public:
    static point2i default_position;
    static int default_width;
    static int default_height;
    static std::string default_texture;
    static std::string default_mask;
    static std::string default_clicksound;
    static std::string default_hoversound;
    static std::string default_collisionsound;
    static std::string default_movementsound;
    point2f get_resting();
    std::string get_type() override;
    float mass;
    float delta_time[6];/*each element of this array represents how much time a change in a direction or velocity took
    0:change in x, 1:change in y, 2:change in velocity x, 3:change in velocity y, 4:change in angle, 5:change in angular velocity*/
    float start_time[6];//same as above except it stores the start times
    float stop_time[6];//same as above except it stores the stop times
    pvector velocity[2];// index 0:initial velocity, index 1: final velocity
    float angular_velocity[2];
    pvector acceleration;
    float angular_acceleration;
    pvector momentum;
    float angular_momentum;
    pvector force;
    float friction;
    float energy[2];//index 0: potential energy, index 1: kinetic energy
    void rest();//set the resting point when the object is not moving
    void calc_delta_time();
    void calc_velocity();
    void calc_acceleration();
    void calc_force();
    void calc_momentum();
    void calc_momentum(physical_object p);
    void calc_energy();
    void calc_physics();
    void apply_inertia();
    void apply_friction();
    void update() override;
    void sync() override;
    void save() override;
    void load() override;
    physical_object();
};
#endif // PHYSICAL_H
