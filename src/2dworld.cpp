#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <windows.h>
#include <math.h>
#include <string>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
clock_t game_start;
double game_time;
float get_game_time()
{
    return ((float)clock()-game_start)/CLOCKS_PER_SEC;
}
#include <\Users\James\Dropbox\My Programs\C++\2dworld\src\compare.h>
#include <\Users\James\Dropbox\My Programs\C++\headers\glutPrint.h>
#include <\Users\James\Dropbox\My Programs\C++\2dworld\src\player.h>
#include <\Users\James\Dropbox\My Programs\C++\2dworld\src\projectile.h>
#include <\Users\James\Dropbox\My Programs\C++\2dworld\src\world.h>

//2D World
//by James Nakano

//This is a basic 2D game engine created from the ground up using openGL and glut
//Disclaimer: The glut and opengl libraries are obviously not mine, but everything else is an original creation.
//

//global definitions
//direction definitions - I used this to make directions less confusing when reading code
const int left=1;
const int right=2;
const int up=3;
const int down=4;
GLfloat size=3.0;
int current_object = 1;
const int max_projectiles =2;
bool* key_states = new bool[256]; // Create an array of boolean values of letters

//coordinates of program window
int window_x=100;
int window_y=100;
//width and height of program window
int window_width=640;
int window_height=320;
double frequency=0.01;//refresh rate in seconds
clock_t time_started;
double time_elapsed;
int random1 = rand() % 4 + 1;//random number between 1 and 4
int random2 = rand() % 4 + 1;//another random number between 1 and 4

int frames=0;//to be used for frame count

//text
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
char text11[10];
char text12[10];

int temp_toggle[2];
int toggle_text=1;

//cursor cursor1;

world current_world;

double world_gravity=-0.01;

player* objects = new player[max_objects];

projectile bullet;

object* projectiles = new projectile[max_projectiles];

void collision_detection()
{
    for(int a=0; a<max_objects; a++)
    {
        for(int b=0; b<max_objects; b++)
        {
            if(a!=b && objects[a].is_close(objects[b]))
                {
                    objects[a].simon_says(objects[b]);
                }
        }
    }
};
player B;

void change_size(int w, int h) {

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
	    cursor1.left_down.x=x;
	    cursor1.left_down.y=window_height-y;
	    cursor1.left_click=true;
	}

    if ( button==GLUT_LEFT_BUTTON && state==GLUT_UP )
	{
        cursor1.left_up.x=x;
        cursor1.left_up.y=window_height-y;
        cursor1.highlighting=false;
        cursor1.left_click=false;

	}

	if ( button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN )
	{
	    cursor1.highlighting=false;
	    cursor1.right_click=true;
        cursor1.right_down.x=x;
        cursor1.right_down.y=window_height-y;
        cursor1.right_dragging=false;

    }

    if ( button==GLUT_RIGHT_BUTTON && state==GLUT_UP )
	{
	    cursor1.highlighting=false;
	    cursor1.right_click=false;
        cursor1.right_up.x=x;
        cursor1.right_up.y=window_height-y;

    }

}

//This is called when user clicks and drags
void mouse_drag(int x, int y)
{
    if(x>cursor1.left_down.x+10 && (window_height - y)<cursor1.left_down.y+10 && cursor1.left_click==true)
    {
        cursor1.highlighting=true;
        cursor1.left_drag.x=x;
        cursor1.left_drag.y=window_height-y;
        cursor1.right_dragging=false;

    }
    else
    {
        cursor1.highlighting=false;
        cursor1.right_drag.x=x;
        cursor1.right_drag.y=window_height-y;
        cursor1.right_dragging=true;

    }
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

if(key_states['w'] || key_states['W'] || key_states['s'] || key_states['S'])
{
    objects[current_object].moving_vertical=true;
}
else
    objects[current_object].moving_vertical=false;

if(key_states['a'] || key_states['A'] || key_states['d'] || key_states['D'])
{
    objects[current_object].moving_horizontal=true;
}
else
    objects[current_object].moving_horizontal=false;

if (key_states['w'] || key_states['W'])
    {
        objects[current_object].current.y+=objects[current_object].step[up].y;
        objects[current_object].current.x+=objects[current_object].step[up].x;
        //objects[current_object].move_forward(1);
        objects[current_object].action[up]=true;
    }

if (key_states['s'] || key_states['S'])
    {
        objects[current_object].current.x+=objects[current_object].step[down].x;
        objects[current_object].current.y+=objects[current_object].step[down].y;
        //objects[current_object].move_back(1);
        objects[current_object].action[down]=true;
    }

if (key_states['a'] || key_states['A'])
    {
        objects[current_object].current.x+=objects[current_object].step[left].x;
        objects[current_object].current.y+=objects[current_object].step[left].y;
        //objects[current_object].move_left(1);
        objects[current_object].action[left]=true;
    }

if (key_states['d'] || key_states['D'])
    {
        objects[current_object].current.x+=objects[current_object].step[right].x;
        objects[current_object].current.y+=objects[current_object].step[right].y;
        //objects[current_object].move_right(1);
        objects[current_object].action[right]=true;
    }

if (key_states['q'] || key_states['Q'])
    {
        objects[current_object].rotation+=objects[current_object].step_size;
    }

if (key_states['e'] || key_states['E'])
    {
        objects[current_object].rotation-=objects[current_object].step_size;
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
        objects[current_object].action[8]=true;
        bullet.fire(objects[current_object]);
    }
    else
    {
        objects[current_object].action[8]=false;

    }

//escape
if (key_states[27])
		exit(0);
}

void text ()
{

    sprintf(text0,"object no.%i", objects[current_object].number);
    glutPrint (window_width/40,window_height -20, GLUT_BITMAP_HELVETICA_12, text0, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text1,"coordinates=%.3f,%.3f", objects[current_object].current.x,objects[current_object].current.y);
    glutPrint (window_width/40,window_height-40, GLUT_BITMAP_HELVETICA_12, text1, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text2,"velocity %.3f,%.3f",objects[current_object].velocity[1].x,objects[current_object].velocity[1].y);
    glutPrint (window_width/40,window_height -60, GLUT_BITMAP_HELVETICA_12, text2, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text3,"velocity2 %.3f,%.3f",objects[current_object].velocity[2].x,objects[current_object].velocity[2].y);
    glutPrint (window_width/40,window_height -80, GLUT_BITMAP_HELVETICA_12, text3, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text4,"resting: %.3f, %.3f",objects[current_object].resting.x,objects[current_object].resting.y);
    glutPrint (window_width/40,window_height -100, GLUT_BITMAP_HELVETICA_12, text4, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text5,"delta_time x: %.3f y:%.3f",objects[current_object].delta_time[1],objects[current_object].delta_time[2]);
    glutPrint (window_width/40,window_height -120, GLUT_BITMAP_HELVETICA_12, text5, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text6,"momentum: %.3f %.3f",objects[current_object].momentum.x,objects[current_object].momentum.y);
    glutPrint (window_width/40,window_height -140, GLUT_BITMAP_HELVETICA_12, text6, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text7,"Force: %.3f %.3f",objects[current_object].force.x,objects[current_object].force.y);
    glutPrint (window_width/40,window_height -160, GLUT_BITMAP_HELVETICA_12, text7, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text8,"acceleration: %.3f %.3f",objects[current_object].acceleration.x,objects[current_object].acceleration.y);
    glutPrint (window_width/40,window_height-180, GLUT_BITMAP_HELVETICA_12, text8, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text9,"delta_time velocity: %.3f %.3f",objects[current_object].delta_time[3],objects[current_object].delta_time[4]);
    glutPrint (window_width/40,window_height-200, GLUT_BITMAP_HELVETICA_12, text9, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text10,"touching object no. L:%d R:%d T:%d B:%d",objects[current_object].touching[left], objects[current_object].touching[right], objects[current_object].touching[up],objects[current_object].touching[down]);
    glutPrint (window_width/40,window_height-220, GLUT_BITMAP_HELVETICA_12, text10, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text11,"game time: %.3f",game_time);
    glutPrint (window_width/40,window_height-240, GLUT_BITMAP_HELVETICA_12, text11, 1.0f,0.0f,0.0f, 0.5f);

    sprintf(text12,"front:%.2f,%.2f",objects[current_object].front.x,objects[current_object].front.y);
    glutPrint (window_width/40,window_height-260, GLUT_BITMAP_HELVETICA_12, text12, 1.0f,0.0f,0.0f, 0.5f);
}

void init_objects()
{
    //initialize the objects

    // object B -the control group
    B.name="control object";
    B.current_color.set(GREEN);
    B.current.set(200.0,160.0);
    printf("object %d: %s initialized\n",B.number, B.name);

    //first object from objects array (player)

    objects[0].name="small square";
    objects[0].current_color.set(RED);
    objects[0].current.set(200,100);
    objects[0].width=32;
    objects[0].height=32;
    objects[0].set_boundaries();
    printf("object %d: %s initialized\n",objects[0].number, objects[0].name);

    objects[1].name="player 1";
    objects[1].current_color.set(BLUE);
    objects[1].step_size=0.001;
    objects[1].set_boundaries();
    printf("object %d: %s initialized\n",objects[1].number, objects[1].name);


    //objects[1].rotation=90;

    //second object from objects array
    objects[2].name="red square";
    objects[2].current_color.set(RED);
    objects[2].current.set(400.0,160.0);
    objects[2].rally.x=objects[2].current.x;
    objects[2].rally.y=objects[2].current.y;
    printf("object %d: %s initialized\n",objects[2].number, objects[2].name);

    //third object from objects array
    objects[3].name="grey square";
    objects[3].current_color.set(0.5,0.5,0.5);
    objects[3].current.set(320.0,60);
    objects[3].rally.x=objects[3].current.x;
    objects[3].rally.y=objects[3].current.y;
    printf("object %d: %s initialized\n",objects[3].number, objects[3].name);

    //fourth object from objects array
    objects[4].name="black square";
    objects[4].current_color.set(BLACK);
    objects[4].current.set(320,260);
    objects[4].rally.x=objects[4].current.x;
    objects[4].rally.y=objects[4].current.y;
    printf("object %d: %s initialized\n",objects[4].number, objects[4].name);


    //fifth object from objects array
    objects[5].name="big cyan square";
    objects[5].current_color.set(0.0,1.0,1.0);
    objects[5].current.set(200,260);
    objects[5].width=64;
    objects[5].height=64;
    objects[5].step_size=0.001;
    objects[5].set_boundaries();
    objects[5].rally.x=objects[5].current.x;
    objects[5].rally.y=objects[5].current.y;
    printf("object %d: %s initialized\n",objects[5].number, objects[5].name);
}

void render_scene(void) {
	// Clear Color Buffers
	glClear(GL_COLOR_BUFFER_BIT);

	cursor1.set_boundaries();
    cursor1.selection_box();
    glTranslatef(0.0,0.0,0.0);
//render the objects
//NOTE: objects are rendered ontop of eachother according to order rendered below (bottom first)

    objects[5].render();
    objects[4].render();
    objects[3].render();
    objects[2].render();
    B.render();
    bullet.render();
    objects[1].render();
    objects[0].render();

    if(toggle_text==1)
    {
        text();
    }

	glFlush();
}

void update_scene()
{
    key_operations();
    time_elapsed = ((float)clock()-time_started)/CLOCKS_PER_SEC;//update the start time
    game_time = ((float)clock()-game_start)/CLOCKS_PER_SEC;
    //calculate the physics for all objects
   objects[0].physics();
    objects[1].physics();
    objects[2].physics();
    objects[3].physics();
    objects[4].physics();
    objects[5].physics();

    collision_detection();//calculate object collision

    //move objects
/*
    objects[1].move_to_point(objects[1].rally.x,objects[1].rally.y, 9);
    objects[2].move_to_point(objects[2].rally.x,objects[2].rally.y, 8);
    objects[3].move_to_point(objects[3].rally.x,objects[3].rally.y, 7);
    objects[4].move_to_point(objects[4].rally.x,objects[4].rally.y, 6);
    objects[5].move_to_point(objects[5].rally.x,objects[5].rally.y, 5);*/
//mouse interactivity
   objects[1].mouse_function();
    objects[2].mouse_function();
    objects[3].mouse_function();
    objects[4].mouse_function();
    objects[5].mouse_function();

    if(compare(time_elapsed,frequency)==1)//time elapsed is > frequency
    {
        time_started=clock();//reset the start time
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

int main(int argc, char **argv) {
    printf("entering main...\n");
    /* initialize random seed: */
    srand ( time(NULL) );
    //initialize objects
    printf("initializing objects...\n");
    init_objects();

	// init GLUT and create window
	printf("initializing GLUT...\n");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
	printf("creating window...\n");
	glutInitWindowPosition(window_x,window_y);
	printf("window position: %d, %d\n", window_x, window_y);
	glutInitWindowSize(window_width,window_height);
	printf("window size: %dX%d\n", window_width, window_height);
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
	printf("rendering...\n");

	glutMainLoop();

}
