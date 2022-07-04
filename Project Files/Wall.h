#pragma once
#include "GameObject.h"

class Wall :public GameObject {

public:
	Wall(std::shared_ptr<sf::Texture> shr_ptr_texture, std::shared_ptr<sf::Vector2f>pos); //!< creates a wall with a particular position
};