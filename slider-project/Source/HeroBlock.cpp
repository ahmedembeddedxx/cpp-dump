#pragma once
#include "HeroBlock.h"

// Constructor implementation
HeroBlock::HeroBlock()
    : Dynamic(sf::Vector2f(20, 485)) // Call the base class constructor to set the deployment position
{
    direction = 'i'; // Set the initial direction to idle
    hero.setSize(sf::Vector2f(100.0f, 35.0f));
    hero.setFillColor(sf::Color(255, 153, 0)); // Set the hero's color (orange)
    hero.setOutlineColor(sf::Color(0, 0, 0)); // Set the outline color (black)
    hero.setOutlineThickness(5); // Set the outline thickness
    hero.setPosition(20, 485); // Set the hero's position
}

// Implementation of the move() function
void HeroBlock::move()
{
    if (gamestatus == 's') // Check if the game is still running
    {
        // Move the hero left or right within the screen boundaries
        if (direction == 'r' && deploy_position.x < window_width - 100 - 20)
            deploy_position.x += 20;
        if (direction == 'l' && deploy_position.x > 20)
            deploy_position.x -= 20;

        direction = 'i'; // Reset the direction to idle
    }
}

// Implementation of the setdirection() function
void HeroBlock::setdirection(int i)
{
    if (gamestatus == 's') // Check if the game is still running
    {
        // Set the direction based on user input (0 for right, 1 for left, other values for idle)
        if (i == 0)
            direction = 'r';
        else if (i == 1)
            direction = 'l';
        else
            direction = 'i';

        move(); // Move the hero based on the new direction
    }
}

// Implementation of the draw() function
void HeroBlock::draw(sf::RenderWindow& window)
{
    hero.setPosition(deploy_position.x, deploy_position.y); // Set the hero's position
    window.draw(hero); // Draw the hero on the window
}

// Implementation of the getGlobalBounds() function
sf::FloatRect HeroBlock::getGlobalBounds()
{
    return hero.getGlobalBounds(); // Get the global bounding rectangle of the hero
}
