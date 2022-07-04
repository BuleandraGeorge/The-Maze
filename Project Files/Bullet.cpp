#include "Bullet.h"



Bullet::Bullet(std::shared_ptr<sf::Texture> shr_ptr_texture, char dir, std::shared_ptr<sf::Vector2f> init):GameObject(shr_ptr_texture, init)
{
	direction = dir;
	
}
bool Bullet::distroyBullet(std::vector<std::vector<std::shared_ptr<GameObject>>> objects)
{
	for (auto list : objects)
	{
		if (collides(list)) return true;
	}
	if (isOutOfMap())return true;
	return false;
	
}
void Bullet::moveBullet()
{
	updateSize(16, 16);
	switch (direction)
	{
	case 'u':
		getSprite()->move(0, -5);
		break;
	case 'd':
		getSprite()->move(0, +5);
		break;
	case 'l':
		getSprite()->move(-5, 0);
		break;
	case 'r':
		getSprite()->move(+5, 0);
		break;
	default:
		break;
	}
}

bool Bullet::isOutOfMap()
{
	return (getSprite()->getPosition().x > 1200 || getSprite()->getPosition().y > 600);

}