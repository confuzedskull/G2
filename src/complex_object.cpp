#include "complex_object.h"
#include <math.h>
#include <iostream>

void complex_object::calc_sides()
{
    calc_points();
    front_side.set(front_left,front_right);
    back_side.set(back_left,back_right);
    left_side.set(front_left,back_left);
    right_side.set(front_right,back_right);
}

void complex_object::calc_direction()
{
    leftward.set(-(sin(rotation*3.14159/180)),cos(rotation*3.14159/180));
    rightward.set(sin(rotation*3.14159/180),-(cos(rotation*3.14159/180)));
    forward.set(cos(rotation*3.14159/180),sin(rotation*3.14159/180));
    backward.set(-(cos(rotation*3.14159/180)),-(sin(rotation*3.14159/180)));
}

void complex_object::rotate(float angle)
{
    rotation+=angle;
    calc_direction();
    calc_sides();
}


void complex_object::calc_points()
{
    front.set(current.x+(forward.x*(height/2)),current.y+(forward.y*(height/2)));
    back.set(current.x+(backward.x*(height/2)),current.y+(backward.y*(height/2)));
    left.set(current.x+(leftward.x*(width/2)),current.y+(leftward.y*(width/2)));
    right.set(current.x+(rightward.x*(width/2)),current.y+(rightward.y*(width/2)));
    front_left.set(current.x+((forward.x+leftward.x)*(height/2)),current.y+((forward.y+leftward.y)*(height/2)));
    front_right.set(current.x+((forward.x+rightward.x)*(height/2)),current.y+((forward.y+rightward.y)*(height/2)));
    back_left.set(current.x+((backward.x+leftward.x)*(width/2)),current.y+((backward.y+leftward.y)*(width/2)));
    back_right.set(current.x+((backward.x+rightward.x)*(width/2)),current.y+((backward.y+rightward.y)*(width/2)));
}

void complex_object::render()
{
    glColor3f(primary_color.r,primary_color.g,primary_color.b);//color the square with object.primary_color
    if(!visible)
    {
        std::clog<<"object#"<<number<<": "<<name<<" rendered."<<std::endl;
        visible=true;
    }
    glBegin(GL_POLYGON);//draws a filled in rectangle
    glVertex2f(back_left.x, back_left.y); // The bottom left corner
    glVertex2f(front_left.x, front_left.y); // The top left corner
    glVertex2f(front_right.x, front_right.y); // The top right corner
    glVertex2f(back_right.x, back_right.y); // The bottom right corner
    glEnd();//finish drawing
}

complex_object::complex_object()
{
    name="complex object";
    set_boundaries();
    std::clog<<"object#"<<number<<": "<<name<<" created."<<std::endl;
}

