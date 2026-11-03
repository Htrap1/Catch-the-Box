#pragma once

#include<SFML/Graphics.hpp>
#include<random>

class Target {
private:
    sf::RectangleShape box;

    float maxSize = 200.f;
    
    std::mt19937 randomGenerator;

public:
    Target();

    const sf::RectangleShape& getShape() const;
    sf::Color getColor() const;

    void changeColor();
    void grow();
    void teleport();
    void reset();
};