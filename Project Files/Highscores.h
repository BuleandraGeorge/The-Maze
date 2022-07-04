#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Message.h"
#include <sstream>
using namespace std;
class Highscores
{
	vector<string> highscoreList; //!< a list of all highscores
	string playerName; //!< holder for retriving the name
	string newHighscore; //!< string version of the new score
	string mapName; //!< the map name where was achieved the highscore
	unsigned int indexNewHS; //!< the index in list of highscore of the new Highscore

	string getMapNameInLine(string line); //!< retrieves the map name from  of the score records
	unsigned int getScoreInLine(string line); //!< retrieves the score from of a score record
	string ajustNumberToFormat(unsigned int number); //!< converts the integer score to a string score of form 000

public:
	Highscores(); //!<reads the highscores and populates the highscoreList
	vector<string> getHighScoreList(); //!< returns the highscoreList
	string getName(sf::Event event); //!< handles the user input
	bool isHighScore(string sMapName, unsigned int noAttemps); //!< checks if the current score is a highscore
	void insetNewScore(); //!< adds to the correct position the new Highscore
	void writeHighscores(); //!< writes everything in the highscore file.
};

