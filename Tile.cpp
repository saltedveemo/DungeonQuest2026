#include "Tile.h"



void Tile::Configure(SDL_Color& color)
{
	SDL_Color black = { 0, 0, 0, 255 };
	IsWalkable = CompareColor(color, black);
	std::cout << IsWalkable;
}

void Tile::Configure(SDL_Color& color, int x, int y, int size, SDL_Texture* texture)
{
	SDL_Color black = { 0, 0, 0, 255 };
	IsWalkable = CompareColor(color, black);
	std::cout << IsWalkable;

	this->Rect = SDL_Rect{ x, y, size, size };
}

bool Tile::CompareColor(SDL_Color& color1, SDL_Color& color2)
{
	return (color1.r == color2.r) && (color1.g == color2.g) && (color1.b == color2.b);
}
