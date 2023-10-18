//#pragma once

#include <SFML/Graphics.hpp>

class Button
{
public:
    Button();
    Button(const sf::Texture& texture);

    void setTexture(const sf::Texture& texture);
    void setPosition(const sf::Vector2<float>& position);
    const sf::Vector2<float>& getPosition() const;
    const sf::Vector2<float>& getSize() const;

    bool checkClick(const sf::Vector2<float>& mousePos);
    void draw(sf::RenderWindow* window);

private:
    sf::Sprite sprite;
};
