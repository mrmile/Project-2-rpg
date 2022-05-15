#include "App.h"
#include "EntityManager.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Window.h"
#include "ModuleCollisions.h"
#include "Collider.h"
#include "GameManager.h"
#include "Entity.h"
#include "ModulePlayer.h"

#include "NPCs.h"
#include "NPCs2.h"
#include "NPCs3.h"
#include "NPCs4.h"
#include "Zombie_Standart.h"
#include "Zombie_Runner.h"
#include "Zombie_Spitter.h"
#include "Switch.h"
#include "Switch2.h"
#include "Switch3.h"
#include "Switch4.h"
#include "Switch5.h"
#include "rockOne.h"
#include "rockTwo.h"
#include "fenceOne.h"
#include "fenceTwo.h"

#define SPAWN_MARGIN 500

EntityManager::EntityManager(bool start_enabled) : Module(start_enabled)
{
	name.Create("entities");
	
	for (uint i = 0; i < MAX_ENTITIES; i++)
	{
		entities[i] = nullptr;

	}
	
}
EntityManager::~EntityManager()
{

}

bool EntityManager::Start()
{
	texture_enemies_base_zombie = app->tex->Load("Assets/textures/Enemies/Zombies/zombie_with_spawn.png");
	texture_enemies_runner_zombie = app->tex->Load("Assets/textures/Enemies/Zombies/zombie_runner.png");
	texture_enemies_spitter_zombie = app->tex->Load("Assets/textures/Enemies/Zombies/zombie_spitter_with_spawn.png");
	texture_npcs = app->tex->Load("Assets/textures/NPCs/Implemented/General_NPCs.png");
	texture_switch = app->tex->Load("Assets/textures/SceneObjects/switch.png");
	texture_rockOne = app->tex->Load("Assets/textures/SceneObjects/rock.png");
	texture_rockTwo = app->tex->Load("Assets/textures/SceneObjects/rock.png");
	texture_fenceOne = app->tex->Load("Assets/textures/SceneObjects/fence.png");
	texture_fenceTwo = app->tex->Load("Assets/textures/SceneObjects/fence.png");

	return true;
}

bool EntityManager::PreUpdate()
{
	
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr && entities[i]->pendingToDelete)
		{
			delete entities[i];
			entities[i] = nullptr;
		}
	}
	
	return true;
}
bool EntityManager::Update(float dt)
{
	HandleEntitiesSpawn();

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr && entities[i]->EntityHP > 0)
		{
			entities[i]->Update(dt);
		}

		if (entities[i] != nullptr && entities[i]->EntityHP <= 0)
		{
			if (entities[i]->type == EntityType::ZOMBIE_STANDART)
			{
				entities[i]->SetToDelete();
				entities[i]->Standart_Zombie_List.end->data->body->SetTransform({ 0,0 }, 0.0f);
				entities[i]->Standart_Zombie_List.end->data->body->SetAwake(false);
			}
			if (entities[i]->type == EntityType::ZOMBIE_RUNNER)
			{
				entities[i]->SetToDelete();
				entities[i]->Runner_Zombie_List.end->data->body->SetTransform({ 0,0 }, 0.0f);
				entities[i]->Runner_Zombie_List.end->data->body->SetAwake(false);
			}
			if (entities[i]->type == EntityType::ZOMBIE_SPITTER)
			{
				entities[i]->SetToDelete();
				entities[i]->Spitter_Zombie_List.end->data->body->SetTransform({ 0,0 }, 0.0f);
				entities[i]->Spitter_Zombie_List.end->data->body->SetAwake(false);
			}

			if (entities[i]->type == EntityType::NPC)
			{
				entities[i]->SetToDelete();
				entities[i]->NPC_List.end->data->body->SetTransform({ 0,0 }, 0.0f);
				entities[i]->NPC_List.end->data->body->SetAwake(false);
			}
			if (entities[i]->type == EntityType::NPC2)
			{
				entities[i]->SetToDelete();
				entities[i]->NPC2_List.end->data->body->SetTransform({ 0,0 }, 0.0f);
				entities[i]->NPC2_List.end->data->body->SetAwake(false);
			}
			if (entities[i]->type == EntityType::NPC3)
			{
				entities[i]->SetToDelete();
				entities[i]->NPC3_List.end->data->body->SetTransform({ 0,0 }, 0.0f);
				entities[i]->NPC3_List.end->data->body->SetAwake(false);
			}
			if (entities[i]->type == EntityType::NPC4)
			{
				entities[i]->SetToDelete();
				entities[i]->NPC4_List.end->data->body->SetTransform({ 0,0 }, 0.0f);
				entities[i]->NPC4_List.end->data->body->SetAwake(false);
			}

			if (entities[i]->type == EntityType::SWITCH_KEY)
			{
				entities[i]->SetToDelete();
				entities[i]->Switch_List.end->data->body->SetTransform({ 0,0 }, 0.0f);
				entities[i]->Switch_List.end->data->body->SetAwake(false);
			}
			if (entities[i]->type == EntityType::SWITCH_KEY2)
			{
				entities[i]->SetToDelete();
				entities[i]->Switch_List2.end->data->body->SetTransform({ 0,0 }, 0.0f);
				entities[i]->Switch_List2.end->data->body->SetAwake(false);
			}
			if (entities[i]->type == EntityType::SWITCH_KEY3)
			{
				entities[i]->SetToDelete();
				entities[i]->Switch_List3.end->data->body->SetTransform({ 0,0 }, 0.0f);
				entities[i]->Switch_List3.end->data->body->SetAwake(false);
			}
			if (entities[i]->type == EntityType::SWITCH_KEY4)
			{
				entities[i]->SetToDelete();
				entities[i]->Switch_List4.end->data->body->SetTransform({ 0,0 }, 0.0f);
				entities[i]->Switch_List4.end->data->body->SetAwake(false);
			}
			if (entities[i]->type == EntityType::SWITCH_KEY5)
			{
				entities[i]->SetToDelete();
				entities[i]->Switch_List5.end->data->body->SetTransform({ 0,0 }, 0.0f);
				entities[i]->Switch_List5.end->data->body->SetAwake(false);
			}
			if (entities[i]->type == EntityType::ROCK_ONE)
			{
				entities[i]->SetToDelete();
				entities[i]->RockOne_List.end->data->body->SetTransform({ 0,0 }, 0.0f);
				entities[i]->RockOne_List.end->data->body->SetAwake(false);
			}
			if (entities[i]->type == EntityType::ROCK_TWO)
			{
				entities[i]->SetToDelete();
				entities[i]->RockTwo_List.end->data->body->SetTransform({ 0,0 }, 0.0f);
				entities[i]->RockTwo_List.end->data->body->SetAwake(false);
			}
			if (entities[i]->type == EntityType::FENCE_ONE)
			{
				entities[i]->SetToDelete();
				entities[i]->FenceOne_List.end->data->body->SetTransform({ 0,0 }, 0.0f);
				entities[i]->FenceOne_List.end->data->body->SetAwake(false);
			}
			if (entities[i]->type == EntityType::FENCE_TWO)
			{
				entities[i]->SetToDelete();
				entities[i]->FenceTwo_List.end->data->body->SetTransform({ 0,0 }, 0.0f);
				entities[i]->FenceTwo_List.end->data->body->SetAwake(false);
			}

		}
			
	}

	//HandleEntitiesDespawn();


	return true;
}

bool EntityManager::PostUpdate()
{
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr && entities[i]->EntityHP > 0)
			entities[i]->Draw();
	}

	return true;
}
bool EntityManager::CleanUp()
{
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			if (HelperQueue[i].type == EntityType::ZOMBIE_STANDART)
			{
				entities[i]->Standart_Zombie_List.end->data->body->DestroyFixture(entities[i]->Standart_Zombie_List.end->data->body->GetFixtureList());
			}
			if (HelperQueue[i].type == EntityType::ZOMBIE_RUNNER)
			{
				entities[i]->Runner_Zombie_List.end->data->body->DestroyFixture(entities[i]->Runner_Zombie_List.end->data->body->GetFixtureList());
			}
			if (HelperQueue[i].type == EntityType::ZOMBIE_SPITTER)
			{
				entities[i]->Spitter_Zombie_List.end->data->body->DestroyFixture(entities[i]->Spitter_Zombie_List.end->data->body->GetFixtureList());
			}
			if (HelperQueue[i].type == EntityType::SWITCH_KEY)
			{
				entities[i]->Switch_List.end->data->body->DestroyFixture(entities[i]->Switch_List.end->data->body->GetFixtureList());
			}
			if (HelperQueue[i].type == EntityType::SWITCH_KEY2)
			{
				entities[i]->Switch_List2.end->data->body->DestroyFixture(entities[i]->Switch_List2.end->data->body->GetFixtureList());
			}
			if (HelperQueue[i].type == EntityType::SWITCH_KEY3)
			{
				entities[i]->Switch_List3.end->data->body->DestroyFixture(entities[i]->Switch_List3.end->data->body->GetFixtureList());
			}
			if (HelperQueue[i].type == EntityType::SWITCH_KEY4)
			{
				entities[i]->Switch_List4.end->data->body->DestroyFixture(entities[i]->Switch_List4.end->data->body->GetFixtureList());
			}
			if (HelperQueue[i].type == EntityType::SWITCH_KEY5)
			{
				entities[i]->Switch_List5.end->data->body->DestroyFixture(entities[i]->Switch_List5.end->data->body->GetFixtureList());
			}
			if (HelperQueue[i].type == EntityType::ROCK_ONE)
			{
				entities[i]->RockOne_List.end->data->body->DestroyFixture(entities[i]->RockOne_List.end->data->body->GetFixtureList());
			}
			if (HelperQueue[i].type == EntityType::ROCK_TWO)
			{
				entities[i]->RockTwo_List.end->data->body->DestroyFixture(entities[i]->RockTwo_List.end->data->body->GetFixtureList());
			}
			if (HelperQueue[i].type == EntityType::FENCE_ONE)
			{
				entities[i]->FenceOne_List.end->data->body->DestroyFixture(entities[i]->FenceOne_List.end->data->body->GetFixtureList());
			}
			if (HelperQueue[i].type == EntityType::FENCE_TWO)
			{
				entities[i]->FenceTwo_List.end->data->body->DestroyFixture(entities[i]->FenceTwo_List.end->data->body->GetFixtureList());
			}
			if (HelperQueue[i].type == EntityType::NPC)
			{
				entities[i]->NPC_List.end->data->body->DestroyFixture(entities[i]->NPC_List.end->data->body->GetFixtureList());
			}
			if (HelperQueue[i].type == EntityType::NPC2)
			{
				entities[i]->NPC2_List.end->data->body->DestroyFixture(entities[i]->NPC2_List.end->data->body->GetFixtureList());
			}
			if (HelperQueue[i].type == EntityType::NPC3)
			{
				entities[i]->NPC3_List.end->data->body->DestroyFixture(entities[i]->NPC3_List.end->data->body->GetFixtureList());
			}
			if (HelperQueue[i].type == EntityType::NPC4)
			{
				entities[i]->NPC4_List.end->data->body->DestroyFixture(entities[i]->NPC4_List.end->data->body->GetFixtureList());
			}

			entities[i] = nullptr;
			delete entities[i];
		}
	}

	return true;
}
bool EntityManager::AddEntity(EntityType type,int x,int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (spawnQueue[i].type == EntityType::NONE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
		
			ret = true;
			break;
		}
	}

	return ret;
}

void EntityManager::HandleEntitiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (spawnQueue[i].type != EntityType::NONE)
		{
			SpawnEntity(spawnQueue[i]);
			spawnQueue[i].type = EntityType::NONE;
		}
	}
}

void EntityManager::HandleEntitiesDespawn()
{
	
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			if (entities[i]->EntityHP == 0)
			{
				entities[i]->SetToDelete();
			}
		}
	}
	
}

void EntityManager::SpawnEntity(const EntitySpawnPoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{

		if (entities[i] == nullptr)
		{
			switch (info.type)
			{
			case EntityType::PLAYER:
				//entities[i]->texture = texture_player;
				break;
			case EntityType::SWITCH_KEY:
				entities[i] = new Switch(info.x, info.y);
				HelperQueue[i].type = EntityType::SWITCH_KEY;
				entities[i]->id = i;
				entities[i]->type = info.type;
				entities[i]->texture = texture_switch;
				break;
			case EntityType::SWITCH_KEY2:
				entities[i] = new Switch2(info.x, info.y);
				HelperQueue[i].type = EntityType::SWITCH_KEY2;
				entities[i]->id = i;
				entities[i]->type = info.type;
				entities[i]->texture = texture_switch;
				break;
			case EntityType::SWITCH_KEY3:
				entities[i] = new Switch3(info.x, info.y);
				HelperQueue[i].type = EntityType::SWITCH_KEY3;
				entities[i]->id = i;
				entities[i]->type = info.type;
				entities[i]->texture = texture_switch;
				break;
			case EntityType::SWITCH_KEY4:
				entities[i] = new Switch4(info.x, info.y);
				HelperQueue[i].type = EntityType::SWITCH_KEY4;
				entities[i]->id = i;
				entities[i]->type = info.type;
				entities[i]->texture = texture_switch;
				break;
			case EntityType::SWITCH_KEY5:
				entities[i] = new Switch5(info.x, info.y);
				HelperQueue[i].type = EntityType::SWITCH_KEY5;
				entities[i]->id = i;
				entities[i]->type = info.type;
				entities[i]->texture = texture_switch;
				break;
			case EntityType::ROCK_ONE:
				entities[i] = new RockOne(info.x, info.y);
				HelperQueue[i].type = EntityType::ROCK_ONE;
				entities[i]->id = i;
				entities[i]->type = info.type;
				entities[i]->texture = texture_rockOne;
				break;
			case EntityType::ROCK_TWO:
				entities[i] = new RockTwo(info.x, info.y);
				HelperQueue[i].type = EntityType::ROCK_TWO;
				entities[i]->id = i;
				entities[i]->type = info.type;
				entities[i]->texture = texture_rockTwo;
				break;
			case EntityType::FENCE_ONE:
				entities[i] = new FenceOne(info.x, info.y);
				HelperQueue[i].type = EntityType::FENCE_ONE;
				entities[i]->id = i;
				entities[i]->type = info.type;
				entities[i]->texture = texture_fenceOne;
				break;
			case EntityType::FENCE_TWO:
				entities[i] = new FenceTwo(info.x, info.y);
				HelperQueue[i].type = EntityType::FENCE_TWO;
				entities[i]->id = i;
				entities[i]->type = info.type;
				entities[i]->texture = texture_fenceTwo;
				break;
			case EntityType::NPC:
				entities[i] = new Npcs(info.x, info.y);
				HelperQueue[i].type = EntityType::NPC;
				entities[i]->id = i;
				entities[i]->type = info.type;
				entities[i]->texture = texture_npcs;
				break;
			case EntityType::NPC2:
				entities[i] = new Npcs2(info.x, info.y);
				HelperQueue[i].type = EntityType::NPC2;
				entities[i]->id = i;
				entities[i]->type = info.type;
				entities[i]->texture = texture_npcs;
				break;
			case EntityType::NPC3:
				entities[i] = new Npcs3(info.x, info.y);
				HelperQueue[i].type = EntityType::NPC3;
				entities[i]->id = i;
				entities[i]->type = info.type;
				entities[i]->texture = texture_npcs;
				break;
			case EntityType::NPC4:
				entities[i] = new Npcs4(info.x, info.y);
				HelperQueue[i].type = EntityType::NPC4;
				entities[i]->id = i;
				entities[i]->type = info.type;
				entities[i]->texture = texture_npcs;
				break;
			case EntityType::ZOMBIE_STANDART:
				entities[i] = new Zombie_Standart(info.x,info.y);
				HelperQueue[i].type = EntityType::ZOMBIE_STANDART;
				entities[i]->id = i;
				entities[i]->type = info.type;
				entities[i]->texture = texture_enemies_base_zombie;
				
				break;

			case EntityType::ZOMBIE_SPITTER:
				entities[i] = new Zombie_Spitter(info.x, info.y);
				HelperQueue[i].type = EntityType::ZOMBIE_SPITTER;
				entities[i]->id = i;
				entities[i]->type = info.type;
				entities[i]->texture = texture_enemies_spitter_zombie;

				break;

			case EntityType::ZOMBIE_RUNNER:
				entities[i] = new Zombie_Runner(info.x, info.y);
				HelperQueue[i].type = EntityType::ZOMBIE_RUNNER;
				entities[i]->id = i;
				entities[i]->type = info.type;
				entities[i]->texture = texture_enemies_runner_zombie;

				break;
			}
			
			
			break;
		}
	}
}


void EntityManager::RegisterEntitesInCombat(Entity* entity)
{
	if (entity->type != EntityType::NPC && entity->type != EntityType::NPC2 && entity->type != EntityType::NPC3 && entity->type != EntityType::NPC4 && entity->type != EntityType::SWITCH_KEY && entity->type != EntityType::SWITCH_KEY2 && entity->type != EntityType::SWITCH_KEY3 && entity->type != EntityType::SWITCH_KEY4 && entity->type != EntityType::SWITCH_KEY5 && entity->type != EntityType::ROCK_ONE && entity->type != EntityType::ROCK_TWO && entity->type != EntityType::FENCE_ONE && entity->type != EntityType::FENCE_TWO)
	{
		if (entity->entityState == GameState::OutOfCombat)
		{

			ListInCombat.add(entity);
			ListInCombat.At(x)->data->entityTurn = TurnState::StartOfTurn;
			x++;

			app->player->entityStatePlayer = GameState::InCombat;
			app->player->entityTurnPlayer = TurnState::NONE;

		}
	}

}

void EntityManager::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr && entities[i]->GetColldier() == c1)
		{
			entities[i]->OnCollision(c2); //Notify the entity of a collision
			break;
		}
	}

}

bool EntityManager::LoadState(pugi::xml_node& data)
{
	pugi::xml_node entityPos = data.child("position");
	pugi::xml_node entityAtributes = data.child("atributes");

	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{
			HelperQueue[i].position.x = entityPos.attribute("x").as_int();
			HelperQueue[i].position.y = entityPos.attribute("y").as_int();
			//entities[i]->FlyingTimer = enemyAtributes.attribute("timer").as_int();
			HelperQueue[i].hp = entityAtributes.attribute("entityHp").as_int();

			if (entities[i] != nullptr)
			{
				if (HelperQueue[i].type == EntityType::ZOMBIE_STANDART)
				{
					entities[i]->SetToDelete();
					entities[i]->Standart_Zombie_List.end->data->body->DestroyFixture(entities[i]->Standart_Zombie_List.end->data->body->GetFixtureList());
					/*entities[i] = nullptr;*/
				}
				if (HelperQueue[i].type == EntityType::ZOMBIE_RUNNER)
				{
					entities[i]->SetToDelete();
					entities[i]->Runner_Zombie_List.end->data->body->DestroyFixture(entities[i]->Runner_Zombie_List.end->data->body->GetFixtureList());
					/*entities[i] = nullptr;*/
				}
				if (HelperQueue[i].type == EntityType::ZOMBIE_SPITTER)
				{
					entities[i]->SetToDelete();
					entities[i]->Spitter_Zombie_List.end->data->body->DestroyFixture(entities[i]->Spitter_Zombie_List.end->data->body->GetFixtureList());
					/*entities[i] = nullptr;*/
				}
				if (HelperQueue[i].type == EntityType::SWITCH_KEY)
				{
					entities[i]->SetToDelete();
					entities[i]->Switch_List.end->data->body->DestroyFixture(entities[i]->Switch_List.end->data->body->GetFixtureList());
					/*entities[i] = nullptr;*/
				}
				if (HelperQueue[i].type == EntityType::SWITCH_KEY2)
				{
					entities[i]->SetToDelete();
					entities[i]->Switch_List2.end->data->body->DestroyFixture(entities[i]->Switch_List2.end->data->body->GetFixtureList());
					/*entities[i] = nullptr;*/
				}
				if (HelperQueue[i].type == EntityType::SWITCH_KEY3)
				{
					entities[i]->SetToDelete();
					entities[i]->Switch_List3.end->data->body->DestroyFixture(entities[i]->Switch_List3.end->data->body->GetFixtureList());
					/*entities[i] = nullptr;*/
				}
				if (HelperQueue[i].type == EntityType::SWITCH_KEY4)
				{
					entities[i]->SetToDelete();
					entities[i]->Switch_List4.end->data->body->DestroyFixture(entities[i]->Switch_List4.end->data->body->GetFixtureList());
					/*entities[i] = nullptr;*/
				}
				if (HelperQueue[i].type == EntityType::SWITCH_KEY5)
				{
					entities[i]->SetToDelete();
					entities[i]->Switch_List5.end->data->body->DestroyFixture(entities[i]->Switch_List5.end->data->body->GetFixtureList());
					/*entities[i] = nullptr;*/
				}
				if (HelperQueue[i].type == EntityType::ROCK_ONE)
				{
					entities[i]->SetToDelete();
					entities[i]->RockOne_List.end->data->body->DestroyFixture(entities[i]->RockOne_List.end->data->body->GetFixtureList());
					/*entities[i] = nullptr;*/
				}
				if (HelperQueue[i].type == EntityType::ROCK_TWO)
				{
					entities[i]->SetToDelete();
					entities[i]->RockTwo_List.end->data->body->DestroyFixture(entities[i]->RockTwo_List.end->data->body->GetFixtureList());
					/*entities[i] = nullptr;*/
				}
				if (HelperQueue[i].type == EntityType::FENCE_ONE)
				{
					entities[i]->SetToDelete();
					entities[i]->FenceOne_List.end->data->body->DestroyFixture(entities[i]->FenceOne_List.end->data->body->GetFixtureList());
					/*entities[i] = nullptr;*/
				}
				if (HelperQueue[i].type == EntityType::FENCE_TWO)
				{
					entities[i]->SetToDelete();
					entities[i]->FenceTwo_List.end->data->body->DestroyFixture(entities[i]->FenceTwo_List.end->data->body->GetFixtureList());
					/*entities[i] = nullptr;*/
				}
				if (HelperQueue[i].type == EntityType::NPC)
				{
					entities[i]->SetToDelete();
					entities[i]->NPC_List.end->data->body->DestroyFixture(entities[i]->NPC_List.end->data->body->GetFixtureList());
					/*entities[i] = nullptr;*/
				}
				if (HelperQueue[i].type == EntityType::NPC2)
				{
					entities[i]->SetToDelete();
					entities[i]->NPC2_List.end->data->body->DestroyFixture(entities[i]->NPC2_List.end->data->body->GetFixtureList());
					/*entities[i] = nullptr;*/
				}
				if (HelperQueue[i].type == EntityType::NPC3)
				{
					entities[i]->SetToDelete();
					entities[i]->NPC3_List.end->data->body->DestroyFixture(entities[i]->NPC3_List.end->data->body->GetFixtureList());
					/*entities[i] = nullptr;*/
				}
				if (HelperQueue[i].type == EntityType::NPC4)
				{
					entities[i]->SetToDelete();
					entities[i]->NPC4_List.end->data->body->DestroyFixture(entities[i]->NPC4_List.end->data->body->GetFixtureList());
					/*entities[i] = nullptr;*/
				}

				entityPos = entityPos.next_sibling();
				entityAtributes = entityAtributes.next_sibling();
			}
					
			if (HelperQueue[i].type != EntityType::NONE)
			{
				//entities[i]->GetColldier();

				if (HelperQueue[i].type == EntityType::ZOMBIE_STANDART)
				{
					AddEntity(EntityType::ZOMBIE_STANDART, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
				if (HelperQueue[i].type == EntityType::ZOMBIE_RUNNER)
				{
					AddEntity(EntityType::ZOMBIE_RUNNER, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
				if (HelperQueue[i].type == EntityType::ZOMBIE_SPITTER)
				{
					AddEntity(EntityType::ZOMBIE_SPITTER, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
				if (HelperQueue[i].type == EntityType::SWITCH_KEY)
				{
					AddEntity(EntityType::SWITCH_KEY, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
				if (HelperQueue[i].type == EntityType::SWITCH_KEY2)
				{
					AddEntity(EntityType::SWITCH_KEY2, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
				if (HelperQueue[i].type == EntityType::SWITCH_KEY3)
				{
					AddEntity(EntityType::SWITCH_KEY3, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
				if (HelperQueue[i].type == EntityType::SWITCH_KEY4)
				{
					AddEntity(EntityType::SWITCH_KEY4, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
				if (HelperQueue[i].type == EntityType::SWITCH_KEY5)
				{
					AddEntity(EntityType::SWITCH_KEY5, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
				if (HelperQueue[i].type == EntityType::ROCK_ONE)
				{
					AddEntity(EntityType::ROCK_ONE, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
				if (HelperQueue[i].type == EntityType::ROCK_TWO)
				{
					AddEntity(EntityType::ROCK_TWO, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
				if (HelperQueue[i].type == EntityType::FENCE_ONE)
				{
					AddEntity(EntityType::FENCE_ONE, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
				if (HelperQueue[i].type == EntityType::FENCE_TWO)
				{
					AddEntity(EntityType::FENCE_TWO, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
				if (HelperQueue[i].type == EntityType::NPC)
				{
					AddEntity(EntityType::NPC, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
				if (HelperQueue[i].type == EntityType::NPC2)
				{
					AddEntity(EntityType::NPC2, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
				if (HelperQueue[i].type == EntityType::NPC3)
				{
					AddEntity(EntityType::NPC3, HelperQueue[i].position.x+10, HelperQueue[i].position.y+5);
				}
				if (HelperQueue[i].type == EntityType::NPC4)
				{
					AddEntity(EntityType::NPC4, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
			
				entityPos = entityPos.next_sibling();
				entityAtributes = entityAtributes.next_sibling();
			}
		}
	}





	return true;
}

bool EntityManager::SaveState(pugi::xml_node& data) const
{
	//pugi::xml_node enemypos = data.append_child("position");
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
		{

			pugi::xml_node entityPos = data.append_child("position");
			pugi::xml_node entityAtributes = data.append_child("atributes");
			entityPos.append_attribute("x") = entities[i]->position.x;
			entityPos.append_attribute("y") = entities[i]->position.y;
			entityAtributes.append_attribute("entityHp") = entities[i]->EntityHP;
			entityAtributes.next_sibling("atributes");
			entityPos.next_sibling("position");
		}
	}


	return true;
}
