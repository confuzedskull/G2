/*  This file is a part of 2DWorld - The Generic 2D Game Engine
    Copyright (C) 2014  James Nakano

    2DWorld is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    2DWorld is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the rest of 2DWorld.  If not, see <http://www.gnu.org/licenses/>.*/

int compare(double d1, double d2)
{
    if((d1*1000000)<1000000)//d1 is less than 1
    {
        d1*=1000000;//d1 is no longer a decimal
    }
    if((d2*1000000)<1000000)
    {
        d2*=1000000;
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
    if((d1*1000000)<1000000)//d1 is less than 1
    {
        d1*=1000000;//d1 is no longer a decimal
    }
    if((d2*1000000)<1000000)
    {
        d2*=1000000;
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
