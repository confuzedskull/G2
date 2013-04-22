class point2f
{
    public:
    float x;
    float y;

    void set(float a, float b)
    {
        x=a;
        y=b;
    }

    point2f()
    {

    }

    ~point2f()
    {

    }

    point2f(float a, float b)
    {
        set(a,b);
    }
};

class point3f
{
    public:
    float x;
    float y;
    float z;

    void set(float a, float b, float c)
    {
        x=a;
        y=b;
        z=c;
    }

    point3f()
    {

    }

    ~point3f()
    {

    }

    point3f(float a, float b, float c)
    {
        set(a,b,c);
    }
};

class point2i
{
    public:
    int x;
    int y;

    void set(int a, int b)
    {
        x=a;
        y=b;
    }

    point2i()
    {

    }

    ~point2i()
    {

    }

    point2i(int a, int b)
    {
        set(a,b);
    }
};

