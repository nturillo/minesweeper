#pragma once

#include <SFML/Graphics.hpp>

#include <math.h>



class Counter {
public:
	Counter();
	void setNumber(const int value);
	void setPosition(const sf::Vector2f& pos);
	void draw(sf::RenderWindow* window);
	Counter& operator++();
	Counter& operator--();
private:
	int value = 0;
	sf::Sprite digitSprites[4];
};