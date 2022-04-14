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
#include "Zombie_Standart.h"
#include "Zombie_Runner.h"
#include "Zombie_Spitter.h"

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
	texture_enemies = app->tex->Load("Assets/textures/Enemies/zombie_farmer.png"); 
	
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
		if (entities[i] != NULL)
		{
			if (HelperQueue[i] == EntityType::ZOMBIE_STANDART)
			{
				entities[i]->Standart_Zombie_List.end->data->body->DestroyFixture(entities[i]->Standart_Zombie_List.end->data->body->GetFixtureList());
			}
			else if (HelperQueue[i] == EntityType::ZOMBIE_RUNNER)
			{
				entities[i]->Runner_Zombie_List.end->data->body->DestroyFixture(entities[i]->Runner_Zombie_List.end->data->body->GetFixtureList());
			}
			else if (HelperQueue[i] == EntityType::ZOMBIE_SPITTER)
			{
				entities[i]->Spitter_Zombie_List.end->data->body->DestroyFixture(entities[i]->Spitter_Zombie_List.end->data->body->GetFixtureList());
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
			// Spawn a new enemy if the screen has reached a spawn position
			if ((spawnQueue[i].x * 1 < app->render->camera.x + (app->render->camera.w * 1) + SPAWN_MARGIN) || (spawnQueue[i].x * 1 > app->render->camera.x - (app->render->camera.w * 1) - SPAWN_MARGIN) || (spawnQueue[i].y * 1 < app->render->camera.y - (app->render->camera.h * 1) - SPAWN_MARGIN))
			{
				SpawnEntity(spawnQueue[i]);
				HelperQueue[i] = spawnQueue[i].type;
				spawnQueue[i].type = EntityType::NONE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void EntityManager::HandleEntitiesDespawn()
{
	
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
				HelperQueue[i] = EntityType::NPC;
				entities[i]->id = i;
				entities[i]->type = info.type;
				//entities[i]->texture = texture_npc;
				break;
			case EntityType::OBJECTS:
				//entities[i]->texture = texture_objects;
				break;
			case EntityType::ZOMBIE_STANDART:
				entities[i] = new Zombie_Standart(info.x,info.y);
				HelperQueue[i] = EntityType::ZOMBIE_STANDART;
				entities[i]->id = i;
				entities[i]->type = info.type;
				entities[i]->texture = texture_enemies;
				
				break;

			case EntityType::ZOMBIE_SPITTER:
				entities[i] = new Zombie_Spitter(info.x, info.y);
				HelperQueue[i] = EntityType::ZOMBIE_SPITTER;
				entities[i]->id = i;
				entities[i]->type = info.type;
				entities[i]->texture = texture_enemies;

				break;

			case EntityType::ZOMBIE_RUNNER:
				entities[i] = new Zombie_Runner(info.x, info.y);
				HelperQueue[i] = EntityType::ZOMBIE_RUNNER;
				entities[i]->id = i;
				entities[i]->type = info.type;
				entities[i]->texture = texture_enemies;

				break;
			
			}
			
			
			break;
		}
	}
}

void EntityManager::RegisterEntitesInCombat(int id)
{

	if (entities[id]->entityState == GameState::OutOfCombat)
	{

		ListInCombat.add(entities[id]);
		ListInCombat.At(x)->data->entityTurn = TurnState::NONE; x++;
	
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
			entities[i]->position.x = entityPos.attribute("x").as_int();
			entities[i]->position.y = entityPos.attribute("y").as_int();
			//entities[i]->FlyingTimer = enemyAtributes.attribute("timer").as_int();
			entities[i]->EntityHP = entityAtributes.attribute("entityHp").as_int();
			

			if (entities[i] != nullptr && !entityPos.next_sibling().empty())
			{
				

				if (HelperQueue[i] == EntityType::ZOMBIE_STANDART)
				{
					entities[i]->Standart_Zombie_List.end->data->body->DestroyFixture(entities[i]->Standart_Zombie_List.end->data->body->GetFixtureList());
					entities[i]->SetToDelete();
				}
				else if (HelperQueue[i] == EntityType::ZOMBIE_RUNNER)
				{
					entities[i]->Runner_Zombie_List.end->data->body->DestroyFixture(entities[i]->Runner_Zombie_List.end->data->body->GetFixtureList());
					entities[i]->SetToDelete();
				}
				else if (HelperQueue[i] == EntityType::ZOMBIE_SPITTER)
				{
					entities[i]->Spitter_Zombie_List.end->data->body->DestroyFixture(entities[i]->Spitter_Zombie_List.end->data->body->GetFixtureList());
					entities[i]->SetToDelete();
				}
			
				entityPos = entityPos.next_sibling();
				entityAtributes = entityAtributes.next_sibling();

			}
			if (entities[i] != nullptr && !entityPos.next_sibling().empty())
			{

				entities[i]->GetColldier();

				if (HelperQueue[i] == EntityType::ZOMBIE_STANDART)
				{
					AddEntity(EntityType::ZOMBIE_STANDART, entities[i]->position.x, entities[i]->position.y);
				}
				else if (HelperQueue[i] == EntityType::ZOMBIE_RUNNER)
				{
					AddEntity(EntityType::ZOMBIE_RUNNER, entities[i]->position.x, entities[i]->position.y);
				}
				else if (HelperQueue[i] == EntityType::ZOMBIE_SPITTER)
				{
					AddEntity(EntityType::ZOMBIE_SPITTER, entities[i]->position.x, entities[i]->position.y);
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