#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <SFML/Graphics.hpp>
#include <conio.h>
#include <random>
#include <iostream>
using namespace std;
using namespace sf;

const int window_width = 800, window_height = 600;


template <typename T>
T SRand(T i, T j);


class Gameobject
{
protected:
    static char gamestatus;

public:
    Gameobject();
    virtual void draw(sf::RenderWindow& window) = 0;
    ~Gameobject();
    void callgameend();
};

#endif // GAMEOBJECT_H

