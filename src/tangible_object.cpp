#include "tangible_object.h"
#include "compare.h"
#include "distance.h"

void tangible_object::repel(object B)//object moves away from object B
{
    if(near_front(B))
        move_back();
    if(near_back(B))
        move_forward();
    if(near_left(B))
        move_right();
    if(near_right(B))
        move_left();

}

void tangible_object::attract(object B)//object moves toward object B
{
    if(near_front(B))
        move_forward();
    if(near_back(B))
        move_back();
    if(near_left(B))
        move_left();
    if(near_right(B))
        move_right();

}

void tangible_object::simon_says(object B)//object changes color according to side touched
{
    if(near_front(B))
        primary_color.set(RED);
    if(near_back(B))
        primary_color.set(GREEN);
    if(near_left(B))
        primary_color.set(BLUE);
    if(near_right(B))
        primary_color.set(YELLOW);

}

void tangible_object::identify(object B)//variable touching[] is updated with number of the touched object
{
    if(near_left(B))
        touching[1]=B.number;
    else
        touching[1]=0;
    if(near_right(B))
        touching[2]=B.number;
    else
        touching[2]=0;
    if(near_front(B))
        touching[3]=B.number;
    else
        touching[3]=0;
    if(near_back(B))
        touching[4]=B.number;
    else
        touching[4]=0;
}

bool tangible_object::is_close(object B)
{
    if(compare(distance(current,B.current),(get_radius()+B.get_radius()))<=0)
        return true;
    else
        return false;
}
bool tangible_object::near_front(object B)
{
    if(compare(distance(front,B.current),B.get_radius())<=0)
    {
        return true;
    }
    else
        return false;
}
bool tangible_object::near_back(object B)
{
    if(compare(distance(back,B.current),B.get_radius())<=0)
    {
        return true;
    }
    else
        return false;
}

bool tangible_object::near_left(object B)
{
    if(compare(distance(left,B.current),B.get_radius())<=0)
    {
        return true;
    }
    else
        return false;
}

bool tangible_object::near_right(object B)
{
    if(compare(distance(right,B.current),B.get_radius())<=0)
    {
        return true;
    }
    else
        return false;
}

tangible_object::tangible_object()
{
    name="tangible object";
    std::clog<<"object#"<<number<<": "<<name<<" created."<<std::endl;
}