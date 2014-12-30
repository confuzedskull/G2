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

#ifndef CLICKABLE_H
#define CLICKABLE_H
#include "basic_object.h"

//A clickable object interacts with the cursor
class clickable_object: virtual public basic_object
{
protected:
    std::string click_sound;
    std::string hover_sound;
public:
    virtual void mouse_function();//performs a variety of actions dependent on cursor interaction
    bool highlighted();//checks if the object lies within the cursor selection box
    bool hovered_over();//checks if the cursor lies within the this object
    bool left_clicked();//checks if the cursor left clicked inside this object
    bool right_clicked();//checks if the cursor right clicked inside this object
    void enable();//allow the mouse function to work
    void disable();//stop running mouse function
    void highlight_function();//function to perform when object is highlighted
    void hover_function();//function to perform when object is hovered over
    void left_click_function();//function to perform when object is left clicked
    void right_click_function();//function to perform when object is right clicked
    void set_click_sound(std::string filename);//sets the sound to be made when clicked
    void set_hover_sound(std::string filename);//sets the sound to be made when hovered over
    void update() override;
    clickable_object();
};
#endif // CLICKABLE_H
