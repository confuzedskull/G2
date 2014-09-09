#include "movable_object.h"
#include <math.h>
#include <queue>
#include <iostream>
#include "compare.h"
#include "distance.h"
#include "point2f.h"
#include "vector2f.h"

std::queue< std::vector<int> > actions;

void movable_object::calc_step()
{
    //left step
    step[1].x=leftward.x*step_size;
    step[1].y=leftward.y*step_size;
    //right step
    step[2].x=rightward.x*step_size;
    step[2].y=rightward.y*step_size;
    //forward step
    step[3].x=forward.x*step_size;
    step[3].y=forward.y*step_size;
    //backward step
    step[4].x=backward.x*step_size;
    step[4].y=backward.y*step_size;
}

void movable_object::reset_motion()
{
    moving_forward=false;
    moving_backward=false;
    moving_left=false;
    moving_right=false;
}

bool movable_object::moving_vertical()
{
    if(moving() && compare(current.y,rest.y)!=0)
        return true;
    else
        return false;
}

bool movable_object::moving_horizontal()
{
    if(moving() && compare(current.x,rest.x)!=0)
        return true;
    else
        return false;
}

bool movable_object::resting()
{
    if(!moving_vertical() && !moving_horizontal())
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
    rotation--;
}

void movable_object::turn_right(float degrees)
{
    rotation-=degrees;
}

void movable_object::turn_left()
{
    rotation++;
}

void movable_object::turn_left(float degrees)
{
    rotation+=degrees;
}

void movable_object::move_left()
{
    current.x+=leftward.x;
    current.y+=leftward.y;
    moving_left=true;
}

void movable_object::move_left(float units_left)
{
    current.x+=leftward.x*units_left;
    current.y+=leftward.y*units_left;
    moving_left=true;
}

void movable_object::move_right()
{
    current.x+=rightward.x;
    current.y+=rightward.y;
    moving_right=true;
}

void movable_object::move_right(float units_right)
{
    current.x+=rightward.x*units_right;
    current.y+=rightward.y*units_right;
    moving_right=true;
}

void movable_object::move_forward()
{
    current.x+=forward.x;
    current.y+=forward.y;
    moving_forward=true;
}

void movable_object::move_forward(float units_forward)
{
    current.x+=forward.x*units_forward;
    current.y+=forward.y*units_forward;
    moving_forward=true;
}

void movable_object::move_back()
{
    current.x+=backward.x;
    current.y+=backward.y;
    moving_backward=true;
}

void movable_object::move_back(float units_back)
{
    current.x+=backward.x*units_back;
    current.y+=backward.y*units_back;
    moving_backward=true;
}

void movable_object::walk_left()
{
    current.x+=step[1].x;
    current.y+=step[1].y;
}

void movable_object::walk_left(int steps_left)
{
    current.x+=step[1].x*steps_left;
    current.y+=step[1].y*steps_left;
}

void movable_object::walk_right()
{
    current.x+=step[2].x;
    current.y+=step[2].y;
}

void movable_object::walk_right(int steps_right)
{
    current.x+=step[2].x*steps_right;
    current.y+=step[2].y*steps_right;
}

void movable_object::walk_forward()
{
    current.x+=step[3].x;
    current.y+=step[3].y;
}

void movable_object::walk_forward(int steps_forward)
{
    current.x+=step[3].x*steps_forward;
    current.y+=step[3].y*steps_forward;
}

void movable_object::walk_back()
{
    current.x+=step[4].x;
    current.y+=step[4].y;
}

void movable_object::walk_back(int steps_back)
{
    current.x+=step[4].x*steps_back;
    current.y+=step[4].y*steps_back;
}

void movable_object::walk(int direction,int steps)//moves object steps in direction[1,2,3,or 4]
{
    current.x+=step[direction].x*steps;
    current.y+=step[direction].y*steps;
}

void movable_object::turn_to_point(float destination_x, float destination_y)//rotates object to face the given coordinates
{
    if(compare(destination_x,current.x)==1 && compare(destination_y,current.y)==1)//destination lies in quadrant 1
        rotation = atan((destination_y-current.y)/(destination_x-current.x))*180/3.14159;

    if(compare(destination_x,current.x)==-1 && compare(destination_y,current.y)==1)//destination lies in quadrant 2
        rotation = atan((destination_y-current.y)/(destination_x-current.x))*180/3.14159 + 180;

    if(compare(destination_x,current.x)==-1 && compare(destination_y,current.y)==-1)//destination lies in quadrant 3
        rotation = atan((destination_y-current.y)/(destination_x-current.x))*180/3.14159 + 180;

    if(compare(destination_x,current.x)==1 && compare(destination_y,current.y)==-1)//destination lies in quadrant 4
        rotation = atan((destination_y-current.y)/(destination_x-current.x))*180/3.14159 + 360;

    if(compare(destination_x,current.x)==0 && compare(destination_y,current.y)==1)//destination lies at 12 O'clock
        rotation = 90;

    if(compare(destination_x,current.x)==0 && compare(destination_y,current.y)==-1)//destination lies at 6'O'clock
        rotation = 270;

    if(compare(destination_x,current.x)==-1 && compare(destination_y,current.y)==0)//destination lies at 9 O'clock
        rotation = 180;

    if(compare(destination_x,current.x)==1 && compare(destination_y,current.y)==0)//destination lies at 3 O'clock
        rotation = 0;
}

void movable_object::turn_to_point(point2f destination)
{
    turn_to_point(destination.x,destination.y);
}
//moves object to destination over time at specified rate
void movable_object::walk_to_point(float destination_x, float destination_y, float rate)
{
    if(rally_set)
    {
        turn_to_point(destination_x,destination_y);
        if(compare(distance(current.x,current.y,destination_x,destination_y),1.5)==-1)
            rally_set=false;
        current.x+=step[3].x*rate;
        current.y+=step[3].y*rate;
    }

}

void movable_object::walk_to_point(point2f destination, float rate)
{
    walk_to_point(destination.x,destination.y,rate);
}

//moves object to destination over time at specified rate
void movable_object::move_to_point(float destination_x, float destination_y, float rate)
{
    if(rally_set)
    {
        movable_object::     turn_to_point(destination_x,destination_y);
        if(compare(distance(current.x,current.y,destination_x,destination_y),1.5f)==-1)//less than or same
        {
            rally_set=false;
        }
        move_forward(rate);
        moving_forward=true;
    }

}

void movable_object::move_to_point(point2f destination,float rate)
{
    move_to_point(destination.x,destination.y,rate);
}

void movable_object::add_action(int action_no, int times)
{
    std::vector<int> action;
    action.push_back(action_no);//number of the action to do
    action.push_back(times);//number of times to do the action
    action.push_back(0);//how many times its already been done
    actions.push(action);
}

void movable_object::perform_actions()
{
    if(!actions.empty())
    {
        if(actions.front().at(2)<actions.front().at(1))//times done is less than times to do
        {
            switch(actions.front().at(0))
            {
            case 1://move left
                move_left();
                break;
            case 2://move right
                move_right();
                break;
            case 3://move up
                move_forward();
                break;
            case 4://move down
                move_back();
                break;
            case 5://turn left
                turn_left();
                break;
            case 6://turn right
                turn_right();
                break;
            }
            actions.front().at(2)++;
        }
        else
            actions.pop();
    }
}

movable_object::movable_object()
{
    name="movable object";
    rally = &rest;
    rally_set=false;
    step_size=0.001;
    std::clog<<"object#"<<number<<": "<<name<<" created."<<std::endl;
}
