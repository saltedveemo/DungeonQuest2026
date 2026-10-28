#include "GameCharacter.h"


GameCharacter::GameCharacter()
{

}

GameCharacter::~GameCharacter()
{
}

void GameCharacter::Move(float _x, float _y)
{
	SetPosition((_x * this->Rect.w) + this->PosX, (_y * this->Rect.h) + this->PosY);
}

void GameCharacter::SetPosition(float _x, float _y)
{
	this->PosX = this->Rect.x = _x;
	this->PosY = this->Rect.y = _y;
}

void GameCharacter::SetSize(float _w, float _h)
{
	this->Rect.w = _w;
	this->Rect.h = _h;
}

void GameCharacter::Initialize(SDL_Renderer* _renderer, std::string _imagePath, float _x, float _y, float size)
{
	SetPosition(_x, _y);
	SetSize(size, size);
	ImagePath = _imagePath;
	Texture = IMG_LoadTexture(_renderer, ImagePath.c_str());
}
