#include "TriggerTurret.h"

TriggerTurret::TriggerTurret(std::shared_ptr<sf::Texture> shr_ptr_texture, std::shared_ptr<sf::Vector2f> objectPos, unsigned char direction, unsigned int id) :NPC(shr_ptr_texture,objectPos) {
	IDTrigger=id;
	setShootingDetails(direction, objectPos);
	ajustInitialPoint();
}
unsigned int TriggerTurret:: getTriggerID()
{
	return IDTrigger;
}
bool TriggerTurret::trigger()
{
	if (time.getElapsedTime().asMilliseconds() - ui_LastTimeShoot > ui_shootDelay)
	{
		ui_LastTimeShoot = time.getElapsedTime().asMilliseconds();
		return true;
	}
	return false;
}
