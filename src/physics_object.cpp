#include "physics_object.h"
#include "game.h"
#include "compare.h"
void physics_object::set_resting()
{
    if(!moving_horizontal())
        rest.x=current.x;

    if(!moving_vertical())
        rest.y=current.y;
}

void physics_object::calc_delta_time()
{
    if(!moving_horizontal())//x-position is not changing
    {
        stop_time[0]=game::time;
        delta_time[0]=0;
    }
    else
    {
        start_time[0]=game::time;
        delta_time[0]=stop_time[0]-start_time[0];
    }

    if(!moving_vertical())//y-position is not changing
    {
        stop_time[1]=game::time;
        delta_time[1]=0;
    }
    else
    {
        start_time[1]=game::time;
        delta_time[1]=stop_time[1]-start_time[1];
    }

    if(compare(velocity[1].x,velocity[0].x)==0)//x-velocity is not changing
    {
        stop_time[2]=game::time;
        delta_time[2]=0;
    }
    else
    {
        start_time[2]=game::time;
        delta_time[2]=stop_time[2]-start_time[2];
    }

    if(compare(velocity[1].y,velocity[0].y)==0)//y-velocity is not changing
    {
        stop_time[3]=game::time;
        delta_time[3]=0;
    }
    else
    {
        start_time[3]=game::time;
        delta_time[3]=stop_time[3]-start_time[3];
    }
}
void physics_object::calc_velocity()
{
    if(!moving_horizontal())
        velocity[0].x=0.000;
    else
        velocity[0].x=(current.x-rest.x)/delta_time[0];

    if(!moving_vertical())
        velocity[0].y=0.000;
    else
        velocity[0].y=(current.y-rest.y)/delta_time[1];
}

void physics_object::calc_acceleration()
{
    if(!moving_horizontal())
        acceleration.x=0;
    else
        acceleration.x=(velocity[1].x - velocity[0].x)/delta_time[2];

    if(!moving_vertical())
        acceleration.y=0;
    else
        acceleration.y=(velocity[1].y - velocity[0].y)/delta_time[3];

}

void physics_object::calc_force()
{
    force.x=mass*acceleration.x;
    force.y=mass*acceleration.y;
}

void physics_object::calc_momentum()
{
    momentum.x=mass*velocity[0].x;
    velocity[1].x = velocity[0].x + momentum.x;

    momentum.y=mass*velocity[0].y;
    velocity[1].y = velocity[0].y + momentum.y;
}

void physics_object::inertia()
{
    current.x+=momentum.x;//only increase player.x when momentum is not null
    current.y+=momentum.y;//only increase player.y when momentum is not null
}

void physics_object::friction()
{
    if(force.x>0)
        force.x-=0.0001;
    if(force.x<0)
        force.x+=0.0001;
}

void physics_object::physics()
{
    set_resting();
    set_boundaries();
    calc_delta_time();
    calc_velocity();
    calc_acceleration();
    calc_momentum();
    calc_force();
    calc_direction();
    calc_step();
    calc_points();
    calc_sides();
    reset_motion();
    //collision();
}

physics_object::physics_object()
{
    name="physics object";
    mass=0.001;//note: changing this seems to have an effect on set_resting
    velocity[0].x=0.00;
    velocity[0].y=0.00;
    velocity[1].x=0.00;
    velocity[1].y=0.00;
    std::clog<<"object#"<<number<<": "<<name<<" created."<<std::endl;

}
