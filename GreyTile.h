#pragma once
#include "Tile.h"
class GreyTile :    public Tile
{
public:
    GreyTile();
    void setIsBomb(const bool& value);
    void setIsFlagged(const bool& value);
    void setNeighbor(unsigned int index, GreyTile* neighbor);
    const bool& getIsBomb() const;
    const bool& getIsFlagged() const;


    const bool& reveal();
    void recursiveReveal();
private:
    bool isFlagged = false;
    bool isBomb = false;
    GreyTile* neighbors[8];
};

