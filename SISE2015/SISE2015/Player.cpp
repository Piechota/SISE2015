#include "Headers.h"

uint32_t Player::idCounter = 0;

Player::Player(const std::string& name, const Colour& color)
{
	id = Player::idCounter++;
	this->name = name;
	this->color = color;
}

Player::Player(const Player& other)
{
	id = other.id;
	name = other.name;
	color = other.color;
}

Player::~Player()
{

}

void Player::ResetIdIndexing()
{
	Player::idCounter = 0;
}

uint32_t Player::GetId() const
{
	return id;
}

const std::string& Player::GetName() const
{
	return name;
}

const Colour& Player::GetColor() const
{
	return color;
}