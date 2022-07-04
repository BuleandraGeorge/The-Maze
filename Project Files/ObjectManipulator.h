#pragma once
#include "GameObject.h"
#include "TriggerTurret.h"
#include "PatternTurret.h"
#include "Wall.h"
#include "Bullet.h"
#include "Player.h"
#include "Portal.h"
#include "Trigger.h"
#include "Screen.h"
#include "Highscores.h"
#include <fstream>
#include <iostream>
using namespace std;
class ObjectManipulator {
private:
	std::shared_ptr<sf::RenderWindow> window; //!< the window where the game will be drawn
	const float f_FPS = 60.0f; //!< number of the fps
	sf::Event event;//!< event holder
	std::vector<std::vector<std::shared_ptr<GameObject>>> shr_ptr_ObjectsMatrix; //!< pointers all the objects of the game
	std::vector<std::shared_ptr<sf::Texture>> vec_shr_ptr_textures;//!<pointers all the textures of the game
	std::vector<std::shared_ptr<Screen>> screens;//!< pointers to the game's screens 
	vector<string> s_mapList; //!< the map list
	enum enum_GameStates {MENU, SELECT_MAP, PLAY,HIGH_SCORES, DIE, PAUSE, WIN, EXIT}GameState; //!< the states in which the games currently is.
	enum objectsIndex { Walls, PatternTurrets, TriggerTurrets, Portals, Triggers, Bullets, Players}; //!< indexes for gameObject matrix, brings more clariting in organization of the matrix
	enum mainScreensIndex{msMENU,msMaps, msDIED, msWON, msPAUSE, msHighScores};//!< indexes for the screens of the game
	unsigned int indexCurentMap=0; //!< used for retriving the name of the current map from the list
	std::vector<unsigned int> ui_noAttemps; //!< no attemps for each map
	std::shared_ptr<Message> Attemps; //!< text sprite for attemps
	Highscores HighScoresO; //!< handles the logic for highscores
	bool isHighscore = false; //!< switch for highscore 
	bool checkedHiscore = false; //!< switch for avoiding to check every frame if is a highscore
	std::shared_ptr<bool[12][24]> shr_bMatrix = std::shared_ptr<bool[12][24]>(new bool[12][24]{ true }); //!< 
	

public:
	ObjectManipulator(sf::VideoMode videoMode, std::string sGameName); //! generates the map
	void animateObjects(); //!< triggers the animation of all entities
	void fireTurrets(); //!< checks if any turret has to shoot
	void checkCollisions(); //!< checks the states of the existent bullets
	void handleEvents(sf::Event event);
	void resetGame();
	void loadMap(string fileName);
	void loadMapList();
	string getMapName(string fileName);
	void resetAttemps();
	void updateAttemps();
	void increaseAttemps();
	void loadTextures();
	void run();
	void loadScreens();
	
};