#include "Classes.h"

int SRand() {
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> dist(40, 340);
	return dist(mt);
}

char GameObject::GameStatus = 'p';

GameObject::GameObject(Vector2f deploy_position) : deploy_position(deploy_position) {}

Vector2f GameObject::getdeploy_position()
{
	return deploy_position;
}

char GameObject::getGameStatus()
{
	return GameStatus;
}

GameObject::~GameObject() {}

Static::Static(int CoorX, int CoorY) : GameObject(Vector2f(CoorX, CoorY)) {}

Static::~Static() {}

Dynamic::Dynamic(int CoorX, int CoorY, float velocity) : GameObject(Vector2f(CoorX, CoorY)), velocity(velocity) {}

Vector2f Dynamic::getend_position()
{
	return end_position;
}

Dynamic::~Dynamic() {}

Texts::Texts() : Static(5, 5)
{
	score = 0;
	font.loadFromFile("monospace.ttf");
	text.setFont(font);
	text.setCharacterSize(10);
	text.setPosition(deploy_position);
	text.setFillColor(Color::White);
}

void Texts::draw(RenderWindow& window)
{
	if (GameStatus != 'e')
		text.setString("Score:" + to_string(score) + "\nSPACE->Continue/Pause\nESC->Exit");

	window.draw(text);
}

void Texts::update()
{
	text.setPosition(75, 50);
	text.setCharacterSize(40);
	text.setFillColor(Color::White);
	text.setString("Score:" + to_string(score) + "\nGAME OVER\nESC->Exit");
}

void Texts::addscore(int counter)
{
	this->score = (counter * 10);
}

Texts::~Texts() {}

Background::Background() : Static(0, 0)
{
	skyTexture.loadFromFile("background.png");
	mountainsTexture.loadFromFile("mountains.png");
	platformTexture.loadFromFile("platform.png");

	skySprite.setTexture(skyTexture);
	mountainsSprite.setTexture(mountainsTexture);
	platformSprite.setTexture(platformTexture);
}

void Background::draw(RenderWindow& window)
{
	window.draw(skySprite);
	mountainsSprite.setPosition(0, 50);
	window.draw(mountainsSprite);
	mountainsSprite.setPosition(192, 50);
	window.draw(mountainsSprite);
	window.draw(platformSprite);
}

Background::~Background() {}

int Fireball::counter = 0;

Fireball::Fireball(float velocity) : Dynamic(SRand(), 0, velocity)
{
	if (SRand() % 2)
		fireballTexture.loadFromFile("fireball1.png");
	else
		fireballTexture.loadFromFile("fireball2.png");
	fireballSprite.setTexture(fireballTexture);
}

void Fireball::move()
{
	if (GameStatus == 'c')
	{
		if (deploy_position.y >= 150)
		{
			deploy_position.y = 0;
			deploy_position.x = SRand();
			counter++;
			end_position.x = deploy_position.x + 35;
			end_position.y = deploy_position.y + 42;
		}
		else
		{
			deploy_position.y += velocity;
			end_position.x = deploy_position.x + 35;
			end_position.y = deploy_position.y + 42;
		}
	}
}

void Fireball::draw(RenderWindow& window)
{
	fireballSprite.setPosition(deploy_position);
	if (static_cast<int>(deploy_position.x) % 2)
		fireballTexture.loadFromFile("fireball1.png");
	else
		fireballTexture.loadFromFile("fireball2.png");
	window.draw(fireballSprite);
}

int Fireball::getcounter()
{
	if (GameStatus == 'e')
	{
		GameStatus = 'p';
		counter = 0;
	}
	return counter;
}

Fireball::~Fireball() {}

Hero::Hero(float velocity) : Dynamic(10, 150, velocity)
{
	heroTexture.loadFromFile("hero-idle-r.png");
	heroSprite.setTexture(heroTexture);
}

void Hero::animate(RenderWindow& window)
{
	for (int i = 0; i < 150; i += 3)
	{
		Background B;
		deploy_position.y = i;
		heroSprite.setPosition(deploy_position);
		B.draw(window);
		this->draw(window);
		window.display();

		Sleep(1);
	}
}

void Hero::draw(RenderWindow& window)
{
	heroSprite.setPosition(deploy_position);

	if (face == 0)
		heroTexture.loadFromFile("hero-idle-r.png");
	else if (face == 1)
		heroTexture.loadFromFile("hero-idle-l.png");
	if (GameStatus == 'e')
		heroTexture.loadFromFile("hero-crouch.png");
	else if (GameStatus == 'p')
		heroTexture.loadFromFile("hero-hurt.png");

	window.draw(heroSprite);
}

void Hero::move()
{
	if (GameStatus == 'c')
	{
		if (movement == 'r' && deploy_position.x < 310)
		{
			deploy_position.x += velocity;
			face = 0;
			end_position.x = deploy_position.x + 41;
			end_position.y = deploy_position.y + 44;
		}
		else if (movement == 'l' && deploy_position.x > 20)
		{
			deploy_position.x -= velocity;
			face = 1;
			end_position.x = deploy_position.x + 41;
			end_position.y = deploy_position.y + 44;
		}
		movement = 'i';
	}
}

void Hero::setmovement(int i)
{
	if (i == 77)
		movement = 'r';
	else if (i == 75)
		movement = 'l';
	else if (i == 101)
		GameStatus = 'e';
	else if (i == 100 && GameStatus == 'p')
		GameStatus = 'c';
	else if (i == 100 && GameStatus == 'c')
		GameStatus = 'p';
	else
		movement = 'i';
}

Hero::~Hero() {}

GameRun::GameRun() : F1(0.1), F2(0.2), F3(0.3), F4(0.4) {}

void GameRun::processEvents(RenderWindow& window)
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
		else if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Left)
				H.setmovement(75);
			else if (event.key.code == Keyboard::Right)
				H.setmovement(77);
			else if (event.key.code == Keyboard::Space)
				H.setmovement(100);
			else if (event.key.code == Keyboard::Escape)
				window.close();
		}
	}
}

bool GameRun::collision(const Vector2f& lt1, const Vector2f& br1, const Vector2f& lt2, const Vector2f& br2)
{
	bool yOverlap = (lt1.y <= br2.y) && (lt2.y <= br1.y);
	if (!yOverlap || abs(lt1.y - br2.y) < 10 || abs(lt2.y - br1.y) < 10)
	{
		return false;
	}
	bool xOverlap = (lt1.x <= br2.x) && (lt2.x <= br1.x);
	return xOverlap && yOverlap;
}

void GameRun::run()
{
	RenderWindow window(VideoMode(384, 224), "Flame Dodge-Developed in SFML/C++");
	H.animate(window);
	while (window.isOpen())
	{
		processEvents(window);

		B.draw(window);
		F1.draw(window);
		F2.draw(window);
		F3.draw(window);
		F4.draw(window);
		if (collision(H.getdeploy_position(), H.getend_position(), F1.getdeploy_position(), F1.getend_position()) ||
			collision(H.getdeploy_position(), H.getend_position(), F2.getdeploy_position(), F2.getend_position()) ||
			collision(H.getdeploy_position(), H.getend_position(), F3.getdeploy_position(), F3.getend_position()) ||
			collision(H.getdeploy_position(), H.getend_position(), F4.getdeploy_position(), F4.getend_position()))
		{
			H.setmovement(101);
			H.draw(window);
			T.update();
			T.draw(window);
			window.display();
			continue;
		}

		T.draw(window);
		T.addscore(F1.getcounter());

		F1.move();
		F2.move();
		F3.move();
		F4.move();
		H.draw(window);
		H.move();
		window.display();
	}
}

GameRun::~GameRun() {}
