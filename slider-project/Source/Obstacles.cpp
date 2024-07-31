#pragma once
#include "Obstacles.h"

// Function to generate a random number between min and max (inclusive)

// Constructor
Obstacle::Obstacle() {
    initShape();
}

// Function to initialize the shape (circle or rectangle) randomly
void Obstacle::initShape() {
    if (SRand(0, 100) % 2) {
        myShape = &R;                     // Upcasting: RectangleShape upcasted to Shape*
        dynamic_cast<RectangleShape*>(myShape)->setSize(Vector2f(SRand(30, 50), SRand(30, 50)));
    }
    else {
        myShape = &C;                     // Upcasting: CircleShape upcasted to Shape*
        dynamic_cast<CircleShape*>(myShape)->setRadius(SRand(18, 30));
    }
    myShape->setFillColor(Color(255, 0, SRand(0, 255)));
    myShape->setOutlineThickness(2);
    myShape->setOutlineColor(Color(0, 0, 0));
}

// Function to draw the obstacle on the window
void Obstacle::draw(RenderWindow& window) {
    window.draw(*myShape);
}

// Function to get the global bounds of the obstacle
FloatRect Obstacle::getGlobalBounds() {
    return myShape->getGlobalBounds();
}

// Function to set the position of the obstacle
void Obstacle::setPosition(int i, int j) {
    myShape->setPosition(i, j);
}

// Destructor
Obstacle::~Obstacle() {
}
