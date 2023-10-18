#include "TextureManager.h"

std::unordered_map<std::string, sf::Texture> TextureManager::textures;

void TextureManager::loadTexture(const std::string& name, const std::string& filename)
{
    sf::Texture texture;
    texture.loadFromFile(filename);
    textures[name] = texture;
}

void TextureManager::loadMinesweeperTextures(std::string& imagesFile) {
	const int numTextures = 20;
	std::string textureNames[numTextures] = { "debug", "digits", "face_happy", "face_lose", "face_win", "flag", "mine",
		"number_1", "number_2", "number_3", "number_4", "number_5", "number_6", "number_7", "number_8",
		"test_1", "test_2", "test_3", "tile_hidden", "tile_revealed" };

	for (int i = 0; i < numTextures; i++) {
		sf::Texture tempTexture;
		textures.emplace(textureNames[i], tempTexture);

		std::string textureLocation = imagesFile + "/" + textureNames[i] + ".png";
		if (!textures[textureNames[i]].loadFromFile(textureLocation)) {
			throw std::runtime_error("Tried to load " + textureNames[i] + " texture file unsuccessfully");
		}
	}
}

const sf::Texture& TextureManager::getTexture(const std::string& name)
{
    return textures.at(name);
}

const sf::Texture& TextureManager::getNumTexture(const int& index) {
	std::string textureNames[8] = {"number_1", "number_2", "number_3", "number_4", "number_5", "number_6", "number_7", "number_8"};
	return textures[textureNames[index - 1]];
}

void TextureManager::clear() {
	textures.clear();
}