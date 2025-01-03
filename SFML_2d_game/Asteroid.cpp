#include "Asteroid.h"


Asteroid::Asteroid(const Texture& texture, const Vector2f& position) {

	setPosition(position);
	setTexture(texture);
	setScale(0.125, 0.125);


	uniform_int_distribution<int> random_int(-2, 2);
	random_device rd;
	mt19937 randomNumbers(rd());

	a_velocity.x = random_int(randomNumbers);
	a_velocity.y = random_int(randomNumbers);

}

void Asteroid::a_move() {

	uniform_int_distribution<int> random_int(0, 800);
	random_device rd;
	mt19937 randomNumbers(rd());


	if (getPosition().x - getGlobalBounds().width >= 800) {
		setPosition(0, random_int(randomNumbers));
	}

	if (getPosition().x + getGlobalBounds().height <= 0) {
		setPosition(800, random_int(randomNumbers));

	}
	if (getPosition().y - getGlobalBounds().height >= 800) {
		setPosition(random_int(randomNumbers), 0);
	}
	if (getPosition().y + getGlobalBounds().height <= 0) {
		setPosition(random_int(randomNumbers), 800);
	}

	



	this->move(a_velocity);
}