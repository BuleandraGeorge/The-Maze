#include "Message.h"
#include <iostream>
Message::Message(std::string text)
{
	bool bSuccess = theFont.loadFromFile(".\\assets\\fonts\\unifont.ttf");
	theMessage.setFont(theFont);
	theMessage.setString(text);
	theMessage.setCharacterSize(32);
	theMessage.setFillColor(Color::White);

}
void Message::setHeight(float height)
{
	float x = theMessage.getPosition().x;
	theMessage.setPosition(Vector2f(x,height));
}
void Message::center()
{
	float width = theMessage.getLocalBounds().width;
	float fX = 600-width/2;
	float fY = theMessage.getPosition().y;
	theMessage.setPosition(Vector2f(fX, fY));
	
}
void Message::setText(std::string text)
{
	theMessage.setString(text);
}
void Message::setSize(unsigned int size) {
	theMessage.setCharacterSize(size);
}
void Message::setColor(sf::Color color) {
	theMessage.setFillColor(color);
}
Text Message::getDrawable() {
	return theMessage;
}
float Message::getHeight() {
	return theMessage.getLocalBounds().height;
}
void Message::makeBold(bool bold)
{
	if (bold)theMessage.setStyle(Text::Bold);
	else theMessage.setStyle(Text::Regular);
}