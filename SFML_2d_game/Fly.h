#pragma once
#include "AnimatedSprite.h"
#include "Spaceship.h"
class Fly :public AnimatedSprite
{
public:
	Vector2f fly_velocity;
	bool is_chasing = false;
	void chasing(const Spaceship& spaceship);
	Fly(const Texture& texture,const Vector2f &position, const IntRect& choose_sprite);

};

