#include "App.h"
#include "Entity.h"
#include "EntityManager.h"
#include "ModuleCollisions.h"
#include "Collider.h"
#include "Render.h"
#include "Textures.h"
#include "ModulePlayer.h"
#include "GameManager.h"

Entity::Entity(int x,int y) : position(x,y)
{

}

Entity::~Entity()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
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
		app->render->DrawTexture(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
	}
}

void Entity::SetToDelete()
{
	LOG("DELETING COLLIDER");

	if (collider != nullptr)
	{

		collider->pendingToDelete = true;
	}

}

void Entity::ReduceAP(int AP_used)
{
	EntityAP = EntityAP - AP_used;
}


void Entity::OnCollision(Collider* c2)
{

	if ((c2->type == Collider::Type::PLAYER_ATTACK) && (EntityKillable == true))
	{
		EntityHP -= 1;
	}

	if ((c2->type == Collider::Type::PLAYER) && (type == EntityType::OBJECT_FOOD))
	{
		//add item food to the list take into account the amount of items in the list and if it is stackable or not
		//have to create an item list and iterate through that list in order to add the item (need to create it in the item manager menu) 
	}

}
