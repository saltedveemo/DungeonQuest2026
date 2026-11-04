#pragma once
#include <SDL3_image/SDL_image.h>
#include <iostream>

class Tile
{

public:
	bool IsWalkable;
	SDL_Texture* Texture;
	SDL_Rect Rect;
	void Configure(SDL_Color& color);
	void Configure(SDL_Color& color, int x, int y, int size, SDL_Texture* texture);
	bool CompareColor(SDL_Color& color1, SDL_Color& color2);
};

