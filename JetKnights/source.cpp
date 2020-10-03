/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "LTexture.h"
#include "Robot.h"
#include "Weapon.h"
#include "Projectile.h"
#include "Hitbox.h"
#include "GameObject.h"
#include "Bullet.h"
#include "Game.h"
#include "NewWeapon.h"
#include "NewRobot.h"


//#include "LTexture.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

const int JOYSTICK_DEAD_ZONE = 8000;



//The application time based timer
class LTimer
{
    public:
		//Initializes variables
		LTimer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

    private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gRobotTexture;
LTexture gWeapon1;
LTexture gBullet;

//Game Controller 1 handler
SDL_GameController* gGameController = NULL;
SDL_Joystick* gJoyStick1 = NULL;
SDL_Joystick* gJoyStick2 = NULL;

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The weapon class is initialized with its texture
			//Projectile bullet(200, 200, 45, gRenderer, &gBullet);

			/*
			The Weapon choice should determine the type of Projectile that will be used. Projectile is dependent on Weapon type.
			-EXAMPLE-
			Player chooses 'Shotgun'. The Weapon class is initialized with the 'Shotgun' texture AND should then load in appropriate projectile type for player.
			-QUESTION-
			How do we set up weapon to load in a specific projectile?F

			*/


			//Initializing with a weapon and takes in Projectile class.
			//Weapon slot1(&bullet, &gWeapon1);


			//The player that will be moving around on the screen
			
			//Robot player(&slot1, &gRobotTexture);

			//Testing hitbox loading
			Hitbox testHitbox(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 50, 50, gRenderer);

			//---Testing GameObject loading---
			//Bullet knight(50, 50, 0.0, 1, gRenderer, &gRobotTexture);
			//.setTexture(&gRobotTexture);
			//knight.setHitbox(45, 78, 5, 15);

			//---Testing use of Bullet object---
			//Bullet myBullet(10, 100, 0, 5, gRenderer, &gBullet);

			//---Testing use of Game object---
			Game game(gRenderer);
			game.genTestWeapon();
			/*
			---Testing NewWeapon Class---
			Initializes with the sarting positon of the GameObject Knight
			*/
			NewRobot myRobot(500, 500, 0, gRenderer, &gRobotTexture);
			NewWeapon myWeapon(myRobot.getPosX(), myRobot.getPosY(), 0, gRenderer, &gWeapon1);





			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the player
					//player.handleEvent( e, JOYSTICK_DEAD_ZONE);
					myWeapon.handleEvent(e);
					myRobot.handleEvent(e);
					game.handlEvent(e);

				}

				//Move the player

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
			

				//Render objects
				////const int particles_max = 100
				//bullet.update();
				//player.update(SCREEN_WIDTH, SCREEN_HEIGHT);
				//player.render(gRenderer);

				//testing hitbox render
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
				SDL_RenderDrawRect(gRenderer, testHitbox.getRect());

				//testing gameobject rendering and update
				/*knight.update();
				knight.render();*/

				//---Testing Bullet class--
				//myBullet.update();
				//myBullet.render();

				//Testing Game object and its rendering

				game.updateObjects();

				//--Testing NewRobot class--
				myRobot.update();
				myRobot.render();

				//---Testing NewWeapon class---
				myWeapon.setPos(myRobot.getPosX(), myRobot.getPosY(), myRobot.getAng());
				myWeapon.update();
				myWeapon.render();


				//std::cout << "X-Axis: "<< SDL_JoystickGetAxis(gGameController, 0) << std::endl;
				//std::cout << "Y-Axis: " << SDL_JoystickGetAxis(gGameController, 1) << std::endl;
				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Check for joysticks
		if (SDL_NumJoysticks() < 1)
		{
			printf("Warning: No joysticks connected!\n");
		}
		else
		{
			//Load joystick
			gGameController = SDL_GameControllerOpen(0);
			gJoyStick1 = SDL_JoystickOpen(0);
			gJoyStick1 = SDL_JoystickOpen(1);

			if (gGameController == NULL)
			{
				printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
			}
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load player texture
	if (!gRobotTexture.loadFromFile("assets/robotrightnew.png", gRenderer))
	{
		printf("Failed to load player texture!\n");
		success = false;
	}

	if (!gWeapon1.loadFromFile("assets/cannonsmall.png", gRenderer))
	{
		printf("Failed to load gun texture!\n");
		success = false;
	}

	if (!gBullet.loadFromFile("assets/bullet.png", gRenderer))
	{
		printf("Failed to load gun texture!\n");
		success = false;
	}

	

	return success;
}

void close()
{
	//Free loaded images
	gRobotTexture.free();
	gWeapon1.free();


	//Close game controller
	SDL_GameControllerClose(gGameController);
	gGameController = NULL;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}