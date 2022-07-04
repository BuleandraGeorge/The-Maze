#include "Player.h"
Player::Player(std::shared_ptr<sf::Texture> shr_ptr_texture, std::shared_ptr<sf::Vector2f> pos, char facingDirection) : GameObject(shr_ptr_texture, pos)
{
		ui_lives = 1;
		c_movingDirection = facingDirection;
		c_respawn_facing = facingDirection;
		setFacingDirection(facingDirection);
		updateSize(100, 120);
		arrangeTexture();
		shr_ptr_spawnPos = pos;

}
void Player::setFacingDirection(char direction)
{
	switch (direction)
	{
	case Down:
	{
		shr_prt_objectsSprite->setTextureRect(sf::IntRect(32, 0, 32, 32));
		break;
	}
	case Left:
	{
		shr_prt_objectsSprite->setTextureRect(sf::IntRect(32, 32, 32, 32));
		break;
	}
	case Right:
	{
		shr_prt_objectsSprite->setTextureRect(sf::IntRect(32, 64, 32, 32));
		break;
	}
	case Up:
	{
		shr_prt_objectsSprite->setTextureRect(sf::IntRect(32, 96, 32, 32));
		break;
	}
	default:
		break;
	}
}
void Player::animate()
{
	if (moving)
	{
		if (playerClock.getElapsedTime().asMilliseconds() - lastTimeAnimation > frameDelay)
		{
			setNextFrame();
			lastTimeAnimation = playerClock.getElapsedTime().asMilliseconds();
		}
	}
	else {
		i_frame = 64;
		setNextFrame();
		lastTimeAnimation = playerClock.getElapsedTime().asMilliseconds();
	}
}
void Player::setNextFrame()
{
	switch (c_movingDirection)
	{
	case Up:
		
		shr_prt_objectsSprite->setTextureRect(sf::IntRect(decideNextFrame(), 96, 32, 32));
		arrangeTexture();
		break;
	case Down:

		shr_prt_objectsSprite->setTextureRect(sf::IntRect(decideNextFrame(), 0, 32, 32));
		arrangeTexture();
		break;
	case Left:

		shr_prt_objectsSprite->setTextureRect(sf::IntRect(decideNextFrame(), 32, 32, 32));
		arrangeTexture();
		break;
	case Right:

		shr_prt_objectsSprite->setTextureRect(sf::IntRect(decideNextFrame(), 64, 32, 32));
		arrangeTexture();
		break;
	default:
		break;
	}
}
int Player::decideNextFrame()
{
	switch (i_frame)
	{
	case 0:
		bFull = false;
		return i_frame += 32;
	case 32:
		if(bFull) return i_frame -= 32;
		return i_frame+= 32;
	case 64:
		bFull = true;
		return i_frame -= 32;
	default:
		return i_frame = 0;
	}
}
void Player::move()
{
	if (moving)
	{

		switch (c_movingDirection)
		{
		case Up:
			if (traversable(nextPosition(sf::Vector2f(0, -i_Speed)))) shr_prt_objectsSprite->move(sf::Vector2f(0, -i_Speed));
			break;
		case Down:
			if (traversable(nextPosition(sf::Vector2f(0, i_Speed)))) shr_prt_objectsSprite->move(sf::Vector2f(0, i_Speed));
			break;
		case Left:
			if (traversable(nextPosition(sf::Vector2f(-i_Speed, 0)))) shr_prt_objectsSprite->move(sf::Vector2f(-i_Speed, 0));
			break;
		case Right:
			if (traversable(nextPosition(sf::Vector2f(i_Speed, 0)))) shr_prt_objectsSprite->move(sf::Vector2f(i_Speed, 0));
			break;
		default:
			break;
		}
	}
}
void Player::resetPlayer()
{
	setPosition(shr_ptr_spawnPos);
	c_movingDirection = 'n';
	setFacingDirection(c_respawn_facing);
}
void Player::handleControls(sf::Event event) {

	switch (event.key.code)
	{
	case sf::Keyboard::Up:
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (c_movingDirection != Up) i_frame = 32; // restart the animation for player
			c_movingDirection = Up;
			moving = true;
			break;
		}
		moving = false;
		break;
	}
	case sf::Keyboard::Down:
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (c_movingDirection != Down) i_frame = 32; // restart the animation for player
			c_movingDirection = Down;
			moving = true;
			break;
		}
		moving = false;
		break;
	}
	case sf::Keyboard::Left:
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (c_movingDirection != Left) i_frame = 32; // restart the animation for player
			c_movingDirection = Left;
			moving = true;
			break;
		}
		moving = false;
		break;
	}
	case sf::Keyboard::Right:
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (c_movingDirection != Right) i_frame = 32; // restart the animation for player
			c_movingDirection = Right;
			moving = true;
			break;
		}
		moving = false;
		break;
	}
	default:
		break;
	}
}
bool Player::traversable(sf::Vector2f nextPos) {
	int iX = ((nextPos.y+16 )/ 50)-1; 
	int iY = ((nextPos.x+16) / 50)-1;
	return traversableMatrix[iX][iY];
}
sf::Vector2f Player::nextPosition(sf::Vector2f speed) {

	return getSprite()->getPosition() + speed;
}
void Player::setTraversableMatrix(std::shared_ptr<bool[12][24]> matrix)
{
	traversableMatrix = matrix;
}