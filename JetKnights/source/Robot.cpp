#pragma once
#include "Robot.h"
#include "Weapon.h"


Robot::Robot(Weapon* slot1)
{
	s1 = slot1;

	//Initialize the offsets
	mPlayerPosX = 100;
	mPlayerPosY = 100;

	//Initialize the velocity
	mPlayerVelX = 0;
	mPlayerVelY = 0;

	//Normalized direction
	xPlayerDir = 0;
	yPlayerDir = 0;
}

void Robot::handleEvent(SDL_Event& e, int JOYSTICK_DEAD_ZONE)
{
	//If a key was pressed
	if (e.type == SDL_JOYAXISMOTION)
	{


		if (e.jaxis.which == 0)
		{

			//X axis motion
			if (e.jaxis.axis == 0)
			{

				//Left of dead zone
				if (e.jaxis.value < -JOYSTICK_DEAD_ZONE)
				{


					//player update
					mPlayerVelX -= DOT_VEL;
					xPlayerDir = -1;

					//Weapon update
					s1->setVelX(mPlayerVelX);
					s1->setDirX(xPlayerDir);
					
				}
				//Right of dead zone
				else if (e.jaxis.value > JOYSTICK_DEAD_ZONE)
				{
					mPlayerVelX += DOT_VEL;
					xPlayerDir = 1;

					//Weapon update
					s1->setVelX(mPlayerVelX);
					s1->setDirX(xPlayerDir);
				}
				else
				{
					xPlayerDir = 0;
					mPlayerVelX = 0;

					//Weapon update
					s1->setVelX(mPlayerVelX);
					s1->setDirX(xPlayerDir);

				}
			}
			//Y axis motion
			else if (e.jaxis.axis == 1)
			{

				//Below of dead zone
				if (e.jaxis.value < -JOYSTICK_DEAD_ZONE)
				{
					mPlayerVelY -= DOT_VEL;

					yPlayerDir = -1;

					//Weapon update
					s1->setVelY(mPlayerVelY);
					s1->setDirY(yPlayerDir);
				}
				//Above of dead zone
				else if (e.jaxis.value > JOYSTICK_DEAD_ZONE)
				{
					mPlayerVelY += DOT_VEL;
					yPlayerDir = 1;

					//Weapon update
					s1->setVelY(mPlayerVelY);
					s1->setDirY(yPlayerDir);
				}
				else //dead zone
				{
					yPlayerDir = 0;
					mPlayerVelY = 0;

					//Weapon update
					s1->setVelY(mPlayerVelY);
					s1->setDirY(yPlayerDir);

				}
			}
		}

	}





}

void Robot::move(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{

	//Move the player left or right
	mPlayerPosX += mPlayerVelX;

	//Move the weapon left or right
	s1->setPosX(mPlayerPosX);

	//If the player went too far to the left or right
	if ((mPlayerPosX < 0) || (mPlayerPosX > SCREEN_WIDTH))
	{
		//Move player back
		mPlayerPosX -= mPlayerVelX;

		//Move Weapon back
		s1->setPosX(mPlayerPosX);

	}

	//Move the player up or down
	mPlayerPosY += mPlayerVelY;


	//Move the weapon up or down
	s1->setPosY(mPlayerPosY);

	//If the player went too far up or down
	if ((mPlayerPosY < 0) || (mPlayerPosY > SCREEN_HEIGHT))
	{
		//Move player back
		mPlayerPosY -= mPlayerVelY;

		//Move Weapon back
		s1->setPosY(mPlayerPosY); 
	}
}

void Robot::render(SDL_Renderer* gRenderer, LTexture gRobotTexture, LTexture gWeapon1)
{
	//Show the player
	gRobotTexture.render(mPlayerPosX, mPlayerPosY, NULL, gRenderer);

	//Show the weapon
    //Weapon1.render


}

int Robot::getxDir()
{
	return xPlayerDir;
}

int Robot::getyDir()
{
	return yPlayerDir;
}

int Robot::getPosX()
{
	return mPlayerPosX;
}

int Robot::getPosY()
{
	return mPlayerPosY;
}

int Robot::getWeaponPosX() {
	return s1->getPosX();
}
int Robot::getWeaponPosY() {
	return s1->getPosY();

}
