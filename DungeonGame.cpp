#include "DungeonGame.h"

DungeonGame::DungeonGame()
{
}

DungeonGame::~DungeonGame()
{
}

//---Cycle----
void DungeonGame::Awake(SDL_Renderer* _renderer)
{
	this->Hero = new Player;
	this->Hero->Initialize(_renderer, heroImagePath, 2, 2, tileSize);	
	
	this->Goblin = new Enemy;
	this->Goblin->Initialize(_renderer, goblinImagePath, 1, 1, tileSize);

	GenerateDungeon();

	LoadTextures(_renderer);
	int i = rand() % (std::size(RoomPathPool) - 1);
	LoadRoom(RoomPathPool[i].c_str());
}

void DungeonGame::Update(SDL_Renderer* _renderer)
{

	//Drawing

	//terrain
	for (int y = 0; y < std::size(CurrentRoom); y++) {
		for (int x = 0; x < std::size(CurrentRoom[y]); x++) {
			SDL_RenderTexture(_renderer, CurrentRoom[x][y].Texture, NULL, &CurrentRoom[x][y].Rect);
		}
	}

	//game character
	SDL_RenderTexture(_renderer, Hero->Texture, NULL, &Hero->Rect);
	SDL_RenderTexture(_renderer, Goblin->Texture, NULL, &Goblin->Rect);
}


//---Loading---
void DungeonGame::LoadTextures(SDL_Renderer* _renderer)
{
	WallTexture = IMG_LoadTexture(_renderer, WallImagePath.c_str());
	SDL_SetTextureScaleMode(WallTexture, SDL_SCALEMODE_NEAREST);

	FloorTexture = IMG_LoadTexture(_renderer, FloorImagePath.c_str());
	SDL_SetTextureScaleMode(FloorTexture, SDL_SCALEMODE_NEAREST);
}

void DungeonGame::LoadRoom(const char* filename)
{
	SDL_Surface* surf = SDL_LoadBMP(filename);

	const SDL_PixelFormatDetails* pixelDetails = SDL_GetPixelFormatDetails(surf->format);
	const Uint8 bpp = SDL_BYTESPERPIXEL(surf->format);
	SDL_Color col;

	//configuring
	for (int y = 0; y < surf->h; y++) {
		for (int x = 0; x < surf->w; x++) {
			Uint8* pixel = static_cast<Uint8*>(surf->pixels) + y * surf->pitch + x * bpp;
			SDL_GetRGB(*reinterpret_cast<Uint32*>(pixel), pixelDetails, NULL, &col.r, &col.g,
				&col.b);
			// col now contains pixel colour at position x,y!
			// TODO, configure the tile at x/y with this colour.

			CurrentRoom[x][y].Configure(col, x, y, tileSize, FloorTexture);
		}
	}
	std::cout << "Room '" << filename << "' has been loaded\n\n";
}

void DungeonGame::GenerateDungeon()
{
	std::cout << "Generate Dungeon Result:\n\n";

	for (int y = 0; y < DungeonSize; y++) {
		for (int x = 0; x < DungeonSize; x++) {
			CurrentDungeon[x][y] = rand() % (std::size(RoomPathPool));
			std::cout << CurrentDungeon[x][y];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}



//---Functions---

Tile* DungeonGame::GetNeighbourTile(int x, int y, Direction _direction)
{
	switch (_direction)
	{
	case Up:	return &CurrentRoom[x][y - 1];
		break;
	case Down:	return &CurrentRoom[x][y + 1];
		break;
	case Left:	return &CurrentRoom[x - 1][y];
		break;
	case Right:	return &CurrentRoom[x + 1][y];
		break;
	}
	return nullptr;
}


const std::string* DungeonGame::GetRandomRoomPath()
{
	int i = rand() % RoomPathPool->length();
	return &RoomPathPool[i];
}

TargetTileContext DungeonGame::TryMoveTile(int x, int y, Direction _direction)
{
	Tile* _targetTile = GetNeighbourTile(x, y, _direction);
	bool _outOfBounds = !((x >= 0 && x < RoomSize) && (x >= 0 && x < RoomSize));
	TargetTileContext result = TargetTileContext(_targetTile->IsWalkable, _outOfBounds, _direction);

	std::cout << "Target Tile Context Created for target X:" << x << " Y:" << y << std::endl;
	std::cout << "	IsWalkable: " << result.IsWalkable << std::endl;
	std::cout << "	IsOutOfBounds: " << result.IsOutOfBounds << std::endl;
	std::cout << "	Direction: " << result.TargetDirection << std::endl  << std::endl ;

	return result;
}
