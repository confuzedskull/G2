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
        if(cursor1.right_click &&
           compare(cursor1.right_down.x,xmax)==-1 &&
           compare(cursor1.right_down.x,xmin)==1 &&
           compare(cursor1.right_down.y,ymax)==-1 &&
           compare(cursor1.right_down.y,ymin)==1)
        return true;
        else
        return false;
    }

    bool highlighted()
    {//if object lies within selection box boundaries, return true
        if(cursor1.highlighting &&
           compare(current.x,cursor1.xmax)==-1 &&
           compare(current.x,cursor1.xmin)==1 &&
           compare(current.y,cursor1.ymax)==1 &&
           compare(current.y,cursor1.ymin)==-1)
        return true;
        else
        return false;
    }

    void mouse_function()
    {
        if(left_clicked())//clicked this object
        {
            cursor1.objects_selected=1;
            cursor1.left_clicked_object=this;
            cursor1.selected_object=number;
            cursor1.highlighted_objects[number]=true;

        }

        if(cursor1.left_click && cursor1.objects_selected>0 && !cursor1.highlighted_objects[number])//clicked another object
        {
            cursor1.highlighted_objects[number]=false;
        }

        if(cursor1.left_click && !left_clicked())//clicked nothing
        {
            cursor1.highlighted_objects[number]=false;
            cursor1.objects_selected=0;
        }

        if(highlighted())
        {

            cursor1.highlighted_objects[number]=true;
        }

        if(!highlighted() && cursor1.highlighted_objects[number])
        {
            if(!left_clicked() && !selected)
            cursor1.objects_selected++;
            cursor1.highlighted_objects[number]=true;
        }

        if(right_clicked())
        {
            cursor1.right_clicked_object=this;
            cursor1.right_clicked_an_object=true;
        }

        selected=cursor1.highlighted_objects[number];

        if(selected)
        {
            if(cursor1.right_click && !right_clicked())
            {
                if(cursor1.right_clicked_an_object)
                {
                    rally = &cursor1.right_clicked_object->current;//used a reference because current is always changing
                }
                else
                {
                    delete &rally;
                    rally = new point2f(cursor1.right_down.x,cursor1.right_down.y);
                    //rally = &cursor1.right_down;
                }
                rally_set=true;
            }
            if(cursor1.right_dragging && !right_clicked())
            {
                rally = &cursor1.right_drag;
                rally_set=true;
            }
            //current_color.set(GREEN);
        }
        else
        {
            //undo_color();
        }
    }

    clickable_object()
    {
        name="clickable object";
        selected=false;
        std::clog<<"object#"<<number<<": "<<name<<" created."<<std::endl;
    }

    ~clickable_object()
    {

    }
};
