#pragma once
#include <SFML/Graphics.hpp>
#include "Input.h"
class GameObject : public sf::RectangleShape
{
public:
	GameObject();
	~GameObject();

	virtual void handleInput(float dt);
	virtual void update(float dt);

	void setInput(Input* in);

	void setVelocity(sf::Vector2f vel);
	void setVelocity(float vx, float vy);
	sf::Vector2f getVelocity();

	sf::FloatRect getCollisionBox();
	void setCollisionBox(sf::FloatRect collision_box);

protected:
	Input* input;

private:
	sf::Vector2f velocity;
	sf::FloatRect collisionBox;
};