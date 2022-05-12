#ifndef __INVENTORY_MENU_H__
#define __INVENTORY_MENU_H__

#include "Module.h"
#include "GuiButton.h"
#include "Entity.h"
//#include "GuiCheckbox.h"
//#include "GuiSlider.h"

struct SDL_Texture;

#define MAX_ITEMS 28

enum class ItemType
{
	NONE,
	OBJECT_FOOD,
	OBJECT_HEALTH_PACK,
	OBJECT_RADIO,
	OBJECT_lONG_SCOPE_GUN,
	OBJECT_SHORT_SCOPE_GUN,
	OBJECT_DEFAULT_GUN,
	OBJECT_CARD,
	OBJECT_GRENADE,
	OBJECT_SUIT,
	OBJECT_KNIFE,

};
struct ItemList
{
	ItemType type = ItemType::NONE;
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

	bool AddItemToInventory(ItemType type, bool usable, bool equipable);

	void UpdateItemList();

	void UpdateEquipment();

	ItemList GetItemFromPosition(int mouseX, int mouseY);

	//Equipment related functions

	bool EquipItemSelected(ItemList* item);

private:

	SDL_Texture* inventoryHUD = nullptr;
	SDL_Texture* characterHealth100 = nullptr;
	SDL_Texture* characterHealth80 = nullptr;
	SDL_Texture* characterHealth60 = nullptr;
	SDL_Texture* characterHealth40 = nullptr;
	SDL_Texture* characterHealth20 = nullptr;
	SDL_Texture* characterHealth0 = nullptr;
	SDL_Texture* medicKitDescription = nullptr;
	/*SDL_Texture* characterName1 = nullptr;*/
	SDL_Texture* object_food = nullptr;
	SDL_Texture* object_health_pack = nullptr;
	SDL_Texture* object_radio = nullptr;
	SDL_Texture* object_card = nullptr;
	SDL_Texture* object_suit = nullptr;
	SDL_Texture* object_knife = nullptr;
	SDL_Texture* default_gun = nullptr;
	SDL_Texture* long_gun = nullptr;
	SDL_Texture* short_gun = nullptr;
	SDL_Texture* object_grenade = nullptr;
	SDL_Texture* grenadeDescription = nullptr;
	SDL_Texture* foodDescription = nullptr;
	SDL_Texture* radioDescription = nullptr;
	SDL_Texture* defaultGunDescription = nullptr;
	SDL_Texture* shortGunDescription = nullptr;
	SDL_Texture* longGunDescription = nullptr;
	SDL_Texture* cardDescription = nullptr;
	SDL_Texture* combatSuitDescription = nullptr;
	SDL_Texture* knifeDescription = nullptr;
	SDL_Texture* equipButton = nullptr;
	SDL_Texture* unequipButton = nullptr;
	SDL_Texture* useButton = nullptr;
	SDL_Texture* deleteButton = nullptr;

public:

	GuiButton* UseItem;
	GuiButton* DeleteItem;
	GuiButton* EquipItem;
	GuiButton* EquipmentButton[3];
	GuiButton* DeEquipButton;
	GuiButton* ItemButton[MAX_ITEMS];

	ItemList itemList[MAX_ITEMS];
	ItemList itemUsing;
	ItemList Equipment[3];

	int mouseX, mouseY;

	
	bool showInventory = false;

	bool showEquipableOptions = false;
	bool showUsableOptions = false;

	bool showOptionsForEquipment = false;


	iPoint ActiveRadioPosition;
	bool ActiveRadioAlive;
};

#endif // __SCENE_FOREST_H__