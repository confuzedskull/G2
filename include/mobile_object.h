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

#ifndef MOBILE_H
#define MOBILE_H
#include "complex_object.h"
#include "pvector.h"
#include "point.h"
#include <queue>
#include <array>

//A mobile object uses the sides of a complex object to calculate steps in each direction relative to the object's rotation
class mobile_object: virtual public complex_object
{
protected:
    point2f* rally;
    std::queue< std::array<int,3> > action_cue;//actions for the object to perform. The array consists of an action number,times to do, and times done
    float degrees_rotated;//keeps track of the progress of a rotation animation
    bool rally_set;//whether or not the object has a point to move to
    std::string movement_sound;
public:
    static float default_speed;
    point2f* get_rally();
    std::string get_type() override;
    float speed;//rate at which an object moves
    bool moving_forward;
    bool moving_backward;
    bool moving_left;
    bool moving_right;
    bool turning_right;
    bool turning_left;
    bool moving_vertical();
    bool moving_horizontal();
    bool turning();
    bool moving();
    //moves object to destination over time at specified rate
    bool moveto_point(int destination_x, int destination_y, float rate);
    bool moveto_point(point2i destination, float rate);
    bool moveto_point(point2i destination);
    bool moveto_point(int destination_x, int destination_y);
    bool moveto_rally();
    bool perform_actions();//makes the object perform the cued actions
    void cue_action(int action_no, int times);//adds an action to be performed n times to the action cue
    void cue_action(std::string action_name,int times);//adds an action to be performed n times to the action cue
    //turn functions make the object rotate over time (as opposed to rotating)
    void turn_right();
    void turn_right(float degrees);
    void turn_left();
    void turn_left(float degrees);
    void move_left();
    void move_left(int units_left);
    void move_left(float units_left);
    void move_right();
    void move_right(int units_right);
    void move_right(float units_right);
    void move_forward();
    void move_forward(int units_forward);
    void move_forward(float units_forward);
    void move_back();
    void move_back(int units_back);
    void move_back(float units_back);
    //rotates object to face the given coordinates
    void turnto_point(int destination_x, int destination_y);
    void turnto_point(point2i destination);
    void set_movementsound(std::string filename);
    void reset_motion();
    void update() override;
    void sync() override;
    void save() override;
    void load() override;
    mobile_object();
};
const int MOVE_LEFT = 1;
const int MOVE_RIGHT = 2;
const int MOVE_FORWARD = 3;
const int MOVE_BACK = 4;
const int TURN_LEFT = 5;
const int TURN_RIGHT = 6;
const int WAIT = 7;
#endif // MOBILE_H
