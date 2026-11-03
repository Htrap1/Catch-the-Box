#include "Target.h"
#include "Colors.h"

Target::Target() 
    : randomGenerator(std::random_device{}())
{
    
    box.setSize({100.f, 100.f});
    box.setPosition({350.f, 250.f});
    box.setFillColor(sf::Color::Red);

}

void Target::changeColor()
{
    std::uniform_int_distribution<int> randomColor(0, 4);

    box.setFillColor(fivecolors[randomColor(randomGenerator)]);
}

void Target::grow()
{
    sf::Vector2f growth(10.f, 10.f);

    sf::Vector2f currentSize = box.getSize();
    sf::Vector2f currentPosition = box.getPosition();

    if (currentSize.x + growth.x <= maxSize &&
        currentSize.y + growth.y <= maxSize) {

        box.setSize(currentSize + growth);
        box.setPosition(currentPosition - growth / 2.f);
    }
}

void Target::teleport()
{
    float maxX = 800.f - box.getSize().x;
    float maxY = 600.f - box.getSize().y;

    std::uniform_real_distribution<float> randomX(0.f, maxX);
    std::uniform_real_distribution<float> randomY(80.f, maxY);

    box.setPosition({randomX(randomGenerator), randomY(randomGenerator)});
}

void Target::reset()
{
    box.setSize({100.f, 100.f});
    box.setPosition({350.f, 250.f});
    box.setFillColor(sf::Color::Red);
}

const sf::RectangleShape& Target::getShape() const
{
    return box;
}

sf::Color Target::getColor() const
{
    return box.getFillColor();
}