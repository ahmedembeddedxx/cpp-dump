#pragma once
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Hierarchy {
private:
    Texture texture;
    Sprite sprite;

public:
    // Constructor: loads the texture and sets it to the sprite
    Hierarchy();

    // Draws the sprite on the given RenderWindow
    void draw(RenderWindow& window);
    ~Hierarchy();
};
