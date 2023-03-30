#include "firstfunc.h"

#pragma warning( push )
#pragma warning( disable : 4996)

char battlefield[10][10];
char battlefield2[10][10];
char battlefield_oppon[10][10];

void printboard(int user )
{
    char bor = 'a';
    cout << "   ";
    for (int i = 0; i < 10; i++)
    {
        cout << bor << "  ";
        bor++;
    }
    cout << "                       ";

    cout << "   ";
    bor = 'a';

    for (int i = 0; i < 10; i++)
    {
        cout << bor << "  ";
        bor++;
    }

    cout << endl;
    for (int k = 0; k < 10; k++)
    {
        if (k < 9)
        {
            cout << 1 + k << "  ";
        }
        else
        {
            cout << 1 + k << " ";
        }


        for (int i = 0; i < 10; i++)
        {
            if (battlefield2[i][k] != ',' && user == 0)
            {
                cout << "#" << "  ";
            }
            else if (battlefield_oppon[i][k] != ',' && user == 1)
            {
                cout << "#" << "  ";
            }
            else if (int(battlefield[i][k]) - 48 >= 10)
            {
                cout << int(battlefield[i][k]) - 48 << " ";
            }
            else
            {

                cout << battlefield[i][k] << "  ";
            }


        }
        cout << "                       ";
        if (k < 9)
        {
            cout << 1 + k << "  ";
        }
        else
        {
            cout << 1 + k << " ";
        }
        for (int i = 0; i < 10; i++)
        {
            if (user == 1)
            {
                cout << battlefield2[i][k] << "  ";
            }
            else
            {
                cout << battlefield_oppon[i][k] << "  ";
            }
        }

        cout << endl;
    }

}

bool validate(int x, int y)
{
    // massiv v kotorom vse koordinati vokrug
    int area[9][2];
    area[0][0] = x;
    area[0][1] = y;
    area[1][0] = x + 1;
    area[1][1] = y;
    area[2][0] = x - 1;
    area[2][1] = y;
    area[3][0] = x + 1;
    area[3][1] = y + 1;
    area[4][0] = x - 1;
    area[4][1] = y + 1;
    area[5][0] = x;
    area[5][1] = y + 1;
    area[6][0] = x + 1;
    area[6][1] = y - 1;
    area[7][0] = x - 1;
    area[7][1] = y - 1;
    area[8][0] = x;
    area[8][1] = y - 1;

    for (int i = 0; i < 9; i++)
    {
        if (area[i][0] >= 0 && area[i][0] < 10 && area[i][1] >= 0 && area[i][1] < 10) {
            if (battlefield[area[i][0]][area[i][1]] != ',') {
                return false;
            }
        }
        else if (i == 0)
            return false;
    }

    return true;
}



int put_ship(Ship* ship)
{

    Paluba* pl = ship->first_paluba();
    bool valide = true;
    while (pl) {
        if (!validate(pl->x, pl->y))
        {
            // show error ship id
            cout << "error " << ship->id() << endl;
            valide = false;
            return -1;
        }
        pl = ship->next_paluba();
    }

    //add ships[i] to board
    pl = ship->first_paluba();
    while (pl != NULL)
    {
        battlefield[pl->x][pl->y] = ship->id() + '0';
        pl = ship->next_paluba();
    }



    return ship->id();
}

int random_ship(Ship* ship)
{

    time_t t;
    int x, y, direct;
    srand((unsigned)time(&t));
    do {
        x = rand() % 10;
        y = rand() % 10;
        direct = rand() % 2;
        cout << "x,y" << x << "," << y << endl;
        cout << direct << endl;
        if (direct == 1)
        {
            ship->dir = HORISONTAL;
        }
        else
        {
            ship->dir = VERTICAL;
        }

        ship->set_first_paluba(x, y);

    } while (put_ship(ship) != ship->id());



    return 1;
};


int put_opponent_ship(string& params, Ship* ship)
{

    // obrabot params
    // x:8,y:6,r:2
    // -->
    // [x:8, y:6, r:2]
    // -->
    // key = x
    // value = 8
    // ...
    int x = -1, y = -1;
    size_t curr_pos = 0;//тип отвечающий за размер обьекта
    size_t pos = std::string::npos;

    while (true) {
        size_t pos = params.find(",", curr_pos);
        string param = params.substr(curr_pos, pos);
        char key = param[0];
        string value = param.substr(2);
        switch (key)
        {
        case'x':
            x = stoi(value);
            break;
        case'y':
            y = stoi(value);
            break;
        case 'r':
            if (stoi(value) == 1)
            {
                ship->set_direction(HORISONTAL);
            }
            else
            {
                ship->set_direction(VERTICAL);
            }
            break;
        }// switch
        curr_pos = pos + 1;

        if (pos == std::string::npos)
            break;

    };

    if (x >= 0 && y >= 0)
        ship->set_first_paluba(x, y);

    return 0;
}



void empty_board()
{
    for (int k = 0; k < 10; k++)
    {
        for (int i = 0; i < 10; i++)
        {
            battlefield[k][i] = ',';
            battlefield2[k][i] = ',';
            battlefield_oppon[k][i] = ',';
        }
    }
}

void clean_board()
{
    for (int k = 0; k < 10; k++)
        for (int i = 0; i < 10; i++)
            battlefield[i][k] = ',';
}



int shoot_ship(int x, int y, Ship* ship)
{
    Paluba* pl = ship->first_paluba();
    while (pl != NULL) {
        if (pl->x == x && pl->y == y)
        {
            pl->lives = false;
            cout << ship->lives() << endl;
            return ship->count_palub();
        }

        pl = ship->next_paluba();
    }
    return -1;
}

int end_game(Ship* ship)
{
    if (ship->lives() > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void wait_enter()
{
    char c = 0;
    while (true)
    {
        c = getch();

        if (c == 13)
            break;
    }
};

bool xy_validate(char alf, int y)
{
    if (y > 0 && y < 11 && alf > 96 && alf < 107)
    {
        return true;
    }
    cout << "invalid" << endl;
    return false;
};

int id_input(int armysize)
{
    int k;
    while (true)
    {
        cout << "Write id of ship" << endl;
        cin >> k;
        if (k <= armysize && k > 0)
        {
            k = k - 1;
            return k;
        };
        cout << "invalid" << endl;
    }
};

void validate_for_set(Ship* ships)
{

    int y;
    int x;
    char alf;
    cout << "Write x y for " << ships->label() << " " << ships->id() << endl;

    do
    {
        cin >> alf;
        cin >> y;
    } while (xy_validate(alf, y) == false);
    x = alf - 97;
    y--;
    ships->set_first_paluba(x, y);

}

void play_validate(Bufferxy* bufxy)
{
    do
    {
        cin >> bufxy->alf;
        cin >> bufxy->y;
        cout << "invalid";
    } while (xy_validate(bufxy->alf, bufxy->y) == false);
    bufxy->x = bufxy->alf - 97;
    bufxy->y--;

}

int game_shoot(Bufferxy* bufxy, int shoot, int player)
{
    if (shoot != 0)
    {
        battlefield_oppon[bufxy->x][bufxy->y] = shoot + '0';
        cout << "You shoot" << endl;
        if (player == 1)
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        battlefield_oppon[bufxy->x][bufxy->y] = '#';
    }
    return player;
}

bool game_random(list<Ship*> ships)
{
    list<Ship*>::iterator itr = ships.begin();//итератор = функция начало обЪекта списка ships
    list<Ship*>::iterator end = ships.end();

    for (; itr != end; itr++)
    {
        random_ship(*itr);
    }
    return true;
};

bool game_coord(list<Ship*> ships)
{
    list<Ship*>::iterator itr = ships.begin();
    list<Ship*>::iterator end = ships.end();

    for (; itr != end; itr++)
    {
        validate_for_set(*itr);
    }
    for (; itr != end; itr++)
    {
        put_ship(*itr);
    }
    return true;
}

bool game_infoship(list<Ship*> ships)
{
    list<Ship*>::iterator itr = ships.begin();
    list<Ship*>::iterator end = ships.end();

    for (; itr != end; itr++)
    {
        cout << (*itr)->serialize() << endl;
    }
    return true;
}

bool game_put1ship(list<Ship*> ships, int army_size)
{
    int k;
    list<Ship*>::iterator itr = ships.begin();
    list<Ship*>::iterator end = ships.end();
    system("CLS");
    printboard();
    clean_board();
    k = id_input(army_size);
    for (; (*itr)->id() == k; itr++);
    validate_for_set(*itr);
    itr = ships.begin();

    for (; itr != end; itr++)
    {
        put_ship(*itr);
    }
    return true;
}

bool game_rotate(list<Ship*> ships, int army_size)
{
    int k;
    list<Ship*>::iterator itr = ships.begin();
    list<Ship*>::iterator end = ships.end();
    system("CLS");
    k = id_input(army_size);
    for (; (*itr)->id() == k; itr++);
    (*itr)->rotate();
    clean_board();
    for (; itr != end; itr++)
    {
        put_ship(*itr);
    }
    printboard();
    return true;
}

bool game_share_to_opponent(list<Ship*> ships)
{
    list<Ship*>::iterator itr = ships.begin();
    list<Ship*>::iterator end = ships.end();
    for (; itr != end; itr++)
    {
        cout << "Share ship nomber" << (*itr)->id() << endl;
        cout << (*itr)->share_ship() << endl;
        wait_enter();
    }
    return true;
}

bool game_set_opose_ship(list<Ship*> oposite_ships)
{
    cout << "Set opponent" << endl;
    clean_board();
    list<Ship*>::iterator itr = oposite_ships.begin();
    list<Ship*>::iterator end = oposite_ships.end();
    for (; itr != end; itr++)
    {
        cout << "put ship nomber  " << (*itr)->id() << endl;
        string share;
        cin >> share;
        put_opponent_ship(share, *itr);
    }
    clean_board();

    for (; itr != end; itr++)
    {
        put_ship(*itr);
    }
    return true;
}

bool game_random_opon(list<Ship*> oposite_ships)
{
    clean_board();
    list<Ship*>::iterator itr = oposite_ships.begin();
    list<Ship*>::iterator end = oposite_ships.end();

    for (; itr != end; itr++)
    {
        random_ship(*itr);
    }
    clean_board();
    for (; itr != end; itr++)
    {
        put_ship(*itr);
    }
    printboard();
    return true;
}

bool game_setxy(Bufferxy* bufxy)
{
    cout << "Break ship.Write x y for " << endl;

    cin >> bufxy->alf;
    cin >> bufxy->y;
    return true;
}

int game_find_op_ship(list<Ship*> oposite_ships, Bufferxy* bufxy)
{
    int shoot = 0;
    list<Ship*>::iterator itr = oposite_ships.begin();
    list<Ship*>::iterator end = oposite_ships.end();

    for (; itr != end; itr++)
    {
        if (shoot_ship(bufxy->x, bufxy->y, *itr) != -1)
        {
            shoot = shoot_ship(bufxy->x, bufxy->y, *itr);
        }
    }

    return shoot;
}


int game_end(list<Ship*> oposite_ships)
{
    int end_ship = 0;
    list<Ship*>::iterator itr = oposite_ships.begin();
    list<Ship*>::iterator end = oposite_ships.end();
    for (; itr != end; itr++)
    {
        end_ship = end_ship + end_game(*itr);
    }
    cout << "-------" << end_ship << endl;
    char c = 0;
    wait_enter();
    system("CLS");
    return end_ship;
}

bool game_put_ship_for2(list<Ship*> ships)
{

    list<Ship*>::iterator itr = ships.begin();
    list<Ship*>::iterator end = ships.end();
    clean_board();

    for (; itr != end; itr++)
    {
        put_ship(*itr);
    }
    printboard();
    return true;
}

void set_initial_ships(list<Ship*>& x)
{
    x.push_back(new Type_1(VERTICAL));
    x.push_back(new Type_1(HORISONTAL));
    x.push_back(new Type_2(VERTICAL));
    x.push_back(new Type_2(HORISONTAL));
    x.push_back(new Type_3(HORISONTAL));
}

void put_all_my_ships(list<Ship*> ships)
{
    while (true)
    {
        string answer;
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
}

void set_oponent(list<Ship*> oposite_ships)
{
    string answer;
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
}

void change_allships(list<Ship*> ships, list<Ship*> oposite_ships, int army_size)
{
    string answer;
    while (true)
    {
        printboard();
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
            set_oponent(oposite_ships);
            break;
        }
    }
}

void for_one_comp(list<Ship*> ships, list<Ship*> oposite_ships, Bufferxy& bufxy)
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
}

void for_two_comp(list<Ship*> ships, list<Ship*> oposite_ships, Bufferxy& bufxy)
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
}

void play_with_different_comp(list<Ship*> ships, list<Ship*> oposite_ships, Bufferxy& bufxy)
{
    string answer;
    while (true)
    {
        system("CLS");
        cout << "If you want play with 2 computers  -------- 'two'" << endl;
        cout << "If you want play with 1 computer -------- 'one'" << endl;

        cin >> answer;

        if (answer == "two")
        {
            for_two_comp(ships, oposite_ships, bufxy);
            break;
        }

        ///////////////////////////////////////////

        if (answer == "one")
        {
            for_one_comp(ships, oposite_ships, bufxy);
            break;
        }
    }
}