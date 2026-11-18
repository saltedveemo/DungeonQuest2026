#include "GameCharacter.h"
#include <iostream>


GameCharacter::GameCharacter()
{
	
}

GameCharacter::~GameCharacter()
{
}

GameCharacter::GameCharacter(SDL_Renderer* _renderer, std::string _imagePath, float _x, float _y, float size)
{
	SetSize(size, size);
	SetCoordinate(_x, _y);
	ImagePath = _imagePath;
	Texture = IMG_LoadTexture(_renderer, ImagePath.c_str());
	SDL_SetTextureScaleMode(Texture, SDL_SCALEMODE_NEAREST);
}

void GameCharacter::Move(float _x, float _y)
{
	SetPosition((_x * this->Rect.w) + this->PosX, (_y * this->Rect.h) + this->PosY);
}

void GameCharacter::SetPosition(float _x, float _y)
{
	this->PosX = this->Rect.x = _x;
	this->PosY = this->Rect.y = _y;
	this->CoordX = this->PosX / this->Rect.w;
	this->CoordY = this->PosY / this->Rect.h;
}

void GameCharacter::SetCoordinate(int _x, int _y)
{
	this->PosX = this->Rect.x = float(_x) * this->Rect.w;
	this->PosY = this->Rect.y = float(_y) * this->Rect.h;

	this->CoordX = this->PosX / this->Rect.w;
	this->CoordY = this->PosY / this->Rect.h;
}

void GameCharacter::SetSize(float _w, float _h)
{
	this->Rect.w = _w;
	this->Rect.h = _h;
}

void GameCharacter::Initialize(SDL_Renderer* _renderer, std::string _imagePath, float _x, float _y, float size)
{
	SetSize(size, size);
	SetCoordinate(_x, _y);
	ImagePath = _imagePath;
	Texture = IMG_LoadTexture(_renderer, ImagePath.c_str());
	SDL_SetTextureScaleMode(Texture, SDL_SCALEMODE_NEAREST);
}
