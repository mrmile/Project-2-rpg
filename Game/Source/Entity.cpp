#include "App.h"
#include "Entity.h"
#include "EntityManager.h"
#include "ModuleCollisions.h"
#include "Collider.h"
#include "Render.h"
#include "Textures.h"

Entity::Entity(iPoint position) : position()
{

}

Entity::~Entity()
{

}
const Collider* Entity::GetColldier() const
{
	return collider;
}
bool Entity::Update(float dt)
{
	if (currentAnim != nullptr)
	{
		currentAnim->Update();
	}
		

	if (collider != nullptr)
	{
		collider->SetPos(position.x, position.y);
	}

	return true;
}
void Entity::Draw()
{
	if (currentAnim != nullptr)
	{
		app->render->DrawTexture2(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
	}
}
