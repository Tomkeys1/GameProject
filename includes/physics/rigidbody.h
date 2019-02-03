
#pragma once
//EXTERNAL INCLUDES
#include <limits>
//INTERNAL INCLUDES
#include "typedefs/types.h"
#include "typedefs/utils.h"
#include "math/vector3.h"
#include "typedefs/components.h"

class Gameobject;
class Collision;

class Rigidbody
{
	//Declare the public functions that are overwritten.
public:
	Rigidbody(Gameobject* gb);

	void Update(void);
	void Cleanup(void);

	void SetGravityCenter(Gameobject* gb = nullptr);
	void AddForce(Math::Vec3 direction, real force);

	Math::Vec3 GetImpactDirection();
	Math::Vec3 GetImpactNormal();

	bool RayCast(Math::Vec3 start, Math::Vec3 end);
	bool RayCast(Math::Vec3 start, Math::Vec3 end, RaycastInfo& hitInfo);
	RigidbodyValues& GetRigidbodyValues();

private:
	void Gravity(void);
	real CalculateVelocity(real force);

	RigidbodyValues rigidBody;

	//Gravity
	const real gravityConstant = 0.000000000006674f; // Gravity constant 6.674 * 10 ^ -11
	real gravity;
	real massOfCenter;
	Math::Vec3 gravityCenter;

	//

	Collision* collision;

	Gameobject* gameobject;
	Gameobject* gravityGb;
};