#include "game.h"
namespace game{
    //initialize variables
    float time_started = 0.0;
    double time = 0.0;
    double time_elapsed = 0.0;
float get_time()
{
    return ((float)clock()-time_started)/CLOCKS_PER_SEC;
}
}
