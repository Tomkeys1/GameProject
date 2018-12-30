
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

private:
	real GetRadius(Gameobject* gb);

	Math::Vec3 GetAxis(Math::Vec3 point1, Math::Vec3 point2);
	bool isProjectionIntersecting(Math::Vec3 aCorners[], Math::Vec3 bCorners[], Math::Vec3 normal);
	void GetMinMaxOfProjection(Math::Vec3 corners[], Math::Vec3 axis, real& min, real& max);


	bool CheckCollision(Gameobject* gb);

	real collisionRange = 40;
};
