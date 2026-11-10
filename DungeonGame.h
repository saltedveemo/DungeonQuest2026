#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "Player.h"
#include "Enemy.h"
#include "GameCharacter.h"
#include "Tile.h"
#include <list>



const static std::string heroImagePath		= "Sprites/Hero_sword.png";
const static std::string goblinImagePath	= "Sprites/Enemy_orc_red.png";
const static std::string WallImagePath		= "Sprites/Tile_Grey_base.bmp";
const static std::string FloorImagePath		= "Sprites/Tile_carpet_base.bmp";

const static int RoomSize = 10;
const static int DungeonSize = 10;

const static std::list<std::string> RoomPool = { "Data/Rooms/Room01.bmp", "Data/Rooms/Room02.bmp", "Data/Rooms/Room03.bmp", "Data/Rooms/Room04.bmp", "Data/Rooms/Room05.bmp" };




class DungeonGame
{
public:
	DungeonGame();
	~DungeonGame();
	void Awake(SDL_Renderer*);
	void Update(SDL_Renderer*);

	void LoadTextures(SDL_Renderer*);

	void LoadRoom(const char* filename);

	Tile* GetNeighbourTile(int x, int y, Direction _direction);

	void GenerateRoom();

	Tile CurrentRoom[RoomSize][RoomSize];

	std::string CurrentDungeon[DungeonSize][DungeonSize];

	Player* Hero;
	Enemy* Goblin;

	float tileSize = 100;

	SDL_Texture* WallTexture;
	SDL_Texture* FloorTexture;
	

private:

};

