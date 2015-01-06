/*  This file is a part of G2 - The Generic 2D Game Engine
    Copyright (C) 2014  James Nakano

    G2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    G2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the rest of G2.  If not, see <http://www.gnu.org/licenses/>.*/

#ifndef INTERACTIVE_H
#define INTERACTIVE_H
#include "basic_object.h"

//An interactive object interfaces with the cursor
class interactive_object: virtual public basic_object
{
protected:
    std::string click_sound;
    std::string hover_sound;
public:
    virtual void mouse_function();//performs a variety of actions dependent on cursor interaction
    static bool enable_clicking;
    static bool enable_dragging;
    static bool enable_highlighting;
    static bool enable_hovering;
    bool click_detection;
    bool drag_detection;
    bool highlight_detection;
    bool hover_detection;
    bool highlighted();//checks if the object lies within the cursor selection box
    bool dragged();//checks if cursor is dragging inside object
    bool hovered_over();//checks if the cursor lies within the this object
    bool left_clicked();//checks if the cursor left clicked inside this object
    bool right_clicked();//checks if the cursor right clicked inside this object
    void highlight_function();//function to perform when object is highlighted
    void drag_function();//function to perform when object is grabbed
    void hover_function();//function to perform when object is hovered over
    void leftclick_function();//function to perform when object is left clicked
    void rightclick_function();//function to perform when object is right clicked
    void set_clicksound(std::string filename);//sets the sound to be made when clicked
    void set_hoversound(std::string filename);//sets the sound to be made when hovered over
    void update() override;
    void save() override;
    void load() override;
    interactive_object();
};
#endif // INTERACTIVE_H
