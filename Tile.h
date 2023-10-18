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
	void setIsRevealed(bool& value);
	void setSpriteState(const SpriteState& spriteState);
	void setExactPosition(const sf::Vector2<float>& exactPosition);
	void setBoardPosition(const sf::Vector2<int>& boardPosition);
	void setTexture(const sf::Texture& texture, const unsigned short& index);
	void setTileSize(const sf::Vector2<float>& tileSize);
	const bool& getIsRevealed() const;
	const SpriteState& getSpriteState() const;
	const sf::Sprite& getSprite(const unsigned short& index) const;
	const sf::Vector2<float>& getExactPosition() const;
	const sf::Vector2<int>& getBoardPosition() const;
	void draw(sf::RenderWindow* window);

	//virtual functions
	virtual const bool& reveal() = 0;
protected:
	bool revealed;
	SpriteState spriteState;
	sf::Sprite sprites[2];
	sf::Vector2<float> position;
	sf::Vector2<float> tileSize = sf::Vector2<float>(32, 32);
};

