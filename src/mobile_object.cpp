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

#include "mobile_object.h"
#include "utilities.h"
#include "audio.h"
#include <math.h>
#include <fstream>
#include <sstream>
#include <iostream>

float mobile_object::default_speed=1.0f;

std::string mobile_object::get_type()
{
    return "mobile object";
}

point2f* mobile_object::get_rally()
{
    return rally;
}

void mobile_object::reset_motion()
{
    moving_forward=false;
    moving_backward=false;
    moving_left=false;
    moving_right=false;
    turning_left=false;
    turning_right=false;
    speed=default_speed;
}

bool mobile_object::moving_vertical()
{
    if(moving_forward || moving_backward)
        return true;
    else
        return false;
}

bool mobile_object::moving_horizontal()
{
    if(moving_left || moving_right)
        return true;
    else
        return false;
}

bool mobile_object::turning()
{
    if(turning_left || turning_right)
        return true;
    else
        return false;
}

bool mobile_object::moving()
{
    if(moving_forward||moving_backward||moving_left||moving_right)
        return true;
    else
        return false;
}

void mobile_object::turn_right()
{
    turn_right(1.0f);
}

void mobile_object::turn_right(float degrees)
{
    rotation-=speed*degrees;
    turning_right=true;
    if(!muted)
        audio::play(movement_sound);
}

void mobile_object::turn_left()
{
    turn_left(1.0f);
}

void mobile_object::turn_left(float degrees)
{
    rotation+=speed*degrees;
    turning_left=true;
    if(!muted)
        audio::play(movement_sound);
}

void mobile_object::move_left()
{
    move_left(1);
}

void mobile_object::move_left(int units_left)
{
    position.x+=leftward.x*speed*units_left;
    position.y+=leftward.y*speed*units_left;
    moving_left=true;
    if(!muted)
        audio::play(movement_sound);
}

void mobile_object::move_left(float units_left)
{
    position.x+=leftward.x*speed*units_left;
    position.y+=leftward.y*speed*units_left;
    moving_left=true;
    if(!muted)
        audio::play(movement_sound);
}

void mobile_object::move_right()
{
    move_right(1);
}

void mobile_object::move_right(int units_right)
{
    position.x+=rightward.x*speed*units_right;
    position.y+=rightward.y*speed*units_right;
    moving_right=true;
    if(!muted)
        audio::play(movement_sound);
}

void mobile_object::move_right(float units_right)
{
    position.x+=rightward.x*speed*units_right;
    position.y+=rightward.y*speed*units_right;
    moving_right=true;
    if(!muted)
        audio::play(movement_sound);
}

void mobile_object::move_forward()
{
    move_forward(1);
}

void mobile_object::move_forward(int units_forward)
{
    position.x+=forward.x*speed*units_forward;
    position.y+=forward.y*speed*units_forward;
    moving_forward=true;
    if(!muted)
        audio::play(movement_sound);
}

void mobile_object::move_forward(float units_forward)
{
    position.x+=forward.x*speed*units_forward;
    position.y+=forward.y*speed*units_forward;
    moving_forward=true;
    if(!muted)
        audio::play(movement_sound);
}

void mobile_object::move_back()
{
    move_back(1);
}

void mobile_object::move_back(int units_back)
{
    position.x+=backward.x*speed*units_back;
    position.y+=backward.y*speed*units_back;
    moving_backward=true;
    if(!muted)
        audio::play(movement_sound);
}

void mobile_object::move_back(float units_back)
{
    position.x+=backward.x*speed*units_back;
    position.y+=backward.y*speed*units_back;
    moving_backward=true;
    if(!muted)
        audio::play(movement_sound);
}

void mobile_object::turnto_point(int destination_x, int destination_y)//rotates object to face the given coordinates
{
    if(isgreater(utilities::distance((float)destination_x,(float)destination_y,position.x,position.y),get_radius()))//prevent infinite spin
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
void mobile_object::turnto_point(point2i destination)
{
    turnto_point(destination.x,destination.y);
}

//moves object to destination over time at specified rate
bool mobile_object::moveto_point(int destination_x, int destination_y, float rate)
{
    if(rally_set)
    {
        mobile_object::turnto_point(destination_x, destination_y);
        if(isless((float)utilities::distance(position.x,position.y,(float)destination_x,(float)destination_y),get_radius()))
        {
            rally_set=false;
            reset_motion();
        }
        move_forward(rate);
        moving_forward=true;
        return true;
    }
    else
        return false;
}

bool mobile_object::moveto_point(point2i destination,float rate)
{
    return moveto_point(destination.x,destination.y,rate);
}

bool mobile_object::moveto_point(point2i destination)
{
    return moveto_point(destination.x,destination.y,1.0f);
}

bool mobile_object::moveto_point(int destination_x,int destination_y)
{
    return moveto_point(destination_x,destination_y,1.0f);
}

bool mobile_object::moveto_rally()
{
    return moveto_point((int)rally->x,(int)rally->y);
}

void mobile_object::cue_action(int action_no, int times)
{
    std::array<int,3> action = {action_no,times,0};
    action_cue.push(action);//add this vector to the actions queue
}

void mobile_object::cue_action(std::string action_name, int times)
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
    if(action_name=="wait")
        action[0]=WAIT;
    action[1]=times;//set the number of times to do the action
    action[2]=0;//set the number of times action has been done
    action_cue.push(action);
}

bool mobile_object::perform_actions()
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
            case WAIT:
                break;//waiting is doing nothing
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

void mobile_object::set_movementsound(std::string filename)
{
    if(audio::sounds.find(filename)!=audio::sounds.end())
        movement_sound=filename;
    else
        std::cerr<<filename<<" not found.\n";
}

void mobile_object::update()
{
    calc_boundaries();
    if(moving())
        orient();//object only needs to orient itself when it moves
}

void mobile_object::sync()
{
    perform_actions();
}

void mobile_object::save()
{
    std::stringstream filename;
    filename<<"./data/objects/object#"<<number<<".mbo";
    std::ofstream object_file(filename.str());
    if(object_file.bad())
    {
        std::cerr<<"bad file name\n";
        return;
    }
    object_file.precision(3);
    object_file.setf(std::ios::fixed);
    //save basic object properties
    object_file<<position.x<<' '<<position.y<<std::endl;
    object_file<<rotation<<std::endl;
    object_file<<width<<' '<<height<<std::endl;
    object_file<<fill_color.str()<<std::endl;
    object_file<<marker_color.str()<<std::endl;
    object_file<<border_color.str()<<std::endl;
    object_file<<filled<<std::endl;
    object_file<<bordered<<std::endl;
    object_file<<textured<<std::endl;
    object_file<<masked<<std::endl;
    object_file<<visible<<std::endl;
    object_file<<selected<<std::endl;
    object_file<<muted<<std::endl;
    object_file<<texture<<std::endl;
    object_file<<mask<<std::endl;
    for(auto p:properties)
        object_file<<p.first<<' '<<p.second<<std::endl;
    object_file<<std::endl;
    //save mobile object properties
    object_file<<movement_sound<<std::endl;
    object_file<<speed<<std::endl;
    object_file<<degrees_rotated<<std::endl;
    object_file<<rally_set<<std::endl;
    object_file<<moving_forward<<std::endl;
    object_file<<moving_backward<<std::endl;
    object_file<<moving_left<<std::endl;
    object_file<<moving_right<<std::endl;
    object_file<<turning_right<<std::endl;
    object_file<<turning_left<<std::endl;
    while(!action_cue.empty())
    {
        object_file<<action_cue.front().at(0)<<' '<<action_cue.front().at(1)<<' '<<action_cue.front().at(2)<<std::endl;
        action_cue.pop();
    }
    object_file<<std::endl;//add an empty line to signal end of action cue
    object_file.close();
    std::clog<<"object#"<<number<<"(movable object)"<<" saved.\n";
}

void mobile_object::load()
{
    std::ifstream object_file(file_name);//access file by name
    if(object_file.bad())//make sure the file is there
    {
        std::cerr<<"bad file name\n";
        return;
    }
    object_file.precision(3);
    object_file.setf(std::ios::fixed);
    //load basic object properties
    object_file>>position.x>>position.y;
    object_file>>rotation;
    object_file>>width>>height;
    object_file>>fill_color.r>>fill_color.g>>fill_color.b;
    object_file>>marker_color.r>>marker_color.g>>marker_color.b;
    object_file>>border_color.r>>border_color.g>>border_color.b;
    object_file>>filled;
    object_file>>bordered;
    object_file>>textured;
    object_file>>masked;
    object_file>>visible;
    object_file>>selected;
    object_file>>muted;
    object_file>>texture;
    object_file>>mask;
    char first_char=' ';
     //load custom properties
    while(first_char>0)//not newline or out of bounds
    {
        std::string name;
        int value;
        object_file.get();//eat the null character
        first_char=object_file.peek();//check the first character of the line
        if(first_char=='\n')
            break;
        object_file>>name>>value;
        add_property(name,value);
    }
    //load mobile object properties
    object_file>>movement_sound;
    object_file>>speed;
    object_file>>degrees_rotated;
    object_file>>rally_set;
    object_file>>moving_forward;
    object_file>>moving_backward;
    object_file>>moving_left;
    object_file>>moving_right;
    object_file>>turning_right;
    object_file>>turning_left;
    first_char=' ';
    while(first_char>0)//not newline or out of bounds
    {
        //load the cued actions
        object_file.get();//eat the null character
        first_char=object_file.peek();//check the first character of the line
        if(first_char=='\n')
            break;
        std::array<int,3> action;
        object_file>>action[0]>>action[1]>>action[2];//add action number, times to do, and  times performed
        action_cue.push(action);//add action to the cue
    }
    std::clog<<"object#"<<number<<"(mobile object)"<<" loaded.\n";
}

mobile_object::mobile_object(): complex_object()
{
    speed=default_speed;
    rally = new point2f(position.x,position.y);
    rally_set=false;
    reset_motion();
}
