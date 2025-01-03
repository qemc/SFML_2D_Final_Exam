#pragma once
#include "AnimatedSprite.h"

class Spaceship:public AnimatedSprite
{
public:

	Spaceship(const Texture& texture);
	bool rusz = false;
	Vector2f mouse_pos;
	Vector2f movement;
	void s_move();
	int hp = 100;
	int points = 0;

	RectangleShape hp_r;
	void set_hp();

};

