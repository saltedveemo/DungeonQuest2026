#pragma once
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include <map>

const static enum Direction {
	Up,
	Down,
	Left,
	Right
};


class Tile
{

public:
	bool IsWalkable;
	SDL_Texture* Texture;
	SDL_FRect Rect;
	std::map<Direction, Tile*> Neighbour;

	void Configure(SDL_Color& color);
	void Configure(SDL_Color& color, float x, float y, float size, SDL_Texture* texture);
	bool CompareColor(SDL_Color& color1, SDL_Color& color2);
	void DefineNeighbours(Tile* upTile, Tile* downTile, Tile* leftTile, Tile* rightTile);
};

