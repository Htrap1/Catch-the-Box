#include <filesystem>
#include <limits.h>

#ifdef _WIN32
#include <windows.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

#include "Game.h"
#include "Colors.h"

std::filesystem::path getAssetPath(const std::filesystem::path& relativePath)
{
#ifdef _WIN32

    wchar_t path[MAX_PATH];
    GetModuleFileNameW(nullptr, path, MAX_PATH);

    return std::filesystem::path(path).parent_path() / relativePath;

#elif defined(__APPLE__)

    char path[PATH_MAX];
    uint32_t size = sizeof(path);

    if (_NSGetExecutablePath(path, &size) == 0)
    {
        auto executableDir =
            std::filesystem::weakly_canonical(path).parent_path();

        if (executableDir.filename() == "MacOS")
        {
            return executableDir.parent_path() / "Resources" / relativePath;
        }

        return executableDir / relativePath;
    }

#endif

    return std::filesystem::current_path() / relativePath;
}

Game::Game()
    : font(getAssetPath("assets/arialbd.ttf")),
    startText(font, "START", 28),
    easyText(font, "EASY", 22),
    mediumText(font, "MEDIUM", 22),
    hardText(font, "HARD", 22),
    scoreText(font, "Score: 0", 24),
    targetText(font, "", 24),
    resultText(font, "", 50),
    retryText(font, "RETRY", 24), //order matters, write just like how its written in Game.h 
    randomng(std::random_device{}()),
    window(sf::VideoMode({800u, 600u}), "Click the box")
{
    scorebox.setSize({150.f, 50.f});
    scorebox.setFillColor(sf::Color::White);
    scorebox.setPosition({10.f, 10.f});

    targetbox.setSize({150.f, 50.f});
    targetbox.setFillColor(sf::Color::White);
    targetbox.setPosition({640.f, 10.f});

    targetColorBox.setSize({30.f, 30.f});
    targetColorBox.setPosition({600.f, 20.f});

    retrybutton.setSize({150.f, 50.f});
    retrybutton.setPosition({325.f, 350.f});
    retrybutton.setFillColor(sf::Color::Green);

    startButton.setSize({200.f, 55.f});
    startButton.setPosition({300.f, 200.f});
    startButton.setFillColor(sf::Color::Green);

    easyButton.setSize({130.f, 50.f});
    easyButton.setPosition({145.f, 320.f});

    mediumButton.setSize({130.f, 50.f});
    mediumButton.setPosition({335.f, 320.f});

    hardButton.setSize({130.f, 50.f});
    hardButton.setPosition({525.f, 320.f});

    easyButton.setFillColor(sf::Color(180, 180, 180));
    mediumButton.setFillColor(sf::Color::Yellow);
    hardButton.setFillColor(sf::Color(180, 180, 180));

    startText.setFillColor(sf::Color::Black);
    startText.setPosition({360.f, 210.f});

    easyText.setFillColor(sf::Color::Black);
    easyText.setPosition({180.f, 332.f});

    mediumText.setFillColor(sf::Color::Black);
    mediumText.setPosition({350.f, 332.f});

    hardText.setFillColor(sf::Color::Black);
    hardText.setPosition({560.f, 332.f});

    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition({20.f, 20.f});

    targetText.setFillColor(sf::Color::Black);
    targetText.setPosition({650.f, 20.f});

    resultText.setFillColor(sf::Color::White);
    resultText.setPosition({250.f, 250.f});

    retryText.setFillColor(sf::Color::Black);
    retryText.setPosition({350.f, 360.f});

    std::uniform_int_distribution<int> targetPicker(0, 4);

    targetIndex = targetPicker(randomng);
    targetColor = fivecolors[targetIndex];

    targetColorBox.setFillColor(targetColor);

}

void Game::run()
{
    std::uniform_int_distribution<int> targetPicker(0, 4);

    while(window.isOpen()){
        while(const auto event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
            else if(const auto* mouseEvent = 
                        event->getIf<sf::Event::MouseButtonPressed>()){
                
                sf::Vector2f mousePos(mouseEvent->position);
                if(state == GameState::Menu){

                    if (easyButton.getGlobalBounds().contains(mousePos)) {
                        difficulty = Difficulty::Easy;
                        teleportInterval = 2.0f;
                    }
                    else if (mediumButton.getGlobalBounds().contains(mousePos)) {
                        difficulty = Difficulty::Medium;
                        teleportInterval = 1.0f;
                    }
                    else if (hardButton.getGlobalBounds().contains(mousePos)) {
                        difficulty = Difficulty::Hard;
                        teleportInterval = 0.5f;
                    }

                    else if (startButton.getGlobalBounds().contains(mousePos)) {
                        state = GameState::Playing;
                        teleportClock.restart();
                    }

                    // Highlight the selected difficulty
                    easyButton.setFillColor(
                        difficulty == Difficulty::Easy
                            ? sf::Color::Yellow
                            : sf::Color(180, 180, 180)
                    );

                    mediumButton.setFillColor(
                        difficulty == Difficulty::Medium
                            ? sf::Color::Yellow
                            : sf::Color(180, 180, 180)
                    );

                    hardButton.setFillColor(
                        difficulty == Difficulty::Hard
                            ? sf::Color::Yellow
                            : sf::Color(180, 180, 180)
                    );
                }

                // GAMEPLAY
                else if (state == GameState::Playing) {

                    if (target.getShape().getGlobalBounds().contains(mousePos)) {

                        if (target.getColor() == targetColor) {
                            score++;

                            if (score >= 10) {
                                won = true;
                                state = GameState::GameOver;
                            }

                            // Change box color
                            target.changeColor();

                            // Grow box
                            target.grow();

                            // Teleport box
                            target.teleport();
                            teleportClock.restart();
                        }
                        else {
                            state = GameState::GameOver;
                        }
                    }
                }

                // GAME OVER: retry
                else if (state == GameState::GameOver) {

                    if (retrybutton.getGlobalBounds().contains(mousePos)) {

                        score = 0;
                        won = false;
                        state = GameState::Playing;

                        target.reset();

                        targetIndex = targetPicker(randomng);
                        targetColor = fivecolors[targetIndex];
                        targetColorBox.setFillColor(targetColor);
                        targetText.setString(colorNames[targetIndex]);

                        teleportClock.restart();
                        resultText.setString("");
                    }
                }

            }
        }

        // MENU DRAWING
        if (state == GameState::Menu) {
            window.clear(sf::Color(40, 40, 50));

            window.draw(startButton);
            window.draw(startText);

            window.draw(easyButton);
            window.draw(mediumButton);
            window.draw(hardButton);

            window.draw(easyText);
            window.draw(mediumText);
            window.draw(hardText);

            window.display();
            continue;
        }

        if (state == GameState::GameOver) {
            resultText.setString(won ? "YOU WIN!" : "GAME OVER!");

            scoreText.setString("Score: " + std::to_string(score));

            window.clear();
            window.draw(scorebox);
            window.draw(scoreText);
            window.draw(resultText);
            window.draw(retrybutton);
            window.draw(retryText);
            window.display();

            continue;
        }

        // Teleport box every certain interval of time
        if (teleportClock.getElapsedTime().asSeconds() >= teleportInterval) {
            target.teleport();
            target.changeColor();

            teleportClock.restart();
        }


        window.clear();

        window.draw(target.getShape());
        window.draw(scorebox);
        window.draw(targetbox);
        window.draw(targetText);
        window.draw(targetColorBox);

        scoreText.setString("Score: " + std::to_string(score));
        targetText.setString(colorNames[targetIndex]);

        window.draw(scoreText);

        window.display();
    }
}