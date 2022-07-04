#include<iostream>
#include<string>
#include <SFML/Graphics.hpp>
#include "ObjectManipulator.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
// It worked before to build it with cmake now for some reason I have these errors.

int main()
{
	ObjectManipulator TheMaze(sf::VideoMode(1200, 600, 32), "The Maze");
	TheMaze.run();

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();
	return 0;
}
