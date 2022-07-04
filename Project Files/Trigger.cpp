#include "Trigger.h"
Trigger::Trigger(std::shared_ptr<sf::Texture> shr_ptr_texture, std::shared_ptr<sf::Vector2f>pos, unsigned int turretId) :GameObject(shr_ptr_texture, pos)
{
	id = turretId;
}
bool Trigger::linkTurret(unsigned int turretID, unsigned int turretIndex) {
	if (id == turretID)
	{
		idTurret = turretIndex;
		return true;
	}
	return false;
}
unsigned int Trigger::getIDTurret() {
	return idTurret;
}