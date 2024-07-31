#pragma once
#include "Gameobject.cpp"

class Obstacle : public Gameobject {
    CircleShape C;            // CircleShape used for circle obstacle
    RectangleShape R;         // RectangleShape used for rectangle obstacle
    Shape* myShape;           // Pointer to the current shape (circle or rectangle)

public:
    Obstacle();               // Constructor
    void initShape();         // Function to initialize the shape
    void draw(RenderWindow& window);        // Function to draw the obstacle on the window
    FloatRect getGlobalBounds();            // Function to get the global bounds of the obstacle
    void setPosition(int i, int j);         // Function to set the position of the obstacle
    ~Obstacle();                            // Destructor
};