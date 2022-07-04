#include "NPC.h"

NPC::NPC(std::shared_ptr<sf::Texture> shr_ptr_texture) :GameObject(shr_ptr_texture)
{
}
NPC::NPC(std::shared_ptr<sf::Texture> shr_ptr_texture, std::shared_ptr<sf::Vector2f> shr_ptr_objectPos) :GameObject(shr_ptr_texture, shr_ptr_objectPos)
	{
	}

void NPC::setShootingDetails(char direction, std::shared_ptr<sf::Vector2f> init)
{
	
	shootingDetails.direction = direction;
	shootingDetails.initPoint = init;
	ajustInitialPoint();
}
NPC::shootingSettings NPC::getShootingDetails()
{
	return shootingDetails;
}
void NPC::ajustInitialPoint()
{
	switch (shootingDetails.direction)
	{
	case 'u':
		shootingDetails.initPoint->y -= ajustValue;
		break;
	case 'd':
		shootingDetails.initPoint->y += ajustValue;
		break;
	case 'l':
		shootingDetails.initPoint->x -= ajustValue;
		break;
	case 'r':
		shootingDetails.initPoint->x += ajustValue;
		break;
	default:
		break;
	}
}