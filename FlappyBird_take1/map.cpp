#include "map.h"
#include <iostream>
#include <sstream>


Map::Map()
{
	BACKGROUND.loadFromFile("data/background.png");
	PIPETEXTURE.loadFromFile("data/pipe.png");
	GROUND.loadFromFile("data/ground.png");
	ENEMYTEXURE.loadFromFile("data/enemyT.png");

	groundSprite[0].setTexture(GROUND);
	groundSprite[1].setTexture(GROUND);

	groundSprite[0].setPosition(0, 300);
	groundSprite[1].setPosition(384, 300);

	spacing = 160;
	verticalSpacing = 120;
	speed = 3;
	
	for (int i = 0; i < 3; i++)
	{
		collectedPoint[i] = false;
		y = rand() % 240 - 300;

		pipeTopSprite[i].setTexture(PIPETEXTURE);
		pipeBottomSprite[i].setTexture(PIPETEXTURE);
		enemySprite[i].setTexture(ENEMYTEXURE);

		pipeTopSprite[i].setPosition(300 + i * spacing, y);
		pipeBottomSprite[i].setPosition(300 + i * spacing, y + 300 + verticalSpacing);
		enemySprite[i].setPosition(300 + i * spacing, y + 300 + (verticalSpacing / 2));
	}

	backgroundSprite.setTexture(BACKGROUND);
}

Map::~Map()
{

}

void Map::draw(sf::RenderWindow &window)
{
	window.draw(backgroundSprite);

	for (int i = 0; i < 3; i++)
	{
		window.draw(pipeTopSprite[i]);
	}

	for (int i = 0; i < 3; i++)
	{
		window.draw(pipeBottomSprite[i]);
	}

	for (int i = 0; i < 3; i++)
	{
		window.draw(enemySprite[i]);
	}

	window.draw(groundSprite[0]);
	window.draw(groundSprite[1]);
}

void Map::positionPipes(int count)
{
	y = rand() % 230 - 300;

	pipeTopSprite[count].setPosition(300 + spacing - 20, y);
	pipeBottomSprite[count].setPosition(300 + spacing - 20, y + 300 + verticalSpacing);
	enemySprite[count].setPosition(300 + spacing - 20, y + 300 + (verticalSpacing / 2));
}

bool Map::update(sf::FloatRect bulletBB, sf::Sprite bullet)
{
	for (int i = 0; i < 3; i++)
	{
		if (bulletBB.intersects(pipeBottomBB[i]) ||
			bulletBB.intersects(pipeTopBB[i]))
		{

			return true;
		}
		if (bulletBB.intersects(enemyBB[i]))
		{
			enemySprite[i].setPosition(490, 490);
			return true;
		}
		
	}
	
}

bool Map::update(sf::FloatRect playerBB, int &score)
{
	groundSprite[0].move(-speed, 0);
	groundSprite[1].move(-speed, 0);

	if (groundSprite[0].getPosition().x < -384)
		groundSprite[0].setPosition(380, 300);
	else if (groundSprite[1].getPosition().x < -384)
		groundSprite[1].setPosition(380, 300);

	for (int i = 0; i < 3; i++)
	{
		pipeTopSprite[i].move(-speed, 0);
		pipeBottomSprite[i].move(-speed, 0);
		enemySprite[i].move(-speed, 0);

		pipeTopBB[i] = pipeTopSprite[i].getGlobalBounds();
		pipeBottomBB[i] = pipeBottomSprite[i].getGlobalBounds();
		enemyBB[i] = enemySprite[i].getGlobalBounds();
			
		if (pipeTopSprite[i].getPosition().x < 50 && !collectedPoint[i])
		{
			score++;
			collectedPoint[i] = true;
		}


		if (playerBB.intersects(pipeTopBB[i]) ||
			playerBB.intersects(pipeBottomBB[i]) ||
			playerBB.intersects(enemyBB[i]))
		{
			return true;
		}

		if (pipeTopSprite[i].getPosition().x < -48)
		{
			positionPipes(i);
			collectedPoint[i] = false;
		}
	}

	return false;
}
