#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
//stores the font and the the actual text;
class Message
{
public:
	Font theFont;
	Text theMessage;

public:
	//loads and sets the font, sets a default size of 32 and the color white;
	Message(std::string text);
	// updates the text accordingly to the parameters;
	void setHeight(float height);
	void center();//!<centers the the text
	void setText(std::string text); //!< sets a new text 
	void setSize(unsigned int size); //!< sets a size
	void setColor(sf::Color color); //!< changes the text's color
	float getHeight(); //!< returns the height of the text object
	Text getDrawable(); //!< returns the sprite of the text
	void makeBold(bool bold); //!< switches between bold and regular

};
