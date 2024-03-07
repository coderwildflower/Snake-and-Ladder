#include <SFML/Graphics.hpp>
#include <iostream>

#include "Button.h"

//Constructor defination
Button::Button(float posX, float posY, float width, float height,float btnImgX,float btnImgY, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color clickColor, std::string imagePath = "") {

	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(sf::Vector2f(posX, posY));
	shape.setFillColor(btnIdleColor);
	btnHoverColor = hoverColor;
	btnClickColor = clickColor;

	textFont.loadFromFile("assets/Cocogoose Pro Regular Trial.ttf");
	btnText.setFont(textFont);
	btnText.setString(text);
	btnText.setCharacterSize(15);
	btnText.setFillColor(sf::Color::Black);
	btnText.setStyle(sf::Text::Bold);

	//centre align the text inside the button
	btnText.setPosition(shape.getPosition().x + (shape.getSize().x / 2 - btnText.getGlobalBounds().width / 2),
		shape.getPosition().y + (shape.getSize().y / 2 - btnText.getGlobalBounds().height / 2));

	btnImgX = posX;
	btnImgY = posY;
	if (!imagePath.empty())
	{
		if (!btnTexture.loadFromFile(imagePath))
			std::cerr << "Failed to load texture!" << std::endl;

		btnSprite.setTexture(btnTexture);
		btnSprite.setPosition(btnImgX, btnImgY);
		btnSprite.setScale(btnSprite.getLocalBounds().width / width/2, btnSprite.getLocalBounds().height / height/3);
	}
}

	//check if mouse is inside button or not--------------------------------------------------------
	bool Button::isMouseOver(sf::RenderWindow& window)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::FloatRect buttonRect = shape.getGlobalBounds();
		if (buttonRect.contains(sf::Vector2f(mousePos)))
			return true;
		else {
			shape.setFillColor(btnIdleColor);
			return false;
		}
	}

	void Button::UpdateColor(sf::RenderWindow& window)
	{
		if (isMouseOver(window))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				shape.setFillColor(btnClickColor);
			}
			else shape.setFillColor(btnHoverColor);
		}
	}

	void Button::RenderButton(sf::RenderWindow& window)
	{
		window.draw(shape);
		window.draw(btnText);
		window.draw(btnSprite);
	}
