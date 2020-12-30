#include "Pause_Menu.h"


//Constructor
Pause_Menu::Pause_Menu(SDL_Renderer* renderer, int screenW, int screenH) {

	SCREEN_HEIGHT = screenH;
	SCREEN_WIDTH = screenW;
	gRenderer = renderer;

	//List of assets that we will be using in the game
	menuBackgroundImagesDir = { "assets/images/Pause_Menu.jpg" };


	//List of sounds that we will be using in the game


	loadMedia();

	genTestPanel();
}

//Loads all the textures for the game
void Pause_Menu::loadMedia() {
	for (int i = 0; i < TOTAL_IMAGES; ++i) {
		menuBackgroundImages[i].loadFromFile(menuBackgroundImagesDir[i], gRenderer);
		//soundEffects[i].loadSound(sounds[i]);
	}
}



// Passes SDL events to classes that use them
void Pause_Menu::handleEvent(SDL_Event e) {

	/*for (auto robot : robots) {
		robot->handleEvent(e);
		robot->passOnEvent(e);
	}
	for (auto weapon : weapons) {
		if (weapon != NULL) {
			weapon->handleEvent(e);
		}
	}*/

}

// Update order of the game


void Pause_Menu::updateObjects(float timeStep) {
	updateRenders(panel);
}

/*SHOULD GENERATE MENU TEMPLATE AND FILL WITH BUTTONS*/


void  Pause_Menu::genTestPanel() {

	RelTexture* panelTex = new RelTexture(0, 0, 0, &menuBackgroundImages[0], gRenderer);

	GameObject* panel0 = new GameObject(0, 0, 0, gRenderer, &*panelTex);
	panel0->addHitbox();
	panel.push_back(panel0);

}

void Pause_Menu::renderTransparentRect() {
	SDL_Rect fillRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(gRenderer, 64, 64, 64, 1);
	SDL_RenderFillRect(gRenderer, &fillRect);
	SDL_RenderPresent(gRenderer);
}

