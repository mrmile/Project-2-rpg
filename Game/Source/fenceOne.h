#ifndef __FENCE_ONE_H__
#define __FENCE_ONE_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class FenceOne : public Entity
{
public:

	FenceOne(int x, int y);


	bool Update(float dt) override;



private:

	Animation fenceOne;
	
	int counter;
};

#endif 
