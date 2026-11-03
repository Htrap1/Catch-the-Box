#pragma once

#include <SFML/Graphics.hpp>
#include "Target.h"
#include <random>
#include <vector>
#include <string>

enum class GameState {
    Menu,
    Playing,
    GameOver
};

enum class Difficulty {
    Easy,
    Medium,
    Hard
};

class Game {
private:
    Target target;

    int score = 0;
    bool won = false;

    GameState state = GameState::Menu;
    Difficulty difficulty = Difficulty::Medium;

    sf::Clock teleportClock;
    float teleportInterval = 1.0f;

    sf::RectangleShape scorebox;
    sf::RectangleShape targetbox;
    sf::RectangleShape targetColorBox;
    sf::RectangleShape retrybutton;

    sf::Font font;

    sf::Text startText;
    sf::Text easyText;
    sf::Text mediumText;
    sf::Text hardText;
    sf::Text scoreText;
    sf::Text targetText;
    sf::Text resultText;
    sf::Text retryText;

    sf::RectangleShape startButton;
    sf::RectangleShape easyButton;
    sf::RectangleShape mediumButton;
    sf::RectangleShape hardButton;

    std::vector<std::string> colorNames = {
        "Red",
        "Green",
        "Blue",
        "Yellow",
        "Magenta"
    };

    sf::Color targetColor;
    int targetIndex = 0;

    std::mt19937 randomng;

    sf::RenderWindow window;

public:
    Game();
    void run();

};