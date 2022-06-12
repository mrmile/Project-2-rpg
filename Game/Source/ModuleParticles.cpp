#include "ModuleParticles.h"

#include "App.h"

#include "Textures.h"
#include "Render.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "TitleScreen.h"
#include "SceneCave.h"
#include "SceneMainMap.h"
#include "SceneBase.h"
#include "SceneMotel.h"
#include "ScenePlatform.h"
#include "QuestManager.h"
#include "InventoryMenu.h"
#include "Audio.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool start_enabled) : Module(start_enabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;

	enemyDefeat.anim.PushBack({ 8, 16, 20, 20 });
	enemyDefeat.anim.PushBack({ 29, 16, 20, 20 });
	enemyDefeat.anim.PushBack({ 49, 16, 20, 20 });
	enemyDefeat.anim.PushBack({ 76, 16, 20, 20 });
	enemyDefeat.anim.PushBack({ 102, 16, 20, 20 });
	enemyDefeat.speed.x = 0;
	enemyDefeat.speed.y = 0;
	enemyDefeat.anim.loop = false;
	enemyDefeat.anim.speed = 0.15f;

	coin.anim.PushBack({ 13, 51, 12, 16 });
	coin.anim.PushBack({ 33, 51, 12, 16 });
	coin.anim.PushBack({ 53, 51, 12, 16 });
	coin.anim.PushBack({ 73, 51, 12, 16 });
	coin.speed.x = 0;
	coin.speed.y = 0;
	coin.anim.loop = true;
	coin.anim.speed = 0.15f;

	lifeRecoverPowerUp.anim.PushBack({ 51, 81, 19, 18 });
	lifeRecoverPowerUp.speed.x = 0;
	lifeRecoverPowerUp.speed.y = 0;
	lifeRecoverPowerUp.anim.loop = true;
	lifeRecoverPowerUp.anim.speed = 0.15f;

	checkPoint.anim.PushBack({ 14, 128, 22, 30 });
	checkPoint.anim.PushBack({ 36, 128, 22, 30 });
	checkPoint.anim.PushBack({ 58, 128, 22, 30 });
	checkPoint.anim.PushBack({ 80, 128, 22, 30 });
	checkPoint.anim.PushBack({ 103, 128, 22, 30 });
	checkPoint.speed.x = 0;
	checkPoint.speed.y = 0;
	checkPoint.anim.loop = true;
	checkPoint.anim.speed = 0.15f;

	checkPointGrabbed.anim.PushBack({ 137, 129, 22, 30 });
	checkPointGrabbed.anim.PushBack({ 157, 129, 22, 30 });
	checkPointGrabbed.speed.x = 0;
	checkPointGrabbed.speed.y = 0;
	checkPointGrabbed.anim.loop = true;
	checkPointGrabbed.anim.speed = 0.15f;

	goalPool.anim.PushBack({ 11, 170, 34, 62 });
	goalPool.anim.PushBack({ 46, 170, 34, 62 });
	goalPool.anim.PushBack({ 81, 170, 34, 62 });
	goalPool.anim.PushBack({ 116, 170, 34, 62 });
	goalPool.anim.PushBack({ 151, 170, 34, 62 });
	goalPool.anim.PushBack({ 186, 170, 34, 62 });
	goalPool.anim.PushBack({ 221, 170, 34, 62 });
	goalPool.speed.x = 0;
	goalPool.speed.y = 0;
	goalPool.anim.loop = true;
	goalPool.anim.speed = 0.15f;

	firework1.anim.PushBack({ 350, 17, 40, 35 });
	firework1.anim.PushBack({ 351, 48, 39, 30 });
	firework1.anim.PushBack({ 354, 70, 32, 35 });
	firework1.anim.PushBack({ 380, 70, 40, 35 });
	firework1.anim.PushBack({ 420, 70, 40, 35 });
	firework1.anim.PushBack({ 420, 70, 40, 35 });
	firework1.speed.x = 0;
	firework1.speed.y = 0;
	firework1.anim.loop = false;
	firework1.anim.speed = 0.15f;

	firework2.anim.PushBack({ 350, 17, 40, 35 });
	firework2.anim.PushBack({ 351, 48, 39, 30 });
	firework2.anim.PushBack({ 354, 104, 32, 35 });
	firework2.anim.PushBack({ 380, 104, 40, 35 });
	firework2.anim.PushBack({ 420, 104, 40, 35 });
	firework2.anim.PushBack({ 460, 104, 40, 35 });
	firework2.speed.x = 0;
	firework2.speed.y = 0;
	firework2.anim.loop = false;
	firework2.anim.speed = 0.15f;

	firework3.anim.PushBack({ 350, 17, 40, 35 });
	firework3.anim.PushBack({ 351, 48, 39, 30 });
	firework3.anim.PushBack({ 354, 138, 32, 35 });
	firework3.anim.PushBack({ 380, 138, 40, 35 });
	firework3.anim.PushBack({ 420, 138, 40, 35 });
	firework3.anim.PushBack({ 460, 138, 40, 35 });
	firework3.speed.x = 0;
	firework3.speed.y = 0;
	firework3.anim.loop = false;
	firework3.anim.speed = 0.15f;

	enemyAttack.anim.PushBack({ 350, 17, 40, 35 });
	enemyAttack.anim.PushBack({ 351, 48, 39, 30 });
	enemyAttack.anim.PushBack({ 354, 138, 32, 35 });
	enemyAttack.anim.PushBack({ 380, 138, 40, 35 });
	enemyAttack.anim.PushBack({ 420, 138, 40, 35 });
	enemyAttack.anim.PushBack({ 460, 138, 40, 35 });
	enemyAttack.speed.x = 0;
	enemyAttack.speed.y = 0;
	enemyAttack.anim.loop = true;
	enemyAttack.anim.speed = 0.15f;
	enemyAttack.lifetime = 15;

	RangedAttack.anim.PushBack({ 350, 17, 40, 35 });
	RangedAttack.anim.PushBack({ 351, 48, 39, 30 });
	RangedAttack.anim.PushBack({ 354, 138, 32, 35 });
	RangedAttack.anim.PushBack({ 380, 138, 40, 35 });
	RangedAttack.anim.PushBack({ 420, 138, 40, 35 });
	RangedAttack.anim.PushBack({ 460, 138, 40, 35 });
	RangedAttack.speed.x = 2;
	RangedAttack.speed.y = 0;
	RangedAttack.anim.loop = true;
	RangedAttack.anim.speed = 0.15f;
	RangedAttack.lifetime = 200;

	playerAttack.anim.PushBack({ 350, 17, 40, 35 });
	playerAttack.anim.PushBack({ 351, 48, 39, 30 });
	playerAttack.anim.PushBack({ 354, 138, 32, 35 });
	playerAttack.anim.PushBack({ 380, 138, 40, 35 });
	playerAttack.anim.PushBack({ 420, 138, 40, 35 });
	playerAttack.anim.PushBack({ 460, 138, 40, 35 });
	playerAttack.speed.x = 0;
	playerAttack.speed.y = 0;
	playerAttack.anim.loop = true;
	playerAttack.anim.speed = 0.15f;
	playerAttack.lifetime = 15;

	playerRangedAttack.anim.PushBack({ 350, 17, 40, 35 });
	playerRangedAttack.anim.PushBack({ 351, 48, 39, 30 });
	playerRangedAttack.anim.PushBack({ 354, 138, 32, 35 });
	playerRangedAttack.anim.PushBack({ 380, 138, 40, 35 });
	playerRangedAttack.anim.PushBack({ 420, 138, 40, 35 });
	playerRangedAttack.anim.PushBack({ 460, 138, 40, 35 });
	playerRangedAttack.speed.x = 2;
	playerRangedAttack.speed.y = 0;
	playerRangedAttack.anim.loop = true;
	playerRangedAttack.anim.speed = 0.15f;
	playerRangedAttack.lifetime = 100;

	RadioActive.anim.PushBack({ 157, 125, 53, 27 });
	RadioActive.anim.PushBack({ 175, 233, 53, 27 });
	RadioActive.anim.PushBack({ 230, 233, 53, 27 });
	RadioActive.speed.x = 0;
	RadioActive.speed.y = 0;
	RadioActive.anim.loop = true;
	RadioActive.anim.speed = 0.15f;
	RadioActive.lifetime = 3600;


	PlayerPickUpRadius.anim.PushBack({ 350, 17, 40, 35 });
	PlayerPickUpRadius.anim.PushBack({ 351, 48, 39, 30 });
	PlayerPickUpRadius.anim.PushBack({ 354, 138, 32, 35 });
	PlayerPickUpRadius.anim.PushBack({ 380, 138, 40, 35 });
	PlayerPickUpRadius.anim.PushBack({ 420, 138, 40, 35 });
	PlayerPickUpRadius.anim.PushBack({ 460, 138, 40, 35 });
	PlayerPickUpRadius.speed.x = 0;
	PlayerPickUpRadius.speed.y = 0;
	PlayerPickUpRadius.anim.loop = true;
	PlayerPickUpRadius.anim.speed = 0.15f;
	PlayerPickUpRadius.lifetime = 5;

	ItemFood.anim.PushBack({ 236, 53, 31, 28 });   //({ 236, 92, 31, 28 }); 
	ItemFood.anim.loop = true;
	ItemFood.anim.speed = 0.15f;

	ItemCard.anim.PushBack({ 171, 98, 22, 15 });
	ItemCard.anim.loop = true;
	ItemCard.anim.speed = 0.15f;

	ItemDefaultGun.anim.PushBack({ 11, 57, 53, 22 });  //({ 16, 165, 34, 24 })
	ItemDefaultGun.anim.loop = true;
	ItemDefaultGun.anim.speed = 0.15f;

	ItemGrenade.anim.PushBack({ 101, 60, 18, 18 });
	ItemGrenade.anim.loop = true;
	ItemGrenade.anim.speed = 0.15f;

	ItemHealthPack.anim.PushBack({ 128, 55, 34, 27 });
	ItemHealthPack.anim.loop = true;
	ItemHealthPack.anim.speed = 0.15f;

	ItemLongRangeGun.anim.PushBack({ 63, 93, 58, 24 });  //({ 115, 164, 28, 25 })
	ItemLongRangeGun.anim.loop = true;
	ItemLongRangeGun.anim.speed = 0.15f;


	ItemRadio.anim.PushBack({ 128, 92, 33, 24 });
	ItemRadio.anim.loop = true;
	ItemRadio.anim.speed = 0.15f;

	
	ItemShortRangeGun.anim.PushBack({ 16, 95, 41, 19 });
	ItemShortRangeGun.anim.loop = true;
	ItemShortRangeGun.anim.speed = 0.15f;


	ItemKnife.anim.PushBack({ 200, 59, 30, 21 });
	ItemKnife.anim.loop = true;
	ItemKnife.anim.speed = 0.15f;

	ItemSuit.anim.PushBack({ 18, 122, 27, 30 });
	ItemSuit.anim.loop = true;
	ItemSuit.anim.speed = 0.15f;

	GrenadeDamage.anim.PushBack({ 350, 17, 150, 200 });
	GrenadeDamage.anim.loop = true;
	GrenadeDamage.anim.speed = 0.15f;
	GrenadeDamage.lifetime = 5;

	//ItemGun.anim.PushBack({ 118, 130, 25, 17 });
	//ItemGun.anim.loop = true;
	//ItemGun.anim.speed = 0.15f;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	/*texture = app->tex->Load("Assets/textures/particles.png");*/
	texture_items = app->tex->Load("Assets/textures/SceneObjects/Final_items.png");
	

	return true;
}

bool ModuleParticles::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			particles[i]->pendingToDelete = true;
			particles[i]->collider->pendingToDelete = true;

			if ((c2->type == Collider::Type::PLAYER_PICKUP_RADIUS) && (c1->type == Collider::Type::ITEM_FOOD))
			{
				app->inventoryMenu->AddItemToInventory(ItemType::OBJECT_FOOD, true, false);
				app->audio->PlayFx(app->player->itemGrab);
				break;
			}
			if ((c2->type == Collider::Type::PLAYER_PICKUP_RADIUS) && (c1->type == Collider::Type::ITEM_HEALTH_PACK))
			{
				app->inventoryMenu->AddItemToInventory(ItemType::OBJECT_HEALTH_PACK, true, false);
				app->audio->PlayFx(app->player->itemGrab);
				break;
			}

			if ((c2->type == Collider::Type::PLAYER_PICKUP_RADIUS) && (c1->type == Collider::Type::ITEM_RADIO))
			{
				app->inventoryMenu->AddItemToInventory(ItemType::OBJECT_RADIO, true, false);
				app->audio->PlayFx(app->player->itemGrab);
				break;
			}

			if ((c2->type == Collider::Type::PLAYER_PICKUP_RADIUS) && (c1->type == Collider::Type::ITEM_CARD))
			{
				app->inventoryMenu->AddItemToInventory(ItemType::OBJECT_CARD, true, false);
				app->audio->PlayFx(app->player->itemGrab);
				app->questManager->SwitchMainQuest(LOOK_FOR_THE_COMPUTER_2);
				break;
			}

			if ((c2->type == Collider::Type::PLAYER_PICKUP_RADIUS) && (c1->type == Collider::Type::ITEM_GRENADE))
			{
				app->inventoryMenu->AddItemToInventory(ItemType::OBJECT_GRENADE, true, false);
				app->audio->PlayFx(app->player->itemGrab);
				break;
			}

			if ((c2->type == Collider::Type::PLAYER_PICKUP_RADIUS) && (c1->type == Collider::Type::ITEM_DEFAULT_GUN))
			{
				app->inventoryMenu->AddItemToInventory(ItemType::OBJECT_DEFAULT_GUN, false, true);
				app->audio->PlayFx(app->player->itemGrab);
				break;
			}

			if ((c2->type == Collider::Type::PLAYER_PICKUP_RADIUS) && (c1->type == Collider::Type::ITEM_KNIFE))
			{
				app->inventoryMenu->AddItemToInventory(ItemType::OBJECT_KNIFE, false, true);
				app->audio->PlayFx(app->player->itemGrab);
				break;
			}

			if ((c2->type == Collider::Type::PLAYER_PICKUP_RADIUS) && (c1->type == Collider::Type::ITEM_SUIT))
			{
				app->inventoryMenu->AddItemToInventory(ItemType::OBJECT_SUIT, false, true);
				app->audio->PlayFx(app->player->itemGrab);
				break;
			}

			if ((c2->type == Collider::Type::PLAYER_PICKUP_RADIUS) && (c1->type == Collider::Type::ITEM_LONG_RANGE_GUN))
			{
				app->inventoryMenu->AddItemToInventory(ItemType::OBJECT_lONG_SCOPE_GUN, false, true);
				app->audio->PlayFx(app->player->itemGrab);
				break;
			}

			if ((c2->type == Collider::Type::PLAYER_PICKUP_RADIUS) && (c1->type == Collider::Type::ITEM_SHORT_RANGE_GUN))
			{
				app->inventoryMenu->AddItemToInventory(ItemType::OBJECT_SHORT_SCOPE_GUN, false, true);
				app->audio->PlayFx(app->player->itemGrab);
				break;
			}

			break;
		}

			
		
	}
	
}

bool ModuleParticles::Update(float dt)
{
	if (app->player->pauseMenu == false)
	{
		for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		{
			Particle* particle = particles[i];

			if (particle == nullptr)	continue;

			// Call particle Update. If it has reached its lifetime, destroy it
			if (particle->Update() == false)
			{
				if (particles[i]->collider->type == Collider::Type::ACTIVE_RADIO)
				{
					app->inventoryMenu->ActiveRadioAlive = false;
					app->audio->playMusicSpatially = false;

					if (app->sceneBase->sceneBase == true) app->audio->ChangeMusic(BASE, 0.0f, 0.0f);
					if (app->sceneMotel->sceneMotel == true) app->audio->ChangeMusic(MOTEL_ZONE, 0.0f, 0.0f);
					if (app->sceneCave->sceneCave == true) app->audio->ChangeMusic(CAVE, 0.0f, 0.0f);
					if (app->scenePlatform->scenePlatform == true) app->audio->ChangeMusic(MAIN_MAP_SUNRISE, 0.0f, 0.0f);
					if (app->sceneMainMap->sceneMainMap == true)
					{
						if (app->questManager->mainQuestID == FIND_THE_DOCTOR_1) app->audio->ChangeMusic(MAIN_MAP, 0.0f, 0.0f);
						if (app->questManager->mainQuestID == LOOK_FOR_THE_COMPUTER_2 && app->questManager->secondaryQuestID != ACTIVATE_SWITCHES) app->audio->ChangeMusic(MAIN_MAP_AT_NIGHT, 0.0f, 0.0f);
						if (app->questManager->mainQuestID == LOOK_FOR_THE_COMPUTER_2 && app->questManager->secondaryQuestID == ACTIVATE_SWITCHES) app->audio->ChangeMusic(TENSION_PUZZLE_1, 0.0f, 0.0f);
						if (app->questManager->mainQuestID == KILL_THE_PATIENT_ZERO_3) app->audio->ChangeMusic(MAIN_MAP_SUNRISE, 0.0f, 0.0f);
					}
				}
				particles[i]->SetToDelete();
			}
			//For the radio usage
			if (particles[i]->collider->type == Collider::Type::ACTIVE_RADIO && particles[i]->collider->pendingToDelete == false)
			{
					app->inventoryMenu->ActiveRadioPosition = particle->position;
					app->inventoryMenu->ActiveRadioAlive = true;
			}
		}
		return true;
	}
	if (app->player->pauseMenu == true)
	{
		return true;
	}
	
}

bool ModuleParticles::PostUpdate()
{
	//Movido la parte del draw() al Map.cpp para el nuevo sistema de dibujado (sprite sorting)
	

	if(app->sceneCave->sceneCave == true) app->render->DrawTexture(app->sceneCave->spotLight, app->player->position.x - 960 + 25, app->player->position.y - 540 - 25, NULL);

	if (app->sceneBase->sceneBase == true && app->player->usingComputer == false) app->render->DrawTexture(app->sceneBase->spotLight, app->player->position.x - 960 + 25, app->player->position.y - 540 - 25, NULL);

	if (app->sceneMainMap->sceneMainMap == true && app->questManager->mainQuestID == LOOK_FOR_THE_COMPUTER_2) app->render->DrawTexture(app->sceneMainMap->spotLight, app->player->position.x - 1056 + 30, app->player->position.y - 594 - 30, NULL);
	if (app->sceneMainMap->sceneMainMap == true && app->questManager->mainQuestID == KILL_THE_PATIENT_ZERO_3) app->render->DrawTexture(app->sceneMainMap->sunrise_effect, app->player->position.x - 960, app->player->position.y - 540, NULL);
	if (app->scenePlatform->scenePlatform == true && app->questManager->mainQuestID == KILL_THE_PATIENT_ZERO_3) app->render->DrawTexture(app->scenePlatform->sunrise_effect, app->player->position.x - 960, app->player->position.y - 540, NULL);

	return true;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	Particle* newParticle = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			newParticle = new Particle(particle);
			newParticle->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newParticle->position.y = y;
			//LOG("Added particle");
			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				newParticle->collider = app->collisions->AddCollider(newParticle->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = newParticle;
			break;
		}
	}

	return newParticle;
}