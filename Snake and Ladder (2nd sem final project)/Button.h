#pragma once
#include <SFML/Graphics.hpp>

class Button {

private:
	sf::RectangleShape shape;
	sf::Text btnText;
	sf::Font textFont;
	sf::Color btnIdleColor = sf::Color::White;
	sf::Color btnHoverColor;
	sf::Color btnClickColor;
	sf::Texture btnTexture;
	sf::Sprite btnSprite;


public:
	//constructor
	Button(float, float , float , float , std::string , sf::Color , sf::Color , sf::Color , std::string );

	bool isMouseOver(sf::RenderWindow& window);
	void UpdateColor(sf::RenderWindow& window);
	void RenderButton(sf::RenderWindow& window);

};
