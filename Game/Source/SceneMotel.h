#ifndef __SCENE_MOTEL_H__
#define __SCENE_MOTEL_H__

#include "Module.h"

struct SDL_Texture;

class SceneMotel : public Module
{
public:

	SceneMotel(bool start_enabled = false);

	// Destructor
	virtual ~SceneMotel();

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

	bool sceneMotel;

	bool enableSceneCave = false;

	int PauseDelay=0;

	SDL_Rect* rectangle = {};

private:
	SDL_Texture* img = nullptr;
	SDL_Texture* PauseFrame = nullptr;
};

#endif // __SCENE_MOTEL_H__