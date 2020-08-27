#include <iostream>
#include <cstdlib>
#include "utils.h"
#include "naumaxia.h"
#include "defs.h"

int main ()
{
    // Make naumaxia game object and set any parameters.
    Naumaxia naumaxia(ROWS, COLS, NUM_SHIP);
    naumaxia.setWeatherThreshold(WEATHER_DAMAGE_THRESHOLD);
    naumaxia.setTreasureTarget(TARGET);
    // Enter game loop
    naumaxia.play();

    // Exit
    return 0;
}
