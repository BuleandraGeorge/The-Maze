#pragma once
#include "GameObject.h"

class Trigger :public GameObject
{
	unsigned int idTurret; //!< the id of the turret which triggers
	unsigned int id;//!< its id
public:
	Trigger(std::shared_ptr<sf::Texture> shr_ptr_texture, std::shared_ptr<sf::Vector2f>pos, unsigned int turretId); //!< describes the texture and position and the turrets id which fires
	bool linkTurret(unsigned int turretID, unsigned int turretIndex);//!< links the turret to the trigger and return true 
	unsigned int getIDTurret();//!< returns the index of the turret that activates
};

