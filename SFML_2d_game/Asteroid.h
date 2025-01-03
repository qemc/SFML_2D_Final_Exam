#pragma once
#include "AnimatedSprite.h"

class Asteroid :public AnimatedSprite
{
public:
	Vector2f a_velocity;
	Asteroid(const Texture& texture, const Vector2f& position);
	void a_move();

};

