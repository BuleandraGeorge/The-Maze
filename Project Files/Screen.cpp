#include "Screen.h"

Screen::Screen(std::string ViewTitle, unsigned int size, float height)
{
	Title = std::shared_ptr<Message>(new Message(ViewTitle));
	Title->setText(ViewTitle);
	Title->setSize(size);
	Title->makeBold(true);
	Title->center();
	Title->setHeight(height);
	Title->setColor(defaultTitleColor);
	overlay.setSize(sf::Vector2f(1200, 600));
	overlay.setFillColor(defaultOverlaycolor);
	userInput = std::shared_ptr<Message> (new Message(""));
	userInput->setText("YOU GOT A TICKET IN HALL OF FAME, INSERT YOUR NAME AND PRESS ENTER");
	userInput->center();
	userInput->setHeight(kfStartHeight - 50);
}
void Screen::addOption(std::string sText)
{
	std::shared_ptr<Message> newOption(new Message(sText));
	newOption->setSize(16);
	newOption->setHeight(getTotalHeightText());
	addHeight(newOption->getHeight());
	newOption->center();
	newOption->setColor(defaultOptionColor);
	vec_shr_ptr_msg_options.push_back(newOption);
}
void Screen::handleControls(sf::Event event)
{
	switch (event.key.code)
	{
	case sf::Keyboard::Up:
	{
		if (event.type == sf::Event::KeyReleased)
		if (selectedOption > 0)
			selectedOption--;
		break;
	}
	case sf::Keyboard::Down:
	{
		if (event.type == sf::Event::KeyReleased)
			if (selectedOption < (vec_shr_ptr_msg_options.size()-1))
				selectedOption++;
		break;
	}
	default:
		break;
	}
	toggleHighLight(selectedOption);

	
}
void Screen::toggleHighLight(unsigned int option)
{
	for (int i = 0; i < vec_shr_ptr_msg_options.size(); i++)
	{
		vec_shr_ptr_msg_options[i]->setColor(defaultOptionColor);
	}
	vec_shr_ptr_msg_options[option]->setColor(defaultSelectedOptionColor);
}
unsigned int Screen::getSelectedOption()
{
	return selectedOption;
}
void Screen::drawTo(sf::RenderWindow& window)
{
	window.draw(overlay);
	for (int i = 0; i < vec_shr_ptr_msg_options.size();i++)
	{
		window.draw(vec_shr_ptr_msg_options[i]->getDrawable());
	}
	window.draw(Title->getDrawable());
}
float Screen::getTotalHeightText()
{
	return totalHeight+kfStartHeight;
}
void Screen::addHeight(float height) {
	totalHeight += height+20;
}
void Screen::setDefaultOverlayColor(sf::Color color) {
	defaultOverlaycolor = color;
}
void Screen::setDefaultOptionColor(sf::Color color) {
	defaultOptionColor = color;
	for (int i = 0; i < vec_shr_ptr_msg_options.size(); i++)
	{
		vec_shr_ptr_msg_options[i]->setColor(color);
	}
	vec_shr_ptr_msg_options[0]->setColor(defaultSelectedOptionColor);
}
void Screen::setDefaultSelectedOptionColor(sf::Color color) {
	defaultSelectedOptionColor = color;
	vec_shr_ptr_msg_options[0]->setColor(color);
}
void Screen::setTitleColor(sf::Color color) {
	defaultTitleColor = color;
	Title->setColor(color);
}
void Screen::getUserInput(std::string input)
{
	std::cout << "GetUserInput";
	userInput->setText(input);
	userInput->center();
	userInput->setHeight(kfStartHeight-50);
}
void Screen::updateOption(std::vector<std::string> optionlist) {
	vec_shr_ptr_msg_options.clear();
	totalHeight = 0;
	if (optionlist.size() > 8) {
		optionlist.resize(8);
	}
	for (auto option : optionlist)
	{
		addOption(option);
	}
	addOption("Exit");
}
void Screen::drawGetInput(sf::RenderWindow& window) {
	window.draw(userInput->getDrawable());
}
void Screen::resetUserInput()
{
	userInput->setText("YOU GOT A TICKET IN HALL OF FAME, INSERT YOUR NAME AND PRESS ENTER");
	userInput->center();
	userInput->setHeight(kfStartHeight - 50);
}
