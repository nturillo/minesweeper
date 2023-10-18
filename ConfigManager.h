#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <unordered_map>


class ConfigManager
{
public:
	static const sf::Vector2<int>& getBoardSize();
	static const int& getDefaultNumMines();
	static const std::string& getSetup(const std::string& name);
	static void load(std::string& fileLocation);
	static void clear();
private:
	static sf::Vector2<int> boardSize;
	static int numMines;
	static std::unordered_map<std::string, std::string> setups;
};

