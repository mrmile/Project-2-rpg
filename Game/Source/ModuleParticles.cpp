#include "ModuleParticles.h"

#include "App.h"

#include "Textures.h"
#include "Render.h"
#include "ModuleCollisions.h"
#include "SceneMainMap.h"
#include "ModulePlayer.h"
#include "TitleScreen.h"
#include "SceneCave.h"
#include "SceneMainMap.h"
#include "SceneBase.h"
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
	RangedAttack.lifetime = 100;

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

	RadioActive.anim.PushBack({ 350, 17, 40, 35 });
	RadioActive.anim.PushBack({ 351, 48, 39, 30 });
	RadioActive.anim.PushBack({ 354, 138, 32, 35 });
	RadioActive.anim.PushBack({ 380, 138, 40, 35 });
	RadioActive.anim.PushBack({ 420, 138, 40, 35 });
	RadioActive.anim.PushBack({ 460, 138, 40, 35 });
	RadioActive.speed.x = 0;
	RadioActive.speed.y = 0;
	RadioActive.anim.loop = true;
	RadioActive.anim.speed = 0.15f;
	RadioActive.lifetime = 240;


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

	ItemFood.anim.PushBack({ 350, 17, 40, 35 });
	ItemFood.speed.x = 0;
	ItemFood.speed.y = 0;
	ItemFood.anim.loop = true;
	ItemFood.anim.speed = 0.15f;

	ItemCard.anim.PushBack({ 350, 17, 40, 35 });
	ItemCard.speed.x = 0;
	ItemCard.speed.y = 0;
	ItemCard.anim.loop = true;
	ItemCard.anim.speed = 0.15f;

	ItemDefaultGun.anim.PushBack({ 350, 17, 40, 35 });
	ItemDefaultGun.speed.x = 0;
	ItemDefaultGun.speed.y = 0;
	ItemDefaultGun.anim.loop = true;
	ItemDefaultGun.anim.speed = 0.15f;

	ItemGrenade.anim.PushBack({ 350, 17, 40, 35 });
	ItemGrenade.speed.x = 0;
	ItemGrenade.speed.y = 0;
	ItemGrenade.anim.loop = true;
	ItemGrenade.anim.speed = 0.15f;

	ItemHealthPack.anim.PushBack({ 350, 17, 40, 35 });
	ItemHealthPack.speed.x = 0;
	ItemHealthPack.speed.y = 0;
	ItemHealthPack.anim.loop = true;
	ItemHealthPack.anim.speed = 0.15f;

	ItemLongRangeGun.anim.PushBack({ 350, 17, 40, 35 });
	ItemLongRangeGun.speed.x = 0;
	ItemLongRangeGun.speed.y = 0;
	ItemLongRangeGun.anim.loop = true;
	ItemLongRangeGun.anim.speed = 0.15f;

	ItemRadio.anim.PushBack({ 350, 17, 40, 35 });
	ItemRadio.speed.x = 0;
	ItemRadio.speed.y = 0;
	ItemRadio.anim.loop = true;
	ItemRadio.anim.speed = 0.15f;

	ItemShortRangeGun.anim.PushBack({ 350, 17, 40, 35 });
	ItemShortRangeGun.speed.x = 0;
	ItemShortRangeGun.speed.y = 0;
	ItemShortRangeGun.anim.loop = true;
	ItemShortRangeGun.anim.speed = 0.15f;

	ItemKnife.anim.PushBack({ 350, 17, 40, 35 });
	ItemKnife.speed.x = 0;
	ItemKnife.speed.y = 0;
	ItemKnife.anim.loop = true;
	ItemKnife.anim.speed = 0.15f;

	ItemSuit.anim.PushBack({ 350, 17, 40, 35 });
	ItemSuit.speed.x = 0;
	ItemSuit.speed.y = 0;
	ItemSuit.anim.loop = true;
	ItemSuit.anim.speed = 0.15f;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = app->tex->Load("Assets/textures/particles.png");

	

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
				app->inventoryMenu->AddItemToInventory(ItemType::OBJECT_GRENADE, false, true);
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
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			app->render->DrawTexture(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	if (app->titleScreen->toTitleScreen == true) // <-- No tendría que estar aquí pero es mas simple ponerlo aquí por como está ordenado el render draw
	{
		app->render->DrawTexture2(app->player->gameOverScreen, 0, 0, NULL, 0.0f);
	}

	if(app->sceneCave->sceneCave == true) app->render->DrawTexture(app->sceneCave->spotLight, app->player->position.x - 960 + 25, app->player->position.y - 540 - 25, NULL);

	if (app->sceneBase->sceneBase == true && app->player->usingComputer == false) app->render->DrawTexture(app->sceneBase->spotLight, app->player->position.x - 960 + 25, app->player->position.y - 540 - 25, NULL);

	if (app->sceneMainMap->sceneMainMap == true && app->questManager->mainQuestID == LOOK_FOR_THE_COMPUTER_2) app->render->DrawTexture(app->sceneMainMap->spotLight, app->player->position.x - 1056 + 30, app->player->position.y - 594 - 30, NULL);
	if (app->sceneMainMap->sceneMainMap == true && app->questManager->mainQuestID == KILL_THE_PATIENT_ZERO_3) app->render->DrawTexture(app->sceneMainMap->sunrise_effect, app->player->position.x - 960, app->player->position.y - 540, NULL);

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