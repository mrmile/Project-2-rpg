#ifndef __LOGO_SCREEN_H__
#define __LOGO_SCREEN_H__

#include "Module.h"

struct SDL_Texture;

class LogoScreen : public Module
{
public:

	LogoScreen(bool start_enabled = false);

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

	SDL_Texture* logoScreen1;
	SDL_Texture* logoScreen10;
	SDL_Texture* logoScreen11;
	SDL_Texture* logoScreen12;
	SDL_Texture* logoScreen2;
	SDL_Texture* logoScreen3;
};

#endif // __TITLE_SCREEN_H__