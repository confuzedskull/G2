

class line2f
{
    public:
    point2f A;
    point2f B;
    point2f C;//the middle point
    point2f midpoint;

    void set(point2f a,point2f b)
    {
        A=a;
        B=b;
    }

    void calc_midpoint()
    {
        C.set((B.x-A.x)/2,(B.y-A.y)/2);
        midpoint=C;
    }

    bool hasPoint(point2f p)
    {
        if(distance(A,C)+distance(C,B)==distance(A,B))
        return true;
        else
        return false;
    }

    line2f()
    {
        calc_midpoint();
    }

    line2f(point2f a, point2f b)
    {
        set(a,b);
        calc_midpoint();
    }

};



class line3i
{
    public:
    point2i A;
    point2i B;
    point2i C;//the middle point
    point2i midpoint;

    void set(point2i a,point2i b)
    {
        A=a;
        B=b;
    }

    void calc_midpoint()
    {
        C.set((B.x-A.x)/2,(B.y-A.y)/2);
        midpoint=C;
    }

    bool hasPoint(point2i p)
    {
        if(distance(A,C)+distance(C,B)==distance(A,B))
        return true;
        else
        return false;
    }

    line3i()
    {
        calc_midpoint();
    }

    line3i(point2i a, point2i b)
    {
        set(a,b);
        calc_midpoint();
    }

};

