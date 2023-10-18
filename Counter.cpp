#include "TextureManager.h"

#include "Counter.h"

Counter::Counter() {
	for (int i = 0; i < 4; i++) {
		digitSprites[i].setTexture(TextureManager::getTexture("digits"));
	}
	digitSprites[3].setTextureRect(sf::Rect<int>(210, 0, 21, 32));

}

void Counter::setNumber(const int value) {
	this->value = value;
	int absvalue = std::abs(value);
	char digits[3];
	for (int i = 0; i < 3; i++) {
		digits[i] = (absvalue / (int)(std::pow(10, i))) % 10;
		digitSprites[i].setTextureRect(sf::Rect<int>(digits[i] * 21, 0, 21, 32));
	}
}
void Counter::setPosition(const sf::Vector2f& pos) {
	for (int i = 0; i < 4; i++) {
		digitSprites[i].setPosition(pos + sf::Vector2f(21 * (3 - i), 0));
	}
}

void Counter::draw(sf::RenderWindow* window) {
	for (int i = 0; i < 3; i++) {
		window->draw(digitSprites[i]);
	}
	if (value < 0) {
		window->draw(digitSprites[3]);
	}
}

Counter& Counter::operator++() {
	setNumber(++value);
	return *this;
}

Counter& Counter::operator--() {
	setNumber(--value);
	return *this;
}