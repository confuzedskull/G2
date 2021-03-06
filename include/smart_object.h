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

#ifndef smart_H
#define smart_H
#include "mobile_object.h"
#include "point.h"

//A smart object can detect collision with another object and react
class smart_object: virtual public mobile_object
{
protected:
    std::string collision_sound;
public:
    static std::string default_collisionsound;
    static void action_placeholder();
    std::string get_type() override;
    int touched_side[4];/*The number of the touching object is stored in each index. "0" is no object
    Each index corresponds to a side:[1] is left, [2] is right, [3] is front, [4] is back. Index [0] is the center.*/
    bool collided;
    bool within_range(complex_object target);//check if target is close to the center of this object
    bool within_range(complex_object target, float range);
    bool near_front(complex_object target);//check if target is close to front side of object
    bool near_back(complex_object target);//check if target is close to back side of object
    bool near_left(complex_object target);//check if target is close to left side of object
    bool near_right(complex_object target);//check if target is close to right side of object
    void (*action)();//a function pointer which will be called when collided
    void set_action(void (*act)());
    void repel(complex_object target);//object moves away from target
    void watch(complex_object target);//object turns to target
    void follow(complex_object target);//object turns to target and moves
    void attract(complex_object target);//object moves toward target
    void simon_says(complex_object target);//object changes color according to side touched
    void identify_touched(complex_object target);//variable touching[] is updated with the number of the target
    void set_collisionsound(std::string filename);//specifies which sound to play when collision occurs
    void update() override;
    void save() override;
    void load() override;
    smart_object();
};
#endif // smart_H
