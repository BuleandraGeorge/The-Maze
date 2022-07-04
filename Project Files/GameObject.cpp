#include "GameObject.h"

GameObject::GameObject(std::shared_ptr<sf::Texture> shr_ptr_texture)
{
	shr_prt_objectsTexture = shr_ptr_texture;
	this->createSprite();
}
GameObject::GameObject(std::shared_ptr<sf::Texture> shr_ptr_texture, std::shared_ptr<sf::Vector2f> shr_ptr_objectPos)
{
	setPosition(shr_ptr_objectPos);
	shr_prt_objectsTexture = shr_ptr_texture;
	this->createSprite();
}
void GameObject::arrangeTexture() {
		shr_prt_objectsSprite->setScale(
			shr_prt_objectsSize->x / shr_prt_objectsTexture->getSize().x,
			shr_prt_objectsSize->y / shr_prt_objectsTexture->getSize().y
		);
		shr_prt_objectsSprite->setOrigin(
			shr_prt_objectsSize->x / 2.f / shr_prt_objectsSprite->getScale().x,
			shr_prt_objectsSize->y / 2.f / shr_prt_objectsSprite->getScale().y
		);
	}
void GameObject::createSprite()
{
	shr_prt_objectsSprite->setTexture(*shr_prt_objectsTexture);
	arrangeTexture();

}

void GameObject::setPosition(std::shared_ptr<sf::Vector2f> shr_prt_objectsPos)
{
	shr_prt_objectsPosition = shr_prt_objectsPos;
	shr_prt_objectsSprite->setPosition(*shr_prt_objectsPosition);

}
void GameObject::drawTo(sf::RenderWindow& window) {
	window.draw(*shr_prt_objectsSprite);
}
void GameObject::updateSize(float x, float y) {
	shr_prt_objectsSize = std::make_shared<sf::Vector2f>(x, y);
	arrangeTexture();

}
void GameObject::animate()
{

}
shared_ptr<sf::Sprite> GameObject::getSprite()
{
	return shr_prt_objectsSprite;
}
bool GameObject::collides(std::vector<std::shared_ptr<GameObject>> objects)
{;
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]!=nullptr) 
			if (objects[i]->getSprite()->getGlobalBounds().intersects(this->getSprite()->getGlobalBounds()))
				return true;
	}
	return false;
}