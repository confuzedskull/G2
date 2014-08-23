#include "game.h"
namespace game{
    //initialize variables
    float time_started = 0.00;
    double time = 0.00;
    double time_elapsed = 0.00;
float get_time()
{
    return ((float)clock()-time_started)/CLOCKS_PER_SEC;
}
}
