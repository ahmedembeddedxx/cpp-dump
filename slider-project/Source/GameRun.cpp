#pragma once
#include "GameRun.h"

GameRun::GameRun() {
    bg = new Background(); // Create an instance of Background (derived class) and store the pointer in 'bg'
    gameObjPtr = new HeroBlock(); // Create an instance of HeroBlock (derived class) and store the pointer in 'gameObjPtr'
    hero = dynamic_cast<HeroBlock*>(gameObjPtr); // Downcasting 'gameObjPtr' (Dynamic) to 'hero' (HeroBlock) pointer
    enemy[0] = &enemy1; // Store the address of enemy1 in the 'enemy' array (Upcasting EnemyBlock to Dynamic)
    enemy[1] = &enemy2; // Store the address of enemy2 in the 'enemy' array (Upcasting EnemyBlock to Dynamic)
    
}

void GameRun::run() {
    RenderWindow window0(VideoMode(960, 540), "Heirarchy"); // Create the heirarchy window
    window0.setPosition(Vector2i(0, 0));
    RenderWindow window(VideoMode(800, 600), "Blocks Game"); // Create the game window
    window.setPosition(Vector2i(960, 0));
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Left) {
                    hero->setdirection(1); // Call the setdirection function on the HeroBlock instance (Downcasting)
                }
                else if (event.key.code == Keyboard::Right) {
                    hero->setdirection(0); // Call the setdirection function on the HeroBlock instance (Downcasting)
                }
                else if (event.key.code == Keyboard::Escape) {
                    window.close();
                }
            }
        }
        if (collision(*hero, enemy1) || collision(*hero, enemy2)) // Check for collision between hero and enemies
            hero->callgameend(); // Call the callgameend function on the HeroBlock instance (Downcasting)

        window.clear();
        heir.draw(window0);
        bg->draw(window); // Call the draw function on the Background instance (Upcasting)
        enemy[0]->draw(window); // Call the draw function on enemy1 (Upcasting)
        enemy[0]->move(); // Call the move function on enemy1 (Upcasting)
        enemy[1]->draw(window); // Call the draw function on enemy2 (Upcasting)
        enemy[1]->move(); // Call the move function on enemy2 (Upcasting)
        hero->draw(window); // Call the draw function on the HeroBlock instance (Upcasting)
        window.display();
    }
}

GameRun::~GameRun() {
    delete bg; // Deallocate memory for the Background instance
    delete gameObjPtr; // Deallocate memory for the Dynamic instance (HeroBlock)
}

bool GameRun::collision(HeroBlock hero, EnemyBlock enemy)
{
    FloatRect heroRect = hero.getGlobalBounds();
    FloatRect enemyRect = enemy.getGlobalBounds();
    return heroRect.intersects(enemyRect);
}
