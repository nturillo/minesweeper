#include "Tile.h"

#include <iostream>

Tile::Tile() {
	sprites[0] = sf::Sprite();
	sprites[1] = sf::Sprite();
	position = sf::Vector2<float>();
	revealed = false;
	spriteState = UNDER;
}

void Tile::setIsRevealed(bool& value) {
	revealed = value;
}

void Tile::setSpriteState(const SpriteState& spriteState) {
	this->spriteState = spriteState;
}

void Tile::setExactPosition(const sf::Vector2<float>& exactPosition) {
	this->position = exactPosition;
	sprites[0].setPosition(exactPosition);
	sprites[1].setPosition(exactPosition);
}

void Tile::setBoardPosition(const sf::Vector2<int>& boardPosition) {
	//Calculate exact position based on board position and cell size
	const sf::Vector2<float> exactPosition = sf::Vector2<float>(tileSize.x * boardPosition.x, tileSize.y * boardPosition.y);
	this->position = exactPosition;
	sprites[0].setPosition(exactPosition);
	sprites[1].setPosition(exactPosition);
}

void Tile::setTexture(const sf::Texture& texture, const unsigned short& index) {
	sprites[index].setTexture(texture);
}

void Tile::setTileSize(const sf::Vector2<float>& tileSize) {
	this->tileSize = tileSize;
}

const bool& Tile::getIsRevealed() const {
	return revealed;
}

const Tile::SpriteState& Tile::getSpriteState() const {
	return spriteState;
}

const sf::Sprite& Tile::getSprite(const unsigned short& index) const {
	return sprites[index];
}

const sf::Vector2<float>& Tile::getExactPosition() const{
	return position;
}

const sf::Vector2<int>& Tile::getBoardPosition() const {
	return sf::Vector2<int>((int) position.x / tileSize.x, (int) position.y / tileSize.y);
}

void Tile::draw(sf::RenderWindow* window) {
	if (spriteState == UNDER || spriteState == BOTH) {
		window->draw(sprites[0]);
	}
	if (spriteState == OVER || spriteState == BOTH) {
		window->draw(sprites[1]);
	}
}