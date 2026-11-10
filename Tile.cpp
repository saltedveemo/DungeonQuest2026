#include "Tile.h"





void Tile::Configure(SDL_Color& color)
{
	SDL_Color black = { 0, 0, 0, 255 };
	IsWalkable = !CompareColor(color, black);
}

void Tile::Configure(SDL_Color& color, float x, float y, float size, SDL_Texture* texture)
{
	SDL_Color black = { 0, 0, 0, 255 };
	IsWalkable = !CompareColor(color, black);

	this->Rect = SDL_FRect{ x*size, y*size, size, size };
	if (IsWalkable) this->Texture = texture;
}

bool Tile::CompareColor(SDL_Color& color1, SDL_Color& color2)
{
	return (color1.r == color2.r) && (color1.g == color2.g) && (color1.b == color2.b);
}

void Tile::DefineNeighbours(Tile* upTile, Tile* downTile, Tile* leftTile, Tile* rightTile)
{
	this->Neighbour[Up]		= upTile;
	this->Neighbour[Down]	= downTile;
	this->Neighbour[Left]	= leftTile;
	this->Neighbour[Right]	= rightTile;
}


