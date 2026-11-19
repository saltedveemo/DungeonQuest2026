#include "DungeonGame.h"

DungeonGame::DungeonGame()
{
}

DungeonGame::~DungeonGame()
{
}



#pragma region //_________Cycle_________

void DungeonGame::Awake(SDL_Renderer* _renderer)
{
	Renderer = _renderer;

	GenerateDungeon();

	//
	LoadEnvironmentTextures(_renderer);
	int _rx = SDL_rand(RoomSize-1);
	int _ry = SDL_rand(RoomSize-1);
	LoadRoom(_rx, _ry);


	//Defining characters
	this->Hero = new Player;
	this->Hero->Initialize(_renderer, heroImagePath, 2, 2, tileSize);
	Characters.push_back(this->Hero);

//	SpawnEnemies();
}

void DungeonGame::Update(SDL_Renderer* _renderer, double _deltaTime)
{
	MoveEnemies(_deltaTime);
}

void DungeonGame::Draw(SDL_Renderer* _renderer)
{
	//Tiles
	for (int y = 0; y < std::size(CurrentRoom); y++) {
		for (int x = 0; x < std::size(CurrentRoom[y]); x++) {
			SDL_RenderTexture(_renderer, CurrentRoom[x][y].Texture, NULL, &CurrentRoom[x][y].Rect);
		}
	}

	//Game Characters
	for (GameCharacter* c : Characters) {
		SDL_RenderTexture(_renderer, c->Texture, NULL, &c->Rect);
	}
	
	for (Enemy* e : Enemies) {
		SDL_RenderTexture(_renderer, e->Texture, NULL, &e->Rect);
	}
}

#pragma endregion




#pragma region //_________Loading Functions_________

void DungeonGame::LoadEnvironmentTextures(SDL_Renderer* _renderer)
{
	WallTexture = IMG_LoadTexture(_renderer, WallImagePath.c_str());
	SDL_SetTextureScaleMode(WallTexture, SDL_SCALEMODE_NEAREST);

	FloorTexture = IMG_LoadTexture(_renderer, FloorImagePath.c_str());
	SDL_SetTextureScaleMode(FloorTexture, SDL_SCALEMODE_NEAREST);
}

void DungeonGame::LoadRoom(int _x, int _y)
{
	int _roomID = CurrentDungeon[_x][_y];
	const char* filename = RoomPathPool[_roomID].c_str();
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

	CurrentRoomX = _x;
	CurrentRoomY = _y;
	std::cout << "Room '" << filename << "' has been loaded at (" << CurrentRoomX << ", " << CurrentRoomY << ")\n\n";
}

bool DungeonGame::TryLoadNeighbourRoom(Direction _direction)
{
	int _x = CurrentRoomX;
	int _y = CurrentRoomY;

	switch (_direction)
	{
		case Up:	_y--; break;
		case Down:	_y++; break;
		case Left:	_x--; break;
		case Right:	_x++; break;
	}

	if (!IsInRange(_x, 0, DungeonSize - 1) || !IsInRange(_y, 0, DungeonSize - 1)) {
		std::cout << "Room at (" << _x << ", " << _y << ") is out of bounds\n\n";
		return false;
	}
	LoadRoom(_x, _y);

	return true;
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

#pragma endregion




//____________________Getters_________________

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

GameCharacter* DungeonGame::TryGetCharacterAtCoord(int _x, int _y)
{
	GameCharacter* _occupant = nullptr;
	for (GameCharacter* c : Characters) {
		if ((c->CoordX == _x) && (c->CoordY == _y)) return c;
	}
	
	for (Enemy* e : Enemies) {
		if ((e->CoordX == _x) && (e->CoordY == _y)) return e;
	}
	return nullptr;
}

const std::string* DungeonGame::GetRandomRoomPath()
{
	int i = rand() % RoomPathPool->length();
	return &RoomPathPool[i];
}

TargetTileContext DungeonGame::TryGetNeighbourTile(int _x, int _y, Direction _direction)
{
	int _xx = _x;
	int _yy = _y;

	switch (_direction)
	{
	case Up:	_yy = _yy - 1;
		break;
	case Down:	_yy = _yy + 1;
		break;
	case Left:	_xx = _xx - 1;
		break;
	case Right:	_xx = _xx + 1;
		break;
	}
	Tile* _targetTile = &CurrentRoom[_xx][_yy];
	
	bool _outOfBounds = (!IsInRange(_xx, 0, RoomSize - 1) || !IsInRange(_yy, 0, RoomSize - 1));

	GameCharacter* _occupant = TryGetCharacterAtCoord(_xx, _yy);

	TargetTileContext result = TargetTileContext(_targetTile->IsWalkable, _outOfBounds, _direction, _occupant);
	

	std::cout << "Target Tile Context Created for target X:" << _xx << " Y:" << _yy << std::endl;
	std::cout << "	IsWalkable: " << result.IsWalkable << std::endl;
	std::cout << "	IsOutOfBounds: " << result.IsOutOfBounds << std::endl;
	std::cout << "	Direction: " << result.TargetDirection << std::endl << std::endl;
	std::cout << "	Occupant: " << (result.Occupant != nullptr) << std::endl << std::endl;

	return result;
}

//___________________________________________



//Moves a given character :D
void DungeonGame::MoveCharacter(GameCharacter* _character, Direction _direction)
{
	int _x = _character->CoordX;
	int _y = _character->CoordY;
	TargetTileContext context = TryGetNeighbourTile(_x, _y, _direction);

	if ((context.IsWalkable) && (context.Occupant == nullptr) && (!context.IsOutOfBounds)){
		switch (_direction) {
			case Up:	_character->Move(0, -1); break;
			case Down:	_character->Move(0, 1); break;
			case Left:	_character->Move(-1, 0); break;
			case Right: _character->Move(1, 0); break;
		}
	}
}

//Variation of MoveCharacter but specifically for player
void DungeonGame::MoveHero(Direction _direction)
{
	int _x = Hero->CoordX;
	int _y = Hero->CoordY;
	TargetTileContext context = TryGetNeighbourTile(_x, _y, _direction);

	if ((context.IsWalkable) && (context.Occupant == nullptr) && (!context.IsOutOfBounds)) {
		switch (_direction) {
			case Up:	Hero->Move(0, -1); break;
			case Down:	Hero->Move(0, 1); break;
			case Left:	Hero->Move(-1, 0); break;
			case Right: Hero->Move(1, 0); break;
		}
	}

	
	if (context.IsOutOfBounds) { //Room Transfer
		bool _loaded = TryLoadNeighbourRoom(_direction);

		int xx = Hero->CoordX;
		int yy = Hero->CoordY;
		switch (_direction) {
			case Up:	yy = 9; break;
			case Down:	yy = 0; break;
			case Left:	xx = 9; break;
			case Right: xx = 0; break;
		}

		Hero->SetCoordinate(xx, yy);

		DestroyAllEnemies();
		SpawnEnemies();
	}
}



//___________Enemy Management_________
void DungeonGame::MoveEnemies(double _deltaTime)
{
	CurrentEnemyMoveCooldwn -= _deltaTime * EnemyMoveInterval;

	if (CurrentEnemyMoveCooldwn <= 0) { //move trigger
		CurrentEnemyMoveCooldwn = EnemyMoveInterval;

		for (Enemy* e : Enemies) {
			Direction _directionPool[] = { Up, Down, Left, Right };
			int i = SDL_rand(10) % 4;
			MoveCharacter(e, _directionPool[i]);
		}
	}
}

void DungeonGame::SpawnEnemies()
{
	for (int i = 0; i < MaxEnemyCount; i++) {
		int _sx = SDL_rand((SpawnBoundMax + 1 - SpawnBoundMin) + SpawnBoundMin);
		int _sy = SDL_rand((SpawnBoundMax + 1 - SpawnBoundMin) + SpawnBoundMin);

		while (!CurrentRoom[_sx][_sy].IsWalkable)
		{
			_sx = SDL_rand((SpawnBoundMax + 1 - SpawnBoundMin) + SpawnBoundMin);
			_sy = SDL_rand((SpawnBoundMax + 1 - SpawnBoundMin) + SpawnBoundMin);
		}

		Enemy* _newE = new Enemy;
		_newE->Initialize(Renderer, goblinImagePath, _sx, _sy, tileSize);
		Enemies.push_back(_newE);
	}
}

void DungeonGame::DestroyAllEnemies()
{
	for (Enemy* e : Enemies) {
		delete e;
	}
	Enemies.clear();
}




//_________Utility__________
bool DungeonGame::IsInRange(float _val, float _lowerBound, float _upperBound) {
	return (_val >= _lowerBound && _val <= _upperBound);
}