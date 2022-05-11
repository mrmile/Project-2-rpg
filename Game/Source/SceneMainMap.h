#ifndef __SCENE_MAIN_MAP_H__
#define __SCENE_MAIN_MAP_H__

#include "Module.h"

struct SDL_Texture;

class SceneMainMap : public Module
{
public:

	SceneMainMap(bool start_enabled = false);

	// Destructor
	virtual ~SceneMainMap();

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

	bool sceneMainMap;

	bool enableSceneCave = false;
	bool enableSceneBase = false;

	int PauseDelay=0;

	SDL_Rect* rectangle = {};

	SDL_Texture* spotLight = nullptr;
	SDL_Texture* sunrise_effect = nullptr;

private:
	SDL_Texture* img = nullptr;
	SDL_Texture* PauseFrame = nullptr;
};

#endif // __SCENE_MAIN_MAP_H__