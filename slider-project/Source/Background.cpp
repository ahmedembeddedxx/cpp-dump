#pragma once
#include "Background.h"

// Constructor implementation
Background::Background()
{
    // Set the properties of the platform
    platform.setSize(sf::Vector2f(800.0f, 75.0f));
    platform.setFillColor(sf::Color(255, 128, 191)); // Set the color of the platform (pinkish)
    platform.setPosition(0.0f, 525.0f); // Set the position of the platform (x=0, y=525)
}

// Implementation of the draw function
void Background::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color(128, 223, 255)); // Clear the window with a custom sky color
    window.draw(platform); // Draw the platform on top of the sky
}

// Destructor implementation (empty in this case, but could be defined if needed)
Background::~Background()
{
}
