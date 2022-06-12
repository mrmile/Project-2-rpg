#ifndef __MINI_BOSS_ONE_H__
#define __MINI_BOSS_ONE_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Mini_Boss_One : public Entity
{
public:

	Mini_Boss_One(int x, int y);


	void Update(float dt) override;

	void PathfindingTo(iPoint destination);


private:

	// IDLE

	Animation idleRightAnim_Enemy1;
	Animation idleLeftAnim_Enemy1;
	Animation idleDownAnim_Enemy1;
	Animation idleUpAnim_Enemy1;

	Animation idleUpLeftAnim_Enemy1;
	Animation idleUpRightAnim_Enemy1;
	Animation idleDownLeftAnim_Enemy1;
	Animation idleDownRightAnim_Enemy1;


	//WALK

	Animation rightWalkAnim_Enemy1;
	Animation leftWalkAnim_Enemy1;
	Animation downWalkAnim_Enemy1;
	Animation upWalkAnim_Enemy1;

	Animation rightDownWalkAnim_Enemy1;
	Animation leftDownWalkAnim_Enemy1;
	Animation rightUpWalkAnim_Enemy1;
	Animation leftUpWalkAnim_Enemy1;


	//ATTACK

	Animation rightAttackAnim_Enemy1;
	Animation leftAttackAnim_Enemy1;
	Animation downAttackAnim_Enemy1;
	Animation upAttackAnim_Enemy1;

	Animation rightDownAttackAnim_Enemy1;
	Animation leftDownAttackAnim_Enemy1;
	Animation rightUpAttackAnim_Enemy1;
	Animation leftUpAttackAnim_Enemy1;

	//DIE

	Animation rightDieAnim_Enemy1;
	Animation leftDieAnim_Enemy1;
	Animation downDieAnim_Enemy1;
	Animation upDieAnim_Enemy1;

	Animation rightDownDieAnim_Enemy1;
	Animation leftDownDieAnim_Enemy1;
	Animation rightUpDieAnim_Enemy1;
	Animation leftUpDieAnim_Enemy1;

	int counter;

	int RunningNumber;
};

#endif 
