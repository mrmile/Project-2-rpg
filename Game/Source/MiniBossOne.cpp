#include "MiniBossOne.h"

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
#include "InventoryMenu.h"

#include "Defs.h"

Mini_Boss_One::Mini_Boss_One(int x, int y) : Entity(x, y)
{
	MaxHp = 40;
	EntityHP = MaxHp;
	EntityAP = 8;
	EntityMP = 5;
	entityState = GameState::OutOfCombat;
	entityTurn = TurnState::NONE;
	counter = 0;
	EntityKillable = true;
	//HERE WE ADD THE ANIMATIONS WITH GIMP

	//IDLE

	idleRightAnim_Enemy1.PushBack({ 3072, 512, 128, 128 });
	idleRightAnim_Enemy1.PushBack({ 3200, 512, 128, 128 });
	idleRightAnim_Enemy1.PushBack({ 3328, 512, 128, 128 });
	idleRightAnim_Enemy1.PushBack({ 3456, 512, 128, 128 });
	idleRightAnim_Enemy1.PushBack({ 3200, 512, 128, 128 });
	idleRightAnim_Enemy1.PushBack({ 3072, 512, 128, 128 });
	idleRightAnim_Enemy1.loop = true;
	idleRightAnim_Enemy1.speed = 0.05f;

	idleLeftAnim_Enemy1.PushBack({ 3072, 0, 128, 128 });
	idleLeftAnim_Enemy1.PushBack({ 3200, 0, 128, 128 });
	idleLeftAnim_Enemy1.PushBack({ 3328, 0, 128, 128 });
	idleLeftAnim_Enemy1.PushBack({ 3456, 0, 128, 128 });
	idleLeftAnim_Enemy1.PushBack({ 3200, 0, 128, 128 });
	idleLeftAnim_Enemy1.PushBack({ 3072, 0, 128, 128 });
	idleLeftAnim_Enemy1.loop = true;
	idleLeftAnim_Enemy1.speed = 0.05f;

	idleDownAnim_Enemy1.PushBack({ 3072, 768, 85, 144 });  //idle_enemy
	idleDownAnim_Enemy1.PushBack({ 3200, 768, 85, 144 });
	idleDownAnim_Enemy1.PushBack({ 3328, 768, 85, 144 });
	idleDownAnim_Enemy1.PushBack({ 3456, 768, 85, 144 });
	idleDownAnim_Enemy1.PushBack({ 3200, 768, 85, 144 });
	idleDownAnim_Enemy1.PushBack({ 3072, 768, 85, 144 });
	idleDownAnim_Enemy1.loop = true;
	idleDownAnim_Enemy1.speed = 0.05f;

	idleUpAnim_Enemy1.PushBack({ 3072, 256, 128, 128 });
	idleUpAnim_Enemy1.PushBack({ 3200, 256, 128, 128 });
	idleUpAnim_Enemy1.PushBack({ 3328, 256, 128, 128 });
	idleUpAnim_Enemy1.PushBack({ 3456, 256, 128, 128 });
	idleUpAnim_Enemy1.PushBack({ 3200, 256, 128, 128 });
	idleUpAnim_Enemy1.PushBack({ 3072, 256, 128, 128 });
	idleUpAnim_Enemy1.loop = true;
	idleUpAnim_Enemy1.speed = 0.05f;

	idleUpLeftAnim_Enemy1.PushBack({ 3072, 128, 128, 128 });
	idleUpLeftAnim_Enemy1.PushBack({ 3200, 128, 128, 128 });
	idleUpLeftAnim_Enemy1.PushBack({ 3328, 128, 128, 128 });
	idleUpLeftAnim_Enemy1.PushBack({ 3456, 128, 128, 128 });
	idleUpLeftAnim_Enemy1.PushBack({ 3200, 128, 128, 128 });
	idleUpLeftAnim_Enemy1.PushBack({ 3072, 128, 128, 128 });
	idleUpLeftAnim_Enemy1.loop = true;
	idleUpLeftAnim_Enemy1.speed = 0.05f;

	idleUpRightAnim_Enemy1.PushBack({ 3072, 384, 128, 128 });
	idleUpRightAnim_Enemy1.PushBack({ 3200, 384, 128, 128 });
	idleUpRightAnim_Enemy1.PushBack({ 3328, 384, 128, 128 });
	idleUpRightAnim_Enemy1.PushBack({ 3456, 384, 128, 128 });
	idleUpRightAnim_Enemy1.PushBack({ 3200, 384, 128, 128 });
	idleUpRightAnim_Enemy1.PushBack({ 3072, 384, 128, 128 });
	idleUpRightAnim_Enemy1.loop = true;
	idleUpRightAnim_Enemy1.speed = 0.05f;

	idleDownLeftAnim_Enemy1.PushBack({ 3072, 896, 128, 128 });
	idleDownLeftAnim_Enemy1.PushBack({ 3200, 896, 128, 128 });
	idleDownLeftAnim_Enemy1.PushBack({ 3328, 896, 128, 128 });
	idleDownLeftAnim_Enemy1.PushBack({ 3456, 896, 128, 128 });
	idleDownLeftAnim_Enemy1.PushBack({ 3200, 896, 128, 128 });
	idleDownLeftAnim_Enemy1.PushBack({ 3072, 896, 128, 128 });
	idleDownLeftAnim_Enemy1.loop = true;
	idleDownLeftAnim_Enemy1.speed = 0.05f;

	idleDownRightAnim_Enemy1.PushBack({ 3072, 640, 128, 128 });
	idleDownRightAnim_Enemy1.PushBack({ 3200, 640, 128, 128 });
	idleDownRightAnim_Enemy1.PushBack({ 3328, 640, 128, 128 });
	idleDownRightAnim_Enemy1.PushBack({ 3456, 640, 128, 128 });
	idleDownRightAnim_Enemy1.PushBack({ 3200, 640, 128, 128 });
	idleDownRightAnim_Enemy1.PushBack({ 3072, 640, 128, 128 });
	idleDownRightAnim_Enemy1.loop = true;
	idleDownRightAnim_Enemy1.speed = 0.05f;



	//WALK

	rightWalkAnim_Enemy1.PushBack({ 719, 603, 128, 128 });
	rightWalkAnim_Enemy1.PushBack({ 876, 603, 128, 128 });
	rightWalkAnim_Enemy1.PushBack({ 1033, 603, 128, 128 });
	rightWalkAnim_Enemy1.PushBack({ 1190, 603, 128, 128 });
	rightWalkAnim_Enemy1.PushBack({ 1348, 603, 128, 128 });
	rightWalkAnim_Enemy1.PushBack({ 1505, 603, 128, 128 });
	rightWalkAnim_Enemy1.PushBack({ 1663, 603, 128, 128 });
	rightWalkAnim_Enemy1.PushBack({ 1820, 603, 128, 128 });
	rightWalkAnim_Enemy1.loop = true;
	rightWalkAnim_Enemy1.speed = 0.05f;

	leftWalkAnim_Enemy1.PushBack({ 719, 27, 128, 128 });
	leftWalkAnim_Enemy1.PushBack({ 876, 27, 128, 128 });
	leftWalkAnim_Enemy1.PushBack({ 1033, 27, 128, 128 });
	leftWalkAnim_Enemy1.PushBack({ 1190, 27, 128, 128 });
	leftWalkAnim_Enemy1.PushBack({ 1348, 27, 128, 128 });
	leftWalkAnim_Enemy1.PushBack({ 1505, 27, 128, 128 });
	leftWalkAnim_Enemy1.PushBack({ 1663, 27, 128, 128 });
	leftWalkAnim_Enemy1.PushBack({ 1820, 27, 128, 128 });
	leftWalkAnim_Enemy1.loop = true;
	leftWalkAnim_Enemy1.speed = 0.05f;

	downWalkAnim_Enemy1.PushBack({ 719, 891, 128, 128 });
	downWalkAnim_Enemy1.PushBack({ 876, 891, 128, 128 });
	downWalkAnim_Enemy1.PushBack({ 1033, 891, 128, 128 });
	downWalkAnim_Enemy1.PushBack({ 1190, 891, 128, 128 });
	downWalkAnim_Enemy1.PushBack({ 1348, 891, 128, 128 });
	downWalkAnim_Enemy1.PushBack({ 1505, 891, 128, 128 });
	downWalkAnim_Enemy1.PushBack({ 1663, 891, 128, 128 });
	downWalkAnim_Enemy1.PushBack({ 1820, 891, 128, 128 });
	downWalkAnim_Enemy1.loop = true;
	downWalkAnim_Enemy1.speed = 0.05f;

	upWalkAnim_Enemy1.PushBack({ 719, 315, 128, 128 });
	upWalkAnim_Enemy1.PushBack({ 876, 315, 128, 128 });
	upWalkAnim_Enemy1.PushBack({ 1033, 315, 128, 128 });
	upWalkAnim_Enemy1.PushBack({ 1190, 315, 128, 128 });
	upWalkAnim_Enemy1.PushBack({ 1348, 315, 128, 128 });
	upWalkAnim_Enemy1.PushBack({ 1505, 315, 128, 128 });
	upWalkAnim_Enemy1.PushBack({ 1663, 315, 128, 128 });
	upWalkAnim_Enemy1.PushBack({ 1820, 315, 128, 128 });
	upWalkAnim_Enemy1.loop = true;
	upWalkAnim_Enemy1.speed = 0.05f;

	rightDownWalkAnim_Enemy1.PushBack({ 719, 747, 128, 128 });
	rightDownWalkAnim_Enemy1.PushBack({ 876, 747, 128, 128 });
	rightDownWalkAnim_Enemy1.PushBack({ 1033, 747, 128, 128 });
	rightDownWalkAnim_Enemy1.PushBack({ 1190, 747, 128, 128 });
	rightDownWalkAnim_Enemy1.PushBack({ 1348, 747, 128, 128 });
	rightDownWalkAnim_Enemy1.PushBack({ 1505, 747, 128, 128 });
	rightDownWalkAnim_Enemy1.PushBack({ 1663, 747, 128, 128 });
	rightDownWalkAnim_Enemy1.PushBack({ 1820, 747, 128, 128 });
	rightDownWalkAnim_Enemy1.loop = true;
	rightDownWalkAnim_Enemy1.speed = 0.05f;

	leftDownWalkAnim_Enemy1.PushBack({ 719, 1035, 128, 128 });
	leftDownWalkAnim_Enemy1.PushBack({ 876, 1035, 128, 128 });
	leftDownWalkAnim_Enemy1.PushBack({ 1033, 1035, 128, 128 });
	leftDownWalkAnim_Enemy1.PushBack({ 1190, 1035, 128, 128 });
	leftDownWalkAnim_Enemy1.PushBack({ 1348, 1035, 128, 128 });
	leftDownWalkAnim_Enemy1.PushBack({ 1505, 1035, 128, 128 });
	leftDownWalkAnim_Enemy1.PushBack({ 1663, 1035, 128, 128 });
	leftDownWalkAnim_Enemy1.PushBack({ 1820, 1035, 128, 128 });
	leftDownWalkAnim_Enemy1.loop = true;
	leftDownWalkAnim_Enemy1.speed = 0.05f;

	rightUpWalkAnim_Enemy1.PushBack({ 719, 459, 128, 128 });
	rightUpWalkAnim_Enemy1.PushBack({ 876, 459, 128, 128 });
	rightUpWalkAnim_Enemy1.PushBack({ 1033, 459, 128, 128 });
	rightUpWalkAnim_Enemy1.PushBack({ 1190, 459, 128, 128 });
	rightUpWalkAnim_Enemy1.PushBack({ 1348, 459, 128, 128 });
	rightUpWalkAnim_Enemy1.PushBack({ 1505, 459, 128, 128 });
	rightUpWalkAnim_Enemy1.PushBack({ 1663, 459, 128, 128 });
	rightUpWalkAnim_Enemy1.PushBack({ 1820, 459, 128, 128 });
	rightUpWalkAnim_Enemy1.loop = true;
	rightUpWalkAnim_Enemy1.speed = 0.05f;

	leftUpWalkAnim_Enemy1.PushBack({ 719, 171, 128, 128 });
	leftUpWalkAnim_Enemy1.PushBack({ 876, 171, 128, 128 });
	leftUpWalkAnim_Enemy1.PushBack({ 1033, 171, 128, 128 });
	leftUpWalkAnim_Enemy1.PushBack({ 1190, 171, 128, 128 });
	leftUpWalkAnim_Enemy1.PushBack({ 1348, 171, 128, 128 });
	leftUpWalkAnim_Enemy1.PushBack({ 1505, 171, 128, 128 });
	leftUpWalkAnim_Enemy1.PushBack({ 1663, 171, 128, 128 });
	leftUpWalkAnim_Enemy1.PushBack({ 1820, 171, 128, 128 });
	leftUpWalkAnim_Enemy1.loop = true;
	leftUpWalkAnim_Enemy1.speed = 0.05f;


	//ATTACK

	rightAttackAnim_Enemy1.PushBack({ 2608, 603, 128, 128 });
	rightAttackAnim_Enemy1.PushBack({ 2450, 603, 128, 128 });
	rightAttackAnim_Enemy1.PushBack({ 2293, 603, 128, 128 });
	rightAttackAnim_Enemy1.PushBack({ 2135, 603, 128, 128 });
	rightAttackAnim_Enemy1.PushBack({ 1978, 603, 128, 128 });
	rightAttackAnim_Enemy1.PushBack({ 2135, 603, 128, 128 });
	rightAttackAnim_Enemy1.PushBack({ 2293, 603, 128, 128 });
	rightAttackAnim_Enemy1.PushBack({ 2450, 603, 128, 128 });
	rightAttackAnim_Enemy1.PushBack({ 2608, 603, 128, 128 });
	rightAttackAnim_Enemy1.loop = true;
	rightAttackAnim_Enemy1.speed = 0.05f;

	leftAttackAnim_Enemy1.PushBack({ 2608, 27, 85, 144 });
	leftAttackAnim_Enemy1.PushBack({ 2450, 27, 85, 144 });
	leftAttackAnim_Enemy1.PushBack({ 2293, 27, 85, 144 });
	leftAttackAnim_Enemy1.PushBack({ 2135, 27, 85, 144 });
	leftAttackAnim_Enemy1.PushBack({ 1978, 27, 85, 144 });
	leftAttackAnim_Enemy1.PushBack({ 2135, 27, 85, 144 });
	leftAttackAnim_Enemy1.PushBack({ 2293, 27, 85, 144 });
	leftAttackAnim_Enemy1.PushBack({ 2450, 27, 85, 144 });
	leftAttackAnim_Enemy1.PushBack({ 2608, 27, 85, 144 });
	leftAttackAnim_Enemy1.loop = true;
	leftAttackAnim_Enemy1.speed = 0.05f;

	downAttackAnim_Enemy1.PushBack({ 2608, 891, 85, 144 });
	downAttackAnim_Enemy1.PushBack({ 2450, 891, 85, 144 });
	downAttackAnim_Enemy1.PushBack({ 2293, 891, 85, 144 });
	downAttackAnim_Enemy1.PushBack({ 2135, 891, 85, 144 });
	downAttackAnim_Enemy1.PushBack({ 1978, 891, 85, 144 });
	downAttackAnim_Enemy1.PushBack({ 2135, 891, 85, 144 });
	downAttackAnim_Enemy1.PushBack({ 2293, 891, 85, 144 });
	downAttackAnim_Enemy1.PushBack({ 2450, 891, 85, 144 });
	downAttackAnim_Enemy1.PushBack({ 2608, 891, 85, 144 });
	downAttackAnim_Enemy1.loop = true;
	downAttackAnim_Enemy1.speed = 0.05f;

	upAttackAnim_Enemy1.PushBack({ 2608, 315, 85, 144 });
	upAttackAnim_Enemy1.PushBack({ 2450, 315, 85, 144 });
	upAttackAnim_Enemy1.PushBack({ 2293, 315, 85, 144 });
	upAttackAnim_Enemy1.PushBack({ 2135, 315, 85, 144 });
	upAttackAnim_Enemy1.PushBack({ 1978, 315, 85, 144 });
	upAttackAnim_Enemy1.PushBack({ 2135, 315, 85, 144 });
	upAttackAnim_Enemy1.PushBack({ 2293, 315, 85, 144 });
	upAttackAnim_Enemy1.PushBack({ 2450, 315, 85, 144 });
	upAttackAnim_Enemy1.PushBack({ 2608, 315, 85, 144 });
	upAttackAnim_Enemy1.loop = true;
	upAttackAnim_Enemy1.speed = 0.05f;

	rightDownAttackAnim_Enemy1.PushBack({ 2608, 747, 85, 144 });
	rightDownAttackAnim_Enemy1.PushBack({ 2450, 747, 85, 144 });
	rightDownAttackAnim_Enemy1.PushBack({ 2293, 747, 85, 144 });
	rightDownAttackAnim_Enemy1.PushBack({ 2135, 747, 85, 144 });
	rightDownAttackAnim_Enemy1.PushBack({ 1978, 747, 85, 144 });
	rightDownAttackAnim_Enemy1.PushBack({ 2135, 747, 85, 144 });
	rightDownAttackAnim_Enemy1.PushBack({ 2293, 747, 85, 144 });
	rightDownAttackAnim_Enemy1.PushBack({ 2450, 747, 85, 144 });
	rightDownAttackAnim_Enemy1.PushBack({ 2608, 747, 85, 144 });
	rightDownAttackAnim_Enemy1.loop = true;
	rightDownAttackAnim_Enemy1.speed = 0.05f;


	leftDownAttackAnim_Enemy1.PushBack({ 2608, 1035, 85, 144 });
	leftDownAttackAnim_Enemy1.PushBack({ 2450, 1035, 85, 144 });
	leftDownAttackAnim_Enemy1.PushBack({ 2293, 1035, 85, 144 });
	leftDownAttackAnim_Enemy1.PushBack({ 2135, 1035, 85, 144 });
	leftDownAttackAnim_Enemy1.PushBack({ 1978, 1035, 85, 144 });
	leftDownAttackAnim_Enemy1.PushBack({ 2135, 1035, 85, 144 });
	leftDownAttackAnim_Enemy1.PushBack({ 2293, 1035, 85, 144 });
	leftDownAttackAnim_Enemy1.PushBack({ 2450, 1035, 85, 144 });
	leftDownAttackAnim_Enemy1.PushBack({ 2608, 1035, 85, 144 });
	leftDownAttackAnim_Enemy1.loop = true;
	leftDownAttackAnim_Enemy1.speed = 0.05f;

	rightUpAttackAnim_Enemy1.PushBack({ 2608, 459, 85, 144 });
	rightUpAttackAnim_Enemy1.PushBack({ 2450, 459, 85, 144 });
	rightUpAttackAnim_Enemy1.PushBack({ 2293, 459, 85, 144 });
	rightUpAttackAnim_Enemy1.PushBack({ 2135, 459, 85, 144 });
	rightUpAttackAnim_Enemy1.PushBack({ 1978, 459, 85, 144 });
	rightUpAttackAnim_Enemy1.PushBack({ 2135, 459, 85, 144 });
	rightUpAttackAnim_Enemy1.PushBack({ 2293, 459, 85, 144 });
	rightUpAttackAnim_Enemy1.PushBack({ 2450, 459, 85, 144 });
	rightUpAttackAnim_Enemy1.PushBack({ 2608, 459, 85, 144 });
	rightUpAttackAnim_Enemy1.loop = true;
	rightUpAttackAnim_Enemy1.speed = 0.05f;

	leftUpAttackAnim_Enemy1.PushBack({ 2608, 171, 85, 144 });
	leftUpAttackAnim_Enemy1.PushBack({ 2450, 171, 85, 144 });
	leftUpAttackAnim_Enemy1.PushBack({ 2293, 171, 85, 144 });
	leftUpAttackAnim_Enemy1.PushBack({ 2135, 171, 85, 144 });
	leftUpAttackAnim_Enemy1.PushBack({ 1978, 171, 85, 144 });
	leftUpAttackAnim_Enemy1.PushBack({ 2135, 171, 85, 144 });
	leftUpAttackAnim_Enemy1.PushBack({ 2293, 171, 85, 144 });
	leftUpAttackAnim_Enemy1.PushBack({ 2450, 171, 85, 144 });
	leftUpAttackAnim_Enemy1.PushBack({ 2608, 171, 85, 144 });
	leftUpAttackAnim_Enemy1.loop = true;
	leftUpAttackAnim_Enemy1.speed = 0.05f;

	//DIE

	rightDieAnim_Enemy1.PushBack({ 3553, 603, 128, 128 });
	rightDieAnim_Enemy1.PushBack({ 3710, 603, 128, 128 });
	rightDieAnim_Enemy1.PushBack({ 3868, 603, 128, 128 });
	rightDieAnim_Enemy1.PushBack({ 4025, 603, 128, 128 });
	rightDieAnim_Enemy1.PushBack({ 4183, 603, 128, 128 });
	rightDieAnim_Enemy1.PushBack({ 4340, 603, 128, 128 });
	rightDieAnim_Enemy1.loop = true;
	rightDieAnim_Enemy1.speed = 0.05f;

	leftDieAnim_Enemy1.PushBack({ 3553, 27, 128, 128 });
	leftDieAnim_Enemy1.PushBack({ 3710, 27, 128, 128 });
	leftDieAnim_Enemy1.PushBack({ 3868, 27, 128, 128 });
	leftDieAnim_Enemy1.PushBack({ 4025, 27, 128, 128 });
	leftDieAnim_Enemy1.PushBack({ 4183, 27, 128, 128 });
	leftDieAnim_Enemy1.PushBack({ 4340, 27, 128, 128 });
	leftDieAnim_Enemy1.loop = true;
	leftDieAnim_Enemy1.speed = 0.05f;

	downDieAnim_Enemy1.PushBack({ 3553, 891, 128, 128 });
	downDieAnim_Enemy1.PushBack({ 3710, 891, 128, 128 });
	downDieAnim_Enemy1.PushBack({ 3868, 891, 128, 128 });
	downDieAnim_Enemy1.PushBack({ 4025, 891, 128, 128 });
	downDieAnim_Enemy1.PushBack({ 4183, 891, 128, 128 });
	downDieAnim_Enemy1.PushBack({ 4340, 891, 128, 128 });
	downDieAnim_Enemy1.loop = true;
	downDieAnim_Enemy1.speed = 0.05f;

	upDieAnim_Enemy1.PushBack({ 3553, 315, 128, 128 });
	upDieAnim_Enemy1.PushBack({ 3710, 315, 128, 128 });
	upDieAnim_Enemy1.PushBack({ 3868, 315, 128, 128 });
	upDieAnim_Enemy1.PushBack({ 4025, 315, 128, 128 });
	upDieAnim_Enemy1.PushBack({ 4183, 315, 128, 128 });
	upDieAnim_Enemy1.PushBack({ 4340, 315, 128, 128 });
	upDieAnim_Enemy1.loop = true;
	upDieAnim_Enemy1.speed = 0.05f;

	rightDownDieAnim_Enemy1.PushBack({ 3553, 747, 128, 128 });
	rightDownDieAnim_Enemy1.PushBack({ 3710, 747, 128, 128 });
	rightDownDieAnim_Enemy1.PushBack({ 3868, 747, 128, 128 });
	rightDownDieAnim_Enemy1.PushBack({ 4025, 747, 128, 128 });
	rightDownDieAnim_Enemy1.PushBack({ 4183, 747, 128, 128 });
	rightDownDieAnim_Enemy1.PushBack({ 4340, 747, 128, 128 });
	rightDownDieAnim_Enemy1.loop = true;
	rightDownDieAnim_Enemy1.speed = 0.05f;

	leftDownDieAnim_Enemy1.PushBack({ 3553, 1035, 128, 128 });
	leftDownDieAnim_Enemy1.PushBack({ 3710, 1035, 128, 128 });
	leftDownDieAnim_Enemy1.PushBack({ 3868, 1035, 128, 128 });
	leftDownDieAnim_Enemy1.PushBack({ 4025, 1035, 128, 128 });
	leftDownDieAnim_Enemy1.PushBack({ 4183, 1035, 128, 128 });
	leftDownDieAnim_Enemy1.PushBack({ 4340, 1035, 128, 128 });
	leftDownDieAnim_Enemy1.loop = true;
	leftDownDieAnim_Enemy1.speed = 0.05f;

	rightUpDieAnim_Enemy1.PushBack({ 3553, 459, 128, 128 });
	rightUpDieAnim_Enemy1.PushBack({ 3710, 459, 128, 128 });
	rightUpDieAnim_Enemy1.PushBack({ 3868, 459, 128, 128 });
	rightUpDieAnim_Enemy1.PushBack({ 4025, 459, 128, 128 });
	rightUpDieAnim_Enemy1.PushBack({ 4183, 459, 128, 128 });
	rightUpDieAnim_Enemy1.PushBack({ 4340, 459, 128, 128 });
	rightUpDieAnim_Enemy1.loop = true;
	rightUpDieAnim_Enemy1.speed = 0.05f;

	leftUpDieAnim_Enemy1.PushBack({ 3553, 171, 128, 128 });
	leftUpDieAnim_Enemy1.PushBack({ 3710, 171, 128, 128 });
	leftUpDieAnim_Enemy1.PushBack({ 3868, 171, 128, 128 });
	leftUpDieAnim_Enemy1.PushBack({ 4025, 171, 128, 128 });
	leftUpDieAnim_Enemy1.PushBack({ 4183, 171, 128, 128 });
	leftUpDieAnim_Enemy1.PushBack({ 4340, 171, 128, 128 });
	leftUpDieAnim_Enemy1.loop = true;
	leftUpDieAnim_Enemy1.speed = 0.05f;


	position.x = x;
	position.y = y;

	offsetX = -25;
	offsetY = -50;

	collider = app->collisions->AddCollider({ position.x, position.y, 25, 56 }, Collider::Type::ENEMY, (Module*)app->entity_manager);

	Mini_Boss_One_List.add(app->physics->CreateZombieStandartBox(position.x, position.y, 25, 10));



}

void Mini_Boss_One::Update(float dt)
{
	//ADD THE PATHFINDING LOGIC FOR MOVEMENT
	if (EntityHP > 0)
	{

		if (app->player->pauseMenu == true)
		{
			iPoint NewPosition = position;
			collider->SetPos(NewPosition.x, NewPosition.y);
			Mini_Boss_One_List.end->data->GetPosition(NewPosition.x, NewPosition.y);
			currentAnim = &idleDownAnim_Enemy1;
			currentAnim->loop = false;

		}
		if (app->player->pauseMenu == false)
		{
			//Escape Combat
			if (app->player->escapeCombat == true)
			{
				entityState = GameState::OutOfCombat;
				entityTurn = TurnState::NONE;
			}


			if (entityState == GameState::OutOfCombat)
			{
				//move normally
				if (app->inventoryMenu->ActiveRadioAlive == true)
				{
					if (position.DistanceTo(app->inventoryMenu->ActiveRadioPosition) < 2650)
					{
						collider->SetPos(position.x, position.y);
						Mini_Boss_One_List.end->data->GetPosition(position.x, position.y);
						currentAnim = &idleDownAnim_Enemy1;
						currentAnim->loop = true;

						if (position.x > app->inventoryMenu->ActiveRadioPosition.x)
						{
							if (currentAnim != &leftWalkAnim_Enemy1)
							{
								//leftWalkAnim_Enemy1.Reset();
								currentAnim = &leftWalkAnim_Enemy1;
							}
							Mini_Boss_One_List.end->data->body->SetLinearVelocity({ -0.5f, 0.0f });
						}
						if (position.x < app->inventoryMenu->ActiveRadioPosition.x)
						{
							if (currentAnim != &rightWalkAnim_Enemy1)
							{
								//rightWalkAnim_Enemy1.Reset();
								currentAnim = &rightWalkAnim_Enemy1;
							}
							Mini_Boss_One_List.end->data->body->SetLinearVelocity({ 0.5f, 0.0f });
						}
						if (position.y > app->inventoryMenu->ActiveRadioPosition.y)
						{
							if (currentAnim != &upWalkAnim_Enemy1)
							{
								//upWalkAnim_Enemy1.Reset();
								currentAnim = &upWalkAnim_Enemy1;
							}
							Mini_Boss_One_List.end->data->body->SetLinearVelocity({ 0.0f, -0.5f });
						}
						if (position.y < app->inventoryMenu->ActiveRadioPosition.y)
						{
							if (currentAnim != &downWalkAnim_Enemy1)
							{
								//downWalkAnim_Enemy1.Reset();
								currentAnim = &downWalkAnim_Enemy1;
							}
							Mini_Boss_One_List.end->data->body->SetLinearVelocity({ 0.0f, 0.5f });
						}


						if ((app->inventoryMenu->ActiveRadioPosition.y > position.y) && (app->inventoryMenu->ActiveRadioPosition.x > position.x))
						{
							if (currentAnim != &rightDownWalkAnim_Enemy1)
							{
								//rightDownWalkAnim_Enemy1.Reset();
								currentAnim = &rightDownWalkAnim_Enemy1;
							}
							Mini_Boss_One_List.end->data->body->SetLinearVelocity({ 0.5f, 0.5f });
						}
						if ((app->inventoryMenu->ActiveRadioPosition.x < position.x) && (app->inventoryMenu->ActiveRadioPosition.y > position.y))
						{
							if (currentAnim != &leftDownWalkAnim_Enemy1)
							{
								//rightDownWalkAnim_Enemy1.Reset();
								currentAnim = &leftDownWalkAnim_Enemy1;
							}
							Mini_Boss_One_List.end->data->body->SetLinearVelocity({ -0.5f, 0.5f });
						}
						if ((app->inventoryMenu->ActiveRadioPosition.y < position.y) && (app->inventoryMenu->ActiveRadioPosition.x < position.x))
						{
							if (currentAnim != &leftUpWalkAnim_Enemy1)
							{
								//leftUpWalkAnim_Enemy1.Reset();
								currentAnim = &leftUpWalkAnim_Enemy1;
							}
							Mini_Boss_One_List.end->data->body->SetLinearVelocity({ -0.5f, -0.5f });
						}
						if ((app->inventoryMenu->ActiveRadioPosition.x > position.x) && (app->inventoryMenu->ActiveRadioPosition.y < position.y))
						{
							if (currentAnim != &rightUpWalkAnim_Enemy1)
							{
								//leftUpWalkAnim_Enemy1.Reset();
								currentAnim = &rightUpWalkAnim_Enemy1;
							}
							Mini_Boss_One_List.end->data->body->SetLinearVelocity({ 0.5f, -0.5f });
						}
					}
					else
					{
						collider->SetPos(position.x, position.y);
						Mini_Boss_One_List.end->data->GetPosition(position.x, position.y);
						currentAnim = &idleDownAnim_Enemy1;
						currentAnim->loop = true;

						Mini_Boss_One_List.end->data->body->SetLinearVelocity({ 0.0f,0.0f });

					}
				}
				if (app->inventoryMenu->ActiveRadioAlive == false)
				{
					if (position.DistanceTo(app->player->position) < 300)
					{
						collider->SetPos(position.x, position.y);
						Mini_Boss_One_List.end->data->GetPosition(position.x, position.y);
						currentAnim = &idleDownAnim_Enemy1;
						currentAnim->loop = true;

						if (position.x > app->player->position.x + app->player->collider->rect.w / 2)
						{
							if (currentAnim != &leftWalkAnim_Enemy1)
							{
								//leftWalkAnim_Enemy1.Reset();
								currentAnim = &leftWalkAnim_Enemy1;
							}
							Mini_Boss_One_List.end->data->body->SetLinearVelocity({ -0.5f, 0.0f });
						}
						if (position.x < app->player->position.x + app->player->collider->rect.w / 2)
						{
							if (currentAnim != &rightWalkAnim_Enemy1)
							{
								//rightWalkAnim_Enemy1.Reset();
								currentAnim = &rightWalkAnim_Enemy1;
							}
							Mini_Boss_One_List.end->data->body->SetLinearVelocity({ 0.5f, 0.0f });
						}
						if (position.y > app->player->position.y - app->player->collider->rect.h)
						{
							if (currentAnim != &upWalkAnim_Enemy1)
							{
								//upWalkAnim_Enemy1.Reset();
								currentAnim = &upWalkAnim_Enemy1;
							}
							Mini_Boss_One_List.end->data->body->SetLinearVelocity({ 0.0f, -0.5f });
						}
						if (position.y < app->player->position.y - app->player->collider->rect.h)
						{
							if (currentAnim != &downWalkAnim_Enemy1)
							{
								//downWalkAnim_Enemy1.Reset();
								currentAnim = &downWalkAnim_Enemy1;
							}
							Mini_Boss_One_List.end->data->body->SetLinearVelocity({ 0.0f, 0.5f });
						}


						if ((app->player->position.y - app->player->collider->rect.h > position.y) && (app->player->position.x + app->player->collider->rect.w / 2 > position.x))
						{
							if (currentAnim != &rightDownWalkAnim_Enemy1)
							{
								//rightDownWalkAnim_Enemy1.Reset();
								currentAnim = &rightDownWalkAnim_Enemy1;
							}
							Mini_Boss_One_List.end->data->body->SetLinearVelocity({ 0.5f, 0.5f });
						}
						if ((app->player->position.x + app->player->collider->rect.w / 2 < position.x) && (app->player->position.y - app->player->collider->rect.h > position.y))
						{
							if (currentAnim != &leftDownWalkAnim_Enemy1)
							{
								//rightDownWalkAnim_Enemy1.Reset();
								currentAnim = &leftDownWalkAnim_Enemy1;
							}
							Mini_Boss_One_List.end->data->body->SetLinearVelocity({ -0.5f, 0.5f });
						}
						if ((app->player->position.y - app->player->collider->rect.h < position.y) && (app->player->position.x + app->player->collider->rect.w / 2 < position.x))
						{
							if (currentAnim != &leftUpWalkAnim_Enemy1)
							{
								//leftUpWalkAnim_Enemy1.Reset();
								currentAnim = &leftUpWalkAnim_Enemy1;
							}
							Mini_Boss_One_List.end->data->body->SetLinearVelocity({ -0.5f, -0.5f });
						}
						if ((app->player->position.x + app->player->collider->rect.w / 2 > position.x) && (app->player->position.y - app->player->collider->rect.h < position.y))
						{
							if (currentAnim != &rightUpWalkAnim_Enemy1)
							{
								//leftUpWalkAnim_Enemy1.Reset();
								currentAnim = &rightUpWalkAnim_Enemy1;
							}
							Mini_Boss_One_List.end->data->body->SetLinearVelocity({ 0.5f, -0.5f });
						}
					}
					else
					{
						collider->SetPos(position.x, position.y);
						Mini_Boss_One_List.end->data->GetPosition(position.x, position.y);
						currentAnim = &idleDownAnim_Enemy1;
						currentAnim->loop = true;

						Mini_Boss_One_List.end->data->body->SetLinearVelocity({ 0.0f,0.0f });

					}

					if (position.DistanceTo(app->player->position) < 100)
					{
						app->entity_manager->RegisterEntitesInCombat(this);
						entityState = GameState::InCombat;
						//app->player->entityStatePlayer = GameState::InCombat;
						app->game_manager->StartTurnManagement = true;
					}
				}






			}

			if (entityState == GameState::InCombat)
			{

				if (EntityHP > 0)
				{
					if (entityTurn == TurnState::NONE)
					{
						//Assigning order of turns
						collider->SetPos(position.x, position.y);
						Mini_Boss_One_List.end->data->GetPosition(position.x, position.y);
						currentAnim = &idleDownAnim_Enemy1;
						currentAnim->loop = true;

						Mini_Boss_One_List.end->data->body->SetLinearVelocity({ 0.0f,0.0f });

					}
					if (entityTurn == TurnState::StartOfTurn)
					{
						collider->SetPos(position.x, position.y);
						currentAnim = &idleDownAnim_Enemy1;
						currentAnim->loop = false;
						Mini_Boss_One_List.end->data->body->SetLinearVelocity({ 0.0f, 0.0f }); //movimiento contrario a la direccion del jugador cuando nos chocamos con el

						entityTurn = TurnState::MidOfTurn;

					}
					if (entityTurn == TurnState::MidOfTurn)
					{

						collider->SetPos(position.x, position.y);
						Mini_Boss_One_List.end->data->GetPosition(position.x, position.y);
						currentAnim = &idleDownAnim_Enemy1;
						currentAnim->loop = true;
						counter++;

						if (position.DistanceTo({ app->player->position.x + app->player->collider->rect.w / 2 , app->player->position.y - app->player->collider->rect.h }) > 60)
						{
							if (position.x > app->player->position.x + app->player->collider->rect.w / 2)
							{
								if (currentAnim != &leftWalkAnim_Enemy1)
								{
									//leftWalkAnim_Enemy1.Reset();
									currentAnim = &leftWalkAnim_Enemy1;
								}
								Mini_Boss_One_List.end->data->body->SetLinearVelocity({ -0.5f, 0.0f });
							}
							if (position.x < app->player->position.x + app->player->collider->rect.w / 2)
							{
								if (currentAnim != &rightWalkAnim_Enemy1)
								{
									//rightWalkAnim_Enemy1.Reset();
									currentAnim = &rightWalkAnim_Enemy1;
								}
								Mini_Boss_One_List.end->data->body->SetLinearVelocity({ 0.5f, 0.0f });
							}
							if (position.y > app->player->position.y - app->player->collider->rect.h)
							{
								if (currentAnim != &upWalkAnim_Enemy1)
								{
									//upWalkAnim_Enemy1.Reset();
									currentAnim = &upWalkAnim_Enemy1;
								}
								Mini_Boss_One_List.end->data->body->SetLinearVelocity({ 0.0f, -0.5f });
							}
							if (position.y < app->player->position.y - app->player->collider->rect.h)
							{
								if (currentAnim != &downWalkAnim_Enemy1)
								{
									//downWalkAnim_Enemy1.Reset();
									currentAnim = &downWalkAnim_Enemy1;
								}
								Mini_Boss_One_List.end->data->body->SetLinearVelocity({ 0.0f, 0.5f });
							}


							if ((app->player->position.y - app->player->collider->rect.h > position.y) && (app->player->position.x + app->player->collider->rect.w / 2 > position.x))
							{
								if (currentAnim != &rightDownWalkAnim_Enemy1)
								{
									//rightDownWalkAnim_Enemy1.Reset();
									currentAnim = &rightDownWalkAnim_Enemy1;
								}
								Mini_Boss_One_List.end->data->body->SetLinearVelocity({ 0.5f, 0.5f });
							}
							if ((app->player->position.x + app->player->collider->rect.w / 2 < position.x) && (app->player->position.y - app->player->collider->rect.h > position.y))
							{
								if (currentAnim != &leftDownWalkAnim_Enemy1)
								{
									//rightDownWalkAnim_Enemy1.Reset();
									currentAnim = &leftDownWalkAnim_Enemy1;
								}
								Mini_Boss_One_List.end->data->body->SetLinearVelocity({ -0.5f, 0.5f });
							}
							if ((app->player->position.y - app->player->collider->rect.h < position.y) && (app->player->position.x + app->player->collider->rect.w / 2 < position.x))
							{
								if (currentAnim != &leftUpWalkAnim_Enemy1)
								{
									//leftUpWalkAnim_Enemy1.Reset();
									currentAnim = &leftUpWalkAnim_Enemy1;
								}
								Mini_Boss_One_List.end->data->body->SetLinearVelocity({ -0.5f, -0.5f });
							}
							if ((app->player->position.x + app->player->collider->rect.w / 2 > position.x) && (app->player->position.y - app->player->collider->rect.h < position.y))
							{
								if (currentAnim != &rightUpWalkAnim_Enemy1)
								{
									//leftUpWalkAnim_Enemy1.Reset();
									currentAnim = &rightUpWalkAnim_Enemy1;
								}
								Mini_Boss_One_List.end->data->body->SetLinearVelocity({ 0.5f, -0.5f });
							}

							if (counter == 150) entityTurn = TurnState::FinishTurn;
						}

						if (position.DistanceTo({ app->player->position.x + app->player->collider->rect.w / 2 , app->player->position.y - app->player->collider->rect.h }) <= 60)
						{
							entityTurn = TurnState::FinishTurn;
						}

					}
					if (entityTurn == TurnState::FinishTurn)
					{
						//Change turn from enemy to player turn still have to develop a way to do it correctly
						Mini_Boss_One_List.end->data->body->SetLinearVelocity({ 0.0f, 0.0f });
						collider->SetPos(position.x, position.y);
						Mini_Boss_One_List.end->data->GetPosition(position.x, position.y);

						currentAnim = &idleDownAnim_Enemy1;
						currentAnim->loop = true;

						if (position.DistanceTo({ app->player->position.x + app->player->collider->rect.w / 2, app->player->position.y - app->player->collider->rect.h }) < 75)
						{

							if ((position.x == app->player->position.x + app->player->collider->rect.w / 2) && (position.y < app->player->position.y - app->player->collider->rect.h))
							{

								app->particles->AddParticle(app->particles->enemyAttack, position.x, position.y + 30, Collider::Type::ENEMY_ATTACK);

							}
							if ((position.x == app->player->position.x + app->player->collider->rect.w / 2) && (position.y > app->player->position.y - app->player->collider->rect.h))
							{

								app->particles->AddParticle(app->particles->enemyAttack, position.x, position.y - 30, Collider::Type::ENEMY_ATTACK);

							}
							if ((position.x < app->player->position.x + app->player->collider->rect.w / 2) && (position.y == app->player->position.y - app->player->collider->rect.h))
							{


								app->particles->AddParticle(app->particles->enemyAttack, position.x + 30, position.y, Collider::Type::ENEMY_ATTACK);


							}
							if ((position.x > app->player->position.x + app->player->collider->rect.w / 2) && (position.y == app->player->position.y - app->player->collider->rect.h))
							{

								app->particles->AddParticle(app->particles->enemyAttack, position.x - 30, position.y, Collider::Type::ENEMY_ATTACK);


							}

							if ((position.x > app->player->position.x + app->player->collider->rect.w / 2) && (position.y > app->player->position.y - app->player->collider->rect.h))
							{


								app->particles->AddParticle(app->particles->enemyAttack, position.x - 30, position.y - 30, Collider::Type::ENEMY_ATTACK);


							}
							if ((position.x > app->player->position.x + app->player->collider->rect.w / 2) && (position.y < app->player->position.y - app->player->collider->rect.h))
							{

								app->particles->AddParticle(app->particles->enemyAttack, position.x - 30, position.y + 30, Collider::Type::ENEMY_ATTACK);


							}
							if ((position.x < app->player->position.x + app->player->collider->rect.w / 2) && (position.y > app->player->position.y - app->player->collider->rect.h))
							{

								app->particles->AddParticle(app->particles->enemyAttack, position.x + 30, position.y - 30, Collider::Type::ENEMY_ATTACK);


							}
							if ((position.x < app->player->position.x + app->player->collider->rect.w / 2) && (position.y < app->player->position.y - app->player->collider->rect.h))
							{

								app->particles->AddParticle(app->particles->enemyAttack, position.x + 30, position.y + 30, Collider::Type::ENEMY_ATTACK);


							}

							entityTurn = TurnState::WaitTurn;
						}
						else
						{
							entityTurn = TurnState::WaitTurn;
						}


					}
					if (entityTurn == TurnState::WaitTurn)
					{
						counter = 0;
						collider->SetPos(position.x, position.y);
						Mini_Boss_One_List.end->data->GetPosition(position.x, position.y);
						currentAnim = &idleDownAnim_Enemy1;
						currentAnim->loop = true;

					}
					if (app->sceneMainMap->playerRestart == true)
					{
						app->game_manager->counter = 0;
						entityState = GameState::OutOfCombat;
						entityTurn = TurnState::NONE;
					}



				}






			}

			currentAnim->Update();
		}
	}






}


