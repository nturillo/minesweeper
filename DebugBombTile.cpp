#include "DebugBombTile.h"

const bool DebugBombTile::reveal() {
	if (!revealed)
	{
		sprites[0].setTexture(TextureManager::getTexture("mine"));
		revealed = true;
	}
	else {
		revealed = false;
	}
	return false;
}