#pragma once
#include "GameObject.h"
class Portal :public GameObject
{
public:
	Portal(std::shared_ptr<sf::Texture> shr_ptr_texture, std::shared_ptr<sf::Vector2f>pos);
	//!< describes the portal position and texture
};

