#pragma once

#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Maze.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

class GameWindow
{
private:
    void welcomeWindow();
    void drawBackground(sf::RenderWindow& window, bool door, bool left, bool right);
    void drawTitle(sf::RenderWindow &window);
    void drawMainMenu(sf::RenderWindow &window, std::vector<bool> selected_option, bool& music_on, std::vector<bool>& pressed);
    void drawDifficulty(sf::RenderWindow &window, std::vector<bool> selected_option,  std::vector<bool>& pressed);
    void gameWindow(sf::RenderWindow& window, std::vector<bool> difficulty, std::vector<bool> cheat_modes);
    void mainMenuWindow(sf::RenderWindow& window, sf::Music& music, sf::Sound& sound);
    void difficultySelectionWindow(sf::RenderWindow& window, sf::Sound& sound, std::vector<bool> cheat_modes);
    void instructionsWindow(sf::RenderWindow& window);
    void drawInstructions(sf::RenderWindow& window, bool& pressed);
    void cheatsWindow(sf::RenderWindow& window, std::vector<bool>& cheat_modes, sf::Sound& bark);
    void drawCheats(sf::RenderWindow& window, std::string input, std::vector<bool> selected, std::vector<bool> pressed);
    bool mazeSolved(int x, int y, int size);
    std::vector<std::vector<bool>> chooseMazeAlgorithm(Maze& maze, int wins);

public:
    void startGame();
};

// starts the game
void GameWindow::startGame()
{
    welcomeWindow();
}

// draws the cheats menu
void GameWindow::drawCheats(sf::RenderWindow &window, std::string input, std::vector<bool> selected, std::vector<bool> pressed)
{
    std::vector<std::string> menu = {"ENTER", "RETURN"};
    std::string cursor = "> ";
    sf::Font font;
    font.loadFromFile("./fonts/Ticketing.ttf");

    sf::Text backToMenu;
    backToMenu.setCharacterSize(39);
    backToMenu.setFillColor(sf::Color::Yellow);
    backToMenu.setFont(font);

    for (int i = 0; i < menu.size(); ++i)
    {
        if (selected[i])
        {
            backToMenu.setString(cursor + menu[i]);
        }
        else
        {
            backToMenu.setString(menu[i]);
        }

        if (pressed[i])
        {
            backToMenu.setFillColor({127, 127, 0});
        }
        else
        {
            backToMenu.setFillColor(sf::Color::Yellow);
        }

        sf::FloatRect backRect = backToMenu.getLocalBounds();
        backToMenu.setOrigin(backRect.left + backRect.width/2.0f,backRect.top - backRect.height*(1.5f+(float)i*2.0f));
        backToMenu.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));
        window.draw(backToMenu);
    }

    sf::Text blank;
    blank.setCharacterSize(45);
    blank.setFillColor(sf::Color::Yellow);
    blank.setFont(font);
    blank.setString("_ _ _ _ _ _ _");

    sf::FloatRect blankRect = blank.getLocalBounds();
    blank.setOrigin(blankRect.left + blankRect.width/2.0f,blankRect.top + blankRect.height*0.5f);
    blank.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));
    window.draw(blank);

    // draws the player's input
    sf::Text cheat;
    cheat.setCharacterSize(44);
    cheat.setFillColor(sf::Color::Yellow);
    cheat.setFont(font);
    cheat.setString(input);

    cheat.setOrigin(blankRect.left + blankRect.width/2.0f,blankRect.top + blankRect.height*0.6f);
    cheat.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));
    window.draw(cheat);
}

// draws the cheats window and reads the player's input
void GameWindow::cheatsWindow(sf::RenderWindow &window, std::vector<bool>& cheat_modes, sf::Sound& bark)
{
    std::string cheat;
    std::vector<bool> selected = {true, false};
    std::vector<bool> pressed = {false, false};
    bool just_activated = false;

    sf::Font font;
    font.loadFromFile("./fonts/Ticketing.ttf");

    sf::Text message;
    message.setFont(font);
    message.setCharacterSize(37);
    message.setFillColor(sf::Color::Yellow);
    message.setString("");

    sf::FloatRect messageRect = message.getLocalBounds();
    message.setOrigin(messageRect.left + messageRect.width/2.0f,messageRect.top + messageRect.height*4.5f);
    message.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));

    while (window.isOpen())
    {
        sf::Event event {};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    // checks what option was pressed
                    for (int i = 0; i < selected.size(); ++i)
                    {
                        if (selected[i])
                        {
                            pressed[i] = true;
                        }
                    }
                }
            }

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    // if 'ENTER' is pressed, check if the cheat code is valid
                    if (pressed[0])
                    {
                        pressed[0] = false;

                        // if the cheat code is valid, then activate the corresponding benefits
                        if (cheat == "G O D M O D E " || cheat == "D O G M O D E " || cheat == "G E T P I N G ")
                        {
                            if (cheat == "G O D M O D E ")
                            {
                                if (cheat_modes[0])
                                {
                                    message.setString("TELEPORTING...");
                                    just_activated = true;
                                }
                                else
                                {
                                    cheat_modes[0] = true;
                                    message.setString("TELEPORT WITH E");
                                    just_activated = true;
                                }
                            }

                            if (cheat == "G E T P I N G ")
                            {
                                if (cheat_modes[1])
                                {
                                    message.setString("OVERWRITING IMAGE");
                                    just_activated = true;
                                }
                                else
                                {
                                    cheat_modes[1] = true;
                                    message.setString("SAVING MAZE.PNG");
                                    just_activated = true;
                                }
                            }

                            if (cheat == "D O G M O D E ")
                            {
                                if (cheat_modes[2])
                                {
                                    message.setString("UNINTELLIGIBLE");
                                    bark.play();
                                    just_activated = true;
                                }
                                else
                                {
                                    cheat_modes[2] = true;
                                    message.setString("BARK AWAY!");
                                    just_activated = true;
                                }
                            }
                        }
                        else
                        {
                            message.setString("NOTHING HAPPENS");
                            just_activated = true;
                        }

                        // updates the message's location in the screen
                        messageRect = message.getLocalBounds();
                        message.setOrigin(messageRect.left + messageRect.width/2.0f,messageRect.top + messageRect.height*4.5f);
                        message.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));
                    }

                    // if 'RETURN' was pressed, return to the main menu
                    if (pressed[1])
                    {
                        return;
                    }

                    cheat = "";
                }

                // deletes one character from the player's input
                if (event.key.code == sf::Keyboard::Delete || event.key.code == sf::Keyboard::BackSpace)
                {
                    cheat = cheat.substr(0, cheat.size()-2);
                }

                if (event.key.code == sf::Keyboard::Up)
                {
                    for (int i = 0; i < selected.size(); ++i)
                    {
                        if (selected[i] && i > 0 && !pressed[i])
                        {
                            selected[i] = false;
                            selected[i-1] = true;
                            break;
                        }
                    }
                }

                if (event.key.code == sf::Keyboard::Down)
                {
                    for (int i = 0; i < selected.size(); ++i)
                    {
                        if (selected[i] && i < selected.size() - 1 && !pressed[i])
                        {
                            selected[i] = false;
                            selected[i+1] = true;
                            break;
                        }
                    }
                }
            }

            // reads the player's input for the cheat code
            if (event.type == sf::Event::TextEntered)
            {
                // adds the character entered if it is valid
                if (cheat.size() < 13 && isalpha(event.text.unicode))
                {
                    cheat += toupper(event.text.unicode);
                    cheat += " ";
                }
            }
        }

        window.clear(sf::Color::Black);
        drawTitle(window);
        drawBackground(window, false, true, false);
        drawCheats(window, cheat, selected, pressed);
        window.draw(message);
        window.display();

        // displays a message if a cheat code was entered
        if (just_activated)
        {
            just_activated = false;
            message.setString("");
            sf::sleep(sf::milliseconds(700));
        }
    }
}

// selects a maze generation algorithm depending on how many mazes the player has solved
std::vector<std::vector<bool>> GameWindow::chooseMazeAlgorithm(Maze& maze, int wins)
{
    maze.resetMaze();

    if (wins % 4 == 1)
    {
        maze.randomizedKruskal();
    }

    if (wins % 4 == 2)
    {
        maze.randomizedDFS();
    }

    if (wins % 4 == 3)
    {
        maze.randomizedPrim();
    }

    if (wins % 4 == 0)
    {
        maze.binaryTree();
    }

    return maze.convertToBinaryMatrix();
}

// draws the instructions
void GameWindow::drawInstructions(sf::RenderWindow &window, bool& pressed)
{
    sf::Font font;
    font.loadFromFile("./fonts/Ticketing.ttf");

    sf::Text backToMenu;
    backToMenu.setCharacterSize(39);
    backToMenu.setFillColor(sf::Color::Yellow);
    backToMenu.setFont(font);
    backToMenu.setString("> RETURN");

    sf::FloatRect backRect = backToMenu.getLocalBounds();
    backToMenu.setOrigin(backRect.left + backRect.width/2.0f,backRect.top - backRect.height*3.5f);
    backToMenu.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));

    sf::Text instruction;
    instruction.setFont(font);
    instruction.setCharacterSize(39);
    instruction.setFillColor(sf::Color::Yellow);

    std::vector<std::string> instructions = {"W: FORWARD", "A: LEFT", "S: BACKWARD", "D: RIGHT"};

    for (int i = 0; i < instructions.size(); ++i)
    {
        instruction.setString(instructions[i]);
        sf::FloatRect optionsRect = instruction.getLocalBounds();
        instruction.setOrigin(optionsRect.left + optionsRect.width/2.0f,optionsRect.top + optionsRect.height*(4.5f-(float)i*2.0f));
        instruction.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));
        window.draw(instruction);
    }

    if (!pressed)
    {
        window.draw(backToMenu);
    }
    else
    {
        backToMenu.setFillColor({127, 127, 0});
        window.draw(backToMenu);
    }
}

// creates the instructions window and reads the player's input
void GameWindow::instructionsWindow(sf::RenderWindow &window)
{
    bool pressed = false;

    while (window.isOpen())
    {
        sf::Event event {};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    pressed = true;
                }
            }

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    return;
                }
            }
        }

        window.clear(sf::Color::Black);
        drawTitle(window);
        drawBackground(window, false, true, false);
        drawInstructions(window, pressed);
        window.display();
    }
}

// checks if the maze was solved by the player
bool GameWindow::mazeSolved(int x, int y, int size)
{
    if (x > 2*size && y > size-1)
    {
        return true;
    }

    return false;
}

// draws the available difficulty options
void GameWindow::drawDifficulty(sf::RenderWindow &window, std::vector<bool> selected_option, std::vector<bool> &pressed)
{
    std::string select = "CHOOSE ONE:";
    std::string cursor = "> ";
    std::vector<std::string> difficulties = {"EASY", "MEDIUM", "HARD", "NIGHTMARE"};

    sf::Font font;
    font.loadFromFile("./fonts/Ticketing.ttf");

    sf::Text option;
    option.setFont(font);
    option.setFillColor(sf::Color::Yellow);
    option.setCharacterSize(39);
    option.setString(select);

    sf::FloatRect optionsRect = option.getLocalBounds();
    option.setOrigin(optionsRect.left + optionsRect.width/2.0f,optionsRect.top + optionsRect.height*4.5f);
    option.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));
    window.draw(option);

    for (int i = 0; i < difficulties.size(); ++i)
    {
        if (selected_option[i])
        {
            option.setString(cursor + difficulties[i]);
        }
        else
        {
            option.setString(difficulties[i]);
        }

        if (pressed[i])
        {
            option.setFillColor({127, 127, 0});
        }
        else
        {
            option.setFillColor(sf::Color::Yellow);
        }


        optionsRect = option.getLocalBounds();
        option.setOrigin(optionsRect.left + optionsRect.width/2.0f,optionsRect.top + optionsRect.height*(2.5f-(float)i*2.0f));
        option.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));
        window.draw(option);
    }
}

// draws the difficulty selection window and reads the player's input
void GameWindow::difficultySelectionWindow(sf::RenderWindow &window, sf::Sound& sound, std::vector<bool> cheat_modes)
{
    std::vector<bool> selected_option = {true, false, false, false};
    std::vector<bool> pressed = {false, false, false, false};

    while(window.isOpen())
    {
        sf::Event event {};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Down)
                {
                    for (int i = 0; i < selected_option.size(); ++i)
                    {
                        if (selected_option[i] && i < selected_option.size() - 1 && !pressed[i])
                        {
                            selected_option[i] = false;
                            selected_option[i+1] = true;
                            break;
                        }
                    }
                }

                if (event.key.code == sf::Keyboard::Up)
                {
                    for (int i = 0; i < selected_option.size(); ++i)
                    {
                        if (selected_option[i] && i > 0 && !pressed[i])
                        {
                            selected_option[i] = false;
                            selected_option[i-1] = true;
                            break;
                        }
                    }
                }

                if (event.key.code == sf::Keyboard::Enter)
                {
                    sound.play();
                    gameWindow(window, pressed, cheat_modes);
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    for (int i = 0; i < selected_option.size(); ++i)
                    {
                        if (selected_option[i])
                        {
                            pressed[i] = true;
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        drawBackground(window, false, false, true);
        drawTitle(window);
        drawDifficulty(window, selected_option, pressed);

        window.display();
    }
}

// draws the main menu
void GameWindow::drawMainMenu(sf::RenderWindow &window, std::vector<bool> selected_option, bool& music_on, std::vector<bool>& pressed)
{
    std::vector<std::string> options = {"START", "INSTRUCTIONS", "MUSIC ", "CHEATS", "QUIT"};
    std::string cursor = "> ";
    std::string music_status;

    if (!music_on)
    {
        music_status = "ON";
    }
    else
    {
        music_status = "OFF";
    }

    sf::Font font;
    font.loadFromFile("./fonts/Ticketing.ttf");

    sf::Text option;
    option.setFont(font);
    option.setFillColor(sf::Color::Yellow);
    option.setCharacterSize(39);
    sf::FloatRect optionRect;

    for (int i = 0; i < options.size(); ++i)
    {
        std::string setting = options[i];

        if (i == 2)
        {
            setting = setting + music_status;
        }

        if (selected_option[i])
        {
            option.setString(cursor + setting);
        }
        else
        {
            option.setString(setting);
        }

        if (pressed[i])
        {
            option.setFillColor({127, 127, 0});
        }
        else
        {
            option.setFillColor(sf::Color::Yellow);
        }


        optionRect = option.getLocalBounds();
        option.setOrigin(optionRect.left + optionRect.width/2.0f,optionRect.top + optionRect.height*(4.5f-(float)i*2.0f));
        option.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));

        window.draw(option);
    }
}

void GameWindow::mainMenuWindow(sf::RenderWindow& window, sf::Music& music, sf::Sound& sound)
{
    std::vector<bool> selected_option = {true, false, false, false, false};
    std::vector<bool> pressed = {false, false, false, false, false};
    std::vector<bool> cheat_modes = {false, false, false};
    bool music_on = true;

    sf::SoundBuffer buffer;
    buffer.loadFromFile("./music/cat2.wav");
    sf::Sound bark;
    bark.setBuffer(buffer);

    while(window.isOpen())
    {
        sf::Event event {};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Down)
                {
                    for (int i = 0; i < selected_option.size(); ++i)
                    {
                        if (selected_option[i] && i < selected_option.size() - 1 && !pressed[i])
                        {
                            selected_option[i] = false;
                            selected_option[i+1] = true;
                            break;
                        }
                    }
                }

                if (event.key.code == sf::Keyboard::Up)
                {
                    for (int i = 0; i < selected_option.size(); ++i)
                    {
                        if (selected_option[i] && i > 0 && !pressed[i])
                        {
                            selected_option[i] = false;
                            selected_option[i-1] = true;
                            break;
                        }
                    }
                }

                if (event.key.code == sf::Keyboard::Enter)
                {
                    // starts the difficulty selection window
                    if (selected_option[0])
                    {
                        sound.play();
                        pressed[0] = false;
                        difficultySelectionWindow(window, sound, cheat_modes);
                    }

                    // starts the instructions window
                    if (selected_option[1])
                    {
                        pressed[1] = false;
                        instructionsWindow(window);
                    }

                    // activates and deactivates the music
                    if (selected_option[2])
                    {
                        music_on = !music_on;

                        if (music_on)
                        {
                            music.play();
                        }
                        else
                        {
                            music.pause();
                        }

                        pressed[2] = false;
                    }

                    // starts the cheats window
                    if (selected_option[3])
                    {
                        pressed[3] = false;
                        cheatsWindow(window, cheat_modes, bark);
                    }

                    // closes the window
                    if (selected_option[4])
                    {
                        window.close();
                    }

                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    for (int i = 0; i < selected_option.size(); ++i)
                    {
                        if (selected_option[i])
                        {
                            pressed[i] = true;
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::Black);

        drawBackground(window, false, true, false);
        drawTitle(window);
        drawMainMenu(window, selected_option, music_on, pressed);

        window.display();
    }
}

// draws the title of the game
void GameWindow::drawTitle(sf::RenderWindow& window)
{
    sf::Text title;
    title.setString("MAZE RUNNER");

    sf::Font fontTitle;
    fontTitle.loadFromFile("./fonts/RUBBBB__.TTF");
    title.setFont(fontTitle);

    sf::FloatRect titleRect;

    title.setFillColor(sf::Color::Yellow);
    title.setCharacterSize(71);
    titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width/2.0f,titleRect.top + titleRect.height*4.5f);
    title.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));
    window.draw(title);

    title.setFillColor(sf::Color::Red);
    title.setCharacterSize(70);
    titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width/2.0f,titleRect.top + titleRect.height*4.6f);
    title.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));
    window.draw(title);
}

// draws the window's background
void GameWindow::drawBackground(sf::RenderWindow &window, bool front = true, bool left = false, bool right = false)
{
    // draws the walls
    sf::Vertex line[2] =
            {
                    sf::Vertex(sf::Vector2f(0, 0), sf::Color::Yellow),
                    sf::Vertex(sf::Vector2f(SCREEN_WIDTH/4.0f, SCREEN_HEIGHT/4.0f), sf::Color::Yellow)
            };
    window.draw(line , 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(0, SCREEN_HEIGHT), sf::Color::Yellow);
    line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/4.0f, SCREEN_HEIGHT*0.75f), sf::Color::Yellow);
    window.draw(line , 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/4.0f, SCREEN_HEIGHT/4.0f), sf::Color::Yellow);
    line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/4.0f, SCREEN_HEIGHT*0.75f), sf::Color::Yellow);
    window.draw(line , 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH, 0), sf::Color::Yellow);
    line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.75f, SCREEN_HEIGHT/4.0f), sf::Color::Yellow);
    window.draw(line , 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT), sf::Color::Yellow);
    line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.75f, SCREEN_HEIGHT*0.75f), sf::Color::Yellow);
    window.draw(line , 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.75f, SCREEN_HEIGHT/4.0f), sf::Color::Yellow);
    line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.75f, SCREEN_HEIGHT*0.75f), sf::Color::Yellow);
    window.draw(line , 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/4.0f, SCREEN_HEIGHT*0.75f), sf::Color::Yellow);
    line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.75f, SCREEN_HEIGHT*0.75f), sf::Color::Yellow);
    window.draw(line , 2, sf::Lines);

    line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/4.0f, SCREEN_HEIGHT/4.0f), sf::Color::Yellow);
    line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.75f, SCREEN_HEIGHT/4.0f), sf::Color::Yellow);
    window.draw(line , 2, sf::Lines);

    // draws the front door
    if (front)
    {
        line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/2.5f, SCREEN_WIDTH*0.75f), sf::Color::Yellow);
        line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/2.5f, SCREEN_HEIGHT/2.5f), sf::Color::Yellow);
        window.draw(line , 2, sf::Lines);

        line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.6f, SCREEN_WIDTH/2.5f), sf::Color::Yellow);
        line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.6f, SCREEN_HEIGHT*0.75f), sf::Color::Yellow);
        window.draw(line , 2, sf::Lines);

        line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/2.5f, SCREEN_HEIGHT/2.5f), sf::Color::Yellow);
        line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.6f, SCREEN_WIDTH/2.5f), sf::Color::Yellow);
        window.draw(line , 2, sf::Lines);
    }

    // draws the left door
    if (left)
    {
        line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/16.0f, SCREEN_WIDTH*0.935f), sf::Color::Yellow);
        line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/16.0f, SCREEN_WIDTH/3.0f), sf::Color::Yellow);
        window.draw(line , 2, sf::Lines);

        line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/6.0f, SCREEN_WIDTH/2.5f), sf::Color::Yellow);
        line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/6.0f, SCREEN_HEIGHT*0.835f), sf::Color::Yellow);
        window.draw(line , 2, sf::Lines);

        line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/16.0f, SCREEN_WIDTH/3.0f), sf::Color::Yellow);
        line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH/6.0f, SCREEN_WIDTH/2.5f), sf::Color::Yellow);
        window.draw(line , 2, sf::Lines);
    }

    // draws the right door
    if (right)
    {
        line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.935f, SCREEN_WIDTH*0.935f), sf::Color::Yellow);
        line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.935f, SCREEN_WIDTH/3.0f), sf::Color::Yellow);
        window.draw(line , 2, sf::Lines);

        line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.835f, SCREEN_WIDTH/2.5f), sf::Color::Yellow);
        line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.835f, SCREEN_HEIGHT*0.835f), sf::Color::Yellow);
        window.draw(line , 2, sf::Lines);

        line[0] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.935f, SCREEN_WIDTH/3.0f), sf::Color::Yellow);
        line[1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH*0.835f, SCREEN_WIDTH/2.5f), sf::Color::Yellow);
        window.draw(line , 2, sf::Lines);
    }
}

// draws the welcome window
void GameWindow::welcomeWindow()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                            "Maze Runner", sf::Style::Close);

    sf::Font fontSubtitle;
    sf::Text subtitle;
    sf::Text footnote;

    sf::SoundBuffer buffer;
    buffer.loadFromFile("./music/door-creak.wav");
    sf::Sound sound;
    sound.setBuffer(buffer);

    sf::Music music;
    music.openFromFile("./music/ferambie.wav");
    music.setLoop(true);
    music.play();

    fontSubtitle.loadFromFile("./fonts/Ticketing.ttf");

    subtitle.setFont(fontSubtitle);
    footnote.setFont(fontSubtitle);

    subtitle.setString("PUSH ENTER TO CONTINUE");
    footnote.setString("2023 Maze Generation Games. All Rights Reserved");

    footnote.setFillColor(sf::Color::Yellow);
    subtitle.setFillColor(sf::Color::Yellow);

    subtitle.setCharacterSize(39);
    footnote.setCharacterSize(23);

    sf::FloatRect subtitleRect = subtitle.getLocalBounds();
    subtitle.setOrigin(subtitleRect.left + subtitleRect.width/2.0f,subtitleRect.top - subtitleRect.height*8.5f);
    subtitle.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));

    sf::FloatRect footnoteRect = footnote.getLocalBounds();
    footnote.setOrigin(footnoteRect.left + footnoteRect.width/2.0f,footnoteRect.top - footnoteRect.height*18.0f);
    footnote.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));

    while(window.isOpen())
    {
        sf::Event event {};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    subtitle.setColor({127, 127, 0});
                }
            }

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    sound.play();
                    sf::sleep(sf::milliseconds(200));
                    mainMenuWindow(window, music, sound);
                }
            }
        }

        window.clear(sf::Color::Black);

        drawBackground(window);
        drawTitle(window);

        window.draw(subtitle);
        window.draw(footnote);

        window.display();
    }
}

/* this function creates and draws the game window. the player's movement and the way the 3d maze is displayed
 * is based on code from this article and GitHub repository (image files were also taken from the repo):
 * https://www.raspberrypi.com/news/recreate-3d-monster-mazes-8-bit-labyrinth-wireframe-issue-18/
 * https://github.com/Wireframe-Magazine/Wireframe18 */
void GameWindow::gameWindow(sf::RenderWindow& window, std::vector<bool> difficulty, std::vector<bool> cheat_modes)
{
    std::vector<int> sizes = {3, 10, 100, 317};
    int size = 0;
    int num_wins = 0;

    sf::Font font;
    font.loadFromFile("./fonts/Pixel Takhisis.ttf");

    sf::Text message;
    message.setFillColor(sf::Color::Red);
    message.setCharacterSize(20);
    message.setFont(font);

    sf::Text timer;
    timer.setFillColor(sf::Color::Red);
    timer.setCharacterSize(40);
    timer.setFont(font);

    sf::FloatRect messageRect = message.getLocalBounds();
    message.setOrigin(messageRect.left + messageRect.width/2.0f,messageRect.top - messageRect.height*18.0f);
    message.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));

    sf::FloatRect timerRect;

    bool just_started = true;
    bool first_maze = true;
    std::chrono::duration<double> seconds{};

    Maze maze;

    // sets the maze's dimensions depending on the difficulty
    for (int i = 0; i < difficulty.size(); ++i)
    {
        if (difficulty[i])
        {
            maze.setDimensions(sizes[i], sizes[i]);
            size = sizes[i];
        }
    }

    auto start = std::chrono::system_clock::now();
    maze.binaryTree();
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    // saves a .png image of the maze if "GETPING" was entered by the player in the cheats menu
    if (cheat_modes[1])
    {
        maze.drawMaze();
    }

    std::vector<std::vector<bool>> world = maze.convertToBinaryMatrix();

    int playerX = 1;
    int playerY = 1;
    int playerDir = 2;

    std::vector<int> dx = {-1, 0, 1, 0};
    std::vector<int> dy = {0, 1, 0, -1};

    sf::Texture back_texture;
    back_texture.loadFromFile("./images/back.png");

    sf::Sprite back;
    back.setTexture(back_texture);
    back.setColor({255, 255, 0});

    std::vector<sf::Texture> left_textures(5);
    std::vector<sf::Sprite> left_sprites(5);

    std::vector<sf::Texture> right_textures(5);
    std::vector<sf::Sprite> right_sprites(5);

    std::vector<sf::Texture> mid_textures(5);
    std::vector<sf::Sprite> mid_sprites(5);

    // loads the image files
    for (int i = 0; i < 5; ++i)
    {
        left_textures[i].loadFromFile("./images/left" + std::to_string(i) + ".png");
        left_sprites[i].setTexture(left_textures[i]);
        left_sprites[i].setColor({255, 255, 0});

        right_textures[i].loadFromFile("./images/right" + std::to_string(i) + ".png");
        right_sprites[i].setTexture(right_textures[i]);
        right_sprites[i].setColor({255, 255, 0});

        mid_textures[i].loadFromFile("./images/mid" + std::to_string(i) + ".png");
        mid_sprites[i].setTexture(mid_textures[i]);
        mid_sprites[i].setColor({255, 255, 0});
    }

    auto s_timer = std::chrono::system_clock::now();

    while(window.isOpen())
    {
        sf::Event event {};

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::W) // move forward
                {
                    int newX = playerX + dx[playerDir];
                    int newY = playerY + dy[playerDir];

                    if (mazeSolved(newX, newY, size))
                    {
                        // creates a new maze if the maze was solved
                        playerX = 1;
                        playerY = 1;

                        ++num_wins;

                        start = std::chrono::system_clock::now();
                        world = chooseMazeAlgorithm(maze, num_wins);
                        end = std::chrono::system_clock::now();
                        elapsed_seconds = end - start;

                        just_started = true;

                        // saves a .png image of the maze
                        if (cheat_modes[1])
                        {
                            maze.drawMaze();
                        }

                        sf::sleep(sf::milliseconds(300));
                    }
                    else
                    {
                        // checks if there's a wall in front of the player
                        if (!world[newX][newY])
                        {
                            if (first_maze)
                            {
                                s_timer = std::chrono::system_clock::now();
                                first_maze = false;
                            }

                            just_started = false;

                            // changes the position of the player
                            playerX = newX;
                            playerY = newY;
                        }
                    }
                }
                if (event.key.code == sf::Keyboard::S) // move backward
                {
                    int newX = playerX - dx[playerDir];
                    int newY = playerY - dy[playerDir];

                    if (mazeSolved(newX, newY, size))
                    {
                        // creates a new maze if the maze was solved
                        playerX = 1;
                        playerY = 1;

                        ++num_wins;

                        start = std::chrono::system_clock::now();
                        world = chooseMazeAlgorithm(maze, num_wins);
                        end = std::chrono::system_clock::now();
                        elapsed_seconds = end - start;

                        just_started = true;

                        // saves a .png image of the maze
                        if (cheat_modes[1])
                        {
                            maze.drawMaze();
                        }
                    }
                    else
                    {
                        // checks if there is a wall behind the player
                        if (!world[newX][newY])
                        {
                            if (first_maze)
                            {
                                s_timer = std::chrono::system_clock::now();
                                first_maze = false;
                            }

                            just_started = false;

                            // changes the position of the player
                            playerX = newX;
                            playerY = newY;
                        }
                    }
                }

                if (event.key.code == sf::Keyboard::A) // rotate to the left
                {
                    --playerDir;

                    if (playerDir < 0)
                    {
                        playerDir = 3;
                    }
                }

                if (event.key.code == sf::Keyboard::D) // rotate to the right
                {
                    ++playerDir;

                    if (playerDir > 3)
                    {
                        playerDir = 0;
                    }
                }

                // creates a new maze when E is released if "GODMODE" was entered by the player in the cheats menu
                if (event.key.code == sf::Keyboard::E && cheat_modes[0])
                {
                    playerX = 1;
                    playerY = 1;

                    ++num_wins;

                    start = std::chrono::system_clock::now();
                    world = chooseMazeAlgorithm(maze, num_wins);
                    end = std::chrono::system_clock::now();
                    elapsed_seconds = end - start;

                    just_started = true;

                    if (cheat_modes[1])
                    {
                        maze.drawMaze();
                    }
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(back);

        int dm = 1;

        if (playerDir == 1 || playerDir == 3)
        {
            dm = -1;
        }

        for (int i = 4; i > -1; --i)
        {
            int x = playerX + (i * dx[playerDir]);
            int y = playerY + (i * dy[playerDir]);

            if (x >= 0 && x < 2*size+1 && y >= 0 && y < 2*size+1)
            {
                int xl = x + (dy[playerDir] * dm);
                int yl = y + (dx[playerDir] * dm);

                if (world[xl][yl])
                {
                    window.draw(left_sprites[i]);
                }

                int xr = x - (dy[playerDir] * dm);
                int yr = y - (dx[playerDir] * dm);

                if (world[xr][yr])
                {
                    window.draw(right_sprites[i]);
                }

                if (world[x][y])
                {
                    window.draw(mid_sprites[i]);
                }
            }
        }

        // displays the level and the time the maze generation algorithm took
        if (just_started)
        {
            if (difficulty[0] || difficulty[1])
            {
                message.setString("Level " + std::to_string(num_wins+1) + ": generated in " + std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_seconds).count()) + " ns");
            }


            if (difficulty[2] || difficulty[3])
            {
                message.setString("Level " + std::to_string(num_wins+1) + ": generated in " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_seconds).count()) + " ms");
            }

            messageRect = message.getLocalBounds();
            message.setOrigin(messageRect.left + messageRect.width/2.0f,messageRect.top - messageRect.height*17.0f);
            message.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));

            window.draw(message);
        }

        if (first_maze)
        {
            seconds = s_timer - s_timer;
        }
        else
        {
            auto e_timer = std::chrono::system_clock::now();
            if (!just_started)
            {
                seconds = e_timer - s_timer;
            }
            else
            {
                seconds = s_timer - s_timer;
                s_timer = std::chrono::system_clock::now();
            }
        }

        int sec = std::chrono::duration_cast<std::chrono::seconds>(seconds).count() % 60;
        int min = std::chrono::duration_cast<std::chrono::seconds>(seconds).count() / 60;
        std::string time = std::to_string(sec);

        if (time.length() < 2)
        {
            time = "0" + time;
        }

        time = std::to_string(min) + " : " + time;

        if (time.length() < 7)
        {
            time = "0" + time;
        }

        // displays the stopwatch
        timer.setString(time);

        timerRect = timer.getLocalBounds();
        timer.setOrigin(timerRect.left + timerRect.width/2.0f,timerRect.top + timerRect.height*10.0f);
        timer.setPosition(sf::Vector2f(SCREEN_WIDTH/2.0f,SCREEN_HEIGHT/2.0f));

        window.draw(timer);

        window.display();
    }
}
