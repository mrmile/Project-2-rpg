#include "ModulePlayer.h"

#include "app.h"
#include "Textures.h"
#include "Input.h"
#include "GamepadInput.h"
#include "Render.h"
#include "EntityManager.h"
#include "Entity.h"
//#include "ModuleParticles.h"
#include "Audio.h"
#include "ModuleFadeToBlack.h"
#include "Window.h"
//#include "ModuleFonts.h"
#include "GameManager.h"
#include "Log.h"

#include "SceneMainMap.h"
#include "SceneCave.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "Audio.h"
#include "TitleScreen.h"
#include "ModuleFonts.h"

#include <stdio.h>
#include <time.h>
#include <SDL_mixer/include/SDL_mixer.h>
#include <iostream>
#include <Optick/include/optick.h>
using namespace std;

ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	name.Create("player");

	idleRightAnim.PushBack({ 0, 0, 40, 56 });
	idleRightAnim.loop = true;
	idleRightAnim.speed = 0.3f;

	idleLeftAnim.PushBack({ 0, 0, 40, 56 });
	idleLeftAnim.loop = true;
	idleLeftAnim.speed = 0.3f;
	
	idleDownAnim.PushBack({ 0, 0, 40, 56 });
	idleDownAnim.loop = true;
	idleDownAnim.speed = 0.3f;

	idleUpAnim.PushBack({ 0, 0, 40, 56 });
	idleUpAnim.loop = true;
	idleUpAnim.speed = 0.3f;
	

	entityTurnPlayer = TurnState::NONE;
	entityStatePlayer = GameState::OutOfCombat;



}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Awake()
{
	return true;
}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;
	
	texture = app->tex->Load("Assets/textures/debugRect.png");


	currentAnimation = &idleRightAnim;



	//laserFx = app->audio->LoadFx("Assets/Fx/laser.wav");
	//explosionFx = app->audio->LoadFx("Assets/Fx/explosion.wav");

	//position = app->map->MapToWorld(5, 21); // En el load objects
	b2VelocitySet.x = 0;
	b2VelocitySet.y = -0.5f;
	//position.x = 0;
	//position.y = 0;

	//scale = 1
	// ofset x = 500
	// ofset y = 50

	//scale = 2
	// ofset Px = 1 = Cx = 2 
	// ofset Py = 1 = Cy = 2

	//app->render->camera.x = app->map->MapToWorld(32, 4100).x;
	//app->render->camera.y = app->map->MapToWorld(32, 4100).y;

	destroyed = false;
	deletePlayer = false;
	checkPointReached = false;

	collider = app->collisions->AddCollider({ position.x + 5, position.y + 3, 28, 23 }, Collider::Type::PLAYER, this); //{ position.x + 5, position.y + 3, 28, 33 
	colliderFeet = app->collisions->AddCollider({ position.x + 5, position.y + 23, 18, 10 }, Collider::Type::PLAYER_FEET, this);

	Player = app->physics->CreatePlayerBox(position.x, position.y, 20, 5);
	//app->physics->CreateRectangleSensor(position.x, position.y + 16, 28, 1);
	//Player = app->physics->CreatePlayerCircle(position.x, position.y, 20);
	

	//TestingGround = app->physics->CreateColliderRectangle(app->map->MapToWorld(5, 26).x, app->map->MapToWorld(5, 26).y, 1000, 100); // Tendria que estar en Scene.cpp
	//TestingGround = app->physics->CreateColliderRectangle(0, 50, 1000, 100);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = app->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	//LOADING FONT FOR GAME
	char lookupTable[] = { "0123456789" };
	scoreFont = app->fonts->Load("Assets/textures/numbersV3.png", lookupTable, 1);

	PlayerLookingPosition = 2;

	playerTimer = 0;
	playerIdleAnimationTimer = 0;
	hoverTimer = 0;
	destroyedDelay = 0;
	winDelay = 0;
	gameOverDelay = 0;
	TransationToTilteDelay = 0;
	createPlayer = false;

	playerWin = false;

	layerZeroReveal = false;

	//srand(time(NULL));

	uint winWidth, winHeight;

	app->win->GetWindowSize(winWidth, winHeight);

	playerHP = 100;
	invincibleDelay = 120;
	playerFPS = 0;

	sceneTimer = 450;

	pauseMenu = false;

	exitActivated = false;
	talking = false;
	
	return ret;
}

bool ModulePlayer::Update(float dt)
{
	
	if (pauseMenu==true)
	{
		iPoint NewPosition = position;
		collider->SetPos(NewPosition.x, NewPosition.y);
		colliderFeet->SetPos(NewPosition.x + 5, NewPosition.y + 23);
		return true;
	}
	if (pauseMenu == false)
	{
		playerFPS++;
		invincibleDelay++;

		//OPTICK_EVENT();
		collider->SetPos(position.x, position.y);
		colliderFeet->SetPos(position.x + 5, position.y + 23);
		//Player->body->SetTransform({ positionToB2D.x, positionToB2D.y }, 0);
		playerTimer++;
		//------------------------------------------------------------------------------------------------------------------------------------------
		if (talking == false && entityStatePlayer == GameState::OutOfCombat)
		{
			showCombatHUD = false;

			if (destroyed == false && playerWin == false && app->sceneCave->godMode == false && app->sceneMainMap->godMode == false)
			{
				/* Mejor no usarlo para este juego
				if ((playerFPS % 60) == 0) sceneTimer--;
				if (sceneTimer <= 0)
				{
					sceneTimer = 0;
					app->player->playerHP = 0;
				}
				*/

				if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT
					&& app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_IDLE)
				{
					if (run == false)Player->body->SetLinearVelocity({ -2.0f,0.0f });
					if (run == true)Player->body->SetLinearVelocity({ -4.0f,0.0f });
				}
				else if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT
					&& app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_IDLE)
				{
					if (run == false)Player->body->SetLinearVelocity({ 2.0f,0.0f });
					if (run == true)Player->body->SetLinearVelocity({ 4.0f,0.0f });
				}
				else if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT
					&& app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_IDLE)
				{
					if (run == false)Player->body->SetLinearVelocity({ 0.0f,-2.0f });
					if (run == true)Player->body->SetLinearVelocity({ 0.0f,-4.0f });
				}
				else if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT)
				{
					if (run == false)Player->body->SetLinearVelocity({ 0.0f,2.0f });
					if (run == true)Player->body->SetLinearVelocity({ 0.0f,4.0f });
				}
				else if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT
					&& app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT
					&& app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_IDLE)
				{
					if (run == false)Player->body->SetLinearVelocity({ -2.0f,-2.0f });
					if (run == true)Player->body->SetLinearVelocity({ -4.0f,-4.0f });
				}
				else if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT
					&& app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT)
				{
					if (run == false)Player->body->SetLinearVelocity({ -2.0f,2.0f });
					if (run == true)Player->body->SetLinearVelocity({ -4.0f,4.0f });
				}
				else if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT
					&& app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT
					&& app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_IDLE)
				{
					if (run == false)Player->body->SetLinearVelocity({ 2.0f,-2.0f });
					if (run == true)Player->body->SetLinearVelocity({ 4.0f,-4.0f });
				}
				else if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT
					&& app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT)
				{
					if (run == false)Player->body->SetLinearVelocity({ 2.0f,2.0f });
					if (run == true)Player->body->SetLinearVelocity({ 4.0f,4.0f });
				}


				if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT)
				{
					if (run == false)
					{
						if (currentAnimation != &leftWalkAnim)
						{
							leftWalkAnim.Reset();
							currentAnimation = &leftWalkAnim;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &leftRunAnim)
						{
							leftRunAnim.Reset();
							currentAnimation = &leftRunAnim;
						}
					}

					PlayerLookingPosition = 1;

				}

				if (app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT)
				{
					if (run == false)
					{
						if (currentAnimation != &upWalkAnim)
						{
							upWalkAnim.Reset();
							currentAnimation = &upWalkAnim;
							PlayerLookingPosition = 4;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &upRunAnim)
						{
							upRunAnim.Reset();
							currentAnimation = &upRunAnim;
							PlayerLookingPosition = 4;
						}
					}

				}

				if (app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT)
				{

					if (run == false)
					{
						if (currentAnimation != &rightWalkAnim)
						{
							rightWalkAnim.Reset();
							currentAnimation = &rightWalkAnim;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &rightRunAnim)
						{
							rightRunAnim.Reset();
							currentAnimation = &rightRunAnim;
						}
					}
					PlayerLookingPosition = 2;

				}

				if (app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT)
				{
					if (run == false)
					{

						if (currentAnimation != &downWalkAnim)
						{
							downWalkAnim.Reset();
							currentAnimation = &downWalkAnim;
							PlayerLookingPosition = 3;
						}
					}
					else if (run == true)
					{

						if (currentAnimation != &downRunAnim)
						{
							downRunAnim.Reset();
							currentAnimation = &downRunAnim;
							PlayerLookingPosition = 3;
						}
					}

				}

				if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT && app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT)
				{
					if (run == false)
					{
						if (currentAnimation != &leftDownWalkAnim)
						{
							leftDownWalkAnim.Reset();
							currentAnimation = &leftDownWalkAnim;
							PlayerLookingPosition = 5;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &leftDownRunAnim)
						{
							leftDownRunAnim.Reset();
							currentAnimation = &leftDownRunAnim;
							PlayerLookingPosition = 5;
						}
					}

				}

				if (app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT && app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT)
				{
					if (run == false)
					{
						if (currentAnimation != &rightDownWalkAnim)
						{
							rightDownWalkAnim.Reset();
							currentAnimation = &rightDownWalkAnim;
							PlayerLookingPosition = 6;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &rightDownRunAnim)
						{
							rightDownRunAnim.Reset();
							currentAnimation = &rightDownRunAnim;
							PlayerLookingPosition = 6;
						}
					}
				}

				if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT && app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT)
				{
					if (run == false)
					{
						if (currentAnimation != &leftUpWalkAnim)
						{
							leftUpWalkAnim.Reset();
							currentAnimation = &leftUpWalkAnim;
							PlayerLookingPosition = 7;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &leftUpRunAnim)
						{
							leftUpRunAnim.Reset();
							currentAnimation = &leftUpRunAnim;
							PlayerLookingPosition = 7;
						}
					}
				}

				if (app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT && app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT)
				{
					if (run == false)
					{
						if (currentAnimation != &rightUpWalkAnim)
						{
							rightUpWalkAnim.Reset();
							currentAnimation = &rightUpWalkAnim;
							PlayerLookingPosition = 8;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &rightUpRunAnim)
						{
							rightUpRunAnim.Reset();
							currentAnimation = &rightUpRunAnim;
							PlayerLookingPosition = 8;
						}
					}
				}

				if (app->input->keys[SDL_SCANCODE_Z] == KeyState::KEY_DOWN)
				{
					// To implement: interact with the environment (examples: grab an object, press a switch…)/select item/select options
				}

				if (app->input->keys[SDL_SCANCODE_X] == KeyState::KEY_DOWN)
				{
					// To implement: use item
				}

				if (app->input->keys[SDL_SCANCODE_C] == KeyState::KEY_DOWN)
				{
					// To implement: throw things away
				}

				if ((app->input->keys[SDL_SCANCODE_LSHIFT] == KeyState::KEY_REPEAT))
				{
					run = true;
				}
				else
				{
					run = false;
				}


				if(app->input->keys[SDL_SCANCODE_9] == KeyState::KEY_DOWN)
				{
					app->game_manager->NextTurn();
				}

				// If no up/down movement detected, set the current animation back to idle
				if (app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_IDLE)
				{
					Player->body->SetLinearVelocity({ 0.0f,0.0f });

					playerIdleAnimationTimer++;
					speed = 0;

					switch (PlayerLookingPosition)
					{
					case 1:
						if (currentAnimation != &idleLeftAnim)
						{
							idleLeftAnim.Reset();
							currentAnimation = &idleLeftAnim;
						}

						break;
					case 2:
						if (currentAnimation != &idleRightAnim)
						{
							idleRightAnim.Reset();
							currentAnimation = &idleRightAnim;
						}

						break;

					case 3:
						if (currentAnimation != &idleDownAnim)
						{
							idleDownAnim.Reset();
							currentAnimation = &idleDownAnim;
						}

						break;

					case 4:
						if (currentAnimation != &idleUpAnim)
						{
							idleUpAnim.Reset();
							currentAnimation = &idleUpAnim;
						}

						break;

					case 5:
						if (currentAnimation != &idleDownLeftAnim)
						{
							idleDownLeftAnim.Reset();
							currentAnimation = &idleDownLeftAnim;
						}

						break;

					case 6:
						if (currentAnimation != &idleDownRightAnim)
						{
							idleDownRightAnim.Reset();
							currentAnimation = &idleDownRightAnim;
						}

						break;

					case 7:
						if (currentAnimation != &idleUpLeftAnim)
						{
							idleUpLeftAnim.Reset();
							currentAnimation = &idleUpLeftAnim;
						}

						break;

					case 8:
						if (currentAnimation != &idleUpRightAnim)
						{
							idleUpRightAnim.Reset();
							currentAnimation = &idleUpRightAnim;
						}

						break;
					}

				}
			}
			//------------------------------------------------------------------------------------------------------------------------------------------
			if (destroyed == false && playerWin == false && (app->sceneCave->godMode == true || app->sceneMainMap->godMode == true))
			{
				//Aquí no hace falta
			}
		}
		if (entityStatePlayer == GameState::InCombat)
		{
			showCombatHUD = true;


			if (entityTurnPlayer == TurnState::NONE)
			{

				iPoint NewPosition = position;
				collider->SetPos(NewPosition.x, NewPosition.y);
				colliderFeet->SetPos(NewPosition.x + 5, NewPosition.y + 23);
				Player->body->SetLinearVelocity({ 0.0f,0.0f });
			}
			if (entityTurnPlayer == TurnState::StartOfTurn)
			{
				
				iPoint NewPosition = position;
				collider->SetPos(NewPosition.x, NewPosition.y);
				colliderFeet->SetPos(NewPosition.x + 5, NewPosition.y + 23);
				Player->body->SetLinearVelocity({ 0.0f,0.0f });
				entityTurnPlayer = TurnState::MidOfTurn;
			}
			if (entityTurnPlayer == TurnState::MidOfTurn)
			{
				
				
				if(app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT)
				{
					counter++;
					Player->body->SetLinearVelocity({ 0.0f,2.0f });
				}
				if (app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT)
				{
					counter++;
					Player->body->SetLinearVelocity({ 0.0f,-2.0f });
				}
				if (app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT)
				{
					counter++;
					Player->body->SetLinearVelocity({ 2.0f,0.0f });
				}
				if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT)
				{
					counter++;
					Player->body->SetLinearVelocity({ -2.0f,0.0f });
				}

				if (counter > 200)
				{
					entityTurnPlayer = TurnState::FinishTurn;
				}
			}
			if (entityTurnPlayer == TurnState::FinishTurn)
			{
				//Attack methodology, after attacking the player goes to wait turn
				entityTurnPlayer = TurnState::WaitTurn;
			}
			if (entityTurnPlayer == TurnState::WaitTurn)
			{
				iPoint NewPosition = position;
				Player->body->SetLinearVelocity({ 0.0f,0.0f });
				collider->SetPos(NewPosition.x, NewPosition.y);
				colliderFeet->SetPos(NewPosition.x + 5, NewPosition.y + 23);

				if (playerHP <= 0)
				{
					invincibleDelay = 121;
					playerHP = 0;
					//app->audio->PlayFx(dead);
					destroyed = true;

				}
				if (destroyed == true)
				{
					if (destroyedDelay < 1)
					{
						//Mix_PauseMusic();
						
						app->audio->PlayFx(dead);
						//lives--;
						app->sceneMainMap->playerRestart = true;
						
					}
					if (destroyedDelay < 60) Player->body->SetLinearVelocity({ 0, 0 });

					if (currentAnimation != &die)
					{
						die.Reset();
						currentAnimation = &die;
					}
				}

			}
		}
		//  //TODO: Para la alpha mejorar el dialog system
		// 
		//else if (talking == true)
		//{
		//	//Cosas comentadas ya que aún no han sido implementadas --> To implement: Dialog manager <-- Es un handout de una presentación de clase
		//	
		//	if (app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_DOWN)
		//	{
		//		//selection--;
		//	}
		//	if (app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_DOWN)
		//	{
		//		//selection++;
		//	}

		//	/*
		//	if(selection > totalSelectionsAvailable) selection = 0;
		//	if(selection < 0) selection = totalSelectionsAvailable;
		//	*/

		//	if (app->input->keys[SDL_SCANCODE_Z] == KeyState::KEY_DOWN)
		//	{
		//		//select answer/continue reading
		//	}
		//}
		//------------------------------------------------------------------------------------------------------------------------------------------
		
		//------------------------------------------------------------------------------------------------------------------------------------------
		/*
		if ((PlayerLookingPosition == 1) && (position.x < app->render->camera.x / app->win->GetScale() + 190))
		{
			app->render->camera.x -= 5;
		}
		if ((PlayerLookingPosition == 2) && (position.x > app->render->camera.x / app->win->GetScale() + 140))
		{
			app->render->camera.x += 5;
		}
		*/
		
		/*
		if (lives == 0)
		{
		
			
			app->titleScreen->SavedGame = false;
			app->titleScreen->Enable();
			app->CheckGameRequest();
			app->titleScreen->MainMenu = true;
			
			app->map->Disable();
			app->collisions->Disable();
			app->particles->Disable();
			app->sceneMainMap->Disable();
			app->player->Disable();
			app->enemies->Disable();
			app->fonts->Disable();
			
		}
		*/

		currentAnimation->Update();

		Player->GetPosition(position.x, position.y);


		
	}
	
	
	if ((app->input->keys[SDL_SCANCODE_P] == KEY_DOWN || app->input->keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN) && app->player->destroyed == false && app->player->playerWin == false)
	{
		app->audio->PlayFx(paused);
		pauseMenu = !pauseMenu;
	}

	
	//------------------------------------------------------------------------------------------------------------------------------------------
	return true;
}

bool ModulePlayer::PostUpdate()
{
	
		if (destroyed == true)
		{
			destroyedDelay++;
		}
		if (playerWin == true)
		{
			winDelay++;
		}

		/* Desplazado a Map.cpp para que se dibuje en orden
		if (invincibleDelay <= 120)
		{
			if ((playerFPS / 5) % 2 == 0)
			{
				SDL_Rect rect = currentAnimation->GetCurrentFrame();
				app->render->DrawTexture(texture, position.x, position.y, &rect);
			}
		}
		else
		{
			SDL_Rect rect = currentAnimation->GetCurrentFrame();
			app->render->DrawTexture(texture, position.x, position.y, &rect);
		}
		*/

		// Draw UI (score) --------------------------------------
		sprintf_s(scoreText, 10, "%5d", score);
		sprintf_s(lifeText, 10, "%1d", lives);
		sprintf_s(timerText, 10, "%3d", sceneTimer);

		app->render->DrawTexture2(yoshiIcon, 5, 28, NULL, 0.0f);
		app->render->DrawTexture2(clockIcon, 400, 30, NULL, 0.0f);

		SDL_Rect quad;
		quad = { 5, 10, playerHP, 10 };

		SDL_Rect quad2;
		quad2 = { 5, 10, 100, 10 };

		SDL_Rect bgquad;
		bgquad = { 3, 8, 104, 14 };
		app->render->DrawRectangle2(bgquad, 255, 255, 255, 255, 0.0f, true);
		app->render->DrawRectangle2(quad2, 200, 200, 200, 255, 0.0f, true);
		//app->render->DrawRectangle(bgquad, 255, 255, 255, 165, true, true);
		if (playerHP >= 100)
		{
			playerHP = 100;
			app->render->DrawRectangle2(quad, 0, 255, 0, 255, 0.0f, true);
		}
		else if (playerHP > 50)
		{
			app->render->DrawRectangle2(quad, 120, 255, 0, 255, 0.0f, true);
		}
		else if (playerHP > 20 && playerHP <= 50)
		{
			app->render->DrawRectangle2(quad, 255, 255, 0, 255, 0.0f, true);
		}
		else
		{
			if ((playerFPS / 5) % 2 == 0)
			{
				app->render->DrawRectangle2(quad, 255, 0, 0, 255, 0.0f, true);
			}
			else
			{
				app->render->DrawRectangle2(quad, 255, 150, 0, 255, 0.0f, true);
			}

		}

		if (app->sceneCave->playerRestart == true)
		{
			//horizontalCB = true;
			app->sceneCave->sceneTimer = 0;

			//if (checkPointReached == false) position = app->map->MapToWorld(32, 14);
				//if (checkPointReached == true) position = app->map->MapToWorld(32, 14);
			score = 0;
			app->player->Disable();
			app->sceneCave->Disable();
			app->collisions->Disable();
			app->map->Disable();
			app->entity_manager->Disable();
			app->particles->Disable();
			app->fonts->Disable();

			if (checkPointReached == false) position = app->map->playerStartPos;
			if (checkPointReached == true) position = app->map->playerCheckPointPos;

			app->player->Enable();
			app->sceneCave->Enable();
			app->collisions->Enable();
			app->map->Enable();
			app->entity_manager->Enable();
			app->particles->Enable();
			app->fonts->Enable();

			app->sceneCave->playerRestart = false;
		}

		
		if (app->sceneMainMap->playerRestart == true)
		{
			//horizontalCB = true;
			app->sceneMainMap->sceneTimer = 0;

			//if (checkPointReached == false) position = app->map->MapToWorld(32, 14);
				//if (checkPointReached == true) position = app->map->MapToWorld(32, 14);
			app->player->Disable();
			app->sceneMainMap->Disable();
			app->collisions->Disable();
			app->map->Disable();
			app->entity_manager->Disable();
			app->particles->Disable();
			app->fonts->Disable();

			if (checkPointReached == false) position = app->map->playerStartPos;
			if (checkPointReached == true) position = app->map->playerCheckPointPos;

			app->player->Enable();
			app->sceneMainMap->Enable();
			app->collisions->Enable();
			app->map->Enable();
			app->entity_manager->Enable();
			app->particles->Enable();
			app->fonts->Enable();

			app->sceneMainMap->playerRestart = false;
			entityStatePlayer = GameState::OutOfCombat;
			entityTurnPlayer = TurnState::NONE;
		}
		

		if (app->titleScreen->toTitleScreen == true)
		{
			gameOverDelay++;

			app->render->DrawTexture2(gameOverScreen, 0, 0, NULL, 0.0f);

			if (gameOverDelay > 1 && gameOverDelay <= 2) app->audio->PlayFx(gameOverfx);

			if (gameOverDelay > 600 && gameOverDelay <= 601)
			{
				app->titleScreen->SavedGame = false;
				app->titleScreen->Enable();
				app->CheckGameRequest();

				app->map->Disable();
				app->collisions->Disable();
				app->particles->Disable();
				app->sceneMainMap->Disable();
				app->player->Disable();
				app->entity_manager->Disable();
				app->fonts->Disable();

				app->titleScreen->toTitleScreen = false;
			}
		}

		// TODO 3: Blit the text of the score in at the bottom of the screen
		app->render->DrawTexture2(ptsScore, 400, 15, NULL);
		app->fonts->BlitText(320, 10, scoreFont, scoreText);
		app->fonts->BlitText(30, 30, scoreFont, lifeText);
		app->fonts->BlitText(350, 30, scoreFont, timerText);

		//app->fonts->BlitText(150, 248, scoreFont, "this is just a font test message");

		return true;
	
	
}

bool ModulePlayer::CleanUp()
{
	app->tex->UnLoad(texture);

	//deletePlayer = true;
	app->player->Player->body->DestroyFixture(app->player->Player->body->GetFixtureList());
	//app->collisions->RemoveCollider(app->player->collider);
	//app->collisions->RemoveCollider(app->player->colliderFeet);

	return true;
}

bool ModulePlayer::LoadState(pugi::xml_node& data)
{
	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();

	score = data.child("atributes").attribute("score").as_int();
	playerHP = data.child("atributes").attribute("hp").as_int();
	lives = data.child("atributes").attribute("lives").as_int();
	sceneTimer = data.child("atributes").attribute("timer").as_int();


	if (app->player->IsEnabled() == true)
	{
		app->player->Player->body->DestroyFixture(app->player->Player->body->GetFixtureList());

		Player = app->physics->CreatePlayerBox(position.x, position.y, 20, 5);
	}
	
	
	//b2Filter b;
	//b.categoryBits = 0x0001;
	//b.maskBits = 0x0001 | 0x0002;
	//Player->body->GetFixtureList()->SetFilterData(b);
	createPlayer = false;

	//if (app->player->horizontalCB == false && app->sceneCave->sceneTimer > 1) app->render->camera.x = -(app->player->Player->body->GetPosition().x * 100) + 630;

	return true;
}

// L02: DONE 8: Create a method to save the state of the renderer
// Save Game State
bool ModulePlayer::SaveState(pugi::xml_node& data) const
{
	pugi::xml_node playerpos = data.append_child("position");
	pugi::xml_node playerAtributes = data.append_child("atributes");
	
	playerpos.append_attribute("x") = position.x;
	playerpos.append_attribute("y") = position.y;
	playerAtributes.append_attribute("score") = score;
	playerAtributes.append_attribute("hp") = playerHP;
	playerAtributes.append_attribute("lives") = lives;
	playerAtributes.append_attribute("timer") = sceneTimer;


	return true;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (app->sceneCave->godMode == false && app->sceneMainMap->godMode == false && destroyed == false && playerWin == false)
	{
		if ((c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY_ATTACK ) && destroyed == false && invincibleDelay >= 120)
		{

			playerHP -= 10;
			if (playerHP < 0) playerHP = 0;
			invincibleDelay = 0;
			if (playerHP != 0) app->audio->PlayFx(damaged);

			if (playerHP <= 0)
			{
				invincibleDelay = 121;
				playerHP = 0;
				//app->audio->PlayFx(dead);
				destroyed = true;

			}


		}

		if ((c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY_RANGED_ATTACK) && destroyed == false && invincibleDelay >= 120)
		{

			playerHP -= 10;
			if (playerHP < 0) playerHP = 0;
			invincibleDelay = 0;
			if (playerHP != 0) app->audio->PlayFx(damaged);

			if (playerHP <= 0)
			{
				invincibleDelay = 121;
				playerHP = 0;
				//app->audio->PlayFx(dead);
				destroyed = true;

			}


		}

		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::EXIT_1)
		{
			exitActivated = true;

			entranceID = 1;
		}

		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::EXIT_2)
		{
			exitActivated = true;
			entranceID = 2;
		}

		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::EXIT_3)
		{
			exitActivated = true;
			entranceID = 3;
		}

		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::LAYER_ZERO)
		{
			if (layerZeroReveal == false)
			{
				layerZeroReveal = true;
			}
		}
		else if ((c1->type == Collider::Type::PLAYER) && c2->type != Collider::Type::LAYER_ZERO)
		{
			if (layerZeroReveal == true)
			{
				layerZeroReveal = false;
			}
		}

		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::SWITCH)
		{
			
		}
		
		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::INSTANT_DEATH)
		{
			playerHP -= 100;
			if (playerHP < 0) playerHP = 0;
			invincibleDelay = 0;
			if (playerHP != 0) app->audio->PlayFx(damaged);

			if (playerHP <= 0)
			{
				invincibleDelay = 121;
				playerHP = 0;
				//app->audio->PlayFx(dead);
				destroyed = true;

			}
		}

		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::RECOVER_LIFE_POWER_UP)
		{
			playerHP += 10;
			if (playerHP > 100) playerHP = 100;
			app->audio->PlayFx(recoverLifePowerUp);
		}

		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::COIN)
		{
			score += 5;
			//if (playerScore > 1000) playerScore = 1000;
			app->audio->PlayFx(coin);
		}

		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::CHECKPOINT)
		{
			score += 10;
			//if (playerScore > 1000) playerScore = 1000;
			app->audio->PlayFx(halfWayPoint);
			app->titleScreen->SavedGame = true;
			app->SaveGameRequest();
			saved_game = true;
			checkPointReached = true;
		}

		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::GOAL_POINT)
		{
			//playerScore += 10;
			//if (playerScore > 1000) playerScore = 1000;
			app->audio->PlayFx(levelClear);
			app->titleScreen->SavedGame = false;
			app->SaveGameRequest();
			playerWin = true;

			app->particles->AddParticle(app->particles->enemyDefeat, app->map->goalPoolPos.x, app->map->goalPoolPos.y - 5, Collider::NONE);
			app->particles->AddParticle(app->particles->firework1, app->map->goalPoolPos.x + 6, app->map->goalPoolPos.y - 8, Collider::NONE, 6);
			app->particles->AddParticle(app->particles->firework2, app->map->goalPoolPos.x - 10, app->map->goalPoolPos.y + 4, Collider::NONE, 12);
			app->particles->AddParticle(app->particles->firework3, app->map->goalPoolPos.x + 2, app->map->goalPoolPos.y - 6, Collider::NONE, 18);

		}
	}
}

iPoint ModulePlayer::GetLastPosition()
{
	iPoint NewPosition = position;

	return NewPosition;
}
