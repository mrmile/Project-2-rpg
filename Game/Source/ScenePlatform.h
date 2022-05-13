#ifndef __SCENE_PLATFORM_H__
#define __SCENE_PLATFORM_H__

#include "Module.h"

struct SDL_Texture;

class ScenePlatform : public Module
{
public:

	ScenePlatform(bool start_enabled = false);

	// Destructor
	virtual ~ScenePlatform();

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

	//void b2dOnCollision(PhysBody* bodyA, PhysBody* bodyB);

	int sceneTimer;

	PhysBody* h_CB1;
	PhysBody* h_CB2;

	bool godMode = false;

	bool playerRestart;

	bool destroyScene;

	bool scenePlatform;

	SDL_Texture* sunrise_effect = nullptr;

private:
	SDL_Texture* img = nullptr;
	
public:


};

#endif // __SCENE_PLATFORM_H__