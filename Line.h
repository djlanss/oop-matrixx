#pragma once

#include <deque>
#include "Character.h"

// Represents a line moving from right to left (horizontal)
class Line
{
public:
    Line(int length, int x, int y, char epilepsyMode);

    void move();

    int getLength() const;
    int getX() const;   
    int getY() const;  

    const Character& getNewCharacter() const;
    int getNewCharacterX() const;
    int getNewCharacterY() const;

    bool hasRemovedCharacter() const;
    int getRemovedCharacterX() const;
    int getRemovedCharacterY() const;

private:
    // Creates a new character with the line's color
    Character createCharacter() const;


    int length;
    int x;
    int y;
    char epilepsyMode;

    CharacterColor lineColor;   

    std::deque<Character> characters;

    int removedCharacterX;     
    bool characterRemoved;
};