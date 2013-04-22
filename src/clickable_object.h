#include <\Users\James\Dropbox\My Programs\C++\2dworld\src\physics_object.h>
#include <\Users\James\Dropbox\My Programs\C++\2dworld\src\cursor.h>

class clickable_object: public physics_object
{
    public:
    bool selected;


    bool left_clicked()
    {
        if(cursor1.left_click &&
           compare(cursor1.left_down.x,xmax)==-1 &&
           compare(cursor1.left_down.x,xmin)==1 &&
           compare(cursor1.left_down.y,ymax)==-1 &&
           compare(cursor1.left_down.y,ymin)==1)
        return true;
        else
        return false;
    }

    bool right_clicked()
    {
        if(compare(cursor1.right_up.x,xmax)==-1 &&
           compare(cursor1.right_up.x,xmin)==1 &&
           compare(cursor1.right_up.y,ymax)==-1 &&
           compare(cursor1.right_up.y,ymin)==1)
        return true;
        else
        return false;
    }

    bool highlighted()
    {//if object lies within selection box boundaries, return true
        if(compare(current.x,cursor1.xmax)==-1 &&
           compare(current.x,cursor1.xmin)==1 &&
           compare(current.y,cursor1.ymax)==1 &&
           compare(current.y,cursor1.ymin)==-1)
        return true;
        else
        return false;
    }

    void mouse_function()
    {
        if(left_clicked()==true && cursor1.left_click==true)//clicked this object
        {
            cursor1.objects_selected=1;
            cursor1.selected_object=number;
            cursor1.highlighted_objects[number]=true;

            }

        if(cursor1.left_click==true && cursor1.objects_selected>0 && cursor1.highlighted_objects[number]==false)//clicked another object
        {
            cursor1.highlighted_objects[number]=false;
        }

        if(cursor1.left_click==true && left_clicked()==false )
        {
            cursor1.highlighted_objects[number]=false;
            cursor1.objects_selected=0;
        }

        if(highlighted()==true)
        {

            cursor1.highlighted_objects[number]=true;
        }

        if(highlighted()==false && cursor1.highlighted_objects[number]==true)
        {
            if(left_clicked()==false && selected==false)
            cursor1.objects_selected++;

            cursor1.highlighted_objects[number]=true;
        }

        if(right_clicked()==true)
        {
            cursor1.rally.x=current.x;
            cursor1.rally.y=current.y;
        }

        selected=cursor1.highlighted_objects[number];

        if(selected==true)
        {
            if(cursor1.right_click==true && right_clicked()==false)
            {
                rally.x=cursor1.right_down.x;
                rally.y=cursor1.right_down.y;
            }
            if(cursor1.right_dragging==true && right_clicked()==false)
            {
                rally.x=cursor1.right_drag.x;
                rally.y=cursor1.right_drag.y;
            }
            current_color.set(GREEN);
        }
        else
        undo_color();
    }

    clickable_object()
    {
        name="clickable object";
        selected=false;
        printf("object %d: %s initialized\n", number, name);

    }

    ~clickable_object()
    {
        printf("object %d: %s distroyed\n", number, name);
    }
};
