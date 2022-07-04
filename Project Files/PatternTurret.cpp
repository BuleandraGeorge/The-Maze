#include "PatternTurret.h"


PatternTurret::PatternTurret(std::shared_ptr<sf::Texture> shr_ptr_texture) :NPC(shr_ptr_texture) {
	}
PatternTurret::PatternTurret(std::shared_ptr<sf::Texture> shr_ptr_texture, std::shared_ptr<sf::Vector2f> objectPos, unsigned char direction) :NPC(shr_ptr_texture, objectPos) {

	setShootingDetails(direction, objectPos);
	ajustInitialPoint();
}
PatternTurret::PatternTurret(std::shared_ptr<sf::Texture> shr_ptr_texture, unsigned int ui_delayShotI, unsigned int ui_delayPatternI, unsigned int ui_noShotsI) :NPC(shr_ptr_texture) {
		ui_delayShot = ui_delayShotI;
		ui_noShots = ui_noShotsI;
		ui_delayPattern = ui_delayPatternI;
		currentDelay = 0;
		
	}
bool PatternTurret::trigger()
{
	switch (state)
	{
		
	case 0:
		timePast = time.getElapsedTime().asMilliseconds() - lastTimeShot;
		if (timePast >= currentDelay)
		{
			state = 1;
			return false;
		}
		state = 0;
		return false;
	case 1:
		timePast = time.getElapsedTime().asMilliseconds() - lastTimeShot;
		if (shotsCounter < ui_noShots)
		{
			currentDelay = ui_delayShot;
			state = 0;
			shotsCounter += 1;
			lastTimeShot = time.getElapsedTime().asMilliseconds();
			return true;
			
		}
		currentDelay = ui_delayPattern;
		state = 0;
		shotsCounter = 0;
		return false;
	}
};
void PatternTurret::resetTurret()
{
	lastTimeShot = 0;
	currentDelay = 0;
	shotsCounter = 0;
	state = 0;
}
void PatternTurret::pause()
{
	lastTimeShot = (time.getElapsedTime().asMilliseconds() - timePast);
}

