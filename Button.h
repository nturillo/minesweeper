//#pragma once

#include <SFML/Graphics.hpp>

class Button
{
public:
    Button();
    Button(const sf::Texture& texture);

    void setTexture(const sf::Texture& texture);
    void setPosition(const sf::Vector2f& position);
    const sf::Vector2f& getPosition() const;
    const sf::Vector2f& getSize() const;

    bool checkClick(const sf::Vector2f& mousePos);
    void draw(sf::RenderWindow* window);

private:
    sf::Sprite sprite;
};
