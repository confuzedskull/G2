/*  2DWorld - The Generic 2D Game Engine
    This is a multipurpose 2D game engine created from the ground up using OpenGL and GLUT
    Copyright (C) 2014  James Nakano

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include "game.h"
#include "cursor.h"
#include "distance.h"
#include "compare.h"
#include "object.h"
#include "physics_object.h"
#include "clickable_object.h"
#include "projectile.h"

bool* key_states = new bool[256]; //stores each on/off state of a keyboard key
//coordinates of program window
int window_x=100;
int window_y=100;
//width and height of program window
int window_width=640;
int window_height=320;
double frequency=0.01;//refresh rate in seconds
//text for information overlay
char text0[30];
char text1[30];
char text2[20];
char text3[20];
char text4[20];
char text5[20];
char text6[10];
char text7[10];
char text8[10];
char text9[10];
char text10[20];
char text11[20];
char text12[20];
bool temp_toggle=false;
bool toggle_text=false;
clickable_object* clickable_objects = new clickable_object[game::max_objects];
projectile bullet;
//This prints text of rgba color at x,y on the screen
void glutPrint(float x, float y, LPVOID font, char* text, float r, float g, float b, float a)
{
    if(!text || !strlen(text)) return;
    bool blending = false;
    if(glIsEnabled(GL_BLEND)) blending = true;
    glEnable(GL_BLEND);
    glColor4f(r,g,b,a);
    glRasterPos2f(x,y);
    while (*text)
    {
        glutBitmapCharacter(font, *text);
        text++;
    }
    if(!blending) glDisable(GL_BLEND);
}

void collision_detection()
{
    for(int a=0; a<game::max_objects; a++)
    {
        for(int b=0; b<game::max_objects; b++)
        {
            if(a!=b && clickable_objects[a].is_close(clickable_objects[b]))
            {
                clickable_objects[a].identify(clickable_objects[b]);
                clickable_objects[a].repel(clickable_objects[b]);
            }
        }
    }
}
//The only way to check if no objects are being clicked is by checking every object
void check_clicked()
{
    bool left_clicked = true;
    for(int a=0; a<game::max_objects; a++)
    {
        if(left_clicked && clickable_objects[a].left_clicked())
        {
            left_clicked=true;
        }
        else
        {
            left_clicked=false;
        }
    }
    cursor::left_clicked_an_object = left_clicked;
    bool right_clicked=true;
    for(int a=0; a<game::max_objects; a++)
    {
        if(right_clicked && clickable_objects[a].right_clicked())
            right_clicked=true;
        else
            right_clicked=false;
    }
    cursor::right_clicked_an_object = right_clicked;
    bool grabbed=true;
    for(int a=0; a<game::max_objects; a++)
    {
        if(grabbed && clickable_objects[a].grabbed())
            grabbed=true;
        else
            grabbed=false;
    }
    cursor::grabbed_an_object = grabbed;
}
//resize the window
void change_size(int w, int h)
{
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;
    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);
    // Reset Matrix
    glLoadIdentity();
    glOrtho(0.0,(GLdouble)w,0.0,(GLdouble)h, -1.0,1.0);
    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    window_width=w;//set the global window width
    window_height=h;//set the global window height
}

void mouse_click(int button, int state, int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        cursor::left_down.set(x,window_height-y);
        cursor::left_click=true;
    }

    if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        cursor::left_up.set(x,window_height-y);
        cursor::highlighting=false;
        cursor::left_click=false;
    }

    if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        cursor::highlighting=false;
        cursor::right_click=true;
        cursor::right_down.set(x,window_height-y);
    }

    if(button==GLUT_RIGHT_BUTTON && state==GLUT_UP)
    {
        cursor::highlighting=false;
        cursor::right_click=false;
        cursor::right_up.set(x,window_height-y);
        cursor::right_dragging=false;
    }
}

//This is called when user clicks and drags
void mouse_drag(int x, int y)
{
    if(cursor::left_click)
    {
        if(!cursor::left_clicked_an_object && !cursor::grabbed_an_object)
        {
            //this condition makes it so that the user has to make a rectangle larger than 10x10. That way, highlighting is less sensitive
            if(compare(x,cursor::left_down.x+10)==1 && compare((window_height - y),cursor::left_down.y+10)==-1)
                cursor::highlighting=true;
            else
                cursor::highlighting=false;
        }
        else
            cursor::highlighting=false;
        cursor::left_drag.set(x,(window_height-y));
        //see if drag point is different from start point
        if(compare(x,cursor::left_down.x)!=0 && compare((window_height - y),cursor::left_down.y)!=0)
            cursor::left_dragging=true;
        else
            cursor::left_dragging=false;
    }
    else
        cursor::left_dragging=false;

    if(cursor::right_click)
    {
        cursor::highlighting=false;
        cursor::right_drag.set(x,(window_height-y));
        //see if drag point is different from start point
        if(compare(x,cursor::right_down.x)!=0 && compare((window_height - y),cursor::right_down.y)!=0)
            cursor::right_dragging=true;
        else
            cursor::right_dragging=false;
    }
    else
        cursor::right_dragging=false;
}

void key_pressed(unsigned char key, int x, int y)
{
    key_states[key] = true; // Set the state of the current key to pressed
}

void key_up(unsigned char key, int x, int y)
{
    key_states[key] = false; // Set the state of the current key to not pressed
}

void key_operations(void)
{
    if(key_states['w'] || key_states['W'])
    clickable_objects[cursor::selected_object].move_forward(0.01);

    if(key_states['s'] || key_states['S'])
    clickable_objects[cursor::selected_object].move_back(0.01);

    if(key_states['a'] || key_states['A'])
    clickable_objects[cursor::selected_object].move_left(0.01);

    if(key_states['d'] || key_states['D'])
    clickable_objects[cursor::selected_object].move_right(0.01);

    if(key_states['q'] || key_states['Q'])
    clickable_objects[cursor::selected_object].turn_left(0.01);

    if(key_states['e'] || key_states['E'])
    clickable_objects[cursor::selected_object].turn_right(0.01);

    if(key_states['i'] || key_states['I'])
    {
        if(toggle_text)
            temp_toggle=false;
        else
            temp_toggle=true;
    }
    else
        toggle_text=temp_toggle;
// spacebar
    if(key_states[32] && !bullet.fired)
        bullet.fire(clickable_objects[cursor::selected_object]);
//escape
    if (key_states[27])
        exit(0);
}

void text()
{
    sprintf(text0,"object no.%i", clickable_objects[cursor::selected_object].number);
    glutPrint (window_width/40,window_height-20, GLUT_BITMAP_HELVETICA_12, text0, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text1,"coordinates=%.2f,%.2f", clickable_objects[cursor::selected_object].current.x,clickable_objects[cursor::selected_object].current.y);
    glutPrint (window_width/40,window_height-40, GLUT_BITMAP_HELVETICA_12, text1, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text2,"resting: %.2f, %.2f",clickable_objects[cursor::selected_object].rest.x,clickable_objects[cursor::selected_object].rest.y);
    glutPrint (window_width/40,window_height-60, GLUT_BITMAP_HELVETICA_12, text2, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text3,"velocity %.2f,%.2f",clickable_objects[cursor::selected_object].velocity[0].x,clickable_objects[cursor::selected_object].velocity[0].y);
    glutPrint (window_width/40,window_height-80, GLUT_BITMAP_HELVETICA_12, text3, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text4,"velocity2 %.2f,%.2f",clickable_objects[cursor::selected_object].velocity[1].x,clickable_objects[cursor::selected_object].velocity[1].y);
    glutPrint (window_width/40,window_height-100, GLUT_BITMAP_HELVETICA_12, text4, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text5,"delta_time x: %.2f y:%.2f",clickable_objects[cursor::selected_object].delta_time[0],clickable_objects[cursor::selected_object].delta_time[1]);
    glutPrint (window_width/40,window_height-120, GLUT_BITMAP_HELVETICA_12, text5, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text6,"momentum: %.2f %.2f",clickable_objects[cursor::selected_object].momentum.x,clickable_objects[cursor::selected_object].momentum.y);
    glutPrint (window_width/40,window_height-140, GLUT_BITMAP_HELVETICA_12, text6, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text7,"force: %.2f %.2f",clickable_objects[cursor::selected_object].force.x,clickable_objects[cursor::selected_object].force.y);
    glutPrint (window_width/40,window_height-160, GLUT_BITMAP_HELVETICA_12, text7, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text8,"acceleration: %.2f %.2f",clickable_objects[cursor::selected_object].acceleration.x,clickable_objects[cursor::selected_object].acceleration.y);
    glutPrint (window_width/40,window_height-180, GLUT_BITMAP_HELVETICA_12, text8, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text9,"delta_time velocity: %.2f %.2f",clickable_objects[cursor::selected_object].delta_time[2],clickable_objects[cursor::selected_object].delta_time[3]);
    glutPrint (window_width/40,window_height-200, GLUT_BITMAP_HELVETICA_12, text9, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text10,"touching object no. L:%d R:%d T:%d B:%d",clickable_objects[cursor::selected_object].touching[0], clickable_objects[cursor::selected_object].touching[1], clickable_objects[cursor::selected_object].touching[2],clickable_objects[cursor::selected_object].touching[3]);
    glutPrint (window_width/40,window_height-220, GLUT_BITMAP_HELVETICA_12, text10, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text11,"game time: %.2f",game::time);
    glutPrint (window_width/40,window_height-240, GLUT_BITMAP_HELVETICA_12, text11, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text12,"click:%.2f,%.2f",cursor::left_down.x,cursor::left_down.y);
    glutPrint (window_width/40,window_height-260, GLUT_BITMAP_HELVETICA_12, text12, 1.0f,0.0f,0.0f, 0.5f);
}

void init_objects()
{
//initialize the clickable_objects

    //first object (yes first, because the index starts at 0) from clickable_objects array
    clickable_objects[0].name="small square";
    clickable_objects[0].primary_color.set(0.5,0.5,0.5);
    clickable_objects[0].current.set(272,208);
    clickable_objects[0].width=32;
    clickable_objects[0].height=32;
    clickable_objects[0].set_boundaries();
    clickable_objects[0].add_action(2,96);
    clickable_objects[0].add_action(4,96);
    clickable_objects[0].add_action(1,96);
    clickable_objects[0].add_action(3,96);
    clickable_objects[0].add_action(5,90);
    clickable_objects[0].add_action(6,90);
    std::clog<<"object#"<<clickable_objects[0].number<<": "<<clickable_objects[0].name<<" initialized."<<std::endl;

    //second object from clickable objects array
    clickable_objects[1].name="black square";
    clickable_objects[1].primary_color.set(BLACK);
    clickable_objects[1].set_boundaries();
    std::clog<<"object#"<<clickable_objects[1].number<<": "<<clickable_objects[1].name<<" initialized."<<std::endl;

    //third object from clickable_objects array
    clickable_objects[2].name="yellow square";
    clickable_objects[2].primary_color.set(YELLOW);
    clickable_objects[2].current.set(416.0,160.0);
    clickable_objects[2].set_boundaries();
    std::clog<<"object#"<<clickable_objects[2].number<<": "<<clickable_objects[2].name<<" initialized."<<std::endl;

    //fourth object from clickable_objects array
    clickable_objects[3].name="green square";
    clickable_objects[3].primary_color.set(GREEN);
    clickable_objects[3].current.set(320.0,64);
    clickable_objects[3].set_boundaries();
    std::clog<<"object#"<<clickable_objects[3].number<<": "<<clickable_objects[3].name<<" initialized."<<std::endl;

    //fifth object from clickable_objects array
    clickable_objects[4].name="red square";
    clickable_objects[4].primary_color.set(RED);
    clickable_objects[4].current.set(320,256);
    clickable_objects[4].set_boundaries();
    std::clog<<"object#"<<clickable_objects[4].number<<": "<<clickable_objects[4].name<<" initialized."<<std::endl;

    //sixth object from clickable_objects array
    clickable_objects[5].name="blue square";
    clickable_objects[5].primary_color.set(BLUE);
    clickable_objects[5].current.set(224,160);
    clickable_objects[5].width=64;
    clickable_objects[5].height=64;
    clickable_objects[5].set_boundaries();
    std::clog<<"object#"<<clickable_objects[5].number<<": "<<clickable_objects[5].name<<" initialized."<<std::endl;
}

void render_scene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);// Clear Color Buffers
//render the projectiles
    bullet.render();
//render the clickable_objects
//NOTE: clickable_objects are rendered ontop of eachother according to the order in which they are rendered
//BOTTOM
    clickable_objects[5].render();
    clickable_objects[4].render();
    clickable_objects[3].render();
    clickable_objects[2].render();
    clickable_objects[1].render();
    clickable_objects[0].render();
//render the selection box
    cursor::selection_box();
//TOP
    if(toggle_text)
    text();
    glFlush();
}

void update_scene()
{
    key_operations();//keyboard controls
    cursor::set_boundaries();//calculate the size of the selection box
    game::time_elapsed = ((float)clock()-game::time_started)/CLOCKS_PER_SEC;//update the start time
    //calculate the physics for all clickable_objects
    clickable_objects[0].physics();
    clickable_objects[1].physics();
    clickable_objects[2].physics();
    clickable_objects[3].physics();
    clickable_objects[4].physics();
    clickable_objects[5].physics();
    bullet.physics();
    collision_detection();
    check_clicked();
//mouse interactivity
    clickable_objects[0].mouse_function();
    clickable_objects[1].mouse_function();
    clickable_objects[2].mouse_function();
    clickable_objects[3].mouse_function();
    clickable_objects[4].mouse_function();
    clickable_objects[5].mouse_function();
//This function acts like timer so that events occur at the set frequency
    if(compare(game::time_elapsed,frequency)==1)//time elapsed is > frequency
    {
        game::time_started=clock();//reset the start time
        game::time+=frequency;//increment the game clock
        //move bullet
        bullet.update();
        //move clickable_objects
        clickable_objects[0].perform_actions();//scripted movement
        clickable_objects[1].move_to_point(clickable_objects[1].rally->x,clickable_objects[1].rally->y, 1);
        clickable_objects[2].move_to_point(clickable_objects[2].rally->x,clickable_objects[2].rally->y, 1);
        clickable_objects[3].move_to_point(clickable_objects[3].rally->x,clickable_objects[3].rally->y, 1);
        clickable_objects[4].move_to_point(clickable_objects[4].rally->x,clickable_objects[4].rally->y, 1);
        clickable_objects[5].move_to_point(clickable_objects[5].rally->x,clickable_objects[5].rally->y, 1);
        glutPostRedisplay();//update the scene
    }
}

void initializeWindow()
{
    glClearColor (1.0, 1.0, 1.0, 1.0);//white background
    glViewport(0,0,window_width,window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLdouble) window_width , 0.0, (GLdouble) window_height , -1.0, 1.0);
    glClearColor (1.0, 1.0, 1.0, 1.0);//white background
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char **argv)
{
    std::clog<<"entering main...\n";
    /* initialize random seed: */
    srand (time(NULL));
    //initialize objects
    std::clog<<"initializing objects...\n";
    init_objects();
    // initialize GLUT and create window
    std::clog<<"initializing GLUT...\n";
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
    std::clog<<"creating window...\n";
    glutInitWindowPosition(window_x,window_y);
    std::clog<<"window position: "<< window_x<< ","<< window_y<<std::endl;
    glutInitWindowSize(window_width,window_height);
    std::clog<<"window size: "<<window_width<<"X"<< window_height<<std::endl;
    glutCreateWindow("2D World");
    initializeWindow();
    glutReshapeFunc(change_size);
    glutIdleFunc(update_scene); //use this for animations
    glutKeyboardFunc(key_pressed); // Tell GLUT to use the method "keyPressed" for key presses
    glutKeyboardUpFunc(key_up); // Tell GLUT to use the method "keyUp" for key releases
    glutMouseFunc(mouse_click);
    glutMotionFunc(mouse_drag);
    glutDisplayFunc(render_scene);
    std::clog<<"rendering...\n";
    glutMainLoop();
}
