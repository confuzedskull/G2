#include <\Users\James\Dropbox\My Programs\C++\2dworld\src\tangible_object.h>
class physics_object: public tangible_object
{
    public:
    float mass;
    float delta_time[4];//each element of array represents how much time a change in a direction or velocity took
    //1:change in x, 2:change in velocity, 3:change in velocity x, 4:change in velocity y
    vect velocity[2];// 1:initial velocity, 2: final velocity
    vect acceleration;
    vect momentum;
    vect force;
    int solidity;//a value from 1 to 5 that indicates the density of the object


    void set_resting()
    {

        if(velocity[2].y>-1 && velocity[2].y<1)
        {
            resting.y=current.y;
        }

        if(velocity[2].x>-1 && velocity[2].x<1)
        {
            resting.x=current.x;
        }
    }

    void calc_delta_time()
    {

        if(current.x==resting.x)
        delta_time[1]=0;
        else
        delta_time[1]+=0.004;

        if(current.y==resting.y)
        delta_time[2]=0;
        else
        delta_time[2]+=0.004;

        if(velocity[2].x==velocity[1].x)
        delta_time[3]=0;
        else
        delta_time[3]+=0.004;

        if(velocity[2].y==velocity[1].y)
        delta_time[4]=0;
        else
        delta_time[4]+=0.004;
    }
    void calc_velocity()
    {
        velocity[1].x=(current.x-resting.x)/delta_time[1];
        velocity[1].y=(current.y-resting.y)/delta_time[2];
    }

    void calc_acceleration()
    {   if(delta_time[3]!=0)
        acceleration.x=0;
        else
        acceleration.x=(velocity[2].x - velocity[1].x)/delta_time[3];

        if(delta_time[4]!=0)
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
        //player.x+=momentum.x; //only increase player.x when momentum is not null
        velocity[2].x = velocity[1].x + momentum.x;

        momentum.y=mass*velocity[1].y;
        //player.y+=momentum.y; //only increase player.y when momentum is not null
        velocity[2].y = velocity[1].y + momentum.y;
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
        //set_resting();
        //calc_delta_time();
        //calc_velocity();
        //friction();
        //calc_acceleration();
        //calc_momentum();
        //calc_force();
        calc_direction();
        calc_step();
        calc_points();

        calc_sides();

        //collision();
    }

    physics_object()
    {
        name="physics object";
        mass=0.01;//note: changing this seems to have an effect on set_resting
        printf("object %d: %s created\n", number, name);
    }

    ~physics_object()
    {
        printf("object %d: %s distroyed\n", number, name);
    }
};
