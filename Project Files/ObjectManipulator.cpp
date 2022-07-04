#include "ObjectManipulator.h"
ObjectManipulator::ObjectManipulator(sf::VideoMode videoMode, std::string sGameName)
{
	window = std::make_shared<sf::RenderWindow>(videoMode,sGameName);
	window->setFramerateLimit(f_FPS);
	GameState = MENU;
	shr_ptr_ObjectsMatrix.resize(Players + 1);
	vec_shr_ptr_textures.resize(Players + 1);
	loadTextures();
	loadMapList();
	loadMap(s_mapList[0]);
	loadScreens();
	
}
void ObjectManipulator::animateObjects()
{
		dynamic_pointer_cast<Player>(shr_ptr_ObjectsMatrix[Players][0])->move();
		dynamic_pointer_cast<Player>(shr_ptr_ObjectsMatrix[Players][0])->animate();
		fireTurrets();
		for (int i = 0; i < shr_ptr_ObjectsMatrix[Bullets].size(); i++)
		{
			dynamic_pointer_cast<Bullet>(shr_ptr_ObjectsMatrix[Bullets][i])->moveBullet();
		}

}
void ObjectManipulator::fireTurrets()
{
		for (int i = 0; i < shr_ptr_ObjectsMatrix[PatternTurrets].size(); i++)
		{
			if (dynamic_pointer_cast<PatternTurret>(shr_ptr_ObjectsMatrix[PatternTurrets][i])->trigger())
			{
				auto fireDetails = dynamic_pointer_cast<PatternTurret>(shr_ptr_ObjectsMatrix[PatternTurrets][i])->getShootingDetails();
				shr_ptr_ObjectsMatrix[Bullets].push_back(std::make_shared<Bullet>(vec_shr_ptr_textures[Bullets], fireDetails.direction, fireDetails.initPoint));
			}
		}
		for (int i = 0; i < shr_ptr_ObjectsMatrix[Triggers].size(); i++)
		{
			if (shr_ptr_ObjectsMatrix[Triggers][i]->collides(shr_ptr_ObjectsMatrix[Players]))
			{
				unsigned int turretIndex = dynamic_pointer_cast<Trigger>(shr_ptr_ObjectsMatrix[Triggers][i])->getIDTurret();
				if (dynamic_pointer_cast<TriggerTurret>(shr_ptr_ObjectsMatrix[TriggerTurrets][turretIndex])->trigger()) {
					auto fireDetails = dynamic_pointer_cast<TriggerTurret>(shr_ptr_ObjectsMatrix[TriggerTurrets][turretIndex])->getShootingDetails();
					shr_ptr_ObjectsMatrix[Bullets].push_back(std::make_shared<Bullet>(vec_shr_ptr_textures[Bullets], fireDetails.direction, fireDetails.initPoint));
				}
			}
		}
}

void ObjectManipulator::checkCollisions()
{
		for (int i = 0; i < shr_ptr_ObjectsMatrix[Bullets].size(); i++)
		{
			if (dynamic_pointer_cast<Bullet>(shr_ptr_ObjectsMatrix[Bullets][i])->distroyBullet(
					{ shr_ptr_ObjectsMatrix[Walls],
					shr_ptr_ObjectsMatrix[PatternTurrets],
					shr_ptr_ObjectsMatrix[TriggerTurrets]}))
			
			{
				shr_ptr_ObjectsMatrix[Bullets].erase(shr_ptr_ObjectsMatrix[Bullets].begin() + i); // delete bullet
			}
			
		}
		if (shr_ptr_ObjectsMatrix[Players][0]->collides(shr_ptr_ObjectsMatrix[Portals]))
		{
			GameState = WIN;
		}
		if (shr_ptr_ObjectsMatrix[Players][0]->collides(shr_ptr_ObjectsMatrix[Bullets]))
		{
			GameState = DIE;
		}
}
void ObjectManipulator::handleEvents(sf::Event event)
{
	if (event.type == sf::Event::Closed) GameState = EXIT;
	switch (GameState)
	{
	case ObjectManipulator::MENU:
		screens[msMENU]->handleControls(event);
		switch (event.key.code)
		{
		case sf::Keyboard::Space:
			if (event.type == sf::Event::KeyReleased)
			{
				switch (screens[msMENU]->getSelectedOption())
				{
				case 0:
					GameState = PLAY;
					break;
				case 1:
					GameState = SELECT_MAP;
					break;
				case 2:
					GameState = HIGH_SCORES;
					break;
				case 3:
					GameState = EXIT;
				default:
					break;
				}
			}
		break;
		default:
			break;
		}
		break;
	case ObjectManipulator::SELECT_MAP:
		screens[msMaps]->handleControls(event);
		switch (event.key.code)
		{
		case sf::Keyboard::Space:
			if (event.type == sf::Event::KeyReleased)
			{
				int selected = screens[msMaps]->getSelectedOption();
				cout << selected << endl;
				if ((s_mapList.size()) > selected)
				{
					loadMap(s_mapList[selected]);
					indexCurentMap = selected;
					updateAttemps(); 
				}
				GameState = MENU;
				resetGame();
			}
			break;
		case sf::Keyboard::Escape:
			GameState = MENU;
			break;
		default:
			break;
		}
		break;
	case ObjectManipulator::HIGH_SCORES:
		screens[msHighScores]->handleControls(event);
		if (event.type == sf::Event::KeyReleased)
		{
			GameState = MENU;
		}
		break;
	case ObjectManipulator::PLAY:
	{
		dynamic_pointer_cast<Player>(shr_ptr_ObjectsMatrix[Players][0])->handleControls(event);
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
		{
			if (event.type == sf::Event::KeyReleased)
			{
				GameState = PAUSE;
			}
			break;
		}
		default:
			break;
		}
		break;
	}
		
	case ObjectManipulator::PAUSE:
		screens[msPAUSE]->handleControls(event);
		for (int i = 0; i < shr_ptr_ObjectsMatrix[PatternTurrets].size(); i++)
		{
			dynamic_pointer_cast<PatternTurret>(shr_ptr_ObjectsMatrix[PatternTurrets][i])->pause();
		}
		switch (event.key.code)
		{
		case sf::Keyboard::Space:
		{
			if (event.type == sf::Event::KeyReleased)
			{
				if (screens[msPAUSE]->getSelectedOption() > 0)
				{
					resetGame();
					GameState = MENU;
					increaseAttemps();
					break;
				}
				GameState = PLAY;
				break;
			}
		}
		default:
			break;
		}
		break;
	case ObjectManipulator::DIE:
		screens[msDIED]->handleControls(event);
		switch (event.key.code)
		{
		case sf::Keyboard::Space:
		{
			resetGame();
			if (event.type == sf::Event::KeyReleased)
			{
				increaseAttemps();
				if (screens[msDIED]->getSelectedOption() > 0)
				{
					GameState = MENU;
					break;
				}
				
				GameState = PLAY;
				break;
				
			}
		}
		default:
			break;
		}
		break;
	case ObjectManipulator::WIN:
		screens[msWON]->handleControls(event);
		if (!checkedHiscore)
		{
			checkedHiscore = true;
			isHighscore = HighScoresO.isHighScore(getMapName(s_mapList[indexCurentMap]), ui_noAttemps[indexCurentMap]);
		}
		if (isHighscore)
		{
			switch (event.type)
			{
			case sf::Event::TextEntered:
				screens[msWON]->getUserInput(HighScoresO.getName(event));
				break;
			case sf::Event::KeyReleased:
				if (event.key.code == sf::Keyboard::Enter)
				{
					HighScoresO.insetNewScore();
					screens[msHighScores]->updateOption(HighScoresO.getHighScoreList());
					GameState = HIGH_SCORES;
					isHighscore = false;
					checkedHiscore = false;
					resetGame();
					resetAttemps();
					screens[msWON]->resetUserInput();
				}
				break;
			default:
				break;
			}
		}
		break;
	default:
		break;
	}
}
void ObjectManipulator::run()
{
	while (window->isOpen())
	{
		while (window->pollEvent(event))
		{
			handleEvents(event);
		}
		window->clear();
		switch (GameState)
		{
		case ObjectManipulator::MENU:
			screens[msMENU]->drawTo(*window);
			break;
		case ObjectManipulator::SELECT_MAP:
			screens[msMaps]->drawTo(*window);
			break;
		case ObjectManipulator::PLAY:
			window->draw(Attemps->getDrawable());
			for (int i = 0; i < shr_ptr_ObjectsMatrix.size(); i++)
			{
				for (int j = 0; j < shr_ptr_ObjectsMatrix[i].size(); j++)
				{
					shr_ptr_ObjectsMatrix[i][j]->drawTo(*window);
				}
			}
			animateObjects();
			checkCollisions();
			break;
		case ObjectManipulator::HIGH_SCORES:
			screens[msHighScores]->drawTo(*window);
			break;
		case ObjectManipulator::DIE:
			screens[msDIED]->drawTo(*window);
			break;
		case ObjectManipulator::PAUSE:
			screens[msPAUSE]->drawTo(*window);
			break;
		case ObjectManipulator::WIN:
			screens[msWON]->drawTo(*window);
			if (isHighscore)screens[msWON]->drawGetInput(*window);
			break;
		case ObjectManipulator::EXIT:
			window->close();
			HighScoresO.writeHighscores();
			break;
		default:
			break;
		}
		
		window->display();
	}

}
void ObjectManipulator::resetGame()
{
	dynamic_pointer_cast<Player>(shr_ptr_ObjectsMatrix[Players][0])->resetPlayer();
	shr_ptr_ObjectsMatrix[Bullets].clear();
	for (int i = 0; i < shr_ptr_ObjectsMatrix[1].size(); i++)
	{
		dynamic_pointer_cast<PatternTurret>(shr_ptr_ObjectsMatrix[PatternTurrets][i])->resetTurret();
	}
}
void ObjectManipulator::loadMap(string fileName)
{
	for (int i = 0; i < shr_ptr_ObjectsMatrix.size(); i++)
	{
		shr_ptr_ObjectsMatrix[i].clear();
	}
	ifstream maptext;
	maptext.open(".\\maps\\"+ fileName);
	
	if (!maptext)
	{
		cout << "Map couldn't be opened";
	}
	int j = 0; // row index of the map
	while (!maptext.eof())
	{
		
		string c;
		maptext >> c;
		int i = 0; // col index of the map
		for (int x = 0; x < c.size(); x++)
		{
			switch (c[x])
			{
			case 'w':
				shr_ptr_ObjectsMatrix[Walls].push_back(std::make_shared<Wall>(vec_shr_ptr_textures[Walls], std::make_shared<sf::Vector2f>((50 * i) + 25, (50 * j) + 25)));
				shr_bMatrix[j][i] = false;
				i++;
				break;
			case 'f':
				shr_bMatrix[j][i] = true;
				i++;
				break;
			case 'p':
				shr_ptr_ObjectsMatrix[PatternTurrets].push_back(std::make_shared<PatternTurret>(vec_shr_ptr_textures[PatternTurrets], std::make_shared<sf::Vector2f>((50 * i) + 25, (50 * j) + 25), c[x + 1]));
				shr_bMatrix[j][i] = false;
				x++;
				i++;
				break;
			case 't':
				shr_ptr_ObjectsMatrix[TriggerTurrets].push_back(std::make_shared<TriggerTurret>(vec_shr_ptr_textures[TriggerTurrets], std::make_shared<sf::Vector2f>((50 * i) + 25, (50 * j) + 25), c[x + 1], c[x + 2]));
				shr_bMatrix[j][i] = false;
				i++;
				x += 2;
				break;
			case 'z':
				shr_ptr_ObjectsMatrix[Portals].push_back(std::make_shared<Portal>(vec_shr_ptr_textures[Portals], std::make_shared<sf::Vector2f>((50 * i) + 25, (50 * j) + 25)));
				shr_bMatrix[j][i] = true;
				i++;
				break;
			case 'm':
				shr_ptr_ObjectsMatrix[Triggers].push_back(std::make_shared<Trigger>(vec_shr_ptr_textures[Triggers], std::make_shared<sf::Vector2f>((50 * i) + 25, (50 * j) + 25), c[x + 1]));
				x++;
				shr_bMatrix[j][i] = true;
				i++;
				break;
			case 'o':
				shr_ptr_ObjectsMatrix[Players].push_back(std::make_shared<Player>(vec_shr_ptr_textures[Players], std::make_shared<sf::Vector2f>((50 * i) + 62.5, (50 * j) + 75), c[x + 1]));
				shr_bMatrix[j][i] = true;
				i++;
				x++;
				break;
			case 's':
				Attemps->theMessage.setPosition(sf::Vector2f((50 * i)+10, (50 * j)+12));
				Attemps->setSize(20);
				Attemps->makeBold(true);
				shr_bMatrix[j][i] = true;
				shr_bMatrix[j][i+1] = true;
				shr_bMatrix[j][i + 2] = true;
				i+=3;
				x+=4;
				break;
			default:
				break;
			}
		}
		j++;
	}
	maptext.close();
	for (int i = 0; i < shr_ptr_ObjectsMatrix[TriggerTurrets].size(); i++)
	{
		for (int j = 0; j < shr_ptr_ObjectsMatrix[Triggers].size(); j++)
		{
			dynamic_pointer_cast<Trigger>(shr_ptr_ObjectsMatrix[Triggers][j])->linkTurret(dynamic_pointer_cast<TriggerTurret>(shr_ptr_ObjectsMatrix[TriggerTurrets][i])->getTriggerID(), i);

		}
	}
	dynamic_pointer_cast<Player>(shr_ptr_ObjectsMatrix[Players][0])->setTraversableMatrix(shr_bMatrix);
}
void ObjectManipulator::loadMapList() {
	system("dir .\\maps /n /b * > assets\\map_list.txt");
	ifstream fileList;
	fileList.open("assets\\map_list.txt");
	if (!fileList)
	{
		cout << "List couldn't be opened";
	}
	while (!fileList.eof())
	{
		string c;
		string csvExtension = ".csv";
		fileList >> c;
		int size = c.size();
		bool isCSV = false;
		if (size > 4)
		{
			isCSV = true;
			for (int i = size - 4; i < c.size(); i++)
			{
				int indexCSV = i - size + 4;
				if (c[i] != csvExtension[indexCSV])
				{
					isCSV = false;
					break;
				}
			}
		}

		if (isCSV) {
			s_mapList.push_back(c);
		}
	}
	ui_noAttemps.resize(s_mapList.size());
	Attemps = std::make_shared<Message>("Attemps:0");
}
string ObjectManipulator::getMapName(string fileName)
{
	string mapName;
	for (int i = 0; i < fileName.size() - 4; i++)
	{
		mapName += fileName[i];
	}
	return mapName;
	
}
void ObjectManipulator::resetAttemps() {
	ui_noAttemps[indexCurentMap] = 0;
	updateAttemps();
}
void ObjectManipulator::increaseAttemps()
{
	ui_noAttemps[indexCurentMap]++;
	updateAttemps();
}
void ObjectManipulator::updateAttemps()
{
	Attemps->setText("Attemps:" + to_string(ui_noAttemps[indexCurentMap]));
}
void ObjectManipulator::loadTextures()
{
	// create textures
	for (int i = 0; i < vec_shr_ptr_textures.size(); i++)
	{
		vec_shr_ptr_textures[i] = std::make_shared<Texture>();
	}
	// load the textures
	if (!vec_shr_ptr_textures[Walls]->loadFromFile(".\\assets\\textures\\Wall.png"))
	{
		std::cout << "Wall not loaded" << std::endl;
	}
	if (!vec_shr_ptr_textures[PatternTurrets]->loadFromFile(".\\assets\\textures\\PatternTurret.jpg"))
	{
		std::cout << "Pattern Turret not loaded" << std::endl;
	}
	if (!vec_shr_ptr_textures[TriggerTurrets]->loadFromFile(".\\assets\\textures\\TriggerTurret.jpg"))
	{
		std::cout << "Trigger Turret not loaded" << std::endl;
	}
	if (!vec_shr_ptr_textures[Players]->loadFromFile(".\\assets\\textures\\Character.png"))
	{
		std::cout << "Player not loaded" << std::endl;
	}
	if (!vec_shr_ptr_textures[Bullets]->loadFromFile(".\\assets\\textures\\bullet.png"))
	{
		std::cout << "Bullet not loaded" << std::endl;
	}
	if (!vec_shr_ptr_textures[Portals]->loadFromFile(".\\assets\\textures\\portal.png"))
	{
		std::cout << "Portal not loaded" << std::endl;
	}
	if (!vec_shr_ptr_textures[Triggers]->loadFromFile(".\\assets\\textures\\trigger.png"))
	{
		std::cout << "Trigger not loaded" << std::endl;
	}
}

void ObjectManipulator::loadScreens()
{
	shared_ptr<Screen> Menu1(new Screen("THE MAZE", 32, 50));
	Menu1->addOption("Play");
	Menu1->addOption("Select Map");
	Menu1->addOption("Hall of Fame");
	Menu1->addOption("Exit");
	Menu1->setDefaultOptionColor(sf::Color::Blue);
	Menu1->setDefaultSelectedOptionColor(sf::Color::Red);
	screens.push_back(Menu1);

	shared_ptr<Screen> SelectMap(new Screen("SELECT MAP", 32, 50));
	for (int i = 0; i < s_mapList.size(); i++)
	{
		SelectMap->addOption(getMapName(s_mapList[i]));
	}
	SelectMap->addOption("Exit");
	SelectMap->setDefaultOptionColor(sf::Color::Blue);
	SelectMap->setDefaultSelectedOptionColor(sf::Color::Red);
	screens.push_back(SelectMap);

	shared_ptr<Screen> DeadScreen(new Screen("YOU DEAD", 32, 50));
	DeadScreen->addOption("PLAY AGAIN");
	DeadScreen->addOption("MAIN MENU");
	DeadScreen->setDefaultOptionColor(sf::Color::Blue);
	DeadScreen->setDefaultSelectedOptionColor(sf::Color::Red);
	screens.push_back(DeadScreen);

	shared_ptr<Screen> WinScreen(new Screen("YOU WON", 32, 50));
	WinScreen->addOption("PLAY AGAIN");
	WinScreen->addOption("MAIN MENU");
	WinScreen->setDefaultOptionColor(sf::Color::Blue);
	WinScreen->setDefaultSelectedOptionColor(sf::Color::Red);
	WinScreen->setTitleColor(sf::Color::Yellow);
	screens.push_back(WinScreen);

	shared_ptr<Screen> PauseScreen(new Screen("PAUSE", 32, 50));
	PauseScreen->addOption("CONTINUE");
	PauseScreen->addOption("MAIN MENU");
	PauseScreen->setDefaultOptionColor(sf::Color::Blue);
	PauseScreen->setDefaultSelectedOptionColor(sf::Color::Red);
	PauseScreen->setTitleColor(sf::Color::Green);
	screens.push_back(PauseScreen);

	shared_ptr<Screen> HighScoresScreen(new Screen("HALL OF FAME", 32, 50));
	if (HighScoresO.getHighScoreList().size() > 0)
	{
		for (int i = 0; i < HighScoresO.getHighScoreList().size(); i++)
		{
			HighScoresScreen->addOption(HighScoresO.getHighScoreList()[i]);
		}

	}
	else
	{
		HighScoresScreen->addOption("NO HIGHSCORES, YOUR TIME TO SHINE!");
	}
	HighScoresScreen->addOption("Exit");

	HighScoresScreen->setDefaultOptionColor(sf::Color::Blue);
	HighScoresScreen->setDefaultSelectedOptionColor(sf::Color::Red);
	HighScoresScreen->setTitleColor(sf::Color::Green);
	screens.push_back(HighScoresScreen);
}

