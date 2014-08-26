#include "projectile.h"

void projectile::reset()
{
    current.x=rest.x;
    current.y=rest.y;
    fired=false;
}

void projectile::fire(object source)//an object fires a projectile
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

void projectile::update()
{
//        set_boundaries();

    if(fired)
        move_forward(range);
    else
    {
        //set projectile position to somewhere outside of scene
        current.x=0;
        current.y=0;
    }
}

projectile::projectile()
{
    name="projectile";
    width=10;
    height=10;
    range=1000;
    fired=false;
    step_size=0.5;
//        set_boundaries();
    primary_color=RED;

}
