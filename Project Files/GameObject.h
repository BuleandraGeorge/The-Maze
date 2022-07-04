#pragma once
#include "GameObject.h"
#include <memory.h>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
class GameObject {
private:

	std::shared_ptr<sf::Vector2f>shr_prt_objectsPosition = std::make_shared<sf::Vector2f>(50, 50); //!< pointer to the position of the sprite
	std::shared_ptr<sf::Vector2f>shr_prt_objectsSize = std::make_shared<sf::Vector2f>(50, 50); //!< pointer to the size of the sprite
	void createSprite(); //!< sets the texture and arange it
protected:
	std::shared_ptr<sf::Texture> shr_prt_objectsTexture; //!< pointer to the texture 
	std::shared_ptr<sf::Sprite>shr_prt_objectsSprite = std::make_shared<sf::Sprite>(); //!< pointer to the sprite of the object
	void updateSize(float x, float y); //!< updates the size of the sprite
	void arrangeTexture(); //!< centers and scales the texture
public:

	GameObject(std::shared_ptr<sf::Texture> shr_ptr_texture); //!, creates a object with the position in 0.0
	GameObject(std::shared_ptr<sf::Texture> shr_ptr_texture, std::shared_ptr<sf::Vector2f> pos); //!< creates an object with the specific position
	void setPosition(std::shared_ptr<sf::Vector2f> shr_prt_objectsPos); //< updates the position of the object
	void drawTo(sf::RenderWindow& window); //!< draws the sprite to the specified window
	virtual void animate(); //!< virtual function for defining the animation logic
	shared_ptr<sf::Sprite> getSprite(); //!< returns the sprite of the object
	bool collides(std::vector<std::shared_ptr<GameObject>> objects); //!< checks collision with the members of the given vector

};
