#include "Player.h"

int Player::idCounter = 0;

Player::Player(std::string name)
{
	this->id = Player::idCounter++;
	this->name = name;
}

Player::Player(const Player &other)
{
	this->id = other.id;
	this->name = other.name;
}

Player::~Player()
{

}

void Player::ResetIdIndexing()
{
	Player::idCounter = 0;
}

int Player::GetId() const
{
	return id;
}

std::string Player::GetName() const
{
	return name;
}