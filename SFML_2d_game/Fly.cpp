#include "Fly.h"

Vector2f norm(const Vector2f& x, const Vector2f& y) {

	Vector2f all(abs(x.x - y.x), abs(x.y - y.y));


	float sqr = sqrt(((y.x - x.x) * (y.x - x.x)) + (y.y - x.y) * (y.y - x.y));

	return Vector2f(all.x / sqr, all.y / sqr);


}



Fly::Fly(const Texture& texture, const Vector2f& position, const IntRect& choose_sprite) {

	setPosition(position);
	setTexture(texture);
	setTextureRect(choose_sprite);
	setOrigin(16, 16);

	uniform_int_distribution<int> random_int(-2, 2);
	random_device rd;
	mt19937 randomNumbers(rd());

	fly_velocity.x = random_int(randomNumbers);
	fly_velocity.y = random_int(randomNumbers);

	uniform_int_distribution<int> random_int2(0, 100);
	random_device rd2;
	mt19937 randomNumbers2(rd2());
	if (random_int2(randomNumbers2) < 50) {
		is_chasing = true;

	}


}



void Fly::chasing(const Spaceship& spaceship) {




	if (is_chasing == true) {

		setColor(Color::Red);

		if (spaceship.getPosition().x < this->getPosition().x && spaceship.getPosition().y < this->getPosition().y) {

			fly_velocity.x = -1 * norm(spaceship.getPosition(), this->getPosition()).x;
			fly_velocity.y = -1 * norm(spaceship.getPosition(), this->getPosition()).y;

		}

		if (spaceship.getPosition().x > this->getPosition().x && spaceship.getPosition().y < this->getPosition().y) {

			fly_velocity.x = 1 * norm(spaceship.getPosition(), this->getPosition()).x;
			fly_velocity.y = -1 * norm(spaceship.getPosition(), this->getPosition()).y;

		}

		if (spaceship.getPosition().x < this->getPosition().x && spaceship.getPosition().y > this->getPosition().y) {

			fly_velocity.x = -1 * norm(spaceship.getPosition(), this->getPosition()).x;
			fly_velocity.y = 1 * norm(spaceship.getPosition(), this->getPosition()).y;

		}

		if (spaceship.getPosition().x > this->getPosition().x && spaceship.getPosition().y > this->getPosition().y) {

			fly_velocity.x = 1 * norm(spaceship.getPosition(), this->getPosition()).x;
			fly_velocity.y = 1 * norm(spaceship.getPosition(), this->getPosition()).y;
		}

		move(fly_velocity.x, fly_velocity.y);

	}




}
