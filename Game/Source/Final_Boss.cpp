//#include "Final_Boss.h"
//
//#include "App.h"
//#include "ModuleCollisions.h"
//#include "ModulePlayer.h"
//#include "EntityManager.h"
////#include "ModuleParticles.h"
//#include "Audio.h"
//#include "Point.h"
//#include "DynArray.h"
//#include "Input.h"
//#include "Map.h"
//#include "Pathfinding.h"
//#include "SceneMainMap.h"
//#include "Render.h"
//#include "Textures.h"
//#include "Log.h"
//#include "ModulePhysics.h"
//#include "ModuleParticles.h"
//
//#include "Defs.h"
//
//
//Final_Boss::Final_Boss(int x,int y) : Entity(x,y)
//{	
//	EntityHP = 1;
//	EntityAP = 5;
//	EntityMP = 3;
//	entityState = GameState::OutOfCombat;
//	entityTurn = TurnState::NONE;
//	counter = 0;
//	EntityKillable = true;
//	//HERE WE ADD THE ANIMATIONS WITH GIMP
//	
//	
//	Idle_Enemy.PushBack({24,45,25,56});
//	Idle_Enemy.loop = true;
//	Idle_Enemy.speed = 0.3f;
//
//	
//
//	position.x = x;
//	position.y = y;
//
//	collider = app->collisions->AddCollider({ position.x, position.y - 46, 25, 56 }, Collider::Type::ENEMY, (Module*)app->entity_manager);
//
//	Standart_Zombie_List.add(app->physics->CreateWalkingEnemyBox(position.x, position.y, 25, 10));
//	
//	
//	
//}
//
//void Final_Boss::Update(float dt)
//{
//	//ADD THE PATHFINDING LOGIC FOR MOVEMENT
//	
//	if (app->player->pauseMenu == true)
//	{
//		iPoint NewPosition = position;
//		collider->SetPos(NewPosition.x, NewPosition.y - 46);
//		Standart_Zombie_List.end->data->GetPosition(NewPosition.x, NewPosition.y);
//		currentAnim = &Idle_Enemy;
//		currentAnim->loop = false;
//
//	}
//	if (app->player->pauseMenu == false)
//	{
//		//Escape Combat
//		if (app->player->escapeCombat == true)
//		{
//			entityState = GameState::OutOfCombat;
//			entityTurn = TurnState::NONE;
//		}
//
//		if (EntityHP == 0)
//		{
//			SetToDelete();
//			//Standart_Zombie_List.end->data->body->DestroyFixture(Standart_Zombie_List.end->data->body->GetFixtureList());
//			// NO FUNCIONA EL DESTRUIR LA FIXTURE
//		}
//		if (entityState == GameState::OutOfCombat)
//		{
//			//move normally
//			
//			
//
//			
//
//		}
//		
//		if (entityState == GameState::InCombat)
//		{
//			
//			if (EntityHP > 0)
//			{
//				if (entityTurn == TurnState::NONE)
//				{
//					//Assigning order of turns
//					
//				}
//				if (entityTurn == TurnState::StartOfTurn)
//				{
//					
//
//					entityTurn = TurnState::MidOfTurn;
//
//				}
//				if (entityTurn == TurnState::MidOfTurn)
//				{
//
//					
//					if (counter == 150) entityTurn = TurnState::FinishTurn;
//
//				}
//				if (entityTurn == TurnState::FinishTurn)
//				{
//					//Change turn from enemy to player turn still have to develop a way to do it correctly
//
//
//
//					entityTurn = TurnState::WaitTurn;
//					
//
//				}
//				if (entityTurn == TurnState::WaitTurn)
//				{
//					counter = 0;
//					
//					currentAnim->loop = true;
//		
//				}
//				
//
//
//			}
//				
//
//			
//			
//		}
//		
//		
//		
//	}
//	
//}



/*
iPoint Origin = app->render->ScreenToWorld(position.x, position.y);
iPoint Destination = app->render->ScreenToWorld(app->player->position.x, app->player->position.y);


const DynArray<iPoint>* path = { nullptr };
app->pathfinding->CreatePath(Origin, Destination);

path = app->pathfinding->GetLastPath();

for (uint i = 0; i < path->Count(); ++i)
{
	iPoint NextPos = app->map->MapToWorld(path->At(i)->x, path->At(i)->y);

	app->render->DrawRectangle({ NextPos.x,NextPos.y,10,10 }, 255, 0, 0, 255);

	if (NextPos.x > position.x) entityBody->body->SetLinearVelocity({ -0.5f, 0.0f });
	if (NextPos.x < position.x) entityBody->body->SetLinearVelocity({ 0.5f, 0.0f });
	if (NextPos.y > position.y) entityBody->body->SetLinearVelocity({ 0.0f, -0.5f });
	if (NextPos.y < position.y) entityBody->body->SetLinearVelocity({ 0.0f, 0.5f });



}
*/