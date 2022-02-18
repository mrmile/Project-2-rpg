#ifndef __WALKING_ENEMY_H__
#define __WALKING_ENEMY_H__

#include "Enemy.h"


class Walking_Enemy : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Walking_Enemy(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update(float dt) override;

	

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	
	//NEED TO ADD THE ANIMATIONS
	Animation Walking_Enemy_Right;
	Animation Walking_Enemy_Left;

	int counter;
};

#endif 