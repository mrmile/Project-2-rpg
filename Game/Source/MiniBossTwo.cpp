#include "MiniBossTwo.h"

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

Mini_Boss_Two::Mini_Boss_Two(int x, int y) : Entity(x, y)
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

	idleRightAnim_Enemy1.PushBack({ 0, 1250, 316, 312 });
	idleRightAnim_Enemy1.loop = true;
	idleRightAnim_Enemy1.speed = 0.05f;

	idleLeftAnim_Enemy1.PushBack({ 0, 0, 316, 312 });
	idleLeftAnim_Enemy1.loop = true;
	idleLeftAnim_Enemy1.speed = 0.05f;

	idleDownAnim_Enemy1.PushBack({ 0, 1875, 316, 312 });  //idle_enemy
	idleDownAnim_Enemy1.loop = true;
	idleDownAnim_Enemy1.speed = 0.05f;

	idleUpAnim_Enemy1.PushBack({ 0, 625, 316, 312 });
	idleUpAnim_Enemy1.loop = true;
	idleUpAnim_Enemy1.speed = 0.05f;

	idleUpLeftAnim_Enemy1.PushBack({ 0, 312, 316, 312 });
	idleUpLeftAnim_Enemy1.loop = true;
	idleUpLeftAnim_Enemy1.speed = 0.05f;

	idleUpRightAnim_Enemy1.PushBack({ 0, 937, 316, 312 });
	idleUpRightAnim_Enemy1.loop = true;
	idleUpRightAnim_Enemy1.speed = 0.05f;

	idleDownLeftAnim_Enemy1.PushBack({ 0, 2187, 316, 312 });
	idleDownLeftAnim_Enemy1.loop = true;
	idleDownLeftAnim_Enemy1.speed = 0.05f;

	idleDownRightAnim_Enemy1.PushBack({ 0, 1562, 316, 312 });
	idleDownRightAnim_Enemy1.loop = true;
	idleDownRightAnim_Enemy1.speed = 0.05f;



	//WALK

	rightWalkAnim_Enemy1.PushBack({ 316, 1250, 316, 312 });
	rightWalkAnim_Enemy1.PushBack({ 633, 1250, 316, 312 });
	rightWalkAnim_Enemy1.PushBack({ 949, 1250, 316, 312 });
	rightWalkAnim_Enemy1.PushBack({ 1266, 1250, 316, 312 });
	rightWalkAnim_Enemy1.PushBack({ 1582, 1250, 316, 312 });
	rightWalkAnim_Enemy1.PushBack({ 1899, 1250, 316, 312 });
	rightWalkAnim_Enemy1.PushBack({ 2215, 1250, 316, 312 });
	rightWalkAnim_Enemy1.PushBack({ 2532, 1250, 316, 312 });
	rightWalkAnim_Enemy1.PushBack({ 2848, 1250, 316, 312 });
	rightWalkAnim_Enemy1.PushBack({ 3165, 1250, 316, 312 });
	rightWalkAnim_Enemy1.PushBack({ 3481, 1250, 316, 312 });
	rightWalkAnim_Enemy1.loop = true;
	rightWalkAnim_Enemy1.speed = 0.05f;

	leftWalkAnim_Enemy1.PushBack({ 316, 0, 316, 312 });
	leftWalkAnim_Enemy1.PushBack({ 633, 0, 316, 312 });
	leftWalkAnim_Enemy1.PushBack({ 949, 0, 316, 312 });
	leftWalkAnim_Enemy1.PushBack({ 1266, 0, 316, 312 });
	leftWalkAnim_Enemy1.PushBack({ 1582, 0, 316, 312 });
	leftWalkAnim_Enemy1.PushBack({ 1899, 0, 316, 312 });
	leftWalkAnim_Enemy1.PushBack({ 2215, 0, 316, 312 });
	leftWalkAnim_Enemy1.PushBack({ 2532, 0, 316, 312 });
	leftWalkAnim_Enemy1.PushBack({ 2848, 0, 316, 312 });
	leftWalkAnim_Enemy1.PushBack({ 3165, 0, 316, 312 });
	leftWalkAnim_Enemy1.PushBack({ 3481, 0, 316, 312 });
	leftWalkAnim_Enemy1.loop = true;
	leftWalkAnim_Enemy1.speed = 0.05f;

	downWalkAnim_Enemy1.PushBack({ 719, 1875, 316, 312 });
	downWalkAnim_Enemy1.PushBack({ 633, 1875, 316, 312 });
	downWalkAnim_Enemy1.PushBack({ 949, 1875, 316, 312 });
	downWalkAnim_Enemy1.PushBack({ 1266, 1875, 316, 312 });
	downWalkAnim_Enemy1.PushBack({ 1582, 1875, 316, 312 });
	downWalkAnim_Enemy1.PushBack({ 1899, 1875, 316, 312 });
	downWalkAnim_Enemy1.PushBack({ 2215, 1875, 316, 312 });
	downWalkAnim_Enemy1.PushBack({ 2532, 1875, 316, 312 });
	downWalkAnim_Enemy1.PushBack({ 2848, 1875, 316, 312 });
	downWalkAnim_Enemy1.PushBack({ 3165, 1875, 316, 312 });
	downWalkAnim_Enemy1.PushBack({ 3481, 1875, 316, 312 });
	downWalkAnim_Enemy1.loop = true;
	downWalkAnim_Enemy1.speed = 0.05f;

	upWalkAnim_Enemy1.PushBack({ 316, 625, 316, 312 });
	upWalkAnim_Enemy1.PushBack({ 633, 625, 316, 312 });
	upWalkAnim_Enemy1.PushBack({ 949, 625, 316, 312 });
	upWalkAnim_Enemy1.PushBack({ 1266, 625, 316, 312 });
	upWalkAnim_Enemy1.PushBack({ 1582, 625, 316, 312 });
	upWalkAnim_Enemy1.PushBack({ 1899, 625, 316, 312 });
	upWalkAnim_Enemy1.PushBack({ 2215, 625, 316, 312 });
	upWalkAnim_Enemy1.PushBack({ 2532, 625, 316, 312 });
	upWalkAnim_Enemy1.PushBack({ 2848, 625, 316, 312 });
	upWalkAnim_Enemy1.PushBack({ 3165, 625, 316, 312 });
	upWalkAnim_Enemy1.PushBack({ 3481, 625, 316, 312 });
	upWalkAnim_Enemy1.loop = true;
	upWalkAnim_Enemy1.speed = 0.05f;

	rightDownWalkAnim_Enemy1.PushBack({ 719, 1562, 316, 312 });
	rightDownWalkAnim_Enemy1.PushBack({ 633, 1562, 316, 312 });
	rightDownWalkAnim_Enemy1.PushBack({ 949, 1562, 316, 312 });
	rightDownWalkAnim_Enemy1.PushBack({ 1266, 1562, 316, 312 });
	rightDownWalkAnim_Enemy1.PushBack({ 1582, 1562, 316, 312 });
	rightDownWalkAnim_Enemy1.PushBack({ 1899, 1562, 316, 312 });
	rightDownWalkAnim_Enemy1.PushBack({ 2215, 1562, 316, 312 });
	rightDownWalkAnim_Enemy1.PushBack({ 2532, 1562, 316, 312 });
	rightDownWalkAnim_Enemy1.PushBack({ 2848, 1562, 316, 312 });
	rightDownWalkAnim_Enemy1.PushBack({ 3165, 1562, 316, 312 });
	rightDownWalkAnim_Enemy1.PushBack({ 3481, 1562, 316, 312 });
	rightDownWalkAnim_Enemy1.loop = true;
	rightDownWalkAnim_Enemy1.speed = 0.05f;

	leftDownWalkAnim_Enemy1.PushBack({ 316, 2187, 316, 312 });
	leftDownWalkAnim_Enemy1.PushBack({ 633, 2187, 316, 312 });
	leftDownWalkAnim_Enemy1.PushBack({ 949, 2187, 316, 312 });
	leftDownWalkAnim_Enemy1.PushBack({ 1266, 2187, 316, 312 });
	leftDownWalkAnim_Enemy1.PushBack({ 1582, 2187, 316, 312 });
	leftDownWalkAnim_Enemy1.PushBack({ 1899, 2187, 316, 312 });
	leftDownWalkAnim_Enemy1.PushBack({ 2215, 2187, 316, 312 });
	leftDownWalkAnim_Enemy1.PushBack({ 2532, 2187, 316, 312 });
	leftDownWalkAnim_Enemy1.PushBack({ 2848, 2187, 316, 312 });
	leftDownWalkAnim_Enemy1.PushBack({ 3165, 2187, 316, 312 });
	leftDownWalkAnim_Enemy1.PushBack({ 3481, 2187, 316, 312 });
	leftDownWalkAnim_Enemy1.loop = true;
	leftDownWalkAnim_Enemy1.speed = 0.05f;

	rightUpWalkAnim_Enemy1.PushBack({ 719, 937, 316, 312 });
	rightUpWalkAnim_Enemy1.PushBack({ 633, 937, 316, 312 });
	rightUpWalkAnim_Enemy1.PushBack({ 949, 937, 316, 312 });
	rightUpWalkAnim_Enemy1.PushBack({ 1266, 937, 316, 312 });
	rightUpWalkAnim_Enemy1.PushBack({ 1582, 937, 316, 312 });
	rightUpWalkAnim_Enemy1.PushBack({ 1899, 937, 316, 312 });
	rightUpWalkAnim_Enemy1.PushBack({ 2215, 937, 316, 312 });
	rightUpWalkAnim_Enemy1.PushBack({ 2532, 937, 316, 312 });
	rightUpWalkAnim_Enemy1.PushBack({ 2848, 937, 316, 312 });
	rightUpWalkAnim_Enemy1.PushBack({ 3165, 937, 316, 312 });
	rightUpWalkAnim_Enemy1.PushBack({ 3481, 937, 316, 312 });
	rightUpWalkAnim_Enemy1.loop = true;
	rightUpWalkAnim_Enemy1.speed = 0.05f;

	leftUpWalkAnim_Enemy1.PushBack({ 316, 312, 316, 312 });
	leftUpWalkAnim_Enemy1.PushBack({ 633, 312, 316, 312 });
	leftUpWalkAnim_Enemy1.PushBack({ 949, 312, 316, 312 });
	leftUpWalkAnim_Enemy1.PushBack({ 1266, 312, 316, 312 });
	leftUpWalkAnim_Enemy1.PushBack({ 1582, 312, 316, 312 });
	leftUpWalkAnim_Enemy1.PushBack({ 1899, 312, 316, 312 });
	leftUpWalkAnim_Enemy1.PushBack({ 2215, 312, 316, 312 });
	leftUpWalkAnim_Enemy1.PushBack({ 2532, 312, 316, 312 });
	leftUpWalkAnim_Enemy1.PushBack({ 2848, 312, 316, 312 });
	leftUpWalkAnim_Enemy1.PushBack({ 3165, 312, 316, 312 });
	leftUpWalkAnim_Enemy1.PushBack({ 3481, 312, 316, 312 });
	leftUpWalkAnim_Enemy1.loop = true;
	leftUpWalkAnim_Enemy1.speed = 0.05f;


	//ATTACK

	rightAttackAnim_Enemy1.PushBack({ 0, 1250, 316, 312 });
	rightAttackAnim_Enemy1.PushBack({ 3798, 1250, 316, 312 });
	rightAttackAnim_Enemy1.PushBack({ 4114, 1250, 316, 312 });
	rightAttackAnim_Enemy1.PushBack({ 4431, 1250, 316, 312 });
	rightAttackAnim_Enemy1.PushBack({ 4747, 1250, 316, 312 });
	rightAttackAnim_Enemy1.PushBack({ 5064, 1250, 316, 312 });
	rightAttackAnim_Enemy1.loop = true;
	rightAttackAnim_Enemy1.speed = 0.05f;

	leftAttackAnim_Enemy1.PushBack({ 0, 0, 316, 312 });
	leftAttackAnim_Enemy1.PushBack({ 3798, 0, 316, 312 });
	leftAttackAnim_Enemy1.PushBack({ 4114, 0, 316, 312 });
	leftAttackAnim_Enemy1.PushBack({ 4431, 0, 316, 312 });
	leftAttackAnim_Enemy1.PushBack({ 4747, 0, 316, 312 });
	leftAttackAnim_Enemy1.PushBack({ 5064, 0, 316, 312 });
	leftAttackAnim_Enemy1.loop = true;
	leftAttackAnim_Enemy1.speed = 0.05f;

	downAttackAnim_Enemy1.PushBack({ 0, 1875, 316, 312 });
	downAttackAnim_Enemy1.PushBack({ 3798, 1875, 316, 312 });
	downAttackAnim_Enemy1.PushBack({ 4114, 1875, 316, 312 });
	downAttackAnim_Enemy1.PushBack({ 4431, 1875, 316, 312 });
	downAttackAnim_Enemy1.PushBack({ 4747, 1875, 316, 312 });
	downAttackAnim_Enemy1.PushBack({ 5064, 1875, 316, 312 });
	downAttackAnim_Enemy1.loop = true;
	downAttackAnim_Enemy1.speed = 0.05f;

	upAttackAnim_Enemy1.PushBack({ 0, 625, 316, 312 });
	upAttackAnim_Enemy1.PushBack({ 3798, 625, 316, 312 });
	upAttackAnim_Enemy1.PushBack({ 4114, 625, 316, 312 });
	upAttackAnim_Enemy1.PushBack({ 4431, 625, 316, 312 });
	upAttackAnim_Enemy1.PushBack({ 4747, 625, 316, 312 });
	upAttackAnim_Enemy1.PushBack({ 5064, 625, 316, 312 });
	upAttackAnim_Enemy1.loop = true;
	upAttackAnim_Enemy1.speed = 0.05f;

	rightDownAttackAnim_Enemy1.PushBack({ 0, 1562, 316, 312 });
	rightDownAttackAnim_Enemy1.PushBack({ 3798, 1562, 316, 312 });
	rightDownAttackAnim_Enemy1.PushBack({ 4114, 1562, 316, 312 });
	rightDownAttackAnim_Enemy1.PushBack({ 4431, 1562, 316, 312 });
	rightDownAttackAnim_Enemy1.PushBack({ 4747, 1562, 316, 312 });
	rightDownAttackAnim_Enemy1.PushBack({ 5064, 1562, 316, 312 });
	rightDownAttackAnim_Enemy1.loop = true;
	rightDownAttackAnim_Enemy1.speed = 0.05f;


	leftDownAttackAnim_Enemy1.PushBack({ 0, 2187, 316, 312 });
	leftDownAttackAnim_Enemy1.PushBack({ 3798, 2187, 316, 312 });
	leftDownAttackAnim_Enemy1.PushBack({ 4114, 2187, 316, 312 });
	leftDownAttackAnim_Enemy1.PushBack({ 4431, 2187, 316, 312 });
	leftDownAttackAnim_Enemy1.PushBack({ 4747, 2187, 316, 312 });
	leftDownAttackAnim_Enemy1.PushBack({ 5064, 2187, 316, 312 });
	leftDownAttackAnim_Enemy1.loop = true;
	leftDownAttackAnim_Enemy1.speed = 0.05f;

	rightUpAttackAnim_Enemy1.PushBack({ 0, 937, 316, 312 });
	rightUpAttackAnim_Enemy1.PushBack({ 3798, 937, 316, 312 });
	rightUpAttackAnim_Enemy1.PushBack({ 4114, 937, 316, 312 });
	rightUpAttackAnim_Enemy1.PushBack({ 4431, 937, 316, 312 });
	rightUpAttackAnim_Enemy1.PushBack({ 4747, 937, 316, 312 });
	rightUpAttackAnim_Enemy1.PushBack({ 5064, 937, 316, 312 });
	rightUpAttackAnim_Enemy1.loop = true;
	rightUpAttackAnim_Enemy1.speed = 0.05f;

	leftUpAttackAnim_Enemy1.PushBack({ 0, 312, 316, 312 });
	leftUpAttackAnim_Enemy1.PushBack({ 3798, 312, 316, 312 });
	leftUpAttackAnim_Enemy1.PushBack({ 4114, 312, 316, 312 });
	leftUpAttackAnim_Enemy1.PushBack({ 4431, 312, 316, 312 });
	leftUpAttackAnim_Enemy1.PushBack({ 4747, 312, 316, 312 });
	leftUpAttackAnim_Enemy1.PushBack({ 5064, 312, 316, 312 });
	leftUpAttackAnim_Enemy1.loop = true;
	leftUpAttackAnim_Enemy1.speed = 0.05f;


	

	//DIE

	rightDieAnim_Enemy1.PushBack({ 0, 1250, 316, 312 });
	rightDieAnim_Enemy1.PushBack({ 5380, 1250, 316, 312 });
	rightDieAnim_Enemy1.PushBack({ 5697, 1250, 316, 312 });
	rightDieAnim_Enemy1.PushBack({ 6013, 1250, 316, 312 });
	rightDieAnim_Enemy1.PushBack({ 6330, 1250, 316, 312 });
	rightDieAnim_Enemy1.PushBack({ 6646, 1250, 316, 312 });
	rightDieAnim_Enemy1.PushBack({ 6963, 1250, 316, 312 });
	rightDieAnim_Enemy1.PushBack({ 7279, 1250, 316, 312 });
	rightDieAnim_Enemy1.PushBack({ 7596, 1250, 316, 312 });
	rightDieAnim_Enemy1.PushBack({ 7912, 1250, 316, 312 });
	rightDieAnim_Enemy1.PushBack({ 8229, 1250, 316, 312 });
	rightDieAnim_Enemy1.PushBack({ 8545, 1250, 316, 312 });
	rightDieAnim_Enemy1.PushBack({ 8862, 1250, 316, 312 });
	rightDieAnim_Enemy1.PushBack({ 9178, 1250, 316, 312 });
	rightDieAnim_Enemy1.PushBack({ 9495, 1250, 316, 312 });
	rightDieAnim_Enemy1.PushBack({ 9811, 1250, 316, 312 });
	rightDieAnim_Enemy1.loop = true;
	rightDieAnim_Enemy1.speed = 0.05f;

	leftDieAnim_Enemy1.PushBack({ 0, 0, 316, 312 });
	leftDieAnim_Enemy1.PushBack({ 5380, 0, 316, 312 });
	leftDieAnim_Enemy1.PushBack({ 5697, 0, 316, 312 });
	leftDieAnim_Enemy1.PushBack({ 6013, 0, 316, 312 });
	leftDieAnim_Enemy1.PushBack({ 6330, 0, 316, 312 });
	leftDieAnim_Enemy1.PushBack({ 6646, 0, 316, 312 });
	leftDieAnim_Enemy1.PushBack({ 6963, 0, 316, 312 });
	leftDieAnim_Enemy1.PushBack({ 7279, 0, 316, 312 });
	leftDieAnim_Enemy1.PushBack({ 7596, 0, 316, 312 });
	leftDieAnim_Enemy1.PushBack({ 7912, 0, 316, 312 });
	leftDieAnim_Enemy1.PushBack({ 8229, 0, 316, 312 });
	leftDieAnim_Enemy1.PushBack({ 8545, 0, 316, 312 });
	leftDieAnim_Enemy1.PushBack({ 8862, 0, 316, 312 });
	leftDieAnim_Enemy1.PushBack({ 9178, 0, 316, 312 });
	leftDieAnim_Enemy1.PushBack({ 9495, 0, 316, 312 });
	leftDieAnim_Enemy1.PushBack({ 9811, 0, 316, 312 });
	leftDieAnim_Enemy1.loop = true;
	leftDieAnim_Enemy1.speed = 0.05f;

	downDieAnim_Enemy1.PushBack({ 0, 1875, 316, 312 });
	downDieAnim_Enemy1.PushBack({ 5380, 1875, 316, 312 });
	downDieAnim_Enemy1.PushBack({ 5697, 1875, 316, 312 });
	downDieAnim_Enemy1.PushBack({ 6013, 1875, 316, 312 });
	downDieAnim_Enemy1.PushBack({ 6330, 1875, 316, 312 });
	downDieAnim_Enemy1.PushBack({ 6646, 1875, 316, 312 });
	downDieAnim_Enemy1.PushBack({ 6963, 1875, 316, 312 });
	downDieAnim_Enemy1.PushBack({ 7279, 1875, 316, 312 });
	downDieAnim_Enemy1.PushBack({ 7596, 1875, 316, 312 });
	downDieAnim_Enemy1.PushBack({ 7912, 1875, 316, 312 });
	downDieAnim_Enemy1.PushBack({ 8229, 1875, 316, 312 });
	downDieAnim_Enemy1.PushBack({ 8545, 1875, 316, 312 });
	downDieAnim_Enemy1.PushBack({ 8862, 1875, 316, 312 });
	downDieAnim_Enemy1.PushBack({ 9178, 1875, 316, 312 });
	downDieAnim_Enemy1.PushBack({ 9495, 1875, 316, 312 });
	downDieAnim_Enemy1.PushBack({ 9811, 1875, 316, 312 });
	downDieAnim_Enemy1.loop = true;
	downDieAnim_Enemy1.speed = 0.05f;

	upDieAnim_Enemy1.PushBack({ 0, 625, 316, 312 });
	upDieAnim_Enemy1.PushBack({ 5380, 625, 316, 312 });
	upDieAnim_Enemy1.PushBack({ 5697, 625, 316, 312 });
	upDieAnim_Enemy1.PushBack({ 6013, 625, 316, 312 });
	upDieAnim_Enemy1.PushBack({ 6330, 625, 316, 312 });
	upDieAnim_Enemy1.PushBack({ 6646, 625, 316, 312 });
	upDieAnim_Enemy1.PushBack({ 6963, 625, 316, 312 });
	upDieAnim_Enemy1.PushBack({ 7279, 625, 316, 312 });
	upDieAnim_Enemy1.PushBack({ 7596, 625, 316, 312 });
	upDieAnim_Enemy1.PushBack({ 7912, 625, 316, 312 });
	upDieAnim_Enemy1.PushBack({ 8229, 625, 316, 312 });
	upDieAnim_Enemy1.PushBack({ 8545, 625, 316, 312 });
	upDieAnim_Enemy1.PushBack({ 8862, 625, 316, 312 });
	upDieAnim_Enemy1.PushBack({ 9178, 625, 316, 312 });
	upDieAnim_Enemy1.PushBack({ 9495, 625, 316, 312 });
	upDieAnim_Enemy1.PushBack({ 9811, 625, 316, 312 });
	upDieAnim_Enemy1.speed = 0.05f;

	rightDownDieAnim_Enemy1.PushBack({ 0, 1562, 316, 312 });
	rightDownDieAnim_Enemy1.PushBack({ 5380, 1562, 316, 312 });
	rightDownDieAnim_Enemy1.PushBack({ 5697, 1562, 316, 312 });
	rightDownDieAnim_Enemy1.PushBack({ 6013, 1562, 316, 312 });
	rightDownDieAnim_Enemy1.PushBack({ 6330, 1562, 316, 312 });
	rightDownDieAnim_Enemy1.PushBack({ 6646, 1562, 316, 312 });
	rightDownDieAnim_Enemy1.PushBack({ 6963, 1562, 316, 312 });
	rightDownDieAnim_Enemy1.PushBack({ 7279, 1562, 316, 312 });
	rightDownDieAnim_Enemy1.PushBack({ 7596, 1562, 316, 312 });
	rightDownDieAnim_Enemy1.PushBack({ 7912, 1562, 316, 312 });
	rightDownDieAnim_Enemy1.PushBack({ 8229, 1562, 316, 312 });
	rightDownDieAnim_Enemy1.PushBack({ 8545, 1562, 316, 312 });
	rightDownDieAnim_Enemy1.PushBack({ 8862, 1562, 316, 312 });
	rightDownDieAnim_Enemy1.PushBack({ 9178, 1562, 316, 312 });
	rightDownDieAnim_Enemy1.PushBack({ 9495, 1562, 316, 312 });
	rightDownDieAnim_Enemy1.PushBack({ 9811, 1562, 316, 312 });
	rightDownDieAnim_Enemy1.loop = true;
	rightDownDieAnim_Enemy1.speed = 0.05f;

	leftDownDieAnim_Enemy1.PushBack({ 0, 2187, 316, 312 });
	leftDownDieAnim_Enemy1.PushBack({ 5380, 2187, 316, 312 });
	leftDownDieAnim_Enemy1.PushBack({ 5697, 2187, 316, 312 });
	leftDownDieAnim_Enemy1.PushBack({ 6013, 2187, 316, 312 });
	leftDownDieAnim_Enemy1.PushBack({ 6330, 2187, 316, 312 });
	leftDownDieAnim_Enemy1.PushBack({ 6646, 2187, 316, 312 });
	leftDownDieAnim_Enemy1.PushBack({ 6963, 2187, 316, 312 });
	leftDownDieAnim_Enemy1.PushBack({ 7279, 2187, 316, 312 });
	leftDownDieAnim_Enemy1.PushBack({ 7596, 2187, 316, 312 });
	leftDownDieAnim_Enemy1.PushBack({ 7912, 2187, 316, 312 });
	leftDownDieAnim_Enemy1.PushBack({ 8229, 2187, 316, 312 });
	leftDownDieAnim_Enemy1.PushBack({ 8545, 2187, 316, 312 });
	leftDownDieAnim_Enemy1.PushBack({ 8862, 2187, 316, 312 });
	leftDownDieAnim_Enemy1.PushBack({ 9178, 2187, 316, 312 });
	leftDownDieAnim_Enemy1.PushBack({ 9495, 2187, 316, 312 });
	leftDownDieAnim_Enemy1.PushBack({ 9811, 2187, 316, 312 });
	leftDownDieAnim_Enemy1.loop = true;
	leftDownDieAnim_Enemy1.speed = 0.05f;

	rightUpDieAnim_Enemy1.PushBack({ 0, 937, 316, 312 });
	rightUpDieAnim_Enemy1.PushBack({ 5380, 937, 316, 312 });
	rightUpDieAnim_Enemy1.PushBack({ 5697, 937, 316, 312 });
	rightUpDieAnim_Enemy1.PushBack({ 6013, 937, 316, 312 });
	rightUpDieAnim_Enemy1.PushBack({ 6330, 937, 316, 312 });
	rightUpDieAnim_Enemy1.PushBack({ 6646, 937, 316, 312 });
	rightUpDieAnim_Enemy1.PushBack({ 6963, 937, 316, 312 });
	rightUpDieAnim_Enemy1.PushBack({ 7279, 937, 316, 312 });
	rightUpDieAnim_Enemy1.PushBack({ 7596, 937, 316, 312 });
	rightUpDieAnim_Enemy1.PushBack({ 7912, 937, 316, 312 });
	rightUpDieAnim_Enemy1.PushBack({ 8229, 937, 316, 312 });
	rightUpDieAnim_Enemy1.PushBack({ 8545, 937, 316, 312 });
	rightUpDieAnim_Enemy1.PushBack({ 8862, 937, 316, 312 });
	rightUpDieAnim_Enemy1.PushBack({ 9178, 937, 316, 312 });
	rightUpDieAnim_Enemy1.PushBack({ 9495, 937, 316, 312 });
	rightUpDieAnim_Enemy1.PushBack({ 9811, 937, 316, 312 });
	rightUpDieAnim_Enemy1.loop = true;
	rightUpDieAnim_Enemy1.speed = 0.05f;

	leftUpDieAnim_Enemy1.PushBack({ 0, 312, 316, 312 });
	leftUpDieAnim_Enemy1.PushBack({ 5380, 312, 316, 312 });
	leftUpDieAnim_Enemy1.PushBack({ 5697, 312, 316, 312 });
	leftUpDieAnim_Enemy1.PushBack({ 6013, 312, 316, 312 });
	leftUpDieAnim_Enemy1.PushBack({ 6330, 312, 316, 312 });
	leftUpDieAnim_Enemy1.PushBack({ 6646, 312, 316, 312 });
	leftUpDieAnim_Enemy1.PushBack({ 6963, 312, 316, 312 });
	leftUpDieAnim_Enemy1.PushBack({ 7279, 312, 316, 312 });
	leftUpDieAnim_Enemy1.PushBack({ 7596, 312, 316, 312 });
	leftUpDieAnim_Enemy1.PushBack({ 7912, 312, 316, 312 });
	leftUpDieAnim_Enemy1.PushBack({ 8229, 312, 316, 312 });
	leftUpDieAnim_Enemy1.PushBack({ 8545, 312, 316, 312 });
	leftUpDieAnim_Enemy1.PushBack({ 8862, 312, 316, 312 });
	leftUpDieAnim_Enemy1.PushBack({ 9178, 312, 316, 312 });
	leftUpDieAnim_Enemy1.PushBack({ 9495, 312, 316, 312 });
	leftUpDieAnim_Enemy1.PushBack({ 9811, 312, 316, 312 });
	leftUpDieAnim_Enemy1.loop = true;
	leftUpDieAnim_Enemy1.speed = 0.05f;



	position.x = x;
	position.y = y;

	offsetX = -145;
	offsetY = -125;

	collider = app->collisions->AddCollider({ position.x, position.y, 25, 56 }, Collider::Type::ENEMY, (Module*)app->entity_manager);

	Mini_Boss_Two_List.add(app->physics->CreateZombieStandartBox(position.x, position.y, 25, 10));



}

void Mini_Boss_Two::Update(float dt)
{
	//ADD THE PATHFINDING LOGIC FOR MOVEMENT
	if (app->player->inBossBatle == false)
	{
		iPoint NewPosition = position;
		collider->SetPos(NewPosition.x, NewPosition.y);
		Mini_Boss_Two_List.end->data->GetPosition(NewPosition.x, NewPosition.y);
		currentAnim = nullptr;
	}
	if (app->player->inBossBatle == true)
	{

		if (EntityHP > 0)
		{

			if (app->player->pauseMenu == true)
			{
				iPoint NewPosition = position;
				collider->SetPos(NewPosition.x, NewPosition.y);
				Mini_Boss_Two_List.end->data->GetPosition(NewPosition.x, NewPosition.y);
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
							Mini_Boss_Two_List.end->data->GetPosition(position.x, position.y);
							currentAnim = &idleDownAnim_Enemy1;
							currentAnim->loop = true;

							if (position.x > app->inventoryMenu->ActiveRadioPosition.x)
							{
								if (currentAnim != &leftWalkAnim_Enemy1)
								{
									//leftWalkAnim_Enemy1.Reset();
									currentAnim = &leftWalkAnim_Enemy1;
								}
								Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ -0.5f, 0.0f });
							}
							if (position.x < app->inventoryMenu->ActiveRadioPosition.x)
							{
								if (currentAnim != &rightWalkAnim_Enemy1)
								{
									//rightWalkAnim_Enemy1.Reset();
									currentAnim = &rightWalkAnim_Enemy1;
								}
								Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ 0.5f, 0.0f });
							}
							if (position.y > app->inventoryMenu->ActiveRadioPosition.y)
							{
								if (currentAnim != &upWalkAnim_Enemy1)
								{
									//upWalkAnim_Enemy1.Reset();
									currentAnim = &upWalkAnim_Enemy1;
								}
								Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ 0.0f, -0.5f });
							}
							if (position.y < app->inventoryMenu->ActiveRadioPosition.y)
							{
								if (currentAnim != &downWalkAnim_Enemy1)
								{
									//downWalkAnim_Enemy1.Reset();
									currentAnim = &downWalkAnim_Enemy1;
								}
								Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ 0.0f, 0.5f });
							}


							if ((app->inventoryMenu->ActiveRadioPosition.y > position.y) && (app->inventoryMenu->ActiveRadioPosition.x > position.x))
							{
								if (currentAnim != &rightDownWalkAnim_Enemy1)
								{
									//rightDownWalkAnim_Enemy1.Reset();
									currentAnim = &rightDownWalkAnim_Enemy1;
								}
								Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ 0.5f, 0.5f });
							}
							if ((app->inventoryMenu->ActiveRadioPosition.x < position.x) && (app->inventoryMenu->ActiveRadioPosition.y > position.y))
							{
								if (currentAnim != &leftDownWalkAnim_Enemy1)
								{
									//rightDownWalkAnim_Enemy1.Reset();
									currentAnim = &leftDownWalkAnim_Enemy1;
								}
								Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ -0.5f, 0.5f });
							}
							if ((app->inventoryMenu->ActiveRadioPosition.y < position.y) && (app->inventoryMenu->ActiveRadioPosition.x < position.x))
							{
								if (currentAnim != &leftUpWalkAnim_Enemy1)
								{
									//leftUpWalkAnim_Enemy1.Reset();
									currentAnim = &leftUpWalkAnim_Enemy1;
								}
								Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ -0.5f, -0.5f });
							}
							if ((app->inventoryMenu->ActiveRadioPosition.x > position.x) && (app->inventoryMenu->ActiveRadioPosition.y < position.y))
							{
								if (currentAnim != &rightUpWalkAnim_Enemy1)
								{
									//leftUpWalkAnim_Enemy1.Reset();
									currentAnim = &rightUpWalkAnim_Enemy1;
								}
								Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ 0.5f, -0.5f });
							}
						}
						else
						{
							collider->SetPos(position.x, position.y);
							Mini_Boss_Two_List.end->data->GetPosition(position.x, position.y);
							currentAnim = &idleDownAnim_Enemy1;
							currentAnim->loop = true;

							Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ 0.0f,0.0f });

						}
					}
					if (app->inventoryMenu->ActiveRadioAlive == false)
					{
						if (position.DistanceTo(app->player->position) < 300)
						{
							collider->SetPos(position.x, position.y);
							Mini_Boss_Two_List.end->data->GetPosition(position.x, position.y);
							currentAnim = &idleDownAnim_Enemy1;
							currentAnim->loop = true;

							if (position.x > app->player->position.x + app->player->collider->rect.w / 2)
							{
								if (currentAnim != &leftWalkAnim_Enemy1)
								{
									//leftWalkAnim_Enemy1.Reset();
									currentAnim = &leftWalkAnim_Enemy1;
								}
								Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ -0.5f, 0.0f });
							}
							if (position.x < app->player->position.x + app->player->collider->rect.w / 2)
							{
								if (currentAnim != &rightWalkAnim_Enemy1)
								{
									//rightWalkAnim_Enemy1.Reset();
									currentAnim = &rightWalkAnim_Enemy1;
								}
								Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ 0.5f, 0.0f });
							}
							if (position.y > app->player->position.y - app->player->collider->rect.h)
							{
								if (currentAnim != &upWalkAnim_Enemy1)
								{
									//upWalkAnim_Enemy1.Reset();
									currentAnim = &upWalkAnim_Enemy1;
								}
								Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ 0.0f, -0.5f });
							}
							if (position.y < app->player->position.y - app->player->collider->rect.h)
							{
								if (currentAnim != &downWalkAnim_Enemy1)
								{
									//downWalkAnim_Enemy1.Reset();
									currentAnim = &downWalkAnim_Enemy1;
								}
								Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ 0.0f, 0.5f });
							}


							if ((app->player->position.y - app->player->collider->rect.h > position.y) && (app->player->position.x + app->player->collider->rect.w / 2 > position.x))
							{
								if (currentAnim != &rightDownWalkAnim_Enemy1)
								{
									//rightDownWalkAnim_Enemy1.Reset();
									currentAnim = &rightDownWalkAnim_Enemy1;
								}
								Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ 0.5f, 0.5f });
							}
							if ((app->player->position.x + app->player->collider->rect.w / 2 < position.x) && (app->player->position.y - app->player->collider->rect.h > position.y))
							{
								if (currentAnim != &leftDownWalkAnim_Enemy1)
								{
									//rightDownWalkAnim_Enemy1.Reset();
									currentAnim = &leftDownWalkAnim_Enemy1;
								}
								Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ -0.5f, 0.5f });
							}
							if ((app->player->position.y - app->player->collider->rect.h < position.y) && (app->player->position.x + app->player->collider->rect.w / 2 < position.x))
							{
								if (currentAnim != &leftUpWalkAnim_Enemy1)
								{
									//leftUpWalkAnim_Enemy1.Reset();
									currentAnim = &leftUpWalkAnim_Enemy1;
								}
								Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ -0.5f, -0.5f });
							}
							if ((app->player->position.x + app->player->collider->rect.w / 2 > position.x) && (app->player->position.y - app->player->collider->rect.h < position.y))
							{
								if (currentAnim != &rightUpWalkAnim_Enemy1)
								{
									//leftUpWalkAnim_Enemy1.Reset();
									currentAnim = &rightUpWalkAnim_Enemy1;
								}
								Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ 0.5f, -0.5f });
							}
						}
						else
						{
							collider->SetPos(position.x, position.y);
							Mini_Boss_Two_List.end->data->GetPosition(position.x, position.y);
							currentAnim = &idleDownAnim_Enemy1;
							currentAnim->loop = true;

							Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ 0.0f,0.0f });

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
							Mini_Boss_Two_List.end->data->GetPosition(position.x, position.y);
							currentAnim = &idleDownAnim_Enemy1;
							currentAnim->loop = true;

							Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ 0.0f,0.0f });

						}
						if (entityTurn == TurnState::StartOfTurn)
						{
							collider->SetPos(position.x, position.y);
							currentAnim = &idleDownAnim_Enemy1;
							currentAnim->loop = false;
							Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ 0.0f, 0.0f }); //movimiento contrario a la direccion del jugador cuando nos chocamos con el

							entityTurn = TurnState::MidOfTurn;

						}
						if (entityTurn == TurnState::MidOfTurn)
						{

							collider->SetPos(position.x, position.y);
							Mini_Boss_Two_List.end->data->GetPosition(position.x, position.y);
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
									Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ -0.5f, 0.0f });
								}
								if (position.x < app->player->position.x + app->player->collider->rect.w / 2)
								{
									if (currentAnim != &rightWalkAnim_Enemy1)
									{
										//rightWalkAnim_Enemy1.Reset();
										currentAnim = &rightWalkAnim_Enemy1;
									}
									Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ 0.5f, 0.0f });
								}
								if (position.y > app->player->position.y - app->player->collider->rect.h)
								{
									if (currentAnim != &upWalkAnim_Enemy1)
									{
										//upWalkAnim_Enemy1.Reset();
										currentAnim = &upWalkAnim_Enemy1;
									}
									Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ 0.0f, -0.5f });
								}
								if (position.y < app->player->position.y - app->player->collider->rect.h)
								{
									if (currentAnim != &downWalkAnim_Enemy1)
									{
										//downWalkAnim_Enemy1.Reset();
										currentAnim = &downWalkAnim_Enemy1;
									}
									Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ 0.0f, 0.5f });
								}


								if ((app->player->position.y - app->player->collider->rect.h > position.y) && (app->player->position.x + app->player->collider->rect.w / 2 > position.x))
								{
									if (currentAnim != &rightDownWalkAnim_Enemy1)
									{
										//rightDownWalkAnim_Enemy1.Reset();
										currentAnim = &rightDownWalkAnim_Enemy1;
									}
									Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ 0.5f, 0.5f });
								}
								if ((app->player->position.x + app->player->collider->rect.w / 2 < position.x) && (app->player->position.y - app->player->collider->rect.h > position.y))
								{
									if (currentAnim != &leftDownWalkAnim_Enemy1)
									{
										//rightDownWalkAnim_Enemy1.Reset();
										currentAnim = &leftDownWalkAnim_Enemy1;
									}
									Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ -0.5f, 0.5f });
								}
								if ((app->player->position.y - app->player->collider->rect.h < position.y) && (app->player->position.x + app->player->collider->rect.w / 2 < position.x))
								{
									if (currentAnim != &leftUpWalkAnim_Enemy1)
									{
										//leftUpWalkAnim_Enemy1.Reset();
										currentAnim = &leftUpWalkAnim_Enemy1;
									}
									Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ -0.5f, -0.5f });
								}
								if ((app->player->position.x + app->player->collider->rect.w / 2 > position.x) && (app->player->position.y - app->player->collider->rect.h < position.y))
								{
									if (currentAnim != &rightUpWalkAnim_Enemy1)
									{
										//leftUpWalkAnim_Enemy1.Reset();
										currentAnim = &rightUpWalkAnim_Enemy1;
									}
									Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ 0.5f, -0.5f });
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
							Mini_Boss_Two_List.end->data->body->SetLinearVelocity({ 0.0f, 0.0f });
							collider->SetPos(position.x, position.y);
							Mini_Boss_Two_List.end->data->GetPosition(position.x, position.y);

							currentAnim = &idleDownAnim_Enemy1;
							currentAnim->loop = true;

							if (position.DistanceTo({ app->player->position.x + app->player->collider->rect.w / 2, app->player->position.y - app->player->collider->rect.h }) < 75)
							{

								if ((position.x == app->player->position.x + app->player->collider->rect.w / 2) && (position.y < app->player->position.y - app->player->collider->rect.h))
								{

									app->particles->AddParticle(app->particles->enemyAttack, position.x, position.y + 30, Collider::Type::BOSS_ATTACK_2);

								}
								if ((position.x == app->player->position.x + app->player->collider->rect.w / 2) && (position.y > app->player->position.y - app->player->collider->rect.h))
								{

									app->particles->AddParticle(app->particles->enemyAttack, position.x, position.y - 30, Collider::Type::BOSS_ATTACK_2);

								}
								if ((position.x < app->player->position.x + app->player->collider->rect.w / 2) && (position.y == app->player->position.y - app->player->collider->rect.h))
								{


									app->particles->AddParticle(app->particles->enemyAttack, position.x + 30, position.y, Collider::Type::BOSS_ATTACK_2);


								}
								if ((position.x > app->player->position.x + app->player->collider->rect.w / 2) && (position.y == app->player->position.y - app->player->collider->rect.h))
								{

									app->particles->AddParticle(app->particles->enemyAttack, position.x - 30, position.y, Collider::Type::BOSS_ATTACK_2);


								}

								if ((position.x > app->player->position.x + app->player->collider->rect.w / 2) && (position.y > app->player->position.y - app->player->collider->rect.h))
								{


									app->particles->AddParticle(app->particles->enemyAttack, position.x - 30, position.y - 30, Collider::Type::BOSS_ATTACK_2);


								}
								if ((position.x > app->player->position.x + app->player->collider->rect.w / 2) && (position.y < app->player->position.y - app->player->collider->rect.h))
								{

									app->particles->AddParticle(app->particles->enemyAttack, position.x - 30, position.y + 30, Collider::Type::BOSS_ATTACK_2);


								}
								if ((position.x < app->player->position.x + app->player->collider->rect.w / 2) && (position.y > app->player->position.y - app->player->collider->rect.h))
								{

									app->particles->AddParticle(app->particles->enemyAttack, position.x + 30, position.y - 30, Collider::Type::BOSS_ATTACK_2);


								}
								if ((position.x < app->player->position.x + app->player->collider->rect.w / 2) && (position.y < app->player->position.y - app->player->collider->rect.h))
								{

									app->particles->AddParticle(app->particles->enemyAttack, position.x + 30, position.y + 30, Collider::Type::BOSS_ATTACK_2);


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
							Mini_Boss_Two_List.end->data->GetPosition(position.x, position.y);
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






}


