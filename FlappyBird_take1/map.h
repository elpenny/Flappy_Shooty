#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

#ifndef MAP_H
#define MAP_H


class Map
{
public:
	Map();
	~Map();

	void draw(sf::RenderWindow &window);

	bool update(sf::FloatRect playerBB, int &score);

	bool update(sf::FloatRect bulletBB, sf::Sprite bullet);

	void positionPipes(int pipe);

private:
	sf::Texture ENEMYTEXURE;
	sf::Texture PIPETEXTURE;
	sf::Sprite enemySprite[3];
	sf::Sprite pipeTopSprite[3];
	sf::Sprite pipeBottomSprite[3];

	bool collectedPoint[3];

	int spacing;
	int verticalSpacing;
	float speed;
	int y;

	sf::FloatRect pipeTopBB[3];
	sf::FloatRect pipeBottomBB[3];
	sf::FloatRect enemyBB[3];

	sf::Texture BACKGROUND;
	sf::Texture GROUND;

	sf::Sprite backgroundSprite;
	sf::Sprite groundSprite[2];


};

#endif // MAP_H

