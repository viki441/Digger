#include "Text.h"
#include "Constants.h"

Text::Text(TextureManager* textures, int x, int y)
	:x(x), y(y)
{
	//get 
	for (int i = 0; i <= 9; i++)
	{
		numbers[i] = textures->get(std::to_string(i));
	}
}

void Text::render(SDL_Renderer* r, int x, int y, const std::string& text)
{
	int offsetX = 0;

	for (char c : text)
	{
		std::string id(1, c);

		SDL_Texture* tex = numbers[c - '0'];

		SDL_Rect dst;
		dst.x = x + offsetX;
		dst.y = y;
		dst.w = Constants::POINTS_TEXT_SIZE;   // character width
		dst.h = Constants::POINTS_TEXT_SIZE;     // character height



		SDL_Rect src = { 0,0, Constants::POINTS_TEXT_SIZE, Constants::POINTS_TEXT_SIZE };

		SDL_RenderCopy(r, numbers[c - '0'], &src, &dst);
		offsetX += Constants::POINTS_TEXT_SIZE;
	}
}

Text::~Text()
{
	for (int i = 0; i <= 9; i++)
	{
		if (numbers[i])
		{
			SDL_DestroyTexture(numbers[i]);
			numbers[i] = nullptr;
		}
	}
}


//std::string Text::renderNumbers(int x, int y, int points)
//{
//
//	std::string txt = "00000";
//
//	int i = 4;
//	while (points > 0 && i >= 0)
//	{
//		txt[i] = '0' + (points % 10);
//		points /= 10;
//		i--;
//	}
//
//	return txt;
//}

//void Text::renderText(int x, int y, const std::string& text)
//{
//	for (char c : text)
//	{
//		std::string id(1, c);
//
//		SDL_Texture* tex = numbers[c - '0'];
//
//		SDL_Rect dst;
//		dst.x = x + Constants::MAP_OFFSET_Y;
//		dst.y = y;
//		dst.w = Constants::POINTS_TEXT_SIZE;   // character width
//		dst.h = Constants::POINTS_TEXT_SIZE;     // character height
//
//
//
//		SDL_Rect src = { 0,0, Constants::TILE_SIZE / 2, Constants::TILE_SIZE / 2 };
//
//		SDL_RenderCopy(numbers[c - '0'], src, dst)
//		offsetX += POINTS;
//	}
//}

