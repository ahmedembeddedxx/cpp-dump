#ifndef CLASSES_H
#define CLASSES_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <windows.h>   
#include <vector>
#include <thread>
#include <random>
#include <iomanip>
#include <conio.h>
using namespace std;
using namespace sf;



class GameObject
{
protected:
	Vector2f deploy_position;
	static char GameStatus;

public:
	GameObject(Vector2f deploy_position);
	Vector2f getdeploy_position();
	virtual void draw(RenderWindow& window) = 0;
	char getGameStatus();
	virtual ~GameObject();
};

class Static : public GameObject
{
public:
	Static(int CoorX, int CoorY);
	~Static();
};

class Dynamic : public GameObject
{
protected:
	float velocity;
	Vector2f end_position;

public:
	Vector2f getend_position();
	virtual void move() = 0;
	Dynamic(int CoorX, int CoorY, float velocity);
	virtual ~Dynamic();
};

class Texts : public Static
{
	Font font;
	Text text;
	int score;

public:
	Texts();
	void draw(RenderWindow& window);
	void update();
	void addscore(int counter);
	~Texts();
};

class Background : public Static
{
	Texture skyTexture, mountainsTexture, platformTexture;
	Sprite skySprite, mountainsSprite, platformSprite;

public:
	Background();
	void draw(RenderWindow& window);
	~Background();
};

class Fireball : public Dynamic
{
	Texture fireballTexture;
	Sprite fireballSprite;
	static int counter;

public:
	Fireball(float velocity = 0.30);
	void move();
	void draw(RenderWindow& window);
	int getcounter();
	~Fireball();
};

class Hero : public Dynamic
{
	Texture heroTexture;
	Sprite heroSprite;
	char movement = 'i';
	bool face = 0;

public:
	Hero(float velocity = 10);
	void animate(RenderWindow& window);
	void draw(RenderWindow& window);
	void move();
	void setmovement(int i);
	~Hero();
};

class GameRun
{
	Hero H;
	Background B;
	Texts T;
	Fireball F1, F2, F3, F4;

	void processEvents(RenderWindow& window);
	bool collision(const Vector2f& lt1, const Vector2f& br1, const Vector2f& lt2, const Vector2f& br2);

public:
	GameRun();
	void run();
	~GameRun();
};

#endif // CLASSES_H
