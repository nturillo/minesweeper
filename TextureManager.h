#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

class TextureManager
{
public:
    static void loadTexture(const std::string& name, const std::string& filename);
    static void loadMinesweeperTextures(std::string& imagesFile);
    static const sf::Texture& getTexture(const std::string& name);
    static const sf::Texture& getNumTexture(const int index);
    static void clear();

private:
    static std::unordered_map<std::string, sf::Texture> textures;
};


