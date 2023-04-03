// SeabattleUpgradeVs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include "Forfirstclass.h"
#include "firstfunc.h"

//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#pragma warning( push )
#pragma warning( disable : 4996)


int main()
{
    
    const int army_size = 5;
    // Create ships;
    
    list<Ship*> ships;
    set_initial_ships(ships);


    Bufferxy bufxy;
    
    list<Ship*> oposite_ships;
    set_initial_ships(oposite_ships);
    
    empty_board();
    
    printboard();
    
    put_all_my_ships(ships);
    system("CLS");
    
    game_infoship(ships);

    change_allships(ships, oposite_ships, army_size);

    play_with_different_comp(ships, oposite_ships, bufxy);

    
    return 0;
}


#pragma warning( pop ) 