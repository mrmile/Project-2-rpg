#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneCastle.h"
#include "SceneMainMap.h"
#include "DrawInOrder.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "TitleScreen.h"
#include "EntityManager.h"
#include "Entity.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "PauseMenu.h"
#include "Pathfinding.h"

#include "Defs.h"
#include "Log.h"
#include <SDL_mixer/include/SDL_mixer.h>

#include <algorithm>

DrawInOrder::DrawInOrder(bool start_enabled) : Module(start_enabled)
{
	name.Create("SceneMainMap");
}

// Destructor
DrawInOrder::~DrawInOrder()
{}

// Called before render is available
bool DrawInOrder::Awake()
{
	LOG("Drawing in order start");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool DrawInOrder::Start()
{
	

	return true;
}

// Called each loop iteration
bool DrawInOrder::PreUpdate()
{
	

	return true;
}

// Called each loop iteration
bool DrawInOrder::Update(float dt)
{
	// Sort everything (only L1)
	
	//texturesList_L1->BubbleSort();
	
	//texturesList_L1->At(1)->data->position.y;
	//std::sort(texturesList_L1->start, texturesList_L1->end, compare);

	return true;
}

// Called each loop iteration
bool DrawInOrder::PostUpdate()
{
	// First draw everything and then clear

	for (int i = 0; texturesList_L2.At(i) != NULL; i++)
	{
		app->render->DrawTexture(texturesList_L2.At(i)->data->texture, texturesList_L2.At(i)->data->position.x, texturesList_L2.At(i)->data->position.y, &texturesList_L2.At(i)->data->section, texturesList_L2.At(i)->data->parallax);
	}

	for (int i = 0; texturesList_L1.At(i) != NULL; i++)
	{
		app->render->DrawTexture(texturesList_L1.At(i)->data->texture, texturesList_L1.At(i)->data->position.x, texturesList_L1.At(i)->data->position.y, &texturesList_L1.At(i)->data->section, texturesList_L1.At(i)->data->parallax);
	}

	for (int i = 0; texturesList_L0.At(i) != NULL; i++)
	{
		app->render->DrawTexture(texturesList_L0.At(i)->data->texture, texturesList_L0.At(i)->data->position.x, texturesList_L0.At(i)->data->position.y, &texturesList_L0.At(i)->data->section, texturesList_L0.At(i)->data->parallax);
	}

	texturesList_L1.clear();
	texturesList_L0.clear();
	texturesList_L2.clear();
	
	return true;
}

// Called before quitting
bool DrawInOrder::CleanUp()
{
	LOG("Freeing DrawInOrder memory (don't really know)");
	texturesList_L1.clear();
	texturesList_L0.clear();
	texturesList_L2.clear();

	return true;
}


void DrawInOrder::AddTextureToList_L1(SDL_Texture* texture, iPoint position, SDL_Rect section, float parallax)
{
	TextureProperties textureProperties;
	textureProperties.texture = texture;
	textureProperties.position = position;
	textureProperties.section = section;
	textureProperties.parallax = parallax;

	texturesList_L1.add(&textureProperties);
	
}

void DrawInOrder::AddTextureToList_L0(SDL_Texture* texture, iPoint position, SDL_Rect section, float parallax)
{
	TextureProperties textureProperties;
	textureProperties.texture = texture;
	textureProperties.position = position;
	textureProperties.section = section;
	textureProperties.parallax = parallax;

	texturesList_L0.add(&textureProperties);

}

void DrawInOrder::AddTextureToList_L2(SDL_Texture* texture, iPoint position, SDL_Rect section, float parallax)
{
	TextureProperties textureProperties;
	textureProperties.texture = texture;
	textureProperties.position = position;
	textureProperties.section = section;
	textureProperties.parallax = parallax;

	texturesList_L2.add(&textureProperties);

}

bool DrawInOrder::compare(TextureProperties a, TextureProperties b)
{
	if (a.position.y < b.position.y)
		return 1;
	else
		return 0;
}