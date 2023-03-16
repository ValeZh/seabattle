// SeabattleUpgradeVs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <string>
#include <thread>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <time.h>

//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#pragma warning( push )
#pragma warning( disable : 4996)

using namespace std;

char battlefield[10][10];
char battlefield2[10][10];
char battlefield_oppon[10][10];

class Paluba {
public:
    int x;
    int y;
    bool lives;
    Paluba() { x = -1; y = -1; lives = false; }
};

enum Direction
{
    HORISONTAL,
    VERTICAL
};

static int counter = 0;

class Ship
{
private:
    int _id;

public:
    Direction    dir;

public:
    virtual const char* label() = 0;
    virtual int count_palub() = 0;
    virtual int lives() = 0;
    virtual void set_first_paluba(int x, int y) = 0;
    virtual Paluba* first_paluba() = 0;
    virtual Paluba* next_paluba() = 0;
    virtual void rotate() = 0;
    virtual string share_ship() = 0;
    int id() { return _id; }

    Ship(Direction d) : dir(d)
    {
        counter++;
        _id = counter;
    }
    void set_direction(Direction d) { dir = d; }

    string serialize() {
        string res = label();
        res += "(";
        res += to_string(id());
        res += ")";
        res += "|cells=";
        res += to_string(count_palub());
        res += "|dir=";
        res += (dir == VERTICAL ? "vertical" : "horizontal");
        res += "|lives=";
        res += to_string(lives());
        Paluba* pl = first_paluba();
        while (pl != NULL) {
            res += "|x,y=";
            res += to_string(pl->x);
            res += ",";
            res += to_string(pl->y);
            pl = next_paluba();
        }
        return res;
    };
};

class MultyPalub : public Ship {
public:
    MultyPalub(Direction d) : Ship(d) { }
    virtual int count_palub()
    {
        int counter = 0;
        Paluba* pl = first_paluba();
        while (pl) {
            counter++;
            pl = next_paluba();
        }
        return counter;
    }
    virtual int lives()
    {
        int counter = 0;
        Paluba* pl = first_paluba();
        while (pl) {
            if (pl->lives == true)
            {
                counter++;
            }
            pl = next_paluba();
        }
        return counter;
    }
    void set_first_paluba(int x, int y) {
        Paluba* pl = first_paluba();
        pl->x = x;
        pl->y = y;
        pl->lives = true;
        int prevx = x;
        int prevy = y;
        pl = next_paluba();
        while (pl) {
            pl->lives = true;

            if (dir == HORISONTAL) {
                pl->x = prevx + 1;
                pl->y = prevy;

            }
            else {
                pl->x = prevx;
                pl->y = prevy + 1;
            }
            prevx = pl->x;
            prevy = pl->y;
            pl = next_paluba();
        }
    }
    virtual void rotate() {
        dir = (dir == HORISONTAL) ? VERTICAL : HORISONTAL;
        Paluba* pl = first_paluba();
        set_first_paluba(pl->x, pl->y);
    };

    string share_ship()
    {
        string share;
        Paluba* pl = first_paluba();
        share = "n:";
        share += to_string(id());
        share += ",";
        share += "x:";
        share += to_string(pl->x);
        share += ",";
        share += "y:";
        share += to_string(pl->y);
        share += ",";
        if (dir == HORISONTAL)
        {
            share += "r:";
            share += "1";
        }
        else
        {
            share += "r:";
            share += "2";
        }
        return share;
    };

};

class Type_1 : public Ship {
private:
    Paluba paluba;

public:
    Type_1(Direction d) : Ship(d) {}
    ~Type_1() {}
    const char* label() { return "Single cell ship"; }
    int count_palub() { return 1; }
    int lives() { return paluba.lives ? 1 : 0; }
    void set_first_paluba(int x, int y) { paluba.x = x; paluba.y = y; paluba.lives = true; }
    Paluba* first_paluba() { return &paluba; }
    Paluba* next_paluba() { return NULL; }
    virtual void rotate() {};
    string share_ship()
    {
        string share;
        share = "n:";
        share += to_string(id());
        share += ",";
        share += "x:";
        share += to_string(paluba.x);
        share += ",";
        share += "y:";
        share += to_string(paluba.y);
        return share;
    };
};


class Type_2 : public MultyPalub {
private:
    int current_paluba;
    Paluba paluba[2];

public:
    Type_2(Direction d) : MultyPalub(d) { current_paluba = 0; }
    ~Type_2() {}
    const char* label() { return "Double cell ship"; }
    Paluba* first_paluba() {
        current_paluba = 0;
        return paluba;
    }
    Paluba* next_paluba() {
        if (current_paluba >= 1)
            return NULL;
        current_paluba++;
        return paluba + current_paluba;
    }



};

class Type_3 : public MultyPalub {
private:
    int current_paluba;
    Paluba paluba[3];

public:
    Type_3(Direction d) : MultyPalub(d) { current_paluba = 0; }
    ~Type_3() {}
    const char* label() { return "Three cell ship"; }
    Paluba* first_paluba() {
        current_paluba = 0;
        return paluba;
    }
    Paluba* next_paluba() {
        if (current_paluba >= 2)
            return NULL;
        current_paluba++;
        return paluba + current_paluba;
    }
};


void printboard(int user = 0)
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



int put_ship(int k, Ship* ship)
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

int random_ship(int k, Ship* ship)
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

    } while (put_ship(k, ship) != ship->id());
    return k;
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
    size_t curr_pos = 0;
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



int shoot_ship(int x, int y, int i, Ship* ship)
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

int id_validate(int armysize)
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

void validate_for_set(Ship* ships, int k)
{
    int y;
    int x;
    char alf;
    cout << "Write x y for " << ships->label() << " " << k << endl;

    do
    {
        cin >> alf;
        cin >> y;
    } while (xy_validate(alf, y) == false);
    x = alf - 97;
    y--;
    ships->set_first_paluba(x, y);
};



/////////////////////////////////////////////////////////////






int main()
{

    const int army_size = 5;
    string answer;
    char alf;
    // Create ships;

    Ship* ships[army_size];
    ships[0] = new Type_1(VERTICAL);
    ships[1] = new Type_1(HORISONTAL);
    ships[2] = new Type_2(VERTICAL);
    ships[3] = new Type_2(HORISONTAL);
    ships[4] = new Type_3(HORISONTAL);

    Ship* oposite_ships[army_size];
    oposite_ships[0] = new Type_1(VERTICAL);
    oposite_ships[1] = new Type_1(HORISONTAL);
    oposite_ships[2] = new Type_2(VERTICAL);
    oposite_ships[3] = new Type_2(HORISONTAL);
    oposite_ships[4] = new Type_3(HORISONTAL);


    empty_board();

    printboard();
    int y, x;
    while (true)
    {
        cout << "If you want put ship random -------- 'random'" << endl;
        cout << "If you want put ship by using coordinate -------- 'coord'" << endl;
        cin >> answer;
        if (answer == "random")
        {
            for (int i = 0; i < army_size; i++)
            {
                random_ship(i, ships[i]);
            }
            break;
        }
        if (answer == "coord")
        {
            for (int i = 0; i < army_size; i++)
            {
                validate_for_set(ships[i],i);
            }
            for (int i = 0; i < army_size; i++)
            {
                put_ship(i, ships[i]);
            }
            break;
        }
    }
    system("CLS");


    for (int i = 0; i < army_size; i++)
    {
        cout << ships[i]->serialize() << endl;
    }

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
            system("CLS");
            printboard();
            clean_board();
            k = id_validate(army_size);
            validate_for_set(ships[k],k);

            for (int i = 0; i < army_size; i++)
            {
                put_ship(i, ships[i]);
            }
        }
        if (answer == "rotate")
        {
            system("CLS");
            k = id_validate(army_size);
            ships[k]->rotate();
            clean_board();
            for (int i = 0; i < army_size; i++)
            {
                put_ship(i, ships[i]);
            }
            printboard();
        }
        if (answer == "share")
        {
            for (int i = 0; i < army_size; i++)
            {
                cout << "Share ship nomber" << i + 1 << endl;
                cout << ships[i]->share_ship() << endl;
                wait_enter();
            }
        }

        if (answer == "start")
        {
            cout << "If you want put random opponent  -------- 'random'" << endl;
            cout << "If you want set opponent  -------- 'set'" << endl;
            cin >> answer;
            if (answer == "set")
            {
                cout << "Set opponent" << endl;
                clean_board();
                for (int i = 0; i < army_size; i++)
                {
                    cout << "put ship nomber  " << i + 1 << endl;
                    string share;
                    cin >> share;
                    put_opponent_ship(share, oposite_ships[i]);
                }
                clean_board();
                for (int i = 0; i < army_size; i++)
                {
                    put_ship(i, ships[i]);
                }
                break;
            }
            if (answer == "random")
            {
                clean_board();
                for (int i = 0; i < army_size; i++)
                {
                    random_ship(i, oposite_ships[i]);
                }
                clean_board();
                for (int i = 0; i < army_size; i++)
                {
                    put_ship(i, ships[i]);
                }
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
            cout << "Break ship.Write x y for " << endl;
            while (true)
            {
                cin >> alf;
                cin >> y;
                if (y > 0 && y < 11 && alf > 96 && alf < 107)
                {
                    break;
                }
            };

            x = alf - 97;
            x;
            y--;

            for (int i = 0; i < army_size; i++)
            {
                if (shoot_ship(x, y, i, oposite_ships[i]) != -1)
                {
                    shoot = shoot_ship(x, y, i, oposite_ships[i]);
                }
            }

            if (shoot != 0)
            {
                battlefield_oppon[x][y] = shoot + '0';
                cout << "You shoot" << endl;
            }
            else
            {
                battlefield_oppon[x][y] = '#';
            }

            for (int i = 0; i < army_size; i++)
            {
                end_ship = end_ship + end_game(oposite_ships[i]);
            }
            cout << "-------" << end_ship << endl;
            char c = 0;
            wait_enter();
            system("CLS");

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
                cout << "PLAYER 1" << endl;
                clean_board();

                for (int i = 0; i < army_size; i++)
                {
                    put_ship(i, ships[i]);
                }

                printboard();
                end_ship = 0;
                int shoot = 0;
                cout << "Break ship.Write x y for " << endl;

                while (true)
                {
                    cin >> alf;
                    cin >> y;
                    if (y > 0 && y < 11 && alf > 96 && alf < 107)
                    {
                        break;
                    }
                    cout << "invalid" << endl;
                };

                x = alf - 97;
                x;
                y--;
                player = 2;

                for (int i = 0; i < army_size; i++)
                {
                    if (shoot_ship(x, y, i, oposite_ships[i]) != -1)
                    {
                        shoot = shoot_ship(x, y, i, oposite_ships[i]);
                    }
                }

                if (shoot != 0)
                {
                    battlefield_oppon[x][y] = shoot + '0';
                    cout << "You shoot" << endl;
                    player = 1;
                }
                else
                {
                    battlefield_oppon[x][y] = '#';
                }

                for (int i = 0; i < army_size; i++)
                {
                    end_ship = end_ship + end_game(oposite_ships[i]);
                }
                cout << "-------" << end_ship << endl;
                char c = 0;

                wait_enter();

                system("CLS");
            }
            while (player == 2)
            {
                cout << "PLAYER 2" << endl;
                clean_board();
                for (int i = 0; i < army_size; i++)
                {
                    put_ship(i, oposite_ships[i]);
                }

                printboard(1);
                end_ship = 0;
                int shoot = 0;
                player = 1;
                cout << "Break ship.Write x y for " << endl;

                while (true)
                {
                    cin >> alf;
                    cin >> y;
                    if (y > 0 && y < 11 && alf > 96 && alf < 107)
                    {
                        break;
                    }
                    cout << "invalid" << endl;
                };

                x = alf - 97;
                x;
                y--;

                for (int i = 0; i < army_size; i++)
                {
                    if (shoot_ship(x, y, i, ships[i]) != -1)
                    {
                        shoot = shoot_ship(x, y, i, ships[i]);
                    }
                }

                if (shoot != 0)
                {
                    battlefield2[x][y] = shoot + '0';
                    cout << "You shoot" << endl;
                    player = 2;
                }
                else
                {
                    battlefield2[x][y] = '#';
                }

                for (int i = 0; i < army_size; i++)
                {
                    end_ship = end_ship + end_game(ships[i]);
                }

                cout << "-------" << end_ship << endl;
                char c = 0;
                player = 1;
                wait_enter();
                system("CLS");
            }
        } while (end_ship != 0);
        cout << "YOU WIN" << endl;
        return 0;

    }
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