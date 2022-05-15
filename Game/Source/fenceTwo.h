#ifndef __FENCE_TWO_H__
#define __FENCE_TWO_H__

#include "Entity.h"
#include "Point.h"
#include "DynArray.h"


class FenceTwo : public Entity
{
public:

	FenceTwo(int x, int y);


	void Update(float dt) override;



private:

	Animation fenceTwo;

	int counter;
};

#endif 