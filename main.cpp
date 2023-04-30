#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Button.cpp"
#include "GameHandler.cpp"

void clearWordContainers(std::vector<sf::Sprite*> underlines){

    for(int i = 0; i < underlines.size(); i++){

        delete underlines[i];

    }

    // for(int i = 0; i < letters.size(); i++){

    //     delete letters[i];

    // }

}

void clearTotalContainers(std::vector<Button*> buttons, std::vector<sf::Sprite*> underlines){

    for(int i = 0; i < buttons.size(); i++){

        delete buttons[i];

    }

    for(int i = 0; i < underlines.size(); i++){

        delete underlines[i];

    }

    // for(int i = 0; i < letters.size(); i++){

    //     delete letters[i];

    // }

}

void resetButtons(std::vector<Button*> &buttonVec){

    for(int i = 0; i < buttonVec.size(); i++){

        buttonVec[i]->resetTexture();

    }
}

bool findInWord(std::string letter, std::string str){

    letter = letter[0] + 32;

    for(int i = 0; i < str.length(); i++){

        if(str[i] == letter[0]){
            return true;
        }

    }

    return false;

}

int numUniqueLetters(std::string str){

    int numUnique = 0;
    std::vector<char> uniques;

    bool charFound = false;

    for(int i = 0; i < str.length(); i++){
        charFound = false;
        for(int n = 0; n < uniques.size(); n++){
            if(uniques[n] == str[i]){
                charFound = true;
            }
        }

        if(!charFound){
            uniques.push_back(str[i]);
            numUnique++;   
        }

    }

    return numUnique;

}

void showLetters(std::vector<sf::Text> &letters, std::string buttonLetter){

    buttonLetter = buttonLetter[0] + 32;

    for(int i = 0; i < letters.size(); i++){

        if(letters[i].getString()[0] == buttonLetter[0]){
            letters[i].setFillColor(sf::Color::White);
        }
    }
}

void detectClick(std::vector<Button*> &buttonContainer, sf::Event event, GameHandler &gameInstance, std::string &currWord, int &rightGuesses, std::vector<sf::Text> &letters, std::vector<sf::Sprite*> &underlines, int &winCondition){

    for(int i = 0; i < buttonContainer.size(); i++){
        if(buttonContainer[i]->getBounds().contains(event.mouseButton.x, event.mouseButton.y) && buttonContainer[i]->getText().getString().getSize() < 2 && winCondition == -1){ // If the button is a keyboard letter

            if(findInWord(buttonContainer[i]->getText().getString(), currWord) && buttonContainer[i]->getTexture() == "imgs/letters/empty.png"){ // If the letter pressed is in the string, mark it right
                buttonContainer[i]->loadTexture("imgs/letters/rightLetter.png");
                rightGuesses++;

                showLetters(letters, buttonContainer[i]->getText().getString());

            }else if(!findInWord(buttonContainer[i]->getText().getString(), currWord) && buttonContainer[i]->getTexture() == "imgs/letters/empty.png"){ // If letter pressed isn't in string, mark it wrong
                buttonContainer[i]->loadTexture("imgs/letters/wrongLetter.png");
                gameInstance.declineHangman();
            }

        }else if(buttonContainer[i]->getBounds().contains(event.mouseButton.x, event.mouseButton.y) && buttonContainer[i]->getText().getString() == "New Word"){ // If the button is the reset button
            
            clearWordContainers(underlines);
            resetButtons(buttonContainer);
            winCondition = -1;
            currWord = "";
            gameInstance.resetHangman();

        }
    }
}

void createKeyboard(std::vector<Button*> &buttonContainer, int windowWidth, int windowHeight){

    std::string letters = "QWERTYUIOPASDFGHJKLZXCVBNM";

    std::string charToString = "";

    int keyGapDist = (windowWidth - 400) / 11;

    // std::cout << keyGapDist << std::endl;

    int topXGap = keyGapDist;

    if(keyGapDist > 40){
        keyGapDist = 40;
        topXGap = (windowWidth - (400 + (9 * keyGapDist))) / 2;
    }

    int midXGap = (windowWidth - (360 + (8 * keyGapDist))) / 2;
    int botXGap = (windowWidth - (280 + (6 * keyGapDist))) / 2;

    int topYGap = windowHeight - (3 * (40 + 20));
    int midYGap = windowHeight - (2 * (40 + 20));
    int botYGap = windowHeight - (1 * (40 + 20));

    int midMultiplier = 0;
    int botMultiplier = 0;

    for(int i = 0; i < 26; i++){

        charToString = letters[i];

        Button *textButton = new Button(sf::Vector2f(40, 40), charToString, 24, sf::Color::Black, sf::Color::White, 5);

        if(i < 10){ // Top Layer = qwertyuiop | 10 letters

            textButton->setPosition(sf::Vector2f( topXGap, topYGap));

            topXGap += 40 + keyGapDist;

        }else if(i < 19){ // Mid Layer = asdfghjkl | 9 letters

            textButton->setPosition(sf::Vector2f( midXGap + (midMultiplier * (40 + keyGapDist)), midYGap));

            midMultiplier++;

        }else{ // Bottom Layer = zxcvbnm | 7 letters

            textButton->setPosition(sf::Vector2f( botXGap + (botMultiplier * (40 + keyGapDist)), botYGap));

            botMultiplier++;

        }

        buttonContainer.push_back(textButton);

    }

}

sf::Vector2i resolutionMenuGUI(){

    sf::VideoMode resolutionFinder = sf::VideoMode::getDesktopMode();
    std::cout << resolutionFinder.width << std::endl;
    std::cout << resolutionFinder.height << std::endl;

    sf::RenderWindow resolutionChooser(sf::VideoMode(300, 300), "SFML Hangman Resolution", sf::Style::Titlebar | sf::Style::Close);

    sf::Vector2i finalResolution;

    Button smallScreenButton(sf::Vector2f(200,50), "800x600", 24, sf::Color::Black);
    Button medScreenButton(sf::Vector2f(200, 50), "1280x600", 24, sf::Color::Black);
    Button fullScreenButton(sf::Vector2f(200, 50), "Fullscreen", 24, sf::Color::Black);

    smallScreenButton.setPosition(sf::Vector2f(50, 50));
    medScreenButton.setPosition(sf::Vector2f(50, 125));
    fullScreenButton.setPosition(sf::Vector2f(50, 200));

    smallScreenButton.setRectangleColor(sf::Color::White, sf::Color::Black, 5);
    medScreenButton.setRectangleColor(sf::Color::White, sf::Color::Black, 5);
    fullScreenButton.setRectangleColor(sf::Color::White, sf::Color::Black, 5);

    std::vector<Button> buttons;

    buttons.push_back(smallScreenButton);
    buttons.push_back(medScreenButton);
    buttons.push_back(fullScreenButton);

    while(resolutionChooser.isOpen()){

        sf::Event resEvent;

        while(resolutionChooser.pollEvent(resEvent)){

            switch(resEvent.type){

                case sf::Event::Closed:
                    finalResolution.x = -1;
                    finalResolution.y = -1;
                    resolutionChooser.close();
                break;

                case sf::Event::MouseButtonPressed:

                    if(smallScreenButton.getBounds().contains(resEvent.mouseButton.x, resEvent.mouseButton.y) && 800 <= resolutionFinder.width && 600 <= resolutionFinder.height){

                        finalResolution.x = 800;
                        finalResolution.y = 600;
                        resolutionChooser.close();

                    }else if(medScreenButton.getBounds().contains(resEvent.mouseButton.x, resEvent.mouseButton.y) && 1280 <= resolutionFinder.width && 800 <= resolutionFinder.height){

                        finalResolution.x = 1280;
                        finalResolution.y = 800;
                        resolutionChooser.close();

                    }else if(fullScreenButton.getBounds().contains(resEvent.mouseButton.x, resEvent.mouseButton.y)){

                        finalResolution.x = resolutionFinder.width - 30;
                        finalResolution.y = resolutionFinder.height - 60;
                        resolutionChooser.close();

                    }
                    
                break;

                default:
                break;
                
            }

        }

        resolutionChooser.clear(sf::Color::White);
        
        for(int i = 0; i < buttons.size(); i++){
            resolutionChooser.draw(buttons[i].getRectangle());
            resolutionChooser.draw(buttons[i].getText());
        }

        resolutionChooser.display();

    }

    return finalResolution;

}



int main(){

    sf::Vector2i resolutionChoice = resolutionMenuGUI();

    if(resolutionChoice.x == -1){
        std::cout << "Resolution must be chosen" << std::endl;
        return -1;
    }

    float windowHeight = resolutionChoice.y;
    float windowWidth = resolutionChoice.x;
    std::string currWord = "";
    int numUnique = 0;
    int rightGuessesCount = 0;

    int winCondition = -1;

    GameHandler hangmanInstance(windowWidth, windowHeight);
    
    sf::Texture texture;

    if(!texture.loadFromFile("imgs/letters/underline.png")){
        std::cout << "[GameHandler::createUnderlines] ERROR LOADING UNDERLINE TEXTURE, ABORT AND FIX" << std::endl;
    }

    sf::Font font;

    if(!font.loadFromFile("fonts/cour.ttf")){
        std::cout << "[GameHandler::createLetters] ERROR LOADING LETTER FONT, ABORT AND FIX" << std::endl;
    }

    std::vector<Button*> buttonContainer;
    std::vector<sf::Sprite*> underlines;
    std::vector<sf::Text> letters;

    createKeyboard(buttonContainer, windowWidth, windowHeight);

    Button *newWordButton = new Button(sf::Vector2f(175, 50), "New Word", 24, sf::Color::Black, sf::Color::Green, 5);
    Button winBox(sf::Vector2f(175, 50), "You Win!", 24, sf::Color::Black, sf::Color::White, 5);
    Button loseBox(sf::Vector2f(475, 50), "You Lost!", 24, sf::Color::Black, sf::Color::White, 5);

    newWordButton->setPosition(sf::Vector2f(5,5));
    winBox.setPosition(sf::Vector2f(190, 5));
    loseBox.setPosition(sf::Vector2f(190, 5));

    // loseBox.offsetTextPos(sf::Vector2f(-150, 0));

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML Hangman", sf::Style::Titlebar | sf::Style::Close);

    while (window.isOpen()){

        sf::Event event;

        while (window.pollEvent(event)){

            switch(event.type){

                case sf::Event::Closed:
                    window.close();
                break;

                case sf::Event::MouseButtonPressed:

                    detectClick(buttonContainer, event, hangmanInstance, currWord, rightGuessesCount, letters, underlines, winCondition);
                    
                break;

                default:
                break;

            }
        }

        if(currWord == ""){

            currWord = hangmanInstance.randomWord();
            // std::cout << currWord << std::endl;
            underlines = hangmanInstance.createUnderlines(windowWidth, windowHeight);
            letters = hangmanInstance.createLetters(windowWidth, windowHeight);

            numUnique = numUniqueLetters(currWord);

            for(int i = 0; i < letters.size(); i++){

                letters[i].setFont(font);

            }

            for(int i = 0; i < underlines.size(); i++){

                underlines[i]->setTexture(texture);

            }

            if(std::find(buttonContainer.begin(), buttonContainer.end(), newWordButton) != buttonContainer.end()){ // If the new word button is found, remove it

                buttonContainer.erase(std::find(buttonContainer.begin(), buttonContainer.end(), newWordButton));

            }

        }else if(hangmanInstance.getWrongGuesses() >= 6){ // Failed at word guess

            std::cout << "You Lose!" << std::endl;

            std::string customLose = "You Lost! The word was: " + currWord;

            loseBox.setTextString(customLose);

            winCondition = 0;

            hangmanInstance.setWrongGuesses(0);

            rightGuessesCount = 0;

            buttonContainer.push_back(newWordButton);

        }else if(numUnique == rightGuessesCount){

            std::cout << "You Win!" << std::endl;

            winCondition = 1;

            rightGuessesCount = 0;

            buttonContainer.push_back(newWordButton);

        }

        window.clear();

        for(int i = 0; i < buttonContainer.size(); i++){

            window.draw(buttonContainer[i]->getRectangle());
            window.draw(buttonContainer[i]->getText());
            window.draw(buttonContainer[i]->getSprite());

        }

        for(int i = 0; i < underlines.size(); i++){

            sf::Sprite currSprite = *underlines[i];

            window.draw(currSprite);

        }

        for(int i = 0; i < letters.size(); i++){

            window.draw(letters[i]);
        }

        window.draw(hangmanInstance.getHangman());
        
        if(winCondition == 1){
            window.draw(winBox.getRectangle());
            window.draw(winBox.getText());
        }else if(winCondition == 0){
            window.draw(loseBox.getRectangle());
            window.draw(loseBox.getText());
        }

        window.display();

    }

    clearTotalContainers(buttonContainer, underlines);

    return 0;
}