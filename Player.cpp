#include "Player.h"
#include "Constants.h"
#include "stdexcept"
#include <iostream>


Player::Player(TextureManager* textures, int x, int y)
{
	this->xpos = x;
	this->ypos = y;

	up = textures->get("playerBulletUp");
	down = textures->get("playerBulletDown");
	left = textures->get("playerBulletLeft");
	right = textures->get("playerBulletRight");

	current = right;

	gridX = xpos / Constants::TILE_SIZE;
	gridY = ypos / Constants::TILE_SIZE;


	//std::cout << "ctor x: " << xpos << "ctor Y: " << ypos << std::endl;
	direction = Direction::NONE;
}

void Player::render(SDL_Renderer* r)
{
	SDL_Rect src = { frame * Constants::TILE_SIZE, 0 , Constants::TILE_SIZE, Constants::TILE_SIZE };
	SDL_Rect dest = { xpos, ypos, Constants::TILE_SIZE, Constants::TILE_SIZE};
	//std::cout << "is rendering\n";

	SDL_RenderCopy(r, current, &src, &dest);

}

void Player::update() 
{
	frame = (SDL_GetTicks() / 120) % framecount;
	int dx = 0;
	int dy = 0;

	
	switch (direction)
	{
	case Direction::UP:    dy = -1; break;
	case Direction::DOWN:  dy = 1; break;
	case Direction::LEFT:  dx = -1; break;
	case Direction::RIGHT: dx = 1; break;
	default: return;
	}

	int nextX = xpos + dx * 4;
	int nextY = ypos + dy * 4;


	int nextGridX = nextX / Constants::TILE_SIZE;
	int nextGridY = nextY / Constants::TILE_SIZE;
	
	if (nextX >= 0 && nextX <= Constants::GAME_WIDTH && nextY >= 0 && nextY <=  Constants::GAME_HEIGHT)
	{
		
		xpos = nextX;
		ypos = nextY;
		gridX = nextGridX;
		gridY = nextGridY;
		changeAnimation(direction);
	}
}


void Player::handleInput(const Uint8* keystate)
{
	if (keystate[SDL_SCANCODE_UP])
		direction = Direction::UP;

	else if (keystate[SDL_SCANCODE_DOWN])
		direction = Direction::DOWN;

	else if (keystate[SDL_SCANCODE_LEFT])
		direction = Direction::LEFT;

	else if (keystate[SDL_SCANCODE_RIGHT])
		direction = Direction::RIGHT;

	else
		direction = Direction::NONE;
}

void Player::changeAnimation(Direction direction)
{
	if (direction == Direction::DOWN)
		current = down;

	else if (direction == Direction::LEFT)
		current = left;

	else if (direction == Direction::UP)
		current = up;

	else if (direction == Direction::RIGHT)
		current = right;
}





const int Player::getGridX() const
{
	return gridX;
}
const int Player::getGridY() const
{
	return gridY;
}
const int Player::getX() const
{
	return xpos;
}
const int Player::getY() const
{
	return ypos;
}

const Direction Player::getDiretion() const
{
	return direction;
}
