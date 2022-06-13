#ifndef __FINAL_BOSS_H__
#define __FINAL_BOSS_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Final_Boss : public Entity
{
public:
	
	Final_Boss(int x,int y);

	
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

	//DIE

	Animation rightDieAnim_Enemy1;
	Animation leftDieAnim_Enemy1;
	Animation downDieAnim_Enemy1;
	Animation upDieAnim_Enemy1;

	Animation rightDownDieAnim_Enemy1;
	Animation leftDownDieAnim_Enemy1;
	Animation rightUpDieAnim_Enemy1;
	Animation leftUpDieAnim_Enemy1;
	
	
	int counter = 0;
};

#endif 