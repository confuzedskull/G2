class projectile: public physics_object
{
    public:

    int range;//how far the projectile can go until it resets
    int power;
    bool fired;

    void reset()
    {
        current.x=rest.x;
        current.y=rest.y;
        fired=false;
    }

    void fire(object source)//an object fires a projectile
    {
        if(!fired)
        {
        current.x=source.current.x;
        rest.x=source.current.x;
        current.y=source.current.y;
        rest.y=source.current.y;
        rotation=source.rotation;
        calc_step();//orient it to the direction aiming
        fired=true;
        }
    }

    void update()
    {
//        set_boundaries();

        if(fired)
        move_forward(range);
        else
        {//set projectile position to somewhere outside of scene
            current.x=0;
            current.y=0;
        }
    }

    projectile()
    {
        name="projectile";
        width=10;
        height=10;
        range=1000;
        fired=false;
        step_size=0.5;
//        set_boundaries();
        current_color=RED;

    }

    ~projectile()
    {

    }
};
