//cpp
#include <iostream>
//sfml
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "AnimatedSprite.h"
#include "Asteroid.h"
#include "Fly.h"

using namespace std;
using namespace sf;


Vector2f randomize_corner() {
	if (rand() % 100 <= 25) { return Vector2f(0, 0); }
	if (rand() % 100 <= 50) { return Vector2f(650, 0); }
	if (rand() % 100 <= 75) { return Vector2f(0, 725); }
	if (rand() % 100 <= 100) { return Vector2f(650, 725); }

}




int main() {

	srand(time(NULL));
	bool restart = false;
	Clock clock_r;

	
while (true) {

		//clocks
		Clock a_clock;
		Clock r_clock;

	
		Clock clock_p;
		Clock clock_h;
		Clock clock_w;
		Clock clock_q;

		//rectangle
		RectangleShape rectangle;
		rectangle.setFillColor(Color::Cyan);
		rectangle.setSize(Vector2f(150, 75));
		rectangle.setPosition(randomize_corner());


		//window /events

		RenderWindow window(VideoMode(800, 800), "sfml - spaceship");
		window.setFramerateLimit(60);
		Event event;
		bool game = true;
		bool is_paused = false;

		//spaceship
		Texture s_texture;
		s_texture.loadFromFile("images/spaceship.png");

		Spaceship spaceship(s_texture);
		//fly
		Texture f_texture;
		f_texture.loadFromFile("images/fly.png");
		IntRect sourceSprite(0, 0, 32, 32);
		float choose_sprite = 32;

		//asteroid 
		Texture a_texture;
		a_texture.loadFromFile("images/asteroid.png");


		vector<unique_ptr<Sprite>> some_space_bugs;



		//asteroids implementation
		for (int i = 0; i < 15; i++) {

			Vector2f position(rand() % (window.getSize().x - 100), (rand() % (window.getSize().y - 100)) + i * 10);
			some_space_bugs.emplace_back(make_unique<Asteroid>(Asteroid(a_texture, position)));


		}

		// fly implementation
		for (int i = 0; i < 5; i++) {
			srand(time(NULL));

			Vector2f position(rand() % (window.getSize().x - 100), (rand() % (window.getSize().y - 100)) + i * 10);
			some_space_bugs.emplace_back(make_unique<Fly>(Fly(f_texture, position, sourceSprite)));

		}

		// some_space_bugs position randomizer v1

		for (int i = 0; i < some_space_bugs.size(); i++) {

			Sprite& some_shape = dynamic_cast<Sprite&>(*some_space_bugs[i].get());

			if (spaceship.getGlobalBounds().intersects(some_shape.getGlobalBounds())) {

				while (spaceship.getGlobalBounds().intersects(some_shape.getGlobalBounds())) {

					Vector2f position(rand() % (window.getSize().x - 100), (rand() % (window.getSize().y - 100)) + i * 10);

					some_shape.setPosition(position);

				}
			}

		}




		// some_space_bugs position randomizer v2
		for (int i = 0; i < some_space_bugs.size(); i++) {

			Sprite& some_shape = dynamic_cast<Sprite&>(*some_space_bugs[i].get());

			for (int j = 0; j < some_space_bugs.size(); j++) {

				Sprite& some_shape2 = dynamic_cast<Sprite&>(*some_space_bugs[j].get());

				if (some_shape.getGlobalBounds().intersects(some_shape2.getGlobalBounds()) && j != i) {

					while (some_shape.getGlobalBounds().intersects(some_shape2.getGlobalBounds())) {

						Vector2f position(rand() % (window.getSize().x - 100), (rand() % (window.getSize().y - 100)) + i * 10);

						some_shape.setPosition(position);

					}
				}
			}
		}



		Vector2f mouse;



		while (window.isOpen()) {


			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window.close();
					break;
				}
			}

			while (game == true && is_paused == false) {



				while (window.pollEvent(event)) {
					if (event.type == Event::Closed) {
						window.close();
						break;
					}
				}


				window.clear();

				if (Mouse::isButtonPressed(Mouse::Left)) {
					spaceship.rusz = true;
					spaceship.mouse_pos = window.mapPixelToCoords(Mouse::getPosition(window));
					mouse = window.mapPixelToCoords(Mouse::getPosition(window));


				}


				//DRAWING SECTION

				for (const auto& s : some_space_bugs) {

					AnimatedSprite& some_shape = dynamic_cast<AnimatedSprite&>(*s.get());
					if (some_shape.getScale().y == 1) {
						if (a_clock.getElapsedTime().asSeconds() > 0.25) {

							sourceSprite.left = choose_sprite;
							choose_sprite += 32;


							for (const auto& g : some_space_bugs) {
								Sprite& some_shape = dynamic_cast<Sprite&>(*g.get());
								if (some_shape.getScale().y == 1) {
									some_shape.setTextureRect(sourceSprite);
								}
							}
							if (choose_sprite == 512) {
								choose_sprite = 32;
							}
							a_clock.restart();


						}
						Fly& some_fly = dynamic_cast<Fly&>(*s.get());
						some_fly.chasing(spaceship);


					}
					else {
						Asteroid& some_asteroid = dynamic_cast<Asteroid&>(*s.get());
						some_asteroid.a_move();

					}

					window.draw(*s);

				}



				for (auto itr = some_space_bugs.begin(); itr != some_space_bugs.end();) {
					AnimatedSprite& some_sprite = dynamic_cast<AnimatedSprite&>(*itr->get());
					if (spaceship.getGlobalBounds().intersects(some_sprite.getGlobalBounds())) {

						if (some_sprite.getScale().y == 1) {
							spaceship.hp = spaceship.hp - 30;
							Vector2f position(rand() % (window.getSize().x - 100), (rand() % (window.getSize().y - 100)));
							some_space_bugs.emplace_back(make_unique<Fly>(Fly(f_texture, position, sourceSprite)));
						}
						else {
							spaceship.hp = spaceship.hp - 10;
							Vector2f position(rand() % (window.getSize().x - 100), (rand() % (window.getSize().y - 100)));
							some_space_bugs.emplace_back(make_unique<Asteroid>(Asteroid(a_texture, position)));

						}
						itr = some_space_bugs.erase(itr);
					}
					else {
						++itr;
					}
				}




				if (r_clock.getElapsedTime().asSeconds() > 5 || rectangle.getGlobalBounds().intersects(spaceship.getGlobalBounds()))
				{
					rectangle.setPosition(randomize_corner());
					r_clock.restart();
					spaceship.points++;
				}

				window.draw(rectangle);
				spaceship.s_move();
				spaceship.set_hp();
				window.draw(spaceship.hp_r);
				window.draw(spaceship);
				window.display();

				if (spaceship.hp <= 0) {
					cout << "PRZEGRANA" << endl;
					game = false;
					window.clear();
					break;
				}
				if (spaceship.points == 4) {
					cout << "WYGRANA" << endl;
					game = false;
					window.clear();
					break;

				}

				if (Keyboard::isKeyPressed(Keyboard::Key::W) && clock_h.getElapsedTime().asSeconds() > 0.5) {
					spaceship.hp += 10;
					clock_h.restart();
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::E) && clock_r.getElapsedTime().asSeconds() > 1) {
					game = false;
					is_paused = true;
					clock_r.restart();
					break;
				}
				if (Keyboard::isKeyPressed(Keyboard::Key::Q) && clock_q.getElapsedTime().asSeconds() > 1) {
					
					restart = true;
					clock_q.restart();
					window.clear();
					break;
				}

			}

			if (Keyboard::isKeyPressed(Keyboard::Key::E) && clock_r.getElapsedTime().asSeconds() > 1) {
				game = true;
				is_paused = false;

				clock_r.restart();
			}
			if (Keyboard::isKeyPressed(Keyboard::Key::Q)) {
				break;


			}

		}

		

	}
	return 0;
}