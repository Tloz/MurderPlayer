/********************************************************************************
** murder.cpp
** Definitions of the functions presented in murder.h
**
**      Created: October 2012
**  Last Edited: 13/09/2013
**           by: Emeric Frémion
**
**  Status: Finished
**
**
********************************************************************************/

#include "murder.h"

int roll_dice (int dice_max_value)
{
    int dice = (rand() % (dice_max_value)) + 1;
    return dice;
}

int solve_investigation (int extra_PP)
{
    int roll=roll_dice(6);
    if (roll == 1)
        return 1;
    if (roll+extra_PP >= 6)
        return 3;
    return 2;
}
