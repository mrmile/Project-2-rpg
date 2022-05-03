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
	int idForUsability;
};
class InventoryMenu : public Module
{
public:

	InventoryMenu(bool start_enabled = true);

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

	void DrawAllInventoryItems();

	bool OnGuiMouseClickEvent(GuiControl* control);

	void ShowOptions(ItemList* item);

	bool UseItemSelected(ItemList* item);

	void UpdateItemList();

	ItemList GetItemFromPosition(int mouseX,int mouseY);

private:

	SDL_Texture* combatHUD;
	SDL_Texture* characterName1;
	SDL_Texture* object_food;
	SDL_Texture* object_health_pack;

public:

	GuiButton* UseItem;
	GuiButton* DeleteItem;
	GuiButton* EquipItem;
	GuiButton* ItemButton[MAX_ITEMS];

	ItemList itemList[MAX_ITEMS];
	ItemList itemUsing;

	int mouseX, mouseY;

	bool AddItemToInventory(EntityType type,bool usable, bool equipable);
	bool showInventory = false;

	bool showEquipableOptions = false;
	bool showUsableOptions = false;
};

#endif // __SCENE_FOREST_H__