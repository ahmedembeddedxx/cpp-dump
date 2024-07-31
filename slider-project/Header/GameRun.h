#pragma once
#ifndef GAMERUN_H
#define GAMERUN_H

#include "GameObject.cpp"
#include "Dynamic.cpp"
#include "HeroBlock.cpp"
#include "EnemyBLock.cpp"
#include "Background.cpp"
#include "Heirarchy.cpp"
#include <SFML/Graphics.hpp>

class GameRun {
    Gameobject* bg; // Pointer to a GameObject (base class)
    Dynamic* gameObjPtr; // Pointer to a Dynamic (base class) used for upcasting HeroBlock
    HeroBlock* hero; // Pointer to a HeroBlock (derived class) used for downcasting Dynamic
    EnemyBlock enemy1; // An instance of EnemyBlock (derived class)
    EnemyBlock enemy2; // Another instance of EnemyBlock (derived class)
    Dynamic* enemy[2]; // An array of pointers to Dynamic (base class) used for upcasting EnemyBlock

    Hierarchy heir;
    bool collision(HeroBlock hero, EnemyBlock enemy);

public:
    GameRun();
    void run();
    ~GameRun();
};

#endif // GAMERUN_H
