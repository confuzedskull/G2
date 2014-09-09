#ifndef GAME_H
#define GAME_H
#include <time.h>
//The game namespace stores important settings and global variables for the program
namespace game
{
    const int max_objects = 6;//maximum number of objects to be created for collision testing. must be constant so that array can be made using this number
    extern float time;
    extern clock_t time_started;
    extern double time_elapsed;
}
#endif // GAME_H
