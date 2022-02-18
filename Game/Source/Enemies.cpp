#include "Enemies.h"

#include "App.h"

#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Window.h"
#include "ModuleCollisions.h"
#include "Collider.h"
#include "ModulePhysics.h"

#include "Enemy.h"
#include "Flying_Enemy.h"
#include "Walking_Enemy.h"
#include "Flying_Enemy_2.h"

#define SPAWN_MARGIN 50


Enemies::Enemies(bool startEnabled) : Module(startEnabled) 
{
	name.Create("enemies");
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

Enemies::~Enemies()
{

}

bool Enemies::Start()
{
	texture = app->tex->Load("Assets/textures/enemies.png");
	
	enemyDestroyedFx = app->audio->LoadFx("Assets/audio/fx/Durp.wav");

	return true;
}


bool Enemies::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->pendingToDelete)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool Enemies::Update(float dt)
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Update(dt);
	}

	HandleEnemiesDespawn();

	return true;
}

bool Enemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return true;
}

// Called before quitting
bool Enemies::CleanUp()
{

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (HelperQueue[i] == Enemy_Type::FLYING_KOOPA)  enemies[i]->Flying_Enemy_List.end->data->body->DestroyFixture(enemies[i]->Flying_Enemy_List.end->data->body->GetFixtureList());
			if (HelperQueue[i] == Enemy_Type::SHYGUY)  enemies[i]->Flying_Enemy_2_List.end->data->body->DestroyFixture(enemies[i]->Flying_Enemy_2_List.end->data->body->GetFixtureList());
			if (HelperQueue[i] == Enemy_Type::GOOMBA)  enemies[i]->Walking_Enemy_List.end->data->body->DestroyFixture(enemies[i]->Walking_Enemy_List.end->data->body->GetFixtureList());

			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool Enemies::AddEnemy(Enemy_Type type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type == Enemy_Type::NO_TYPE)
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

void Enemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if ((spawnQueue[i].x * 1 < app->render->camera.x + (app->render->camera.w * 1) + SPAWN_MARGIN) || (spawnQueue[i].x * 1 > app->render->camera.x - (app->render->camera.w * 1) - SPAWN_MARGIN) || (spawnQueue[i].y * 1 < app->render->camera.y - (app->render->camera.h * 1) - SPAWN_MARGIN))
			{
				SpawnEnemy(spawnQueue[i]);
				HelperQueue[i] = spawnQueue[i].type;
				spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
		}
	}
}

void Enemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (enemies[i]->position.y * 1 > (app->render->camera.y + app->win->screenSurface->h * 1) + SPAWN_MARGIN)
			{
				enemies[i]->SetToDelete();
			}

		}
	}
}

void Enemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{

		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
			case Enemy_Type::FLYING_KOOPA:
				enemies[i] = new Flying_Enemy(info.x, info.y);
				HelperQueue[i] = Enemy_Type::FLYING_KOOPA;
				break;
			case Enemy_Type::GOOMBA:
				enemies[i] = new Walking_Enemy(info.x, info.y);
				HelperQueue[i] = Enemy_Type::GOOMBA;
				break;
			case Enemy_Type::SHYGUY:
				enemies[i] = new Flying_Enemy_2(info.x, info.y);
				HelperQueue[i] = Enemy_Type::SHYGUY;

			}
			enemies[i]->texture = texture;
			enemies[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}

bool Enemies::LoadState(pugi::xml_node& data)
{
	pugi::xml_node enemypos = data.child("position");
	pugi::xml_node enemyAtributes = data.child("atributes");
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			enemies[i]->position.x = enemypos.attribute("x").as_int();
			enemies[i]->position.y = enemypos.attribute("y").as_int();
			enemies[i]->FlyingTimer = enemyAtributes.attribute("timer").as_int();
			enemies[i]->EnemyHP = enemyAtributes.attribute("enemyHp").as_int();

			if (enemies[i] != nullptr)
			{
				enemies[i]->SetToDelete();

				if (HelperQueue[i] == Enemy_Type::GOOMBA)  	enemies[i]->Walking_Enemy_List.end->data->body->DestroyFixture(enemies[i]->Walking_Enemy_List.end->data->body->GetFixtureList());
				if (HelperQueue[i] == Enemy_Type::SHYGUY)  	enemies[i]->Flying_Enemy_2_List.end->data->body->DestroyFixture(enemies[i]->Flying_Enemy_2_List.end->data->body->GetFixtureList());
				if (HelperQueue[i] == Enemy_Type::FLYING_KOOPA)  	enemies[i]->Flying_Enemy_List.end->data->body->DestroyFixture(enemies[i]->Flying_Enemy_List.end->data->body->GetFixtureList());

				enemypos = enemypos.next_sibling();
				enemyAtributes = enemyAtributes.next_sibling();
			}


			if (enemies[i] != nullptr)
			{
				enemies[i]->GetCollider();
				if (HelperQueue[i] == Enemy_Type::GOOMBA)  	AddEnemy(Enemy_Type::GOOMBA, enemies[i]->position.x + 28 / 2, enemies[i]->position.y + 33 / 2);
				if (HelperQueue[i] == Enemy_Type::SHYGUY)  	AddEnemy(Enemy_Type::SHYGUY, enemies[i]->position.x + 28 / 2, enemies[i]->position.y + 33 / 2);
				if (HelperQueue[i] == Enemy_Type::FLYING_KOOPA)		AddEnemy(Enemy_Type::FLYING_KOOPA, enemies[i]->startingKoopaPosition.x , enemies[i]->startingKoopaPosition.y);
				

				enemypos = enemypos.next_sibling();
				enemyAtributes = enemyAtributes.next_sibling();
			}
			
		}
	}

	
		
	

	return true;
}

bool Enemies::SaveState(pugi::xml_node& data) const
{
	//pugi::xml_node enemypos = data.append_child("position");
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			
			pugi::xml_node enemypos = data.append_child("position");
			pugi::xml_node enemyAtributes = data.append_child("atributes");
			enemypos.append_attribute("x") = enemies[i]->position.x;
			enemypos.append_attribute("y") = enemies[i]->position.y;
			enemyAtributes.append_attribute("timer") = enemies[i]->FlyingTimer;
			enemyAtributes.append_attribute("enemyHp") = enemies[i]->EnemyHP;
			enemyAtributes.next_sibling("atributes");
			enemypos.next_sibling("position");
		}
	}
	

	return true;
}

void Enemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision
			break;
		}
	}

}