#ifndef __SCREEN_SCREEN_H__
#define __SCREEN_SCREEN_H__

#include "Module.h"
#include "GuiButton.h"

struct SDL_Texture;

class CreditsScreen : public Module
{
public:

	CreditsScreen(bool start_enabled = false);

	// Destructor
	virtual ~CreditsScreen();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control);

	// Define multiple Gui Event methods

	//void b2dOnCollision(PhysBody* bodyA, PhysBody* bodyB);
public:

	/*int delay;
	int animationPositionY;
	int logoPart;*/

	int buttonClickedFx = 0;
	bool creditsScene = false;

	// Position of the player and zombies
	iPoint position;
	fPoint fPosition;
	fPoint fPosition1;
	fPoint fPosition2;
	fPoint fPosition3;
	fPoint fPosition4;
	fPoint fPosition5;
	fPoint fPosition6;
	fPoint fPosition7;
	fPoint fPosition8;
	fPoint fPosition9;

	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Texture* texture1 = nullptr;
	SDL_Texture* texture2 = nullptr;
	SDL_Texture* texture3 = nullptr;
	SDL_Texture* texture4 = nullptr;

	SDL_Texture* returnButton1;
	SDL_Texture* returnButtonOnIdle1;
	SDL_Texture* returnButtonPressed1;

	GuiButton* returnButton_1;

	//Animations for the zombies and player
	Animation idleAnimPlayer;
	Animation idleAnim;
	Animation idleAnim1;
	Animation idleAnim2;
	Animation idleAnim3;

	Animation* playerAnimation = nullptr;
	Animation* currentAnimation = nullptr;
	Animation* currentAnimation1 = nullptr;
	Animation* currentAnimation2 = nullptr;
	Animation* currentAnimation3 = nullptr;
	Animation* currentAnimation4 = nullptr;


};

#endif // __CREDITS_SCREEN_H__