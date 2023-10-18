#include "FlagTile.h"

const bool FlagTile::reveal() {
	if (!revealed)
	{
		sprites[0].setTexture(TextureManager::getTexture("flag"));
		revealed = true;
		return true;
	}
	else {
		revealed = false;
		return false;
	}
}