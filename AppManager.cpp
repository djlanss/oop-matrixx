#include "AppManager.h"
#include "Console.h"
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <thread>

// Creates an application manager with the specified parameters
ApplicationManager::ApplicationManager(int speed, int length, char epilepsyMode)
    : speed(speed),
    length(length),
    epilepsyMode(epilepsyMode),
    line(nullptr)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

// Runs the Matrix application
void ApplicationManager::run()
{
    Console::clear();
    while (true)
    {
        createLine();

        while (!isLineFinished())
        {
            line->move();

            renderNewCharacter();
            clearRemovedCharacter();

            std::this_thread::sleep_for(
                std::chrono::milliseconds(1000 / speed)
            );
        }

        line.reset();
    }
}

// Creates a new line at a random row, entering from the right edge
void ApplicationManager::createLine()
{
    int consoleHeight = Console::getHeight();
    int y = 0;

    if (consoleHeight > 1)
    {
        y = std::rand() % (consoleHeight - 1);
    }

    int x = Console::getWidth();

    line = std::make_unique<Line>(length, x, y, epilepsyMode);
}

// Renders the newly generated character
void ApplicationManager::renderNewCharacter()
{
    int characterX = line->getNewCharacterX();

    if (characterX >= 0 && characterX < Console::getWidth())
    {
        Console::setCursorPosition(
            characterX,
            line->getNewCharacterY()
        );

        Console::writeCharacter(line->getNewCharacter());
    }
}

// Clears the character removed from the end
void ApplicationManager::clearRemovedCharacter()
{
    if (!line->hasRemovedCharacter())
    {
        return;
    }

    int characterX = line->getRemovedCharacterX();

    if (characterX >= 0 && characterX < Console::getWidth())
    {
        Console::clearCharacter(
            characterX,
            line->getRemovedCharacterY()
        );
    }
}

// Checks whether the line has completely left the console
bool ApplicationManager::isLineFinished() const
{
    return line->getX() + line->getLength() <= 0;
}