#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::handleInput(float dt)
{
}

void GameObject::update(float dt)
{
}

void GameObject::setInput(Input* in)
{
	input = in;
}

void GameObject::setVelocity(sf::Vector2f vel)
{
	velocity = vel;
}

void GameObject::setVelocity(float vx, float vy)
{
	velocity = sf::Vector2f(vx, vy);
}

sf::Vector2f GameObject::getVelocity()
{
	return velocity;
}

sf::FloatRect GameObject::getCollisionBox()
{
	return collisionBox;
}

void GameObject::setCollisionBox(sf::FloatRect collision_box)
{
	collisionBox = collision_box;
}
