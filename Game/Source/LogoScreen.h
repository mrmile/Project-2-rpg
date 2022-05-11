#ifndef __LOGO_SCREEN_H__
#define __LOGO_SCREEN_H__

#include "Module.h"

struct SDL_Texture;

class LogoScreen : public Module
{
public:

	LogoScreen(bool start_enabled = true);

	// Destructor
	virtual ~LogoScreen();

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

	// Define multiple Gui Event methods

	//void b2dOnCollision(PhysBody* bodyA, PhysBody* bodyB);
public:

	int delay;
	int animationPositionY;
	int logoPart;

	SDL_Texture* logoAnimationP1 = nullptr;
	SDL_Texture* logoAnimationP2 = nullptr;
	SDL_Texture* logoAnimationP3 = nullptr;
	SDL_Texture* logoAnimationP4 = nullptr;
	SDL_Texture* logoAnimationP5 = nullptr;
	SDL_Texture* logoAnimationP6 = nullptr;
	SDL_Texture* logoAnimationP7 = nullptr;
	SDL_Texture* logoAnimationP8 = nullptr;

};

#endif // __TITLE_SCREEN_H__