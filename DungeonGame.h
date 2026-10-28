#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "Player.h"
#include "GameCharacter.h"

const static std::string heroImagePath = "Sprites/Hero_sword.png";


class DungeonGame
{
public:
	DungeonGame();
	~DungeonGame();
	void Awake(SDL_Renderer*);
	void Update(SDL_Renderer*);
	void LoadTextures(SDL_Renderer*);

	Player* Hero;

	float tileSize = 100;

private:

};

