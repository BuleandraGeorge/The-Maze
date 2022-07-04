#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Message.h"
#include <memory.h>
#include <vector>
#include <iostream>
class Screen
{
private:
	std::shared_ptr<Message> Title;
	std::vector<std::shared_ptr<Message>> vec_shr_ptr_msg_options;
	unsigned int selectedOption = 0;
	const float kfStartHeight = 200;
	float totalHeight = 0;
	sf::RectangleShape overlay;
	sf::Color defaultOptionColor = sf::Color::White;
	sf::Color defaultSelectedOptionColor = sf::Color::Red;
	sf::Color defaultTitleColor = sf::Color:: White;
	sf::Color defaultOverlaycolor = sf::Color::Black;
	void toggleHighLight(unsigned int option);
	float getTotalHeightText();
	void addHeight(float);
	std::shared_ptr<Message> userInput;
public:
	Screen(std::string sViewTitle, unsigned int size, float height);//!< Creates a simple view with title
	void addOption(std::string sText); //!< Adds an option on the page or just a regular text
	void handleControls(sf::Event event);
	unsigned int getSelectedOption();
	void drawTo(sf::RenderWindow& window);
	void setDefaultOverlayColor(sf::Color color);
	void setDefaultOptionColor(sf::Color color);
	void setDefaultSelectedOptionColor(sf::Color color);
	void setTitleColor(sf::Color color);
	void getUserInput(std::string someMessage);
	void updateOption(std::vector<std::string> optionlist);
	void drawGetInput(sf::RenderWindow& window);
	void resetUserInput();
	

};

