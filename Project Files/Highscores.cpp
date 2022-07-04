#include "Highscores.h"

Highscores::Highscores()
{
	ifstream hsList;

	hsList.open(".\\highscores\\high_scores.txt");
	string hs;
	if (!hsList) std::cout << "Scores couldn't be loaded";
	while (!hsList.eof())
	{
		std::getline(hsList, hs);
		if(hs!="") highscoreList.push_back(hs);
		
	}
	hsList.close();
}
vector<string> Highscores::getHighScoreList() {
	return highscoreList;
}
string Highscores::getName(sf::Event Event)
{
	switch (Event.type)
	{
	case sf::Event::TextEntered:
		if ((Event.text.unicode >= 20) && (Event.text.unicode <= 127))
		{
			if(Event.text.unicode != 32)playerName += Event.text.unicode;
		}
		if ((Event.text.unicode == 8) && (playerName.size()>0)) playerName.resize(playerName.size() - 1);
		break;
	default:
		break;
	}
	return playerName;
}
bool Highscores::isHighScore(string sMapName, unsigned int noAttemps)
{
	mapName = sMapName;
	newHighscore = "";
	indexNewHS = 0;
	for (int i = 0; i < highscoreList.size(); i++)
	{

		if (getScoreInLine(highscoreList[i]) > noAttemps)
		{
			indexNewHS = i;
			newHighscore = ajustNumberToFormat(noAttemps);
			return true;
		}

	}
	if (highscoreList.size() <8)
	{
		newHighscore = ajustNumberToFormat(noAttemps);
		indexNewHS = highscoreList.size();
		return true;
	}
		
	mapName = "";
	return false;
}
string Highscores::getMapNameInLine(string line)
{
	bool isName = false;
	string map;
	for (int j = 0; j < line.size() - 4; j++)
	{
		if (!isName)
		{
			if (line[j] == ' ')
			{
				isName = true;
			}
		}
		else
		{
			map += line[j];
		}
	}
	return map;
}
unsigned int Highscores::getScoreInLine(string line) {
	unsigned int number = 0;
	string strNumber;
	for (int j = line.size() - 4; j < line.size(); j++)
	{
		strNumber +=line[j];
	}
	stringstream ss;
	ss << strNumber;
	ss >> number;
	return number;
}
void Highscores::insetNewScore()
{
	string record;
	record += playerName + " " + mapName + " " + newHighscore;
	std::vector<string>::iterator it;
	it = highscoreList.begin();
	highscoreList.insert(it+indexNewHS, record);
};
string Highscores::ajustNumberToFormat(unsigned int number)
{
	string format = "000";
	for (int i = to_string(number).size()-1; i >=0 ; i--)
		format[2-i] = to_string(number)[i];

	return format;
}
void Highscores::writeHighscores() 
{
	ofstream hsList;
	hsList.open(".\\highscores\\high_scores.txt");
	if (!hsList) std::cout << "Scores couldn't be loaded";
	for (auto line : highscoreList)
	{
		hsList << line<<"\n";
	}
	hsList.close();
}