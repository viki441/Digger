#include "Enemy.h"
#include "Constants.h"
#include "TileMap.h"
#include <iostream>

Enemy::Enemy(TextureManager* textures)
	:speed(3), gridX(13), gridY(0), canDig(false)
{
	xpos = gridX * Constants::TILE_SIZE;
	ypos = gridY * Constants::TILE_SIZE + Constants::MAP_OFFSET_Y;

	nobbin = textures->get("nobbin");
	//fFIX LATER
	hobbinLeft = nullptr;
	hobbinRight = nullptr;

	current = nobbin;
}


void Enemy::render(SDL_Renderer* r)
{
	SDL_Rect src = { frame * Constants::TILE_SIZE, 0 , Constants::TILE_SIZE, Constants::TILE_SIZE };
	SDL_Rect dest = { xpos, ypos, Constants::TILE_SIZE, Constants::TILE_SIZE };
	//std::cout << "is rendering\n";

	SDL_RenderCopy(r, current, &src, &dest);

}


void Enemy::update()
{
	frame = (SDL_GetTicks() / 120) % framecount;

	if (canDig)
	{
		changeAnimation(direction);
	}
}

void Enemy::changeAnimation(Direction direction)
{
	if (direction == Direction::LEFT)
		current = hobbinLeft;

	else if (direction == Direction::RIGHT)
		current = hobbinRight;

	else current = current;
}


void Enemy::update(TileMap& map,int playerGridX,int playerGridY)
{
	direction = map.findDirectionBFS(
		gridX,
		gridY,
		playerGridX,
		playerGridY);

	move();
	std::cout << "is walkable current" << map.isWalkable(gridX, gridY) << std::endl;
	std::cout <<"GRID: "<< gridX << " " << gridY << std::endl;


}
void Enemy::move()
{
	int dx = 0;
	int dy = 0;

	switch (direction)
	{
	case Direction::LEFT:
		dx = -speed;
		break;

	case Direction::RIGHT:
		dx = speed;
		break;

	case Direction::UP:
		dy = -speed;
		break;

	case Direction::DOWN:
		dy = speed;
		break;

	default:
		return;
	}

	xpos += dx;
	ypos += dy; // +Constants::MAP_OFFSET_Y;

	gridX = (xpos + 32 ) / Constants::TILE_SIZE;
	gridY = (ypos - 32 ) / Constants::TILE_SIZE;


	//std::cout << "REG: " << xpos << " " << ypos << std::endl;
	//std::cout <<"GRID: "<< gridX << " " << gridY << std::endl;
	

}











const int Enemy::getGridX() const
{
	return gridX;
}
const int Enemy::getGridY() const
{
	return gridY;
}
const int Enemy::getX() const
{
	return xpos;
}
const int Enemy::getY() const
{
	return ypos;
}