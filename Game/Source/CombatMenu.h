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

	CombatMenu(bool start_enabled = false);

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

	SDL_Texture* combatHUD;
	SDL_Texture* enemyTurn;
	SDL_Texture* enemyTurn1;
	SDL_Texture* enemyTurn2;
	SDL_Texture* enemyTurn3;

	SDL_Texture* combatShoot;
	SDL_Texture* combatMelee;
	SDL_Texture* combatItems;
	SDL_Texture* combatEscape;

	//GUI BUTTONS
	GuiButton* combatShootGUI;
	GuiButton* combatMeleeGUI;
	GuiButton* combatItemsGUI;
	GuiButton* combatEscapeGUI;

	int delay = 0;
	int delay2 = 0;
	int delay3 = 0;

	int buttonClickedFx = 0;
};

#endif // __SCENE_FOREST_H__