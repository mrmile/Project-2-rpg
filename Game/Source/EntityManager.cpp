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

//#include "Object_Food.h"
//#include "Object_HealthPack.h"
//#include "Object_DefaultGun.h"
//#include "Object_LongScopeGun.h"
//#include "Object_ShortScopeGun.h"
//#include "Object_Radio.h"
//#include "Object_Card.h"

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
	texture_enemies_base_zombie = app->tex->Load("Assets/textures/Enemies/Zombies/zombie__with_spawn_2.0_TEST.png");
	texture_enemies_runner_zombie = app->tex->Load("Assets/textures/Enemies/zombie__with_spawn.png");
	texture_enemies_spitter_zombie = app->tex->Load("Assets/textures/Enemies/zombie__with_spawn.png");
	texture_npcs = app->tex->Load("Assets/textures/NPCs/Worker/Worker/stand.png");
	
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
		if (entities[i] != nullptr)
			entities[i]->Update(dt);
	}

	//HandleEntitiesDespawn();


	return true;
}

bool EntityManager::PostUpdate()
{
	for (uint i = 0; i < MAX_ENTITIES; ++i)
	{
		if (entities[i] != nullptr)
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
	/*
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
	*/
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
			case EntityType::NPC:
				entities[i] = new Npcs(info.x, info.y);
				HelperQueue[i].type = EntityType::NPC;
				entities[i]->id = i;
				entities[i]->type = info.type;
				//entities[i]->texture = texture_npcs;
				break;
			case EntityType::NPC2:
				entities[i] = new Npcs2(info.x, info.y);
				HelperQueue[i].type = EntityType::NPC2;
				entities[i]->id = i;
				entities[i]->type = info.type;
				//entities[i]->texture = texture_npcs;
				break;
			case EntityType::NPC3:
				entities[i] = new Npcs3(info.x, info.y);
				HelperQueue[i].type = EntityType::NPC3;
				entities[i]->id = i;
				entities[i]->type = info.type;
				//entities[i]->texture = texture_npcs;
				break;
			case EntityType::NPC4:
				entities[i] = new Npcs4(info.x, info.y);
				HelperQueue[i].type = EntityType::NPC4;
				entities[i]->id = i;
				entities[i]->type = info.type;
				//entities[i]->texture = texture_npcs;
				break;
			//case EntityType::OBJECT_FOOD:
			//	//entities[i]->texture = texture_objects;
			//	entities[i] = new Object_Food(info.x, info.y);
			//	HelperQueue[i].type = EntityType::OBJECT_FOOD;
			//	break;
			//case EntityType::OBJECT_HEALTH_PACK:
			//	//entities[i]->texture = texture_objects;
			//	entities[i] = new Object_HealthPack(info.x, info.y);
			//	HelperQueue[i].type = EntityType::OBJECT_HEALTH_PACK;
			//	break;

			//case EntityType::OBJECT_DEFAULT_GUN:
			//	entities[i] = new Object_DefaultGun(info.x, info.y);
			//	HelperQueue[i].type = EntityType::OBJECT_DEFAULT_GUN;
			//	entities[i]->id = i;
			//	entities[i]->type = info.type;
			//	//entities[i]->texture =;

			//	break;

			//case EntityType::OBJECT_lONG_SCOPE_GUN:
			//	entities[i] = new Object_LongScopeGun(info.x, info.y);
			//	HelperQueue[i].type = EntityType::OBJECT_lONG_SCOPE_GUN;
			//	entities[i]->id = i;
			//	entities[i]->type = info.type;
			//	//entities[i]->texture =;

			//	break;

			//case EntityType::OBJECT_SHORT_SCOPE_GUN:
			//	entities[i] = new Object_ShortScopeGun(info.x, info.y);
			//	HelperQueue[i].type = EntityType::OBJECT_SHORT_SCOPE_GUN;
			//	entities[i]->id = i;
			//	entities[i]->type = info.type;
			//	//entities[i]->texture =;

			//	break;

			//case EntityType::OBJECT_RADIO:
			//	entities[i] = new Object_Radio(info.x, info.y);
			//	HelperQueue[i].type = EntityType::OBJECT_RADIO;
			//	entities[i]->id = i;
			//	entities[i]->type = info.type;
			//	//entities[i]->texture =;

			//	break;

			//case EntityType::OBJECT_CARD:
			//	entities[i] = new Object_Card(info.x, info.y);
			//	HelperQueue[i].type = EntityType::OBJECT_CARD;
			//	entities[i]->id = i;
			//	entities[i]->type = info.type;
			//	//entities[i]->texture =;

			//	break;

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
	if (entity->type != EntityType::OBJECT_FOOD && entity->type != EntityType::OBJECT_HEALTH_PACK && entity->type != EntityType::NPC && entity->type != EntityType::NPC2 && entity->type != EntityType::NPC3 && entity->type != EntityType::NPC4)
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
					entities[i] = nullptr;
				}
				if (HelperQueue[i].type == EntityType::ZOMBIE_RUNNER)
				{
					entities[i]->SetToDelete();
					entities[i]->Runner_Zombie_List.end->data->body->DestroyFixture(entities[i]->Runner_Zombie_List.end->data->body->GetFixtureList());
					entities[i] = nullptr;
				}
				if (HelperQueue[i].type == EntityType::ZOMBIE_SPITTER)
				{
					entities[i]->SetToDelete();
					entities[i]->Spitter_Zombie_List.end->data->body->DestroyFixture(entities[i]->Spitter_Zombie_List.end->data->body->GetFixtureList());
					entities[i] = nullptr;
				}
				if (HelperQueue[i].type == EntityType::NPC)
				{
					entities[i]->SetToDelete();
					entities[i]->NPC_List.end->data->body->DestroyFixture(entities[i]->NPC_List.end->data->body->GetFixtureList());
					entities[i] = nullptr;
				}
				if (HelperQueue[i].type == EntityType::NPC2)
				{
					entities[i]->SetToDelete();
					entities[i]->NPC2_List.end->data->body->DestroyFixture(entities[i]->NPC2_List.end->data->body->GetFixtureList());
					entities[i] = nullptr;
				}
				if (HelperQueue[i].type == EntityType::NPC3)
				{
					entities[i]->SetToDelete();
					entities[i]->NPC3_List.end->data->body->DestroyFixture(entities[i]->NPC3_List.end->data->body->GetFixtureList());
					entities[i] = nullptr;
				}
				if (HelperQueue[i].type == EntityType::NPC4)
				{
					entities[i]->SetToDelete();
					entities[i]->NPC4_List.end->data->body->DestroyFixture(entities[i]->NPC4_List.end->data->body->GetFixtureList());
					entities[i] = nullptr;
				}
				if (HelperQueue[i].type == EntityType::OBJECT_FOOD)
				{
					entities[i]->SetToDelete();
					entities[i] = nullptr;
				}
				if (HelperQueue[i].type == EntityType::OBJECT_HEALTH_PACK)
				{
					entities[i]->SetToDelete();
					entities[i] = nullptr;
				}
				if (HelperQueue[i].type == EntityType::OBJECT_RADIO)
				{
					entities[i]->SetToDelete();
					entities[i] = nullptr;
				}
				if (HelperQueue[i].type == EntityType::OBJECT_CARD)
				{
					entities[i]->SetToDelete();
					entities[i] = nullptr;
				}
				if (HelperQueue[i].type == EntityType::OBJECT_DEFAULT_GUN)
				{
					entities[i]->SetToDelete();
					entities[i] = nullptr;
				}
				if (HelperQueue[i].type == EntityType::OBJECT_lONG_SCOPE_GUN)
				{
					entities[i]->SetToDelete();
					entities[i] = nullptr;
				}
				if (HelperQueue[i].type == EntityType::OBJECT_SHORT_SCOPE_GUN)
				{
					entities[i]->SetToDelete();
					entities[i] = nullptr;
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
				if (HelperQueue[i].type == EntityType::OBJECT_FOOD)
				{
					AddEntity(EntityType::OBJECT_FOOD, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
				if (HelperQueue[i].type == EntityType::OBJECT_HEALTH_PACK)
				{
					AddEntity(EntityType::OBJECT_HEALTH_PACK, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
				if (HelperQueue[i].type == EntityType::OBJECT_RADIO)
				{
					AddEntity(EntityType::OBJECT_RADIO, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
				if (HelperQueue[i].type == EntityType::OBJECT_CARD)
				{
					AddEntity(EntityType::OBJECT_CARD, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
				if (HelperQueue[i].type == EntityType::OBJECT_DEFAULT_GUN)
				{
					AddEntity(EntityType::OBJECT_DEFAULT_GUN, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
				if (HelperQueue[i].type == EntityType::OBJECT_lONG_SCOPE_GUN)
				{
					AddEntity(EntityType::OBJECT_lONG_SCOPE_GUN, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
				}
				if (HelperQueue[i].type == EntityType::OBJECT_SHORT_SCOPE_GUN)
				{
					AddEntity(EntityType::OBJECT_SHORT_SCOPE_GUN, HelperQueue[i].position.x + 10, HelperQueue[i].position.y + 5);
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
