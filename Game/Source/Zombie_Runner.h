#ifndef __ZOMBIE_RUNNER_H__
#define __ZOMBIE_RUNNER_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class Zombie_Runner : public Entity
{
public:
	
	Zombie_Runner(int x,int y);

	
	bool Update(float dt) override;

	
	

private:

	Animation Idle_Enemy;
	
	Animation rightWalkAnim_Enemy;
	Animation leftWalkAnim_Enemy;
	Animation downWalkAnim_Enemy;
	Animation upWalkAnim_Enemy;

	Animation rightDownWalkAnim_Enemy;
	Animation leftDownWalkAnim_Enemy;
	Animation rightUpWalkAnim_Enemy;
	Animation leftUpWalkAnim_Enemy;


	int counter;
};

#endif 