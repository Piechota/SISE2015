#include "Player.h"

int Player::idCounter = 0;

Player::Player()
{
	this->id = Player::idCounter++;
}

Player::Player(const Player &other)
{
	this->id = other.id;
}

Player::~Player()
{

}

void Player::ResetIdIndexing()
{
	Player::idCounter;
}

int Player::GetId()
{
	return this->id;
}