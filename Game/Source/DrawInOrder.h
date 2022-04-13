#ifndef __DRAW_IN_ORDER_H__
#define __DRAW_IN_ORDER_H__

#include "Module.h"
#include "Point.h"

struct SDL_Texture;

struct TextureProperties
{
	SDL_Rect section;
	float parallax;
	SDL_Texture* texture;
	iPoint position;
};

class DrawInOrder : public Module
{
public:

	DrawInOrder(bool start_enabled = false);

	// Destructor
	virtual ~DrawInOrder();

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

	void AddTextureToList_L1(SDL_Texture* texture, iPoint position, SDL_Rect section, float parallax); //Only layer 1 is sorted
	void AddTextureToList_L0(SDL_Texture* texture, iPoint position, SDL_Rect section, float parallax);
	void AddTextureToList_L2(SDL_Texture* texture, iPoint position, SDL_Rect section, float parallax);

	bool compare(TextureProperties a, TextureProperties b);

public:
	//SDL_Texture* img;
	//SDL_Texture* PauseFrame;

	List<TextureProperties*> texturesList_L1;
	List<TextureProperties*> texturesList_L0;
	List<TextureProperties*> texturesList_L2;

};

#endif // __DRAW_IN_ORDER_H__