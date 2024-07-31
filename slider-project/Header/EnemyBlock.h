#pragma once

#include "Dynamic.cpp"
#include "Obstacles.cpp"

class EnemyBlock : public Dynamic {
    Obstacle enemy;    // Object of type Obstacle representing the enemy block
    float velocity;    // The velocity of the enemy block

public:
    // Constructor
    EnemyBlock();

    // Function to move the enemy block
    void move();

    // Function to draw the enemy block on the window
    void draw(RenderWindow& window);

    // Function to get the global bounds of the enemy block
    FloatRect getGlobalBounds();

    // Function to get the underlying Obstacle object
    Obstacle& getObstacle();
};
