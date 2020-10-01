#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Hitbox : public SDL_Rect {
public:
	Hitbox();
	Hitbox(int posX, int posY, int width, int height, SDL_Renderer* renderer);

	bool chkCollision(Hitbox b);
	int getWidth();
	int getHeight();
	SDL_Rect* getRect();
	void render();
	void setPos( int PosX, int posY);
	void setParameters(int x, int y, int width, int height, SDL_Renderer* renderer);
private:
	SDL_Renderer* gRenderer;
};