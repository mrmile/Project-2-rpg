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
#include "GuiManager.h"
#include "SceneMotel.h"
#include "SceneMainMap.h"
#include "SceneCave.h"
#include "SceneBase.h"
#include "ScenePlatform.h"
#include "Map.h"
#include "ModulePhysics.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "Audio.h"
#include "TitleScreen.h"
#include "MapMenu.h"
#include "InventoryMenu.h"
#include "ModuleFonts.h"
#include "QuestManager.h"
#include "DialogManager.h"

#include <stdio.h>
#include <time.h>
#include <SDL_mixer/include/SDL_mixer.h>
#include <iostream>
#include <Optick/include/optick.h>
using namespace std;

ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	name.Create("player");


	//IDLE

	idleRightAnim.PushBack({ 141, 579, 80, 95 });
	idleRightAnim.loop = true;
	idleRightAnim.speed = 0.3f;

	idleLeftAnim.PushBack({ 141, 199, 80, 95 });
	idleLeftAnim.loop = true;
	idleLeftAnim.speed = 0.3f;

	idleDownAnim.PushBack({ 141, 769, 80, 95 });
	idleDownAnim.loop = true;
	idleDownAnim.speed = 0.3f;

	idleUpAnim.PushBack({ 141, 389, 80, 95 });
	idleUpAnim.loop = true;
	idleUpAnim.speed = 0.3f;

	idleUpLeftAnim.PushBack({ 141, 294, 80, 95 });
	idleUpLeftAnim.loop = true;
	idleUpLeftAnim.speed = 0.3f;

	idleUpRightAnim.PushBack({ 141, 484, 80, 95 });
	idleUpRightAnim.loop = true;
	idleUpRightAnim.speed = 0.3f;

	idleDownLeftAnim.PushBack({ 141, 104, 80, 95 });
	idleDownLeftAnim.loop = true;
	idleDownLeftAnim.speed = 0.3f;

	idleDownRightAnim.PushBack({ 141, 674, 80, 95 });
	idleDownRightAnim.loop = true;
	idleDownRightAnim.speed = 0.3f;


	//WALK 

	rightWalkAnim.PushBack({ 140, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 225, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 310, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 395, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 480, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 565, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 650, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 735, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 820, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 905, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 990, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 1075, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 1160, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 1245, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 1330, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 1415, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 1500, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 1585, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 1670, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 1755, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 1840, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 1925, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 2010, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 2095, 3885, 85, 105 });
	rightWalkAnim.PushBack({ 2180, 3885, 85, 105 });
	rightWalkAnim.loop = true;
	rightWalkAnim.speed = 0.27f;

	leftWalkAnim.PushBack({ 140, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 225, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 310, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 395, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 480, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 565, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 650, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 735, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 820, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 905, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 990, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 1075, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 1160, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 1245, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 1330, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 1415, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 1500, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 1585, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 1670, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 1755, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 1840, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 1925, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 2010, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 2095, 3465, 85, 105 });
	leftWalkAnim.PushBack({ 2180, 3465, 85, 105 });
	leftWalkAnim.loop = true;
	leftWalkAnim.speed = 0.27f;

	downWalkAnim.PushBack({ 140, 4095, 85, 105 });
	downWalkAnim.PushBack({ 225, 4095, 85, 105 });
	downWalkAnim.PushBack({ 310, 4095, 85, 105 });
	downWalkAnim.PushBack({ 395, 4095, 85, 105 });
	downWalkAnim.PushBack({ 480, 4095, 85, 105 });
	downWalkAnim.PushBack({ 565, 4095, 85, 105 });
	downWalkAnim.PushBack({ 650, 4095, 85, 105 });
	downWalkAnim.PushBack({ 735, 4095, 85, 105 });
	downWalkAnim.PushBack({ 820, 4095, 85, 105 });
	downWalkAnim.PushBack({ 905, 4095, 85, 105 });
	downWalkAnim.PushBack({ 990, 4095, 85, 105 });
	downWalkAnim.PushBack({ 1075, 4095, 85, 105 });
	downWalkAnim.PushBack({ 1160, 4095, 85, 105 });
	downWalkAnim.PushBack({ 1245, 4095, 85, 105 });
	downWalkAnim.PushBack({ 1330, 4095, 85, 105 });
	downWalkAnim.PushBack({ 1415, 4095, 85, 105 });
	downWalkAnim.PushBack({ 1500, 4095, 85, 105 });
	downWalkAnim.PushBack({ 1585, 4095, 85, 105 });
	downWalkAnim.PushBack({ 1670, 4095, 85, 105 });
	downWalkAnim.PushBack({ 1755, 4095, 85, 105 });
	downWalkAnim.PushBack({ 1840, 4095, 85, 105 });
	downWalkAnim.PushBack({ 1925, 4095, 85, 105 });
	downWalkAnim.PushBack({ 2010, 4095, 85, 105 });
	downWalkAnim.PushBack({ 2095, 4095, 85, 105 });
	downWalkAnim.PushBack({ 2180, 4095, 85, 105 });
	downWalkAnim.loop = true;
	downWalkAnim.speed = 0.27f;

	upWalkAnim.PushBack({ 140, 3675, 85, 105 });
	upWalkAnim.PushBack({ 225, 3675, 85, 105 });
	upWalkAnim.PushBack({ 310, 3675, 85, 105 });
	upWalkAnim.PushBack({ 395, 3675, 85, 105 });
	upWalkAnim.PushBack({ 480, 3675, 85, 105 });
	upWalkAnim.PushBack({ 565, 3675, 85, 105 });
	upWalkAnim.PushBack({ 650, 3675, 85, 105 });
	upWalkAnim.PushBack({ 735, 3675, 85, 105 });
	upWalkAnim.PushBack({ 820, 3675, 85, 105 });
	upWalkAnim.PushBack({ 905, 3675, 85, 105 });
	upWalkAnim.PushBack({ 990, 3675, 85, 105 });
	upWalkAnim.PushBack({ 1075, 3675, 85, 105 });
	upWalkAnim.PushBack({ 1160, 3675, 85, 105 });
	upWalkAnim.PushBack({ 1245, 3675, 85, 105 });
	upWalkAnim.PushBack({ 1330, 3675, 85, 105 });
	upWalkAnim.PushBack({ 1415, 3675, 85, 105 });
	upWalkAnim.PushBack({ 1500, 3675, 85, 105 });
	upWalkAnim.PushBack({ 1585, 3675, 85, 105 });
	upWalkAnim.PushBack({ 1670, 3675, 85, 105 });
	upWalkAnim.PushBack({ 1755, 3675, 85, 105 });
	upWalkAnim.PushBack({ 1840, 3675, 85, 105 });
	upWalkAnim.PushBack({ 1925, 3675, 85, 105 });
	upWalkAnim.PushBack({ 2010, 3675, 85, 105 });
	upWalkAnim.PushBack({ 2095, 3675, 85, 105 });
	upWalkAnim.PushBack({ 2180, 3675, 85, 105 });
	upWalkAnim.loop = true;
	upWalkAnim.speed = 0.27f;

	rightDownWalkAnim.PushBack({ 140, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 225, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 310, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 395, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 480, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 565, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 650, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 735, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 820, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 905, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 990, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 1075, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 1160, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 1245, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 1330, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 1415, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 1500, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 1585, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 1670, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 1755, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 1840, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 1925, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 2010, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 2095, 3990, 85, 105 });
	rightDownWalkAnim.PushBack({ 2180, 3990, 85, 105 });
	rightDownWalkAnim.loop = true;
	rightDownWalkAnim.speed = 0.27f;

	leftDownWalkAnim.PushBack({ 140, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 225, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 310, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 395, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 480, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 565, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 650, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 735, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 820, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 905, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 990, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 1075, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 1160, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 1245, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 1330, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 1415, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 1500, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 1585, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 1670, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 1755, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 1840, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 1925, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 2010, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 2095, 3360, 85, 105 });
	leftDownWalkAnim.PushBack({ 2180, 3360, 85, 105 });
	leftDownWalkAnim.loop = true;
	leftDownWalkAnim.speed = 0.27f;

	rightUpWalkAnim.PushBack({ 140, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 225, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 310, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 395, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 480, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 565, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 650, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 735, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 820, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 905, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 990, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 1075, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 1160, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 1245, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 1330, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 1415, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 1500, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 1585, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 1670, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 1755, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 1840, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 1925, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 2010, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 2095, 3780, 85, 105 });
	rightUpWalkAnim.PushBack({ 2180, 3780, 85, 105 });
	rightUpWalkAnim.loop = true;
	rightUpWalkAnim.speed = 0.27f;

	leftUpWalkAnim.PushBack({ 140, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 225, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 310, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 395, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 480, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 565, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 650, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 735, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 820, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 905, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 990, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 1075, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 1160, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 1245, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 1330, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 1415, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 1500, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 1585, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 1670, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 1755, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 1840, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 1925, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 2010, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 2095, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 2180, 3570, 85, 105 });
	leftUpWalkAnim.loop = true;
	leftUpWalkAnim.speed = 0.27f;


	//RUN

	rightRunAnim.PushBack({ 140, 3885, 85, 105 });
	rightRunAnim.PushBack({ 225, 3885, 85, 105 });
	rightRunAnim.PushBack({ 310, 3885, 85, 105 });
	rightRunAnim.PushBack({ 395, 3885, 85, 105 });
	rightRunAnim.PushBack({ 480, 3885, 85, 105 });
	rightRunAnim.PushBack({ 565, 3885, 85, 105 });
	rightRunAnim.PushBack({ 650, 3885, 85, 105 });
	rightRunAnim.PushBack({ 735, 3885, 85, 105 });
	rightRunAnim.PushBack({ 820, 3885, 85, 105 });
	rightRunAnim.PushBack({ 905, 3885, 85, 105 });
	rightRunAnim.PushBack({ 990, 3885, 85, 105 });
	rightRunAnim.PushBack({ 1075, 3885, 85, 105 });
	rightRunAnim.PushBack({ 1160, 3885, 85, 105 });
	rightRunAnim.PushBack({ 1245, 3885, 85, 105 });
	rightRunAnim.PushBack({ 1330, 3885, 85, 105 });
	rightRunAnim.PushBack({ 1415, 3885, 85, 105 });
	rightRunAnim.PushBack({ 1500, 3885, 85, 105 });
	rightRunAnim.PushBack({ 1585, 3885, 85, 105 });
	rightRunAnim.PushBack({ 1670, 3885, 85, 105 });
	rightRunAnim.PushBack({ 1755, 3885, 85, 105 });
	rightRunAnim.PushBack({ 1840, 3885, 85, 105 });
	rightRunAnim.PushBack({ 1925, 3885, 85, 105 });
	rightRunAnim.PushBack({ 2010, 3885, 85, 105 });
	rightRunAnim.PushBack({ 2095, 3885, 85, 105 });
	rightRunAnim.PushBack({ 2180, 3885, 85, 105 });
	rightRunAnim.loop = true;
	rightRunAnim.speed = 0.56f;

	leftRunAnim.PushBack({ 140, 3465, 85, 105 });
	leftRunAnim.PushBack({ 225, 3465, 85, 105 });
	leftRunAnim.PushBack({ 310, 3465, 85, 105 });
	leftRunAnim.PushBack({ 395, 3465, 85, 105 });
	leftRunAnim.PushBack({ 480, 3465, 85, 105 });
	leftRunAnim.PushBack({ 565, 3465, 85, 105 });
	leftRunAnim.PushBack({ 650, 3465, 85, 105 });
	leftRunAnim.PushBack({ 735, 3465, 85, 105 });
	leftRunAnim.PushBack({ 820, 3465, 85, 105 });
	leftRunAnim.PushBack({ 905, 3465, 85, 105 });
	leftRunAnim.PushBack({ 990, 3465, 85, 105 });
	leftRunAnim.PushBack({ 1075, 3465, 85, 105 });
	leftRunAnim.PushBack({ 1160, 3465, 85, 105 });
	leftRunAnim.PushBack({ 1245, 3465, 85, 105 });
	leftRunAnim.PushBack({ 1330, 3465, 85, 105 });
	leftRunAnim.PushBack({ 1415, 3465, 85, 105 });
	leftRunAnim.PushBack({ 1500, 3465, 85, 105 });
	leftRunAnim.PushBack({ 1585, 3465, 85, 105 });
	leftRunAnim.PushBack({ 1670, 3465, 85, 105 });
	leftRunAnim.PushBack({ 1755, 3465, 85, 105 });
	leftRunAnim.PushBack({ 1840, 3465, 85, 105 });
	leftRunAnim.PushBack({ 1925, 3465, 85, 105 });
	leftRunAnim.PushBack({ 2010, 3465, 85, 105 });
	leftRunAnim.PushBack({ 2095, 3465, 85, 105 });
	leftRunAnim.PushBack({ 2180, 3465, 85, 105 });
	leftRunAnim.loop = true;
	leftRunAnim.speed = 0.56f;

	downRunAnim.PushBack({ 140, 4095, 85, 105 });
	downRunAnim.PushBack({ 225, 4095, 85, 105 });
	downRunAnim.PushBack({ 310, 4095, 85, 105 });
	downRunAnim.PushBack({ 395, 4095, 85, 105 });
	downRunAnim.PushBack({ 480, 4095, 85, 105 });
	downRunAnim.PushBack({ 565, 4095, 85, 105 });
	downRunAnim.PushBack({ 650, 4095, 85, 105 });
	downRunAnim.PushBack({ 735, 4095, 85, 105 });
	downRunAnim.PushBack({ 820, 4095, 85, 105 });
	downRunAnim.PushBack({ 905, 4095, 85, 105 });
	downRunAnim.PushBack({ 990, 4095, 85, 105 });
	downRunAnim.PushBack({ 1075, 4095, 85, 105 });
	downRunAnim.PushBack({ 1160, 4095, 85, 105 });
	downRunAnim.PushBack({ 1245, 4095, 85, 105 });
	downRunAnim.PushBack({ 1330, 4095, 85, 105 });
	downRunAnim.PushBack({ 1415, 4095, 85, 105 });
	downRunAnim.PushBack({ 1500, 4095, 85, 105 });
	downRunAnim.PushBack({ 1585, 4095, 85, 105 });
	downRunAnim.PushBack({ 1670, 4095, 85, 105 });
	downRunAnim.PushBack({ 1755, 4095, 85, 105 });
	downRunAnim.PushBack({ 1840, 4095, 85, 105 });
	downRunAnim.PushBack({ 1925, 4095, 85, 105 });
	downRunAnim.PushBack({ 2010, 4095, 85, 105 });
	downRunAnim.PushBack({ 2095, 4095, 85, 105 });
	downRunAnim.PushBack({ 2180, 4095, 85, 105 });
	downRunAnim.loop = true;
	downRunAnim.speed = 0.56f;

	upRunAnim.PushBack({ 140, 3675, 85, 105 });
	upRunAnim.PushBack({ 225, 3675, 85, 105 });
	upRunAnim.PushBack({ 310, 3675, 85, 105 });
	upRunAnim.PushBack({ 395, 3675, 85, 105 });
	upRunAnim.PushBack({ 480, 3675, 85, 105 });
	upRunAnim.PushBack({ 565, 3675, 85, 105 });
	upRunAnim.PushBack({ 650, 3675, 85, 105 });
	upRunAnim.PushBack({ 735, 3675, 85, 105 });
	upRunAnim.PushBack({ 820, 3675, 85, 105 });
	upRunAnim.PushBack({ 905, 3675, 85, 105 });
	upRunAnim.PushBack({ 990, 3675, 85, 105 });
	upRunAnim.PushBack({ 1075, 3675, 85, 105 });
	upRunAnim.PushBack({ 1160, 3675, 85, 105 });
	upRunAnim.PushBack({ 1245, 3675, 85, 105 });
	upRunAnim.PushBack({ 1330, 3675, 85, 105 });
	upRunAnim.PushBack({ 1415, 3675, 85, 105 });
	upRunAnim.PushBack({ 1500, 3675, 85, 105 });
	upRunAnim.PushBack({ 1585, 3675, 85, 105 });
	upRunAnim.PushBack({ 1670, 3675, 85, 105 });
	upRunAnim.PushBack({ 1755, 3675, 85, 105 });
	upRunAnim.PushBack({ 1840, 3675, 85, 105 });
	upRunAnim.PushBack({ 1925, 3675, 85, 105 });
	upRunAnim.PushBack({ 2010, 3675, 85, 105 });
	upRunAnim.PushBack({ 2095, 3675, 85, 105 });
	upRunAnim.PushBack({ 2180, 3675, 85, 105 });
	upRunAnim.loop = true;
	upRunAnim.speed = 0.56f;

	rightDownRunAnim.PushBack({ 140, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 225, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 310, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 395, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 480, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 565, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 650, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 735, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 820, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 905, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 990, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 1075, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 1160, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 1245, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 1330, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 1415, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 1500, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 1585, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 1670, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 1755, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 1840, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 1925, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 2010, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 2095, 3990, 85, 105 });
	rightDownRunAnim.PushBack({ 2180, 3990, 85, 105 });
	rightDownRunAnim.loop = true;
	rightDownRunAnim.speed = 0.56f;

	leftDownRunAnim.PushBack({ 140, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 225, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 310, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 395, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 480, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 565, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 650, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 735, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 820, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 905, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 990, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 1075, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 1160, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 1245, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 1330, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 1415, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 1500, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 1585, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 1670, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 1755, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 1840, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 1925, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 2010, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 2095, 3360, 85, 105 });
	leftDownRunAnim.PushBack({ 2180, 3360, 85, 105 });
	leftDownRunAnim.loop = true;
	leftDownRunAnim.speed = 0.56f;

	rightUpRunAnim.PushBack({ 140, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 225, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 310, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 395, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 480, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 565, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 650, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 735, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 820, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 905, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 990, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 1075, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 1160, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 1245, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 1330, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 1415, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 1500, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 1585, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 1670, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 1755, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 1840, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 1925, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 2010, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 2095, 3780, 85, 105 });
	rightUpRunAnim.PushBack({ 2180, 3780, 85, 105 });
	rightUpRunAnim.loop = true;
	rightUpRunAnim.speed = 0.56f;

	leftUpRunAnim.PushBack({ 140, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 225, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 310, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 395, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 480, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 565, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 650, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 735, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 820, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 905, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 990, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 1075, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 1160, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 1245, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 1330, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 1415, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 1500, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 1585, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 1670, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 1755, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 1840, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 1925, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 2010, 3570, 85, 105 });
	leftUpRunAnim.PushBack({ 2095, 3570, 85, 105 });
	leftUpWalkAnim.PushBack({ 2180, 3570, 85, 105 });
	leftUpRunAnim.loop = true;
	leftUpRunAnim.speed = 0.56f;

	//ATTACK

	rightAttackAnim.PushBack({ 130, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 250, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 370, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 490, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 610, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 730, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 850, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 970, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 1090, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 1210, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 1330, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 1450, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 1570, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 1690, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 1810, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 1930, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 2050, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 2170, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 2290, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 2410, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 2530, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 2650, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 2770, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 2890, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 3010, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 3130, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 3250, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 3370, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 3490, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 3610, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 3730, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 3490, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 3610, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 3730, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 3850, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 3970, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 4090, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 4210, 2890, 120, 120 });
	rightAttackAnim.PushBack({ 4330, 2890, 120, 120 });
	rightAttackAnim.loop = true;
	rightAttackAnim.speed = 0.56f;

	leftAttackAnim.PushBack({ 130, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 250, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 370, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 490, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 610, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 730, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 850, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 970, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 1090, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 1210, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 1330, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 1450, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 1570, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 1690, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 1810, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 1930, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 2050, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 2170, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 2290, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 2410, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 2530, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 2650, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 2770, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 2890, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 3010, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 3130, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 3250, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 3370, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 3490, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 3610, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 3730, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 3490, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 3610, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 3730, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 3850, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 3970, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 4090, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 4210, 2410, 120, 120 });
	leftAttackAnim.PushBack({ 4330, 2410, 120, 120 });
	leftAttackAnim.loop = true;
	leftAttackAnim.speed = 0.56f;

	downAttackAnim.PushBack({ 130, 3130, 120, 120 });
	downAttackAnim.PushBack({ 250, 3130, 120, 120 });
	downAttackAnim.PushBack({ 370, 3130, 120, 120 });
	downAttackAnim.PushBack({ 490, 3130, 120, 120 });
	downAttackAnim.PushBack({ 610, 3130, 120, 120 });
	downAttackAnim.PushBack({ 730, 3130, 120, 120 });
	downAttackAnim.PushBack({ 850, 3130, 120, 120 });
	downAttackAnim.PushBack({ 970, 3130, 120, 120 });
	downAttackAnim.PushBack({ 1090, 3130, 120, 120 });
	downAttackAnim.PushBack({ 1210, 3130, 120, 120 });
	downAttackAnim.PushBack({ 1330, 3130, 120, 120 });
	downAttackAnim.PushBack({ 1450, 3130, 120, 120 });
	downAttackAnim.PushBack({ 1570, 3130, 120, 120 });
	downAttackAnim.PushBack({ 1690, 3130, 120, 120 });
	downAttackAnim.PushBack({ 1810, 3130, 120, 120 });
	downAttackAnim.PushBack({ 1930, 3130, 120, 120 });
	downAttackAnim.PushBack({ 2050, 3130, 120, 120 });
	downAttackAnim.PushBack({ 2170, 3130, 120, 120 });
	downAttackAnim.PushBack({ 2290, 3130, 120, 120 });
	downAttackAnim.PushBack({ 2410, 3130, 120, 120 });
	downAttackAnim.PushBack({ 2530, 3130, 120, 120 });
	downAttackAnim.PushBack({ 2650, 3130, 120, 120 });
	downAttackAnim.PushBack({ 2770, 3130, 120, 120 });
	downAttackAnim.PushBack({ 2890, 3130, 120, 120 });
	downAttackAnim.PushBack({ 3010, 3130, 120, 120 });
	downAttackAnim.PushBack({ 3130, 3130, 120, 120 });
	downAttackAnim.PushBack({ 3250, 3130, 120, 120 });
	downAttackAnim.PushBack({ 3370, 3130, 120, 120 });
	downAttackAnim.PushBack({ 3490, 3130, 120, 120 });
	downAttackAnim.PushBack({ 3610, 3130, 120, 120 });
	downAttackAnim.PushBack({ 3730, 3130, 120, 120 });
	downAttackAnim.PushBack({ 3490, 3130, 120, 120 });
	downAttackAnim.PushBack({ 3610, 3130, 120, 120 });
	downAttackAnim.PushBack({ 3730, 3130, 120, 120 });
	downAttackAnim.PushBack({ 3850, 3130, 120, 120 });
	downAttackAnim.PushBack({ 3970, 3130, 120, 120 });
	downAttackAnim.PushBack({ 4090, 3130, 120, 120 });
	downAttackAnim.PushBack({ 4210, 3130, 120, 120 });
	downAttackAnim.PushBack({ 4330, 3130, 120, 120 });
	downAttackAnim.loop = true;
	downAttackAnim.speed = 0.56f;

	upAttackAnim.PushBack({ 130, 2650, 120, 120 });
	upAttackAnim.PushBack({ 250, 2650, 120, 120 });
	upAttackAnim.PushBack({ 370, 2650, 120, 120 });
	upAttackAnim.PushBack({ 490, 2650, 120, 120 });
	upAttackAnim.PushBack({ 610, 2650, 120, 120 });
	upAttackAnim.PushBack({ 730, 2650, 120, 120 });
	upAttackAnim.PushBack({ 850, 2650, 120, 120 });
	upAttackAnim.PushBack({ 970, 2650, 120, 120 });
	upAttackAnim.PushBack({ 1090, 2650, 120, 120 });
	upAttackAnim.PushBack({ 1210, 2650, 120, 120 });
	upAttackAnim.PushBack({ 1330, 2650, 120, 120 });
	upAttackAnim.PushBack({ 1450, 2650, 120, 120 });
	upAttackAnim.PushBack({ 1570, 2650, 120, 120 });
	upAttackAnim.PushBack({ 1690, 2650, 120, 120 });
	upAttackAnim.PushBack({ 1810, 2650, 120, 120 });
	upAttackAnim.PushBack({ 1930, 2650, 120, 120 });
	upAttackAnim.PushBack({ 2050, 2650, 120, 120 });
	upAttackAnim.PushBack({ 2170, 2650, 120, 120 });
	upAttackAnim.PushBack({ 2290, 2650, 120, 120 });
	upAttackAnim.PushBack({ 2410, 2650, 120, 120 });
	upAttackAnim.PushBack({ 2530, 2650, 120, 120 });
	upAttackAnim.PushBack({ 2650, 2650, 120, 120 });
	upAttackAnim.PushBack({ 2770, 2650, 120, 120 });
	upAttackAnim.PushBack({ 2890, 2650, 120, 120 });
	upAttackAnim.PushBack({ 3010, 2650, 120, 120 });
	upAttackAnim.PushBack({ 3130, 2650, 120, 120 });
	upAttackAnim.PushBack({ 3250, 2650, 120, 120 });
	upAttackAnim.PushBack({ 3370, 2650, 120, 120 });
	upAttackAnim.PushBack({ 3490, 2650, 120, 120 });
	upAttackAnim.PushBack({ 3610, 2650, 120, 120 });
	upAttackAnim.PushBack({ 3730, 2650, 120, 120 });
	upAttackAnim.PushBack({ 3490, 2650, 120, 120 });
	upAttackAnim.PushBack({ 3610, 2650, 120, 120 });
	upAttackAnim.PushBack({ 3730, 2650, 120, 120 });
	upAttackAnim.PushBack({ 3850, 2650, 120, 120 });
	upAttackAnim.PushBack({ 3970, 2650, 120, 120 });
	upAttackAnim.PushBack({ 4090, 2650, 120, 120 });
	upAttackAnim.PushBack({ 4210, 2650, 120, 120 });
	upAttackAnim.PushBack({ 4330, 2650, 120, 120 });
	upAttackAnim.loop = true;
	upAttackAnim.speed = 0.56f;

	rightDownAttackAnim.PushBack({ 130, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 250, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 370, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 490, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 610, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 730, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 850, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 970, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 1090, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 1210, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 1330, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 1450, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 1570, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 1690, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 1810, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 1930, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 2050, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 2170, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 2290, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 2410, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 2530, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 2650, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 2770, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 2890, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 3010, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 3130, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 3250, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 3370, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 3490, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 3610, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 3730, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 3490, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 3610, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 3730, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 3850, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 3970, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 4090, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 4210, 3010, 120, 120 });
	rightDownAttackAnim.PushBack({ 4330, 3010, 120, 120 });
	rightDownAttackAnim.loop = true;
	rightDownAttackAnim.speed = 0.56f;

	leftDownAttackAnim.PushBack({ 130, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 250, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 370, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 490, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 610, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 730, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 850, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 970, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 1090, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 1210, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 1330, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 1450, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 1570, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 1690, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 1810, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 1930, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 2050, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 2170, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 2290, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 2410, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 2530, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 2650, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 2770, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 2890, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 3010, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 3130, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 3250, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 3370, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 3490, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 3610, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 3730, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 3490, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 3610, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 3730, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 3850, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 3970, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 4090, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 4210, 2290, 120, 120 });
	leftDownAttackAnim.PushBack({ 4330, 2290, 120, 120 });
	leftDownAttackAnim.loop = true;
	leftDownAttackAnim.speed = 0.56f;

	rightUpAttackAnim.PushBack({ 130, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 250, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 370, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 490, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 610, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 730, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 850, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 970, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 1090, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 1210, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 1330, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 1450, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 1570, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 1690, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 1810, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 1930, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 2050, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 2170, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 2290, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 2410, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 2530, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 2650, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 2770, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 2890, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 3010, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 3130, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 3250, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 3370, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 3490, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 3610, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 3730, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 3490, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 3610, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 3730, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 3850, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 3970, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 4090, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 4210, 2770, 120, 120 });
	rightUpAttackAnim.PushBack({ 4330, 2770, 120, 120 });
	rightUpAttackAnim.loop = true;
	rightUpAttackAnim.speed = 0.56f;

	leftUpAttackAnim.PushBack({ 130, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 250, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 370, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 490, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 610, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 730, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 850, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 970, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 1090, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 1210, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 1330, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 1450, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 1570, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 1690, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 1810, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 1930, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 2050, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 2170, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 2290, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 2410, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 2530, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 2650, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 2770, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 2890, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 3010, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 3130, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 3250, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 3370, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 3490, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 3610, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 3730, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 3490, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 3610, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 3730, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 3850, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 3970, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 4090, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 4210, 2530, 120, 120 });
	leftUpAttackAnim.PushBack({ 4330, 2530, 120, 120 });
	leftUpAttackAnim.loop = true;
	leftUpAttackAnim.speed = 0.56f;

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
	
	texture = app->tex->Load("Assets/textures/Character/SWAT_Character.png");
	doctorNote = app->tex->Load("Assets/textures/extras/doctor_note.png");
	computerBG = app->tex->Load("Assets/textures/extras/computer_bg.png");
	gameOverScreen = app->tex->Load("Assets/textures/extras/game_over_screen.png");
	selectedEnemy = app->tex->Load("Assets/textures/CircleSelectionInRange.png");
	selectedEnemyNotInRange = app->tex->Load("Assets/textures/CircleSelection.png");

	noteDay1 = app->tex->Load("Assets/textures/extras/day1_text.png");
	noteDay5 = app->tex->Load("Assets/textures/extras/day5_text.png");
	noteDay10 = app->tex->Load("Assets/textures/extras/day10_text.png");
	noteDay15 = app->tex->Load("Assets/textures/extras/day15_text.png");


	returnComputer = app->tex->Load("Assets/textures/extras/returnComputer.png");
	computerExecutable = app->tex->Load("Assets/textures/extras/computerExecutable.png");
	noteComputerDay1 = app->tex->Load("Assets/textures/extras/noteComputerDay1.png");
	noteComputerDay5 = app->tex->Load("Assets/textures/extras/noteComputerDay5.png");
	noteComputerDay10 = app->tex->Load("Assets/textures/extras/noteComputerDay10.png");
	noteComputerDay15 = app->tex->Load("Assets/textures/extras/noteComputerDay15.png");
	folderComputer = app->tex->Load("Assets/textures/extras/folderComputer.png");

	playerHurtSound = app->audio->LoadFx("Assets/audio/fx/ZPlayer/player_damaged_1.wav");
	itemGrab = app->audio->LoadFx("Assets/audio/fx/ZPlayer/player_grab_finish_back_fast_begin_0.wav");
	dead = app->audio->LoadFx("Assets/audio/fx/ZPlayer/player_damaged_2.wav");
	shoot = app->audio->LoadFx("Assets/audio/fx/ZPlayer/PlayerActions/Gun.wav");
	gameOver = app->audio->LoadFx("Assets/audio/fx/ZPlayer/game_over.wav");

	computerOff = app->audio->LoadFx("Assets/audio/fx/extra/windows_off.wav");
	computerOn = app->audio->LoadFx("Assets/audio/fx/extra/windows_on.wav");
	computerClick = app->audio->LoadFx("Assets/audio/fx/extra/click.wav");
	harborUnlockFx = app->audio->LoadFx("Assets/audio/fx/extra/harbor_unlock.wav");
	alarmCardReaderFx = app->audio->LoadFx("Assets/audio/fx/extra/alarm_card_reader.wav");
	switchOkFx = app->audio->LoadFx("Assets/audio/fx/extra/switch_ok.wav");
	decodeButtonFx = app->audio->LoadFx("Assets/audio/fx/extra/decode_button.wav");

	alarmSwitch1Fx = app->audio->LoadFx("Assets/audio/fx/extra/alarm_switch.wav");
	alarmSwitch2Fx = app->audio->LoadFx("Assets/audio/fx/extra/alarm_switch.wav");
	alarmSwitch3Fx = app->audio->LoadFx("Assets/audio/fx/extra/alarm_switch.wav");
	alarmSwitch4Fx = app->audio->LoadFx("Assets/audio/fx/extra/alarm_switch.wav");
	alarmSwitch5Fx = app->audio->LoadFx("Assets/audio/fx/extra/alarm_switch.wav");

	explosionFx_far = app->audio->LoadFx("Assets/audio/fx/zombies/zombie_grenade_explode_far.wav");
	heartbeatFX = app->audio->LoadFx("Assets/audio/fx/UISounds/heartbeat.wav");

	if (app->sceneMainMap->sceneMainMap == true || app->sceneMotel->sceneMotel == true)
	{
		playerWalkSound[0] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Tile/FootstepTile01.wav");
		playerWalkSound[1] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Tile/FootstepTile02.wav");
		playerWalkSound[2] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Tile/FootstepTile03.wav");
		playerWalkSound[3] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Tile/FootstepTile04.wav");
		playerWalkSound[4] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Tile/FootstepTile05.wav");
		playerWalkSound[5] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Tile/FootstepTile06.wav");
		playerWalkSound[6] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Tile/FootstepTile07.wav");
	}

	if (app->sceneCave->sceneCave == true)
	{
		playerWalkSound[0] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Dirt/FootstepDirt01.wav");
		playerWalkSound[1] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Dirt/FootstepDirt02.wav");
		playerWalkSound[2] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Dirt/FootstepDirt03.wav");
		playerWalkSound[3] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Dirt/FootstepDirt04.wav");
		playerWalkSound[4] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Dirt/FootstepDirt05.wav");
		playerWalkSound[5] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Dirt/FootstepDirt06.wav");
		playerWalkSound[6] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Dirt/FootstepDirt07.wav");
	}

	if (app->sceneBase->sceneBase == true || app->scenePlatform->scenePlatform == true)
	{
		playerWalkSound[0] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Metal/FootstepMetal01.wav");
		playerWalkSound[1] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Metal/FootstepMetal02.wav");
		playerWalkSound[2] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Metal/FootstepMetal03.wav");
		playerWalkSound[3] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Metal/FootstepMetal04.wav");
		playerWalkSound[4] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Metal/FootstepMetal05.wav");
		playerWalkSound[5] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Metal/FootstepMetal06.wav");
		playerWalkSound[6] = app->audio->LoadFx("Assets/audio/fx/ZPlayer/Footsteps/Metal/FootstepMetal07.wav");
	}

	returnComputerGUI = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 41, "Computer Return Button", { 35,40,29,23 }, this, returnComputer, NULL, {});
	computerExecutableGUI = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 42, "Computer Executable Button", { 407,245,54,50 }, this, computerExecutable, NULL, {});
	noteComputerDay1GUI = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 45, "Computer Note Button", { 50,75,54,50 }, this, noteComputerDay1, NULL, {});
	noteComputerDay5GUI = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 46, "Computer Note Button", { 160,190,54,50 }, this, noteComputerDay5, NULL, {});
	noteComputerDay10GUI = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 47, "Computer Note Button", { 520,235,54,50 }, this, noteComputerDay10, NULL, {});
	noteComputerDay15GUI = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 43, "Computer Note Button", { 460,40,54,50 }, this, noteComputerDay15, NULL, {});
	folderComputerGUI = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 44, "Computer Fold Button", { 90,200,54,50 }, this, folderComputer, NULL, {});

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

	readingNote = false;
	usingComputer = false;
	usingSwitch = false;
	usingCardReader = false;

	collider = app->collisions->AddCollider({ position.x + 5, position.y - 20, 35, 25 }, Collider::Type::PLAYER, this); //{ position.x + 5, position.y + 3, 28, 33 
	

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

	PlayerMaxHP = 100;
	playerHP = 100;
	/*invincibleDelay = 120;*/
	playerFPS = 0;

	sceneTimer = 450;

	pauseMenu = false;

	exitActivated = false;
	talking = false;

	walkSoundID = 0;

	inBossBatle = false;
	activateFinalBoss = false;

	QTE_Counter = 0;
	finalBossPhaseCounter = 0;
	finalBossPlayerStrikes = 0;
	QTE_Counter_bar = 0;

	return ret;
}

bool ModulePlayer::PreUpdate()
{

	return true;
}

bool ModulePlayer::Update(float dt)
{
	if (pauseMenu == false && app->inventoryMenu->showInventory == false && destroyed == false && talking == false && app->player->showCombatHUD == false && app->mapMenu->showMapMenu == false)
	{
		if (usingComputer == true)
		{
			if (computerPhase == 0)
			{
				folderComputerGUI->canClick = true;
			}
			if (computerPhase == 1)
			{
				noteComputerDay1GUI->canClick = true;
				noteComputerDay5GUI->canClick = true;
				noteComputerDay10GUI->canClick = true;
				noteComputerDay15GUI->canClick = true;
			}
			if (computerPhase == 2) //condicion del .exe AlvaroComputer
			{
				computerExecutableGUI->canClick = true;
			}

			returnComputerGUI->canClick = true;
		}
		if (usingComputer == false)
		{
			returnComputerGUI->canClick = false;
			folderComputerGUI->canClick = false;
			noteComputerDay1GUI->canClick = false;
			noteComputerDay5GUI->canClick = false;
			noteComputerDay10GUI->canClick = false;
			noteComputerDay15GUI->canClick = false;
			computerExecutableGUI->canClick = false;
		}
	}
	
	if (pauseMenu==true)
	{
		iPoint NewPosition = position;
		collider->SetPos(NewPosition.x, NewPosition.y);
		//colliderFeet->SetPos(NewPosition.x + 5, NewPosition.y + 23);
		return true;
	}

	if (pauseMenu == false && app->inventoryMenu->showInventory == false && app->mapMenu->showMapMenu == false)
	{
		playerFPS++;

		//OPTICK_EVENT();
		collider->SetPos(position.x + 5, position.y - 20);
		
		playerTimer++;
		//------------------------------------------------------------------------------------------------------------------------------------------
		if (talking == false && entityStatePlayer == GameState::OutOfCombat)
		{
			showCombatHUD = false;

			if (destroyed == false && playerWin == false && app->sceneCave->godMode == false && app->sceneMainMap->godMode == false && app->sceneMotel->godMode == false && app->sceneBase->godMode == false && app->scenePlatform->godMode == false)
			{
				if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT
					|| app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT
					|| app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT
					|| app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT)
				{
					if (run == false)
					{
						if (playerFPS % 40 == 0)
						{
							app->audio->PlayFx(playerWalkSound[walkSoundID]);
							walkSoundID++;

							if (walkSoundID > 6) walkSoundID = 0;
						}
					}
					if (run == true)
					{
						if (playerFPS % 20 == 0)
						{
							app->audio->PlayFx(playerWalkSound[walkSoundID]);
							walkSoundID++;

							if (walkSoundID > 6) walkSoundID = 0;
						}
					}
				}

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
							//leftWalkAnim.Reset();
							currentAnimation = &leftWalkAnim;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &leftRunAnim)
						{
							//leftRunAnim.Reset();
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
							//upWalkAnim.Reset();
							currentAnimation = &upWalkAnim;
							PlayerLookingPosition = 4;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &upRunAnim)
						{
							//upRunAnim.Reset();
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
							//rightWalkAnim.Reset();
							currentAnimation = &rightWalkAnim;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &rightRunAnim)
						{
							//rightRunAnim.Reset();
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
							//downWalkAnim.Reset();
							currentAnimation = &downWalkAnim;
							PlayerLookingPosition = 3;
						}
					}
					else if (run == true)
					{

						if (currentAnimation != &downRunAnim)
						{
							//downRunAnim.Reset();
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
							//leftDownWalkAnim.Reset();
							currentAnimation = &leftDownWalkAnim;
							PlayerLookingPosition = 5;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &leftDownRunAnim)
						{
							//leftDownRunAnim.Reset();
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
							//rightDownWalkAnim.Reset();
							currentAnimation = &rightDownWalkAnim;
							PlayerLookingPosition = 6;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &rightDownRunAnim)
						{
							//rightDownRunAnim.Reset();
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
							//leftUpWalkAnim.Reset();
							currentAnimation = &leftUpWalkAnim;
							PlayerLookingPosition = 7;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &leftUpRunAnim)
						{
							//leftUpRunAnim.Reset();
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
							//rightUpWalkAnim.Reset();
							currentAnimation = &rightUpWalkAnim;
							PlayerLookingPosition = 8;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &rightUpRunAnim)
						{
							//rightUpRunAnim.Reset();
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
					//Grab items from the floor
					app->particles->AddParticle(app->particles->PlayerPickUpRadius, position.x-10, position.y, Collider::Type::PLAYER_PICKUP_RADIUS);
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
							//idleLeftAnim.Reset();
							currentAnimation = &idleLeftAnim;
						}

						break;
					case 2:
						if (currentAnimation != &idleRightAnim)
						{
							//idleRightAnim.Reset();
							currentAnimation = &idleRightAnim;
						}

						break;

					case 3:
						if (currentAnimation != &idleDownAnim)
						{
							//idleDownAnim.Reset();
							currentAnimation = &idleDownAnim;
						}

						break;

					case 4:
						if (currentAnimation != &idleUpAnim)
						{
							//idleUpAnim.Reset();
							currentAnimation = &idleUpAnim;
						}

						break;

					case 5:
						if (currentAnimation != &idleDownLeftAnim)
						{
							//idleDownLeftAnim.Reset();
							currentAnimation = &idleDownLeftAnim;
						}

						break;

					case 6:
						if (currentAnimation != &idleDownRightAnim)
						{
							//idleDownRightAnim.Reset();
							currentAnimation = &idleDownRightAnim;
						}

						break;

					case 7:
						if (currentAnimation != &idleUpLeftAnim)
						{
							//idleUpLeftAnim.Reset();
							currentAnimation = &idleUpLeftAnim;
						}

						break;

					case 8:
						if (currentAnimation != &idleUpRightAnim)
						{
							//idleUpRightAnim.Reset();
							currentAnimation = &idleUpRightAnim;
						}

						break;
					}

				}
			}
			//------------------------------------------------------------------------------------------------------------------------------------------
			if (destroyed == false && playerWin == false && (app->sceneCave->godMode == true || app->sceneMainMap->godMode == true || app->sceneMotel->godMode == true || app->sceneBase->godMode == true || app->scenePlatform->godMode == true))
			{
				if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_REPEAT
					|| app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_REPEAT
					|| app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_REPEAT
					|| app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_REPEAT)
				{
					if (run == false)
					{
						if (playerFPS % 40 == 0)
						{
							app->audio->PlayFx(playerWalkSound[walkSoundID]);
							walkSoundID++;

							if (walkSoundID > 6) walkSoundID = 0;
						}
					}
					if (run == true)
					{
						if (playerFPS % 20 == 0)
						{
							app->audio->PlayFx(playerWalkSound[walkSoundID]);
							walkSoundID++;

							if (walkSoundID > 6) walkSoundID = 0;
						}
					}
				}

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
							//leftWalkAnim.Reset();
							currentAnimation = &leftWalkAnim;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &leftRunAnim)
						{
							//leftRunAnim.Reset();
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
							//upWalkAnim.Reset();
							currentAnimation = &upWalkAnim;
							PlayerLookingPosition = 4;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &upRunAnim)
						{
							//upRunAnim.Reset();
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
							//rightWalkAnim.Reset();
							currentAnimation = &rightWalkAnim;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &rightRunAnim)
						{
							//rightRunAnim.Reset();
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
							//downWalkAnim.Reset();
							currentAnimation = &downWalkAnim;
							PlayerLookingPosition = 3;
						}
					}
					else if (run == true)
					{

						if (currentAnimation != &downRunAnim)
						{
							//downRunAnim.Reset();
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
							//leftDownWalkAnim.Reset();
							currentAnimation = &leftDownWalkAnim;
							PlayerLookingPosition = 5;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &leftDownRunAnim)
						{
							//leftDownRunAnim.Reset();
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
							//rightDownWalkAnim.Reset();
							currentAnimation = &rightDownWalkAnim;
							PlayerLookingPosition = 6;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &rightDownRunAnim)
						{
							//rightDownRunAnim.Reset();
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
							//leftUpWalkAnim.Reset();
							currentAnimation = &leftUpWalkAnim;
							PlayerLookingPosition = 7;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &leftUpRunAnim)
						{
							//leftUpRunAnim.Reset();
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
							//rightUpWalkAnim.Reset();
							currentAnimation = &rightUpWalkAnim;
							PlayerLookingPosition = 8;
						}
					}
					else if (run == true)
					{
						if (currentAnimation != &rightUpRunAnim)
						{
							//rightUpRunAnim.Reset();
							currentAnimation = &rightUpRunAnim;
							PlayerLookingPosition = 8;
						}
					}
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
							//idleLeftAnim.Reset();
							currentAnimation = &idleLeftAnim;
						}

						break;
					case 2:
						if (currentAnimation != &idleRightAnim)
						{
							//idleRightAnim.Reset();
							currentAnimation = &idleRightAnim;
						}

						break;

					case 3:
						if (currentAnimation != &idleDownAnim)
						{
							//idleDownAnim.Reset();
							currentAnimation = &idleDownAnim;
						}

						break;

					case 4:
						if (currentAnimation != &idleUpAnim)
						{
							//idleUpAnim.Reset();
							currentAnimation = &idleUpAnim;
						}

						break;

					case 5:
						if (currentAnimation != &idleDownLeftAnim)
						{
							//idleDownLeftAnim.Reset();
							currentAnimation = &idleDownLeftAnim;
						}

						break;

					case 6:
						if (currentAnimation != &idleDownRightAnim)
						{
							//idleDownRightAnim.Reset();
							currentAnimation = &idleDownRightAnim;
						}

						break;

					case 7:
						if (currentAnimation != &idleUpLeftAnim)
						{
							//idleUpLeftAnim.Reset();
							currentAnimation = &idleUpLeftAnim;
						}

						break;

					case 8:
						if (currentAnimation != &idleUpRightAnim)
						{
							//idleUpRightAnim.Reset();
							currentAnimation = &idleUpRightAnim;
						}

						break;
					}

				}
			}

		}
		if (entityStatePlayer == GameState::InCombat)
		{
			showCombatHUD = true;


			if (entityTurnPlayer == TurnState::NONE)
			{
				counter = 0;
				iPoint NewPosition = position;
				collider->SetPos(position.x + 5, position.y - 56);
				//colliderFeet->SetPos(NewPosition.x + 5, NewPosition.y + 23);
				Player->body->SetLinearVelocity({ 0.0f,0.0f });
				
			}
			if (entityTurnPlayer == TurnState::StartOfTurn)
			{
				counter = 0;
				iPoint NewPosition = position;
				collider->SetPos(position.x + 5, position.y - 56);
				//colliderFeet->SetPos(NewPosition.x + 5, NewPosition.y + 23);
				Player->body->SetLinearVelocity({ 0.0f,0.0f });
				entityTurnPlayer = TurnState::MidOfTurn;
				playerAttacked = false;
			}
			if (entityTurnPlayer == TurnState::MidOfTurn)
			{
				
				
				if(app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_DOWN)
				{
					counter++;
					Player->body->SetLinearVelocity({ -45.0f,21.0f });
				}
				else Player->body->SetLinearVelocity({ 0.0f,0.0f });
				if (app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_DOWN)
				{
					counter++;
					Player->body->SetLinearVelocity({ 45.0f,-21.0f });
				}
				if (app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_DOWN)
				{
					counter++;
					Player->body->SetLinearVelocity({ 45.0f,21.0f });
				}
				if (app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_DOWN)
				{
					counter++;
					Player->body->SetLinearVelocity({ -45.0f,-21.0f });
				}

				if (app->input->keys[SDL_SCANCODE_DOWN] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_UP] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_RIGHT] == KeyState::KEY_IDLE
					&& app->input->keys[SDL_SCANCODE_LEFT] == KeyState::KEY_IDLE)
				{
					Player->body->SetLinearVelocity({ 0.0f,0.0f });
				}

				//If you press space bar while in combat you can go directly to the attack state
				if (app->input->keys[SDL_SCANCODE_SPACE] == KEY_DOWN)
				{
					Player->body->SetLinearVelocity({ 0.0f,0.0f });
					CounterForEnemySelection = -1;
					EnemySelectionBool = false;
					entityTurnPlayer = TurnState::FinishTurn;
				}

				if (counter > 6)
				{
					Player->body->SetLinearVelocity({ 0.0f,0.0f });
					CounterForEnemySelection = -1;
					EnemySelectionBool = false;
					entityTurnPlayer = TurnState::FinishTurn;
				}
			}
			if (entityTurnPlayer == TurnState::FinishTurn)
			{
				Player->body->SetLinearVelocity({ 0.0f,0.0f });

				//Looking position for the melee attack
				if (app->input->keys[SDL_SCANCODE_DOWN] == KEY_UP)
				{
					PlayerLookingPosition = 3;
				}
				if (app->input->keys[SDL_SCANCODE_UP] == KEY_UP)
				{
					PlayerLookingPosition = 4;
				}
				if (app->input->keys[SDL_SCANCODE_LEFT] == KEY_UP)
				{
					PlayerLookingPosition = 1;
				}
				if (app->input->keys[SDL_SCANCODE_RIGHT] == KEY_UP)
				{
					PlayerLookingPosition = 2;
				}

				switch (PlayerLookingPosition)
				{
				case 1:
					if (currentAnimation != &idleLeftAnim)
					{
						//idleLeftAnim.Reset();
						currentAnimation = &idleLeftAnim;
					}

					break;
				case 2:
					if (currentAnimation != &idleRightAnim)
					{
						//idleRightAnim.Reset();
						currentAnimation = &idleRightAnim;
					}

					break;

				case 3:
					if (currentAnimation != &idleDownAnim)
					{
						//idleDownAnim.Reset();
						currentAnimation = &idleDownAnim;
					}

					break;

				case 4:
					if (currentAnimation != &idleUpAnim)
					{
						//idleUpAnim.Reset();
						currentAnimation = &idleUpAnim;
					}

					break;
				default:
					break;
				}



				//Attack methodology, after attacking the player goes to wait turn
				if (app->input->keys[SDL_SCANCODE_X] == KeyState::KEY_UP)
				{
					
					if (CounterForEnemySelection < app->entity_manager->ListInCombat.count())
					{
						CounterForEnemySelection++;
					}
					if (CounterForEnemySelection >= app->entity_manager->ListInCombat.count())
					{
						CounterForEnemySelection = 0;
					}

					EnemySelectionBool = true;
					enemySelected = app->entity_manager->ListInCombat.At(CounterForEnemySelection)->data->position;
				}
				if (playerAttacked == true)
				{
					entityTurnPlayer = TurnState::WaitTurn;
				}
				
				if (EnemySelectionBool == true)
				{
					if (position.DistanceTo(enemySelected) <= EquipmentRange)
					{
						app->render->DrawTexture(selectedEnemy, enemySelected.x - 15, enemySelected.y - 5, NULL);
					}
					if (position.DistanceTo(enemySelected) > EquipmentRange)
					{
						app->render->DrawTexture(selectedEnemyNotInRange, enemySelected.x - 15, enemySelected.y - 5, NULL);
					}
				}

			}
			if (entityTurnPlayer == TurnState::WaitTurn)
			{
				iPoint NewPosition = position;
				Player->body->SetLinearVelocity({ 0.0f,0.0f });
				collider->SetPos(position.x + 5, position.y - 56);
				//colliderFeet->SetPos(NewPosition.x + 5, NewPosition.y + 23);
				counter = 0;

			}
		}
		//Escape Combat
		if (escapeCombat == true)
		{
			escapeCombatCounterToReset++;

			if ((escapeCombatCounterToReset / 300) % 2 == 0)
			{
				escapeCombat = false;
			}
		}

		if (playerHP <= 0)
		{
			/*invincibleDelay = 121;*/
			playerHP = 0;
			//app->audio->PlayFx(dead);
			destroyed = true;

		}
		if (destroyed == true)
		{
			if (destroyedDelay < 1)
			{
				//Mix_PauseMusic();

				app->audio->PlayFx(gameOver);
				//lives--;


			}
			Player->body->SetLinearVelocity({ 0, 0 });

			if (currentAnimation != &die)
			{
				die.Reset();
				currentAnimation = &die;
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

	if ((app->input->keys[SDL_SCANCODE_I] == KEY_DOWN) && app->player->destroyed == false && app->player->playerWin == false)
	{
		/*app->audio->PlayFx(paused);*/
		app->inventoryMenu->showInventory = !app->inventoryMenu->showInventory;
	}

	if ((app->input->keys[SDL_SCANCODE_M] == KEY_DOWN) && app->player->destroyed == false && app->player->playerWin == false)
	{
		/*app->audio->PlayFx(paused);*/
		app->mapMenu->showMapMenu = !app->mapMenu->showMapMenu;
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


		//SDL_Rect quad;
		//quad = { 5, 10, playerHP, 10 };

		//SDL_Rect quad2;
		//quad2 = { 5, 10, PlayerMaxHP, 10 };

		//SDL_Rect bgquad;
		//bgquad = { 3, 8, PlayerMaxHP+4, 14 };
		//app->render->DrawRectangle2(bgquad, 255, 255, 255, 255, 0.0f, true);
		//app->render->DrawRectangle2(quad2, 200, 200, 200, 255, 0.0f, true);
		////app->render->DrawRectangle(bgquad, 255, 255, 255, 165, true, true);
		//if (playerHP >= PlayerMaxHP)
		//{
		//	playerHP = PlayerMaxHP;
		//	app->render->DrawRectangle2(quad, 0, 255, 0, 255, 0.0f, true);
		//}
		//else if (playerHP > PlayerMaxHP/2)
		//{
		//	app->render->DrawRectangle2(quad, 120, 255, 0, 255, 0.0f, true);
		//}
		//else if (playerHP > PlayerMaxHP/5 && playerHP <= PlayerMaxHP/2)
		//{
		//	app->render->DrawRectangle2(quad, 255, 255, 0, 255, 0.0f, true);
		//}
		//else
		//{
		//	if ((playerFPS / 5) % 2 == 0)
		//	{
		//		app->render->DrawRectangle2(quad, 255, 0, 0, 255, 0.0f, true);
		//	}
		//	else
		//	{
		//		app->render->DrawRectangle2(quad, 255, 150, 0, 255, 0.0f, true);
		//	}

		//}
		

		/*app->render->DrawTexture2(characterHealth20, 0, 0, NULL);*/

		/*lowHPdelay++;

		app->render->DrawTexture2(characterHealth20, -60, -7, NULL);
		if ((lowHPdelay / 60) % 2 == 0) app->render->DrawTexture2(characterHealth20Grey, -60, -7, NULL);
		app->render->DrawTexture2(lowHealthGreyBg, 0, 0, NULL);
		app->audio->PlayFx(heartbeatFX, 0);*/

		//Interfaz movida al questManager para que se dibuje bien

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

			//app->render->DrawTexture2(gameOverScreen, 0, 0, NULL, 0.0f);

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
				app->sceneCave->Disable();
				app->sceneBase->Disable();
				app->sceneMotel->Disable();
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

		if(readingNote == true) app->render->DrawTexture2(doctorNote, 0, 0, NULL);

		if (usingComputer == true)
		{
			app->render->DrawTexture2(computerBG, 0, 0, NULL);

			//Aquí va la lógica del computer GUI:

			//Experiment (folder icon)
			
				//DAY 1 (notepad icon)
					//BACK (back arrow icon)
			
				//DAY 5 (notepad icon)
					//BACK (back arrow icon)
				
				//DAY 10 (notepad icon)
					//BACK (back arrow icon)
				
				//DAY 15 (notepad icon)
					//BACK (back arrow icon)
					//UNLOCK HARBOR.EXE (executable icon)

			//BACK (back arrow icon)
			
			if (returnComputerGUI->state == GuiControlState::NORMAL && returnComputerGUI->canClick == true) returnComputerGUI->SetTexture(returnComputer);
			returnComputerGUI->Draw(app->render);

			if (computerPhase == 0)
			{
				if (folderComputerGUI->state == GuiControlState::NORMAL && folderComputerGUI->canClick == true) folderComputerGUI->SetTexture(folderComputer);
				folderComputerGUI->Draw(app->render);
			}

			if (computerPhase == 1)
			{
				if (noteComputerDay1GUI->state == GuiControlState::NORMAL && noteComputerDay1GUI->canClick == true) noteComputerDay1GUI->SetTexture(noteComputerDay1);
				noteComputerDay1GUI->Draw(app->render);

				if (noteComputerDay5GUI->state == GuiControlState::NORMAL && noteComputerDay5GUI->canClick == true) noteComputerDay5GUI->SetTexture(noteComputerDay5);
				noteComputerDay5GUI->Draw(app->render);

				if (noteComputerDay10GUI->state == GuiControlState::NORMAL && noteComputerDay10GUI->canClick == true) noteComputerDay10GUI->SetTexture(noteComputerDay10);
				noteComputerDay10GUI->Draw(app->render);

				if (noteComputerDay15GUI->state == GuiControlState::NORMAL && noteComputerDay15GUI->canClick == true) noteComputerDay15GUI->SetTexture(noteComputerDay15);
				noteComputerDay15GUI->Draw(app->render);
			}

			if (computerPhase == 2 && note1 == true) 
			{
				app->render->DrawTexture2(noteDay1, 0, 0, NULL);
			}
			if (computerPhase == 2 && note5 == true)
			{
				app->render->DrawTexture2(noteDay5, 0, 0, NULL);
			}
			if (computerPhase == 2 && note10 == true)
			{
				app->render->DrawTexture2(noteDay10, 0, 0, NULL);
			}
			if (computerPhase == 2 && note15 == true)
			{
				app->render->DrawTexture2(noteDay15, 0, 0, NULL);
				if (computerExecutableGUI->state == GuiControlState::NORMAL && computerExecutableGUI->canClick == true) computerExecutableGUI->SetTexture(computerExecutable);
				computerExecutableGUI->Draw(app->render);
				//usingComputer = false;
			}
		}
		if (usingComputer == false)
		{
			computerPhase = 0;
		}
		
		return true;
	
}

bool ModulePlayer::CleanUp()
{
	app->tex->UnLoad(texture);
	app->tex->UnLoad(doctorNote);
	app->tex->UnLoad(computerBG);
	app->tex->UnLoad(gameOverScreen);
	app->tex->UnLoad(selectedEnemy);
	app->tex->UnLoad(selectedEnemyNotInRange);

	app->tex->UnLoad(noteDay1);
	app->tex->UnLoad(noteDay5);
	app->tex->UnLoad(noteDay10);
	app->tex->UnLoad(noteDay15);

	app->tex->UnLoad(returnComputer);
	app->tex->UnLoad(folderComputer);
	app->tex->UnLoad(computerExecutable);
	app->tex->UnLoad(noteComputerDay1);
	app->tex->UnLoad(noteComputerDay5);
	app->tex->UnLoad(noteComputerDay10);
	app->tex->UnLoad(noteComputerDay15);

	app->guiManager->DestroyGuiControl(41);
	app->guiManager->DestroyGuiControl(42);
	app->guiManager->DestroyGuiControl(43);
	app->guiManager->DestroyGuiControl(44);
	app->guiManager->DestroyGuiControl(45);
	app->guiManager->DestroyGuiControl(46);
	app->guiManager->DestroyGuiControl(47);

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
	//entranceID = data.child("atributes").attribute("entranceID").as_int();
	//app->sceneMainMap->sceneMainMap = data.child("atributes").attribute("sceneMainMap").as_bool();
	//app->sceneCave->sceneCave = data.child("atributes").attribute("sceneCave").as_bool();
	//app->sceneBase->sceneBase = data.child("atributes").attribute("sceneBase").as_bool();

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
	playerAtributes.append_attribute("entranceID") = entranceID;
	playerAtributes.append_attribute("sceneMainMap") = app->sceneMainMap->sceneMainMap;
	playerAtributes.append_attribute("sceneCave") = app->sceneCave->sceneCave;
	playerAtributes.append_attribute("sceneBase") = app->sceneBase->sceneBase;

	return true;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (app->sceneCave->godMode == false && app->sceneMainMap->godMode == false && destroyed == false && playerWin == false)
	{
		if ((c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::BOSS_ATTACK ))
		{
			app->audio->PlayFx(playerHurtSound, 0);
			playerHP -= 10;

			if (app->player->playerHP > app->player->PlayerMaxHP / 5 && app->player->playerHP <= app->player->PlayerMaxHP / 2.5f)
			{
				app->audio->PlayFx(heartbeatFX, 0);
			}
		}

		if ((c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::BOSS_ATTACK))
		{
			app->audio->PlayFx(playerHurtSound, 0);
			playerHP -= 15;

			if (app->player->playerHP > app->player->PlayerMaxHP / 5 && app->player->playerHP <= app->player->PlayerMaxHP / 2.5f)
			{
				app->audio->PlayFx(heartbeatFX, 0);
			}
		}

		if ((c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::BOSS_ATTACK_2))
		{
			app->audio->PlayFx(playerHurtSound, 0);
			playerHP -= 30;

			if (app->player->playerHP > app->player->PlayerMaxHP / 5 && app->player->playerHP <= app->player->PlayerMaxHP / 2.5f)
			{
				app->audio->PlayFx(heartbeatFX, 0);
			}
		}

		if ((c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY_RANGED_ATTACK)) /*&& invincibleDelay >= 120)*/
		{
			app->audio->PlayFx(playerHurtSound, 0);
			playerHP -= 10;
			
			if (app->player->playerHP > app->player->PlayerMaxHP / 5 && app->player->playerHP <= app->player->PlayerMaxHP / 2.5f)
			{
				app->audio->PlayFx(heartbeatFX, 0);
			}
		}

		/*if ((c1->type == Collider::Type::PLAYER_ATTACK && c2->type == Collider::Type::ENEMY))
		{

			playerHP -= 10;
			
		}*/

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
		
		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::INSTANT_DEATH)
		{
			playerHP -= 250;
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

		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::ENABLE_FINAL_BATTLE)
		{
			//playerWin = true;

			if (inBossBatle == false)
			{
				inBossBatle = true;
				activateFinalBoss = true;
				app->audio->ChangeMusic(STORY_FINAL_BOSS_APPEARS, 0.0f, 0.0f);

			}
		}

		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::ENABLE_BOSS_1)
		{
			if (app->questManager->mainQuestID == LOOK_FOR_THE_COMPUTER_2 && inBossBatle == false && boss1Dead == false)
			{
				inBossBatle = true;
				app->audio->ChangeMusic(BOSS_1, 0.0f, 0.0f);
				
			}
		}

		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::ENABLE_BOSS_2)
		{
			if (app->questManager->mainQuestID == KILL_THE_PATIENT_ZERO_3 && inBossBatle == false && boss2Dead == false)
			{
				inBossBatle = true;
				app->audio->ChangeMusic(BOSS_2, 0.0f, 0.0f);

			}
		}

		if ((c1->type == Collider::Type::PLAYER) && c2->type == Collider::Type::ENABLE_BOSS_3)
		{
			if (boss3Dead == false && inBossBatle == false)
			{
				inBossBatle = true;
				app->audio->ChangeMusic(BOSS_3, 0.0f, 0.0f);

			}
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::DOCTOR_NOTE_MESSAGE)
		{
			if (layerZeroReveal == false)
			{
				layerZeroReveal = true;
			}

			if (app->input->keys[SDL_SCANCODE_X] == KeyState::KEY_DOWN)
			{
				readingNote = !readingNote;
				app->audio->PlayFx(itemGrab);
			}
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::BASE_COMPUTER)
		{
			if (app->input->keys[SDL_SCANCODE_X] == KeyState::KEY_DOWN)
			{
				if (usingComputer == false)
				{
					usingComputer = true;
					app->audio->PlayFx(computerOn);
				}
				else if (usingComputer == true)
				{
					usingComputer = false;
					app->audio->PlayFx(computerOff);
				}
			}
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::TNT_SWITCH)
		{
			if (rock1Removed == false)
			{
				if (app->input->keys[SDL_SCANCODE_X] == KeyState::KEY_DOWN)
				{
					app->audio->PlayFx(explosionFx_far);
					rock1Removed = true;
				}
			}
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::TNT_SWITCH2)
		{
			if (rock2Removed == false)
			{
				if (app->input->keys[SDL_SCANCODE_X] == KeyState::KEY_DOWN)
				{
					app->audio->PlayFx(explosionFx_far);
					rock2Removed = true;
				}
			}
		}
		
		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::DOOR_KEY_READER)
		{
			if (app->input->keys[SDL_SCANCODE_X] == KeyState::KEY_DOWN && baseUnlock == false && app->questManager->mainQuestID == LOOK_FOR_THE_COMPUTER_2)
			{
				app->audio->ChangeMusic(TENSION_PUZZLE_1, 0.2f, 0.2f);
				app->audio->PlayFx(alarmCardReaderFx);
				app->questManager->secondaryQuestID = ACTIVATE_SWITCHES;
				baseUnlock = true;

				app->entity_manager->AddEntity(EntityType::ZOMBIE_VOLATILE, 1516, 3040);
				app->entity_manager->AddEntity(EntityType::ZOMBIE_VOLATILE, 3367, 2014);
				app->entity_manager->AddEntity(EntityType::ZOMBIE_VOLATILE, 4327, 2757);
				app->entity_manager->AddEntity(EntityType::ZOMBIE_VOLATILE, 3295, 3495);


			}

			if (app->input->keys[SDL_SCANCODE_X] == KeyState::KEY_DOWN) app->questManager->descriptionCounter = 0;
			
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::SWITCH)
		{

		}
	}
}

iPoint ModulePlayer::GetLastPosition()
{
	iPoint NewPosition = position;

	return NewPosition;
}


void ModulePlayer::RangedAttack()
{
	//Add logic for ranged attack
	if (EnemySelectionBool == true)
	{
		if (position.DistanceTo(enemySelected) <= EquipmentRange)
		{
			app->entity_manager->ListInCombat.At(CounterForEnemySelection)->data->EntityHP -= EquipmentDamage;
			playerAttacked = true;
		}
		if (position.DistanceTo(enemySelected) > EquipmentRange)
		{
			//Not in range so the player misses his turn
			playerAttacked = true;
		}
	}
	if (EnemySelectionBool == false)
	{

	}
	
	
	
}
void ModulePlayer::MeleeAttack()
{
	//Add logic for attack

	switch (PlayerLookingPosition)
	{
	case 1:
		app->particles->AddParticle(app->particles->playerAttack, app->player->position.x - 30, app->player->position.y - 20, Collider::Type::PLAYER_ATTACK);
		playerAttacked = true;
		break;
	case 2:
		app->particles->AddParticle(app->particles->playerAttack, app->player->position.x + 30, app->player->position.y - 20, Collider::Type::PLAYER_ATTACK);
		playerAttacked = true;
		break;

	case 3:
		app->particles->AddParticle(app->particles->playerAttack, app->player->position.x + 10, app->player->position.y + 20, Collider::Type::PLAYER_ATTACK);
		playerAttacked = true;
		break;

	case 4:
		app->particles->AddParticle(app->particles->playerAttack, app->player->position.x + 10, app->player->position.y -60, Collider::Type::PLAYER_ATTACK);
		playerAttacked = true;
		break;

	default:
		break;
	}
	
}
bool ModulePlayer::OnGuiMouseClickEvent(GuiControl* control) {
	switch (control->type)
	{
	case GuiControlType::BUTTON:
	{
		//Checks the GUI element ID
		
		
			if (control->id == 41 && returnComputerGUI->canClick == true)
			{
				app->audio->PlayFx(computerClick, 0);
				if (computerPhase > 0) computerPhase--;
				note1 = false;
				note5 = false;
				note10 = false;
				note15 = false;
			}
			if (control->id == 42 && computerExecutableGUI->canClick == true)
			{
				app->audio->PlayFx(computerClick, 0);

				//Logica del harbor.exe	
				if (harborUnlock == false)
				{
					app->audio->PlayFx(harborUnlockFx, 0);
					app->questManager->SwitchMainQuest(KILL_THE_PATIENT_ZERO_3);
					harborUnlock = true;
				}
			}
			if (control->id == 43 && noteComputerDay15GUI->canClick == true)
			{
				app->audio->PlayFx(computerClick, 0);
				computerPhase = 2;
				note15 = true;
			}
			if (control->id == 44 && folderComputerGUI->canClick == true)
			{
				app->audio->PlayFx(computerClick, 0);
				computerPhase = 1;
			}
			if (control->id == 45 && noteComputerDay1GUI->canClick == true)
			{
				app->audio->PlayFx(computerClick, 0);
				//Nota 1
				computerPhase = 2;
				note1 = true;
			}
			if (control->id == 46 && noteComputerDay5GUI->canClick == true)
			{
				app->audio->PlayFx(computerClick, 0);
				//Nota 5
				computerPhase = 2;
				note5 = true;
			}
			if (control->id == 47 && noteComputerDay10GUI->canClick == true)
			{
				app->audio->PlayFx(computerClick, 0);
				//Nota 10
				computerPhase = 2;
				note10 = true;
			}
		
		



	default: break;
	}
	}

	return true;
}