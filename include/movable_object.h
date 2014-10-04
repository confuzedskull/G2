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
#include "vector2f.h"
#include "point2f.h"
#include <queue>

//A movable object uses the sides of a complex object to calculate steps in each direction relative to the object's rotation
class movable_object: virtual public complex_object
{
public:
    point2f * rally;
    bool rally_set;//whether or not the object has a point to move to
    float degrees_rotated;//keeps track of the progress of a rotation animation
    float speed;
    void set_resting();
    bool moving_forward;
    bool moving_backward;
    bool moving_left;
    bool moving_right;
    bool turning_right;
    bool turning_left;
    std::queue< std::vector<int> > actions;//a cue of actions for the object to perform
    void reset_motion();
    bool moving_vertical();
    bool moving_horizontal();
    bool turning();
    bool moving();
    //turn functions make the object rotate over time
    void turn_right();
    void turn_right(float degrees);
    void turn_left();
    void turn_left(float degrees);
    void move_left();
    void move_left(float units_left);
    void move_right();
    void move_right(float units_right);
    void move_forward();
    void move_forward(float units_forward);
    void move_back();
    void move_back(float units_back);
    //rotates object to face the given coordinates
    void turn_to_point(float destination_x, float destination_y);
    void turn_to_point(point2f destination);
    //moves object to destination over time at specified rate
    bool move_to_point(float destination_x, float destination_y, float rate);
    bool move_to_point(point2f destination,float rate);
    bool move_to_point(point2f destination);
    bool move_to_point(float destination_x, float destination_y);
    void add_action(int action_no, int times);//adds an action to be performed n times to the action cue
    bool perform_actions();//makes the object perform the cued actions
    void update();
    movable_object();
};
#endif // MOVABLE_H
