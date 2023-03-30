#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <stdlib.h>
#include <conio.h>
#include <fstream>
#include <time.h>
#include <list>

using namespace std;

struct Bufferxy {
    char alf;
    int y, x;

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