#pragma once
#include "GameObject.h"
#include "Bullet.h";
class Player :public GameObject {
private:
	unsigned int ui_lives; //!< number of lives
	char c_movingDirection;
	enum movingDirections { Up = 'u', Down = 'd', Right = 'r', Left = 'l'}; //!< facing direction
	sf::Clock playerClock; //!< clock of the player
	float lastTimeAnimation=0; //!< last time when a change in frame had place
	int i_frame = 32; //!< pixel position of the frame
	int frameDelay = 150; //!< delay between animation's frames
	bool bFull = false;//!< if animation went through all the frames
	int i_Speed = 2; //!< player speed
	shared_ptr<sf::Vector2f> shr_ptr_spawnPos; //!< shared pointer to the spawn position
	bool moving = false; //!< stores if the player moves
	std::shared_ptr<bool[12][24]> traversableMatrix; //!< information with the squares the player can pass
	char c_respawn_facing; //!< facing of the player 

	void setFacingDirection(char direction); //!< updates the facing direction
	void setNextFrame(); //!< updates the frame of animation
	int decideNextFrame(); //!< calculates next frame of the animation
	bool traversable(sf::Vector2f nextPos); //!< calculates if the given position is traversable
	sf::Vector2f nextPosition(sf::Vector2f speed); //!< calculates the future position 
public:
	Player(std::shared_ptr<sf::Texture> shr_ptr_texture, std::shared_ptr<sf::Vector2f> pos, char faDirection); //!< creates a player with a particular position and facing direction
	void animate(); //!< animates the player
	void move(); //!< moves the player if there is no collision
	void resetPlayer(); //!< brings the player to the spawn position and the correct orientation
	void setTraversableMatrix(std::shared_ptr<bool[12][24]> matrix); //!< sets the traversablesMatrix
	void handleControls(sf::Event event); //!< handles the player controlls

};