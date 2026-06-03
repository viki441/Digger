#include "TileMap.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdexcept>



TileMap::TileMap(int l, TextureManager* textures, int OY)
	:offsetY(OY)
{
	if (l < 1) throw std::invalid_argument("Incorrect level\n");

	//init an empty map
	for (int i = 0; i < Constants::ROWS; i++)
	{
		for (int j = 0; j < Constants::COLS; j++)
		{
			tiles[i][j] = Tile{TileType::Empty, false};
		}
	}
	assignTiles(evaluateLevel(l));
	
	
	background = textures->get("background");
	if (!background) throw std::runtime_error("Missing background texture");

	dugH = textures->get("dugH");
	dugV = textures->get("dugV");
	dugFull = textures->get("dugFull");
	emerald = textures->get("emerald");

}

void TileMap::render(SDL_Renderer* r)
{
	SDL_Rect dest;
	dest.x = 0;
	dest.y = offsetY;

	dest.w = Constants::GAME_WIDTH;
	dest.h = Constants::GAME_HEIGHT;

	SDL_RenderCopy(r, background, nullptr, &dest);

	//render map
	for (int row = 0; row < Constants::ROWS; row++)
		for (int col = 0; col < Constants::COLS; col++)
		{
			{
				SDL_Rect dest =
				{
					col * Constants::TILE_SIZE,
					offsetY + row * Constants::TILE_SIZE,
					Constants::TILE_SIZE,
					Constants::TILE_SIZE
				};
				SDL_Texture* current = findCurrent(row, col);

				if (current) SDL_RenderCopy(r, current, nullptr, &dest);
				
			} 
		}
}

SDL_Texture* TileMap::findCurrent(int row, int col)
{
	switch (tiles[row][col].type)
	{
	case TileType::Empty:
		return nullptr;

	case TileType::DugV:
		return dugV;

	case TileType::DugH:
		return dugH;

	case TileType::DugFull:
		return dugFull;

	case TileType::Emerald:
		return emerald;

	default:
		return nullptr;
	}
}


void TileMap::assignTiles(const std::string& path)
{
	std::ifstream level(path);
	int currEmeralds = 0;
	if (!level) throw std::runtime_error("MAP LOAD TIES SAYS: Problem opening file\n");

	for (int row = 0; row < Constants::ROWS; row++)
		for (int col = 0; col < Constants::COLS; col++)
		{
			int current;
			level >> current;
			bool walkable = (current >= 1 && current <= 3);
			if (current < 0 || current > 4) throw std::invalid_argument("Incorrect data from file.\n");
			
			tiles[row][col] = { TileType(current), walkable};
			if (current == 4) currEmeralds++;
		}
	level.close();
	emeraldsLeft = currEmeralds;
}

const std::string TileMap::evaluateLevel(const int level)
{
	switch (level)
	{
	case 1:
		return "C:/Users/vikik/source/repos/newDigger/assets/levels/level1.txt"; break;
	case 2:
		return "C:/Users/vikik/source/repos/newDigger/assets/levels/level2.txt"; break;
	default:
		return "";
	}
}

bool TileMap::isWalkable(int gridX, int gridY)const
{
	return tiles[gridY][gridX].walkable;
}

void TileMap::setTile(int gridX, int gridY, TileType tile, bool walkable)
{
	tiles[gridY][gridX] = { tile, walkable };
}


int TileMap::dig(int x, int y, Direction direction)
{
	int tilePosX = (x + 32) / Constants::TILE_SIZE;
	int tilePosY = (y - 32) / Constants::TILE_SIZE;

	TileType tile = tiles[tilePosY][tilePosX].type;
	int emerald = 0;
	//if it is fully dug, we have no bussines here
	if (tile != TileType::DugFull)
	{
		//if it is only verticaly dug and direction is HORIZONTAL (r + l)
		if (tile == TileType::DugV && (direction == Direction::LEFT || direction == Direction::RIGHT))
		{
			setTile(tilePosX, tilePosY, TileType::DugFull, true);
			//std::cout << "we move horizontal - left or right" << std::endl;

		}
		//if it is only horizontaly dug and direction is VERTICAL (d + u)
		if (tile == TileType::DugH && (direction == Direction::DOWN || direction == Direction::UP))
		{
			setTile(tilePosX, tilePosY, TileType::DugFull, true);
			//std::cout << "we move vertical - down or up"<< std::endl;

		}

		//if it was turned into full dug
		if (tiles[tilePosY][tilePosX].type == TileType::DugFull) return 0;

		//left is, EMPTY OR EMERALD
		
		//if we are moving vertical
		if (direction == Direction::LEFT || direction == Direction::RIGHT)
		{
			if (tile == TileType::Emerald)
			{
				emerald = 1;
				emeraldsLeft--;
			}
				
			
			//change the tile into a dug version, according to your movement
			setTile(tilePosX, tilePosY, TileType::DugH, true);
		}
		//if we are moving horizontal
		if (direction == Direction::DOWN || direction == Direction::UP)
		{
			if (tile == TileType::Emerald)
			{
				emerald = 1;
				emeraldsLeft--;
			}
			//change the tile into a dug version, according to your movement
			setTile(tilePosX, tilePosY, TileType::DugV, true);
		}
	}	
	return emerald;

}

const int TileMap::getEmeraldsLeft() const
{
	return emeraldsLeft;
}

Direction TileMap::findDirectionBFS(int ex, int ey, int px, int py) const
{
	int dx = px - ex;
	int dy = py - ey;

	// small randomness factor (0 or 1)
	int r = std::rand() % 100;

	bool preferX = std::abs(dx) > std::abs(dy);

	// 20% chance to flip preference
	if (r < 20)
		preferX = !preferX;

	if (preferX)
	{
		if (dx < 0 && isWalkable(ex - 1, ey)) return Direction::LEFT;
		if (dx > 0 && isWalkable(ex + 1, ey)) return Direction::RIGHT;
		if (dy < 0 && isWalkable(ex, ey - 1)) return Direction::UP;
		if (dy > 0 && isWalkable(ex, ey + 1)) return Direction::DOWN;
	}
	else
	{
		if (dy < 0 && isWalkable(ex, ey - 1)) return Direction::UP;
		if (dy > 0 && isWalkable(ex, ey + 1)) return Direction::DOWN;
		if (dx < 0 && isWalkable(ex - 1, ey)) return Direction::LEFT;
		if (dx > 0 && isWalkable(ex + 1, ey)) return Direction::RIGHT;
	}

	return Direction::NONE;
}



TileMap::~TileMap()
{
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(dugFull);
	SDL_DestroyTexture(dugH);
	SDL_DestroyTexture(dugV);
	SDL_DestroyTexture(emerald);
	dugFull = nullptr;
	dugH = nullptr;
	dugV = nullptr;
	emerald = nullptr;
	background = nullptr;
}