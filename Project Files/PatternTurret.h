#pragma once
#include "NPC.h"
class PatternTurret : public NPC
{
private:
	unsigned int ui_delayShot = 100; //!< default delay between 2 shots
	unsigned int ui_noShots = 3; //!< default number of shots
	unsigned int ui_delayPattern = 3000; //!< delay between two patterns
	float lastTimeShot = 0; //!< last time when a bullet was shooted
	float timePast = 0; //!< last time when a pattern was completed
	float currentDelay; //!< holds the current delay of the turret
	unsigned int state = 0; //!< state of the FSM of trigger
	unsigned int shotsCounter = 0; //!< number of the fired bullets 

public:
	PatternTurret(std::shared_ptr<sf::Texture> shr_ptr_texture); //!< creates a turret with position 0.0
	PatternTurret(std::shared_ptr<sf::Texture> shr_ptr_texture, std::shared_ptr<sf::Vector2f> objectPos, unsigned char direction); //!< creates a turret with a particular position
	PatternTurret(std::shared_ptr<sf::Texture> shr_ptr_texture, unsigned int ui_delayShotI, unsigned int ui_delayPatternI, unsigned int ui_noShotsI); //!< creates a turret with some particular shooting details
	bool trigger(); //!< calculates if is time to shoot. 
	void resetTurret(); //!< resets the times for shooting
	void pause(); //!< pause the time trackers for shooting

};