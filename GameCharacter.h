#pragma once
#include <SDL3_image/SDL_image.h>
#include <string>

class GameCharacter
{
public:
	GameCharacter();
	~GameCharacter();

	void Move(float x, float y);
	void SetPosition(float, float);
	void SetSize(float, float);
	void Initialize(SDL_Renderer* _renderer, std::string _imagePath, float _x, float _y, float size);

	//Variables
	SDL_FRect Rect;
	SDL_Texture* Texture;
	std::string ImagePath;

	int PosX;
	int PosY;
};

