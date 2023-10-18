#pragma once

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "ConfigManager.h"

class Tile
{
public:
	enum SpriteState {
		UNDER, OVER, BOTH
	};

	Tile();
	void setIsRevealed(bool value);
	void setSpriteState(const SpriteState& spriteState);
	void setExactPosition(const sf::Vector2f& exactPosition);
	void setBoardPosition(const sf::Vector2i& boardPosition);
	void setTexture(const sf::Texture& texture, const unsigned short& index);
	void setTileSize(const sf::Vector2f& tileSize);
	const bool getIsRevealed() const;
	const SpriteState& getSpriteState() const;
	const sf::Sprite& getSprite(const unsigned short& index) const;
	const sf::Vector2f& getExactPosition() const;
	const sf::Vector2i& getBoardPosition() const;
	void draw(sf::RenderWindow* window);

	//virtual functions
	virtual const bool reveal() = 0;
protected:
	bool revealed;
	SpriteState spriteState;
	sf::Sprite sprites[2];
	sf::Vector2f position;
	sf::Vector2f tileSize = sf::Vector2f(32, 32);
};

