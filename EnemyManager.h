#pragma once
#include "Enemy.h"
#include <vector>
#include "Constants.h"
class EnemyManager
{
public:
	EnemyManager(TextureManager* textures);
	~EnemyManager();

	void addEnemy();
	void update();
	void render(SDL_Renderer* r);

	void changeIdentity();
	void updateTime();
	bool checkInnerCollision(); // this is how nobbin turns into hobbin
	//when 2 enemies "collide" or just overlap, there is a chance one or both might turn into hobbin
	const int getCurrentCount() const;
	Enemy* getCurrentEnemy(int i);

private:
	Enemy* enemies[Constants::ENEMY_LIMIT-1]; // limit per screen
	int time = 5;
	int enemyCount = 0;
	int maxCount = 9; // after destroying them all, you progress to the next level
	TextureManager* textures;


};