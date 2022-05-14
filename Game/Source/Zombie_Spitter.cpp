#include "Zombie_Spitter.h"

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
#include "Pathfinding.h"
#include "SceneMainMap.h"
#include "Render.h"
#include "Textures.h"
#include "Log.h"
#include "ModulePhysics.h"
#include "ModuleParticles.h"
#include "InventoryMenu.h"
#include "Defs.h"

Zombie_Spitter::Zombie_Spitter(int x,int y) : Entity(x,y)
{	
	EntityHP = 1;
	EntityAP = 5;
	EntityMP = 3;
	entityState = GameState::OutOfCombat;
	entityTurn = TurnState::NONE;
	counter = 0;
	//HERE WE ADD THE ANIMATIONS WITH GIMP
	
	
	//IDLE

	idleRightAnim_Enemy1.PushBack({ 88, 603, 85, 144 });
	idleRightAnim_Enemy1.PushBack({ 246, 603, 85, 144 });
	idleRightAnim_Enemy1.PushBack({ 403, 603, 85, 144 });
	idleRightAnim_Enemy1.PushBack({ 560, 603, 85, 144 });
	idleRightAnim_Enemy1.loop = true;
	idleRightAnim_Enemy1.speed = 0.3f;

	idleLeftAnim_Enemy1.PushBack({ 88, 27, 85, 144 });
	idleLeftAnim_Enemy1.PushBack({ 246, 27, 85, 144 });
	idleLeftAnim_Enemy1.PushBack({ 403, 27, 85, 144 });
	idleLeftAnim_Enemy1.PushBack({ 560, 27, 85, 144 });
	idleLeftAnim_Enemy1.loop = true;
	idleLeftAnim_Enemy1.speed = 0.3f;

	idleDownAnim_Enemy1.PushBack({ 88, 891, 85, 144 });  //idle_enemy
	idleDownAnim_Enemy1.PushBack({ 246, 891, 85, 144 });
	idleDownAnim_Enemy1.PushBack({ 403, 891, 85, 144 });
	idleDownAnim_Enemy1.PushBack({ 560, 891, 85, 144 });
	idleDownAnim_Enemy1.loop = true;
	idleDownAnim_Enemy1.speed = 0.3f;

	idleUpAnim_Enemy1.PushBack({ 88, 315, 85, 144 });
	idleUpAnim_Enemy1.PushBack({ 246, 315, 85, 144 });
	idleUpAnim_Enemy1.PushBack({ 403, 315, 85, 144 });
	idleUpAnim_Enemy1.PushBack({ 560, 315, 85, 144 });
	idleUpAnim_Enemy1.loop = true;
	idleUpAnim_Enemy1.speed = 0.3f;

	idleUpLeftAnim_Enemy1.PushBack({ 88, 171, 85, 144 });
	idleUpLeftAnim_Enemy1.PushBack({ 246, 171, 85, 144 });
	idleUpLeftAnim_Enemy1.PushBack({ 403, 171, 85, 144 });
	idleUpLeftAnim_Enemy1.PushBack({ 560, 171, 85, 144 });
	idleUpLeftAnim_Enemy1.loop = true;
	idleUpLeftAnim_Enemy1.speed = 0.3f;

	idleUpRightAnim_Enemy1.PushBack({ 88, 459, 85, 144 });
	idleUpRightAnim_Enemy1.PushBack({ 246, 459, 85, 144 });
	idleUpRightAnim_Enemy1.PushBack({ 403, 459, 85, 144 });
	idleUpRightAnim_Enemy1.PushBack({ 560, 459, 85, 144 });
	idleUpRightAnim_Enemy1.loop = true;
	idleUpRightAnim_Enemy1.speed = 0.3f;

	idleDownLeftAnim_Enemy1.PushBack({ 88, 1035, 85, 144 });
	idleDownLeftAnim_Enemy1.PushBack({ 246, 1035, 85, 144 });
	idleDownLeftAnim_Enemy1.PushBack({ 403, 1035, 85, 144 });
	idleDownLeftAnim_Enemy1.PushBack({ 560, 1035, 85, 144 });
	idleDownLeftAnim_Enemy1.loop = true;
	idleDownLeftAnim_Enemy1.speed = 0.3f;

	idleDownRightAnim_Enemy1.PushBack({ 88, 747, 85, 144 });
	idleDownRightAnim_Enemy1.PushBack({ 246, 747, 85, 144 });
	idleDownRightAnim_Enemy1.PushBack({ 403, 747, 85, 144 });
	idleDownRightAnim_Enemy1.PushBack({ 560, 747, 85, 144 });
	idleDownRightAnim_Enemy1.loop = true;
	idleDownRightAnim_Enemy1.speed = 0.3f;



	//WALK

	rightWalkAnim_Enemy1.PushBack({ 719, 603, 85, 144 });
	rightWalkAnim_Enemy1.PushBack({ 876, 603, 85, 144 });
	rightWalkAnim_Enemy1.PushBack({ 1033, 603, 85, 144 });
	rightWalkAnim_Enemy1.PushBack({ 1190, 603, 85, 144 });
	rightWalkAnim_Enemy1.PushBack({ 1348, 603, 85, 144 });
	rightWalkAnim_Enemy1.PushBack({ 1505, 603, 85, 144 });
	rightWalkAnim_Enemy1.PushBack({ 1663, 603, 85, 144 });
	rightWalkAnim_Enemy1.PushBack({ 1820, 603, 85, 144 });
	rightWalkAnim_Enemy1.loop = true;
	rightWalkAnim_Enemy1.speed = 0.3f;

	leftWalkAnim_Enemy1.PushBack({ 719, 27, 85, 144 });
	leftWalkAnim_Enemy1.PushBack({ 876, 27, 85, 144 });
	leftWalkAnim_Enemy1.PushBack({ 1033, 27, 85, 144 });
	leftWalkAnim_Enemy1.PushBack({ 1190, 27, 85, 144 });
	leftWalkAnim_Enemy1.PushBack({ 1348, 27, 85, 144 });
	leftWalkAnim_Enemy1.PushBack({ 1505, 27, 85, 144 });
	leftWalkAnim_Enemy1.PushBack({ 1663, 27, 85, 144 });
	leftWalkAnim_Enemy1.PushBack({ 1820, 27, 85, 144 });
	leftWalkAnim_Enemy1.loop = true;
	leftWalkAnim_Enemy1.speed = 0.3f;

	downWalkAnim_Enemy1.PushBack({ 719, 891, 85, 144 });
	downWalkAnim_Enemy1.PushBack({ 876, 891, 85, 144 });
	downWalkAnim_Enemy1.PushBack({ 1033, 891, 85, 144 });
	downWalkAnim_Enemy1.PushBack({ 1190, 891, 85, 144 });
	downWalkAnim_Enemy1.PushBack({ 1348, 891, 85, 144 });
	downWalkAnim_Enemy1.PushBack({ 1505, 891, 85, 144 });
	downWalkAnim_Enemy1.PushBack({ 1663, 891, 85, 144 });
	downWalkAnim_Enemy1.PushBack({ 1820, 891, 85, 144 });
	downWalkAnim_Enemy1.loop = true;
	downWalkAnim_Enemy1.speed = 0.3f;

	upWalkAnim_Enemy1.PushBack({ 719, 315, 85, 144 });
	upWalkAnim_Enemy1.PushBack({ 876, 315, 85, 144 });
	upWalkAnim_Enemy1.PushBack({ 1033, 315, 85, 144 });
	upWalkAnim_Enemy1.PushBack({ 1190, 315, 85, 144 });
	upWalkAnim_Enemy1.PushBack({ 1348, 315, 85, 144 });
	upWalkAnim_Enemy1.PushBack({ 1505, 315, 85, 144 });
	upWalkAnim_Enemy1.PushBack({ 1663, 315, 85, 144 });
	upWalkAnim_Enemy1.PushBack({ 1820, 315, 85, 144 });
	upWalkAnim_Enemy1.loop = true;
	upWalkAnim_Enemy1.speed = 0.3f;

	rightDownWalkAnim_Enemy1.PushBack({ 719, 747, 85, 144 });
	rightDownWalkAnim_Enemy1.PushBack({ 876, 747, 85, 144 });
	rightDownWalkAnim_Enemy1.PushBack({ 1033, 747, 85, 144 });
	rightDownWalkAnim_Enemy1.PushBack({ 1190, 747, 85, 144 });
	rightDownWalkAnim_Enemy1.PushBack({ 1348, 747, 85, 144 });
	rightDownWalkAnim_Enemy1.PushBack({ 1505, 747, 85, 144 });
	rightDownWalkAnim_Enemy1.PushBack({ 1663, 747, 85, 144 });
	rightDownWalkAnim_Enemy1.PushBack({ 1820, 747, 85, 144 });
	rightDownWalkAnim_Enemy1.loop = true;
	rightDownWalkAnim_Enemy1.speed = 0.3f;

	leftDownWalkAnim_Enemy1.PushBack({ 719, 1035, 85, 144 });
	leftDownWalkAnim_Enemy1.PushBack({ 876, 1035, 85, 144 });
	leftDownWalkAnim_Enemy1.PushBack({ 1033, 1035, 85, 144 });
	leftDownWalkAnim_Enemy1.PushBack({ 1190, 1035, 85, 144 });
	leftDownWalkAnim_Enemy1.PushBack({ 1348, 1035, 85, 144 });
	leftDownWalkAnim_Enemy1.PushBack({ 1505, 1035, 85, 144 });
	leftDownWalkAnim_Enemy1.PushBack({ 1663, 1035, 85, 144 });
	leftDownWalkAnim_Enemy1.PushBack({ 1820, 1035, 85, 144 });
	leftDownWalkAnim_Enemy1.loop = true;
	leftDownWalkAnim_Enemy1.speed = 0.3f;

	rightUpWalkAnim_Enemy1.PushBack({ 719, 459, 85, 144 });
	rightUpWalkAnim_Enemy1.PushBack({ 876, 459, 85, 144 });
	rightUpWalkAnim_Enemy1.PushBack({ 1033, 459, 85, 144 });
	rightUpWalkAnim_Enemy1.PushBack({ 1190, 459, 85, 144 });
	rightUpWalkAnim_Enemy1.PushBack({ 1348, 459, 85, 144 });
	rightUpWalkAnim_Enemy1.PushBack({ 1505, 459, 85, 144 });
	rightUpWalkAnim_Enemy1.PushBack({ 1663, 459, 85, 144 });
	rightUpWalkAnim_Enemy1.PushBack({ 1820, 459, 85, 144 });
	rightUpWalkAnim_Enemy1.loop = true;
	rightUpWalkAnim_Enemy1.speed = 0.3f;

	leftUpWalkAnim_Enemy1.PushBack({ 719, 171, 85, 144 });
	leftUpWalkAnim_Enemy1.PushBack({ 876, 171, 85, 144 });
	leftUpWalkAnim_Enemy1.PushBack({ 1033, 171, 85, 144 });
	leftUpWalkAnim_Enemy1.PushBack({ 1190, 171, 85, 144 });
	leftUpWalkAnim_Enemy1.PushBack({ 1348, 171, 85, 144 });
	leftUpWalkAnim_Enemy1.PushBack({ 1505, 171, 85, 144 });
	leftUpWalkAnim_Enemy1.PushBack({ 1663, 171, 85, 144 });
	leftUpWalkAnim_Enemy1.PushBack({ 1820, 171, 85, 144 });
	leftUpWalkAnim_Enemy1.loop = true;
	leftUpWalkAnim_Enemy1.speed = 0.3f;

	
	//ATTACK

	rightAttackAnim_Enemy1.PushBack({ 2608, 603, 85, 144 });
	rightAttackAnim_Enemy1.PushBack({ 2450, 603, 85, 144 });
	rightAttackAnim_Enemy1.PushBack({ 2293, 603, 85, 144 });
	rightAttackAnim_Enemy1.PushBack({ 2135, 603, 85, 144 });
	rightAttackAnim_Enemy1.PushBack({ 1978, 603, 85, 144 });
	rightAttackAnim_Enemy1.PushBack({ 2135, 603, 85, 144 });
	rightAttackAnim_Enemy1.PushBack({ 2293, 603, 85, 144 });
	rightAttackAnim_Enemy1.PushBack({ 2450, 603, 85, 144 });
	rightAttackAnim_Enemy1.PushBack({ 2608, 603, 85, 144 });
	rightAttackAnim_Enemy1.loop = true;
	rightAttackAnim_Enemy1.speed = 0.3f;

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
	leftAttackAnim_Enemy1.speed = 0.3f;

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
	downAttackAnim_Enemy1.speed = 0.3f;

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
	upAttackAnim_Enemy1.speed = 0.3f;

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
	rightDownAttackAnim_Enemy1.speed = 0.3f;


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
	leftDownAttackAnim_Enemy1.speed = 0.3f;

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
	rightUpAttackAnim_Enemy1.speed = 0.3f;

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
	leftUpAttackAnim_Enemy1.speed = 0.3f;


	//SPAWN

	rightSpawnAnim_Enemy1.PushBack({ 5758, 603, 85, 144 });
	rightSpawnAnim_Enemy1.PushBack({ 5915, 603, 85, 144 });
	rightSpawnAnim_Enemy1.PushBack({ 6073, 603, 85, 144 });
	rightSpawnAnim_Enemy1.PushBack({ 6230, 603, 85, 144 });
	rightSpawnAnim_Enemy1.PushBack({ 6388, 603, 85, 144 });
	rightSpawnAnim_Enemy1.PushBack({ 6545, 603, 85, 144 });
	rightSpawnAnim_Enemy1.PushBack({ 6703, 603, 85, 144 });
	rightSpawnAnim_Enemy1.PushBack({ 6860, 603, 85, 144 });
	rightSpawnAnim_Enemy1.loop = true;
	rightSpawnAnim_Enemy1.speed = 0.3f;

	leftSpawnAnim_Enemy1.PushBack({ 5758, 27, 85, 144 });
	leftSpawnAnim_Enemy1.PushBack({ 5915, 27, 85, 144 });
	leftSpawnAnim_Enemy1.PushBack({ 6073, 27, 85, 144 });
	leftSpawnAnim_Enemy1.PushBack({ 6230, 27, 85, 144 });
	leftSpawnAnim_Enemy1.PushBack({ 6388, 27, 85, 144 });
	leftSpawnAnim_Enemy1.PushBack({ 6545, 27, 85, 144 });
	leftSpawnAnim_Enemy1.PushBack({ 6703, 27, 85, 144 });
	leftSpawnAnim_Enemy1.PushBack({ 6860, 27, 85, 144 });
	leftSpawnAnim_Enemy1.loop = true;
	leftSpawnAnim_Enemy1.speed = 0.3f;

	downSpawnAnim_Enemy1.PushBack({ 5758, 891, 85, 144 });
	downSpawnAnim_Enemy1.PushBack({ 5915, 891, 85, 144 });
	downSpawnAnim_Enemy1.PushBack({ 6073, 891, 85, 144 });
	downSpawnAnim_Enemy1.PushBack({ 6230, 891, 85, 144 });
	downSpawnAnim_Enemy1.PushBack({ 6388, 891, 85, 144 });
	downSpawnAnim_Enemy1.PushBack({ 6545, 891, 85, 144 });
	downSpawnAnim_Enemy1.PushBack({ 6703, 891, 85, 144 });
	downSpawnAnim_Enemy1.PushBack({ 6860, 891, 85, 144 });
	downSpawnAnim_Enemy1.loop = true;
	downSpawnAnim_Enemy1.speed = 0.3f;

	upSpawnAnim_Enemy1.PushBack({ 5758, 315, 85, 144 });
	upSpawnAnim_Enemy1.PushBack({ 5915, 315, 85, 144 });
	upSpawnAnim_Enemy1.PushBack({ 6073, 315, 85, 144 });
	upSpawnAnim_Enemy1.PushBack({ 6230, 315, 85, 144 });
	upSpawnAnim_Enemy1.PushBack({ 6388, 315, 85, 144 });
	upSpawnAnim_Enemy1.PushBack({ 6545, 315, 85, 144 });
	upSpawnAnim_Enemy1.PushBack({ 6703, 315, 85, 144 });
	upSpawnAnim_Enemy1.PushBack({ 6860, 315, 85, 144 });
	upSpawnAnim_Enemy1.loop = true;
	upSpawnAnim_Enemy1.speed = 0.3f;

	rightDownSpawnAnim_Enemy1.PushBack({ 5758, 747, 85, 144 });
	rightDownSpawnAnim_Enemy1.PushBack({ 5915, 747, 85, 144 });
	rightDownSpawnAnim_Enemy1.PushBack({ 6073, 747, 85, 144 });
	rightDownSpawnAnim_Enemy1.PushBack({ 6230, 747, 85, 144 });
	rightDownSpawnAnim_Enemy1.PushBack({ 6388, 747, 85, 144 });
	rightDownSpawnAnim_Enemy1.PushBack({ 6545, 747, 85, 144 });
	rightDownSpawnAnim_Enemy1.PushBack({ 6703, 747, 85, 144 });
	rightDownSpawnAnim_Enemy1.PushBack({ 6860, 747, 85, 144 });
	rightDownSpawnAnim_Enemy1.loop = true;
	rightDownSpawnAnim_Enemy1.speed = 0.3f;

	leftDownSpawnAnim_Enemy1.PushBack({ 5758, 1035, 85, 144 });
	leftDownSpawnAnim_Enemy1.PushBack({ 5915, 1035, 85, 144 });
	leftDownSpawnAnim_Enemy1.PushBack({ 6073, 1035, 85, 144 });
	leftDownSpawnAnim_Enemy1.PushBack({ 6230, 1035, 85, 144 });
	leftDownSpawnAnim_Enemy1.PushBack({ 6388, 1035, 85, 144 });
	leftDownSpawnAnim_Enemy1.PushBack({ 6545, 1035, 85, 144 });
	leftDownSpawnAnim_Enemy1.PushBack({ 6703, 1035, 85, 144 });
	leftDownSpawnAnim_Enemy1.PushBack({ 6860, 1035, 85, 144 });
	leftDownSpawnAnim_Enemy1.loop = true;
	leftDownSpawnAnim_Enemy1.speed = 0.3f;

	rightUpSpawnAnim_Enemy1.PushBack({ 5758, 459, 85, 144 });
	rightUpSpawnAnim_Enemy1.PushBack({ 5915, 459, 85, 144 });
	rightUpSpawnAnim_Enemy1.PushBack({ 6073, 459, 85, 144 });
	rightUpSpawnAnim_Enemy1.PushBack({ 6230, 459, 85, 144 });
	rightUpSpawnAnim_Enemy1.PushBack({ 6388, 459, 85, 144 });
	rightUpSpawnAnim_Enemy1.PushBack({ 6545, 459, 85, 144 });
	rightUpSpawnAnim_Enemy1.PushBack({ 6703, 459, 85, 144 });
	rightUpSpawnAnim_Enemy1.PushBack({ 6860, 459, 85, 144 });
	rightUpSpawnAnim_Enemy1.loop = true;
	rightUpSpawnAnim_Enemy1.speed = 0.3f;

	leftUpSpawnAnim_Enemy1.PushBack({ 5758, 171, 85, 144 });
	leftUpSpawnAnim_Enemy1.PushBack({ 5915, 171, 85, 144 });
	leftUpSpawnAnim_Enemy1.PushBack({ 6073, 171, 85, 144 });
	leftUpSpawnAnim_Enemy1.PushBack({ 6230, 171, 85, 144 });
	leftUpSpawnAnim_Enemy1.PushBack({ 6388, 171, 85, 144 });
	leftUpSpawnAnim_Enemy1.PushBack({ 6545, 171, 85, 144 });
	leftUpSpawnAnim_Enemy1.PushBack({ 6703, 171, 85, 144 });
	leftUpSpawnAnim_Enemy1.PushBack({ 6860, 171, 85, 144 });
	leftUpSpawnAnim_Enemy1.loop = true;
	leftUpSpawnAnim_Enemy1.speed = 0.3f;


	//DIE

	rightDieAnim_Enemy1.PushBack({ 3553, 603, 85, 144 });
	rightDieAnim_Enemy1.PushBack({ 3710, 603, 85, 144 });
	rightDieAnim_Enemy1.PushBack({ 3868, 603, 85, 144 });
	rightDieAnim_Enemy1.PushBack({ 4025, 603, 85, 144 });
	rightDieAnim_Enemy1.PushBack({ 4183, 603, 85, 144 });
	rightDieAnim_Enemy1.PushBack({ 4340, 603, 85, 144 });
	rightDieAnim_Enemy1.loop = true;
	rightDieAnim_Enemy1.speed = 0.3f;

	leftDieAnim_Enemy1.PushBack({ 3553, 27, 85, 144 });
	leftDieAnim_Enemy1.PushBack({ 3710, 27, 85, 144 });
	leftDieAnim_Enemy1.PushBack({ 3868, 27, 85, 144 });
	leftDieAnim_Enemy1.PushBack({ 4025, 27, 85, 144 });
	leftDieAnim_Enemy1.PushBack({ 4183, 27, 85, 144 });
	leftDieAnim_Enemy1.PushBack({ 4340, 27, 85, 144 });
	leftDieAnim_Enemy1.loop = true;
	leftDieAnim_Enemy1.speed = 0.3f;

	downDieAnim_Enemy1.PushBack({ 3553, 891, 85, 144 });
	downDieAnim_Enemy1.PushBack({ 3710, 891, 85, 144 });
	downDieAnim_Enemy1.PushBack({ 3868, 891, 85, 144 });
	downDieAnim_Enemy1.PushBack({ 4025, 891, 85, 144 });
	downDieAnim_Enemy1.PushBack({ 4183, 891, 85, 144 });
	downDieAnim_Enemy1.PushBack({ 4340, 891, 85, 144 });
	downDieAnim_Enemy1.loop = true;
	downDieAnim_Enemy1.speed = 0.3f;

	upDieAnim_Enemy1.PushBack({ 3553, 315, 85, 144 });
	upDieAnim_Enemy1.PushBack({ 3710, 315, 85, 144 });
	upDieAnim_Enemy1.PushBack({ 3868, 315, 85, 144 });
	upDieAnim_Enemy1.PushBack({ 4025, 315, 85, 144 });
	upDieAnim_Enemy1.PushBack({ 4183, 315, 85, 144 });
	upDieAnim_Enemy1.PushBack({ 4340, 315, 85, 144 });
	upDieAnim_Enemy1.loop = true;
	upDieAnim_Enemy1.speed = 0.3f;

	rightDownDieAnim_Enemy1.PushBack({ 3553, 747, 85, 144 });
	rightDownDieAnim_Enemy1.PushBack({ 3710, 747, 85, 144 });
	rightDownDieAnim_Enemy1.PushBack({ 3868, 747, 85, 144 });
	rightDownDieAnim_Enemy1.PushBack({ 4025, 747, 85, 144 });
	rightDownDieAnim_Enemy1.PushBack({ 4183, 747, 85, 144 });
	rightDownDieAnim_Enemy1.PushBack({ 4340, 747, 85, 144 });
	rightDownDieAnim_Enemy1.loop = true;
	rightDownDieAnim_Enemy1.speed = 0.3f;

	leftDownDieAnim_Enemy1.PushBack({ 3553, 1035, 85, 144 });
	leftDownDieAnim_Enemy1.PushBack({ 3710, 1035, 85, 144 });
	leftDownDieAnim_Enemy1.PushBack({ 3868, 1035, 85, 144 });
	leftDownDieAnim_Enemy1.PushBack({ 4025, 1035, 85, 144 });
	leftDownDieAnim_Enemy1.PushBack({ 4183, 1035, 85, 144 });
	leftDownDieAnim_Enemy1.PushBack({ 4340, 1035, 85, 144 });
	leftDownDieAnim_Enemy1.loop = true;
	leftDownDieAnim_Enemy1.speed = 0.3f;

	rightUpDieAnim_Enemy1.PushBack({ 3553, 459, 85, 144 });
	rightUpDieAnim_Enemy1.PushBack({ 3710, 459, 85, 144 });
	rightUpDieAnim_Enemy1.PushBack({ 3868, 459, 85, 144 });
	rightUpDieAnim_Enemy1.PushBack({ 4025, 459, 85, 144 });
	rightUpDieAnim_Enemy1.PushBack({ 4183, 459, 85, 144 });
	rightUpDieAnim_Enemy1.PushBack({ 4340, 459, 85, 144 });
	rightUpDieAnim_Enemy1.loop = true;
	rightUpDieAnim_Enemy1.speed = 0.3f;

	leftUpDieAnim_Enemy1.PushBack({ 3553, 171, 85, 144 });
	leftUpDieAnim_Enemy1.PushBack({ 3710, 171, 85, 144 });
	leftUpDieAnim_Enemy1.PushBack({ 3868, 171, 85, 144 });
	leftUpDieAnim_Enemy1.PushBack({ 4025, 171, 85, 144 });
	leftUpDieAnim_Enemy1.PushBack({ 4183, 171, 85, 144 });
	leftUpDieAnim_Enemy1.PushBack({ 4340, 171, 85, 144 });
	leftUpDieAnim_Enemy1.loop = true;
	leftUpDieAnim_Enemy1.speed = 0.3f;


	//CRITICAL DIE

	rightCriticalDieAnim_Enemy1.PushBack({ 4498, 603, 85, 144 });
	rightCriticalDieAnim_Enemy1.PushBack({ 4655, 603, 85, 144 });
	rightCriticalDieAnim_Enemy1.PushBack({ 4813, 603, 85, 144 });
	rightCriticalDieAnim_Enemy1.PushBack({ 4970, 603, 85, 144 });
	rightCriticalDieAnim_Enemy1.PushBack({ 5128, 603, 85, 144 });
	rightCriticalDieAnim_Enemy1.PushBack({ 5285, 603, 85, 144 });
	rightCriticalDieAnim_Enemy1.PushBack({ 5443, 603, 85, 144 });
	rightCriticalDieAnim_Enemy1.PushBack({ 5600, 603, 85, 144 });
	rightCriticalDieAnim_Enemy1.loop = true;
	rightCriticalDieAnim_Enemy1.speed = 0.3f;

	leftCriticalDieAnim_Enemy1.PushBack({ 4498, 27, 85, 144 });
	leftCriticalDieAnim_Enemy1.PushBack({ 4655, 27, 85, 144 });
	leftCriticalDieAnim_Enemy1.PushBack({ 4813, 27, 85, 144 });
	leftCriticalDieAnim_Enemy1.PushBack({ 4970, 27, 85, 144 });
	leftCriticalDieAnim_Enemy1.PushBack({ 5128, 27, 85, 144 });
	leftCriticalDieAnim_Enemy1.PushBack({ 5285, 27, 85, 144 });
	leftCriticalDieAnim_Enemy1.PushBack({ 5443, 27, 85, 144 });
	leftCriticalDieAnim_Enemy1.PushBack({ 5600, 27, 85, 144 });
	leftCriticalDieAnim_Enemy1.loop = true;
	leftCriticalDieAnim_Enemy1.speed = 0.3f;

	downCriticalDieAnim_Enemy1.PushBack({ 4498, 891, 85, 144 });
	downCriticalDieAnim_Enemy1.PushBack({ 4655, 891, 85, 144 });
	downCriticalDieAnim_Enemy1.PushBack({ 4813, 891, 85, 144 });
	downCriticalDieAnim_Enemy1.PushBack({ 4970, 891, 85, 144 });
	downCriticalDieAnim_Enemy1.PushBack({ 5128, 891, 85, 144 });
	downCriticalDieAnim_Enemy1.PushBack({ 5285, 891, 85, 144 });
	downCriticalDieAnim_Enemy1.PushBack({ 5443, 891, 85, 144 });
	downCriticalDieAnim_Enemy1.PushBack({ 5600, 891, 85, 144 });
	downCriticalDieAnim_Enemy1.loop = true;
	downCriticalDieAnim_Enemy1.speed = 0.3f;

	upCriticalDieAnim_Enemy1.PushBack({ 4498, 315, 85, 144 });
	upCriticalDieAnim_Enemy1.PushBack({ 4655, 315, 85, 144 });
	upCriticalDieAnim_Enemy1.PushBack({ 4813, 315, 85, 144 });
	upCriticalDieAnim_Enemy1.PushBack({ 4970, 315, 85, 144 });
	upCriticalDieAnim_Enemy1.PushBack({ 5128, 315, 85, 144 });
	upCriticalDieAnim_Enemy1.PushBack({ 5285, 315, 85, 144 });
	upCriticalDieAnim_Enemy1.PushBack({ 5443, 315, 85, 144 });
	upCriticalDieAnim_Enemy1.PushBack({ 5600, 315, 85, 144 });
	upCriticalDieAnim_Enemy1.loop = true;
	upCriticalDieAnim_Enemy1.speed = 0.3f;

	rightDownCriticalDieAnim_Enemy1.PushBack({ 4498, 747, 85, 144 });
	rightDownCriticalDieAnim_Enemy1.PushBack({ 4655, 747, 85, 144 });
	rightDownCriticalDieAnim_Enemy1.PushBack({ 4813, 747, 85, 144 });
	rightDownCriticalDieAnim_Enemy1.PushBack({ 4970, 747, 85, 144 });
	rightDownCriticalDieAnim_Enemy1.PushBack({ 5128, 747, 85, 144 });
	rightDownCriticalDieAnim_Enemy1.PushBack({ 5285, 747, 85, 144 });
	rightDownCriticalDieAnim_Enemy1.PushBack({ 5443, 747, 85, 144 });
	rightDownCriticalDieAnim_Enemy1.PushBack({ 5600, 747, 85, 144 });
	rightDownCriticalDieAnim_Enemy1.loop = true;
	rightDownCriticalDieAnim_Enemy1.speed = 0.3f;

	leftDownCriticalDieAnim_Enemy1.PushBack({ 4498, 1035, 85, 144 });
	leftDownCriticalDieAnim_Enemy1.PushBack({ 4655, 1035, 85, 144 });
	leftDownCriticalDieAnim_Enemy1.PushBack({ 4813, 1035, 85, 144 });
	leftDownCriticalDieAnim_Enemy1.PushBack({ 4970, 1035, 85, 144 });
	leftDownCriticalDieAnim_Enemy1.PushBack({ 5128, 1035, 85, 144 });
	leftDownCriticalDieAnim_Enemy1.PushBack({ 5285, 1035, 85, 144 });
	leftDownCriticalDieAnim_Enemy1.PushBack({ 5443, 1035, 85, 144 });
	leftDownCriticalDieAnim_Enemy1.PushBack({ 5600, 1035, 85, 144 });
	leftDownCriticalDieAnim_Enemy1.loop = true;
	leftDownCriticalDieAnim_Enemy1.speed = 0.3f;

	rightUpCriticalDieAnim_Enemy1.PushBack({ 4498, 459, 85, 144 });
	rightUpCriticalDieAnim_Enemy1.PushBack({ 4655, 459, 85, 144 });
	rightUpCriticalDieAnim_Enemy1.PushBack({ 4813, 459, 85, 144 });
	rightUpCriticalDieAnim_Enemy1.PushBack({ 4970, 459, 85, 144 });
	rightUpCriticalDieAnim_Enemy1.PushBack({ 5128, 459, 85, 144 });
	rightUpCriticalDieAnim_Enemy1.PushBack({ 5285, 459, 85, 144 });
	rightUpCriticalDieAnim_Enemy1.PushBack({ 5443, 459, 85, 144 });
	rightUpCriticalDieAnim_Enemy1.PushBack({ 5600, 459, 85, 144 });
	rightUpCriticalDieAnim_Enemy1.loop = true;
	rightUpCriticalDieAnim_Enemy1.speed = 0.3f;

	leftUpCriticalDieAnim_Enemy1.PushBack({ 4498, 171, 85, 144 });
	leftUpCriticalDieAnim_Enemy1.PushBack({ 4655, 171, 85, 144 });
	leftUpCriticalDieAnim_Enemy1.PushBack({ 4813, 171, 85, 144 });
	leftUpCriticalDieAnim_Enemy1.PushBack({ 4970, 171, 85, 144 });
	leftUpCriticalDieAnim_Enemy1.PushBack({ 5128, 171, 85, 144 });
	leftUpCriticalDieAnim_Enemy1.PushBack({ 5285, 171, 85, 144 });
	leftUpCriticalDieAnim_Enemy1.PushBack({ 5443, 171, 85, 144 });
	leftUpCriticalDieAnim_Enemy1.PushBack({ 5600, 171, 85, 144 });
	leftUpCriticalDieAnim_Enemy1.loop = true;
	leftUpCriticalDieAnim_Enemy1.speed = 0.3f;
	

	position.x = x;
	position.y = y;

	collider = app->collisions->AddCollider({ position.x, position.y - 46, 25, 56 }, Collider::Type::ENEMY, (Module*)app->entity_manager);

	Spitter_Zombie_List.add(app->physics->CreateWalkingEnemyBox(position.x, position.y, 25, 10));
	
	
	
}

bool Zombie_Spitter::Update(float dt)
{
	//ADD THE PATHFINDING LOGIC FOR MOVEMENT
	
	if (app->player->pauseMenu == true)
	{
		iPoint NewPosition = position;
		collider->SetPos(NewPosition.x, NewPosition.y - 46);
		Spitter_Zombie_List.end->data->GetPosition(NewPosition.x, NewPosition.y);
		currentAnim = &idleDownAnim_Enemy1;
		currentAnim->loop = false;

		return true;
	}
	if (app->player->pauseMenu == false)
	{
		Spitter_Zombie_List.end->data->GetPosition(position.x, position.y);

		if (entityState == GameState::OutOfCombat)
		{
			//move normally

			if (app->inventoryMenu->ActiveRadioAlive == true)
			{
				if (position.DistanceTo(app->inventoryMenu->ActiveRadioPosition) < 300)
				{
					collider->SetPos(position.x, position.y - 46);
					Spitter_Zombie_List.end->data->GetPosition(position.x, position.y);
					currentAnim = &idleDownAnim_Enemy1;
					currentAnim->loop = true;

					if (position.x > app->inventoryMenu->ActiveRadioPosition.x)
					{
						if (currentAnim != &leftWalkAnim_Enemy1)
						{
							leftWalkAnim_Enemy1.Reset();
							currentAnim = &leftWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ -0.5f, 0.0f });
					}
					if (position.x < app->inventoryMenu->ActiveRadioPosition.x)
					{
						if (currentAnim != &rightWalkAnim_Enemy1)
						{
							rightWalkAnim_Enemy1.Reset();
							currentAnim = &rightWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.5f, 0.0f });
					}
					if (position.y > app->inventoryMenu->ActiveRadioPosition.y)
					{
						if (currentAnim != &upWalkAnim_Enemy1)
						{
							upWalkAnim_Enemy1.Reset();
							currentAnim = &upWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.0f, -0.5f });
					}
					if (position.y < app->inventoryMenu->ActiveRadioPosition.y)
					{
						if (currentAnim != &downWalkAnim_Enemy1)
						{
							downWalkAnim_Enemy1.Reset();
							currentAnim = &downWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.0f, 0.5f });
					}


					if ((app->inventoryMenu->ActiveRadioPosition.y > position.y) && (app->inventoryMenu->ActiveRadioPosition.x > position.x))
					{
						if (currentAnim != &rightDownWalkAnim_Enemy1)
						{
							rightDownWalkAnim_Enemy1.Reset();
							currentAnim = &rightDownWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.5f, 0.5f });
					}
					if ((app->inventoryMenu->ActiveRadioPosition.x < position.x) && (app->inventoryMenu->ActiveRadioPosition.y > position.y))
					{
						if (currentAnim != &leftDownWalkAnim_Enemy1)
						{
							rightDownWalkAnim_Enemy1.Reset();
							currentAnim = &rightDownWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ -0.5f, 0.5f });
					}
					if ((app->inventoryMenu->ActiveRadioPosition.y < position.y) && (app->inventoryMenu->ActiveRadioPosition.x < position.x))
					{
						if (currentAnim != &leftUpWalkAnim_Enemy1)
						{
							leftUpWalkAnim_Enemy1.Reset();
							currentAnim = &leftUpWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ -0.5f, -0.5f });
					}
					if ((app->inventoryMenu->ActiveRadioPosition.x > position.x) && (app->inventoryMenu->ActiveRadioPosition.y < position.y))
					{
						if (currentAnim != &rightUpWalkAnim_Enemy1)
						{
							leftUpWalkAnim_Enemy1.Reset();
							currentAnim = &leftUpWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.5f, -0.5f });
					}
				}
				else
				{
					collider->SetPos(position.x, position.y - 46);
					Spitter_Zombie_List.end->data->GetPosition(position.x, position.y);
					currentAnim = &idleDownAnim_Enemy1;
					currentAnim->loop = true;

					Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.0f,0.0f });

				}
			}
			if (app->inventoryMenu->ActiveRadioAlive == false)
			{
				if (position.DistanceTo(app->player->position) < 300)
				{
					collider->SetPos(position.x, position.y - 46);
					Spitter_Zombie_List.end->data->GetPosition(position.x, position.y);
					currentAnim = &idleDownAnim_Enemy1;
					currentAnim->loop = true;

					if (position.x > app->player->position.x)
					{
						if (currentAnim != &leftWalkAnim_Enemy1)
						{
							leftWalkAnim_Enemy1.Reset();
							currentAnim = &leftWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ -0.5f, 0.0f });
					}
					if (position.x < app->player->position.x)
					{
						if (currentAnim != &rightWalkAnim_Enemy1)
						{
							rightWalkAnim_Enemy1.Reset();
							currentAnim = &rightWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.5f, 0.0f });
					}
					if (position.y > app->player->position.y)
					{
						if (currentAnim != &upWalkAnim_Enemy1)
						{
							upWalkAnim_Enemy1.Reset();
							currentAnim = &upWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.0f, -0.5f });
					}
					if (position.y < app->player->position.y)
					{
						if (currentAnim != &downWalkAnim_Enemy1)
						{
							downWalkAnim_Enemy1.Reset();
							currentAnim = &downWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.0f, 0.5f });
					}


					if ((app->player->position.y > position.y) && (app->player->position.x > position.x))
					{
						if (currentAnim != &rightDownWalkAnim_Enemy1)
						{
							rightDownWalkAnim_Enemy1.Reset();
							currentAnim = &rightDownWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.5f, 0.5f });
					}
					if ((app->player->position.x < position.x) && (app->player->position.y > position.y))
					{
						if (currentAnim != &leftDownWalkAnim_Enemy1)
						{
							rightDownWalkAnim_Enemy1.Reset();
							currentAnim = &rightDownWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ -0.5f, 0.5f });
					}
					if ((app->player->position.y < position.y) && (app->player->position.x < position.x))
					{
						if (currentAnim != &leftUpWalkAnim_Enemy1)
						{
							leftUpWalkAnim_Enemy1.Reset();
							currentAnim = &leftUpWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ -0.5f, -0.5f });
					}
					if ((app->player->position.x > position.x) && (app->player->position.y < position.y))
					{
						if (currentAnim != &rightUpWalkAnim_Enemy1)
						{
							leftUpWalkAnim_Enemy1.Reset();
							currentAnim = &leftUpWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.5f, -0.5f });
					}
				}
				else
				{
					collider->SetPos(position.x, position.y - 46);
					Spitter_Zombie_List.end->data->GetPosition(position.x, position.y);
					currentAnim = &idleDownAnim_Enemy1;
					currentAnim->loop = true;

					Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.0f,0.0f });

				}

				if (position.DistanceTo(app->player->position) < 100)
				{
					app->entity_manager->RegisterEntitesInCombat(this);
					entityState = GameState::InCombat;
					app->player->entityStatePlayer = GameState::InCombat;
					app->player->entityTurnPlayer = TurnState::NONE;
					app->game_manager->StartTurnManagement = true;
				}
			}

			

			return true;

		}

		if (entityState == GameState::InCombat)
		{

			if (EntityHP > 0)
			{
				if (entityTurn == TurnState::NONE)
				{
					//Assigning order of turns
					collider->SetPos(position.x, position.y - 46);
					Spitter_Zombie_List.end->data->GetPosition(position.x, position.y);
					currentAnim = &idleDownAnim_Enemy1;
					currentAnim->loop = true;

					Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.0f,0.0f });

				}
				if (entityTurn == TurnState::StartOfTurn)
				{
					collider->SetPos(position.x, position.y - 46);
					currentAnim = &idleDownAnim_Enemy1;
					currentAnim->loop = false;
					Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.0f, 0.0f }); //movimiento contrario a la direccion del jugador cuando nos chocamos con el

					entityTurn = TurnState::MidOfTurn;

				}
				if (entityTurn == TurnState::MidOfTurn)
				{

					collider->SetPos(position.x, position.y - 46);
					Spitter_Zombie_List.end->data->GetPosition(position.x, position.y);
					currentAnim = &idleDownAnim_Enemy1;
					currentAnim->loop = true;
					counter++;

					if (position.x > app->player->position.x)
					{
						if (currentAnim != &leftWalkAnim_Enemy1)
						{
							leftWalkAnim_Enemy1.Reset();
							currentAnim = &leftWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ -0.5f, 0.0f });
					}
					if (position.x < app->player->position.x)
					{
						if (currentAnim != &rightWalkAnim_Enemy1)
						{
							rightWalkAnim_Enemy1.Reset();
							currentAnim = &rightWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.5f, 0.0f });
					}
					if (position.y > app->player->position.y)
					{
						if (currentAnim != &upWalkAnim_Enemy1)
						{
							upWalkAnim_Enemy1.Reset();
							currentAnim = &upWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.0f, -0.5f });
					}
					if (position.y < app->player->position.y)
					{
						if (currentAnim != &downWalkAnim_Enemy1)
						{
							downWalkAnim_Enemy1.Reset();
							currentAnim = &downWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.0f, 0.5f });
					}


					if ((app->player->position.y > position.y) && (app->player->position.x > position.x))
					{
						if (currentAnim != &rightDownWalkAnim_Enemy1)
						{
							rightDownWalkAnim_Enemy1.Reset();
							currentAnim = &rightDownWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.5f, 0.5f });
					}
					if ((app->player->position.x < position.x) && (app->player->position.y > position.y))
					{
						if (currentAnim != &leftDownWalkAnim_Enemy1)
						{
							rightDownWalkAnim_Enemy1.Reset();
							currentAnim = &rightDownWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ -0.5f, 0.5f });
					}
					if ((app->player->position.y < position.y) && (app->player->position.x < position.x))
					{
						if (currentAnim != &leftUpWalkAnim_Enemy1)
						{
							leftUpWalkAnim_Enemy1.Reset();
							currentAnim = &leftUpWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ -0.5f, -0.5f });
					}
					if ((app->player->position.x > position.x) && (app->player->position.y < position.y))
					{
						if (currentAnim != &rightUpWalkAnim_Enemy1)
						{
							leftUpWalkAnim_Enemy1.Reset();
							currentAnim = &leftUpWalkAnim_Enemy1;
						}
						Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.5f, -0.5f });
					}

					if (counter == 150) entityTurn = TurnState::FinishTurn;

				}
				if (entityTurn == TurnState::FinishTurn)
				{
					//Change turn from enemy to player turn still have to develop a way to do it correctly
					Spitter_Zombie_List.end->data->body->SetLinearVelocity({ 0.0f, 0.0f });
					collider->SetPos(position.x, position.y - 46);
					Spitter_Zombie_List.end->data->GetPosition(position.x, position.y);

					currentAnim = &idleDownAnim_Enemy1;
					currentAnim->loop = true;

					if (position.DistanceTo(app->player->position) < 150)
					{
						if ((position.x == app->player->position.x) && (position.y < app->player->position.y))
						{
							app->particles->RangedAttack.speed.y = 5;
							app->particles->AddParticle(app->particles->RangedAttack, position.x, position.y + 30, Collider::Type::ENEMY_RANGED_ATTACK);

						}
						if ((position.x == app->player->position.x) && (position.y > app->player->position.y))
						{
							app->particles->RangedAttack.speed.y = -5;
							app->particles->AddParticle(app->particles->RangedAttack, position.x, position.y - 30, Collider::Type::ENEMY_RANGED_ATTACK);

						}
						if ((position.x < app->player->position.x) && (position.y == app->player->position.y))
						{

							app->particles->AddParticle(app->particles->RangedAttack, position.x + 30, position.y, Collider::Type::ENEMY_RANGED_ATTACK);


						}
						if ((position.x > app->player->position.x) && (position.y == app->player->position.y))
						{
							app->particles->RangedAttack.speed.x *= -1;
							app->particles->AddParticle(app->particles->RangedAttack, position.x - 30, position.y, Collider::Type::ENEMY_RANGED_ATTACK);


						}

						if ((position.x > app->player->position.x) && (position.y   > app->player->position.y))
						{
							app->particles->RangedAttack.speed.x *= -1;
							app->particles->RangedAttack.speed.y = ((app->player->position.y - position.y) / ((app->player->position.x - position.x) / app->particles->RangedAttack.speed.x));
							app->particles->AddParticle(app->particles->RangedAttack, position.x - 30, position.y - 30, Collider::Type::ENEMY_RANGED_ATTACK);


						}
						if ((position.x > app->player->position.x) && (position.y   < app->player->position.y))
						{
							app->particles->RangedAttack.speed.x *= -1;
							app->particles->RangedAttack.speed.y = ((app->player->position.y - position.y) / ((app->player->position.x - position.x) / app->particles->RangedAttack.speed.x));
							app->particles->AddParticle(app->particles->RangedAttack, position.x - 30, position.y + 30, Collider::Type::ENEMY_RANGED_ATTACK);


						}
						if ((position.x < app->player->position.x) && (position.y   > app->player->position.y))
						{
							app->particles->RangedAttack.speed.y = ((app->player->position.y - position.y) / ((app->player->position.x - position.x) / app->particles->RangedAttack.speed.x));
							app->particles->AddParticle(app->particles->RangedAttack, position.x + 30, position.y - 30, Collider::Type::ENEMY_RANGED_ATTACK);


						}
						if ((position.x < app->player->position.x) && (position.y   < app->player->position.y))
						{
							app->particles->RangedAttack.speed.y = ((app->player->position.y - position.y) / ((app->player->position.x - position.x) / app->particles->RangedAttack.speed.x));
							app->particles->AddParticle(app->particles->RangedAttack, position.x + 30, position.y + 30, Collider::Type::ENEMY_RANGED_ATTACK);


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
					//Change turn from enemy to player turn still have to develop a way to do it correctly
					counter = 0;
					collider->SetPos(position.x, position.y - 46);
					Spitter_Zombie_List.end->data->GetPosition(position.x, position.y);
					currentAnim = &idleDownAnim_Enemy1;
					currentAnim->loop = true;



				}
				if (app->sceneMainMap->playerRestart == true)
				{
					app->game_manager->counter = 0;
					entityState = GameState::OutOfCombat;
					entityTurn = TurnState::NONE;
				}
				//Escape Combat
				/*if (app->player->escapeCombat == true)
				{
					app->game_manager->counter = 0;
					entityState = GameState::OutOfCombat;
					entityTurn = TurnState::NONE;
				}*/
			}


			if (EntityHP == 0)
			{
				SetToDelete();
			}


		}

	}
	return true;
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