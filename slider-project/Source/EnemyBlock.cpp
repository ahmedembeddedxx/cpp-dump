#pragma once
#include "EnemyBlock.h"

// Constructor
EnemyBlock::EnemyBlock()
    : Dynamic(Vector2f(SRand(20, window_width - 50 - 20), 0))
{
    enemy.setPosition(deploy_position.x, deploy_position.y);
    velocity = SRand(0.30, 0.5);
}

// Function to move the enemy block
void EnemyBlock::move()
{
    if (gamestatus == 's')
    {
        if (deploy_position.y >= 470)
        {
            deploy_position.y = 0;
            deploy_position.x = SRand(20, window_width - 50 - 20);
            enemy.initShape(); // Reinitialize the shape of the enemy when it reaches the bottom
        }
        else
        {
            deploy_position.y += velocity;
        }
    }
}

// Function to draw the enemy block on the window
void EnemyBlock::draw(RenderWindow& window) {
    enemy.setPosition(deploy_position.x, deploy_position.y);
    enemy.draw(window);
}

// Function to get the global bounds of the enemy block
FloatRect EnemyBlock::getGlobalBounds() {
    return enemy.getGlobalBounds();
}

// Function to get the underlying Obstacle object
Obstacle& EnemyBlock::getObstacle() {
    return enemy;
}
