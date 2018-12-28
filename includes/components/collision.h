
#pragma once

//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "component.h"

//Class Movement that is derived from class Component.
class Collision : public Component
{
	//Declare the public functions that are overwritten.
public:
	Collision();

	void Initialize(Gameobject* gb);
	virtual void Update(void) override;
	virtual void Cleanup(void) override;

	void PushBack(void);

	bool CheckCollision(Gameobject* gb);

private:
	real collisionRange = 40;
};
