#include "Spaceship.h"

Vector2f normalize(const Vector2f& x, const Vector2f& y) {

	Vector2f all(abs(x.x - y.x), abs(x.y - y.y));


	float sqr = sqrt(((y.x - x.x) * (y.x - x.x)) + (y.y - x.y) * (y.y - x.y));

	return Vector2f(all.x / sqr, all.y / sqr);


}



Spaceship::Spaceship(const Texture& texture){

	setTexture(texture);
	setScale(0.125, 0.125);
	setPosition(384, 384);


}


void Spaceship::s_move() {


	if (getPosition().x >= 800) {
		setPosition(0, getPosition().y);
	}

	if (getPosition().x + getGlobalBounds().height <= 0) {
		setPosition(800, getPosition().y);

	}
	if (getPosition().y >= 800) {
		setPosition(getPosition().x, 0);
	}
	if (getPosition().y + getGlobalBounds().height < 0) {
		setPosition(getPosition().x, 800);
	}

		if (rusz == true) {

		if (mouse_pos.x < getPosition().x && mouse_pos.y < getPosition().y) {
			move(movement);
			movement.x = -5 * normalize(mouse_pos, getPosition()).x;
			movement.y = -5 * normalize(mouse_pos, getPosition()).y;

		}
		else
		if (mouse_pos.x > getPosition().x && mouse_pos.y < getPosition().y) {
			move(movement);
			movement.x = 5 * normalize(mouse_pos, getPosition()).x;
			movement.y = -5 * normalize(mouse_pos, getPosition()).y;
		}
		else
		if (mouse_pos.x < getPosition().x && mouse_pos.y > getPosition().y) {
			move(movement);
			movement.x = -5 * normalize(mouse_pos, getPosition()).x;
			movement.y = 5 * normalize(mouse_pos, getPosition()).y;

		}
		else
		if (mouse_pos.x > getPosition().x && mouse_pos.y > getPosition().y) {
			move(movement);
			movement.x = 5 * normalize(mouse_pos, getPosition()).x;
			movement.y = 5 * normalize(mouse_pos, getPosition()).y;
		}
		else {
			move(movement);
			movement.x = 0 * normalize(mouse_pos, getPosition()).x;
			movement.y = 0 * normalize(mouse_pos, getPosition()).y;
		}
	}


}

void Spaceship::set_hp() {

	hp_r.setFillColor(Color::Green);
	hp_r.setPosition(0, 790);
	hp_r.setSize(Vector2f((800 * hp) / 100, 10));

}