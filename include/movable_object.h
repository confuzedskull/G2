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

#ifndef MOVABLE_H
#define MOVABLE_H
#include "complex_object.h"
#include "physics_vector.h"
#include "point.h"
#include <queue>
#include <array>

//A movable object uses the sides of a complex object to calculate steps in each direction relative to the object's rotation
class movable_object: virtual public complex_object
{
public:
    point2i* rally;
    point2f rest;
    std::queue< std::array<int,3> > action_cue;//actions for the object to perform. The array consists of an action number,times to do, and times done
    float speed;//rate at which an object moves
    float degrees_rotated;//keeps track of the progress of a rotation animation
    float rest_rotation;
    bool rally_set;//whether or not the object has a point to move to
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
    bool move_to_point(int destination_x, int destination_y, float rate);
    bool move_to_point(point2i destination, float rate);
    bool move_to_point(point2i destination);
    bool move_to_point(int destination_x, int destination_y);
    bool perform_actions();//makes the object perform the cued actions
    void cue_action(int action_no, int times);//adds an action to be performed n times to the action cue
    void cue_action(std::string action_name,int times);//adds an action to be performed n times to the action cue
    void set_resting();
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
    void turn_to_point(int destination_x, int destination_y);
    void turn_to_point(point2i destination);
    void reset_motion();
    void update();
    movable_object();
};
const int MOVE_LEFT = 1;
const int MOVE_RIGHT = 2;
const int MOVE_FORWARD = 3;
const int MOVE_BACK = 4;
const int TURN_LEFT = 5;
const int TURN_RIGHT = 6;
#endif // MOVABLE_H
