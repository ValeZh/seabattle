// SeabattleUpgradeVs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "firstfunc.h"
#include "Forfirstclass.h"

//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#pragma warning( push )
#pragma warning( disable : 4996)


int main()
{
    
    const int army_size = 5;
 

    Game game;
    game.run();
    
    return 0;
}


#pragma warning( pop ) 