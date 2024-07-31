#pragma once
#ifndef HEROBLOCK_H
#define HEROBLOCK_H

#include "Dynamic.h" // Include the Dynamic header file to inherit from it
#include <SFML/Graphics.hpp>

class HeroBlock : public Dynamic
{
private:
    char direction; // Direction of movement
    sf::RectangleShape hero; // Rectangle shape representing the hero

public:
    // Constructor to initialize the HeroBlock with a default position (20, 485)
    HeroBlock();

    // Implementation of the pure virtual function to move the hero
    void move() override;

    // Set the direction of movement based on user input (0 for right, 1 for left, other values for idle)
    void setdirection(int i);

    // Draw the hero on the window
    void draw(sf::RenderWindow& window) override;

    // Get the global bounding rectangle of the hero for collision detection
    sf::FloatRect getGlobalBounds();
};

#endif // HEROBLOCK_H
