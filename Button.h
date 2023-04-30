#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Button{

//(int width, int height, std::string textString, int textSize, sf::Color buttonColor)

public:
    Button(sf::Vector2f rectangleSize, std::string textString, int textSize, sf::Color buttonColor);
    Button(sf::Vector2f rectangleSize, std::string textString, int textSize, sf::Color fill, sf::Color outline, int outlineThickness);
    sf::FloatRect getBounds();
    bool loadTexture(std::string fileName);
    void resetTexture();

    void setPosition(sf::Vector2f pos);
    void setRectangleColor(sf::Color fill, sf::Color outline, int outlineThickness);
    void setTextString(std::string newStr);

    void hideButton();
    void showButton();

    sf::RectangleShape getRectangle();
    sf::Text getText();
    sf::Sprite getSprite();
    std::string getTexture();

    void offsetTextPos(sf::Vector2f);

private:
    sf::RectangleShape rectangle;
    sf::Text text;
    sf::Font font;

    std::string currTexture;
    sf::Texture spriteTexture;
    sf::Sprite buttonSprite;

};


#endif