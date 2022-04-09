#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "Collider.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Enemies.h"
#include "ModulePhysics.h"
#include "Enemy.h"
#include "App.h"



Enemy::Enemy(int x, int y) : position(x, y)
{

}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update(float dt)
{

	if (currentAnim != nullptr)
			currentAnim->Update();

	if (collider != nullptr)
			collider->SetPos(position.x, position.y);

	EnemyCounter++;

}

void Enemy::Draw()
{
	if (enemyHit == false)
	{
		if (currentAnim != nullptr)
			app->render->DrawTexture(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
	}
	enemyHit = false; // For visual hit effect
}

void Enemy::OnCollision(Collider* c2)
{
	if (enemyHit == false && EnemyCounter>2) // Cambiar ya que los pies del jugador ya no sirven para nada
	{
		/*
		if (app->player->jump == true || app->player->hover==true || app->player->inTheAir==true)
		{
			if (c2->type == Collider::Type::PLAYER_FEET)
			{
				app->player->Player->body->SetLinearVelocity({ 0.0f,0.0f });
				//if (app->player->PlayerLookingPosition == 1) app->player->currentAnimation = &app->player->jumpLeftAnim;
				//if (app->player->PlayerLookingPosition == 2) app->player->currentAnimation = &app->player->jumpRightAnim;
				app->player->Player->body->ApplyLinearImpulse({ 0.0f,-150.0f }, { 0.0f,0.0f }, true);
				enemyHit = true;
				//LOG("Enemy particle test");
				EnemyCounter = 0;
				EnemyHP -= 1;
			}
		}
		*/
		
	}
	enemyHit = false;
}

void Enemy::SetToDelete()
{
	pendingToDelete = true;
	//app->audio->PlayFx(app->enemies->enemyDestroyedFx, 0);
	//app->particles->AddParticle(app->particles->enemyDefeat, position.x + 4, position.y + 4, Collider::NONE);
	if(collider != nullptr)
	{
		app->audio->PlayFx(app->enemies->enemyDestroyedFx, 0);
		app->particles->AddParticle(app->particles->enemyDefeat, position.x + 4, position.y + 4, Collider::NONE);
		collider->pendingToDelete = true; 
	}
		
}