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

	void DrawEntitiesHP();

	bool OnGuiMouseClickEvent(GuiControl* control);

private:

	SDL_Texture* combatHUD = nullptr;
	SDL_Texture* enemyTurn = nullptr;
	SDL_Texture* enemyTurn1 = nullptr;
	SDL_Texture* enemyTurn2 = nullptr;
	SDL_Texture* enemyTurn3 = nullptr;

	SDL_Texture* combatShoot = nullptr;
	SDL_Texture* combatMelee = nullptr;
	SDL_Texture* combatItems = nullptr;
	SDL_Texture* combatEscape = nullptr;

	SDL_Texture* entitiesHP100 = nullptr;
	SDL_Texture* entitiesHP90 = nullptr;
	SDL_Texture* entitiesHP80 = nullptr;
	SDL_Texture* entitiesHP70 = nullptr;
	SDL_Texture* entitiesHP60 = nullptr;
	SDL_Texture* entitiesHP50 = nullptr;
	SDL_Texture* entitiesHP40 = nullptr;
	SDL_Texture* entitiesHP30 = nullptr;
	SDL_Texture* entitiesHP20 = nullptr;
	SDL_Texture* entitiesHP10 = nullptr;

	//GUI BUTTONS
	GuiButton* combatShootGUI = nullptr;
	GuiButton* combatMeleeGUI = nullptr;
	GuiButton* combatItemsGUI = nullptr;
	GuiButton* combatEscapeGUI = nullptr;

	int delay = 0;
	int delay2 = 0;
	int delay3 = 0;

	int buttonClickedFx = 0;
	int buttonClickedMelee = 0;

	bool transitionStarting = true;
};

#endif // __SCENE_FOREST_H__