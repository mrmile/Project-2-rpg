#include "InventoryMenu.h"
#include "PauseMenu.h"
#include "TitleScreen.h"
#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneMainMap.h"
#include "SceneCave.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "Map.h"
#include "EntityManager.h"
#include "GameManager.h"
#include "GuiManager.h"
#include "CreditsScreen.h"
#include "Entity.h"
#include "Defs.h"
#include "Log.h"
#include "QuestManager.h"

InventoryMenu::InventoryMenu(bool start_enabled) : Module(start_enabled)
{
	name.Create("InventoryMenu");
}

// Destructor
InventoryMenu::~InventoryMenu()
{}

// Called before render is available
bool InventoryMenu::Awake()
{
	LOG("Loading Inventory Menu");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool InventoryMenu::Start()
{
	inventoryHUD = app->tex->Load("Assets/textures/GUI/Inventory/InventoryHud.png");
	medicKitDescription = app->tex->Load("Assets/textures/GUI/Inventory/medicKitDescription.png");
	//characterName1 = app->tex->Load("Assets/textures/GUI/Inventory/chararcterName1.png"); // Just for testing
	object_food = app->tex->Load("Assets/textures/GUI/Inventory/food_item_test.png");
	object_health_pack = app->tex->Load("Assets/textures/GUI/Inventory/health_pack_item_test.png");
	//Still need button textures the position does not matter right now as we are gonna update it 

	Equipment.itemRect = { 70,107,26,25 };

	DeleteItem = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 29, "Delete item Button", { 25,160,26,25 }, this, object_health_pack, NULL, {});
	EquipItem = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 30, "Equip item Button", { 25,160,26,25 }, this, object_food, NULL, {});
	UseItem = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 31, "Use item Button", { 25,160,26,25 }, this, object_food, NULL, {});
	DeEquipButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 33, "DeEquip item button", { 25,160,26,25 }, this, object_food, NULL, {});
	EquipmentButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 34, "EquipmentButton", Equipment.itemRect, this, NULL, NULL, {});

	int counter = 0;

	for (int j = 0; j < MAX_ITEMS / 4; j++)
	{
		for (int i = 0; i < MAX_ITEMS / 7; i++)
		{
			itemList[counter].itemRect = { 253 + (i * 46),65 + (j * 36),26,25 };
			counter++;
		}
		
	}
	
	for (int z = 0; z < MAX_ITEMS; z++)
	{
		ItemButton[z] = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 32, "Access item button", itemList[z].itemRect, this, NULL, NULL, {});

		ItemButton[z]->canClick = true;

	}


	

	return true;
}

// Called each loop iteration
bool InventoryMenu::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool InventoryMenu::Update(float dt)
{
	//Used to get what item we are checking with the mouse in order for the buttons to work
	
	app->input->GetMousePosition(mouseX, mouseY);
	UpdateItemList();
	UpdateEquipment();

	if (Equipment.type == EntityType::NONE)
	{
		app->player->EquipmentDamage = 0;
		app->player->EquipmentRange = 0;
	}

	return true;
}

// Called each loop iteration
bool InventoryMenu::PostUpdate()
{
	bool ret = true;

	if (app->player->pauseMenu == false && app->titleScreen->active == false && app->creditsScreen->active == false && showInventory == true)
	{
		app->render->DrawTexture2(inventoryHUD, 0, 0, NULL);
		//app->render->DrawTexture2(characterName1, 0, 0, NULL); // Just for testing
		DrawAllInventoryItems();
		DrawEquipment();

		if (showEquipableOptions == true)
		{
			EquipItem->Draw(app->render);
			DeleteItem->Draw(app->render);
			//show Equipable buttons
		}
		if (showUsableOptions == true)
		{
			UseItem->Draw(app->render);
			DeleteItem->Draw(app->render);
			//show Usable Options

			DrawItemDescription(&itemUsing);
		}
		if (showOptionsForEquipment == true)
		{
			DeEquipButton->Draw(app->render);
		}
	}
	
	if (showInventory == false)
	{
		showEquipableOptions = false;
		showUsableOptions = false;
		showOptionsForEquipment = false;
	}

	return true;
}

// Called before quitting
bool InventoryMenu::CleanUp()
{
	app->tex->UnLoad(inventoryHUD);
	app->tex->UnLoad(object_food);
	app->tex->UnLoad(object_health_pack);
	app->tex->UnLoad(medicKitDescription);
	app->guiManager->DestroyGuiControl(29);
	app->guiManager->DestroyGuiControl(30);
	app->guiManager->DestroyGuiControl(31);
	app->guiManager->DestroyGuiControl(32);

	return true;
}

bool InventoryMenu::AddItemToInventory(EntityType type,bool usable,bool equipable)
{
	bool ret;

	for (int i = 0; i < MAX_ITEMS; i++)
	{
		if (itemList[i].type != EntityType::NONE && itemList[i].type == type)
		{
			ret = true;

			if (itemList[i].amount < 10)
			{
				itemList[i].amount++;
				return ret;
			}
			
			return ret;
		}
		if (itemList[i].type == EntityType::NONE)
		{
			ret = true;

			itemList[i].amount = 1;
			itemList[i].usable = usable;
			itemList[i].equipable = equipable;
			itemList[i].type = type;

			return ret;
		}
	
	}

}

void InventoryMenu::DrawAllInventoryItems()
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
	
		if (itemList[i].type != EntityType::NONE)
		{
			if (itemList[i].type == EntityType::OBJECT_FOOD && itemList[i].amount > 0)
			{
				app->render->DrawTexture2(object_food, itemList[i].itemRect.x, itemList[i].itemRect.y);
			}
			if (itemList[i].type == EntityType::OBJECT_HEALTH_PACK && itemList[i].amount > 0)
			{
				app->render->DrawTexture2(object_health_pack, itemList[i].itemRect.x, itemList[i].itemRect.y);
			}
			if (itemList[i].type == EntityType::OBJECT_RADIO && itemList[i].amount > 0)
			{
				//app->render->DrawTexture2(object_health_pack, itemList[i].itemRect.x, itemList[i].itemRect.y);
			}
			if (itemList[i].type == EntityType::OBJECT_DEFAULT_GUN && itemList[i].amount > 0)
			{
				//app->render->DrawTexture2(object_health_pack, itemList[i].itemRect.x, itemList[i].itemRect.y);
			}
			if (itemList[i].type == EntityType::OBJECT_lONG_SCOPE_GUN && itemList[i].amount > 0)
			{
				//app->render->DrawTexture2(object_health_pack, itemList[i].itemRect.x, itemList[i].itemRect.y);
			}
			if (itemList[i].type == EntityType::OBJECT_SHORT_SCOPE_GUN && itemList[i].amount > 0)
			{
				//app->render->DrawTexture2(object_health_pack, itemList[i].itemRect.x, itemList[i].itemRect.y);
			}
			
		}
	}
}

void InventoryMenu::DrawEquipment()
{
	if (Equipment.type != EntityType::NONE)
	{
		if (Equipment.type == EntityType::OBJECT_DEFAULT_GUN && Equipment.amount > 0)
		{
			app->render->DrawTexture2(object_health_pack, Equipment.itemRect.x, Equipment.itemRect.y);
		}
		if (Equipment.type == EntityType::OBJECT_lONG_SCOPE_GUN && Equipment.amount > 0)
		{
			//app->render->DrawTexture2(object_health_pack, itemList[i].itemRect.x, itemList[i].itemRect.y);
		}
		if (Equipment.type == EntityType::OBJECT_SHORT_SCOPE_GUN && Equipment.amount > 0)
		{
			//app->render->DrawTexture2(object_health_pack, itemList[i].itemRect.x, itemList[i].itemRect.y);
		}
	}
}

bool InventoryMenu::OnGuiMouseClickEvent(GuiControl* control)
{
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		if (control->id == 29 && DeleteItem->canClick == true)
		{
			//Delete Item Button
			app->audio->PlayFx(app->pause_menu->buttonClickedFx, 0);
			DeleteItemSelected(&itemUsing);
		}
		if (control->id == 30 && EquipItem->canClick == true)
		{
			//Equip item button
			app->audio->PlayFx(app->pause_menu->buttonClickedFx, 0);
			EquipItemSelected(&itemUsing);
		}
		if (control->id == 31 && UseItem->canClick == true)
		{
			//Use item button
			app->audio->PlayFx(app->pause_menu->buttonClickedFx, 0);
			UseItemSelected(&itemUsing);
		}
		if (control->id == 32)
		{
			//Item Button in general
			app->audio->PlayFx(app->pause_menu->buttonClickedFx, 0);
			ShowOptions(&GetItemFromPosition(mouseX, mouseY));
		
		}
		if (control->id == 33)
		{
			//DeEquip button
			app->audio->PlayFx(app->pause_menu->buttonClickedFx, 0);
			DeEquipItemSelected(&itemUsing);
		}
		if (control->id == 34)
		{
			//Equipment Button
			app->audio->PlayFx(app->pause_menu->buttonClickedFx, 0);
			ShowOptions(&GetItemFromPosition(mouseX, mouseY));
		}
	}
	}

	return true;
}
void InventoryMenu::ShowOptions(ItemList* item)
{

	if (item->usable == true)
	{
		UseItem->bounds.x = item->itemRect.x + item->itemRect.w;
		UseItem->bounds.y = item->itemRect.y - item->itemRect.h;
		DeleteItem->bounds.x = item->itemRect.x + item->itemRect.w;
		DeleteItem->bounds.y = item->itemRect.y;

		showEquipableOptions = false;
		showUsableOptions = true;
		showOptionsForEquipment = false;

	}
	if (item->equipable == true)
	{
		EquipItem->bounds.x = item->itemRect.x + item->itemRect.w;
		EquipItem->bounds.y = item->itemRect.y - item->itemRect.h;
		DeleteItem->bounds.x = item->itemRect.x + item->itemRect.w;
		DeleteItem->bounds.y = item->itemRect.y;

		showUsableOptions = false;
		showEquipableOptions = true;
		showOptionsForEquipment = false;
	}
	if (item->alreadyEquipped == true)
	{
		DeEquipButton->bounds.x = item->itemRect.x + item->itemRect.w;
		DeEquipButton->bounds.y = item->itemRect.y;

		showOptionsForEquipment = true;
		showUsableOptions = false;
		showEquipableOptions = false;
	}
}

ItemList InventoryMenu::GetItemFromPosition(int mouseX, int mouseY)
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		if ((mouseX > itemList[i].itemRect.x && mouseX < (itemList[i].itemRect.x + itemList[i].itemRect.w)) &&
			(mouseY > itemList[i].itemRect.y && mouseY < itemList[i].itemRect.y + itemList[i].itemRect.h))
		{
			itemUsing = itemList[i];
			return itemList[i];
		}

		if ((mouseX > Equipment.itemRect.x && mouseX < (Equipment.itemRect.x + Equipment.itemRect.w)) &&
			(mouseY > Equipment.itemRect.y && mouseY < Equipment.itemRect.y + Equipment.itemRect.h))
		{
			itemUsing = Equipment;
			return Equipment;
		}
	}
}

bool InventoryMenu::DrawItemDescription(ItemList* item)
{
	if (item->amount > 0)
	{
		/*if (item->type == EntityType::OBJECT_FOOD)
		{
		
			return true;
		}*/
		if (item->type == EntityType::OBJECT_HEALTH_PACK)
		{
			app->render->DrawTexture2(medicKitDescription, -15, 0, NULL);

			return true;
		}
	}
}

bool InventoryMenu::UseItemSelected(ItemList* item)
{
	if (item->amount > 0)
	{
		if (item->type == EntityType::OBJECT_FOOD)
		{
			item->amount--;
			app->player->playerHP += 15;

			return true;
		}
		if (item->type == EntityType::OBJECT_HEALTH_PACK)
		{
			item->amount--;
			app->player->playerHP += 100;

			return true;
		}
		if (item->type == EntityType::OBJECT_RADIO)
		{
			item->amount--;
			//Add radio particle so zombies follow it instead of following the player
			app->particles->AddParticle(app->particles->RadioActive, app->player->position.x, app->player->position.y+25, Collider::Type::ACTIVE_RADIO);

			return true;
		}
	}
}

bool InventoryMenu::DeEquipItemSelected(ItemList* item)
{
	if (item->type != EntityType::NONE)
	{
		if (item->type == EntityType::OBJECT_DEFAULT_GUN)
		{
			AddItemToInventory(EntityType::OBJECT_DEFAULT_GUN, false, true);

			Equipment.amount = 0;
			Equipment.alreadyEquipped = false;
			
			return true;
		}
		if (item->type == EntityType::OBJECT_lONG_SCOPE_GUN)
		{
			AddItemToInventory(EntityType::OBJECT_lONG_SCOPE_GUN, false, true);

			Equipment.amount = 0;
			Equipment.alreadyEquipped = false;

			return true;
		}
		if (item->type == EntityType::OBJECT_SHORT_SCOPE_GUN)
		{
			AddItemToInventory(EntityType::OBJECT_SHORT_SCOPE_GUN, false, true);

			Equipment.amount = 0;
			Equipment.alreadyEquipped = false;
		
			return true;
		}
	}
}
bool InventoryMenu::DeleteItemSelected(ItemList* item)
{
	if (item->amount > 0)
	{
		item->amount--;

		return true;
	}
}
bool InventoryMenu::EquipItemSelected(ItemList* item)
{
	if (Equipment.type == EntityType::NONE)
	{
		//Also need to create a function for the player that updates it's damage in function of the item equipped
		Equipment.type = item->type;
		Equipment.alreadyEquipped = true;
		Equipment.amount = 1;
		item->amount--;
		if (Equipment.type == EntityType::OBJECT_DEFAULT_GUN)
		{
			app->player->EquipmentDamage = 2;
			app->player->EquipmentRange = 150;
		}
		if (Equipment.type == EntityType::OBJECT_SHORT_SCOPE_GUN)
		{
			app->player->EquipmentDamage = 6;
			app->player->EquipmentRange = 75;
		}
		if (Equipment.type == EntityType::OBJECT_lONG_SCOPE_GUN)
		{
			app->player->EquipmentDamage = 3;
			app->player->EquipmentRange = 300;
		}
		
		return true;
	}
	if (Equipment.type != EntityType::NONE)
	{
		//do not allow the equipment change unless you unequip the item first
		return true;
	}
	
}
void InventoryMenu::UpdateItemList()
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{

		if (itemUsing.type != EntityType::NONE)
		{
			if (itemList[i].type == itemUsing.type)
			{
				itemList[i].amount = itemUsing.amount;

				if (itemList[i].amount == 0)
				{
					itemList[i].usable = false;
					itemList[i].equipable = false;
					itemList[i].type = EntityType::NONE;
				}
			}
		}
		
	}
}

void InventoryMenu::UpdateEquipment()
{
	if (itemUsing.type != EntityType::NONE)
	{
		if (Equipment.type == itemUsing.type)
		{

			if (Equipment.amount == 0)
			{
				Equipment.usable = false;
				Equipment.equipable = false;
				Equipment.type = EntityType::NONE;
			}
		}
	}
}