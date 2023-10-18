#include "GreyTile.h"
#include <iostream>

GreyTile::GreyTile() : Tile::Tile() {
	isBomb = false;
	for (int i = 0; i < 8; i++) {
		neighbors[i] = nullptr;
	}
}

void GreyTile::setIsBomb(const bool value) {
	isBomb = value;
}

void GreyTile::setIsFlagged(const bool value) {
	isFlagged = value;
}

void GreyTile::setNeighbor(unsigned int index, GreyTile* neighbor) {
	neighbors[index] = neighbor;
}

const bool GreyTile::getIsBomb() const {
	return isBomb;
}

const bool GreyTile::getIsFlagged() const {
	return isFlagged;
}

const bool GreyTile::reveal() {
	if (isBomb) {
		sprites[0].setTexture(TextureManager::getTexture("tile_revealed"));
		spriteState = BOTH;
		return true;
	}
	else {
		this->recursiveReveal();
		return false;
	}
}

void GreyTile::recursiveReveal() {
	if (revealed) {
		return;
	}
	revealed = true;

	int neighborBombNum = 0;
	for (int i = 0; i < 8; i++) {
		if (neighbors[i] != nullptr && neighbors[i]->getIsBomb()) {
			neighborBombNum++;
		}
	}

	sprites[0].setTexture(TextureManager::getTexture("tile_revealed"));

	if (neighborBombNum > 0) {
		sprites[1].setTexture(TextureManager::getNumTexture(neighborBombNum));
		spriteState = BOTH;
	}
	else {
		for (int i = 0; i < 8; i++) {
			if (neighbors[i] != nullptr && !neighbors[i]->getIsFlagged()) {
				neighbors[i]->recursiveReveal();
			}
		}
	}
}

