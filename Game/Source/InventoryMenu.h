#ifndef __INVENTORY_MENU_H__
#define __INVENTORY_MENU_H__

#include "Module.h"
#include "GuiButton.h"
#include "Entity.h"
//#include "GuiCheckbox.h"
//#include "GuiSlider.h"

struct SDL_Texture;

#define MAX_ITEMS 28

struct ItemList
{
	EntityType type = EntityType::NONE;
	int amount = 0;
	bool usable = false;
	bool equipable = false;
	SDL_Rect itemRect = { 0,0,0,0 };

};
class InventoryMenu : public Module
{
public:

	InventoryMenu(bool start_enabled = false);

	// Destructor
	virtual ~InventoryMenu();

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

	/*bool OnGuiMouseClickEvent(GuiControl* control);*/

private:

	SDL_Texture* combatHUD;
	SDL_Texture* characterName1;

public:

	GuiButton* UseItem;
	GuiButton* DeleteItem;
	GuiButton* EquipItem;

	ItemList itemList[MAX_ITEMS];

	void AddItemToInventory(EntityType type,bool usable, bool equipable);
	bool showInventory = false;

};

#endif // __SCENE_FOREST_H__