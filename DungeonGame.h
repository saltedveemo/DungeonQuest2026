#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "Player.h"
#include "Enemy.h"
#include "GameCharacter.h"
#include "Tile.h"

const static std::string heroImagePath = "Sprites/Hero_sword.png";
const static std::string goblinImagePath = "Sprites/Enemy_orc_red.png";

const static int RoomSize = 10;

class DungeonGame
{
public:
	DungeonGame();
	~DungeonGame();
	void Awake(SDL_Renderer*);
	void Update(SDL_Renderer*);
	void LoadTextures(SDL_Renderer*);

	void LoadRoom(const char* filename);

	Tile Tiles[RoomSize][RoomSize];

	Player* Hero;
	Enemy* Goblin;

	float tileSize = 100;

private:

};

