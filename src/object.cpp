#include "object.h"

//initialize static variable
int object::total_objects=0;

void object::set_boundaries()//calculates the max's and mins
{
    xmin= current.x-(width/2);
    xmax= current.x+(width/2);
    ymin= current.y-(height/2);
    ymax= current.y+(height/2);

}

void object::render()//draws the object
{
    glPushMatrix();//need push and pop so that entire scene isn't rotated
    glTranslatef(current.x,current.y,0.0);//translate object according to coordinates
    glRotatef(rotation,0,0,1);//rotates object with object.rotation
    glTranslatef(-current.x,-current.y,0.0);//translate object according to coordinates
    glColor3f(current_color.r,current_color.g,current_color.b);//color the square with object.current_color

    if(!visible)
    {
        std::clog<<"object#"<<number<<": "<<name<<" rendered."<<std::endl;
        visible=true;
    }
    glBegin(GL_POLYGON);//draws a filled in rectangle
    glVertex2f(xmin, ymin); // The bottom left corner
    glVertex2f(xmin, ymax); // The top left corner
    glVertex2f(xmax, ymax); // The top right corner
    glVertex2f(xmax, ymin); // The bottom right corner

    glEnd();//finish drawing

    glPopMatrix();//reset transformation matrix

}

void object::undo_color()//sets the current color to the previous
{
    current_color.r=prev_color.r;
    current_color.g=prev_color.g;
    current_color.b=prev_color.b;
}

void object::rotate(float angle)
{
    rotation+=angle;
}

int object::get_radius()//calculates a radius from the width and height
{
    return ((width/2)+(height/2))/2;
}


object::object()//constructs an object
{
    name="generic object";
    number=total_objects;
    total_objects++;
    current.x=320.0;
    current.y=160.0;
    rest.x=320.0;
    rest.y=160.0;
    width=64;
    height=64;
    prev_color.set(0.0,0.0,0.0);
    current_color.set(0.0,0.0,0.0);
    rotation=90;
    visible=false;
    std::clog<<"object#"<<number<<": "<<name<<" created."<<std::endl;
}

object::object(float x, float y, float w, float h, color c)
{
    name="generic object";
    number=total_objects;
    total_objects++;
    current.x=x;
    current.y=y;
    rest.x=x;
    rest.y=y;
    width=w;
    height=h;
    current_color=c;
    rotation=90.1;
    visible=false;
}
