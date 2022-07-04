#pragma once
#include "NPC.h"
class TriggerTurret : public NPC
{
private:
	const int ui_shootDelay = 1000; //!< activation delay of the turret
	unsigned int ui_LastTimeShoot=0;//!< timestamp for last time fired
	unsigned int IDTrigger;//!< trigger's id which activates it
public:
	TriggerTurret(std::shared_ptr<sf::Texture> shr_ptr_texture, std::shared_ptr<sf::Vector2f> objectPos, unsigned char direction, unsigned int triggerID); //!< creates a turret with a particular trigger position
	bool trigger(); //!< checks if the shooting delay is over
	unsigned int getTriggerID(); //!< returns the trigger's id
};
