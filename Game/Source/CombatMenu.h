#ifndef __COMBAT_MENU_H__
#define __COMBAT_MENU_H__

#include "Module.h"
#include "GuiButton.h"
#include "GuiCheckbox.h"
#include "GuiSlider.h"

struct SDL_Texture;

class CombatMenu : public Module
{
public:

	CombatMenu(bool start_enabled);

	// Destructor
	virtual ~CombatMenu();

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

	bool OnGuiMouseClickEvent(GuiControl* control);

private:

};

#endif // __SCENE_FOREST_H__