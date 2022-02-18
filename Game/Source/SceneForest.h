#ifndef __SCENE_FOREST_H__
#define __SCENE_FOREST_H__

#include "Module.h"

struct SDL_Texture;

class SceneForest : public Module
{
public:

	SceneForest(bool start_enabled = false);

	// Destructor
	virtual ~SceneForest();

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

	bool sceneForest;

	int PauseDelay=0;

	SDL_Rect* rectangle = {};

private:
	SDL_Texture* img;
	SDL_Texture* PauseFrame;
};

#endif // __SCENE_FOREST_H__