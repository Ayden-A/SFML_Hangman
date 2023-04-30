#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <time.h>

class GameHandler{

public:

    struct Word{
        std::string word;
        bool recentlyUsed;
    };

    GameHandler(int windowWidth, int windowHeight);
    void loadWords();
    std::string randomWord();
    sf::Sprite getHangman();
    bool declineHangman();
    void resetHangman();
    std::vector<sf::Sprite*> createUnderlines(int windowWidth, int windowHeight);
    std::vector<sf::Text> createLetters(int windowWidth, int windowHeight);
    int getWrongGuesses();
    void setWrongGuesses(int numGuesses);

private:

    std::vector<Word> words;

    sf::Texture hangmanPhase;
    sf::Sprite hangmanSprite;

    std::string currentWord;

    int wrongGuesses;

};

#endif