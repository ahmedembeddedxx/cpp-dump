#pragma once
#ifndef DYNAMIC_H
#define DYNAMIC_H

#include "Gameobject.h" // Include the Gameobject header file to inherit from it
#include <SFML/Graphics.hpp>

class Dynamic : public Gameobject
{
protected:
    sf::Vector2f deploy_position; // The position where the dynamic object is deployed

public:
    // Constructor with a default parameter (0, 100)
    Dynamic(sf::Vector2f dep = sf::Vector2f(0, 100));

    // Virtual function to be implemented by derived classes for movement
    virtual void move() = 0;

    // Destructor
    ~Dynamic();
};

#endif // DYNAMIC_H
