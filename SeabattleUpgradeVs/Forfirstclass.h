#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <time.h>
#include <list>

#pragma warning( push )
#pragma warning( disable : 4996)

#define NUM_CELLS  10
#define ZERO_CHAR  48
#define FAIL_BOOM  -1
#define CHAR_A     97

using namespace std;

struct Bufferxy {
    char alf;
    int y;
    int x;

};

class Paluba {
public:
    int x;
    int y;
    bool lives;
    Paluba() { 
        x = -1; 
        y = -1; 
        lives = false;
    }
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
        dir = (dir == HORISONTAL ? VERTICAL : HORISONTAL);
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

struct Board {
    list<Ship*> ships;
    list<Ship*> oposite_ships;
    char battlefield[10][10];
    char battlefield2[10][10];
    char battlefield_oppon[10][10];
    char battlefield_oppon2[10][10];

    Board() {
        set_initial_ships();
        empty_board();
        printboard();
    }

    void set_initial_ships() {
        ships.push_back(new Type_1(VERTICAL));
        ships.push_back(new Type_1(HORISONTAL));
        ships.push_back(new Type_2(VERTICAL));
        ships.push_back(new Type_2(HORISONTAL));
        ships.push_back(new Type_3(HORISONTAL));

        oposite_ships.push_back(new Type_1(VERTICAL));
        oposite_ships.push_back(new Type_1(HORISONTAL));
        oposite_ships.push_back(new Type_2(VERTICAL));
        oposite_ships.push_back(new Type_2(HORISONTAL));
        oposite_ships.push_back(new Type_3(HORISONTAL));
    }
    void empty_board()
    {
        ////////////////////////////// const
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

    void clean()
    {
        for (int k = 0; k < 10; k++)
            for (int i = 0; i < 10; i++)
                battlefield[i][k] = ',';
    }

    void print_numbers(int k)
    {
        string offset = k < 9 ? "  " : " ";
        cout << 1 + k << offset;
    }

    void print_border()
    {
        char bor = 'a';
        for (int i = 0; i < NUM_CELLS; i++)
        {
            cout << bor << "  ";
            bor++;
        }
    }

    void printboard(int user = 1)
    {
        cout << "   ";
        print_border();

        cout << "                       ";
        cout << "   ";
        print_border();
        cout << endl;

        for (int k = 0; k < NUM_CELLS; k++)
        {
            print_numbers(k);

            for (int i = 0; i < NUM_CELLS; i++)
            {
                if ((battlefield2[i][k] != ',' && user == 2) ||
                    (battlefield_oppon[i][k] != ',' && user == 1))
                    cout << "#" << "  ";

                //////////////////////////////// 48 to const
                else if (int(battlefield[i][k]) - ZERO_CHAR >= 10)
                    cout << int(battlefield[i][k]) - ZERO_CHAR << " ";

                else
                    cout << battlefield[i][k] << "  ";
            }

            cout << "                       ";
            print_numbers(k);

            for (int i = 0; i < NUM_CELLS; i++)
            {
                if (user == 1)
                    cout << battlefield2[i][k] << "  ";
                else
                    cout << battlefield_oppon[i][k] << "  ";
            }
            cout << endl;
        }
    }

    bool validate(int x, int y)
    {
        // massiv v kotorom vse koordinati vokrug
        int area[9][2] = {};

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

    void clear_put(list<Ship*>& ships) {

        list<Ship*>::iterator itr = ships.begin();
        list<Ship*>::iterator end = ships.end();

        clean();

        for (list<Ship*>::iterator itr = ships.begin(); itr != ships.end(); itr++)
        {
            put_ship(*itr);
        }

    }

    int game_shoot(Bufferxy& bufxy, int shoot, int player =  1)
    {
        if (shoot != 0)
        {
            if (player == 1)
                battlefield2[bufxy.x][bufxy.y] = shoot + '0';
            else
                battlefield_oppon[bufxy.x][bufxy.y] = shoot + '0';

            cout << "You shoot" << endl;
            ////////////////////////// ternary

            return player;
        }
        else
        {
            if (player == 1)
                battlefield2[bufxy.x][bufxy.y] = '#';
            else
                battlefield_oppon[bufxy.x][bufxy.y] = '#';
        }
        int player_ret = (player == 1) ? 2 : 1;
        return player_ret;
    }
};

struct Game {

    const int army_size = 5;
    Board board;

    Game() {}

    void run(){
        put_all_my_ships(board.ships, board);
        system("CLS");

        game_infoship(board.ships);

        change_allships(board.ships, board.oposite_ships, army_size, board);

        play_with_different_comp(board.ships, board.oposite_ships, board);
    }

    /////////////////////////put_all_my_ships/////////////////
    void put_all_my_ships(list<Ship*>& ships, Board board)
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
                board.clear_put(ships);
                break;
            }
        }
    }

    bool game_random(list<Ship*>& ships)
    {
        for (list<Ship*>::iterator itr = ships.begin(); itr != ships.end(); itr++)
            random_ship(*itr);
        return true;
    };

    void random_ship(Ship* ship)
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

            ship->dir = direct == VERTICAL ? VERTICAL : HORISONTAL;
            ship->set_first_paluba(x, y);

        } while (board.put_ship(ship) != ship->id());
    };

    bool game_coord(list<Ship*>& ships)
    {
        ////////////////////////////////////////// delete brakets  //////////////// check if it can be together
        for (list<Ship*>::iterator itr = ships.begin(); itr != ships.end(); itr++)
        {
            validate_for_set(*itr);
        }
        wait_enter();
        return true;
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

        void validate_for_set(Ship * ships)
        {
            int y;
            int x;
            char alf;
            cout << "Write x y for " << ships->label() << " " << ships->id() << endl;
            string buffer;
            while (true)
            {
                cin >> buffer;
                if (buffer.length() == 1 && isalpha(buffer[0]) && tolower(buffer[0]) <= 'j') {
                    alf = buffer[0];
                    break;
                }
                cout << "Invalid value 1. Try again. It should be a letter.[a..j]" << endl;
            }

            while (true)
            {
                cin >> buffer;
                y = atoi(buffer.c_str());
                if (y >= 1 && y <= 10) {
                    break;
                }
                cout << "Invalid value 2. It should be a number [1..10]" << endl;
            }

            x = alf - 97;
            y--;
            ships->set_first_paluba(x, y);
        }

    

    

   
    /////////////////////////put_all_my_ships END/////////////////

    bool game_infoship(list<Ship*>& ships)
    {

        for (list<Ship*>::iterator itr = ships.begin(); itr != ships.end(); itr++)
        {
            cout << (*itr)->serialize() << endl;
        }
        return true;
    }

     
    ///////////////////change_allships//////////////////
    void change_allships(list<Ship*>& ships, list<Ship*>& oposite_ships, int army_size, Board board)
    {
        string answer;
        while (true)
        {
            board.printboard();
            cout << "If you want change place of ships on the board ---- <put>" << endl;
            cout << "if you want rotate ship --- <rotate>" << endl;
            cout << "If you want start game --- <start>" << endl;
            cout << "If you want put ship random -------- 'random'" << endl;
            cout << "If you want share ship -------- 'share'" << endl;
            cin >> answer;
            if (answer == "put")
            {
                system("CLS");
                board.printboard();
                game_put1ship(ships, army_size);
                board.clear_put(ships);
            }
            if (answer == "rotate")
            {
                game_rotate(ships, army_size);
                board.clear_put(ships);
            }
            if (answer == "share")
            {
                game_share_to_opponent(ships);
            }

            if (answer == "start")
            {
                board.clean();
                set_oponent(oposite_ships);
                board.clear_put(oposite_ships);
                break;
            }
        }
    }

    bool game_put1ship(list<Ship*>& ships, int army_size)
    {
        int k;
        list<Ship*>::iterator itr = ships.begin();
        list<Ship*>::iterator end = ships.end();

        k = id_input(army_size);

        for (; (*itr)->id() != k; itr++);
        validate_for_set(*itr);
        itr = ships.begin();

    
        return true;
    }

    int id_input(int armysize)
    {
        int k;
        while (true)
        {
            cout << "Write id of ship" << endl;
            cin >> k;
            if (k <= armysize && k > 0)
            {
                return k;
            }
            cout << "invalid" << endl;
        }
    };

    bool game_rotate(list<Ship*>& ships, int army_size)
    {
        int k;

        system("CLS");
        
        k = id_input(army_size);
        for (list<Ship*>::iterator itr = ships.begin(); itr != ships.end(); itr++) {
            if ((*itr)->id() == k)
            {
                (*itr)->rotate();
                break;
            }
        }

        return true;
    }

    bool game_share_to_opponent(list<Ship*>& ships)
    {
        for (list<Ship*>::iterator itr = ships.begin(); itr != ships.end(); itr++)
        {
            cout << "Share ship nomber" << (*itr)->id() << endl;
            cout << (*itr)->share_ship() << endl;
            wait_enter();
        }
        return true;
    }

    ////////////////////////set_oponent///////////////////////
    void set_oponent(list<Ship*>& oposite_ships)
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

    bool game_set_opose_ship(list<Ship*>& oposite_ships)
    {
        cout << "Set opponent" << endl;
        for (list<Ship*>::iterator itr = oposite_ships.begin(); itr != oposite_ships.end(); itr++)
        {
            cout << "put ship nomber  " << (*itr)->id() << endl;
            string share;
            cin >> share;
            put_opponent_ship(share, *itr);
        }

        return true;
    }

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
                ///////////////////////////// ternary
                Direction direction = (stoi(value) == 1) ? HORISONTAL : VERTICAL;
                ship->set_direction(direction);
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

    bool game_random_opon(list<Ship*>& oposite_ships)
    {

        for (list<Ship*>::iterator itr = oposite_ships.begin(); itr != oposite_ships.end(); itr++)
        {
            random_ship(*itr);
        }
        
        return true;
    }
    ////////////////////////set_oponentEND///////////////////////
    ///////////////////change_allshipsEND//////////////////


    /////////////////////////////   PLAY WITH DIFERENT COMP   ///////////////////

    void play_with_different_comp(list<Ship*> ships, list<Ship*> oposite_ships, Board board)
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
                for_two_comp(ships, oposite_ships,board);
                break;
            }

            ///////////////////////////////////////////

            if (answer == "one")
            {
                for_one_comp(ships, oposite_ships, board);
                break;
            }
        }
    }

    //////////////////////   FOR TWO COMP //////////////////////

    void for_two_comp(list<Ship*>& ships, list<Ship*>& oposite_ships, Board board)
    {
        int end_ship = 0;
        Bufferxy bufxy;
        system("CLS");

        do
        {
            board.printboard();
            end_ship = 0;
            int shoot = 0;


            ///////////////////

            play_validate(bufxy);

            ///////////////// oposite_ships
            shoot = game_find_op_ship(oposite_ships, bufxy);
            //////////////////////// shoot

            /////////////////////// shoot /////
            board.game_shoot(bufxy, shoot);
            /////////////////////////////


            ///////////////
            end_ship = game_end(oposite_ships);
            //////////////////////////////

        } while (end_ship != 0);

        cout << "YOU WIN" << endl;
    }

    void play_validate(Bufferxy& bufxy)
    {
        string buffer;
        while (true)
        {
            cin >> buffer;
            if (buffer.length() == 1 && isalpha(buffer[0]) && tolower(buffer[0]) <= 'j') {
                bufxy.alf = buffer[0];
                break;
            }
            cout << "Invalid value 1. Try again. It should be a letter.[a..j]" << endl;
        }

        while (true)
        {
            cin >> buffer;
            bufxy.y = atoi(buffer.c_str());
            if (bufxy.y >= 1 && bufxy.y <= 10) {
                break;
            }
            cout << "Invalid value 2. It should be a number [1..10]" << endl;
        }

        bufxy.x = bufxy.alf - CHAR_A;
        bufxy.y--;
    }

    int game_find_op_ship(list<Ship*>& oposite_ships, Bufferxy& bufxy)
    {
        int shoot = 0;

        for (list<Ship*>::iterator itr = oposite_ships.begin(); itr != oposite_ships.end(); itr++)
        {
            if (shoot_ship(bufxy.x, bufxy.y, *itr) != -1)
            {
                shoot = shoot_ship(bufxy.x, bufxy.y, *itr);
            }
        }

        return shoot;
    }

    int shoot_ship(int x, int y, Ship* ship)
    {
        Paluba* pl = ship->first_paluba();
        while (pl != NULL) {
            if (pl->x == x && pl->y == y)
            {
                pl->lives = false;
                return ship->count_palub();
            }

            pl = ship->next_paluba();
        }
        //////////////////// make const
        return FAIL_BOOM;
    }

    int game_end(list<Ship*>& oposite_ships)
    {
        int end_ship = 0;
        for (list<Ship*>::iterator itr = oposite_ships.begin(); itr != oposite_ships.end(); itr++)
        {
            end_ship = end_ship + end_game(*itr);
        }
        cout << "-------" << end_ship << endl;
        char c = 0;
        wait_enter();
        system("CLS");
        return end_ship;
    }

    int end_game(Ship* ship)
    {
        ////////////////////////////////////make terniary
        int end_func = (ship->lives() > 0) ? 1 : 0;
        return end_func;
    }

    void for_one_comp(list<Ship*> ships, list<Ship*> oposite_ships, Board board)
    {
        int end_ship = 0;
        int player = 1;
        Bufferxy bufxy;

        do {
            while (player == 1)
            {
                system("CLS");
                cout << "PLAYER 1" << endl;
                ////////////////////////////////
                board.clear_put(ships);
                board.printboard(player);
                /////////////////////////////////////

                end_ship = 0;
                int shoot = 0;

                cout << "Break ship.Write x y for " << endl;
                /////////////
                play_validate(bufxy);
                ////////////////////////////

                ///////////////////////////
                shoot = game_find_op_ship(oposite_ships, bufxy);
                //////////////////////////////

                ///////////////////////////
                player = board.game_shoot(bufxy, shoot, player);
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
                board.clear_put(oposite_ships);
                board.printboard(player);
                /////////////////////////////////////

                end_ship = 0;
                int shoot = 0;
                cout << "Break ship.Write x y for " << endl;

                /////////////
                play_validate(bufxy);
                ////////////////////////////


                ///////////////////////////
                shoot = game_find_op_ship(ships, bufxy);
                //////////////////////////////

                ///////////////////////////
                player = board.game_shoot(bufxy, shoot, player);
                /////////////////////////////////

                //////////////////////////////
                end_ship = game_end(ships);
                ////////////////////////////
            }
            ///////////////////
        } while (end_ship != 0);
        cout << "YOU WIN" << endl;
    }
};