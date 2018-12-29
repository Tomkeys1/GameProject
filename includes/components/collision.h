
#pragma once

//EXTERNAL INCLUDES
//INTERNAL INCLUDES
#include "component.h"
#include "math/vector3.h"
#include "math/vector2.h"
#include "math/mat4x4.h"

//Class Movement that is derived from class Component.
class Collision : public Component
{
	//Declare the public functions that are overwritten.
public:
	Collision();

	void Initialize(Gameobject* gb);
	virtual void Update(void) override;
	virtual void Cleanup(void) override;

	bool CheckCollision(Gameobject* gb);
	Math::Vec3 GetBoxPosition(Gameobject* gb, fColorRGBA pos);

private:

	real collisionRange = 40;
};
