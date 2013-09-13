#ifndef MURDER_H
#define MURDER_H

/********************************************************************************
** murder.h
** File defining the core functions of the MurderPlayer engine
**
**
**      Created: October 2012
**  Last Edited: 13/09/2013
**           by: Emeric Frémion
**
**  Status: Working, improvements to come (XML)
**
**  HOW IT WORKS:
**      It's very very basic, you don't need help
**
**
**  FUNCTIONS:
**      int roll_dice (int dice_max_value);
**          This gives a number x, 1 <= x <= dice_max_value
**      int solve_investigation (int extra_PP);
**          Returns the quality of the report taking in account the extra PP
**
**
********************************************************************************/

#include <cstdlib>

int roll_dice (int dice_max_value);
int solve_investigation (int extra_PP);
#endif // MURDER_H
