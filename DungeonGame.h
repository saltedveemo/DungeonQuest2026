#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "Player.h"
#include "Enemy.h"
#include "GameCharacter.h"
#include "Tile.h"
#include <list>
#include <iterator>



const static std::string heroImagePath		= "Sprites/Hero_sword.png";
const static std::string goblinImagePath	= "Sprites/Enemy_orc_red.png";
const static std::string WallImagePath		= "Sprites/Tile_Grey_base.bmp";
const static std::string FloorImagePath		= "Sprites/Tile_carpet_base.bmp";

const static int RoomSize = 10;
const static int DungeonSize = 10;

const static std::string RoomPathPool[] {"Data/Rooms/Room01.bmp", "Data/Rooms/Room02.bmp", "Data/Rooms/Room03.bmp", "Data/Rooms/Room04.bmp", "Data/Rooms/Room05.bmp"};

struct TargetTileContext {
	bool IsWalkable;
	bool IsOutOfBounds;
	Direction TargetDirection;
	GameCharacter* Occupant = nullptr;

	TargetTileContext() {};
	TargetTileContext(bool _isWalkable, bool _isOutOfBounds, Direction _direction, GameCharacter* _occupant) : IsWalkable(_isWalkable), IsOutOfBounds(_isOutOfBounds), TargetDirection(_direction), Occupant(_occupant) {}
};

struct Position {
	int x;
	int y;
	Position() : x(0), y(0) {}
	Position(int _x, int _y) : x(_x), y(_y) {}
};


class DungeonGame
{
public:
	DungeonGame();
	~DungeonGame();
	void Awake(SDL_Renderer*);
	void Update(SDL_Renderer*, double);
	void Draw(SDL_Renderer*);

	void LoadEnvironmentTextures(SDL_Renderer*);
	void LoadRoom(int _x, int _y);
	bool TryLoadNeighbourRoom(Direction _direction);
//	void LoadRoom(const char* filename);
	void GenerateDungeon();

	Tile* GetNeighbourTile(int x, int y, Direction _direction);
	int GetNeighbourRoom(int _x, int _y, Direction _direction);
	GameCharacter* TryGetCharacterAtCoord(int _x, int _y);
	const static std::string* GetRandomRoomPath();

	TargetTileContext TryGetNeighbourTile(int _x, int _y, Direction _direction);

	void MoveCharacter(GameCharacter* _character, Direction _direction);
	void MoveHero(Direction _direction);

	

	//Utility
	bool IsInRange(float _val, float _lowerBound, float _upperBound);

	void MoveEnemies(double _deltaTime);
	void SpawnEnemies();
	void DestroyAllEnemies();

	SDL_Renderer* Renderer;

	Tile CurrentRoom[RoomSize][RoomSize];
	int CurrentDungeon[DungeonSize][DungeonSize];

	int CurrentRoomX;
	int CurrentRoomY;

	Player* Hero;
	Enemy* Goblin;

	float tileSize = 100;

	SDL_Texture* WallTexture;
	SDL_Texture* FloorTexture;

	std::list<GameCharacter*> Characters;
	std::list<Enemy*> Enemies;


	float CurrentEnemyMoveCooldwn = 0;
	float EnemyMoveInterval = 1.2;
	int MinEnemyCount = 0;
	int MaxEnemyCount = 3;

	int SpawnBoundMin = 1;
	int SpawnBoundMax = 8;

	//actions
	void MoveHero(int _x, int _y);
	
private:

};

