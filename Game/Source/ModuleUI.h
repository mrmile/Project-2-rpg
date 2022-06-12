#ifndef __MODULE_UI_H__
#define __MODULE_UI_H__

#include "Module.h"
#include "GuiButton.h"
#include "GuiCheckbox.h"
#include "GuiSlider.h"

struct SDL_Texture;

class ModuleUI : public Module
{
public:

	ModuleUI(bool start_enabled = false);

	// Destructor
	virtual ~ModuleUI();

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

private:

	SDL_Texture* characterHealth100 = nullptr;
	SDL_Texture* characterHealth80 = nullptr;
	SDL_Texture* characterHealth60 = nullptr;
	SDL_Texture* characterHealth40 = nullptr;
	SDL_Texture* characterHealth20 = nullptr;
	SDL_Texture* characterHealth20Grey = nullptr;
	SDL_Texture* characterHealth0 = nullptr;

	SDL_Texture* QTE_keys_KB = nullptr;
	SDL_Texture* QTE_keys_XB = nullptr;
	SDL_Texture* QTE_keys_PS = nullptr;
	SDL_Texture* QTE_keys_pointer = nullptr;


	//Low Health Effects
	SDL_Texture* lowHealthBlood = nullptr;
	SDL_Texture* lowHealthGreyBg = nullptr;

	//Inventory and Map Icons
	SDL_Texture* inventoryMapIcons = nullptr;

	//Low Health Effects

	int lowHPdelay = 0;

public:

	bool showMapMenu = false;
};

#endif // __SCENE_FOREST_H__

