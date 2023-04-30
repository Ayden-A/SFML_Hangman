#include "Button.h"

Button::Button(sf::Vector2f rectangleSize, std::string textString, int textSize, sf::Color buttonColor){

    rectangle.setSize(rectangleSize);
    text.setString(textString);

    rectangle.setFillColor(buttonColor);
    text.setFillColor(buttonColor);

    font.loadFromFile("fonts/cour.ttf");

    text.setFont(font);
    text.setCharacterSize(textSize);

    spriteTexture.loadFromFile("imgs/letters/empty.png");
    currTexture = "imgs/letters/empty.png";

}

Button::Button(sf::Vector2f rectangleSize, std::string textString, int textSize, sf::Color fill, sf::Color outline, int outlineThickness){

    rectangle.setSize(rectangleSize);
    text.setString(textString);

    rectangle.setFillColor(fill);
    text.setFillColor(outline);

    rectangle.setOutlineColor(outline);
    rectangle.setOutlineThickness(outlineThickness);

    if(!font.loadFromFile("fonts/cour.ttf")){

        std::cout << "[Button Constructor Font Load Error! Abort!]" << std::endl;

    }

    text.setFont(font);
    text.setCharacterSize(textSize);

    spriteTexture.loadFromFile("imgs/letters/empty.png");
    currTexture = "imgs/letters/empty.png";

}

sf::FloatRect Button::getBounds(){

    return rectangle.getGlobalBounds();

}

bool Button::loadTexture(std::string fileName){

    if(!spriteTexture.loadFromFile(fileName)){

        return false;

    }

    currTexture = fileName;

    buttonSprite.setTexture(spriteTexture);

    return true;

}

void Button::resetTexture(){

    spriteTexture.loadFromFile("imgs/letters/empty.png");
    currTexture = "imgs/letters/empty.png";
    buttonSprite.setTexture(spriteTexture);

}

void Button::setPosition(sf::Vector2f pos){

    rectangle.setPosition(pos);

    int remainingX = rectangle.getLocalBounds().width - text.getLocalBounds().width;
    int remainingY = rectangle.getLocalBounds().height - text.getLocalBounds().height;

    text.setPosition(pos.x + (remainingX/2)-5, pos.y + (remainingY/2)-10);

    buttonSprite.setPosition(pos);

}

void Button::setRectangleColor(sf::Color fill, sf::Color outline, int outlineThickness){

    rectangle.setFillColor(fill);
    rectangle.setOutlineColor(outline);
    rectangle.setOutlineThickness(outlineThickness);

}

void Button::setTextString(std::string newStr){

    text.setString(newStr);

    int remainingX = rectangle.getLocalBounds().width - text.getLocalBounds().width;
    int remainingY = rectangle.getLocalBounds().height - text.getLocalBounds().height;

    text.setPosition(rectangle.getPosition().x + (remainingX/2)-5, rectangle.getPosition().y + (remainingY/2)-10);

}

void Button::hideButton(){

    rectangle.setFillColor(sf::Color::Black);
    rectangle.setOutlineColor(sf::Color::Black);
    
    text.setFillColor(sf::Color::Black);

}

void Button::showButton(){

    rectangle.setOutlineColor(sf::Color::White);
    
    text.setFillColor(sf::Color::White);

}

sf::RectangleShape Button::getRectangle(){

    return rectangle;

}

sf::Text Button::getText(){

    return text;

}

sf::Sprite Button::getSprite(){

    return buttonSprite;

}

std::string Button::getTexture(){

    return currTexture;

}

void Button::offsetTextPos(sf::Vector2f newVector){

    text.setPosition(text.getPosition().x + newVector.x, text.getPosition().y - newVector.y);

}