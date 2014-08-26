#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "game.h"
#include "cursor.h"
#include "distance.h"
#include "compare.h"
#include "object.h"
#include "physics_object.h"
#include "clickable_object.h"
#include "projectile.h"

//2D World
//by James Nakano

//This is a basic 2D game engine created from the ground up using openGL and glut
//Disclaimer: The glut and opengl libraries are obviously not mine, but everything else is an original creation.
//
// object.total_objects=0;//initial object number. This gets incremented and assigned to object.number after each object is created.
const int left=1;
const int right=2;
const int up=3;
const int down=4;
GLfloat size=3.0;
bool* key_states = new bool[256]; // Create an array of boolean values of letters

//coordinates of program window
int window_x=100;
int window_y=100;
//width and height of program window
int window_width=640;
int window_height=320;
double frequency=0.01;//refresh rate in seconds
int random1 = rand() % 4 + 1;//random number between 1 and 4
int random2 = rand() % 4 + 1;//another random number between 1 and 4

int frames=0;//to be used for frame count

//text for HUD
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
char text11[15];
char text12[15];
int temp_toggle[2];
int toggle_text=1;
double world_gravity=-0.01;
clickable_object* clickable_objects = new clickable_object[game::max_objects];
projectile bullet;

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
        {
            right_clicked=true;
        }
        else
        {
            right_clicked=false;
        }
    }
    cursor::right_clicked_an_object = right_clicked;
}

void change_size(int w, int h)
{

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;
    float ratio =  w * 1.0 / h;

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

    // Set the correct perspective.
    //gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    window_width=w;
    window_height=h;
}

void mouse_click( int button, int state, int x, int y )
{
    if ( button==GLUT_LEFT_BUTTON && state==GLUT_DOWN )
    {
        cursor::left_down.x=x;
        cursor::left_down.y=window_height-y;
        cursor::left_click=true;
    }

    if ( button==GLUT_LEFT_BUTTON && state==GLUT_UP )
    {
        cursor::left_up.x=x;
        cursor::left_up.y=window_height-y;
        cursor::highlighting=false;
        cursor::left_click=false;

    }

    if ( button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN )
    {
        cursor::highlighting=false;
        cursor::right_click=true;
        cursor::right_down.x=x;
        cursor::right_down.y=window_height-y;
        cursor::right_dragging=false;

    }

    if ( button==GLUT_RIGHT_BUTTON && state==GLUT_UP )
    {
        cursor::highlighting=false;
        cursor::right_click=false;
        cursor::right_up.x=x;
        cursor::right_up.y=window_height-y;
    }
}

//This is called when user clicks and drags
void mouse_drag(int x, int y)
{
    if(cursor::left_click)
    {
        //this condition makes it so that the user has to make a rectangle larger than 10x10. That way, highlighting is less sensitive
        if(!cursor::left_clicked_an_object && compare(x,cursor::left_down.x+10)==1 && compare((window_height - y),cursor::left_down.y+10)==-1)
        cursor::highlighting=true;
        else
            cursor::highlighting=false;
        cursor::left_drag.x=x;
        cursor::left_drag.y=(window_height-y);
        //see if drag point is different from start point
        if(compare(x,cursor::left_down.x)!=0 && compare((window_height - y),cursor::left_down.y)!=0)//drag point is different from start point
            cursor::left_dragging=true;
        else
            cursor::left_dragging=false;
    }
    else
        cursor::left_dragging=false;

    if(cursor::right_click)
    {
        cursor::highlighting=false;
        cursor::right_drag.x=x;
        cursor::right_drag.y=(window_height-y);
        //see if drag point is different from start point
        if(compare(x,cursor::right_down.x)!=0 && compare((window_height - y),cursor::right_down.y)!=0)
            cursor::right_dragging=true;
        else
            cursor::right_dragging=false;
    }
        else
            cursor::right_dragging=false;
}

void key_pressed (unsigned char key, int x, int y)
{
    key_states[key] = true; // Set the state of the current key to pressed
}

void key_up (unsigned char key, int x, int y)
{
    key_states[key] = false; // Set the state of the current key to not pressed
}

void key_operations (void)
{
    if (key_states['w'] || key_states['W'])
    {
        clickable_objects[cursor::selected_object].move_forward(0.01);
    }

    if (key_states['s'] || key_states['S'])
    {
        clickable_objects[cursor::selected_object].move_back(0.01);
    }

    if (key_states['a'] || key_states['A'])
    {
        clickable_objects[cursor::selected_object].move_left(0.01);
    }

    if (key_states['d'] || key_states['D'])
    {
        clickable_objects[cursor::selected_object].move_right(0.01);
    }

    if (key_states['q'] || key_states['Q'])
    {
        clickable_objects[cursor::selected_object].turn_left(0.01);
    }

    if (key_states['e'] || key_states['E'])
    {
        clickable_objects[cursor::selected_object].turn_right(0.01);
    }

    if (key_states['i'] || key_states['I'])
    {
        if(toggle_text==1)
            temp_toggle[1]=0;

        if(toggle_text==0)
            temp_toggle[1]=1;

    }
    else
        toggle_text=temp_toggle[1];

// spacebar
    if (key_states[32])
    {
        bullet.fire(clickable_objects[cursor::selected_object]);
    }

//escape
    if (key_states[27])
        exit(0);
}

void text()
{

    sprintf(text0,"object no.%i", clickable_objects[cursor::selected_object].number);
    glutPrint (window_width/40,window_height -20, GLUT_BITMAP_HELVETICA_12, text0, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text1,"coordinates=%.2f,%.2f", clickable_objects[cursor::selected_object].current.x,clickable_objects[cursor::selected_object].current.y);
    glutPrint (window_width/40,window_height-40, GLUT_BITMAP_HELVETICA_12, text1, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text2,"resting: %.2f, %.2f",clickable_objects[cursor::selected_object].rest.x,clickable_objects[cursor::selected_object].rest.y);
    glutPrint (window_width/40,window_height -60, GLUT_BITMAP_HELVETICA_12, text2, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text3,"velocity %.2f,%.2f",clickable_objects[cursor::selected_object].velocity[1].x,clickable_objects[cursor::selected_object].velocity[1].y);
    glutPrint (window_width/40,window_height -80, GLUT_BITMAP_HELVETICA_12, text3, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text4,"velocity2 %.2f,%.2f",clickable_objects[cursor::selected_object].velocity[2].x,clickable_objects[cursor::selected_object].velocity[2].y);
    glutPrint (window_width/40,window_height -100, GLUT_BITMAP_HELVETICA_12, text4, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text5,"delta_time x: %.2f y:%.2f",clickable_objects[cursor::selected_object].delta_time[1],clickable_objects[cursor::selected_object].delta_time[2]);
    glutPrint (window_width/40,window_height -120, GLUT_BITMAP_HELVETICA_12, text5, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text6,"momentum: %.2f %.2f",clickable_objects[cursor::selected_object].momentum.x,clickable_objects[cursor::selected_object].momentum.y);
    glutPrint (window_width/40,window_height -140, GLUT_BITMAP_HELVETICA_12, text6, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text7,"force: %.2f %.2f",clickable_objects[cursor::selected_object].force.x,clickable_objects[cursor::selected_object].force.y);
    glutPrint (window_width/40,window_height -160, GLUT_BITMAP_HELVETICA_12, text7, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text8,"acceleration: %.2f %.2f",clickable_objects[cursor::selected_object].acceleration.x,clickable_objects[cursor::selected_object].acceleration.y);
    glutPrint (window_width/40,window_height-180, GLUT_BITMAP_HELVETICA_12, text8, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text9,"delta_time velocity: %.2f %.2f",clickable_objects[cursor::selected_object].delta_time[3],clickable_objects[cursor::selected_object].delta_time[4]);
    glutPrint (window_width/40,window_height-200, GLUT_BITMAP_HELVETICA_12, text9, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text10,"touching object no. L:%d R:%d T:%d B:%d",clickable_objects[cursor::selected_object].touching[left], clickable_objects[cursor::selected_object].touching[right], clickable_objects[cursor::selected_object].touching[up],clickable_objects[cursor::selected_object].touching[down]);
    glutPrint (window_width/40,window_height-220, GLUT_BITMAP_HELVETICA_12, text10, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text11,"game time: %.2f",game::time);
    glutPrint (window_width/40,window_height-240, GLUT_BITMAP_HELVETICA_12, text11, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text12,"click:%.2f,%.2f",cursor::left_down.x,cursor::left_down.y);
    glutPrint (window_width/40,window_height-260, GLUT_BITMAP_HELVETICA_12, text12, 1.0f,0.0f,0.0f, 0.5f);
}

void init_objects()
{
    //initialize the clickable_objects

    //first object from clickable_objects array (player)
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

    clickable_objects[1].name="black square";
    clickable_objects[1].primary_color.set(BLACK);
    clickable_objects[1].set_boundaries();
    std::clog<<"object#"<<clickable_objects[1].number<<": "<<clickable_objects[1].name<<" initialized."<<std::endl;


    //clickable_objects[1].rotation=90;

    //second object from clickable_objects array
    clickable_objects[2].name="yellow square";
    clickable_objects[2].primary_color.set(YELLOW);
    clickable_objects[2].current.set(416.0,160.0);
    clickable_objects[2].set_boundaries();
    std::clog<<"object#"<<clickable_objects[2].number<<": "<<clickable_objects[2].name<<" initialized."<<std::endl;

    //third object from clickable_objects array
    clickable_objects[3].name="green square";
    clickable_objects[3].primary_color.set(GREEN);
    clickable_objects[3].current.set(320.0,64);
    clickable_objects[3].set_boundaries();
    std::clog<<"object#"<<clickable_objects[3].number<<": "<<clickable_objects[3].name<<" initialized."<<std::endl;

    //fourth object from clickable_objects array
    clickable_objects[4].name="red square";
    clickable_objects[4].primary_color.set(RED);
    clickable_objects[4].current.set(320,256);
    clickable_objects[4].set_boundaries();
    std::clog<<"object#"<<clickable_objects[4].number<<": "<<clickable_objects[4].name<<" initialized."<<std::endl;


    //fifth object from clickable_objects array
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
    // Clear Color Buffers
    glClear(GL_COLOR_BUFFER_BIT);
    cursor::selection_box();
//render the clickable_objects
//NOTE: clickable_objects are rendered ontop of eachother according to order rendered below (bottom first)

    clickable_objects[5].render();
    clickable_objects[4].render();
    clickable_objects[3].render();
    clickable_objects[2].render();
    clickable_objects[1].render();
    clickable_objects[0].render();
    bullet.render();

    if(toggle_text==1)
    {
        text();
    }

    glFlush();
}

void update_scene()
{
    key_operations();
    cursor::set_boundaries();
    game::time_elapsed = ((float)clock()-game::time_started)/CLOCKS_PER_SEC;//update the start time
    game::time = ((float)clock()-game::time_started)/CLOCKS_PER_SEC;
    //calculate the physics for all clickable_objects
    clickable_objects[0].physics();
    clickable_objects[1].physics();
    clickable_objects[2].physics();
    clickable_objects[3].physics();
    clickable_objects[4].physics();
    clickable_objects[5].physics();
    bullet.update();
    check_clicked();
    collision_detection();//calculate object collision

//mouse interactivity
    clickable_objects[0].mouse_function();
    clickable_objects[1].mouse_function();
    clickable_objects[2].mouse_function();
    clickable_objects[3].mouse_function();
    clickable_objects[4].mouse_function();
    clickable_objects[5].mouse_function();

    if(compare(game::time_elapsed,frequency)==1)//time elapsed is > frequency
    {
        game::time_started=clock();//reset the start time
        //move clickable_objects
        clickable_objects[0].perform_actions();
        clickable_objects[1].move_to_point(clickable_objects[1].rally->x,clickable_objects[1].rally->y, 1);
        clickable_objects[2].move_to_point(clickable_objects[2].rally->x,clickable_objects[2].rally->y, 1);
        clickable_objects[3].move_to_point(clickable_objects[3].rally->x,clickable_objects[3].rally->y, 1);
        clickable_objects[4].move_to_point(clickable_objects[4].rally->x,clickable_objects[4].rally->y, 1);
        clickable_objects[5].move_to_point(clickable_objects[5].rally->x,clickable_objects[5].rally->y, 1);
        glutPostRedisplay();
    }
}

void initializeWindow()
{
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glViewport(0,0,window_width,window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLdouble) window_width , 0.0, (GLdouble) window_height , -1.0, 1.0);
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char **argv)
{
    std::clog<<"entering main...\n";
    /* initialize random seed: */
    srand ( time(NULL) );
    //initialize players
    std::clog<<"initializing objects...\n";
    init_objects();

    // init GLUT and create window
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
    //  glutPassiveMotionFunc(mouseMovement);
    // enter GLUT event processing cycle
    glutDisplayFunc(render_scene);
    std::clog<<"rendering...\n";

    glutMainLoop();

}
