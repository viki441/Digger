#pragma once
#include "Entity.h"
#include "Direction.h"
#include "TextureManager.h"

class TileMap;

enum class Status
{
	HOBBIN = 0,
	NOBBIN
};

class Enemy : public Entity
{
public:
	Enemy(TextureManager* textures);
	~Enemy() override 
	{
		SDL_DestroyTexture(current);
		SDL_DestroyTexture(nobbin);
		SDL_DestroyTexture(hobbinLeft);
		SDL_DestroyTexture(hobbinRight);
		current = nullptr;
		nobbin = nullptr;
		hobbinLeft = nullptr;
		hobbinRight = nullptr;

	
	}
	virtual void update() override;
	void changeAnimation(Direction direction); // for nobbin

	void update(TileMap& map, int playerGridX, int playerGridY);

	virtual void render(SDL_Renderer* r) override;
	void move();

	const int getY() const;
	const int getX() const;
	const int getGridY() const;
	const int getGridX() const;
private:
	SDL_Texture* current;
	
	SDL_Texture* nobbin;
	SDL_Texture* hobbinLeft;
	SDL_Texture* hobbinRight;
	Direction direction = Direction::NONE;

	bool canDig;

	int gridX;
	int gridY;

	int speed;
	int framecount = 3;



};