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

#include <stdio.h>
#include <time.h>

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
	inventoryHUD = app->tex->Load("Assets/textures/GUI/Inventory/InventoryHud4.png");
	playerStats = app->tex->Load("Assets/textures/GUI/Inventory/playerStats.png");
	characterHealth100 = app->tex->Load("Assets/textures/GUI/Inventory/barLife100.png");
	characterHealth80 = app->tex->Load("Assets/textures/GUI/Inventory/barLife80.png");
	characterHealth60 = app->tex->Load("Assets/textures/GUI/Inventory/barLife60.png");
	characterHealth40 = app->tex->Load("Assets/textures/GUI/Inventory/barLife40.png");
	characterHealth20 = app->tex->Load("Assets/textures/GUI/Inventory/barLife20.png");
	characterHealth0 = app->tex->Load("Assets/textures/GUI/Inventory/barLife00.png");
	//characterName1 = app->tex->Load("Assets/textures/GUI/Inventory/chararcterName1.png"); // Just for testing
	object_food = app->tex->Load("Assets/textures/GUI/Inventory/food_item_test.png");
	object_health_pack = app->tex->Load("Assets/textures/GUI/Inventory/health_pack_item_test.png");
	object_radio = app->tex->Load("Assets/textures/GUI/Inventory/radio_item.png");
	object_card = app->tex->Load("Assets/textures/GUI/Inventory/card_item.png");
	object_grenade = app->tex->Load("Assets/textures/GUI/Inventory/grenade_item.png");
	default_gun = app->tex->Load("Assets/textures/GUI/Inventory/default_gun.png");
	short_gun = app->tex->Load("Assets/textures/GUI/Inventory/short_scope_gun.png");
	long_gun = app->tex->Load("Assets/textures/GUI/Inventory/long_scope_gun.png");
	object_suit = app->tex->Load("Assets/textures/GUI/Inventory/combat_suit.png");
	object_knife = app->tex->Load("Assets/textures/GUI/Inventory/combat_knife.png");

	medicKitDescription = app->tex->Load("Assets/textures/GUI/Inventory/itemDescriptions/medicKitDescription.png");
	cardDescription = app->tex->Load("Assets/textures/GUI/Inventory/itemDescriptions/InventoryItemCard.png");
	foodDescription = app->tex->Load("Assets/textures/GUI/Inventory/itemDescriptions/InventoryItemFood.png");
	grenadeDescription = app->tex->Load("Assets/textures/GUI/Inventory/itemDescriptions/InventoryItemGrenade.png");
	defaultGunDescription = app->tex->Load("Assets/textures/GUI/Inventory/itemDescriptions/InventoryItemDefaultGun.png");
	shortGunDescription = app->tex->Load("Assets/textures/GUI/Inventory/itemDescriptions/InventoryItemShortRifle.png");
	longGunDescription = app->tex->Load("Assets/textures/GUI/Inventory/itemDescriptions/InventoryItemLongRifle.png");
	radioDescription = app->tex->Load("Assets/textures/GUI/Inventory/itemDescriptions/InventoryItemRadio.png");
	combatSuitDescription = app->tex->Load("Assets/textures/GUI/Inventory/itemDescriptions/InventoryItemDefaultCombatSuit.png");
	knifeDescription = app->tex->Load("Assets/textures/GUI/Inventory/itemDescriptions/InventoryItemKnife.png");

	equipButton = app->tex->Load("Assets/textures/GUI/Inventory/equipButton.png");
	unequipButton = app->tex->Load("Assets/textures/GUI/Inventory/unequipButton.png");
	useButton = app->tex->Load("Assets/textures/GUI/Inventory/useButton.png");
	deleteButton = app->tex->Load("Assets/textures/GUI/Inventory/deleteButton.png");

	objectEquipedFX = app->audio->LoadFx("Assets/audio/fx/UISounds/objectEquipedFX.wav");

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = app->fonts->Load("Assets/textures/Fonts/rtype_font3.png", lookupTable, 2);
	scoreFont2 = app->fonts->Load("Assets/textures/Fonts/rtype_font3.png", lookupTable, 2);

	DeleteItem = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 29, "Delete item Button", { 25,160,35,25 }, this, deleteButton, NULL, {});
	EquipItem = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 30, "Equip item Button", { 25,160,35,25 }, this, equipButton, NULL, {});
	UseItem = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 31, "Use item Button", { 25,160,35,25 }, this, useButton, NULL, {});
	DeEquipButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 33, "DeEquip item button", { 25,160,35,25 }, this, unequipButton, NULL, {});
	

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

	for (int i = 0; i < 3; i++)
	{
		Equipment[i].itemRect = {69,82 + i*50,26,25};
	}
	for (int i = 0; i < 3; i++)
	{
		EquipmentButton[i] = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 34, "EquipmentButton", Equipment[i].itemRect, this, NULL, NULL, {});

		EquipmentButton[i]->canClick = true;
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
	if (showInventory == true)
	{
		DeleteItem->canClick = true;
		EquipItem->canClick = true;
		UseItem->canClick = true;
		DeEquipButton->canClick = true;

	}
	if (showInventory == false)
	{
		DeleteItem->canClick = false;
		EquipItem->canClick = false;
		UseItem->canClick = false;
		DeEquipButton->canClick = false;
	}

	app->input->GetMousePosition(mouseX, mouseY);
	UpdateItemList();
	UpdateEquipment();

	//ARMAS A RANGO EL 0
	if (Equipment[0].type == ItemType::NONE)
	{
		app->player->EquipmentDamage = 0;
		app->player->EquipmentRange = 0;
	}

	//ARMAS A MELEE EL 1
	if (Equipment[1].type == ItemType::NONE)
	{
		app->player->MeleeDamage = 0;
	}

	//ARMADURA EL 2
	if (Equipment[2].type == ItemType::NONE)
	{
		app->player->PlayerMaxHP = 100;
		combatSuitStrenghtPoints = 0;
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
		app->render->DrawTexture2(playerStats, 0, -6, NULL);

		sprintf_s(scoreText, 10, "%7d", app->player->PlayerMaxHP);
		app->fonts->BlitText(117, 28, scoreFont, scoreText);
		/*app->fonts->BlitText(106, 47, scoreFont, scoreText);*/
		sprintf_s(scoreText2, 10, "%7d", app->player->MeleeDamage + app->player->EquipmentDamage + combatSuitStrenghtPoints);
		app->fonts->BlitText(106, 40, scoreFont2, scoreText2);

		if (app->player->playerHP >= app->player->PlayerMaxHP)
		{
			app->render->DrawTexture2(characterHealth100, 0, -7, NULL);
		}
		if (app->player->playerHP > app->player->PlayerMaxHP / 1.25f && app->player->playerHP < app->player->PlayerMaxHP )
		{
			app->render->DrawTexture2(characterHealth80, 0, -7, NULL);
		}
		if (app->player->playerHP > app->player->PlayerMaxHP / 1.66f && app->player->playerHP <= app->player->PlayerMaxHP / 1.25f)
		{
			app->render->DrawTexture2(characterHealth60, 0, -7, NULL);
		}
		if (app->player->playerHP > app->player->PlayerMaxHP / 2.5f && app->player->playerHP <= app->player->PlayerMaxHP / 1.66f)
		{
			app->render->DrawTexture2(characterHealth40, 0, -7, NULL);
		}
		if (app->player->playerHP > app->player->PlayerMaxHP / 5 && app->player->playerHP <= app->player->PlayerMaxHP / 2.5f)
		{
			app->render->DrawTexture2(characterHealth20, 0, -7, NULL);
		}
		if (app->player->playerHP <= 0)
		{
			app->render->DrawTexture2(characterHealth0, 0, -7, NULL);
		}

		//app->render->DrawTexture2(characterName1, 0, 0, NULL); // Just for testing
		DrawAllInventoryItems();
		DrawEquipment();

		if (showEquipableOptions == true)
		{
			EquipItem->Draw(app->render);
			DeleteItem->Draw(app->render);
			//show Equipable buttons

			DrawItemDescription(&itemUsing);
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
	app->tex->UnLoad(playerStats);
	app->tex->UnLoad(characterHealth100);
	app->tex->UnLoad(characterHealth80);
	app->tex->UnLoad(characterHealth60);
	app->tex->UnLoad(characterHealth40);
	app->tex->UnLoad(characterHealth20);
	app->tex->UnLoad(characterHealth0);
	app->tex->UnLoad(object_food);
	app->tex->UnLoad(object_health_pack);
	app->tex->UnLoad(medicKitDescription);
	app->tex->UnLoad(object_radio);
	app->tex->UnLoad(object_card);
	app->tex->UnLoad(default_gun);
	app->tex->UnLoad(short_gun);
	app->tex->UnLoad(long_gun);
	app->tex->UnLoad(object_grenade);
	app->tex->UnLoad(object_suit);
	app->tex->UnLoad(object_knife);

	app->tex->UnLoad(cardDescription);
	app->tex->UnLoad(foodDescription);
	app->tex->UnLoad(grenadeDescription);
	app->tex->UnLoad(defaultGunDescription);
	app->tex->UnLoad(shortGunDescription);
	app->tex->UnLoad(longGunDescription);
	app->tex->UnLoad(radioDescription);
	app->tex->UnLoad(combatSuitDescription);
	app->tex->UnLoad(knifeDescription);

	app->tex->UnLoad(equipButton);
	app->tex->UnLoad(unequipButton);
	app->tex->UnLoad(useButton);
	app->tex->UnLoad(deleteButton);

	app->guiManager->DestroyGuiControl(29);
	app->guiManager->DestroyGuiControl(30);
	app->guiManager->DestroyGuiControl(31);
	app->guiManager->DestroyGuiControl(32);

	return true;
}

bool InventoryMenu::AddItemToInventory(ItemType type,bool usable,bool equipable)
{
	bool ret;

	for (int i = 0; i < MAX_ITEMS; i++)
	{
		if (itemList[i].type != ItemType::NONE && itemList[i].type == type)
		{
			ret = true;

			if (itemList[i].amount < 10)
			{
				itemList[i].amount++;
				return ret;
			}
			
			return ret;
		}
		if (itemList[i].type == ItemType::NONE)
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
	
		if (itemList[i].type != ItemType::NONE)
		{
			if (itemList[i].type == ItemType::OBJECT_FOOD && itemList[i].amount > 0)
			{
				app->render->DrawTexture2(object_food, itemList[i].itemRect.x, itemList[i].itemRect.y);
			}
			if (itemList[i].type == ItemType::OBJECT_HEALTH_PACK && itemList[i].amount > 0)
			{
				app->render->DrawTexture2(object_health_pack, itemList[i].itemRect.x, itemList[i].itemRect.y);
			}
			if (itemList[i].type == ItemType::OBJECT_RADIO && itemList[i].amount > 0)
			{
				app->render->DrawTexture2(object_radio, itemList[i].itemRect.x, itemList[i].itemRect.y);
			}
			if (itemList[i].type == ItemType::OBJECT_KNIFE && itemList[i].amount > 0)
			{
				app->render->DrawTexture2(object_knife, itemList[i].itemRect.x, itemList[i].itemRect.y);
			}
			if (itemList[i].type == ItemType::OBJECT_SUIT && itemList[i].amount > 0)
			{
				app->render->DrawTexture2(object_suit, itemList[i].itemRect.x, itemList[i].itemRect.y);
			}
			if (itemList[i].type == ItemType::OBJECT_CARD && itemList[i].amount > 0)
			{
				app->render->DrawTexture2(object_card, itemList[i].itemRect.x, itemList[i].itemRect.y);
			}
			if (itemList[i].type == ItemType::OBJECT_GRENADE && itemList[i].amount > 0)
			{
				app->render->DrawTexture2(object_grenade, itemList[i].itemRect.x, itemList[i].itemRect.y);
			}
			if (itemList[i].type == ItemType::OBJECT_DEFAULT_GUN && itemList[i].amount > 0)
			{
				app->render->DrawTexture2(default_gun, itemList[i].itemRect.x, itemList[i].itemRect.y);
			}
			if (itemList[i].type == ItemType::OBJECT_lONG_SCOPE_GUN && itemList[i].amount > 0)
			{
				app->render->DrawTexture2(long_gun, itemList[i].itemRect.x, itemList[i].itemRect.y);
			}
			if (itemList[i].type == ItemType::OBJECT_SHORT_SCOPE_GUN && itemList[i].amount > 0)
			{
				app->render->DrawTexture2(short_gun, itemList[i].itemRect.x, itemList[i].itemRect.y);
			}
			
		}
	}
}

void InventoryMenu::DrawEquipment()
{
	for (int i = 0; i < 3; i++)
	{
		if (Equipment[i].type != ItemType::NONE)
		{
			if (Equipment[i].type == ItemType::OBJECT_DEFAULT_GUN && Equipment[i].amount > 0)
			{
				app->render->DrawTexture2(default_gun, Equipment[i].itemRect.x, Equipment[i].itemRect.y);
			}
			if (Equipment[i].type == ItemType::OBJECT_lONG_SCOPE_GUN && Equipment[i].amount > 0)
			{
				app->render->DrawTexture2(long_gun, Equipment[i].itemRect.x, Equipment[i].itemRect.y);
			}
			if (Equipment[i].type == ItemType::OBJECT_SHORT_SCOPE_GUN && Equipment[i].amount > 0)
			{
				app->render->DrawTexture2(short_gun, Equipment[i].itemRect.x, Equipment[i].itemRect.y);
			}
			if (Equipment[i].type == ItemType::OBJECT_KNIFE && Equipment[i].amount > 0)
			{
				app->render->DrawTexture2(object_knife, Equipment[i].itemRect.x, Equipment[i].itemRect.y);
			}
			if (Equipment[i].type == ItemType::OBJECT_SUIT && Equipment[i].amount > 0)
			{
				app->render->DrawTexture2(object_suit, Equipment[i].itemRect.x, Equipment[i].itemRect.y);
			}
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
	}
	for (int i = 0; i < 3; i++)
	{
		if ((mouseX > Equipment[i].itemRect.x && mouseX < (Equipment[i].itemRect.x + Equipment[i].itemRect.w)) &&
			(mouseY > Equipment[i].itemRect.y && mouseY < Equipment[i].itemRect.y + Equipment[i].itemRect.h))
		{
			itemUsing = Equipment[i];
			return Equipment[i];
		}
	}
}

bool InventoryMenu::DrawItemDescription(ItemList* item)
{
	if (item->amount > 0)
	{
		if (item->type == ItemType::OBJECT_FOOD)
		{
			app->render->DrawTexture2(foodDescription, -15, 0, NULL);
		
			return true;
		}
		if (item->type == ItemType::OBJECT_HEALTH_PACK)
		{
			app->render->DrawTexture2(medicKitDescription, -15, 0, NULL);

			return true;
		}
		if (item->type == ItemType::OBJECT_CARD)
		{
			app->render->DrawTexture2(cardDescription, -15, 0, NULL);

			return true;
		}
		if (item->type == ItemType::OBJECT_GRENADE)
		{
			app->render->DrawTexture2(grenadeDescription, -15, 0, NULL);

			return true;
		}
		if (item->type == ItemType::OBJECT_DEFAULT_GUN)
		{
			app->render->DrawTexture2(defaultGunDescription, -15, 0, NULL);

			return true;
		}
		if (item->type == ItemType::OBJECT_SHORT_SCOPE_GUN)
		{
			app->render->DrawTexture2(shortGunDescription, -15, 0, NULL);

			return true;
		}
		if (item->type == ItemType::OBJECT_lONG_SCOPE_GUN)
		{
			app->render->DrawTexture2(longGunDescription, -15, 0, NULL);

			return true;
		}
		if (item->type == ItemType::OBJECT_RADIO)
		{
			app->render->DrawTexture2(radioDescription, -15, 0, NULL);

			return true;
		}
		if (item->type == ItemType::OBJECT_SUIT)
		{
			app->render->DrawTexture2(combatSuitDescription, -15, 0, NULL);

			return true;
		}
		if (item->type == ItemType::OBJECT_KNIFE)
		{
			app->render->DrawTexture2(knifeDescription, -15, 0, NULL);

			return true;
		}
	}
}

bool InventoryMenu::UseItemSelected(ItemList* item)
{

	if (item->amount > 0)
	{
		if (item->type == ItemType::OBJECT_FOOD)
		{
			item->amount--;
			app->player->playerHP += 15;

			return true;
		}
		if (item->type == ItemType::OBJECT_HEALTH_PACK)
		{
			item->amount--;
			app->player->playerHP += 100;

			return true;
		}
		if (item->type == ItemType::OBJECT_RADIO)
		{
			item->amount--;
			//Add radio particle so zombies follow it instead of following the player
			app->particles->AddParticle(app->particles->RadioActive, app->player->position.x, app->player->position.y+25, Collider::Type::ACTIVE_RADIO);

			app->audio->ChangeMusic(RADIO_ITEM_MUSIC, 0.0f, 0.0f);
			app->audio->playMusicSpatially = true;
			app->audio->musicSourcePosition = app->player->position;

			return true;
		}
	}
}

bool InventoryMenu::DeEquipItemSelected(ItemList* item)
{
	if (item->type != ItemType::NONE)
	{
		if (item->type == ItemType::OBJECT_DEFAULT_GUN)
		{
			app->audio->PlayFx(objectEquipedFX, 0);
			AddItemToInventory(ItemType::OBJECT_DEFAULT_GUN, false, true);

			Equipment[0].amount = 0;
			Equipment[0].alreadyEquipped = false;
			
			return true;
		}
		if (item->type == ItemType::OBJECT_lONG_SCOPE_GUN)
		{
			app->audio->PlayFx(objectEquipedFX, 0);
			AddItemToInventory(ItemType::OBJECT_lONG_SCOPE_GUN, false, true);

			Equipment[0].amount = 0;
			Equipment[0].alreadyEquipped = false;

			return true;
		}
		if (item->type == ItemType::OBJECT_SHORT_SCOPE_GUN)
		{
			app->audio->PlayFx(objectEquipedFX, 0);
			AddItemToInventory(ItemType::OBJECT_SHORT_SCOPE_GUN, false, true);

			Equipment[0].amount = 0;
			Equipment[0].alreadyEquipped = false;
		
			return true;
		}
		if (item->type == ItemType::OBJECT_KNIFE)
		{
			app->audio->PlayFx(objectEquipedFX, 0);
			AddItemToInventory(ItemType::OBJECT_KNIFE, false, true);

			Equipment[1].amount = 0;
			Equipment[1].alreadyEquipped = false;

			return true;
		}
		if (item->type == ItemType::OBJECT_SUIT)
		{
			app->audio->PlayFx(objectEquipedFX, 0);
			AddItemToInventory(ItemType::OBJECT_SUIT, false, true);
			app->player->playerHP -= 100;
			Equipment[2].amount = 0;
			Equipment[2].alreadyEquipped = false;

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
	if (Equipment[0].type == ItemType::NONE)
	{
		//Also need to create a function for the player that updates it's damage in function of the item equipped
		if (item->type == ItemType::OBJECT_DEFAULT_GUN || item->type == ItemType::OBJECT_SHORT_SCOPE_GUN || item->type == ItemType::OBJECT_lONG_SCOPE_GUN)
		{
			app->audio->PlayFx(objectEquipedFX, 0);
			Equipment[0].type = item->type;
			Equipment[0].alreadyEquipped = true;
			Equipment[0].amount = 1;
			item->amount--;
			if (Equipment[0].type == ItemType::OBJECT_DEFAULT_GUN)
			{
				app->player->EquipmentDamage = 2;
				app->player->EquipmentRange = 150;
			}
			if (Equipment[0].type == ItemType::OBJECT_SHORT_SCOPE_GUN)
			{
				app->player->EquipmentDamage = 6;
				app->player->EquipmentRange = 75;
			}
			if (Equipment[0].type == ItemType::OBJECT_lONG_SCOPE_GUN)
			{
				app->player->EquipmentDamage = 3;
				app->player->EquipmentRange = 300;
			}
		}
	}

	if (Equipment[1].type == ItemType::NONE)
	{
		//Also need to create a function for the player that updates it's damage in function of the item equipped
		if (item->type == ItemType::OBJECT_KNIFE)
		{
			app->audio->PlayFx(objectEquipedFX, 0);
			Equipment[1].type = item->type;
			Equipment[1].alreadyEquipped = true;
			Equipment[1].amount = 1;
			item->amount--;

			if (Equipment[1].type == ItemType::OBJECT_KNIFE)
			{
				app->player->MeleeDamage = 2;
			}
		}
		
	}
	if (Equipment[2].type == ItemType::NONE)
	{
		if (item->type == ItemType::OBJECT_SUIT)
		{
			app->audio->PlayFx(objectEquipedFX, 0);
			//Also need to create a function for the player that updates it's damage in function of the item equipped
			Equipment[2].type = item->type;
			Equipment[2].alreadyEquipped = true;
			Equipment[2].amount = 1;
			item->amount--;

			if (Equipment[2].type == ItemType::OBJECT_SUIT)
			{
				app->player->playerHP += 100;
				app->player->PlayerMaxHP = 200;
				combatSuitStrenghtPoints = 8;
			}
		}
		
	}

	return true;

}
void InventoryMenu::UpdateItemList()
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{

		if (itemUsing.type != ItemType::NONE)
		{
			if (itemList[i].type == itemUsing.type)
			{
				itemList[i].amount = itemUsing.amount;

				if (itemList[i].amount == 0)
				{
					itemList[i].usable = false;
					itemList[i].equipable = false;
					itemList[i].type = ItemType::NONE;
				}
			}
		}
		
	}
}

void InventoryMenu::UpdateEquipment()
{
	for (int i = 0; i < 3; i++)
	{
		if (itemUsing.type != ItemType::NONE)
		{
			if (Equipment[i].type == itemUsing.type)
			{

				if (Equipment[i].amount == 0)
				{
					Equipment[i].usable = false;
					Equipment[i].equipable = false;
					Equipment[i].type = ItemType::NONE;
				}
			}
		}
	}

}

bool InventoryMenu::SaveState(pugi::xml_node& data) const
{
	
	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (itemList[i].type != ItemType::NONE)
		{
			int type = (int)itemList[i].type;
			pugi::xml_node item = data.append_child("item_list");
			item.append_attribute("type") = type;
			item.append_attribute("amount") = itemList[i].amount;
			item.append_attribute("usable") = itemList[i].usable;		
			item.append_attribute("equipable") = itemList[i].equipable;
			item.append_attribute("already_equipped") = itemList[i].alreadyEquipped;

			item.next_sibling("item_list");
		}
	}
	for (uint i = 0; i < 3; i++)
	{
		if (Equipment[i].type != ItemType::NONE)
		{
			int type = (int)Equipment[i].type;
			pugi::xml_node equipment = data.append_child("equipment_list");

			equipment.append_attribute("type") = type;
			equipment.append_attribute("amount") = Equipment[i].amount;
			equipment.append_attribute("usable") = Equipment[i].usable;
			equipment.append_attribute("equipable") = Equipment[i].equipable;
			equipment.append_attribute("already_equipped") = Equipment[i].alreadyEquipped;

			equipment.next_sibling("equipment_list");
		}
	}

	return true;

}
bool InventoryMenu::LoadState(pugi::xml_node& data)
{
	pugi::xml_node item = data.child("item_list");
	pugi::xml_node equipment = data.child("equipment_list");

	
	for (uint i = 0; i < MAX_ITEMS; ++i)
	{
		if (itemList[i].type == ItemType::NONE)
		{
			itemList[i].type = (ItemType)item.attribute("type").as_int();
			itemList[i].amount = item.attribute("amount").as_int();
			itemList[i].usable = item.attribute("usable").as_bool();
			itemList[i].equipable = item.attribute("equipable").as_bool();
			itemList[i].alreadyEquipped = item.attribute("already_equipped").as_bool();

		}
		item = item.next_sibling();
	}

	for (uint i = 0; i < 3; ++i)
	{
		if (Equipment[i].type == ItemType::NONE)
		{
			Equipment[i].type = (ItemType)equipment.attribute("type").as_int();
			Equipment[i].amount = equipment.attribute("amount").as_int();
			Equipment[i].usable = equipment.attribute("usable").as_bool();
			Equipment[i].equipable = equipment.attribute("equipable").as_bool();
			Equipment[i].alreadyEquipped = equipment.attribute("already_equipped").as_bool();

		}
		equipment = equipment.next_sibling();
	}
	

	return true;
}