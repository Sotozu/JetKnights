#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <SDL_gamecontroller.h>
#include "LTexture.h"
#include "Hitbox.h"

class GameObject {

public:

	//Constructors
	GameObject();
	GameObject(int x, int y, float angle, SDL_Renderer* renderer);
	GameObject(int x, int y, float angle, SDL_Renderer* renderer, LTexture* ltexture);

	//Mutators
	void setHitbox();
	void setHitbox(int h, int w, int offsetX, int offsetY);
	void setTexture(LTexture* tex);
	void setPos(int x, int y, float angle);
	void setTeam(int);

	//Accessors
	int getPosX();
	int getPosY();
	float getAng();

	//Pocesses
	void render();

	template <class T>
	bool chkCollision(T* b) {
		if (hitbox != NULL && b->hitbox != NULL && team != b->team && !isDead && !b->isDead) {
			return hitbox->chkCollision(b->getHitbox());
		}
		return false;
	}
	bool chkBorderCollision(int, int);

	//unknown
	Hitbox* getHitbox();
	bool isDead;
	int team;

protected:
	SDL_Renderer* gRenderer;
	LTexture* texture;
	Hitbox* hitbox;

	float posX;
	float posY;
	float ang;

	int hitboxOffsetX = 0;
	int hitboxOffsetY = 0;
};