#include "GameHandler.h"

GameHandler::GameHandler(int windowWidth, int windowHeight){

    if(!hangmanPhase.loadFromFile("imgs/hangman/emptyHangman.png")){
        std::cout << "[GameHandler] Constructor Texture Fail! ABORT!" << std::endl;
    }

    hangmanSprite.setTexture(hangmanPhase);

    hangmanSprite.setPosition((windowWidth - 150)/2, 25);

    wrongGuesses = 0;

    loadWords();

}

void GameHandler::loadWords(){

    std::ifstream readFile;

    readFile.open("words.txt");

    if(readFile.fail()){

        std::cout << "WORD FILE NOT FOUND, ERROR LOADING" << std::endl;
        return;

    }

    std::string line;

    while(getline(readFile, line)){

        Word newWord;
        newWord.word = line;
        newWord.recentlyUsed = false;

        words.push_back(newWord);

    }

    readFile.close();

}

std::string GameHandler::randomWord(){

    // currentWord = words[0].word;

    // return words[0].word;

    srand (time(NULL));

    int randomNum;
    bool wordFound = false;
    int maxIndex = words.size() - 1;

    int maxTries = 0;

    while(!wordFound){

        randomNum = rand() % maxIndex;

        if(!words[randomNum].recentlyUsed){

            wordFound = true;
            words[randomNum].recentlyUsed = true;

        }else if(maxTries > 3){

            std::cout << "TOO MANY TRIES" << std::endl;
            return "";

        }else{
            maxTries++;
        }
    }

    currentWord = words[randomNum].word;
    
    return words[randomNum].word;

}

sf::Sprite GameHandler::getHangman(){

    return hangmanSprite;

}

bool GameHandler::declineHangman(){

    switch(wrongGuesses){

        case 0:
            hangmanPhase.loadFromFile("imgs/hangman/headHangman.png");
            hangmanSprite.setTexture(hangmanPhase);
            wrongGuesses++;
        break;

        case 1:
            hangmanPhase.loadFromFile("imgs/hangman/torsoHangman.png");
            hangmanSprite.setTexture(hangmanPhase);
            wrongGuesses++;
        break;

        case 2:
            hangmanPhase.loadFromFile("imgs/hangman/leftArmHangman.png");
            hangmanSprite.setTexture(hangmanPhase);
            wrongGuesses++;
        break;

        case 3:
            hangmanPhase.loadFromFile("imgs/hangman/rightArmHangman.png");
            hangmanSprite.setTexture(hangmanPhase);
            wrongGuesses++;
        break;

        case 4:
            hangmanPhase.loadFromFile("imgs/hangman/leftLegHangman.png");
            hangmanSprite.setTexture(hangmanPhase);
            wrongGuesses++;
        break;

        case 5:
            hangmanPhase.loadFromFile("imgs/hangman/rightLegHangman.png");
            hangmanSprite.setTexture(hangmanPhase);
            wrongGuesses++;
            return true;
        break;

        default:
        break;

    }

    return false;

}


void GameHandler::resetHangman(){

    hangmanPhase.loadFromFile("imgs/hangman/emptyHangman.png");
    hangmanSprite.setTexture(hangmanPhase);
    wrongGuesses = 0;

}

std::vector<sf::Sprite*> GameHandler::createUnderlines(int windowWidth, int windowHeight){

    

    int lengthToInt = currentWord.length();

    std::vector<sf::Sprite*> underlineSprites;

    int yGap = 325;
    int underlineGap = 5;
    int totalSpace = (lengthToInt * 40) + ((lengthToInt-1) * 5);
    int edgeGap = (windowWidth - totalSpace) / 2;

    if(windowHeight/2 > 325){
        yGap = windowHeight/2;
    }

    for(int i = 0; i < lengthToInt; i++){

        sf::Sprite *newUnderline = new sf::Sprite;

        newUnderline->setPosition(edgeGap + (i * (40 + underlineGap)), yGap);

        underlineSprites.push_back(newUnderline);

    }

    return underlineSprites;

}

std::vector<sf::Text> GameHandler::createLetters(int windowWidth, int windowHeight){

    int lengthToInt = currentWord.length();

    std::vector<sf::Text> letters;

    int yGap = 325;
    int underlineGap = 5;
    int totalSpace = (lengthToInt * 40) + ((lengthToInt-1) * 5);
    int edgeGap = (windowWidth - totalSpace) / 2;
    int midOffset = 10;

    std::string charToStr = "";

    if(windowHeight/2 > 325){
        yGap = windowHeight/2;
    }

    for(int i = 0; i < lengthToInt; i++){

        sf::Text newLetter;

        charToStr = currentWord[i];
        newLetter.setString(charToStr);

        newLetter.setFillColor(sf::Color::Black);

        newLetter.setPosition(edgeGap + (i * (40 + underlineGap) + midOffset), yGap);

        newLetter.setCharacterSize(25);

        letters.push_back(newLetter);

    }

    return letters;

}

int GameHandler::getWrongGuesses(){

    return wrongGuesses;

}

void GameHandler::setWrongGuesses(int numGuesses){

    wrongGuesses = numGuesses;

}