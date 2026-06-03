#pragma once
#include "TextureManager.h"
#include <unordered_map>
#include <string>

class Text
{
public: 
	Text(TextureManager* textures, int x, int y);
	~Text();

	//std::string renderNumbers(int x, int y, int points);
	void render(SDL_Renderer* r, int x, int y, const std::string& text);

private:

	SDL_Texture* numbers[10]{};
	int x;
	int y;

};