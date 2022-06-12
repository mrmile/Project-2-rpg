#ifndef __INTRO_SCREEN_H__
#define __INTRO_SCREEN_H__

#include "Module.h"

struct SDL_Texture;

class ModuleIntro : public Module
{
public:

	ModuleIntro(bool start_enabled = true);

	// Destructor
	virtual ~ModuleIntro();

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
	int backwardsImage = 0;

	SDL_Texture* logoAnimationP1 = nullptr;
};

#endif // __TITLE_SCREEN_H__

