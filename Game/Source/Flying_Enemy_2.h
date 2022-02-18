#ifndef __FLYING_ENEMY_2_H__
#define __FLYING_ENEMY_2_H__

#include "Enemy.h"


class Flying_Enemy_2 : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Flying_Enemy_2(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update(float dt) override;

	
	
	

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	
	//NEED TO ADD ANIMATIONS
	Animation Flying_Enemy_2_Right;
	Animation Flying_Enemy_2_Left;

};

#endif // __ENEMY_BROWNSHIP_H__