#include "player.h"

void Player::setName(std::string username) {
	this->username = username;
}

std::string Player::getName() {
	return this->username;
}
