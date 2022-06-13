#include "Final_Boss.h"

#include "App.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "EntityManager.h"
//#include "ModuleParticles.h"
#include "Audio.h"
#include "Point.h"
#include "DynArray.h"
#include "Input.h"
#include "Map.h"
#include "SceneMainMap.h"
#include "Render.h"
#include "Textures.h"
#include "Log.h"
#include "ModulePhysics.h"
#include "ModuleParticles.h"

#include "Defs.h"


Final_Boss::Final_Boss(int x,int y) : Entity(x,y)
{	

	EntityHP = 1;
	EntityAP = 5;
	EntityMP = 3;
	entityState = GameState::OutOfCombat;
	entityTurn = TurnState::NONE;
	counter = 0;
	EntityKillable = true;
	//HERE WE ADD THE ANIMATIONS WITH GIMP
	
		//IDLE

	idleRightAnim_Enemy1.PushBack({ 0, 4151, 180, 180 });
	idleRightAnim_Enemy1.loop = true;
	idleRightAnim_Enemy1.speed = 0.04f;

	idleLeftAnim_Enemy1.PushBack({ 0, 3429, 180, 180 });
	idleLeftAnim_Enemy1.loop = true;
	idleLeftAnim_Enemy1.speed = 0.04f;

	idleDownAnim_Enemy1.PushBack({ 0, 4512, 180, 180 });  //idle_enemy
	idleDownAnim_Enemy1.loop = true;
	idleDownAnim_Enemy1.speed = 0.04f;

	idleUpAnim_Enemy1.PushBack({ 0, 3790, 180, 180 });
	idleUpAnim_Enemy1.loop = true;
	idleUpAnim_Enemy1.speed = 0.04f;

	idleUpLeftAnim_Enemy1.PushBack({ 0, 3610, 180, 180 });
	idleUpLeftAnim_Enemy1.loop = true;
	idleUpLeftAnim_Enemy1.speed = 0.04f;

	idleUpRightAnim_Enemy1.PushBack({ 0, 3971, 180, 180 });
	idleUpRightAnim_Enemy1.loop = true;
	idleUpRightAnim_Enemy1.speed = 0.04f;

	idleDownLeftAnim_Enemy1.PushBack({ 0, 3249, 180, 180 });
	idleDownLeftAnim_Enemy1.loop = true;
	idleDownLeftAnim_Enemy1.speed = 0.04f;

	idleDownRightAnim_Enemy1.PushBack({ 0, 4332, 180, 180 });
	idleDownRightAnim_Enemy1.loop = true;
	idleDownRightAnim_Enemy1.speed = 0.04f;



	//WALK


	rightWalkAnim_Enemy1.PushBack({ 180, 4151, 180, 180 });
	rightWalkAnim_Enemy1.PushBack({ 361, 4151, 180, 180 });
	rightWalkAnim_Enemy1.PushBack({ 541, 4151, 180, 180 });
	rightWalkAnim_Enemy1.PushBack({ 722, 4151, 180, 180 });
	rightWalkAnim_Enemy1.PushBack({ 902, 4151, 180, 180 });
	rightWalkAnim_Enemy1.PushBack({ 1083, 4151, 180, 180 });
	rightWalkAnim_Enemy1.PushBack({ 1263, 4151, 180, 180 });
	rightWalkAnim_Enemy1.PushBack({ 1444, 4151, 180, 180 });
	rightWalkAnim_Enemy1.PushBack({ 1624, 4151, 180, 180 });
	rightWalkAnim_Enemy1.PushBack({ 1805, 4151, 180, 180 });
	rightWalkAnim_Enemy1.PushBack({ 1985, 4151, 180, 180 });
	rightWalkAnim_Enemy1.PushBack({ 2166, 4151, 180, 180 });
	rightWalkAnim_Enemy1.PushBack({ 2346, 4151, 180, 180 });
	rightWalkAnim_Enemy1.PushBack({ 2527, 4151, 180, 180 });
	rightWalkAnim_Enemy1.PushBack({ 2707, 4151, 180, 180 });
	rightWalkAnim_Enemy1.PushBack({ 2888, 4151, 180, 180 });
	rightWalkAnim_Enemy1.PushBack({ 3068, 4151, 180, 180 });
	rightWalkAnim_Enemy1.PushBack({ 3249, 4151, 180, 180 });
	rightWalkAnim_Enemy1.loop = true;
	rightWalkAnim_Enemy1.speed = 0.05f;


	leftWalkAnim_Enemy1.PushBack({ 180, 3429, 180, 180 });
	leftWalkAnim_Enemy1.PushBack({ 361, 3429, 180, 180 });
	leftWalkAnim_Enemy1.PushBack({ 541, 3429, 180, 180 });
	leftWalkAnim_Enemy1.PushBack({ 722, 3429, 180, 180 });
	leftWalkAnim_Enemy1.PushBack({ 902, 3429, 180, 180 });
	leftWalkAnim_Enemy1.PushBack({ 1083, 3429, 180, 180 });
	leftWalkAnim_Enemy1.PushBack({ 1263, 3429, 180, 180 });
	leftWalkAnim_Enemy1.PushBack({ 1444, 3429, 180, 180 });
	leftWalkAnim_Enemy1.PushBack({ 1624, 3429, 180, 180 });
	leftWalkAnim_Enemy1.PushBack({ 1805, 3429, 180, 180 });
	leftWalkAnim_Enemy1.PushBack({ 1985, 3429, 180, 180 });
	leftWalkAnim_Enemy1.PushBack({ 2166, 3429, 180, 180 });
	leftWalkAnim_Enemy1.PushBack({ 2346, 3429, 180, 180 });
	leftWalkAnim_Enemy1.PushBack({ 2527, 3429, 180, 180 });
	leftWalkAnim_Enemy1.PushBack({ 2707, 3429, 180, 180 });
	leftWalkAnim_Enemy1.PushBack({ 2888, 3429, 180, 180 });
	leftWalkAnim_Enemy1.PushBack({ 3068, 3429, 180, 180 });
	leftWalkAnim_Enemy1.PushBack({ 3249, 3429, 180, 180 });
	leftWalkAnim_Enemy1.loop = true;
	leftWalkAnim_Enemy1.speed = 0.05f;


	downWalkAnim_Enemy1.PushBack({ 180, 4512, 180, 180 });
	downWalkAnim_Enemy1.PushBack({ 361, 4512, 180, 180 });
	downWalkAnim_Enemy1.PushBack({ 541, 4512, 180, 180 });
	downWalkAnim_Enemy1.PushBack({ 722, 4512, 180, 180 });
	downWalkAnim_Enemy1.PushBack({ 902, 4512, 180, 180 });
	downWalkAnim_Enemy1.PushBack({ 1083, 4512, 180, 180 });
	downWalkAnim_Enemy1.PushBack({ 1263, 4512, 180, 180 });
	downWalkAnim_Enemy1.PushBack({ 1444, 4512, 180, 180 });
	downWalkAnim_Enemy1.PushBack({ 1624, 4512, 180, 180 });
	downWalkAnim_Enemy1.PushBack({ 1805, 4512, 180, 180 });
	downWalkAnim_Enemy1.PushBack({ 1985, 4512, 180, 180 });
	downWalkAnim_Enemy1.PushBack({ 2166, 4512, 180, 180 });
	downWalkAnim_Enemy1.PushBack({ 2346, 4512, 180, 180 });
	downWalkAnim_Enemy1.PushBack({ 2527, 4512, 180, 180 });
	downWalkAnim_Enemy1.PushBack({ 2707, 4512, 180, 180 });
	downWalkAnim_Enemy1.PushBack({ 2888, 4512, 180, 180 });
	downWalkAnim_Enemy1.PushBack({ 3068, 4512, 180, 180 });
	downWalkAnim_Enemy1.PushBack({ 3249, 4512, 180, 180 });
	downWalkAnim_Enemy1.loop = true;
	downWalkAnim_Enemy1.speed = 0.05f;


	upWalkAnim_Enemy1.PushBack({ 180, 3790, 180, 180 });
	upWalkAnim_Enemy1.PushBack({ 361, 3790, 180, 180 });
	upWalkAnim_Enemy1.PushBack({ 541, 3790, 180, 180 });
	upWalkAnim_Enemy1.PushBack({ 722, 3790, 180, 180 });
	upWalkAnim_Enemy1.PushBack({ 902, 3790, 180, 180 });
	upWalkAnim_Enemy1.PushBack({ 1083, 3790, 180, 180 });
	upWalkAnim_Enemy1.PushBack({ 1263, 3790, 180, 180 });
	upWalkAnim_Enemy1.PushBack({ 1444, 3790, 180, 180 });
	upWalkAnim_Enemy1.PushBack({ 1624, 3790, 180, 180 });
	upWalkAnim_Enemy1.PushBack({ 1805, 3790, 180, 180 });
	upWalkAnim_Enemy1.PushBack({ 1985, 3790, 180, 180 });
	upWalkAnim_Enemy1.PushBack({ 2166, 3790, 180, 180 });
	upWalkAnim_Enemy1.PushBack({ 2346, 3790, 180, 180 });
	upWalkAnim_Enemy1.PushBack({ 2527, 3790, 180, 180 });
	upWalkAnim_Enemy1.PushBack({ 2707, 3790, 180, 180 });
	upWalkAnim_Enemy1.PushBack({ 2888, 3790, 180, 180 });
	upWalkAnim_Enemy1.PushBack({ 3068, 3790, 180, 180 });
	upWalkAnim_Enemy1.PushBack({ 3249, 3790, 180, 180 });
	upWalkAnim_Enemy1.loop = true;
	upWalkAnim_Enemy1.speed = 0.05f;


	rightDownWalkAnim_Enemy1.PushBack({ 180, 4332, 180, 180 });
	rightDownWalkAnim_Enemy1.PushBack({ 361, 4332, 180, 180 });
	rightDownWalkAnim_Enemy1.PushBack({ 541, 4332, 180, 180 });
	rightDownWalkAnim_Enemy1.PushBack({ 722, 4332, 180, 180 });
	rightDownWalkAnim_Enemy1.PushBack({ 902, 4332, 180, 180 });
	rightDownWalkAnim_Enemy1.PushBack({ 1083, 4332, 180, 180 });
	rightDownWalkAnim_Enemy1.PushBack({ 1263, 4332, 180, 180 });
	rightDownWalkAnim_Enemy1.PushBack({ 1444, 4332, 180, 180 });
	rightDownWalkAnim_Enemy1.PushBack({ 1624, 4332, 180, 180 });
	rightDownWalkAnim_Enemy1.PushBack({ 1805, 4332, 180, 180 });
	rightDownWalkAnim_Enemy1.PushBack({ 1985, 4332, 180, 180 });
	rightDownWalkAnim_Enemy1.PushBack({ 2166, 4332, 180, 180 });
	rightDownWalkAnim_Enemy1.PushBack({ 2346, 4332, 180, 180 });
	rightDownWalkAnim_Enemy1.PushBack({ 2527, 4332, 180, 180 });
	rightDownWalkAnim_Enemy1.PushBack({ 2707, 4332, 180, 180 });
	rightDownWalkAnim_Enemy1.PushBack({ 2888, 4332, 180, 180 });
	rightDownWalkAnim_Enemy1.PushBack({ 3068, 4332, 180, 180 });
	rightDownWalkAnim_Enemy1.PushBack({ 3249, 4332, 180, 180 });
	rightDownWalkAnim_Enemy1.loop = true;
	rightDownWalkAnim_Enemy1.speed = 0.05f;


	leftDownWalkAnim_Enemy1.PushBack({ 180, 3249, 180, 180 });
	leftDownWalkAnim_Enemy1.PushBack({ 361, 3249, 180, 180 });
	leftDownWalkAnim_Enemy1.PushBack({ 541, 3249, 180, 180 });
	leftDownWalkAnim_Enemy1.PushBack({ 722, 3249, 180, 180 });
	leftDownWalkAnim_Enemy1.PushBack({ 902, 3249, 180, 180 });
	leftDownWalkAnim_Enemy1.PushBack({ 1083, 3249, 180, 180 });
	leftDownWalkAnim_Enemy1.PushBack({ 1263, 3249, 180, 180 });
	leftDownWalkAnim_Enemy1.PushBack({ 1444, 3249, 180, 180 });
	leftDownWalkAnim_Enemy1.PushBack({ 1624, 3249, 180, 180 });
	leftDownWalkAnim_Enemy1.PushBack({ 1805, 3249, 180, 180 });
	leftDownWalkAnim_Enemy1.PushBack({ 1985, 3249, 180, 180 });
	leftDownWalkAnim_Enemy1.PushBack({ 2166, 3249, 180, 180 });
	leftDownWalkAnim_Enemy1.PushBack({ 2346, 3249, 180, 180 });
	leftDownWalkAnim_Enemy1.PushBack({ 2527, 3249, 180, 180 });
	leftDownWalkAnim_Enemy1.PushBack({ 2707, 3249, 180, 180 });
	leftDownWalkAnim_Enemy1.PushBack({ 2888, 3249, 180, 180 });
	leftDownWalkAnim_Enemy1.PushBack({ 3068, 3249, 180, 180 });
	leftDownWalkAnim_Enemy1.PushBack({ 3249, 3249, 180, 180 });
	leftDownWalkAnim_Enemy1.loop = true;
	leftDownWalkAnim_Enemy1.speed = 0.05f;


	rightUpWalkAnim_Enemy1.PushBack({ 180, 3971, 180, 180 });
	rightUpWalkAnim_Enemy1.PushBack({ 361, 3971, 180, 180 });
	rightUpWalkAnim_Enemy1.PushBack({ 541, 3971, 180, 180 });
	rightUpWalkAnim_Enemy1.PushBack({ 722, 3971, 180, 180 });
	rightUpWalkAnim_Enemy1.PushBack({ 902, 3971, 180, 180 });
	rightUpWalkAnim_Enemy1.PushBack({ 1083, 3971, 180, 180 });
	rightUpWalkAnim_Enemy1.PushBack({ 1263, 3971, 180, 180 });
	rightUpWalkAnim_Enemy1.PushBack({ 1444, 3971, 180, 180 });
	rightUpWalkAnim_Enemy1.PushBack({ 1624, 3971, 180, 180 });
	rightUpWalkAnim_Enemy1.PushBack({ 1805, 3971, 180, 180 });
	rightUpWalkAnim_Enemy1.PushBack({ 1985, 3971, 180, 180 });
	rightUpWalkAnim_Enemy1.PushBack({ 2166, 3971, 180, 180 });
	rightUpWalkAnim_Enemy1.PushBack({ 2346, 3971, 180, 180 });
	rightUpWalkAnim_Enemy1.PushBack({ 2527, 3971, 180, 180 });
	rightUpWalkAnim_Enemy1.PushBack({ 2707, 3971, 180, 180 });
	rightUpWalkAnim_Enemy1.PushBack({ 2888, 3971, 180, 180 });
	rightUpWalkAnim_Enemy1.PushBack({ 3068, 3971, 180, 180 });
	rightUpWalkAnim_Enemy1.PushBack({ 3249, 3971, 180, 180 });
	rightUpWalkAnim_Enemy1.loop = true;
	rightUpWalkAnim_Enemy1.speed = 0.05f;


	leftUpWalkAnim_Enemy1.PushBack({ 180, 3610, 180, 180 });
	leftUpWalkAnim_Enemy1.PushBack({ 361, 3610, 180, 180 });
	leftUpWalkAnim_Enemy1.PushBack({ 541, 3610, 180, 180 });
	leftUpWalkAnim_Enemy1.PushBack({ 722, 3610, 180, 180 });
	leftUpWalkAnim_Enemy1.PushBack({ 902, 3610, 180, 180 });
	leftUpWalkAnim_Enemy1.PushBack({ 1083, 3610, 180, 180 });
	leftUpWalkAnim_Enemy1.PushBack({ 1263, 3610, 180, 180 });
	leftUpWalkAnim_Enemy1.PushBack({ 1444, 3610, 180, 180 });
	leftUpWalkAnim_Enemy1.PushBack({ 1624, 3610, 180, 180 });
	leftUpWalkAnim_Enemy1.PushBack({ 1805, 3610, 180, 180 });
	leftUpWalkAnim_Enemy1.PushBack({ 1985, 3610, 180, 180 });
	leftUpWalkAnim_Enemy1.PushBack({ 2166, 3610, 180, 180 });
	leftUpWalkAnim_Enemy1.PushBack({ 2346, 3610, 180, 180 });
	leftUpWalkAnim_Enemy1.PushBack({ 2527, 3610, 180, 180 });
	leftUpWalkAnim_Enemy1.PushBack({ 2707, 3610, 180, 180 });
	leftUpWalkAnim_Enemy1.PushBack({ 2888, 3610, 180, 180 });
	leftUpWalkAnim_Enemy1.PushBack({ 3068, 3610, 180, 180 });
	leftUpWalkAnim_Enemy1.PushBack({ 3249, 3610, 180, 180 });
	leftUpWalkAnim_Enemy1.loop = true;
	leftUpWalkAnim_Enemy1.speed = 0.05f;


	//ATTACK

	//DIE

	rightDieAnim_Enemy1.PushBack({ 180, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 361, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 541, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 722, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 902, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 1083, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 1263, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 1444, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 1624, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 1805, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 1985, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 2166, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 2346, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 2527, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 2707, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 2888, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 3068, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 3249, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 3429, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 3610, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 3790, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 3971, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 4151, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 4332, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 4512, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 4693, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 4873, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 5053, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 5234, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 5414, 902, 180, 180 });
	rightDieAnim_Enemy1.PushBack({ 5595, 902, 180, 180 });
	rightDieAnim_Enemy1.loop = true;
	rightDieAnim_Enemy1.speed = 0.05f;

	leftDieAnim_Enemy1.PushBack({ 180, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 361, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 541, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 722, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 902, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 1083, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 1263, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 1444, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 1624, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 1805, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 1985, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 2166, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 2346, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 2527, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 2707, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 2888, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 3068, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 3249, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 3429, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 3610, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 3790, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 3971, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 4151, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 4332, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 4512, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 4693, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 4873, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 5053, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 5234, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 5414, 180, 180, 180 });
	leftDieAnim_Enemy1.PushBack({ 5595, 180, 180, 180 });
	leftDieAnim_Enemy1.loop = true;
	leftDieAnim_Enemy1.speed = 0.05f;

	downDieAnim_Enemy1.PushBack({ 180, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 361, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 541, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 722, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 902, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 1083, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 1263, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 1444, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 1624, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 1805, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 1985, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 2166, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 2346, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 2527, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 2707, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 2888, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 3068, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 3249, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 3429, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 3610, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 3790, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 3971, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 4151, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 4332, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 4512, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 4693, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 4873, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 5053, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 5234, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 5414, 1263, 180, 180 });
	downDieAnim_Enemy1.PushBack({ 5595, 1263, 180, 180 });
	downDieAnim_Enemy1.loop = true;
	downDieAnim_Enemy1.speed = 0.05f;

	upDieAnim_Enemy1.PushBack({ 180, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 361, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 541, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 722, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 902, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 1083, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 1263, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 1444, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 1624, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 1805, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 1985, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 2166, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 2346, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 2527, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 2707, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 2888, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 3068, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 3249, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 3429, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 3610, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 3790, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 3971, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 4151, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 4332, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 4512, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 4693, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 4873, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 5053, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 5234, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 5414, 541, 180, 180 });
	upDieAnim_Enemy1.PushBack({ 5595, 541, 180, 180 });
	upDieAnim_Enemy1.loop = true;
	upDieAnim_Enemy1.speed = 0.05f;

	rightDownDieAnim_Enemy1.PushBack({ 180, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 361, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 541, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 722, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 902, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 1083, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 1263, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 1444, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 1624, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 1805, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 1985, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 2166, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 2346, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 2527, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 2707, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 2888, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 3068, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 3249, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 3429, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 3610, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 3790, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 3971, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 4151, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 4332, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 4512, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 4693, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 4873, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 5053, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 5234, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 5414, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.PushBack({ 5595, 1083, 180, 180 });
	rightDownDieAnim_Enemy1.loop = true;
	rightDownDieAnim_Enemy1.speed = 0.05f;

	leftDownDieAnim_Enemy1.PushBack({ 180, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 361, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 541, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 722, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 902, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 1083, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 1263, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 1444, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 1624, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 1805, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 1985, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 2166, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 2346, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 2527, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 2707, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 2888, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 3068, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 3249, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 3429, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 3610, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 3790, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 3971, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 4151, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 4332, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 4512, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 4693, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 4873, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 5053, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 5234, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 5414, 0, 180, 180 });
	leftDownDieAnim_Enemy1.PushBack({ 5595, 0, 180, 180 });
	leftDownDieAnim_Enemy1.loop = true;
	leftDownDieAnim_Enemy1.speed = 0.05f;

	rightUpDieAnim_Enemy1.PushBack({ 180, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 361, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 541, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 722, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 902, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 1083, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 1263, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 1444, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 1624, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 1805, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 1985, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 2166, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 2346, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 2527, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 2707, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 2888, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 3068, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 3249, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 3429, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 3610, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 3790, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 3971, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 4151, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 4332, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 4512, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 4693, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 4873, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 5053, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 5234, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 5414, 722, 180, 180 });
	rightUpDieAnim_Enemy1.PushBack({ 5595, 722, 180, 180 });
	rightUpDieAnim_Enemy1.loop = true;
	rightUpDieAnim_Enemy1.speed = 0.05f;

	leftUpDieAnim_Enemy1.PushBack({ 180, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 361, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 541, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 722, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 902, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 1083, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 1263, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 1444, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 1624, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 1805, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 1985, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 2166, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 2346, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 2527, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 2707, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 2888, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 3068, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 3249, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 3429, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 3610, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 3790, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 3971, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 4151, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 4332, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 4512, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 4693, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 4873, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 5053, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 5234, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 5414, 361, 180, 180 });
	leftUpDieAnim_Enemy1.PushBack({ 5595, 361, 180, 180 });
	leftUpDieAnim_Enemy1.loop = true;
	leftUpDieAnim_Enemy1.speed = 0.05f;

	

	position.x = x;
	position.y = y;

	collider = app->collisions->AddCollider({ position.x, position.y - 46, 25, 56 }, Collider::Type::ENEMY, (Module*)app->entity_manager);

	Standart_Zombie_List.add(app->physics->CreateWalkingEnemyBox(position.x, position.y, 25, 10));
	
	counter = 0;
	
}

void Final_Boss::Update(float dt)
{
	//ADD THE PATHFINDING LOGIC FOR MOVEMENT

	if (app->player->pauseMenu == true)
	{
		iPoint NewPosition = position;
		collider->SetPos(NewPosition.x, NewPosition.y - 46);
		Standart_Zombie_List.end->data->GetPosition(NewPosition.x, NewPosition.y);
		currentAnim = &idleDownAnim_Enemy1;
		currentAnim->loop = false;

	}
	if (app->player->pauseMenu == false)
	{
		if (EntityHP == 0)
		{
			SetToDelete();
		}

		//Escape Combat
		//if (app->player->escapeCombat == true)
		//{
		//	entityState = GameState::OutOfCombat;
		//	entityTurn = TurnState::NONE;
		//}

		//
		//if (entityState == GameState::OutOfCombat)
		//{
		//	//move normally
		//	
		//	

		//	

		//}
		//
		//if (entityState == GameState::InCombat)
		//{
		//	
		//	if (EntityHP > 0)
		//	{
		//		if (entityTurn == TurnState::NONE)
		//		{
		//			//Assigning order of turns
		//			
		//		}
		//		if (entityTurn == TurnState::StartOfTurn)
		//		{
		//			

		//			entityTurn = TurnState::MidOfTurn;

		//		}
		//		if (entityTurn == TurnState::MidOfTurn)
		//		{

		//			
		//			if (counter == 150) entityTurn = TurnState::FinishTurn;

		//		}
		//		if (entityTurn == TurnState::FinishTurn)
		//		{
		//			//Change turn from enemy to player turn still have to develop a way to do it correctly



		//			entityTurn = TurnState::WaitTurn;
		//			

		//		}
		//		if (entityTurn == TurnState::WaitTurn)
		//		{
		//			counter = 0;
		//			
		//			currentAnim->loop = true;
		//
		//		}
		//		


		//	}
		//		

		//	
		//	
		//}
		
		if (app->player->activateFinalBoss == true)
		{
			app->player->finalBossPhaseCounter++;
			counter++;



		}
		
		currentAnim->Update();
	}
	
	
}



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