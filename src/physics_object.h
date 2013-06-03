#include <\Users\James\Dropbox\My Programs\C++\2dworld\src\tangible_object.h>
class physics_object: public tangible_object
{
    public:
    float mass;
    double delta_time[4];//each element of array represents how much time a change in a direction or velocity took
    //1:change in x, 2:change in velocity, 3:change in velocity x, 4:change in velocity y
    double start_time[4];
    double stop_time[4];
    vector2f velocity[2];// 1:initial velocity, 2: final velocity
    vector2f acceleration;
    vector2f momentum;
    vector2f force;
    int solidity;//a value from 1 to 5 that indicates the density of the object


    void set_resting()
    {
        if(!moving_horizontal())
        rest.x=current.x;

        if(!moving_vertical())
        rest.y=current.y;
    }

    void calc_delta_time()
    {
        if(!moving_horizontal())//x-position is not changing
        {
            stop_time[1]=get_game_time();
            delta_time[1]=0;
        }
        else
        {
            start_time[1]=get_game_time();
            delta_time[1]=stop_time[1]-start_time[1];
        }

        if(!moving_vertical())//y-position is not changing
        {
            stop_time[2]=get_game_time();
            delta_time[2]=0;
        }
        else
        {
            start_time[2]=get_game_time();
            delta_time[2]=stop_time[2]-start_time[2];
        }

        if(compare(velocity[2].x,velocity[1].x)==0)//x-velocity is not changing
        {
            stop_time[3]=get_game_time();
            delta_time[3]=0;
        }
        else
        {
            start_time[3]=get_game_time();
            delta_time[3]=stop_time[3]-start_time[3];
        }

        if(compare(velocity[2].y,velocity[1].y)==0)//y-velocity is not changing
        {
            stop_time[4]=get_game_time();
            delta_time[4]=0;
        }
        else
        {
            start_time[4]=get_game_time();
            delta_time[4]=stop_time[4]-start_time[4];
        }
    }
    void calc_velocity()
    {
        if(!moving_horizontal())
        velocity[1].x=0.000;
        else
        velocity[1].x=(current.x-rest.x)/delta_time[1];

        if(!moving_vertical())
        velocity[1].y=0.000;
        else
        velocity[1].y=(current.y-rest.y)/delta_time[2];
    }

    void calc_acceleration()
    {   if(!moving_horizontal())
        acceleration.x=0;
        else
        acceleration.x=(velocity[2].x - velocity[1].x)/delta_time[3];

        if(!moving_vertical())
        acceleration.y=0;
        else
        acceleration.y=(velocity[2].y - velocity[1].y)/delta_time[4];

    }

    void calc_force()
    {
        force.x=mass*acceleration.x;
        force.y=mass*acceleration.y;
    }

    void calc_momentum()
    {
        momentum.x=mass*velocity[1].x;
        velocity[2].x = velocity[1].x + momentum.x;

        momentum.y=mass*velocity[1].y;
        velocity[2].y = velocity[1].y + momentum.y;
    }

    void inertia()
    {
        current.x+=momentum.x;//only increase player.x when momentum is not null
        current.y+=momentum.y;//only increase player.y when momentum is not null
    }

    void friction()
    {
        if(force.x>0)
        force.x-=0.0001;
        if(force.x<0)
        force.x+=0.0001;
    }

    void physics()
    {
        set_resting();
        set_boundaries();
        calc_delta_time();
        calc_velocity();
        //friction();
        calc_acceleration();
        calc_momentum();
        calc_force();
        calc_direction();
        calc_step();
        calc_points();
        calc_sides();
        //inertia();
        reset_motion();

        //collision();
    }

    physics_object()
    {
        name="physics object";
        mass=0.001;//note: changing this seems to have an effect on set_resting
        velocity[1].x=0.00;
        velocity[1].y=0.00;
        velocity[2].x=0.00;
        velocity[2].y=0.00;
        std::clog<<"object#"<<number<<": "<<name<<" created."<<std::endl;

    }

    ~physics_object()
    {

    }
};
