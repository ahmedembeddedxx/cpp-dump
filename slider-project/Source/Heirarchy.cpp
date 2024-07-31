#pragma once
#include "Heirarchy.h"

// Constructor definition
Hierarchy::Hierarchy() {
    texture.loadFromFile("Heirarchy.png");
    sprite.setTexture(texture);
}

// draw function definition
void Hierarchy::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.display();
}

Hierarchy::~Hierarchy()
{
}