#ifndef __SCENE_CAVE_H__
#define __SCENE_CAVE_H__

#include "Module.h"

struct SDL_Texture;

class SceneCave : public Module
{
public:

	SceneCave(bool start_enabled = false);

	// Destructor
	virtual ~SceneCave();

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

	bool sceneCave;

	bool enableSceneMainMap = false;
	bool enableSceneMotel = false;

private:
	SDL_Texture* img = nullptr;

	int sceneSoundRandomizerNumber;
	
public:
	SDL_Texture* spotLight = nullptr;

	uint cave_bg_noise1 = 0;
	uint cave_bg_noise2 = 0;
	uint cave_bg_noise3 = 0;
	uint cave_bg_noise4 = 0;
	uint cave_bg_noise5 = 0;

};

#endif // __SCENE_CAVE_H__