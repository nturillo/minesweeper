#include "Button.h"

Button::Button() {
    sprite = sf::Sprite();
}

Button::Button(const sf::Texture& texture)
    : sprite{ texture }
{
}

bool Button::checkClick(const sf::Vector2<float>& mousePos)
{
    auto bounds = sprite.getGlobalBounds();

    if (mousePos.x >= bounds.left && mousePos.x <= bounds.left + bounds.width &&
        mousePos.y >= bounds.top && mousePos.y <= bounds.top + bounds.height) {
        return true;
    }
    return false;
}

void Button::setPosition(const sf::Vector2<float>& position)
{
    sprite.setPosition(position);
}

void Button::setTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
}

const sf::Vector2<float>& Button::getPosition() const {
    return sprite.getPosition();
}

const sf::Vector2<float>& Button::getSize() const {
    auto bounds = sprite.getGlobalBounds();
    return sf::Vector2<float>(bounds.width, bounds.height);
}

void Button::draw(sf::RenderWindow* window) {
    window->draw(sprite);
}