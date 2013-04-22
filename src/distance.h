float distance(float x1, float y1, float x2, float y2)//calculates distance given x,y values
{
    return (sqrt(pow((x2 - x1),2) + pow((y2 - y1),2)));
}

int distance(int x1, int y1, int x2, int y2)//calculates distance given x,y values
{
    return (sqrt(pow((x2 - x1),2) + pow((y2 - y1),2)));
}

float distance(point3f A, point3f B)//calculates distance from A to B
{
    return (sqrt(pow((B.x - A.x),2) + pow((B.y - A.y),2)));
}

int distance(point2i A, point2i B)//calculates distance from A to B
{
    return (int)(sqrt(pow((B.x - A.x),2) + pow((B.y - A.y),2)));
}

float distance(point2f A, point2f B)//calculates distance from A to B
{
    return (sqrt(pow((B.x - A.x),2) + pow((B.y - A.y),2)));
}

float distance(float x1, float y1, float z1, float x2, float y2, float z2)//calculates 3 dimensional distance
{
    return (sqrt(pow((x2 - x1),2) + pow((y2 - y1),2) + pow((z2 - z1),2)));
}
