#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>
#include <Windows.h>

#include "map.cpp"
#include <time.h>

int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(300, 348), "Flappy Shooty");
	sf::Vector2i localPosition = sf::Mouse::getPosition(window);

	sf::Image icon;
	icon.loadFromFile("data/icon.png");
	window.setIcon(32, 19, icon.getPixelsPtr());

	window.setFramerateLimit(30);
	sf::Event event;

	Map *map;
	map = new Map;

	sf::Texture CATETEXTURE;
	sf::FloatRect cateBoundBox;

	sf::Texture BULLETTEXTURE;
	sf::FloatRect bulletBB;

	sf::Texture GETREADY;
	GETREADY.loadFromFile("data/getready.png");
	GETREADY.setSmooth(true);

	sf::Sprite getReadySprite;
	getReadySprite.setTexture(GETREADY);
	getReadySprite.setPosition(81, 50);

	bool readyUp = true;

	sf::Font font;
	font.loadFromFile("data/visitor.ttf");

	sf::Text score;
	score.setFont(font);
	score.setPosition(138, 0);
	score.setCharacterSize(48);
	score.setFillColor(sf::Color::Black);

	sf::Text credits;
	credits.setFont(font);
	credits.setPosition(50, 320);
	credits.setCharacterSize(20);
	credits.setFillColor(sf::Color::Black);
	credits.setString("El Penny");

	std::string scoreStr;
	int scoreInt = 0;

	CATETEXTURE.loadFromFile("data/cateSS.png");

	sf::Sprite flappyCate;
	float velY = 2;
	float rotateAmount = 0;

	sf::IntRect animation1 = sf::IntRect(0, 0, 50, 29);
	sf::IntRect animation2 = sf::IntRect(50, 0, 50, 29);

	bool keyPressed = false;
	bool alive = true;

	flappyCate.setPosition(50, 50);
	flappyCate.setScale(0.6, 0.6);
	flappyCate.setTexture(CATETEXTURE);
	flappyCate.setTextureRect(animation1);
	

	BULLETTEXTURE.loadFromFile("data/bullet.png");
	sf::Sprite bulletSprite;
	//bulletSprite.setPosition(flappyCate.getPosition());
	bulletSprite.setPosition(500,500);
	bulletSprite.setTexture(BULLETTEXTURE);
	



	sf::Clock clock;
	sf::Time animationTime;

	while (window.isOpen())
	{
		bulletBB = sf::FloatRect(bulletSprite.getPosition().x, bulletSprite.getPosition().y, 30, 30);
		
		cateBoundBox = sf::FloatRect(flappyCate.getPosition().x, flappyCate.getPosition().y, 20, 22);
		localPosition = sf::Mouse::getPosition(window);
		score.setString(scoreStr);

		animationTime = clock.getElapsedTime();

		std::ostringstream convert;
		convert << scoreInt;

		scoreStr = convert.str();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				return 0;
			}

			if (event.key.code == sf::Keyboard::Escape)
			{
				return 0;
			}
		}

		if (!readyUp)
		{
			bulletSprite.move(10, 0);
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::E)
				|| (sf::Mouse::isButtonPressed(sf::Mouse::Right))) && !keyPressed
				&& flappyCate.getPosition().y > 0)
			{
				bulletSprite.setPosition(flappyCate.getPosition().x+5,flappyCate.getPosition().y+8);
				
			}
			else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E)
				&& !(sf::Mouse::isButtonPressed(sf::Mouse::Right)))


			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
				|| (sf::Mouse::isButtonPressed(sf::Mouse::Left))) && !keyPressed
				&& flappyCate.getPosition().y > 0)
			{
				velY -= velY + 10;
				rotateAmount -= rotateAmount + 10;
				keyPressed = true;
			}
			else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
				&& !(sf::Mouse::isButtonPressed(sf::Mouse::Left)))
				keyPressed = false;
		}
		else
		{
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
				|| (sf::Mouse::isButtonPressed(sf::Mouse::Left))) && !keyPressed)
			{
				scoreInt = 0;
				alive = true;
				readyUp = false;
			}
			else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
				&& !(sf::Mouse::isButtonPressed(sf::Mouse::Left)))
				keyPressed = false;
		}

		if (velY < 20 && !readyUp)
			velY++;

		if (rotateAmount < 70 && !readyUp)
			rotateAmount++;

		if (!readyUp)
			flappyCate.move(0, velY);

		flappyCate.setRotation(rotateAmount);

		if (animationTime.asSeconds() > 0.2)
		{
			if (animation1 == flappyCate.getTextureRect())
				flappyCate.setTextureRect(animation2);
			else
				flappyCate.setTextureRect(animation1);

			clock.restart();
		}

		window.clear();
		map->draw(window);
		window.draw(flappyCate);
		window.draw(bulletSprite);
		
		if (!readyUp && alive)
		{
			if (map->update(bulletBB, bulletSprite))
			{
				
			}
			if (map->update(cateBoundBox, scoreInt))
			{
				alive = false;
			}

			if (flappyCate.getPosition().y > 295)
			{
				alive = false;
			}
		}

		if (!alive)
		{
			delete map;
			map = new Map;

			flappyCate.setPosition(50, 50);
			flappyCate.setRotation(0);
			velY = 2;

			sf::sleep(sf::seconds(0.2));
			readyUp = true;
			alive = true;
		}

		if (readyUp)
		{
			window.draw(getReadySprite);
			window.draw(credits);
		}


		window.draw(score);
		window.display();
	}

	return 0;
}
