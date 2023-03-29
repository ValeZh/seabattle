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
    string answer;
    // Create ships;
    
    list<Ship*> ships;
    ships.push_back(new Type_1(VERTICAL));
    ships.push_back(new Type_1(HORISONTAL));
    ships.push_back(new Type_2(VERTICAL));
    ships.push_back(new Type_2(HORISONTAL));
    ships.push_back(new Type_3(HORISONTAL));

    Bufferxy bufxy;
    
    list<Ship*> oposite_ships;
    oposite_ships.push_back(new Type_1(VERTICAL));
    oposite_ships.push_back(new Type_1(HORISONTAL));
    oposite_ships.push_back(new Type_2(VERTICAL));
    oposite_ships.push_back(new Type_2(HORISONTAL));
    oposite_ships.push_back(new Type_3(HORISONTAL));
    
    empty_board();
    
    printboard();
    
    while (true)
    {
        cout << "If you want put ship random -------- 'random'" << endl;
        cout << "If you want put ship by using coordinate -------- 'coord'" << endl;
        cin >> answer;
        if (answer == "random")
        {
            game_random(ships);
            break;
        }
        if (answer == "coord")
        {
            game_coord(ships);
            break;
        }
    }
    system("CLS");
    
    
    game_infoship(ships);


    
    while (true)
    {
        printboard();
        int k = 0;
        cout << "If you want change place of ships on the board ---- <put>" << endl;
        cout << "if you want rotate ship --- <rotate>" << endl;
        cout << "If you want start game --- <start>" << endl;
        cout << "If you want put ship random -------- 'random'" << endl;
        cout << "If you want share ship -------- 'share'" << endl;
        cin >> answer;
        if (answer == "put")
        {
            game_put1ship(ships, army_size);
        }
        if (answer == "rotate")
        {
            game_rotate(ships, army_size);
        }
        if (answer == "share")
        {
            game_share_to_opponent(ships);
        }

        if (answer == "start")
        {
            cout << "If you want put random opponent  -------- 'random'" << endl;
            cout << "If you want set opponent  -------- 'set'" << endl;
            cin >> answer;
            
            if (answer == "set")
            {
                game_set_opose_ship(oposite_ships);
            }
            if (answer == "random")
            {
                game_random_opon(oposite_ships);
            }
            break;
        }
    }
    
    system("CLS");
    cout << "If you want play with 2 computers  -------- 'two'" << endl;
    cout << "If you want play with 1 computer -------- 'one'" << endl;

    cin >> answer;

    if (answer == "two")
    {
        int end_ship = 0;
        system("CLS");

        do
        {
            printboard();
            end_ship = 0;
            int shoot = 0;


            ///////////////////

            play_validate(&bufxy);

            ///////////////// oposite_ships
            shoot = game_find_op_ship(oposite_ships, &bufxy);
            //////////////////////// shoot

            /////////////////////// shoot /////
            game_shoot(&bufxy, shoot);
            /////////////////////////////

            
            ///////////////
            end_ship = game_end(oposite_ships);
            //////////////////////////////

        } while (end_ship != 0);

        cout << "YOU WIN" << endl;

        return 0;
    }
    
    ///////////////////////////////////////////
    
    if (answer == "one")
    {
        int end_ship = 0;
        int player = 1;
        do {
            while (player == 1)
            {
                system("CLS");
                cout << "PLAYER 1" << endl;
                ////////////////////////////////
                game_put_ship_for2(ships);
                /////////////////////////////////////

                end_ship = 0;
                int shoot = 0;

                /////////////
                play_validate(&bufxy);
                ////////////////////////////


                player = 2;
                ///////////////////////////
                shoot = game_find_op_ship(oposite_ships, &bufxy);
                //////////////////////////////

                ///////////////////////////
                player = game_shoot(&bufxy, shoot, player);
                /////////////////////////////////

                //////////////////////////////
                end_ship = game_end(oposite_ships);
                ////////////////////////////
            }
            
            ///////////////////////////////////
            while (player == 2)
            {
                cout << "PLAYER 2" << endl;
                ////////////////////////////////
                game_put_ship_for2(oposite_ships);
                /////////////////////////////////////

                end_ship = 0;
                int shoot = 0;
                cout << "Break ship.Write x y for " << endl;

                game_setxy(&bufxy);
                /////////////
                play_validate(&bufxy);
                ////////////////////////////


                player = 1;
                ///////////////////////////
                shoot = game_find_op_ship(ships, &bufxy);
                //////////////////////////////

                ///////////////////////////
                game_shoot(&bufxy, shoot, player);
                /////////////////////////////////

                //////////////////////////////
                end_ship = game_end(ships);
                ////////////////////////////
            }
            ///////////////////
        } while (end_ship != 0);
        cout << "YOU WIN" << endl;
        return 0;

    }
    
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#pragma warning( pop ) 