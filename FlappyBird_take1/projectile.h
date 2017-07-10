/*

#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>

#ifndef PROJECTILE_H
#define PROJECTILE_H

// We make the Projectile class inherite from sf::Sprite
class Projectile : public sf::Sprite
{
	sf::Sprite Bullet;  // Projectile became itself a sf::Sprite, we don't need to create another sprite anymore.

	bool BulletState;

	float BulletSpeed;

public:


	Projectile();  // In the default constructor, we'll call for the default constructor of sf::Sprite
	~Projectile();
	Projectile(sf::Image &image, sf::Vector2f &position, float speed);  // In this constructor, we'ell call for the sf::Sprite constructor and pass to it the &image and the &position.

	void SetDirection(sf::Vector2f &target);  // The direction to a target is still interresting, but with an angle, you don't need anymore to have a SetDirection(float angle) function, you can use the sf::Sprite::SetRotation(float rotation).

											  //  Functions bellow are still needed
	void SetSpeed(float);

	void Destroy(bool);

	bool IsDestroyed();

	void Calculate(sf::RenderWindow &app);

};

#endif
*/