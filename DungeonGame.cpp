#include "DungeonGame.h"

DungeonGame::DungeonGame()
{
}

DungeonGame::~DungeonGame()
{
}

void DungeonGame::Awake(SDL_Renderer* _renderer)
{
	std::cout << "[Dungeon Game] Awake Called";
	this->Hero = new Player;
	this->Hero->Initialize(_renderer, heroImagePath, 2, 2, tileSize);
}

void DungeonGame::Update(SDL_Renderer* _renderer)
{
	SDL_RenderTexture(_renderer, Hero->Texture, NULL, &Hero->Rect);
}

void DungeonGame::LoadTextures(SDL_Renderer* _renderer)
{
	
}
