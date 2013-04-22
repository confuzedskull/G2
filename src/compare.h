int compare(double d1, double d2)
{
    if((d1*1000)<1000)//d1 is less than 1
    {
        d1*=1000;//d1 is no longer a decimal
    }
    if((d2*1000)<1000)
    {
        d2*=1000;
    }
    (int)d1;
    (int)d2;
    if(d1>d2)
        return 1;
    if(d1<d2)
        return -1;
    if(d1==d2)
        return 0;
}

int compare(float d1, float d2)
{
    if((d1*1000)<1000)//d1 is less than 1
    {
        d1*=1000;//d1 is no longer a decimal
    }
    if((d2*1000)<1000)
    {
        d2*=1000;
    }
    (int)d1;
    (int)d2;
    if(d1>d2)
        return 1;
    if(d1<d2)
        return -1;
    if(d1==d2)
        return 0;
}
