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
	bool alreadyEquipped = false;
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
	void DrawEquipment();

	bool OnGuiMouseClickEvent(GuiControl* control);

	void ShowOptions(ItemList* item);


	bool DrawItemDescription(ItemList* item);

	bool UseItemSelected(ItemList* item);

	bool DeleteItemSelected(ItemList* item);

	bool DeEquipItemSelected(ItemList* item);

	bool AddItemToInventory(EntityType type, bool usable, bool equipable);

	void UpdateItemList();

	void UpdateEquipment();

	ItemList GetItemFromPosition(int mouseX, int mouseY);

	//Equipment related functions

	bool EquipItemSelected(ItemList* item);

private:

	SDL_Texture* inventoryHUD;
	SDL_Texture* medicKitDescription;
	/*SDL_Texture* characterName1;*/
	SDL_Texture* object_food;
	SDL_Texture* object_health_pack;
	SDL_Texture* object_radio;
	SDL_Texture* object_card;
	SDL_Texture* default_gun;
	SDL_Texture* long_gun;
	SDL_Texture* short_gun;

public:

	GuiButton* UseItem;
	GuiButton* DeleteItem;
	GuiButton* EquipItem;
	GuiButton* EquipmentButton;
	GuiButton* DeEquipButton;
	GuiButton* ItemButton[MAX_ITEMS];

	ItemList itemList[MAX_ITEMS];
	ItemList itemUsing;
	ItemList Equipment;

	int mouseX, mouseY;

	
	bool showInventory = false;

	bool showEquipableOptions = false;
	bool showUsableOptions = false;

	bool showOptionsForEquipment = false;
};

#endif // __SCENE_FOREST_H__