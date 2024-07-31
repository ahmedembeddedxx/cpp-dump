#pragma once
#include "Gameobject.h"

template <typename T>
T SRand(T i, T j) {
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<float> dist(i, j);
	return dist(mt);
}


char Gameobject::gamestatus = 's';

Gameobject::Gameobject()
{
}

void Gameobject::callgameend()
{
	gamestatus = 'e';
}

Gameobject::~Gameobject()
{
}
