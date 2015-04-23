#include "Headers.h"

uint32_t Player::idCounter = 0;

Player::Player(std::string name)
{
	id = Player::idCounter++;
	this->name = name;
}

Player::Player(const Player& other)
{
	id = other.id;
	name = other.name;
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

std::string Player::GetName() const
{
	return name;
}