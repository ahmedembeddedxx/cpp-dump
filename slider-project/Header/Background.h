#pragma once
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "Gameobject.h" // Include the Gameobject header file to inherit from it
#include <SFML/Graphics.hpp>

class Background : public Gameobject
{
private:
    sf::RectangleShape platform; // A rectangular shape to represent the platform

public:
    Background();

    // Implementation of the virtual function to draw the background
    void draw(sf::RenderWindow& window) override;

    // Destructor
    ~Background();
};

#endif // BACKGROUND_H
