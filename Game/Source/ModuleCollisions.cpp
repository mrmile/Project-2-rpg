#include "ModuleCollisions.h"
#include "SceneCastle.h"
#include "SceneForest.h"

#include "app.h"

#include "Render.h"
#include "Input.h"
#include "Log.h"

#include "SDL/include/SDL_Scancode.h"

//ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
ModuleCollisions::ModuleCollisions(bool start_enabled) : Module(start_enabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::LAYER_ZERO][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::B_CB] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::H_CB] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::V_CB] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::LAVA] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::COIN] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::LAYER_ZERO][Collider::Type::GOAL_POINT] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::LAYER_ZERO] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::INSTANT_DEATH] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::B_CB] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::H_CB] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::V_CB] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::LAVA] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::NULL_COLLIDER] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::RECOVER_LIFE_POWER_UP] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::COIN] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::CHECKPOINT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::GOAL_POINT] = true;

	matrix[Collider::Type::ENEMY][Collider::Type::LAYER_ZERO] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::INSTANT_DEATH] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::B_CB] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::H_CB] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::V_CB] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::LAVA] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::COIN] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::GOAL_POINT] = false;

	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::LAYER_ZERO] = true;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::B_CB] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::H_CB] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::V_CB] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::LAVA] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::COIN] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::INSTANT_DEATH][Collider::Type::GOAL_POINT] = false;

	matrix[Collider::Type::B_CB][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::B_CB][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::B_CB][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::B_CB][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::B_CB][Collider::Type::B_CB] = false;
	matrix[Collider::Type::B_CB][Collider::Type::H_CB] = false;
	matrix[Collider::Type::B_CB][Collider::Type::V_CB] = false;
	matrix[Collider::Type::B_CB][Collider::Type::LAVA] = false;
	matrix[Collider::Type::B_CB][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::B_CB][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::B_CB][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::B_CB][Collider::Type::COIN] = false;
	matrix[Collider::Type::B_CB][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::B_CB][Collider::Type::GOAL_POINT] = false;

	matrix[Collider::Type::H_CB][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::H_CB][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::H_CB][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::H_CB][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::H_CB][Collider::Type::B_CB] = false;
	matrix[Collider::Type::H_CB][Collider::Type::H_CB] = false;
	matrix[Collider::Type::H_CB][Collider::Type::V_CB] = false;
	matrix[Collider::Type::H_CB][Collider::Type::LAVA] = false;
	matrix[Collider::Type::H_CB][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::H_CB][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::H_CB][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::H_CB][Collider::Type::COIN] = false;
	matrix[Collider::Type::H_CB][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::H_CB][Collider::Type::GOAL_POINT] = false;

	matrix[Collider::Type::V_CB][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::V_CB][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::V_CB][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::V_CB][Collider::Type::INSTANT_DEATH] = true;
	matrix[Collider::Type::V_CB][Collider::Type::B_CB] = false;
	matrix[Collider::Type::V_CB][Collider::Type::H_CB] = false;
	matrix[Collider::Type::V_CB][Collider::Type::V_CB] = false;
	matrix[Collider::Type::V_CB][Collider::Type::LAVA] = false;
	matrix[Collider::Type::V_CB][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::V_CB][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::V_CB][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::V_CB][Collider::Type::COIN] = false;
	matrix[Collider::Type::V_CB][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::V_CB][Collider::Type::GOAL_POINT] = false;

	matrix[Collider::Type::LAVA][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::LAVA][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::LAVA][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::LAVA][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::LAVA][Collider::Type::B_CB] = false;
	matrix[Collider::Type::LAVA][Collider::Type::H_CB] = false;
	matrix[Collider::Type::LAVA][Collider::Type::V_CB] = false;
	matrix[Collider::Type::LAVA][Collider::Type::LAVA] = false;
	matrix[Collider::Type::LAVA][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::LAVA][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::LAVA][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::LAVA][Collider::Type::COIN] = false;
	matrix[Collider::Type::LAVA][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::LAVA][Collider::Type::GOAL_POINT] = false;

	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::B_CB] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::H_CB] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::V_CB] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::LAVA] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::COIN] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::NULL_COLLIDER][Collider::Type::GOAL_POINT] = false;

	matrix[Collider::Type::PLAYER_FEET][Collider::Type::LAYER_ZERO] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::INSTANT_DEATH] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::B_CB] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::H_CB] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::V_CB] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::LAVA] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::NULL_COLLIDER] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::PLAYER_FEET] = false;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::RECOVER_LIFE_POWER_UP] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::COIN] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::CHECKPOINT] = true;
	matrix[Collider::Type::PLAYER_FEET][Collider::Type::GOAL_POINT] = true;

	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::B_CB] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::H_CB] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::V_CB] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::LAVA] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::COIN] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::RECOVER_LIFE_POWER_UP][Collider::Type::GOAL_POINT] = false;

	matrix[Collider::Type::COIN][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::COIN][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::COIN][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::COIN][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::COIN][Collider::Type::B_CB] = false;
	matrix[Collider::Type::COIN][Collider::Type::H_CB] = false;
	matrix[Collider::Type::COIN][Collider::Type::V_CB] = false;
	matrix[Collider::Type::COIN][Collider::Type::LAVA] = false;
	matrix[Collider::Type::COIN][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::COIN][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::COIN][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::COIN][Collider::Type::COIN] = false;
	matrix[Collider::Type::COIN][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::COIN][Collider::Type::GOAL_POINT] = false;

	matrix[Collider::Type::CHECKPOINT][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::B_CB] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::H_CB] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::V_CB] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::LAVA] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::COIN] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::CHECKPOINT][Collider::Type::GOAL_POINT] = false;

	matrix[Collider::Type::GOAL_POINT][Collider::Type::LAYER_ZERO] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::INSTANT_DEATH] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::B_CB] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::H_CB] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::V_CB] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::LAVA] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::NULL_COLLIDER] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::PLAYER_FEET] = true;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::RECOVER_LIFE_POWER_UP] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::COIN] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::CHECKPOINT] = false;
	matrix[Collider::Type::GOAL_POINT][Collider::Type::GOAL_POINT] = false;

}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

bool ModuleCollisions::Awake()
{
	return true;
}

bool ModuleCollisions::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
			{
				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);

				for (uint i = 0; i < MAX_LISTENERS; ++i)
					if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
			}
		}
	}

	return true;
}

bool ModuleCollisions::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		debug = !debug;

	return true;
}

bool ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return true;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		
		if (app->sceneCastle->godMode == false && app->sceneForest->godMode == false)
		{
			switch (colliders[i]->type)
			{
			case Collider::Type::NONE: // white
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::LAYER_ZERO: // blue
				app->render->DrawRectangle(colliders[i]->rect, 0, 0, 255, alpha);
				break;
			case Collider::Type::PLAYER: // green
				app->render->DrawRectangle(colliders[i]->rect, 0, 255, 0, alpha);
				break;
			case Collider::Type::PLAYER_FEET: //orange
				app->render->DrawRectangle(colliders[i]->rect, 255, 100, 0, alpha);
				break;
			case Collider::Type::ENEMY: // yellow
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 0, alpha);
				break;
			case Collider::Type::INSTANT_DEATH: // red
				app->render->DrawRectangle(colliders[i]->rect, 170, 255, 0, alpha);
				break;
			case Collider::Type::B_CB: // magenta
				app->render->DrawRectangle(colliders[i]->rect, 0, 255, 255, alpha);
				break;
			case Collider::Type::H_CB: // orange
				app->render->DrawRectangle(colliders[i]->rect, 255, 155, 0, alpha);
				break;
			case Collider::Type::V_CB: // light blue
				app->render->DrawRectangle(colliders[i]->rect, 0, 240, 255, alpha);
				break;
			case Collider::Type::LAVA: // red
				app->render->DrawRectangle(colliders[i]->rect, 170, 255, 0, alpha);
				break;
			case Collider::Type::NULL_COLLIDER: // black
				app->render->DrawRectangle(colliders[i]->rect, 0, 0, 0, alpha);
				break;
			case Collider::Type::RECOVER_LIFE_POWER_UP: // purple
				app->render->DrawRectangle(colliders[i]->rect, 128, 0, 255, alpha);
				break;
			case Collider::Type::COIN: // light yellow
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 172, alpha);
				break;
			case Collider::Type::CHECKPOINT: // light green
				app->render->DrawRectangle(colliders[i]->rect, 172, 255, 200, alpha);
				break;
			case Collider::Type::GOAL_POINT: // light green
				app->render->DrawRectangle(colliders[i]->rect, 172, 255, 200, alpha);
				break;
			}
		}
		if (app->sceneCastle->godMode == true || app->sceneForest->godMode == true)
		{
			switch (colliders[i]->type)
			{
			case Collider::Type::NONE: // white
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::LAYER_ZERO: // blue
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::PLAYER: // green
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::PLAYER_FEET: //orange
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::ENEMY: // red
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::INSTANT_DEATH: // yellow
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::B_CB: // magenta
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::H_CB: // orange
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::V_CB: // light blue
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::LAVA: // light green
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::NULL_COLLIDER: // black
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::RECOVER_LIFE_POWER_UP: // purple
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::COIN: // light yellow
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::CHECKPOINT: // light green
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::GOAL_POINT: // light green
				app->render->DrawRectangle(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			}
		}
	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			//LOG("Added ColliderSensor");
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
			//LOG("Removed ColliderSensor");
		}
	}
}