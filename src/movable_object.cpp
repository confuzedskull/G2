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

#include "movable_object.h"
#include "distance.h"
#include <math.h>
#include <iostream>

float movable_object::default_speed=1.0f;

point2f* movable_object::get_rally()
{
    return rally;
}

void movable_object::reset_motion()
{
    moving_forward=false;
    moving_backward=false;
    moving_left=false;
    moving_right=false;
    turning_left=false;
    turning_right=false;
    speed=default_speed;
}

bool movable_object::moving_vertical()
{
    if(moving_forward || moving_backward)
        return true;
    else
        return false;
}

bool movable_object::moving_horizontal()
{
    if(moving_left || moving_right)
        return true;
    else
        return false;
}

bool movable_object::turning()
{
    if(turning_left || turning_right)
        return true;
    else
        return false;
}

bool movable_object::moving()
{
    if(moving_forward||moving_backward||moving_left||moving_right)
        return true;
    else
        return false;
}

void movable_object::turn_right()
{
    turn_right(1.0f);
}

void movable_object::turn_right(float degrees)
{
    rotation-=speed*degrees;
    turning_right=true;
}

void movable_object::turn_left()
{
    turn_left(1.0f);
}

void movable_object::turn_left(float degrees)
{
    rotation+=speed*degrees;
    turning_left=true;
}

void movable_object::move_left()
{
    move_left(1);
}

void movable_object::move_left(int units_left)
{
    position.x+=leftward.x*speed*units_left;
    position.y+=leftward.y*speed*units_left;
    moving_left=true;
}

void movable_object::move_left(float units_left)
{
    position.x+=leftward.x*speed*units_left;
    position.y+=leftward.y*speed*units_left;
    moving_left=true;
}

void movable_object::move_right()
{
    move_right(1);
}

void movable_object::move_right(int units_right)
{
    position.x+=rightward.x*speed*units_right;
    position.y+=rightward.y*speed*units_right;
    moving_right=true;
}

void movable_object::move_right(float units_right)
{
    position.x+=rightward.x*speed*units_right;
    position.y+=rightward.y*speed*units_right;
    moving_right=true;
}

void movable_object::move_forward()
{
    move_forward(1);
}

void movable_object::move_forward(int units_forward)
{
    position.x+=forward.x*speed*units_forward;
    position.y+=forward.y*speed*units_forward;
    moving_forward=true;
}

void movable_object::move_forward(float units_forward)
{
    position.x+=forward.x*speed*units_forward;
    position.y+=forward.y*speed*units_forward;
    moving_forward=true;
}

void movable_object::move_back()
{
    move_back(1);
}

void movable_object::move_back(int units_back)
{
    position.x+=backward.x*speed*units_back;
    position.y+=backward.y*speed*units_back;
    moving_backward=true;
}

void movable_object::move_back(float units_back)
{
    position.x+=backward.x*speed*units_back;
    position.y+=backward.y*speed*units_back;
    moving_backward=true;
}

void movable_object::turn_to_point(int destination_x, int destination_y)//rotates object to face the given coordinates
{
    if(isgreater(distance((float)destination_x,(float)destination_y,position.x,position.y),get_radius()))//prevent infinite spin
    {
        if(isgreater((float)destination_x,position.x) && isgreater((float)destination_y,position.y))//destination lies in quadrant 1
            rotation = atan(((float)destination_y-position.y)/((float)destination_x-position.x))*180.0f/3.14159f;

        if(isless((float)destination_x,position.x) && isgreater((float)destination_y,position.y))//destination lies in quadrant 2
            rotation = atan(((float)destination_y-position.y)/((float)destination_x-position.x))*180.0f/3.14159f + 180.0f;

        if(isless((float)destination_x,position.x) && isless((float)destination_y,position.y))//destination lies in quadrant 3
            rotation = atan(((float)destination_y-position.y)/((float)destination_x-position.x))*180.0f/3.14159f + 180.0f;

        if(isgreater((float)destination_x,position.x) && isless((float)destination_y,position.y))//destination lies in quadrant 4
            rotation = atan(((float)destination_y-position.y)/((float)destination_x-position.x))*180.0f/3.14159f + 360.0f;

        if((!isless((float)destination_x,position.x)&&!isgreater((float)destination_x,position.x)) && isgreater((float)destination_y,position.y))//destination lies at 12 O'clock
            rotation = 90.0f;

        if((!isless((float)destination_x,position.x)&&!isgreater((float)destination_x,position.x))&& isless((float)destination_y,position.y))//destination lies at 6'O'clock
            rotation = 270.0f;

        if(isless((float)destination_x,position.x) && (!isless((float)destination_y,position.y)&&!isgreater((float)destination_y,position.y)))//destination lies at 9 O'clock
            rotation = 180.0f;

        if(isgreater((float)destination_x,position.x) && (!isless((float)destination_y,position.y)&&!isgreater((float)destination_y,position.y)))//destination lies at 3 O'clock
            rotation = 0.0f;
    }
}
void movable_object::turn_to_point(point2i destination)
{
    turn_to_point(destination.x,destination.y);
}

//moves object to destination over time at specified rate
bool movable_object::move_to_point(int destination_x, int destination_y, float rate)
{
    if(rally_set)
    {
        movable_object::turn_to_point(destination_x, destination_y);
        if(isless((float)distance(position.x,position.y,(float)destination_x,(float)destination_y),get_radius()))
            rally_set=false;
        move_forward(rate);
        moving_forward=true;
        return true;
    }
    else
        return false;
}

bool movable_object::move_to_point(point2i destination,float rate)
{
    return move_to_point(destination.x,destination.y,rate);
}

bool movable_object::move_to_point(point2i destination)
{
    return move_to_point(destination.x,destination.y,1.0f);
}

bool movable_object::move_to_point(int destination_x,int destination_y)
{
    return move_to_point(destination_x,destination_y,1.0f);
}

bool movable_object::move_to_rally()
{
    return move_to_point((int)rally->x,(int)rally->y);
}

void movable_object::cue_action(int action_no, int times)
{
    std::array<int,3> action = {action_no,times,0};
    action_cue.push(action);//add this vector to the actions queue
}

void movable_object::cue_action(std::string action_name, int times)
{
    std::array<int,3> action;
    if(action_name=="move left")
        action[0]=MOVE_LEFT;//set the action
    if(action_name=="move right")
        action[0]=MOVE_RIGHT;//set the action
    if(action_name=="move forward"||action_name=="move up")
        action[0]=MOVE_FORWARD;//set the action
    if(action_name=="move back"||action_name=="move down")
        action[0]=MOVE_BACK;//set the action
    if(action_name=="turn left")
        action[0]=TURN_LEFT;//set the action
    if(action_name=="turn right")
        action[0]=TURN_RIGHT;//set the action
    action[1]=times;//set the number of times to do the action
    action[2]=0;//set the number of times action has been done
    action_cue.push(action);
}

bool movable_object::perform_actions()
{
    if(!action_cue.empty())//there are still some actions to perform
    {
        if(action_cue.front().at(2)<action_cue.front().at(1))//times done(stored at index 2) is less than times to do (stored at index 1)
        {
            switch(action_cue.front().at(0))//action number from index 0 of the stored vector
            {
            case MOVE_LEFT:
                move_left();
                break;
            case MOVE_RIGHT:
                move_right();
                break;
            case MOVE_FORWARD:
                move_forward();
                break;
            case MOVE_BACK:
                move_back();
                break;
            case TURN_LEFT:
                turn_left();
                break;
            case TURN_RIGHT:
                turn_right();
                break;
            }
            action_cue.front().at(2)++;//increment number of times done (stored at index 2)
        }
        else
            action_cue.pop();//if the action is done being performed, remove it from the queue
        return true;//show that the action has been performed
    }
    else
        return false;//still need to perform some actions
}

void movable_object::update()
{
    calc_boundaries();
    if(moving())
        orient();//object only needs to orient itself when it moves
}

void movable_object::sync()
{
    perform_actions();
}

movable_object::movable_object(): complex_object()
{
    speed=default_speed;
    rally = new point2f(position.x,position.y);
    rally_set=false;
    reset_motion();
}
