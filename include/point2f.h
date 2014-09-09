#ifndef POINT2F_H
#define POINT2F_H

//A point2f is a 2D point that consists of two floating point values
class point2f
{
    public:
    float x;
    float y;
    void set(float a, float b);
    point2f();
    point2f(float a, float b);
};
#endif // POINT2F_H
