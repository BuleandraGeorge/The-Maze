#pragma once
#include "GameObject.h"
class Bullet : public GameObject
{
private:
	char direction; //!< direction of the bullet
	bool isOutOfMap(); //!< tests if the bullet is outside of the map
public:
	Bullet(std::shared_ptr<sf::Texture> shr_ptr_texture, char dir, std::shared_ptr<sf::Vector2f> init); //!< creates the bullet with traveling details
	bool distroyBullet(std::vector<std::vector<std::shared_ptr<GameObject>>> objects); //!< checks if the live of the bullet is over
	void moveBullet();  //!< moves the bullet
	
};