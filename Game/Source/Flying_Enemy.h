#ifndef __FLYING_ENEMY_H__
#define __FLYING_ENEMY_H__

#include "Enemy.h"


class Flying_Enemy : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Flying_Enemy(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update(float dt) override;

	
	int NewPos = 0;
	

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	
	//NEED TO ADD ANIMATIONS
	
	Animation Flying_Enemy_Right;
	Animation Flying_Enemy_Left;

};

#endif // __ENEMY_BROWNSHIP_H__