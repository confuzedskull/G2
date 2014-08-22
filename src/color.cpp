#include "color.h"
void color::brighten()
{
    prev_r=r;
    prev_g=g;
    prev_b=b;
    prev_a=a;
    a+=0.1;
}

void color::brighten(float alpha)
{
    prev_r=r;
    prev_g=g;
    prev_b=b;
    prev_a=a;
    a+=alpha;
}

void color::darken()
{
    prev_r=r;
    prev_g=g;
    prev_b=b;
    prev_a=a;
    a-=0.1;
}

void color::darken(float alpha)
{
    prev_r=r;
    prev_g=g;
    prev_b=b;
    prev_a=a;
    a-=alpha;
}


void color::set(float red, float green, float blue)
{
    prev_r=r;
    prev_g=g;
    prev_b=b;
    prev_a=a;
    r=red;
    g=green;
    b=blue;

}

void color::set(float red, float green, float blue, float alpha)
{
    prev_r=r;
    prev_g=g;
    prev_b=b;
    prev_a=a;
    r=red;
    g=green;
    b=blue;
    a=alpha;

}

void color::set(color c)
{
    prev_r=r;
    prev_g=g;
    prev_b=b;
    prev_a=a;
    r=c.r;
    g=c.g;
    b=c.b;
}

void color::undo()
{
    r=prev_r;
    g=prev_g;
    b=prev_b;
    a=prev_a;
}

color::color()
{
    r=0.0;
    g=0.0;
    b=0.0;
}

color::color(float red, float green, float blue)
{
    r=red;
    g=green;
    b=blue;
}

color::color(float red, float green, float blue, float alpha)
{
    r=red;
    g=green;
    b=blue;
    a=alpha;
}
