#ifndef TILESET_H_
#define TILESET_H_

#include "SDLBase.h"
#include <string>
#include <stdlib.h>
#include <vector>
#include "Sprite.h"

class TileSet {
public:
	virtual ~TileSet();
	TileSet(std::string filePath, int lines, int columns);
	TileSet(int tileWidth, int tileHeight, std::string filePath);
	TileSet(int tileWidth, int tileHeight);
	void addTile(std::string filePath);
	void render(int index, float pos_x, float pos_y);
	bool usingSingleFile();
	int getTileWidth();
	int getTileHeight();

private:
	int tileWidth, tileHeight;
	int lines, columns;
	Sprite * tileSet;
	std::vector<Sprite *>* vTiles;
	SDL_Rect * destRect;
	bool useSingleFile;
};

#endif /* TILESET_H_ */
