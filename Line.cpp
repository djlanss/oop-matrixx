#include "Line.h"
#include <cstdlib>

// Creates a line with the specified parameters
Line::Line(int length, int x, int y, char epilepsyMode)
    : length(length),
    x(x),
    y(y),
    epilepsyMode(epilepsyMode),
    removedCharacterX(0),          
    characterRemoved(false)
{

    if (epilepsyMode == 'Y' || epilepsyMode == 'y')
    {
        lineColor = static_cast<CharacterColor>(std::rand() % 7);
    }
    else
    {
        lineColor = CharacterColor::Green;
    }
}

// Moves the line one step to the left
void Line::move()
{
    --x;                                   
    characterRemoved = false;

    characters.push_front(createCharacter());

    if (static_cast<int>(characters.size()) > length)
    {
        removedCharacterX = x + length;     
        characters.pop_back();
        characterRemoved = true;
    }
}

int Line::getLength() const
{
    return length;
}

int Line::getX() const
{
    return x;
}

int Line::getY() const
{
    return y;
}

const Character& Line::getNewCharacter() const
{
    return characters.front();
}


int Line::getNewCharacterX() const
{
    return x;
}

int Line::getNewCharacterY() const
{
    return y;
}

bool Line::hasRemovedCharacter() const
{
    return characterRemoved;
}

int Line::getRemovedCharacterX() const
{
    return removedCharacterX;
}

int Line::getRemovedCharacterY() const
{
    return y;
}

// Creates a new character with the line's color
Character Line::createCharacter() const
{
    char symbol = static_cast<char>('A' + std::rand() % 26);
    return Character(symbol, lineColor);    // ИЗМЕНЕНО: один цвет на всю линию
}

