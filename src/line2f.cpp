#include "line2f.h"
#include "compare.h"

line2f::line2f()
{

}

point2f line2f::midpoint()
{
    point2f m;
    m.x = (A.x + B.x) / 2;
    m.y = (A.y + B.y) / 2;
    return m;
}

float line2f::slope()
{
    return (B.y - A.y) / (B.x - A.x);
}

bool line2f::hasPoint(point2f p)
{
    float s = (p.y - A.y) / (p.x - A.x);
    if(compare(s,slope())==0)
        return true;
    else
        return false;
}

void line2f::set(point2f a, point2f b)
{
    A.set(a.x,a.y);
    B.set(b.x,a.y);
}
